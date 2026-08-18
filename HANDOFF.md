# HANDOFF: Continue implementing Cyphal Services on nucleo-cyphal

Status: **Discovery phase only. No code written.** Prepared 2026-08-13.

## What the human asked for

Implement, next, on the `nucleo-cyphal` application:
1. `uavcan.node.ExecuteCommand` (fixed port-ID **435**) — server side.
2. `uavcan.register.Access` (**384**) / `uavcan.register.List` (**385**) — server side.

## Current state of nucleo-cyphal (all merged into `develop`)

The app lives in `applications/nucleo-cyphal/`. Already implemented:
- `uavcan.node.Heartbeat` (7509) publication — every 1 s.
- `uavcan.diagnostic.Record` (8184) publication — every 1 s.
- `uavcan.node.GetInfo` (430) **server** — issue #44.
- `uavcan.node.GetInfo` (430) **client scanner** — issue #45 (`GetInfoScanner` class, host-tested).

Key files:
- `applications/nucleo-cyphal/include/CyphalApp.hpp` — app state: `service_dispatcher_` (`UdpardRxRPCDispatcher`), `get_info_service_port_`, `get_info_response_port_` (`UdpardRxRPCPort`), `service_group_address_`.
- `applications/nucleo-cyphal/source/CyphalApp.cpp` — `ServiceDispatcherInit()` registers the GetInfo request+response ports; `OnReceiveUdp()` routes UDP datagrams to the dispatcher vs. the subject subscription based on `metadata->destination_address` (service multicast vs subject multicast); `ServiceResponseHandler()` / `GetInfoResponseHandler()`.
- `applications/nucleo-cyphal/include/GetInfoScanner.hpp` + `source/GetInfoScanner.cpp` — the host-testable scan window / transfer-ID tracker pattern to imitate for any client-side work.
- Tests: `applications/nucleo-cyphal/tests/` (`catch2-cyphal-getinfo-server.cpp`, `-client.cpp`, `-heartbeat.cpp`, `-record.cpp`), registered via `host_unit_test(...)` in `tests/CMakeLists.txt`.

## Design findings

### DSDL codegen already covers the new services

`external/CMakeLists.txt` `generate_cyphal_dsdl()` runs nunavut over the whole
`third-party/public_regulated_data_types/uavcan/` tree, so the headers already
exist in the build dir (example: `build/native-llvm/generated/cyphal-dsdl/`):

- `uavcan/node/ExecuteCommand_1_0.h` .. `_1_3.h` — **use 1.3** (the 1.0/1.1/1.2
  are `@deprecated`; 1.3 adds `COMMAND_IDENTIFY = 65529` and an `output` field in
  the response). Request: `uint16 command` + `parameter` (max 112 bytes). Response:
  `uint8 status` + `output`.
- `uavcan/_register/` — **note the namespace mangles to `_register`** because
  `register` is a C++ keyword:
  - `Access_1_0.h` → `uavcan_register_Access_Request_1_0` (name + value),
    `uavcan_register_Access_Response_1_0` (timestamp, `_mutable`, `persistent`, value).
  - `List_1_0.h` → request is just `uint16 index`; response is `uavcan_register_Name_1_0 name`.
  - `Name_1_0.h` → `{uint8 elements[256]; size_t count;}`.
  - `Value_1_0.h` → big C union (15 tags, max field 258 bytes), `_tag_` byte.
- Extents: Access req 515 B, Access resp 267 B, List resp 256 B, Value 259 B.

Include them as `#include "uavcan/_register/Access_1_0.h"` etc.

### RPC dispatcher handles multiple service ports

`udpardRxRPCDispatcherReceive` (libudpard v1.x, `third-party/libudpard/libudpard/udpard.h:1056`)
returns `>0` on a completed transfer and the transfer carries `service_id` and
`is_request`. So we register several request ports (384, 385, 435) via
`udpardRxRPCDispatcherListen(&dispatcher, &port, id, /*is_request=*/true, extent)`
and dispatch on `transfer.service_id`. This is the extension point for the
current single-GetInfo `ServiceResponseHandler` (CyphalApp.cpp:588) — it must
become a switch over service-id.

The service multicast group + `HyphaIpPrepareUdpReceive` are already set up in
`ServiceDispatcherInit()`; no new multicast memberships needed.

### RegisterStore — new host-testable component

