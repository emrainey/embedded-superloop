# elf-mcp

An MCP server that turns the ARM GNU binutils and GNU ld link-maps into
structured-JSON tools for firmware flash/RAM analysis.  It is the smallest
possible bridge between an AI agent and the on-target firmware artifacts:
given a firmware ELF it can report exact image sizes, linker-memory fill,
per-object bloat (from the `.map`), the largest symbols, whether the image
uses dynamic memory, and disassembly / DWARF address resolution.

Sibling server [`../pylink-square-mcp`](../pylink-square-mcp) does live
J-Link flashing/debugging; this server is purely host-side (no target
connection needed).

## Layout

- `mcp_server.py` — JSON-RPC 2.0 over stdio entrypoint registered in
  `opencode.json` (mirrors `pylink-square-mcp`'s protocol).
- `tools.py` — the nine tool handlers + the `TOOLS` registry.
- `parsers.py` — pure text parsers (no subprocesses): objdump/readelf/nm
  output, linker-script `MEMORY{}`, `.map` memory config, per-object blame,
  discarded input sections.
- `toolchain.py` — resolves `arm-none-eabi-{size,nm,readelf,objdump,addr2line}`
  (`/Applications/ArmGNUToolchain/**`, `/opt/homebrew/bin`, `$PATH`).
- `tests/` — pytest suite; runs on any host with no ARM toolchain (tools are
  exercised through a scripted fake runner).

## Tools

| Tool | What it answers |
| --- | --- |
| `list_elf_files` | Which firmware ELFs/link-maps exist under `build/`. |
| `binary_size` | Flash vs RAM totals with per-section classification. |
| `section_breakdown` | Verbose `readelf -S` listing (debug sections too). |
| `memory_map` | Fill percentage of each linker `MEMORY` region. |
| `largest_symbols` | Top-N symbols by size (`nm`), for bloat hunting. |
| `per_object_map` | Per-object flash/RAM contributions from the `.map`. |
| `verify_no_heap` | Scan for dynamic memory / C++ exception / static-init machinery. |
| `disassemble` | Disassemble a function or address range. |
| `addr2line` | Resolve address(es) -> function + source line (pairs with J-Link backtraces). |

## Usage

```jsonc
// opencode.json (already wired)
"elf-mcp": {
  "type": "local",
  "command": [".venv/bin/python", "tools/elf-mcp/mcp_server.py"],
  "cwd": ".",
  "environment": { "PYTHONPATH": "tools/elf-mcp" }
}
```

Restart opencode after editing `opencode.json` (config is not hot-reloaded).

Each tool can also be driven from a shell:

```sh
.venv/bin/python tools/elf-mcp/tools.py binary_size \
  --json '{"elf":"build/cortex-m7-gcc-arm-none-eabi/applications/nucleo-demo/firmware-nucleo-demo-basic-nucleo_h753zi.elf"}'
```

## Tests

```sh
PYTHONPATH=tools/elf-mcp .venv/bin/python -m pytest tools/elf-mcp/tests -q
```

No cross-compiled targets or toolchain are required: parsers eat fixture text
and the tool handlers run against a scripted fake binutils runner.

## Validation notes

Against `firmware-nucleo-demo-basic-nucleo_h753zi.elf` (GCC 13.2, M7):

- `binary_size` matches `arm-none-eabi-size` exactly: flash `0xe0f4`,
  RAM `0x37b20`.
- `per_object_map` attributes input objects to flash within ~2% of the image
  total.  Its RAM figure excludes linker-reserved regions (`.process_stack`,
  `.main_stack`, `.ethernet_dma_buffers`, `.dma_buffers`) and `.data` LMA
  copies by design — use `binary_size` for exact totals.
- `.map` parsing tolerates both classic (`name 0xaddr 0xsize obj`) and
  function-sections (bare header + raw leaf) layouts, and strips
  `Discarded input sections` blocks wherever the linker printed them.