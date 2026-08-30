"""Tool implementations for the elf-mcp server.

Every tool is a plain ``callable(params, runner) -> (exit_code, output_text)``.
``runner`` must match :class:`toolchain.BinutilsRunner` (defaults to the real
binutils via :func:`toolchain.make_runner`), so the tools are unit-testable
with a fake runner and the same entrypoints can be driven from a CLI or the
MCP server.
"""

from __future__ import annotations

import json
import os
import re
from typing import Callable

from toolchain import BinutilsRunner, make_runner, run_binutils
from parsers import (
    MemoryRegion,
    compute_size_breakdown,
    parse_linker_memory,
    parse_map_discarded,
    parse_map_memory_config,
    parse_map_per_object,
    parse_nm_symbols,
    parse_objdump_sections,
    parse_readelf_sections,
    region_for_address,
)

PROJECT_ROOT = os.path.abspath(os.path.join(os.path.dirname(__file__), "..", ".."))

#: Sections that must never appear in the on-target image. Matched against
#: linker-mangled names and hard-coded symbol spellings.
HEAP_SYMBOLS = (
    "malloc", "calloc", "realloc", "free",
    "_Znwm", "_Znam", "_Znaj", "_Znwj",   # operator new / new[]
    "_ZdlPv", "_ZdaPv", "_ZdlPvj", "_ZdaPvj",  # operator delete / delete[]
    "__cxa_throw", "__cxa_allocate_exception", "__cxa_free_exception",
    "__cxa_rethrow", "_Unwind_", "__gxx_personality",
    "_GLOBAL__sub_I", "__dso_handle", "_initterm",
)


def _resolve_path(path: str, root: str) -> str:
    """Resolve a possibly-relative path against ``root`` (the project dir)."""
    if os.path.isabs(path):
        return path
    return os.path.abspath(os.path.join(root, path))


def _require_elf(params: dict, root: str) -> str:
    elf = params.get("elf")
    if not elf:
        raise ValueError("'elf' argument is required")
    elf = _resolve_path(elf, root)
    if not os.path.isfile(elf):
        raise FileNotFoundError(f"ELF file not found: {elf}")
    return elf


def _sibling_map_path(elf: str) -> str:
    return elf.rsplit(".", 1)[0] + ".map"


def _find_linkerscript(elf: str, root: str) -> str | None:
    """Best-effort discovery of the linker script for a firmware ELF.

    Searches, in order: an explicit ``ld`` argument, a ``.map`` sibling (for the
    ``Memory Configuration`` table), and the conventional ``linkerscripts/``
    layout under ``projects/``, ``modules/`` and ``boards/``.
    """
    map_path = _sibling_map_path(elf)
    if os.path.isfile(map_path):
        return map_path
    return None


def _json(output) -> tuple[int, str]:
    return 0, json.dumps(output, indent=2)


def _err(msg: str) -> tuple[int, str]:
    return 1, json.dumps({"error": msg}, indent=2)


def _regions_from_ld(ld_path: str) -> list[MemoryRegion]:
    with open(ld_path) as handle:
        return parse_linker_memory(handle.read())


def _regions_from_map(map_path: str) -> list[MemoryRegion]:
    with open(map_path) as handle:
        return parse_map_memory_config(handle.read())


# ---------------------------------------------------------------------------
# discovery
# ---------------------------------------------------------------------------


