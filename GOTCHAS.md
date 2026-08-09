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

## 2026-08-08 — nunavut-generated `initialize_()` trips GCC `-Warray-bounds` when called in firmware

- **Symptom:** `error: array subscript 536870911 is outside array bounds of 'const uint8_t [1]'`
  in the generated `GetInfo_1_0.h`, `-Werror` (with `-O2`) during the M7 ARM build. Fails in
  the *caller*, not the header — the `-isystem` path does not suppress it.
- **Root cause:** `uavcan_node_GetInfo_Response_1_0_initialize_()` inlines a
  `deserialize_()` fed a 1-byte stack buffer; unguarded `nunavutGetU64(&buffer[0], ...)`
  reads past it. Heartbeat's generated code happens to be bounds-guarded, so it compiles fine.
- **Fix:** do not call the generated `initialize_()` for Getinfo responses in firmware; instead
  `std::memset(&info, 0, sizeof(info))` — all GetInfo defaults are zero, so the result is
  identical. (Host tests keep `initialize_()`; LLVM/AppleClang do not flag the pattern.)

## 2026-08-08 — `HyphaIpIsSameIPv4Address` is not exported by the public `hypha_ip.h`

- **Symptom:** link/compile error referencing `HyphaIpIsSameIPv4Address` from app code that
  includes only `hypha_ip/hypha_ip.h`.
- **Root cause:** the helper is declared in `third-party/libhypha/source/include/hypha_ip/hypha_internal.h`
  (internal translation units) and not re-exported publicly.
- **Fix:** on-target code compares `HyphaIpIPv4Address_t` directly with a local
  `std::memcmp`/`==` helper (the struct is exactly `sizeof(uint32_t)`).

## 2026-08-09 — Bare-metal firmware link fails: `memmove` undefined (udpard uses it)

- **Symptom:** M7 (nucleo-cyphal) link error `undefined reference to memmove` when adding the
  GetInfo client, even though `memcpy`/`memset` link fine. Fails at link, not compile.
- **Root cause:** `udpardGather` (libudpard) calls standard `memmove` for overlap-safe copies,
  but the bare-metal `modules/memory` only supplied `memset` + `memcpy` (both wrapped under
  `#if defined(__arm__)` as `extern "C"`).
- **Fix:** added `memory::move` (overlap-safe: forward loop when `dst < src`, backward when
  `dst > src`) plus a `void*` overload, and an `extern "C" void *memmove(...)` wrapper in
  `modules/memory/source/memmove.cpp`. Registered only for cross builds in
  `modules/memory/CMakeLists.txt` (same `$<IF:$<BOOL:${BUILD_CROSS_TARGET}>...>` gate as
  memset/memcpy) so host tests don't collide with libc's memmove.
- **Gotcha:** the `memory::move` template must branch on `dst < src`/`dst > src` to remain
  overlap-safe; a plain forward `copy` loop corrupts overlapping ranges.

## 2026-08-08 — `on-host-native-gcc` preset cannot build on macOS/Darwin

- `g++-13` (homebrew) does not provide `cstddef`/libc++ headers, so any `module-core` TU fails
  with `fatal error: cstddef: No such file or directory`. This is pre-existing and unrelated to
  this change; AGENTS.md documents that the GCC host preset only works on Linux.
