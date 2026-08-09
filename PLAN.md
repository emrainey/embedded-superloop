# PLAN: uavcan.node.GetInfo service server in CyphalApp

Issue: #44 (server half) — branch `issue-44` (tracks `develop`).
Depends/scope: this PR is **server only**; the client scanner is a separate issue (#45).

## Summary

Add the service-side half of `uavcan.node.GetInfo.1.0` (fixed port-ID `430`) to the
`nucleo::cyphal::CyphalApp` in `applications/nucleo-cyphal`. The app already publishes a
Heartbeat on subject 7509 (publisher) and has a libudpard v1 subscription. We need to also:

1. Create a `UdpardRxRPCDispatcher` (one per node) initialized with the same O1Heap-backed
   memory resources as the existing subject subscription.
2. Register one service **request** RX port for `430` so requests addressed to our node-ID
   are accepted/reassembled.
3. Route incoming UDP datagrams to the *subject subscription* or the *RPC dispatcher* based
   on `metadata.destination_address` (subject multicast 239.255.x vs service multicast 239.1.0.<node_id>).
4. Register the service membership for `239.1.0.<node_id>` (via `HyphaIpPrepareUdpReceive`),
   so multicast requests from scanners (e.g. yakut / bus-monitor) are delivered.
5. On a completed request: build a `uavcan_node_GetInfo_Response_1_0` with an **assigned**
   node name / versions / unique-id (hard-coded constants for now), serialize it, and
   `udpardTxRespond` using the same service-ID, the request's client node-ID and its transfer-ID.

## Design decisions

- **Assigned identity**: per requirement the unique-ID / name / versions are assigned
  (not MAC-derived):
  - name = `com.emrainey.superloop.nucleo` (DSDL allowed charset: `.` `-` `_` and a-z0-9).
  - protocol_version = {1, 0}, hardware_version kept {0,0} for now.
  - software_vcs_revision_id = 0 (TBD) — can be filled later.
  - unique_id = `{0xDE,0xAD,0xBE,0xEF,0x10..0xC0}` 16 bytes (assigned).
- **Membership**: Reuse `HyphaIpPrepareUdpReceive` with the dispatcher's derived endpoint
  (`239.1.0.103`). The ETH MPL filter in `Execute()` already whitelists the service multicast
  group — keep it there.
- **Transport flow**: `OnReceiveUdp` stays as-is except a new early branch that detects
  service-multicast datagrams via the cached group address. `ProcessTransmitQueue()` already
  drains whatever `udpardTxRequest/Respond` enqueues, so responses transmit via the existing
  UDP TX path.
- **TID / deadlines**: match existing heartbeat style (`udpardTxRespond(&tx_, now+..., prio,
  service_id, client_node_id, transfer_id, payload, user_reference)`).

## Steps

1. Write a Catch2 host test file `catch2-cyphal-getinfo-server.cpp` covering:
   - GetInfo Request serialization → 0 bytes (sealed), deserialize no-op.
   - GetInfo Response serialize/deserialize round trip incl. vcs, unique_id, name.
2. Implement in `CyphalApp`:
   - Members: `UdpardRxRPCDispatcher service_dispatcher_`, `UdpardRxRPCPort get_info_service_port_`,
     cached `HyphaIpIPv4Address_t service_group_address_`, `bool service_initialized_`.
   - New `ServiceDispatcherInit()`: init + start dispatcher (port 430, is_request=true),
     store the group IP, join membership.
   - In `Execute()`: lazy-init the dispatcher once udpard is running.
   - In `OnReceiveUdp`: compare `metadata.destination_address` against the cached group; if
     equal → `udpardRxRPCDispatcherReceive`, else subject subscription.
   - New `ServiceResponseHandler(...)` that, on `is_request && service_id==430`, constructs the
     response and `udpardTxRespond`s.
3. Update CMake test list (add the new Catch2 file).
4. Build / test hosts + cross, then build-all-presets + act.

## Progress

- [x] Host unit test file written and passing (`test-cyphal-getinfo-server-none-all`,
      4 tests / 21 assertions) on LLVM and AppleClang.
- [x] `ServiceDispatcherInit()` implemented; lazy-called from `Execute()`.
- [x] `OnReceiveUdp` routes service-multicast datagrams to the RPC dispatcher.
- [x] `ServiceResponseHandler()` builds the assigned response and `udpardTxRespond`s.
- [x] M7 firmware compiles + links; M4 workflow builds; all LLVM/AppleClang host tests pass.
- [ ] GOTCHAS entries, build-all-presets, act, commit, PR.

## Gotchas (add to GOTCHAS)

- Generated `GetInfo_1_0.h` `initialize_()` inlines a `deserialize_` from a 1-byte stack buffer;
  GCC's `-Warray-bounds` (with `-Werror`) rejects it. Workaround: `memset` the response to zero
  instead of calling `uavcan_node_GetInfo_Response_1_0_initialize_()` (all defaults are zero).
- `HyphaIpIsSameIPv4Address` is declared only in `hypha_internal.h`, not the public
  `hypha_ip.h`; use a local `memcmp`-based helper instead.
- Udpard v1: server reuses the request's transfer-ID in the response (client-side transfer
  tracking is out of scope; see #45).

## Out of scope (see #45)

- Client scanner: registering a response port, per-server transfer counters, scanning
  *several* node IDs, and logging the arriving responses.
EOF