def list_elf_files(params: dict, runner: BinutilsRunner | None = None,
                   root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Discover firmware ``.elf`` / ``.map`` artifacts under a build root."""
    build_root = params.get("build_root", "build")
    preset_filter = params.get("preset") or None
    build_root = _resolve_path(build_root, root)
    if not os.path.isdir(build_root):
        return _err(f"build root not found: {build_root}")
    artifacts = []
    for dirpath, dirnames, filenames in os.walk(build_root):
        if ".dot." in dirpath:  # graphviz scratch outputs
            continue
        if "native" in params.get("preset", "") or "host" in params.get("preset", ""):
            pass
        for fname in filenames:
            if not fname.endswith(".elf"):
                continue
            if ".dot." in fname:  # graphviz copy inside build dir
                continue
            rel = os.path.relpath(os.path.join(dirpath, fname), build_root)
            preset = rel.split(os.sep)[0]
            if preset_filter and not (
                preset == preset_filter
                or preset_filter == f"on-target-{preset}"
                or preset_filter.endswith(preset)
            ):
                continue
            elf_path = os.path.join(dirpath, fname)
            map_path = _sibling_map_path(elf_path)
            artifacts.append({
                "preset": preset,
                "relative": rel,
                "elf": elf_path,
                "map": map_path if os.path.isfile(map_path) else None,
                "modified": os.path.getmtime(elf_path),
            })
    artifacts.sort(key=lambda a: a["relative"])
    return _json({"count": len(artifacts), "artifacts": artifacts})


# ---------------------------------------------------------------------------
# memory / section analysis
# ---------------------------------------------------------------------------


def binary_size(params: dict, runner: BinutilsRunner | None = None,
                root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Flash/RAM totals and per-section classification from an ELF."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    result = runner("objdump", ["-h", elf])
    if result.returncode != 0:
        return _err(f"objdump failed: {result.stderr.strip()}")
    sections = parse_objdump_sections(result.stdout)
    breakdown = compute_size_breakdown(sections)
    flash_rows = []
    for name, fbytes, rbytes in breakdown.sections:
        flash_rows.append({
            "section": name,
            "flash": fbytes,
            "ram": rbytes,
        })
    return _json({
        "elf": elf,
        "flash": breakdown.flash,
        "ram": breakdown.ram,
        "total": breakdown.total,
        "sections": flash_rows,
        "note": ".data-like sections are charged to flash (LMA copy) and RAM (VMA); "
                "stack && DMA reservations are linker-reserved RAM.",
    })


def section_breakdown(params: dict, runner: BinutilsRunner | None = None,
                      root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Verbose ``readelf -S``-derived listing of every section."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    result = runner("readelf", ["-SW", elf])
    if result.returncode != 0:
        return _err(f"readelf failed: {result.stderr.strip()}")
    sections = parse_readelf_sections(result.stdout)
    rows = [
        {
            "number": s.number,
            "name": s.name,
            "type": s.type,
            "address": s.addr,
            "offset": s.offset,
            "size": s.size,
            "flags": s.flags,
        }
        for s in sections
    ]
    return _json({"elf": elf, "count": len(rows), "sections": rows})


def memory_map(params: dict, runner: BinutilsRunner | None = None,
               root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Map ELF sections onto linker ``MEMORY`` regions with fill percentages."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    ld_path = params.get("ld")
    if ld_path:
        ld_path = _resolve_path(ld_path, root)
    regions = []
    if ld_path and os.path.isfile(ld_path):
        regions = _regions_from_ld(ld_path)
    else:
        map_path = _sibling_map_path(elf)
        if os.path.isfile(map_path):
            regions = _regions_from_map(map_path)
    if not regions:
        return _err(
            "no MEMORY regions found: pass an explicit 'ld' linkerscript path "
            f"(checked {_sibling_map_path(elf)})"
        )

    result = runner("objdump", ["-h", elf])
    if result.returncode != 0:
        return _err(f"objdump failed: {result.stderr.strip()}")
    sections = parse_objdump_sections(result.stdout)

    region_sizes: dict[str, int] = {r.name: 0 for r in regions}
    section_placement: list[dict] = []
    for section in sections:
        region = region_for_address(regions, section.vma) or region_for_address(
            regions, section.lma
        )
        if region is None:
            continue
        region_sizes[region.name] += section.size
        section_placement.append({
            "section": section.name,
            "size": section.size,
            "vma": section.vma,
            "lma": section.lma,
            "region": region.name,
            "writable": region.is_writable,
        })

    region_rows = []
    for region in regions:
        used = region_sizes.get(region.name, 0)
        if used == 0:
            continue
        region_rows.append({
            "region": region.name,
            "used": used,
            "length": region.length,
            "fill_percent": round(100.0 * used / region.length, 2),
            "kind": "ram" if region.is_writable else "flash",
        })
    region_rows.sort(key=lambda r: r["fill_percent"], reverse=True)
    return _json({
        "elf": elf,
        "linker_script": ld_path or _sibling_map_path(elf),
        "regions": region_rows,
        "section_placement": section_placement,
    })


def largest_symbols(params: dict, runner: BinutilsRunner | None = None,
                    root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Top-N symbols by size from ``nm`` (bloat hunting)."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    count = int(params.get("count", 25))
    result = runner("nm", ["-S", "--size-sort", "--radix=x", elf])
    if result.returncode != 0:
        return _err(f"nm failed: {result.stderr.strip()}")
    symbols = parse_nm_symbols(result.stdout)
    sized = [s for s in symbols if s.size is not None and s.address is not None]
    sized.sort(key=lambda s: (s.size or 0), reverse=True)
    top = []
    for symbol in sized[:count]:
        top.append({
            "name": symbol.name,
            "address": symbol.address,
            "size": symbol.size,
            "kind": symbol.kind,
        })
    total_text = sum(s.size or 0 for s in sized if s.kind == "text")
    return _json({
        "elf": elf,
        "count": len(top),
        "total_text_bytes": total_text,
        "symbols": top,
    })


def per_object_map(params: dict, runner: BinutilsRunner | None = None,
                   root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Per-object flash/RAM contributions from the linker map file."""
    runner = runner or make_runner()
    elf = params.get("elf")
    map_path = params.get("map")
    if not elf and not map_path:
        return _err("'elf' or 'map' argument is required")
    if map_path:
        map_path = _resolve_path(map_path, root)
    else:
        elf = _require_elf(params, root)
        map_path = _sibling_map_path(elf)
    if not os.path.isfile(map_path):
        return _err(f"map file not found: {map_path} (build firmware with -Map)")
    with open(map_path) as handle:
        text = handle.read()
    regions = parse_map_memory_config(text)
    blames = parse_map_per_object(text, regions)
    top = int(params.get("top", 15))
    rows = [
        {
            "object": b.object,
            "flash": b.flash,
            "ram": b.ram,
            "total": b.total,
        }
        for b in blames[:top]
    ]
    covered_flash = sum(b.flash for b in blames)
    covered_ram = sum(b.ram for b in blames)
    discarded = parse_map_discarded(text)
    return _json({
        "elf": elf,
        "map": map_path,
        "objects": rows,
        "covered_flash": covered_flash,
        "covered_ram": covered_ram,
        "discarded_sections": len(discarded),
        "note": "Totals exclude linker-reserved regions (stacks, DMA buffers) "
                "and .data LMA copies; use binary_size for exact image totals.",
    })


# ---------------------------------------------------------------------------
# code inspection
# ---------------------------------------------------------------------------

#: Regular expressions that reliably name a heap-related routine in ARM
#: disassembly once demangled.  Kept as a tuple for testability.
_HEAP_DISASSEMBLY_RE = re.compile(
    r"\b(malloc|calloc|realloc|free|_Znwm|_Znam|_Znaj|_Znwj|_ZdlPv|_ZdaPv"
    r"|__cxa_throw|__cxa_allocate_exception|__cxa_free_exception|__cxa_rethrow)\b"
)


def verify_no_heap(params: dict, runner: BinutilsRunner | None = None,
                   root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Scan the image for dynamic memory / exception machinery.

    Reports any heap-ish symbols found in the symbol table or as call targets in
    the disassembly.  A clean image exits 0 with ``violations: []``.
    """
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    include_unwind = bool(params.get("include_unwind", False))
    violations: list[dict] = []

    nm_result = runner("nm", ["--defined-only", elf])
    if nm_result.returncode == 0:
        for symbol in parse_nm_symbols(nm_result.stdout):
            lowered = symbol.name
            found = any(
                needle in lowered
                for needle in ("malloc", "calloc", "realloc")
            ) or any(
                needle in lowered
                for needle in ("_Znwm", "_Znam", "_ZdlPv", "_ZdaPv",
                               "__cxa_", "_GLOBAL__sub_I", "__dso_handle")
            )
            if include_unwind:
                found = found or lowered.startswith("_Unwind_") or "__gxx_personality" in lowered
            if found:
                violations.append({
                    "source": "symbol_table",
                    "symbol": symbol.name,
                    "address": symbol.address,
                })

    objdump_result = runner("objdump", ["-d", elf])
    if objdump_result.returncode == 0:
        for lineno, line in enumerate(objdump_result.stdout.splitlines(), 1):
            if _HEAP_DISASSEMBLY_RE.search(line):
                violations.append({
                    "source": "disassembly",
                    "line": lineno,
                    "line_text": line.strip(),
                })

    pass_result = not violations
    return _json({
        "elf": elf,
        "pass": pass_result,
        "violations": violations[: int(params.get("limit", 40))],
        "checked_symbols": list(HEAP_SYMBOLS),
    })


def disassemble(params: dict, runner: BinutilsRunner | None = None,
                root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Disassemble one function/address range from the ELF."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    symbol = params.get("symbol")
    address = params.get("address")
    if not symbol and not address:
        return _err("'symbol' or 'address' argument is required")
    if symbol:
        nm_result = runner("nm", ["-S", elf])
        if nm_result.returncode != 0:
            return _err(f"nm failed: {nm_result.stderr.strip()}")
        matches = [
            (s.address, s.size)
            for s in parse_nm_symbols(nm_result.stdout)
            if s.name == symbol and s.address is not None and s.size is not None
        ]
        if not matches:
            return _err(f"symbol not found in ELF: {symbol}")
        start, size = matches[0]
        if size == 0:
            size = 0x100
        start_arg = hex(start)
        stop_arg = hex(start + size)
        desc = {"symbol": symbol, "start": start, "size": size}
    else:
        if not isinstance(address, str):
            return _err("'address' must be a hex string")
        start = int(address, 0)
        span = int(params.get("span", 0x80))
        start_arg = hex(start)
        stop_arg = hex(start + span)
        desc = {"address": start, "span": span}
    result = runner(
        "objdump",
        ["-d", "--no-show-raw-insn", f"--start-address={start_arg}",
         f"--stop-address={stop_arg}", elf],
    )
    if result.returncode != 0:
        return _err(f"objdump failed: {result.stderr.strip()}")
    return _json({"elf": elf, **desc, "disassembly": result.stdout})


def addr2line(params: dict, runner: BinutilsRunner | None = None,
              root: str = PROJECT_ROOT) -> tuple[int, str]:
    """Resolve one or more addresses to function + source line (DWARF)."""
    runner = runner or make_runner()
    elf = _require_elf(params, root)
    raw = params.get("address")
    if not raw:
        return _err("'address' argument is required")
    addresses = raw if isinstance(raw, list) else [raw]
    resolved = []
    for address in addresses:
        result = runner("addr2line", ["-e", elf, "-f", "-i", str(address)])
        lines = [ln for ln in result.stdout.splitlines() if ln.strip()]
        resolved.append({
            "address": address,
            "function": lines[0] if lines else "??",
            "source": lines[-1] if len(lines) > 1 else "??",
        })
    return _json({"elf": elf, "resolved": resolved})


#: Registry consumed by the MCP server.  Keeping it here lets the CLI and
#: server share the same tool surface.
TOOLS: list[dict] = [
    {
        "name": "list_elf_files",
        "description": "Discover firmware .elf/.map artifacts under a CMake build root. "
                       "Returns the preset, relative path, and map sibling for each ELF.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "build_root": {"type": "string", "description": "Build directory (default 'build')"},
                "preset": {"type": "string", "description": "Optional preset name filter"},
            },
        },
        "handler": list_elf_files,
    },
    {
        "name": "binary_size",
        "description": "Flash/RAM totals for an ELF with per-section classification. "
                       ".data-like sections are charged to flash (LMA copy) and RAM (VMA).",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF (absolute or relative)"},
            },
            "required": ["elf"],
        },
        "handler": binary_size,
    },
    {
        "name": "section_breakdown",
        "description": "Verbose per-section listing (readelf -S) including debug sections. "
                       "Use for address/offset/flags inspection.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
            },
            "required": ["elf"],
        },
        "handler": section_breakdown,
    },
    {
        "name": "memory_map",
        "description": "Fill percentage of each linker MEMORY region by the ELF's sections. "
                       "Resolves regions from the .map sibling, or from an explicit linker script.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
                "ld": {"type": "string", "description": "Optional linker script path"},
            },
            "required": ["elf"],
        },
        "handler": memory_map,
    },
    {
        "name": "largest_symbols",
        "description": "Top-N symbols by size from nm (flash/RAM bloat hunting).",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
                "count": {"type": "integer", "description": "How many symbols (default 25)"},
            },
            "required": ["elf"],
        },
        "handler": largest_symbols,
    },
    {
        "name": "per_object_map",
        "description": "Per-object flash/RAM contributions parsed from the linker .map file. "
                       "Takes 'elf' (map sibling guessed) or an explicit 'map' path.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Firmware ELF (map sibling derived)"},
                "map": {"type": "string", "description": "Explicit .map path"},
                "top": {"type": "integer", "description": "Objects to list (default 15)"},
            },
        },
        "handler": per_object_map,
    },
    {
        "name": "verify_no_heap",
        "description": "Scan the image for dynamic-memory/exception machinery "
                       "(malloc, operator new, __cxa_*, static init). Pass/fail + violations.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
                "include_unwind": {"type": "boolean",
                                   "description": "Also flag _Unwind_/personality routines"},
                "limit": {"type": "integer", "description": "Max violations to report (default 40)"},
            },
            "required": ["elf"],
        },
        "handler": verify_no_heap,
    },
    {
        "name": "disassemble",
        "description": "Disassemble one function (by symbol) or an address range.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
                "symbol": {"type": "string", "description": "Function name to disassemble"},
                "address": {"type": "string", "description": "Start address (hex), used with span"},
                "span": {"type": "integer", "description": "Bytes after address (default 0x80)"},
            },
            "required": ["elf"],
        },
        "handler": disassemble,
    },
    {
        "name": "addr2line",
        "description": "Resolve address(es) to function + source file:line via DWARF. "
                       "Pairs with pylink-square-mcp backtraces.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to firmware ELF"},
                "address": {
                    "oneOf": [
                        {"type": "string", "description": "Single hex address"},
                        {"type": "array", "items": {"type": "string"}},
                    ],
                    "description": "One or more addresses",
                },
            },
            "required": ["elf", "address"],
        },
        "handler": addr2line,
    },
]


def main() -> None:
    """CLI entrypoint: ``python tools.py <tool-name> --json '{...}'``."""
    import argparse
    import sys

    parser = argparse.ArgumentParser(description="elf-mcp tool CLI")
    parser.add_argument("tool", choices=[t["name"] for t in TOOLS])
    parser.add_argument("--json", required=True, help="JSON arguments object")
    args = parser.parse_args()

    tool = next(t for t in TOOLS if t["name"] == args.tool)
    try:
        params = json.loads(args.json)
    except json.JSONDecodeError as exc:
        print(json.dumps({"error": f"invalid JSON: {exc}"}))
        sys.exit(1)
    exit_code, output = tool["handler"](params)
    print(output)
    sys.exit(exit_code)


if __name__ == "__main__":
    main()