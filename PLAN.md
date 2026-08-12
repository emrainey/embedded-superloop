# PLAN: Add SWO (Serial Wire Output) trace viewer to tools/jalo.py

Issue: #54 — branch `issue-54` (tracks `github/develop`). **STATUS: DONE,
awaiting human review before commit.**

## Summary

`tools/jalo.py` is the Textual TUI SVD/J-Link debugger. It has an RTT console
but no SWO (Serial Wire Output / ITM trace) viewer. This issue adds a SWO
Console tab mirroring the RTT Console UX, backed by the pylink-square SWO API,
plus CLI preconfiguration and host-run unit tests.

SWO target-side init (pin mux / DBGMCU / trace registers) is tracked
separately in #41 and is out of scope here. This issue is tool-side only:
capture and display SWO trace through the J-Link.

## Changes

1. **`JLinkController` SWO wrappers** (`tools/jalo.py`) — thin, guarded methods
   over the pylink-square SWO API:
   - `swo_enabled()`, `swo_enable(cpu_speed, swo_speed, port_mask)`,
   - `swo_start(swo_speed)`, `swo_stop()`, `swo_flush()`,
   - `swo_num_bytes()`, `swo_read(offset, num_bytes, remove=False)`,
   - `swo_read_stimulus(port, num_bytes)`.
   All return `False`/`None` (with `last_error`) instead of raising when not
   connected or on JLinkException.

2. **SWO Console tab** in `SVDDebuggerApp` (mirrors RTT tab):
   - Controls: CPU speed (Hz, default 480000000), SWO speed (Hz, default
     2000000), port mask (default 0x1), stimulus port (default 0), bytes to
     read, continuous-capture switch.
   - Buttons: Enable SWO, Start, Read, Stop, Clear.
   - `RichLog` output; stimulus-port data decoded as text with the same
     line-buffering approach as the RTT console.
   - SWO is stopped cleanly on disconnect and on unmount.

3. **CLI args** (`build_argument_parser`):
   - `--swo-cpu-speed`, `--swo-speed`, `--swo-port-mask`, `--swo-port`,
   - `--swo-auto-start` (enable SWO + begin capture after connecting).
   - Validation added in `parse_args`.

4. **Tests** (`tools/test_jalo_swo.py`, run via `.venv/bin/python -m pytest`):
   - `JLinkController` SWO methods against a mocked `pylink.JLink` (connected
     and disconnected paths, error paths, last_error capture).
   - `build_argument_parser`/`parse_args` SWO arg parsing and validation.
   - Pure decode/line-buffering helper tests (no hardware required).

## Verification

- `.venv/bin/python -m pytest tools/test_jalo_swo.py -v` — **54 passed**.
- `python3 -m py_compile tools/jalo.py tools/test_jalo_swo.py` — OK.
- Live probe smoke test (`JLinkController` against the J-Link remote server at
  127.0.0.1:19020, STM32H753ZI): connect, `swo_enable(480M, 2M, 0x1)`,
  `swo_start(2M)`, `swo_num_bytes()`, `swo_read_stimulus`, `swo_read`,
  `swo_stop`, disconnect all succeeded against real pylink. No trace bytes were
  returned because the target is not yet emitting ITM/SWO (target-side init is
  #41) — the empty-payload "no new data" path was exercised.
- No C++ source touched; firmware build presets unaffected.

## Gotchas

- pylink `swo_enable(cpu_speed, swo_speed, port_mask)` also programs the
  target ITM/DWT/TPIU registers (via `JLINKARM_SWO_EnableTarget`), so the tool
  only needs to provide CPU/SWO speeds; the GPIO/pin init is target firmware
  side (#41).
- `swo_read(offset, num_bytes, remove=False)` does NOT remove data unless
  `remove=True`; the console must either pass `remove=True` or call
  `swo_flush()` to avoid re-reading the same bytes.
- `swo_read_stimulus(port, num_bytes)` only returns printable data for the
  given stimulus port and is the right primitive for a console.
- With a target not emitting ITM trace, `swo_read_stimulus` returns an empty
  list (not `None`) — the console treats that as "no new data", so guard on
  `data is None` for errors, not on empty payloads.
- Textual app tests need `run_test(size=(200, 50))` (SWO controls overflow the
  80x24 default), `pilot.pause()` after tab switches, and
  `active_effect_duration = 0` on re-clicked buttons (textual drops clicks
  while the `-active` animation class is set).
