"""Unit tests for tools/elf-mcp/parsers.py."""

from parsers import (
    MemoryRegion,
    _is_meta_section,
    _parse_size,
    _strip_discarded,
    classify_section,
    compute_size_breakdown,
    parse_linker_memory,
    parse_map_discarded,
    parse_map_memory_config,
    parse_map_per_object,
    parse_nm_symbols,
    parse_objdump_sections,
    parse_readelf_sections,
    region_for_address,
    Section,
)


# ---------------------------------------------------------------------------
# shared / size tokens
# ---------------------------------------------------------------------------


def test_parse_size_literals():
    assert _parse_size("0x20000") == 0x20000
    assert _parse_size("2M") == 2 * 1024 * 1024
    assert _parse_size("128K") == 128 * 1024
    assert _parse_size("128k") == 128 * 1024
    assert _parse_size("1G") == 1 << 30
    assert _parse_size("100000") == 100000


def test_parse_size_expression():
    assert _parse_size("2 * 1024") == 2048
    assert _parse_size("262144 / 2") == 131072
    assert _parse_size("64K / 4") == 16384


# ---------------------------------------------------------------------------
# objdump -h
# ---------------------------------------------------------------------------

OBJDUMP_H = """\
firmware.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000bc88  08000400  08000400  00010300  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000108  24000000  0800dd54  00020300  2**3
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          0000eca4  24000800  24000800  00030000  2**3
                  ALLOC
  3 .debug_info   00000000  00000000  00000000  000c0000  2**0
                  DEBUG
"""


def test_parse_objdump_sections_attaches_flags_and_filters():
    sections = parse_objdump_sections(OBJDUMP_H)
    by_name = {s.name: s for s in sections}
    assert set(by_name) == {".text", ".data", ".bss"}  # .debug_info dropped
    assert by_name[".text"].is_readonly
    assert by_name[".text"].is_stored
    assert by_name[".data"].is_stored and not by_name[".data"].is_readonly
    assert not by_name[".bss"].is_stored
    assert by_name[".text"].vma == 0x08000400
    assert by_name[".text"].lma == 0x08000400
    assert by_name[".data"].lma == 0x0800dd54


def test_classify_section():
    readonly = Section(name=".text", size=4, vma=0, lma=0,
                       flags=frozenset(["CONTENTS", "ALLOC", "LOAD", "READONLY"]))
    stored_wr = Section(name=".data", size=4, vma=0, lma=0,
                        flags=frozenset(["CONTENTS", "ALLOC", "LOAD"]))
    bss = Section(name=".bss", size=4, vma=0, lma=0,
                  flags=frozenset(["ALLOC"]))
    debug = Section(name=".debug_info", size=4, vma=0, lma=0,
                    flags=frozenset(["DEBUG"]))
    assert classify_section(readonly) == "flash"
    assert classify_section(stored_wr) == "data"
    assert classify_section(bss) == "ram"
    assert classify_section(debug) == "other"


def test_compute_size_breakdown():
    sections = parse_objdump_sections(OBJDUMP_H)
    breakdown = compute_size_breakdown(sections)
    assert breakdown.flash == 0xbc88 + 0x108  # text + data LMA copy
    assert breakdown.ram == 0x108 + 0xeca4    # data VMA + bss
    rows = dict((name, (f, r)) for name, f, r in breakdown.sections)
    assert rows[".data"] == (0x108, 0x108)


# ---------------------------------------------------------------------------
# nm -S --size-sort --radix=x
# ---------------------------------------------------------------------------

NM_TEXT = """\
08000400 000000fc T _ZN4Foo3RunEv
08010000 00000020 R foo_format
24000000 00000400 D bar_counter
24001000 0000ffff B bar_buf
         U malloc
         U memset
nm: warning: some junk input
"""


def test_parse_nm_symbols():
    symbols = parse_nm_symbols(NM_TEXT)
    by_name = {s.name: s for s in symbols}
    assert by_name["_ZN4Foo3RunEv"].kind == "text"
    assert by_name["foo_format"].kind == "rodata"
    assert by_name["bar_counter"].kind == "data"
    assert by_name["bar_buf"].size == 0xffff
    assert by_name["malloc"].address is None
    assert by_name["malloc"].size is None
    assert by_name["memset"].type == "U"


