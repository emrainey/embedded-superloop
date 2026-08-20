# PLAN: Implement `uavcan.node.GetTransportStatistics` server in `cyphal::Node`

Issue: #59 — branch `issue-59` (based on `issue-58`, which contains the
`cyphal::Node`; the Node is not yet in `develop`).

**STATUS: DONE — awaiting human review before commit.**

## Summary

The `cyphal::Node` registers a server for `uavcan.node.GetTransportStatistics`
(434.0.1) in `RunOnce` but `Node::GetResponse` never handles that service id,
so requests time out. This issue implements the response by querying the
`cyphal::Interface` for its transport statistics and reporting them.

## Changes

1. **`Types.hpp`** — add transport-agnostic statistics types that the Interface
   reports and the Node serializes:
   - `InterfaceStatistics { num_emitted, num_received, num_errored }` (uint64_t,
     mirrors the DSDL `uavcan.node.IOStatistics.0.1` truncated uint40 fields).
   - `TransportStatistics { transfer, network_interfaces, num_interfaces }`.
   - `MaxNetworkInterfaces` constant bound to
     `uavcan_node_GetTransportStatistics_Response_0_1_MAX_NETWORK_INTERFACES`.

2. **`Interface.hpp`** — add pure virtual
   `core::Status GetStatistics(TransportStatistics& statistics) = 0;` so the
   Node can query the transport's counters.

3. **`MockInterface.hpp`** — add `MOCK_METHOD` for `GetStatistics`.

4. **`Node.hpp`** — add `get_transport_statistics_response_blob_` static blob
   for the serialized response.

5. **`Node.cpp`** — handle `GetTransportStatisticsServiceId` in
   `Node::GetResponse`: query `interface_.GetStatistics`, populate the DSDL
   `uavcan_node_GetTransportStatistics_Response_0_1` (transfer_statistics plus
   per-interface `network_interface_statistics`), serialize into the blob.

6. **Tests** (`gtest-cyphal-node.cpp`) — cover the response contents:
   - transfer + per-interface statistics are echoed from the interface.
   - zero/empty interface statistics.
   - interface failure still yields a **successful response with zeroed**
     statistics (the response type has no "unavailable" field, so the request
     is answered rather than left to time out).

## Verification

- `cmake --workflow --preset on-host-native-llvm` — **21/21 passed** (cyphal suite 40/40).
- `cmake --workflow --preset on-host-native-clang` — **21/21 passed**.
- Cross-builds: `on-target-cortex-m4-gcc-arm-none-eabi` and
  `on-target-cortex-m7-gcc-arm-none-eabi` both build clean (incl. nucleo-cyphal app).
- New tests: `GetTransportStatisticsResponseContainsInterfaceStatistics`,
  `GetTransportStatisticsResponseHandlesNoInterfaces`,
  `GetTransportStatisticsResponseReportsZerosWhenInterfaceFails` — all pass.
- `./scripts/build-all-presets.sh` does not exist in this repo; the four presets above are the
  equivalent verification.

## Notes

- Branch `issue-59` is based on `issue-58` because `cyphal::Node` only exists
  there; rebase onto `develop` after `issue-58` merges.