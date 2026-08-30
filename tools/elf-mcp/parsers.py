"""Pure text parsers for ARM binutils / GNU ld output and linker scripts.

These functions take *strings* (the stdout of a tool, or the text of a linker
script / map file) and return plain-Python data structures.  They never spawn
a subprocess, so they are fully unit-testable and reusable by the MCP tools.
"""

from __future__ import annotations

import re
from dataclasses import dataclass, field
from typing import Iterable, Optional

# ---------------------------------------------------------------------------
# shared
# ---------------------------------------------------------------------------


def _parse_size(value: str) -> int:
    """Parse a GNU size token like ``0x20000``, ``2M``, ``128K``, ``100000``.

    Also accepts a bare symbol name (resolved against ``symbols``) or a simple
    ``A * N`` / ``A / N`` expression, matching how real linker scripts compute
    region lengths (e.g. ``LENGTH = DTCM_SIZE / 2``).
    """
    value = value.strip()
    suffix = 1
    tail = value
    for marker, mult in (("K", 1 << 10), ("M", 1 << 20), ("G", 1 << 30)):
        if tail.upper().endswith(marker):
            suffix = mult
            tail = tail[:-1]
            break
    try:
        return int(tail, 0) * suffix
    except ValueError:
        pass
    # simple binary arithmetic: "A op B" where A/B are numbers or symbol refs
    binary = re.match(r"^\s*(\S+)\s*([*/])\s*(\S+)\s*$", tail)
    if binary:
        try:
            lhs = _parse_size(binary.group(1))
            rhs = _parse_size(binary.group(3))
        except ValueError:
            raise
        return (lhs * rhs) if binary.group(2) == "*" else (lhs // rhs)
    raise ValueError(f"cannot parse numeric token {value!r}")


@dataclass(frozen=True)
class Section:
    """One alloc section parsed from ``objdump -h``."""

    name: str
    size: int
    vma: int
    lma: int
    flags: frozenset[str] = frozenset()

    @property
    def is_alloc(self) -> bool:
        return "ALLOC" in self.flags

    @property
    def is_writable(self) -> bool:
        return "WRITE" in self.flags  # objdump shows READONLY; writable = not read-only

    @property
    def is_stored(self) -> bool:
        return "CONTENTS" in self.flags  # has bytes in the image (vs NOBITS)

    @property
    def is_readonly(self) -> bool:
        return "READONLY" in self.flags


# ---------------------------------------------------------------------------
# objdump -h
# ---------------------------------------------------------------------------

_OBJDUMP_SECTION_RE = re.compile(
    r"^\s*(\d+)\s+(\S+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+\S+\s+\S+\s*$"
)


def parse_objdump_sections(text: str) -> list[Section]:
    """Parse ``objdump -h`` output into a list of ``Section``.

    The flags for a section appear on the *following* line; we attach them to
    the preceding header row.
    """
    sections: list[Section] = []
    pending: Section | None = None
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            pending = None
            continue
        match = _OBJDUMP_SECTION_RE.match(line)
        if match:
            pending = Section(
                name=match.group(2),
                size=int(match.group(3), 16),
                vma=int(match.group(4), 16),
                lma=int(match.group(5), 16),
                flags=frozenset(),
            )
            sections.append(pending)
            continue
        if pending is not None:
            # Flag line, e.g. "CONTENTS, ALLOC, LOAD, READONLY, CODE"
            new_flags = frozenset(
                f.strip() for f in line.split(",") if f.strip()
            ) | set(pending.flags)
            pending = Section(
                name=pending.name,
                size=pending.size,
                vma=pending.vma,
                lma=pending.lma,
                flags=new_flags,
            )
            sections[-1] = pending
    return [s for s in sections if s.is_alloc]


@dataclass(frozen=True)
class SizeBreakdown:
    """Flash/RAM totals for an image."""

    flash: int = 0
    ram: int = 0
    #: Name -> breakdown of the flash/RAM space that section occupies.
    sections: tuple[tuple[str, int, int], ...] = ()

    @property
    def total(self) -> int:
        return self.flash + self.ram

    def as_dict(self) -> dict:
        return {"flash": self.flash, "ram": self.ram, "total": self.total}


def classify_section(section: Section) -> None | str:
    """Classify an alloc section as ``"flash"``, ``"ram"`` or ``"other"``.

    - Read-only stored sections (``.text``, ``.rodata``, ``.tables`` ...) live
      in flash.
    - Stored writable sections (``.data``) have an LMA copy in flash **and** a
      runtime VMA in RAM.
    - Unstored writable sections (``.bss``, stacks, DMA buffers) live in RAM.
    """
    if not section.is_alloc:
        return "other"
    if section.is_readonly:
        return "flash" if section.size else "other"
    if section.is_stored:
        return "data"  # both flash (LMA) and ram (VMA)
    return "ram"


def compute_size_breakdown(sections: Iterable[Section]) -> SizeBreakdown:
    """Compute flash/RAM totals for a list of alloc sections.

    ``.data``-like sections are charged to flash (LMA copy) and RAM (VMA).
    """
    flash = 0
    ram = 0
    rows: list[tuple[str, int, int]] = []
    for s in sections:
        kind = classify_section(s)
        if kind == "flash":
            flash += s.size
            rows.append((s.name, s.size, 0))
        elif kind == "data":
            flash += s.size
            ram += s.size
            rows.append((s.name, s.size, s.size))
        elif kind == "ram":
            ram += s.size
            rows.append((s.name, 0, s.size))
    rows.sort(key=lambda r: r[1] + r[2], reverse=True)
    return SizeBreakdown(flash=flash, ram=ram, sections=tuple(rows))


# ---------------------------------------------------------------------------
# nm -S --size-sort
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class Symbol:
    """One symbol from ``nm``."""

    name: str
    address: int | None
    size: int | None
    type: str

    @property
    def kind(self) -> str:
        if self.type in "Tt":
            return "text"
        if self.type in "Rr":
            return "rodata"
        if self.type in "Dd":
            return "data"
        if self.type in "Bb":
            return "bss"
        return "other"


_NM_LINE_RE = re.compile(
    r"^\s*([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+([A-Za-z])\s+(.+)$"
)
_NM_UNDEF_RE = re.compile(r"^\s*([A-Za-z])\s+(.+)$")


def parse_nm_symbols(text: str) -> list[Symbol]:
    """Parse ``nm -S --size-sort`` output (debug/diagnostic lines tolerated)."""
    symbols: list[Symbol] = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        match = _NM_LINE_RE.match(line)
        if match:
            symbols.append(
                Symbol(
                    name=match.group(4).strip(),
                    address=int(match.group(1), 16),
                    size=int(match.group(2), 16),
                    type=match.group(3),
                )
            )
            continue
        match = _NM_UNDEF_RE.match(line)
        if match and len(line.split()) == 2:
            symbols.append(
                Symbol(name=match.group(2).strip(), address=None, size=None,
                       type=match.group(1))
            )
    return symbols


# ---------------------------------------------------------------------------
# readelf -S -W
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class ReadelfSection:
    number: int
    name: str
    type: str
    addr: int
    offset: int
    size: int
    flags: str


_READELF_SECTION_RE = re.compile(
    r"^\s*\[\s*(\d+)\]\s+(\S*?)\s+(\S+)\s+([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+"
    r"([0-9a-fA-F]+)\s+([0-9a-fA-F]+)\s+(\S+)"
)


def parse_readelf_sections(text: str) -> list[ReadelfSection]:
    """Parse ``readelf -S -W`` output (wide).

    Only row-shaped entries are kept; the leading NULL section (whose Name
    column is empty) is skipped.
    """
    out: list[ReadelfSection] = []
    for raw in text.splitlines():
        line = raw.strip()
        if not line or not line.startswith("["):
            continue
        match = _READELF_SECTION_RE.match(line)
        if not match:
            continue
        number = int(match.group(1))
        if number == 0:  # readelf's resident NULL section
            continue
        name = match.group(2)
        if not name:
            continue
        out.append(
            ReadelfSection(
                number=number,
                name=name,
                type=match.group(3),
                addr=int(match.group(4), 16),
                offset=int(match.group(5), 16),
                size=int(match.group(6), 16),
                flags=match.group(8),
            )
        )
    return out


# ---------------------------------------------------------------------------
# linker script: MEMORY { }
# ---------------------------------------------------------------------------

@dataclass(frozen=True)
class MemoryRegion:
    name: str
    attributes: str
    origin: int
    length: int
    #: Where the region was defined (file:line), if known.
    defines: str = ""

    @property
    def is_writable(self) -> bool:
        """A region is RAM-ish if its access attributes permit writes."""
        if self.attributes:
            return "w" in self.attributes.lower()
        return True  # default attributes are rwx


_MEMORY_BLOCK_RE = re.compile(r"MEMORY\s*\{(.*?)\}", re.DOTALL)
_REGION_RE = re.compile(
    r"^\s*(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s*(?:\((?P<attrs>[^)]*)\))?\s*:"
    r"\s*ORIGIN\s*=\s*(?P<origin>[^,\n]+)\s*,\s*LENGTH\s*=\s*(?P<length>[^,\n]+)",
    re.MULTILINE,
)
_ASSIGN_RE = re.compile(r"^\s*(\w+)\s*=\s*([^;]+);", re.MULTILINE)


def _parse_symbols(text: str) -> dict[str, str]:
    """Collect top-level ``NAME = value;`` assignments from a linker script."""
    out: dict[str, str] = {}
    for match in _ASSIGN_RE.finditer(text):
        out[match.group(1)] = match.group(2).strip()
    return out


def _resolve_token(token: str, symbols: dict[str, str]) -> int:
    """Resolve a region ORIGIN/LENGTH token to an integer.

    Falls back through: numeric literal, top-level linker-script symbols
    (expanded inside a simple ``A op B`` expression too), then a plain
    ``A op B`` expression made of numeric literals.
    """
    token = token.strip()
    expanded = token
    for name, value in symbols.items():
        expanded = re.sub(rf"\b{re.escape(name)}\b", value, expanded)
    try:
        return _parse_size(expanded)
    except ValueError:
        raise ValueError(f"cannot resolve {token!r} as an ORIGIN/LENGTH value")


def parse_linker_memory(text: str) -> list[MemoryRegion]:
    """Parse the ``MEMORY { ... }`` block of a linker script.

    Handles ``LENGTH = 2M`` style literals as well as symbol references like
    ``LENGTH = FLASH_SIZE`` (resolved from top-level assignments).
    """
    symbols = _parse_symbols(text)
    regions: list[MemoryRegion] = []
    match = _MEMORY_BLOCK_RE.search(text)
    block = match.group(1) if match else ""
    if not block:
        return regions
    for region_match in _REGION_RE.finditer(block):
        attrs = region_match.group("attrs") or ""
        try:
            origin = _resolve_token(region_match.group("origin"), symbols)
            length = _resolve_token(region_match.group("length"), symbols)
        except ValueError:
            continue
        regions.append(
            MemoryRegion(
                name=region_match.group("name"),
                attributes="".join(attrs.split()),
                origin=origin,
                length=length,
            )
        )
    return regions


def region_for_address(regions: Iterable[MemoryRegion], addr: int) -> MemoryRegion | None:
    """Return the first memory region containing ``addr``, or ``None``."""
    for region in regions:
        if region.origin <= addr < region.origin + region.length:
            return region
    return None


# ---------------------------------------------------------------------------
# linker map file (+ per-object accounting)
# ---------------------------------------------------------------------------

@dataclass
class MapSection:
    """A top-level section seen in the map file."""

    name: str
    address: int
    size: int


@dataclass
class ObjectBlame:
    """Flash/RAM bytes attributable to one object file."""

    object: str
    flash: int = 0
    ram: int = 0
    sections: dict[str, int] = field(default_factory=dict)

    @property
    def total(self) -> int:
        return self.flash + self.ram


_MEMCONFIG_BLOCK_RE = re.compile(
    r"Memory Configuration(.*?)\n\n", re.DOTALL
)
_STACK_RE = re.compile(
    r"^\s*(?P<name>[A-Za-z_][A-Za-z0-9_]*)\s+(?P<origin>0x[0-9a-fA-F]+)"
    r"\s+(?P<length>0x[0-9a-fA-F]+)\s+(?P<attrs>\S*)"
)
#: Section-header row: either a bare input-section header (function-sections
#: style, e.g. " .text._ZN13GlobalContext10InitializeEv") or an output-section
#: total (".text 0x08000400 0xbc88").  Never has a trailing object path.
_MAP_HEADER_RE = re.compile(
    r"^\s*(?P<name>\.[A-Za-z0-9_.]+|[A-Za-z0-9_]+)"
    r"(?:\s+0x(?P<addr>[0-9a-fA-F]{8,16})\s+0x(?P<size>[0-9a-fA-F]+))?\s*$"
)
#: Classic leaf with a name, e.g. " .text 0x08000400 0x21c <object>".
_MAP_LEAF_RE = re.compile(
    r"^\s*(?P<name>\.?[A-Za-z_][A-Za-z0-9_.]*?)\s+0x(?P<addr>[0-9a-fA-F]{8,16})"
    r"\s+0x(?P<size>[0-9a-fA-F]+)\s+(?P<obj>\S.*)$"
)
#: Raw-leaf where the section header and its contribution are on separate
#: lines, e.g. " 0x08000650 0xe4 <object>".
_MAP_RAW_LEAF_RE = re.compile(
    r"^\s*0x(?P<addr>[0-9a-fA-F]{8,16})\s+0x(?P<size>[0-9a-fA-F]+)\s+(?P<obj>\S.*)$"
)
#: A row inside a ``Discarded input sections`` listing: either a named leaf
#: (" .text 0x00000000 0x0 <object>"), a bare input-section header
#: (" .text._ZN13GlobalContext10InitializeEv") with a raw leaf below it, a
#: raw " 0x00000000 0x4 <object>" line, or a plain value row (" 0x00000000 x").
_DISCARD_ROW_RE = re.compile(
    r"^\s*(?:"
    r"\.?\w[\w.\-$]*$"                                   # bare section header
    r"|\.\S+\s+0x[0-9a-fA-F]+\s+0x[0-9a-fA-F]+\s+\S.*$"  # named discard row
    r"|0x[0-9a-fA-F]+\s+0x[0-9a-fA-F]+\s+\S.*$"          # raw discard leaf
    r"|0x[0-9a-fA-F]+\s+\S.*$"                          # symbol/value row
    r")"
)


def _strip_discarded(text: str) -> str:
    """Remove every ``Discarded input sections`` block from a map.

    The block may appear *anywhere* (some ld versions print it before the
    memory configuration); it ends at the first line that is not a
    name/addr/size/object discard row.
    """
    out: list[str] = []
    discarding = False
    for line in text.splitlines():
        if "Discarded input sections" in line:
            discarding = True
            continue
        if not discarding:
            out.append(line)
            continue
        if line.strip() and not _DISCARD_ROW_RE.match(line):
            discarding = False
            out.append(line)
    return "\n".join(out)


def parse_map_memory_config(text: str) -> list[MemoryRegion]:
    """Parse the ``Memory Configuration`` table printed in a GNU ld ``.map``.

    Returns an empty list if the table is absent (e.g. the map was made with a
    plain ``-Map`` and no MEMORY command in the script); callers then fall back
    to section-name heuristics.
    """
    regions: list[MemoryRegion] = []
    lines = text.splitlines()
    start = next(
        (i for i, line in enumerate(lines) if "Memory Configuration" in line), None
    )
    if start is None:
        return regions
    # The header row "Name Origin Length Attributes" is on its own line.
    header = next(
        (i for i in range(start + 1, len(lines)) if "Name" in lines[i]), None
    )
    if header is None:
        return regions
    for line in lines[header + 1:]:
        m = _STACK_RE.match(line)
        if not m:
            break  # e.g. "*default*" or a blank line ends the table
        try:
            origin = int(m.group("origin"), 16)
            length = int(m.group("length"), 16)
        except ValueError:
            continue
        regions.append(
            MemoryRegion(
                name=m.group("name"),
                attributes="".join(m.group("attrs").split()),
                origin=origin,
                length=length,
            )
        )
    return regions


def _is_meta_section(name: str) -> bool:
    """True for sections that never occupy device flash/RAM.

    Debug, symtab/strtab, group, vendor attribute and relocation sections are
    link-time metadata (or section-group overviews) and must not be charged to
    an object's flash/RAM totals.
    """
    lowered = name.lower()
    if lowered.startswith(".debug"):
        return True
    for prefix in (".arm.", ".group", ".symtab", ".strtab", ".dynsym", ".dynstr",
                   ".comment", ".note", ".rela", ".rel.", ".got", ".sdata"):
        if lowered.startswith(prefix):
            return True
    return False


def parse_map_per_object(text: str, regions: Iterable[MemoryRegion] = ()) -> list[ObjectBlame]:
    """Aggregate the size of each input object from a GNU ld ``.map`` file.

    ``regions`` (from :func:`parse_map_memory_config` or the linker script) are
    used to classify each leaf's address as flash vs ram; without them the
    section name header is used (`text/d`/`bss` heuristics).

    Supports both the classic ``name 0xaddr 0xsize <object>`` format and the
    function-sections format where a bare ``name`` header line is followed by a
    raw ``0xaddr 0xsize <object>`` contribution line.  ``Discarded input
    sections`` blocks are removed wherever they appear so GC'd input does not
    pollute totals.
    """
    region_list = list(regions)
    text = _strip_discarded(text)
    blames: dict[str, ObjectBlame] = {}
    current_section: MapSection | None = None
    in_memconfig = False

    def _classify(addr: int, section_name: str) -> str:
        if region_list:
            region = region_for_address(region_list, addr)
            if region is not None:
                return "ram" if region.is_writable else "flash"
        head = section_name
        if head.startswith(".text") or head.startswith(".rodata"):
            return "flash"
        return "ram"

    for raw in text.splitlines():
        line = raw.strip()
        if not line:
            continue
        if "Memory Configuration" in line:
            in_memconfig = True
            continue
        if "Linker script and memory map" in line:
            in_memconfig = False
            continue
        if in_memconfig:
            # Region table rows ("ITCM ... xrw") must not count as object input.
            continue
        # Raw-leaf: " 0x08000650 0xe4 <object>" (function-sections format).
        raw_match = _MAP_RAW_LEAF_RE.match(raw)
        if raw_match and current_section is not None:
            if _is_meta_section(current_section.name):
                continue
            try:
                addr = int(raw_match.group("addr"), 16)
                size = int(raw_match.group("size"), 16)
            except ValueError:
                continue
            obj = raw_match.group("obj").strip()
            if obj and not obj.startswith("load address"):
                blame = blames.setdefault(obj, ObjectBlame(object=obj))
                kind = _classify(addr, current_section.name)
                if kind == "flash":
                    blame.flash += size
                else:
                    blame.ram += size
                blame.sections[current_section.name] = (
                    blame.sections.get(current_section.name, 0) + size
                )
            continue
        # Symbol/value rows like "0x08000400 __aeabi_frsub" or
        # "0x00000001 ASSERT(...)" — single-hex rows, never section contributions.
        if line.startswith("0x"):
            continue
        bare_match = _MAP_HEADER_RE.match(raw)
        leaf_match = _MAP_LEAF_RE.match(raw)
        if bare_match and not leaf_match:
            # Output-section header (".name 0xaddr 0xsize") or bare input-section
            # header (".name") — either way it starts a new section context.
            try:
                current_section = MapSection(
                    name=bare_match.group("name"),
                    address=0,
                    size=0,
                )
            except ValueError:
                current_section = None
            continue
        if leaf_match and current_section is not None:
            if _is_meta_section(leaf_match.group("name")):
                continue
            try:
                addr = int(leaf_match.group("addr"), 16)
                size = int(leaf_match.group("size"), 16)
            except ValueError:
                continue
            leaf_name = leaf_match.group("name")
            obj = leaf_match.group("obj").strip()
            if obj and not obj.startswith("load address"):
                blame = blames.setdefault(obj, ObjectBlame(object=obj))
                kind = _classify(addr, leaf_name)
                if kind == "flash":
                    blame.flash += size
                else:
                    blame.ram += size
                blame.sections[leaf_name] = (
                    blame.sections.get(leaf_name, 0) + size
                )
    return sorted(blames.values(), key=lambda b: b.total, reverse=True)


def parse_map_discarded(text: str) -> list[str]:
    """Extract the ``Discarded input sections`` listing (for dead-code eyeballing)."""
    marker = "Discarded input sections"
    if marker not in text:
        return []
    tail = text.split(marker, 1)[1]
    out: list[str] = []
    for raw in tail.splitlines():
        line = raw.strip()
        if not line:
            continue
        if re.match(r"^\s*\.\.\.\s*$", line):
            break
        if re.match(r"^[\w./].*\s+0x[0-9a-fA-F]+", line):
            out.append(line)
    return out