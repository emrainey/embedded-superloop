# Gotchas

## 2026-08-05 — Intermittent HardFault during GlobalContext construction (nucleo-cyphal, STM32H753ZI)

- **Symptom:** Occasionally the target faults with a corrupt `blx r3` (vtable call to address `0x00010000`)
  at `0x0800af72` inside `CountDown::Restart`, which runs during construction of
  `GlobalContext::monitor_` — *before* `cyphal_app_` is even constructed.
- **Root cause:** Not a bug in the CyphalApp v1.x port. The fault occurs on the board's
  normal static-init path (`CountDown`/`Monitor`/`Timer`), which the port does not touch.
  Repeated resets + single-stepping through the exact same init path ran cleanly to Thread mode.
- **Conclusion:** Known flakiness of this hardware/flash session, not deterministic code. When
  reproducing, reset and re-run; the fault is not reliably repeatable. Do not chase this as a
  regression from a CyphalApp change unless it becomes consistently reproducible.

## 2026-08-05 — RTT reads are intermittently empty (buffer contention)

- **Symptom:** `pylink-square-mcp rtt_read` sometimes returns nothing even though the target
  is publishing (heartbeat/stats appear on the next read).
- **Workaround:** Reset the RTT tracked offset with `since=reset`, then run for a few seconds
  and read again. If a capture shows an unexpected counter dip (e.g. `IGMP: tx=0`), re-run;
  it is read-side timing, not a TX regression.

## 2026-08-08 — PRIx64/PRId64/PRIu64 undefined in CI with Debian/Ubuntu `gcc-arm-none-eabi`

- **Symptom:** `error: expected ')' before 'PRIx64'` when compiling with
  `arm-none-eabi-gcc` (14.2.1) from Debian/Ubuntu, even with `<inttypes.h>` included.
  GCC even mis-suggests `#include <inttypes.h>`. This is NOT a code bug.
- **Root cause:** Ubuntu/Debian split the newlib headers (`/usr/include/newlib/`) from the
  toolchain. GCC ships its own self-contained `/usr/lib/gcc/arm-none-eabi/*/include/stdint.h`
  which shadows newlib's `<stdint.h>`. newlib's `<inttypes.h>` gates all 64-bit PRI/SCN
  macros behind `#if __int64_t_defined` (inttypes.h:216), and `__int64_t_defined` is only set
  by newlib's `sys/_stdint.h` — which is never reached. Upstream Debian bugs #953844/#1067692;
  the Debian patch `provide-stdint-for-embedded` used to carry the missing wrapper.
- **Fix (container):** `bare-metal-dev` `Containerfile.ubuntu` appends
  `#include_next <stdint.h>` to `$(arm-none-eabi-gcc -print-file-name=include/stdint.h)` so
  GCC's stdint.h chains into newlib's. Same fix is in `distcc-bare-metal-builder`.
- **Gotcha:** the `bare-metal-dev` multi-arch workflow also fails on the arm64 QEMU leg because
  `sudo chmod` after `USER dev` is broken under buildx (setuid stripped, "effective uid is not
  0"). Fixed by creating the catalog 0644 for `dev`, appending without sudo, and restoring
  `chmod 444` as root. Alpine/Debian/Arch Containerfiles still use the old sudo pattern.