Plan: a static-table register store following the `GetInfoScanner` precedent
(no target deps, host unit tests with Catch2):

- Fixed array of entries: name buffer + `uavcan_register_Value_1_0` value +
  `mutable`/`persistent` flags. Add `RegisterStore` in
  `applications/nucleo-cyphal/include/RegisterStore.hpp` (+ source).
- API sketch: `Count()`, `NameAt(index, out_name)` (empty when OOB — terminates
  List iteration), `Access(name, write_value, out_value, out_mutable, out_persistent)`
  implementing the spec's write-then-read semantics: write skipped when value is
  `empty` (tag 0) or register immutable; unknown name → empty value + cleared flags.
- Registers to expose (standard names from the 384.Access dsdl doc):
  - `uavcan.node.id` → natural16[1] = {103} (matches `CyphalApp::NodeId`).
  - `uavcan.node.description` → string, e.g. "nucleo-cyphal STM32H753ZI".
  - `uavcan.pub.heartbeat.id` = 7509, `uavcan.srv.getinfo.id` = 430,
    `uavcan.srv.executecommand.id` = 435, `uavcan.srv.register_access.id` = 384,
    `uavcan.srv.register_list.id` = 385.
- Note: no NVS on the board yet → `persistent` flags will be claims only; either
  keep all non-persistent or document the gap in PLAN.md. `COMMAND_STORE_PERSISTENT_STATES`
  can respond SUCCESS as a no-op.

### ExecuteCommand server — what to support

- `COMMAND_RESTART` (65535): **no reset mechanism found yet** — grep for
  `NVIC_SystemReset`/`__DSB`/`SystemReset` across `modules/` returned nothing.
  Check `boards/nucleo_h753zi/include/BoardContext.hpp` (there is a `cortex`
  module); if none, either add a `cortex::system::Reset()` or respond
  `STATUS_BAD_STATE`/`STATUS_FAILURE` and log. **Investigate before wiring.**
- `COMMAND_STORE_PERSISTENT_STATES` (65530): SUCCESS no-op (no NVS).
- `COMMAND_EMERGENCY_STOP` (65531): could gate Heartbeat/Record publishing.
- `COMMAND_IDENTIFY` (65529): board has `status_pin_`/`error_pin_` GPIO pins in
  `BoardContext` — could blink; optional.
- Unknown commands → `STATUS_BAD_COMMAND`.

### Tests to write (host, Catch2)

- `catch2-cyphal-executecommand.cpp` — request/response DSDL round-trip; command
  enum serialization; response status values.
- `catch2-cyphal-register.cpp` — RegisterStore: Define/Count, NameAt bounds,
  Access read vs write, immutable write rejected, empty-value write skipped,
  unknown name → empty value.
- `catch2-cyphal-register-dsdl.cpp` (or fold in) — Access/List/Value round-trips,
  string/union tag select/check helpers.
- Register the new tests in `applications/nucleo-cyphal/tests/CMakeLists.txt` with
  `host_unit_test(NAME cyphal-... SOURCES ... LIBRARIES cyphal-dsdl CATCH2
  NO_CONFIGURATIONS NO_BOARDS)`.
- App-level service handlers behind hypha/udpard are not host-testable — add a
  mock + test plan per AGENTS.md (same caveat as GetInfo).

## Workflow reminders (from AGENTS.md)

- Write a `PLAN.md`, review with human before committing.
- `gh issue` lookup/create and branch `issue-N` tracking `develop`; PR to `develop`.
- Build/tests: `cmake --workflow --preset on-host-native-llvm`,
  `on-host-native-clang`; cross builds `on-target-cortex-m4-gcc-arm-none-eabi`,
  `on-target-cortex-m7-gcc-arm-none-eabi`. Native-GCC preset does not work on
  Darwin (see GOTCHAS.md). Run `./scripts/build-all-presets.sh` before PR.
- Update issue comments as progress is made.

## Open questions for the human

1. Reset mechanism for `COMMAND_RESTART` — is there a `cortex` reset API planned,
   or should this first pass answer `STATUS_BAD_STATE` and log?
2. Which ExecuteCommand version to target — 1.3 (non-deprecated) is the strong
   default unless yactui/tools expect 1.0.
3. Register set — confirm the port-ID registers list above is the right starting
   set, and whether `uavcan.node.description` should be mutable in RAM only.
