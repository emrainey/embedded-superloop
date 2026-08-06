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
