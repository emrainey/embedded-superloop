# PLAN: Route pylink-square-mcp through a persistent J-Link Remote Server

Issue: #52 — branch `issue-52` (tracks `github/develop`).

## Summary

The `tools/pylink-square-mcp` J-Link MCP server crashes periodically. Every
tool call created a fresh `pylink.JLink()`, opened the USB link, connected,
and discarded it — repeated J-Link DLL load/unload + USB connect/disconnect
churn inside a long-lived process. Fix: connect through a persistent local
**J-Link Remote Server** (default `127.0.0.1:19020`), and have
`mcp_server.py` launch that daemon on startup if it isn't already listening.
The daemon intentionally outlives the MCP process so USB stays stable across
MCP crashes/restarts.

## Changes

1. **`jlink_connection.py` (new)** — shared helper:
   - `add_connection_args(parser)`: adds `--remote-host` (default
     `127.0.0.1`), `--remote-port` (default `19020`), `--direct`.
   - `connect(device, speed, remote_host, remote_port, interface=SWD)`: opens
     via `jlink.open(ip_addr="host:port")`; falls back to a direct USB
     connection (with a stderr warning) if the Remote Server is unreachable.
   - Device/speed stay client-side in `jlink.connect()`; the Remote Server
     only needs `-Port` (and optionally `-USB <S/N or nickname>`) per
     https://kb.segger.com/J-Link_Remote_Server.
2. **All 13 J-Link tool scripts** — import the shared helper, register the
   connection args, and replace the inline open/connect block with
   `connect(...)` (backtrace, clock_tree, debug_target, dump_ethernet,
   dump_memory, flash_target, flash_verify, live_dump, rtt_read, run_for,
   run_to_main, step_target, test_breakpoint). `svd_query` is SVD-only, no
   J-Link.
3. **`mcp_server.py`** — on startup:
   - parse `--device/--speed/--remote-port/--usb-serial` (env fallbacks
     `JLINK_MCP_*`);
   - `ensure_remote_server()`: if nothing is listening on the port, locate
     `JLinkRemoteServer` and spawn `-Port <port> [-USB <serial>]` with output
     to `jlink-remote-server.log`; poll for the listener; never kill on exit;
   - every J-Link tool handler appends `--remote-host/--remote-port` so all
     calls route through the daemon.
4. **`.gitignore`** — ignore the Remote Server log artifacts.
5. **README.md** — document the backend, options/env vars, config example.

## Verification

- `python3 -m py_compile` on all touched scripts.
- Live hardware test through the daemon: `debug_target`, `run_for --seconds 2`,
  `rtt_read --continuous 4` all connected/ran/read correctly via
  `127.0.0.1:19020`.
- MCP startup twice: first run launched the daemon; second run detected the
  existing listener ("already listening").
- No C++ source touched; firmware build presets unaffected (CI still validates).

## Gotchas

- `JLinkRemoteServer` on macOS is a symlink to `JLinkRemoteServerCLExe`; its
  accepted options are `-Port`, `-USB`, `-IP` — there is no `-if/-device/-speed`
  (those are client-side).
- Do NOT put the probe's real serial number in commits/examples/code.
