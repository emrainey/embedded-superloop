"""Unit tests for tools/elf-mcp/tools.py.

Uses a scripted FakeRunner instead of real binutils so the suite runs on any
host (no ARM toolchain needed) and every expected subprocess call is asserted.
"""

from pathlib import Path

import pytest

from toolchain import CommandResult
from tools import PROJECT_ROOT, TOOLS


def _handler(name):
    tool = next(t for t in TOOLS if t["name"] == name)
    return tool["handler"]


class FakeRunner:
    """Records calls, fails on any unscripted invocation."""

    def __init__(self):
        self.calls = []
        self._script = {}

    def add(self, tool, args, *, returncode=0, stdout="", stderr=""):
        self._script[(tool, tuple(args))] = CommandResult(returncode, stdout, stderr)
        return self

    def expect(self, tool, args):
        return (tool, list(args)) in [(t, a) for t, a in self.calls]

    def __call__(self, tool, args, *, cwd=None):
        key = (tool, tuple(args))
        self.calls.append((tool, list(args)))
        if key not in self._script:
            raise AssertionError(f"unscripted call: {tool} {args}")
        return self._script[key]


@pytest.fixture
def elf_file(tmp_path):
    path = tmp_path / "firmware.elf"
    path.write_bytes(b"\x7fELF")
    return str(path)


# ---------------------------------------------------------------------------
# binary_size / section_breakdown / memory_map
# ---------------------------------------------------------------------------

OBJDUMP_H = """\
firmware.elf:     file format elf32-littlearm

Sections:
Idx Name          Size      VMA       LMA       File off  Algn
  0 .text         0000bc88  08000400  08000400  00010300  2**2
                  CONTENTS, ALLOC, LOAD, READONLY, CODE
  1 .data         00000108  24000000  0800dd54  00020300  2**3
                  CONTENTS, ALLOC, LOAD, DATA
  2 .bss          0000eca4  20000000  20000000  00030000  2**3
                  ALLOC
  3 .zero_table   00000038  0800dd54  0800dd54  00020300  2**3
                  CONTENTS, ALLOC, LOAD, READONLY, DATA
"""


