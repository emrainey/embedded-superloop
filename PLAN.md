# PLAN: Add gtests for `cyphal::Node::Print` diagnostic records

Issue: #60 — branch `issue-60` (tracks `develop`; carries the user's
uncommitted diagnostic Record work: `Printer` interface, `Severity` enum,
`Node::Print`, `diagnostic_record_blob_`, `diagnostic_statistics_`).

## Summary

Add GoogleTest coverage for the diagnostic Record publishing added by the
human: `Node::Print(Severity, fmt, ...)` serializes a
`uavcan.diagnostic.Record.1.1` (subject 8184) and publishes it via the
interface.

## Changes

1. **`gtest-cyphal-node.cpp`** — new `TEST_F`s for `Node::Print`:
   - publishes a deserializable Record on `DiagnosticRecordSubjectId` with the
     expected severity and text,
   - text longer than 255 bytes is truncated to the DSDL capacity,
   - the `timestamp.microsecond` field reflects the timer,
   - `diagnostic_statistics_.passed` increments on a successful publish,
   - `diagnostic_statistics_.failed` increments when the interface `Send`
     fails.
   - `TestNode` accessor `GetDiagnosticStatistics()` exposing the protected
     `diagnostic_statistics_`.

## Production fixes required by the tests (all flagged/approved)

2. **`modules/jarnax/source/cyphal/Node.cpp`** — `Node::Print` called
   `jarnax::vsnprint`, which is *declared* in `jarnax/print.hpp` but has no
   definition anywhere in the repo. Changed to `core::vsnprint` (always linked
   into cyphal targets; keeps the test target lean). Approved by human.

3. **`modules/memory/source/copy.cpp`** — the definition was
   `copy(void*, void* const, size_t)` while the header declares
   `copy(void*, void const*, size_t)`. Different mangled symbols; the overload
   had never been linked before. Fixed the definition to match the header.

4. **`modules/memory/tests/catch2-strings.cpp`** — added 2 `TEST_CASE`s
   covering the fixed `copy(void*, void const*, size_t)` overload (mismatched
   element types to force the non-template overload, as in `Node::Print`).

## Verification

- `cmake --workflow --preset on-host-native-llvm` — 21/21 tests pass,
  including 5 new `Print` tests and 2 new memory `copy` tests.
- `cmake --workflow --preset on-host-native-clang` — 21/21 tests pass.
- Cross-builds: `on-target-cortex-m4-gcc-arm-none-eabi` and
  `on-target-cortex-m7-gcc-arm-none-eabi` still build clean.

## Notes

- The `Print` impl is the human's uncommitted work on this branch; the two
  production fixes above were the only changes needed and were approved before
  applying.