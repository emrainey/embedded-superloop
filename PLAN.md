# PLAN: Enable Serial Wire Output (SWO) for debug tracing

Issue: #41 — branch `issue-41` (tracks `github/develop`).

## Summary

On the H7 the Cortex-M7 TPIU (`0xE0040000`) does NOT drive the SWO pin. The trace
path is ITM → SWTF (`0x5C004000`) → SWO (`0x5C003000`) → PB3 (`TRACESWO`, AF0),
and the ST SWO block is driven from TRACECK. This change programs those ST blocks
and un-gates the debug clocks:

1. `DBGMCU_CR`: `TRACECLKEN` (bit 20), `D1DBGCKEN` (bit 21), `D3DBGCKEN` (bit 22).
2. `SWO` (`0x5C003000`): unlock via LAR, Async-NRZ mode (`SWO_SPPR`=2), baud
   prescaler (`SWO_CODR`, zero-based: `prescaler = trace_clock / baud - 1`).
3. `SWTF` (`0x5C004000`): unlock via LAR, `ENSO=1` to forward the ITM trace bus.
4. TRACECK follows `RCC_CFGR[SW]`; with SYSCLK = PLL1P, TRACECK = PLL1R. Board
   config gives VCO 800 MHz, `pll_r=8-1` → TRACECK = **100 MHz** → CODR = 43 for
   the 2.24 MBaud `basic` config.

The F4 has no ST SWO block (standard TPIU drives the pin), so its
`enable_serial_wire_output` is a documented no-op and `ClockTree.trace = sysclk`.

## Verified facts

- SWO/SWTF register layout per RM0433 Rev 8 §35.4; LAR unlock key `0xC5ACCE55`
  (`SWO_LAR`@0x5C003FB0, `SWTF_LAR`@0x5C004FB0). Reset values: SWTF_CTRL 0x300
  (bit 0 `ENSO` off), SWO_SWTF_PRIORITY 0x8.
- `DBGMCU_CR` field names confirmed from SVD: `trace_clock_enable` (bit 20),
  `domain1_debug_clock_enable` (bit 21), `domain3_debug_clock_enable` (bit 22).
  The D3 domain holds the SWO/SWTF blocks, so D3DBGCKEN must be set.
- PB3 = `JTDO/TRACESWO`, AF0 (datasheet stm32h753zi.txt line 6873), unused by any
  board pin.
- The SVD has no RCC trace-clock mux field on the H7 — TRACECK is derived from
  SYSCLK selection; the STM32H753.svd has no SWO/SWTF description, so the headers
  were hand-written in the peripheralyzer style (per-register struct with
  `Fields bits` + `uint32_t whole`, `static_assert` on size/offsets,
  `sizeof(Swo)==sizeof(SwoTraceFunnel)==0xFB4`).
- **Link ordering**: module archives are scanned once, before the jarnax archive.
  Vendor symbols referenced only from `configure.cpp` do not link (same problem
  documented at `clocks.cpp:38` for `early_power`). The SWO call therefore lives
  in the vendor `clocks()`; `configure.cpp` keeps only `cortex::initialize::swo()`
  (TPIU/ITM, which is in the repeated cortex archive).

## Changes

1. **`modules/stm32/include/stm32/h7xx/Swo.hpp`** (new) — `Swo` peripheral at
   0x5C003000: `current_output_divisor` (`CODR`@0x010, 13-bit `prescaler`),
   `selected_pin_protocol` (`SWO_SPPR`@0x0F0), `lock_access` (`SWO_LAR`@0xFB0).
2. **`modules/stm32/include/stm32/h7xx/SwoTraceFunnel.hpp`** (new) — `SwoTraceFunnel`
   at 0x5C004000: `control` (`SWTF_CTRL`@0x000, bit 0 `enable_swo`),
   `priority` (`SWTF_PRIORITY`@0x004), `lock_access` (`SWTF_LAR`@0xFB0).
3. **`stm32h7xx.hpp`** — include both new headers; add externs
   `serial_wire_output` / `swo_trace_funnel` beside `debug`.
4. **`source/stm32h7xx/peripherals.cpp`** — UNITTEST RAM globals for the two new
   peripherals (same pattern as `debug`).
5. **`modules/stm32/linkerscripts/stm32h753zi-sections.ld`** — PROVIDE
   `_stm32_swo = 0x5C003000`, `_stm32_swo_trace_funnel = 0x5C004000` (mangled
   extern names also PROVIDEd).
6. **`modules/stm32/include/stm32/Initialize.hpp`** — declare
   `enable_serial_wire_output(core::units::Hertz trace_clock, std::uint32_t baud)`.
7. **`source/stm32h7xx/debug.cpp`** (new) — `enable_trace_port_clock()` (sets bits
   20/21/22, read-modify-write, idempotent) and `enable_serial_wire_output()`:
   unlock LARs, `transmit_mode = AsyncNRZ`, masked CODR write (whole register to
   dodge GCC `-Wconversion` on the 13-bit field), `SWTF_CTRL.ENSO = 1`.