def test_binary_size(elf_file, tmp_path):
    runner = FakeRunner().add("objdump", ["-h", elf_file], stdout=OBJDUMP_H)
    exit_code, output = _handler("binary_size")(
        {"elf": elf_file}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["flash"] == 0xbc88 + 0x108 + 0x38
    assert data["ram"] == 0x108 + 0xeca4
    assert runner.expect("objdump", ["-h", elf_file])


def test_section_breakdown(elf_file, tmp_path):
    readelf = """\
Section Headers:
  [Nr] Name              Type            Address          Off    Size   ES Flg Lk Inf Al
  [ 1] .text             PROGBITS        08000400 010300 00bc88 00  AX  0   0  4
  [ 3] .bss              NOBITS          24000800 020000 000eca4 00  WA  0   0  8
"""
    runner = FakeRunner().add("readelf", ["-SW", elf_file], stdout=readelf)
    exit_code, output = _handler("section_breakdown")(
        {"elf": elf_file}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["count"] == 2
    assert data["sections"][1]["size"] == 0xeca4


LD_MEMORY = """\
MEMORY
{
  FLASH  (rx)  : ORIGIN = 0x08000000, LENGTH = 2M
  DTCM   (xrw) : ORIGIN = 0x20000000, LENGTH = 128K
}
"""


def test_memory_map_with_explicit_ld(elf_file, tmp_path):
    ld_path = tmp_path / "app.ld"
    ld_path.write_text(LD_MEMORY)
    runner = FakeRunner().add("objdump", ["-h", elf_file], stdout=OBJDUMP_H)
    exit_code, output = _handler("memory_map")(
        {"elf": elf_file, "ld": str(ld_path)}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    regions = {r["region"]: r for r in data["regions"]}
    # .text 0xbc88 + .data 0x108 + .zero_table 0x38 inside FLASH(0x08000000..+2M)
    assert regions["FLASH"]["used"] == 0xbc88 + 0x108 + 0x38
    assert regions["DTCM"]["used"] == 0xeca4
    assert regions["FLASH"]["fill_percent"] == pytest.approx(
        100.0 * (0xbc88 + 0x108 + 0x38) / (2 * 1024 * 1024), abs=0.01
    )


def test_memory_map_missing_regions_is_error(elf_file, tmp_path):
    # No ld and no map sibling -> no regions -> error result, exit 1.
    runner = FakeRunner().add("objdump", ["-h", elf_file], stdout=OBJDUMP_H)
    exit_code, output = _handler("memory_map")(
        {"elf": elf_file}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 1
    data = __import__("json").loads(output)
    assert "MEMORY" in data["error"]


# ---------------------------------------------------------------------------
# largest_symbols
# ---------------------------------------------------------------------------

NM_SORTED = """\
24001000 0000ffff B bar_buf
08000400 000000fc T _ZN4Foo3RunEv
08010000 00000020 R foo_format
"""


def test_largest_symbols(elf_file, tmp_path):
    runner = FakeRunner().add(
        "nm", ["-S", "--size-sort", "--radix=x", elf_file], stdout=NM_SORTED
    )
    exit_code, output = _handler("largest_symbols")(
        {"elf": elf_file, "count": 2}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert [s["name"] for s in data["symbols"]] == ["bar_buf", "_ZN4Foo3RunEv"]
    assert data["total_text_bytes"] == 0xfc


# ---------------------------------------------------------------------------
# per_object_map
# ---------------------------------------------------------------------------

MAP_TEXT = """\
Memory Configuration

Name             Origin             Length             Attributes
ITCM             0x0000000000000000 0x0000000000020000 xrw
FLASH            0x0000000008000000 0x0000000000200000 rx
*default*        0x0000000000000000 0xffffffffffffffff

Linker script and memory map

.text           0x08000400       0xbc88
 .text          0x08000400        0x21c   source/GlobalContext.cpp.obj
 .text._ZN4core10StateChartI9DemoStateE7RunOnceEv
                0x08000654        0xfc    core/statechart.cpp.obj
.bss            0x24000800       0xeca4 load address 0x0800e25c
 .bss           0x24000800       0x14   source/app.cpp.obj
"""


def test_per_object_map(tmp_path):
    map_path = tmp_path / "firmware.map"
    map_path.write_text(MAP_TEXT)
    exit_code, output = _handler("per_object_map")(
        {"map": str(map_path), "top": 10}, runner=FakeRunner(), root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    by_obj = {o["object"]: o for o in data["objects"]}
    assert by_obj["source/GlobalContext.cpp.obj"]["flash"] == 0x21c
    assert by_obj["core/statechart.cpp.obj"]["flash"] == 0xfc
    assert by_obj["source/app.cpp.obj"]["ram"] == 0x14
    # the "load address" pseudo-row contributes nothing
    assert data["covered_flash"] == 0x21c + 0xfc
    assert data["covered_ram"] == 0x14


def test_per_object_map_requires_argument():
    exit_code, output = _handler("per_object_map")({}, runner=FakeRunner())
    assert exit_code == 1
    data = __import__("json").loads(output)
    assert "required" in data["error"]


# ---------------------------------------------------------------------------
# verify_no_heap
# ---------------------------------------------------------------------------

NM_CLEAN = """\
08000400 000000fc T _ZN4Foo3RunEv
"""
NM_DIRTY = NM_CLEAN + """\
         U malloc
"""
DISASM_CLEAN = """\
08000400 <_ZN4Foo3RunEv>:
 8000400:   4770        bx  lr
"""


def test_verify_no_heap_clean(elf_file, tmp_path):
    runner = FakeRunner()
    runner.add("nm", ["--defined-only", elf_file], stdout=NM_CLEAN)
    runner.add("objdump", ["-d", elf_file], stdout=DISASM_CLEAN)
    exit_code, output = _handler("verify_no_heap")(
        {"elf": elf_file}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["pass"] is True
    assert data["violations"] == []


def test_verify_no_heap_flags_malloc_symbol(elf_file, tmp_path):
    runner = FakeRunner()
    runner.add("nm", ["--defined-only", elf_file], stdout=NM_DIRTY)
    runner.add("objdump", ["-d", elf_file], stdout=DISASM_CLEAN)
    exit_code, output = _handler("verify_no_heap")(
        {"elf": elf_file}, runner=runner, root=str(tmp_path)
    )
    data = __import__("json").loads(output)
    assert data["pass"] is False
    assert any(v["symbol"] == "malloc" for v in data["violations"])


# ---------------------------------------------------------------------------
# disassemble / addr2line
# ---------------------------------------------------------------------------

NM_WITH_SIZE = """\
08000400 000000fc T _ZN4Foo3RunEv
"""


def test_disassemble_by_symbol(elf_file, tmp_path):
    runner = FakeRunner()
    runner.add("nm", ["-S", elf_file], stdout=NM_WITH_SIZE)
    disasm = "08000400 <_ZN4Foo3RunEv>:\n".replace("\n", "") + "__leading\n"
    runner.add(
        "objdump",
        ["-d", "--no-show-raw-insn", "--start-address=0x8000400",
         "--stop-address=0x80004fc", elf_file],
        stdout=disasm,
    )
    exit_code, output = _handler("disassemble")(
        {"elf": elf_file, "symbol": "_ZN4Foo3RunEv"}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["start"] == 0x08000400
    assert data["size"] == 0xfc
    assert "__leading" in data["disassembly"]


def test_disassemble_by_address(elf_file, tmp_path):
    runner = FakeRunner()
    runner.add(
        "objdump",
        ["-d", "--no-show-raw-insn", "--start-address=0x8000400",
         "--stop-address=0x8000480", elf_file],
        stdout="before\n08000400: 4770 bx lr\nafter\n",
    )
    exit_code, output = _handler("disassemble")(
        {"elf": elf_file, "address": "0x08000400", "span": 0x80},
        runner=runner, root=str(tmp_path),
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["address"] == 0x08000400
    assert "bx lr" in data["disassembly"]


def test_disassemble_unknown_symbol_is_error(elf_file, tmp_path):
    runner = FakeRunner().add("nm", ["-S", elf_file], stdout=NM_WITH_SIZE)
    exit_code, output = _handler("disassemble")(
        {"elf": elf_file, "symbol": "NoSuch"}, runner=runner, root=str(tmp_path)
    )
    assert exit_code == 1
    assert "not found" in __import__("json").loads(output)["error"]


def test_addr2line(elf_file, tmp_path, monkeypatch):
    runner = FakeRunner()
    runner.add("addr2line", ["-e", elf_file, "-f", "-i", "0x08000400"],
               stdout="_ZN4Foo3RunEv\nsource/foo.cpp:41")
    runner.add("addr2line", ["-e", elf_file, "-f", "-i", "0x08000800"],
               stdout="_ZN4Bar4StopEv\nsource/bar.cpp:7")
    exit_code, output = _handler("addr2line")(
        {"elf": elf_file, "address": ["0x08000400", "0x08000800"]},
        runner=runner, root=str(tmp_path),
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["resolved"][0] == {
        "address": "0x08000400",
        "function": "_ZN4Foo3RunEv",
        "source": "source/foo.cpp:41",
    }
    assert data["resolved"][1]["source"] == "source/bar.cpp:7"


# ---------------------------------------------------------------------------
# list_elf_files
# ---------------------------------------------------------------------------


def _scaffold_build(tmp_path):
    root = tmp_path / "proj"
    m7 = (root / "build" / "cortex-m7-gcc-arm-none-eabi" / "applications" /
          "nucleo-demo")
    m7.mkdir(parents=True)
    (m7 / "firmware-nucleo-demo-basic-nucleo_h753zi.elf").write_bytes(b"\x7fELF")
    (m7 / "firmware-nucleo-demo-basic-nucleo_h753zi.map").write_text("x")
    m4 = (root / "build" / "cortex-m4-gcc-arm-none-eabi" / "applications" /
          "emb-demo")
    m4.mkdir(parents=True)
    (m4 / "firmware-emb-demo-basic-stm32_f4ve_v2.elf").write_bytes(b"\x7fELF")
    # a non-elf file and a .dot. copy should be ignored
    (m4 / "notes.txt").write_text("noise")
    (m4 / "firmware-emb-demo.min.dot").write_bytes(b"digraph{}")
    return root


def test_list_elf_files(tmp_path):
    root = _scaffold_build(tmp_path)
    exit_code, output = _handler("list_elf_files")(
        {"build_root": "build"}, runner=FakeRunner(), root=str(root)
    )
    assert exit_code == 0
    data = __import__("json").loads(output)
    assert data["count"] == 2
    elves = [a["relative"] for a in data["artifacts"]]
    assert any("nucleo-demo" in e and e.endswith(".elf") for e in elves)
    m7 = next(a for a in data["artifacts"] if "nucleo-demo" in a["relative"])
    assert m7["map"] is not None
    m4 = next(a for a in data["artifacts"] if "emb-demo" in a["relative"])
    assert m4["map"] is None


def test_list_elf_files_preset_filter(tmp_path):
    root = _scaffold_build(tmp_path)
    exit_code, output = _handler("list_elf_files")(
        {"build_root": "build",
         "preset": "on-target-cortex-m7-gcc-arm-none-eabi"},
        runner=FakeRunner(), root=str(root),
    )
    data = __import__("json").loads(output)
    assert data["count"] == 1
    assert "nucleo-demo" in data["artifacts"][0]["relative"]


def test_list_elf_files_missing_root():
    exit_code, output = _handler("list_elf_files")(
        {"build_root": "does-not-exist"},
        runner=FakeRunner(), root=PROJECT_ROOT,
    )
    assert exit_code == 1
    assert "not found" in __import__("json").loads(output)["error"]