# ---------------------------------------------------------------------------
# readelf -S -W
# ---------------------------------------------------------------------------

READELF_S = """\
Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 0]                   NULL            0000000000000000 000000 000000 00  0   0  0
  [ 1] .text             PROGBITS        08000400 010300 00bc88 00  AX  0   0  4
  [ 2] .rodata           PROGBITS        0800c0bc 01bfbc 001bc8 00  AX  0   0  4
  [ 3] .bss              NOBITS          24000800 020000 000eca4 00  WA  0   0  8
  [ 4] .debug          PROGBITS        00000000 030000 0089453 00   0   0  1
"""


def test_parse_readelf_sections():
    sections = parse_readelf_sections(READELF_S)
    assert len(sections) == 4  # NULL row (empty name) skipped
    text = sections[0]
    assert text.name == ".text"
    assert text.type == "PROGBITS"
    assert text.addr == 0x08000400
    assert text.offset == 0x010300
    assert text.size == 0xbc88
    assert text.flags == "AX"
    assert sections[2].size == 0xeca4
    assert sections[3].name == ".debug"


# ---------------------------------------------------------------------------
# linker script MEMORY {}
# ---------------------------------------------------------------------------

LD_MEMORY = """\
FLASH_SIZE   = 2M;
DTCM_SIZE    = 128K;
SRAM1_SIZE   = 512K;

MEMORY
{
  ITCM      (xrw)  : ORIGIN = 0x00000000, LENGTH = 128K
  FLASH     (rx)   : ORIGIN = 0x08000000, LENGTH = FLASH_SIZE
  DTCM      (xrw)  : ORIGIN = 0x20000000, LENGTH = DTCM_SIZE
  SRAM1     (xrw)  : ORIGIN = 0x24000000, LENGTH = SRAM1_SIZE / 2
}
"""


def test_parse_linker_memory():
    regions = parse_linker_memory(LD_MEMORY)
    by_name = {r.name: r for r in regions}
    assert set(by_name) == {"ITCM", "FLASH", "DTCM", "SRAM1"}
    assert by_name["FLASH"].origin == 0x08000000
    assert by_name["FLASH"].length == 2 * 1024 * 1024
    assert not by_name["FLASH"].is_writable
    assert by_name["DTCM"].length == 128 * 1024
    assert by_name["DTCM"].is_writable
    assert by_name["SRAM1"].length == 256 * 1024  # expression resolved
    assert by_name["ITCM"].attributes == "xrw"


def test_region_for_address():
    regions = parse_linker_memory(LD_MEMORY)
    flash = region_for_address(regions, 0x08000400)
    sram1 = region_for_address(regions, 0x24010000)
    itcm = region_for_address(regions, 0x00001000)
    assert flash is not None and flash.name == "FLASH"
    assert sram1 is not None and sram1.name == "SRAM1"
    assert itcm is not None and itcm.name == "ITCM"
    assert region_for_address(regions, 0x24080000) is None  # past SRAM1/2


# ---------------------------------------------------------------------------
# map file: memory configuration
# ---------------------------------------------------------------------------

MAP_MEMORY_CONFIG = """\
Cross Reference Table

Memory Configuration

Name             Origin             Length             Attributes
ITCM             0x0000000000000000 0x0000000000020000 xrw
FLASH            0x0000000008000000 0x0000000000200000 rx
DTCM             0x0000000002000000 0x0000000000020000 xrw
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map
"""


def test_parse_map_memory_config():
    regions = parse_map_memory_config(MAP_MEMORY_CONFIG)
    by_name = {r.name: r for r in regions}
    assert set(by_name) == {"ITCM", "FLASH", "DTCM"}
    assert by_name["FLASH"].origin == 0x08000000
    assert by_name["FLASH"].length == 0x00200000
    assert not by_name["FLASH"].is_writable
    assert by_name["DTCM"].is_writable