8. **`source/stm32f4xx/debug.cpp`** (new) — no-op implementations of both
   functions (added to the F4 CMakeLists sources).
9. **`source/stm32h7xx/clocks.cpp`** — `clock_tree.trace = pll_vco / (pll_r + 1)`;
   at the end, `if constexpr (cortex::swo::enable)`
   `enable_serial_wire_output(trace, baud)` (cast to `std::uint32_t`). Called here,
   not from configure.cpp, for the link-ordering reason above.
10. **`source/stm32f4xx/clocks.cpp`** + **`stm32f4xx.hpp`** — `ClockTree.trace =
    sysclk`; same guarded no-op call.
11. **`modules/jarnax/source/configure.cpp`** — SWO vendor call removed; comment
    explains why it lives in the vendor `clocks()`. `cortex::initialize::swo()` kept.
12. **`modules/cortex/source/initialize.cpp`** — fix stale black-magic SWO URL
    comment.
13. **`boards/nucleo_h753zi/**`** — PB3 `swo_pin_` configured AF0 in `Initialize()`
    (matches existing AF pin pattern).
14. **`applications/nucleo-demo/source/Demo.cpp`** — TEMP trace-capture
    instrumentation removed; SWO marker emit + `cortex/swo.hpp` include retained.

## Tests

- **`modules/stm32/tests/gtest-stm32-debug.cpp`** (new, registered in
  `modules/stm32/tests/CMakeLists.txt` as `host_unit_test(NAME stm32-debug ...
  BOARDS nucleo_h753zi CONFIGURATIONS basic)`): 10 tests over the UNITTEST
  globals — Empty setup/teardown check; D3DBGCKEN set (bit 22); idempotence;
  unrelated CR bits preserved by RMW; LAR unlock values; AsyncNRZ protocol;
  CODR = 24 for 100 MHz/4 MBaud and 43 for 100 MHz/2.24 MBaud; ENSO enabled.
  All pass on host (llvm + clang).
- The register writes are hardware init; host coverage is register-level via the
  UNITTEST globals. Future emulator-based testing will exercise the end-to-end
  trace path (ITM → SWTF → SWO → pin).

## Verification

- Host: `cmake --workflow --preset on-host-native-llvm` and `-clang` — all pass.
- Cross: `cmake --workflow --preset on-target-cortex-m4-gcc-arm-none-eabi` and
  `-cortex-m7-gcc-arm-none-eabi` — all link and build clean.
- Live hardware (DONE): flashed `firmware-nucleo-demo-basic-nucleo_h753zi.elf`,
  reset+ran to `cortex::system::main()`. Single-session breakpoint dump at main
  entry (avoiding the J-Link's DBGMCU_CR clobber on connect) showed:
  - `DBGMCU_CR` = 0x00700007 (TRACECLKEN/D1DBGCKEN/D3DBGCKEN set; low bits are
    the J-Link's own DBG_SLEEP/STOP/STANDBY).
  - `SWO_CODR` = 0x2b (43) → 100 MHz / 2.24 MBaud.
  - `SWO_SPPR` = 2 → AsyncNRZ (UART).
  - `SWTF_CTRL` = 0x301 → reset 0x300 + ENSO.
  - A J-Link reconnect between sessions rewrites DBGMCU_CR to 0x07 (unclocks the
    D3 debug domain, making SWO/SWTF reads fail) — the firmware writes are only
    visible in a single session, which is why the in-session breakpoint dump was
    needed.
- PB3 waveform capture deferred: the tooling to read SWO bytes from the J-Link
  probe does not exist yet (issue #54).

## Gotchas

- Do NOT enable the H7 DBGMCU/SWO in a shared TU: F4 must not link H7
  `debug.cpp` (references `stm32::h7xx::debug`). The `add_module` CHIPS split
  handles this; F4 has its own no-op `debug.cpp`.
- **Archive ordering**: vendor symbols referenced only from `configure.cpp` are
  never extracted (single scan before jarnax). Keep vendor-init calls inside the
  vendor module (see the `early_power` FIXME at `clocks.cpp:38`).
- `std::size_t` → `std::uint32_t` for the baud needs an explicit cast on host
  builds (`-Wconversion -Werror`); identical types on ARM32.
- CODR is a 13-bit field; write the whole register with `& 0x1FFFU` to avoid
  `-Wconversion` on the truncated bitfield.
- `clocks(ClockConfiguration const&)` early-returns when SWS already = PLL (warm
  boot), so the SWO programming only runs on cold boots; DBGMCU/SWO/SWTF
  registers survive system reset, so this is acceptable.
- Deferred to issue #55: cold-POR boot hard-fault (CFSR IMPREISERR, HFSR
  0xC0000000) observed in `on_startup()` before `configure()`.
