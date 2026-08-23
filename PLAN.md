# PLAN: Encapsulate libudpard in a `cyphal::Interface` implementation

**Status:** In progress — steps 4–5 complete (socket abstraction + `CyphalUDPInterface` + GoogleTest suite); hypha adapter and app refactor remain.
**Issue:** https://github.com/emrainey/embedded-superloop/issues/61
**Branch (when started):** `issue-61`, tracking `develop`

## Summary

Extract the libudpard plumbing inlined in `applications/nucleo-cyphal/source/CyphalApp.cpp` (~400 of 795 lines) into a reusable `jarnax::cyphal::CyphalUDPInterface` implementing `jarnax::cyphal::Interface`. Applications stop touching udpard directly.

## Estimate

4–7 days total including tests.

## Steps

1. Branch `issue-61` off `develop`.
2. [complete] Move the shared O1Heap pool into `jarnax-cyphal-udp`, implement `core::Allocator`, and provide libudpard memory-resource factories.
3. [complete] Add host-runnable GoogleTest coverage for the allocator and libudpard callbacks.
4. [complete] Socket abstraction: `source/include/jarnax/services/CyphalUDPSocket.hpp` (`udp::Endpoint`, `DatagramHandler`, `Socket` with Join/Leave/Send). Time comes from an injected `MicrosecondClock` (generic modules cannot include cortex headers).
5. [complete] `CyphalUDPInterface` in `source/services/CyphalUDPInterface.cpp` + internal header: all 6 `Interface` virtuals + `Loopable::Execute` TX drain + `DatagramHandler::OnDatagramReceived` RX dispatch; per-port transfer-ID counters; priority fixed Nominal; remembered request transfer-IDs for responses; fragment gather into scratch buffer; statistics.
6. Hypha adapter for the socket abstraction.
7. [complete] GoogleTest suite `tests/gtest-cyphal-udpinterface.cpp` with `tests/mocks/jarnax/services/MockUDPSocket.hpp`: Listen/Remove/IsListening lifecycle, Join-once semantics, Send publish/request/respond, TX error stats, RX subject round-trip, RPC request→response round-trip, unknown-group/bad-datagram handling. Valid RX datagrams are produced with a local `UdpardTx` producer (no hand-built wire formats). 62/62 pass on LLVM and AppleClang; both cross presets build.
8. Refactor `CyphalApp` onto `CyphalUDPInterface`; verify on hardware via pylink/RTT + yactui.
9. Run all presets and `./scripts/build-all-presets.sh`; PR against `develop`.

## Key design decisions

- Do **not** extend `Metadata` with priority/transfer-ID yet — priority is constant Nominal; per-port transfer-ID counters live inside the interface; response transfers echo the transfer-ID of the last remembered request from that client.
- Constructor takes `O1HeapPool&`, node-ID, `udp::Socket&`, and `MicrosecondClock&` — no singletons reached from inside; no cortex dependency so the generic module stays host-testable.
- Single redundant interface initially; `TransportStatistics` reports one interface entry.
- RX transfers are gathered into a contiguous scratch buffer bounded by `MaxExtent`; empty transfers are delivered as zero-length messages.
- Service ports share one RPC multicast group; Join is issued once for the first port and Leave when the last port is removed.

## Acceptance criteria

- No udpard types leak into application code.
- All host unit tests pass on LLVM and AppleClang; cross builds unbroken.
- nucleo-cyphal behaves identically on hardware.