# ---------------------------------------------------------------------------
# map file: per-object accounting
# ---------------------------------------------------------------------------

MAP_FULL = """\
                0x08000000        _start
                0x08000400        Reset_Handler

Discarded input sections

 .text.startup._GLOBAL__sub_I_main
                0x00000000        0x4 dead_boot.o
 .bss
                0x00000000        0x10 dead_boot.o

Memory Configuration

Name             Origin             Length             Attributes
ITCM             0x0000000000000000 0x0000000000020000 xrw
FLASH            0x0000000008000000 0x0000000000200000 rx
DTCM             0x0000000002000000 0x0000000000020000 xrw
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

.text           0x08000400       0xbc88
 .text          0x08000400        0x21c   source/GlobalContext.cpp.obj
                0x0800061c        _ZN13GlobalContext10InitializeEv
 .text          0x08000650        0x4     source/utility.cpp.obj
 .text._ZN4core10StateChartI9DemoStateE7RunOnceEv
                0x08000654        0xfc    core/statechart.cpp.obj
 .rodata        0x0800c0bc       0x1bc8
 .rodata        0x0800c0bc        0x50   source/utility.cpp.obj
.bss            0x24000800       0xeca4 load address 0x0800e25c
 .bss           0x24000800       0x14   source/app.cpp.obj
 .bss           0x24000814       0xffff core/shared.cpp.obj
.debug_str      0x24001000       0x89453 source/GlobalContext.cpp.obj
"""


def test_parse_map_per_object_classic_and_function_sections():
    regions = parse_map_memory_config(MAP_FULL)
    blames = parse_map_per_object(MAP_FULL, regions)
    by_obj = {b.object: b for b in blames}

    # dead_boot.o lives only in the Discarded block -> must be absent.
    assert "dead_boot.o" not in by_obj

    gc = by_obj["source/GlobalContext.cpp.obj"]
    assert gc.flash == 0x21c
    assert gc.ram == 0          # .debug_str meta row excluded

    util = by_obj["source/utility.cpp.obj"]
    assert util.flash == 0x4 + 0x50  # .text + .rodata contributions
    assert util.ram == 0

    # function-sections bare header + raw leaf
    sc = by_obj["core/statechart.cpp.obj"]
    assert sc.flash == 0xfc

    # bss leaf in a RAM region (DTCM here) -> ram; ".bss ... load address" row skipped
    app = by_obj["source/app.cpp.obj"]
    assert app.flash == 0
    assert app.ram == 0x14

    shared = by_obj["core/shared.cpp.obj"]
    assert shared.ram == 0xffff

    # sorted by total descending
    totals = [b.total for b in blames]
    assert totals == sorted(totals, reverse=True)


def test_parse_map_per_object_without_regions_uses_names():
    blames = parse_map_per_object(MAP_FULL)
    util = next(b for b in blames if b.object == "source/utility.cpp.obj")
    assert util.flash == 0x54  # .text/.rodata heuristic
    app = next(b for b in blames if b.object == "source/app.cpp.obj")
    assert app.ram == 0x14


def test_parse_map_discarded():
    discarded = parse_map_discarded(MAP_FULL)
    assert any("dead_boot.o" in row for row in discarded)


def test_strip_discarded_removes_block():
    stripped = _strip_discarded(MAP_FULL)
    assert "dead_boot.o" not in stripped
    assert "Discarded input sections" not in stripped
    assert "Memory Configuration" in stripped


# ---------------------------------------------------------------------------
# meta-section filter
# ---------------------------------------------------------------------------


def test_is_meta_section():
    assert _is_meta_section(".debug_info")
    assert _is_meta_section(".debug_str")
    assert _is_meta_section(".ARM.attributes")
    assert _is_meta_section(".group")
    assert _is_meta_section(".symtab")
    assert _is_meta_section(".rela.dyn")
    assert not _is_meta_section(".text")
    assert not _is_meta_section(".bss._Z4main")
    assert not _is_meta_section(".rodata._ZTV3Foo")