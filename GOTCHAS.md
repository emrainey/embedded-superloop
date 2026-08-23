# Gotchas

## 2026-08-19 — Brace-ended `else` snippets are ambiguous targets for text edits

- **Symptom:** editing `modules/jarnax/source/cyphal/Node.cpp`, a search/replace for the
  pattern `} else {` intended for the end of `Node::GetResponse` silently matched the **first**
  occurrence in the file instead (inside `RunOnce`'s publisher period loop), inserting the new
  `else if (id == GetTransportStatisticsServiceId)` branch into the middle of `RunOnce`.
- **Root cause:** `} else {` appears multiple times across the file; a short oldString matches
  the earliest occurrence, not the one near the caret/context.
- **Fix / rule:** when replacing an `else`/`else if` tail, always anchor the oldString with
  enough surrounding context to be unique (e.g. include the preceding `} else if (...) {`
  block or a following `return ...;` line). Verify the diff landed in the intended function
  before building.

## 2026-08-12 — Vendor symbols referenced only from `configure.cpp` do not link (archive ordering)

- **Symptom:** `undefined reference to stm32::initialize::enable_serial_wire_output(core::units::Hertz, unsigned long)`
  at link time for **all** F4 apps AND all M7 apps that use jarnax `configure.cpp`, even though
  `nm` shows the symbol IS defined (`T`) in `libmodule-stm32-basic-<chip>.a` and the mangled name
  matches (`Em` = unsigned long = both `std::uint32_t` and `std::size_t` on ARM32).
- **Root cause:** module static-library archives are placed **once**, *before* the jarnax archive,
  on the link line (`libmodule-stm32-...a libarch-cortex-...a libmodule-jarnax-...a libarch-cortex-...a libmodule-jarnax-...a`).
  When ld scans the stm32 archive nothing has referenced the symbol yet, so the member is never
  extracted; by the time jarnax's reference appears the archive has passed. `-Wl,--no-undefined`
  then fails the link. (cortex+jarnax are repeated twice on the link line for exactly this reason.)
- **Pre-existing example:** the `@FIXME` at `modules/stm32/source/stm32h7xx/clocks.cpp:38` documents
  the same problem for `early_power()`: it has to be called from inside the vendor's `clocks()`
  rather than from `configure.cpp`.
- **Fix / rule:** any vendor symbol referenced only from `configure.cpp` must be *pulled in* by
  an already-extracted member — call it from the vendor `clocks()` (guarded by
  `if constexpr (cortex::swo::enable)`), not from `configure.cpp`. Do not rely on the board
  archive happening to reference it.
- **Gotcha:** a misleading "M7 passes" check — building only a module or a configure stage and
  grepping for `FAILED` can miss that the app ELFs never linked. Verify app `.elf` artifacts
  actually exist / contain the symbol.

## 2026-08-12 — J-Link rewrites DBGMCU_CR on connect, unclocking the D3 debug domain

- **Symptom:** after the firmware programs the ST SWO/SWTF blocks (0x5C003000/0x5C004000), a
  fresh J-Link session reads `DBGMCU_CR` = `0x00000007` (bits 0-2 = J-Link's own
  DBG_SLEEP/DBG_STOP/DBG_STANDBY) and the SWO/SWTF registers are unreadable
  (`Could not start CPU core. (ErrorCode: -1)`), making it look like the firmware never
  programmed them.
- **Root cause:** each pylink-square-mcp tool call is a new J-Link connection; on connect/reset
  the J-Link writes `DBGMCU_CR` with its low-power debug bits (0x07), clobbering
  TRACECLKEN/D1DBGCKEN/D3DBGCKEN (bits 20/21/22). With those clear, the D3 debug domain is
  unclocked, so SWO/SWTF reads hang.
- **Fix / verification pattern:** verify in a **single session** — set a hardware breakpoint at a
  post-configure symbol (e.g. `cortex::system::main()`) via `pylink-square-mcp test_breakpoint`
  and dump the registers when it hits, before any reconnect. Verified values for issue-41:
  `DBGMCU_CR`=0x00700007, `SWO_CODR`=0x2b (43 @100MHz/2.24MBaud), `SWO_SPPR`=2 (AsyncNRZ),
  `SWTF_CTRL`=0x301 (ENSO).

## 2026-08-11 — J-Link Remote Server has no `-if/-device/-speed` options

- **Symptom:** Launching the backend with `JLinkRemoteServer -if SWD -device STM32H753ZI -speed auto`
  is not a valid invocation.
- **Root cause:** On macOS `JLinkRemoteServer` is a symlink to `JLinkRemoteServerCLExe`. Per the SEGGER
  KB (https://kb.segger.com/J-Link_Remote_Server) and UM08001, its only meaningful options are
  `-Port <port>`, `-USB <S/N or nickname>` and `-IP <...>` (plus tunnel options). Target device,
  interface (SWD) and speed are chosen **client-side** in `pylink.JLink.connect(...)`; the Remote
  Server simply forwards the DLL traffic.
- **Conclusion:** `mcp_server.py` launches it as `JLinkRemoteServer -Port 19020 [-USB <serial>]` only.
- **Gotcha:** the Remote Server also does NOT do RTT scraping; RTT is read by the client (pylink)
  over the tunneled connection (works, verified via `rtt_read --continuous`).
- **Gotcha:** do not commit/publish a real J-Link serial number. The raw server log
  (`jlink-remote-server.log`) contains it and is gitignored for that reason.

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

## 2026-08-19 — Mangled-signature mismatch in `memory::copy` definition vs header (silent until linked)

- **Symptom:** `test-jarnax-cyphal-none-all` link error: `undefined reference to memory::copy(void*, void const*, unsigned long)` even though `libmodule-memory-none-all.a` is on the link line.
- **Root cause:** `modules/memory/source/copy.cpp` defined `void copy(void*, void *const, size_t)` (top-level const pointer = mangles to `void*`), but the header `memory.hpp` declares `void copy(void*, void const*, size_t)` (mangles to `void const*`). The template overload had masked it for years because no caller forced the non-template `void` overload (e.g. `memory::copy(uint8_t[], char[], n)` — mismatched element types defeat template deduction and fall through to the fixed overload).
- **Fix:** changed the definition's parameter to `void const *_src` to match the header. Added Catch2 tests in `modules/memory/tests/catch2-strings.cpp` using mismatched element types (`uint8_t[]` dst, `char const*` src) to force the fixed overload.
- **Gotcha:** top-level `const` on a pointer parameter is dropped during C++ name mangling, but pointee-const is not — `void *const` and `void const *` are different symbols. Keep definitions byte-for-byte consistent with the header declaration.

## 2026-08-22 — Encapsulating libudpard in `CyphalUDPInterface` (issue-61)

- **Gotcha:** generic modules (`add_module` with `NO_BOARDS`) cannot include `jarnax/Ticker.hpp`
  because it pulls `cortex/tick.hpp`, which only the cortex *architecture* target exposes on its
  include line. The main `jarnax` module gets it via `ARCH cortex`; `jarnax-cyphal-udp` does not.
  Fix: define a tiny `MicrosecondClock` abstract interface (core-only types) and inject it instead.
- **Gotcha:** `jarnax::cyphal::PortId` is **not copy-assignable** (its copy assignment is implicitly
  deleted, anonymous union of non-trivial-ish members). Store port identity as plain fields
  (type/style/value) when a struct needs to hold and overwrite one; do not keep `PortId` members.
- **Gotcha:** `udpardGather` returns 0 for an empty fragment list, so an "empty payload" transfer
  (e.g. `uavcan.node.GetInfo` request) looks identical to a gather failure if you gate delivery on
  `gathered > 0`. Gate on `transfer.payload_size` instead; empty transfers are valid Cyphal transfers.
- **Gotcha:** libudpard TX responses (`udpardTxRespond`) are addressed to the *client's* RPC multicast
  group derived from the client node-ID — not to the group the request arrived on. In tests,
  `sent_to == from` is wrong for responses.
- **Gotcha:** o1heap does **not** reject allocation requests whose alignment exceeds max_align_t;
  with NDEBUG it serves the block at its own granularity. Don't write tests asserting nullptr for
  over-aligned requests. Fixed stale expectation in gtest-cyphal-o1heappool.cpp.
- **Gotcha:** subject-IDs passed to `udpardTxPublish` must be ≤ 8191 (UDPARD_SUBJECT_ID_MAX);
  out-of-range IDs return -UDPARD_ERROR_ARGUMENT, which surfaces as an innocent-looking
  `Publish() == false` in test producers.
