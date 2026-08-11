import sys
import os
import copy
import argparse
import struct
import xml.etree.ElementTree as ET
from typing import List, Optional

# Core Textual TUI engine imports
textual_import_error: Optional[Exception] = None
try:
    from textual.app import App, ComposeResult
    from textual.containers import Horizontal, Vertical
    from textual.widgets import Header, Footer, Tree, DataTable, Input, Button, Label, Select, RichLog, Switch, TabbedContent, TabPane
except ImportError as exc:
    textual_import_error = exc

    class _FallbackApp:
        pass

    class _DummyContext:
        def __init__(self, *args: object, **kwargs: object):
            pass

        def __enter__(self):
            return self

        def __exit__(self, exc_type: object, exc_val: object, exc_tb: object) -> bool:
            return False

    class _DummyWidget:
        def __init__(self, *args: object, **kwargs: object):
            pass

    class _DummyButton(_DummyWidget):
        class Pressed:  # pragma: no cover - fallback shim
            button = None

    class _DummyTree(_DummyWidget):
        class NodeSelected:  # pragma: no cover - fallback shim
            node = None

    class _DummyComposeResult:
        pass

    ComposeResult = _DummyComposeResult
    App = _FallbackApp  # type: ignore[assignment]
    Horizontal = _DummyContext
    Vertical = _DummyContext
    Header = _DummyWidget
    Footer = _DummyWidget
    Tree = _DummyTree
    DataTable = _DummyWidget
    Input = _DummyWidget
    Button = _DummyButton
    Label = _DummyWidget
    Select = _DummyWidget
    RichLog = _DummyWidget
    Switch = _DummyWidget
    TabbedContent = _DummyContext
    TabPane = _DummyContext

# PyLink library for interacting with SEGGER J-Link probes
try:
    import pylink
except ImportError:
    pylink = None


class SVDParser:
    """Parses CMSIS-SVD XML files to extract peripherals, registers, and bitfields."""

    @staticmethod
    def _parse_int(value: Optional[str], default: Optional[int] = None) -> Optional[int]:
        if value is None:
            return default
        try:
            return int(value.strip(), 0)
        except (ValueError, AttributeError):
            return default

    @staticmethod
    def _strip_xml_namespace(root: ET.Element) -> None:
        for elem in root.iter():
            if isinstance(elem.tag, str) and "}" in elem.tag:
                elem.tag = elem.tag.split("}", 1)[1]

    @staticmethod
    def _parse_field_position(field_node: ET.Element) -> Optional[tuple[int, int]]:
        bit_offset = SVDParser._parse_int(field_node.findtext("bitOffset"))
        bit_width = SVDParser._parse_int(field_node.findtext("bitWidth"))
        if bit_offset is not None and bit_width is not None:
            return bit_offset, bit_width

        bit_range = field_node.findtext("bitRange")
        if bit_range:
            # CMSIS-SVD bitRange syntax is usually "[msb:lsb]".
            cleaned = bit_range.strip().lstrip("[").rstrip("]")
            if ":" in cleaned:
                msb_str, lsb_str = cleaned.split(":", 1)
                msb = SVDParser._parse_int(msb_str)
                lsb = SVDParser._parse_int(lsb_str)
                if msb is not None and lsb is not None and msb >= lsb:
                    return lsb, (msb - lsb + 1)

        lsb = SVDParser._parse_int(field_node.findtext("lsb"))
        msb = SVDParser._parse_int(field_node.findtext("msb"))
        if lsb is not None and msb is not None and msb >= lsb:
            return lsb, (msb - lsb + 1)

        return None

    @staticmethod
    def parse(file_path: str) -> Optional[dict]:
        if not os.path.exists(file_path):
            return None

        try:
            tree = ET.parse(file_path)
            root = tree.getroot()
            SVDParser._strip_xml_namespace(root)
        except Exception as e:
            print(f"Error parsing SVD XML: {e}")
            return None

        device_info = {
            "name": root.findtext("name", "Unknown"),
            "peripherals": {}
        }

        # Locate the peripherals element block safely
        peripherals_node = root.find("peripherals")
        if peripherals_node is None:
            peripherals_node = root

        for peri_node in peripherals_node.findall("peripheral"):
            p_name = peri_node.findtext("name")
            base_addr_str = peri_node.findtext("baseAddress")
            if not p_name or not base_addr_str:
                continue

            base_addr = SVDParser._parse_int(base_addr_str)
            if base_addr is None:
                continue

            peripheral = {
                "name": p_name,
                "base_address": base_addr,
                "description": peri_node.findtext("description", ""),
                "registers": {}
            }

            # Extract child register layout trees
            regs_node = peri_node.find("registers")
            if regs_node is not None:
                for reg_node in regs_node.findall("register"):
                    r_name = reg_node.findtext("name")
                    offset_str = reg_node.findtext("addressOffset")
                    if not r_name or not offset_str:
                        continue

                    offset = SVDParser._parse_int(offset_str)
                    size = SVDParser._parse_int(reg_node.findtext("size", "32"), 32)
                    if offset is None or size is None:
                        continue

                    register = {
                        "name": r_name,
                        "address_offset": offset,
                        "size": size,
                        "description": reg_node.findtext("description", ""),
                        "fields": []
                    }

                    # Extract nested bitfield structural specifications
                    fields_node = reg_node.find("fields")
                    if fields_node is not None:
                        for field_node in fields_node.findall("field"):
                            f_name = field_node.findtext("name")
                            parsed_position = SVDParser._parse_field_position(field_node)
                            if not f_name or parsed_position is None:
                                continue

                            bit_offset, bit_width = parsed_position

                            register["fields"].append({
                                "name": f_name,
                                "bit_offset": bit_offset,
                                "bit_width": bit_width,
                                "description": field_node.findtext("description", "")
                            })

                    # Sort bit ranges from descending order for typical hardware map consistency
                    register["fields"].sort(key=lambda x: x["bit_offset"], reverse=True)
                    peripheral["registers"][r_name] = register

            device_info["peripherals"][p_name] = peripheral

        # Handle derivedPeripherals cross-references inheriting attributes from previous parents
        for p_name, peri in list(device_info["peripherals"].items()):
            for peri_node in peripherals_node.findall("peripheral"):
                if peri_node.findtext("name") == p_name and peri_node.attrib.get("derivedFrom"):
                    parent_name = peri_node.attrib.get("derivedFrom")
                    if parent_name in device_info["peripherals"]:
                        peri["registers"] = copy.deepcopy(device_info["peripherals"][parent_name]["registers"])

        return device_info


def build_default_cortex_m7_ppb_map() -> dict:
    """Return a minimal Cortex-M7 PPB register map when no core SVD is supplied."""
    def reg(name: str, offset: int, desc: str) -> dict:
        return {
            "name": name,
            "address_offset": offset,
            "size": 32,
            "description": desc,
            "fields": [],
        }

    return {
        "name": "Cortex-M7 PPB",
        "peripherals": {
            "SCB": {
                "name": "SCB",
                "base_address": 0xE000ED00,
                "description": "System Control Block",
                "registers": {
                    "CPUID": reg("CPUID", 0x000, "CPUID Base Register"),
                    "ICSR": reg("ICSR", 0x004, "Interrupt Control and State Register"),
                    "VTOR": reg("VTOR", 0x008, "Vector Table Offset Register"),
                    "AIRCR": reg("AIRCR", 0x00C, "Application Interrupt and Reset Control Register"),
                    "SCR": reg("SCR", 0x010, "System Control Register"),
                    "CCR": reg("CCR", 0x014, "Configuration and Control Register"),
                    "SHPR1": reg("SHPR1", 0x018, "System Handler Priority Register 1"),
                    "SHPR2": reg("SHPR2", 0x01C, "System Handler Priority Register 2"),
                    "SHPR3": reg("SHPR3", 0x020, "System Handler Priority Register 3"),
                    "SHCSR": reg("SHCSR", 0x024, "System Handler Control and State Register"),
                    "CFSR": reg("CFSR", 0x028, "Configurable Fault Status Register"),
                    "HFSR": reg("HFSR", 0x02C, "HardFault Status Register"),
                    "DFSR": reg("DFSR", 0x030, "Debug Fault Status Register"),
                    "MMFAR": reg("MMFAR", 0x034, "MemManage Fault Address Register"),
                    "BFAR": reg("BFAR", 0x038, "BusFault Address Register"),
                },
            },
            "SysTick": {
                "name": "SysTick",
                "base_address": 0xE000E010,
                "description": "System Tick Timer",
                "registers": {
                    "CTRL": reg("CTRL", 0x000, "Control and Status Register"),
                    "LOAD": reg("LOAD", 0x004, "Reload Value Register"),
                    "VAL": reg("VAL", 0x008, "Current Value Register"),
                    "CALIB": reg("CALIB", 0x00C, "Calibration Register"),
                },
            },
            "NVIC": {
                "name": "NVIC",
                "base_address": 0xE000E100,
                "description": "Nested Vectored Interrupt Controller",
                "registers": {
                    "ISER0": reg("ISER0", 0x000, "Interrupt Set-Enable Register 0"),
                    "ISPR0": reg("ISPR0", 0x100, "Interrupt Set-Pending Register 0"),
                    "IABR0": reg("IABR0", 0x200, "Interrupt Active Bit Register 0"),
                    "IPR0": reg("IPR0", 0x300, "Interrupt Priority Register 0"),
                },
            },
            "DWT": {
                "name": "DWT",
                "base_address": 0xE0001000,
                "description": "Data Watchpoint and Trace",
                "registers": {
                    "CTRL": reg("CTRL", 0x000, "Control Register"),
                    "CYCCNT": reg("CYCCNT", 0x004, "Cycle Count Register"),
                    "CPICNT": reg("CPICNT", 0x008, "CPI Count Register"),
                    "EXCCNT": reg("EXCCNT", 0x00C, "Exception Overhead Count Register"),
                    "SLEEPCNT": reg("SLEEPCNT", 0x010, "Sleep Count Register"),
                    "LSUCNT": reg("LSUCNT", 0x014, "LSU Count Register"),
                    "FOLDCNT": reg("FOLDCNT", 0x018, "Folded-instruction Count Register"),
                },
            },
            "CoreDebug": {
                "name": "CoreDebug",
                "base_address": 0xE000EDF0,
                "description": "Core Debug Registers",
                "registers": {
                    "DHCSR": reg("DHCSR", 0x000, "Debug Halting Control and Status Register"),
                    "DCRSR": reg("DCRSR", 0x004, "Debug Core Register Selector Register"),
                    "DCRDR": reg("DCRDR", 0x008, "Debug Core Register Data Register"),
                    "DEMCR": reg("DEMCR", 0x00C, "Debug Exception and Monitor Control Register"),
                },
            },
        },
    }


def merge_core_maps(base_map: dict, overlay_map: dict) -> dict:
    """Merge a parsed core SVD over the default PPB map.

    The base PPB map is always preserved so essential core peripherals stay visible
    even if the overlay SVD is incomplete.
    """
    merged = copy.deepcopy(base_map)

    overlay_name = str(overlay_map.get("name", "")).strip() if overlay_map else ""
    if overlay_name and overlay_name.lower() != "unknown":
        merged["name"] = overlay_name

    overlay_peripherals = overlay_map.get("peripherals", {}) if overlay_map else {}
    if isinstance(overlay_peripherals, dict):
        for p_name, p_info in overlay_peripherals.items():
            merged["peripherals"][p_name] = p_info

    return merged


class JLinkController:
    """Manages raw hardware probe transactions over pylink-square bindings."""

    def __init__(
        self,
        remote_host: str = "127.0.0.1",
        remote_port: int = 19020,
        usb_serial: str = "",
    ):
        self.link: Optional[pylink.JLink] = None
        self.connected: bool = False
        self.last_error: str = ""
        self.remote_host = remote_host
        self.remote_port = remote_port
        self.usb_serial = usb_serial.strip()
        self.register_index_by_key: dict = {}

    @staticmethod
    def _normalize_register_key(name: str) -> str:
        return "".join(ch for ch in name.upper() if ch.isalnum())

    def _refresh_register_index_cache(self) -> None:
        self.register_index_by_key = {}
        if not self.link:
            return
        try:
            for reg_idx in self.link.register_list():
                reg_name = self.link.register_name(reg_idx)
                key = self._normalize_register_key(str(reg_name))
                if key and key not in self.register_index_by_key:
                    self.register_index_by_key[key] = reg_idx
        except Exception:
            # Discovery may fail on some devices; reads can still use direct indices.
            self.register_index_by_key = {}

    def get_core_register_index_by_name(self, name: str) -> Optional[int]:
        return self.register_index_by_key.get(self._normalize_register_key(name))

    def fpu_register_summary(self) -> tuple[bool, int]:
        fpu_regs = 0
        for i in range(32):
            if self.get_core_register_index_by_name(f"S{i}") is not None:
                fpu_regs += 1
        has_fpscr = self.get_core_register_index_by_name("FPSCR") is not None
        return has_fpscr, fpu_regs

    def connect(self, chip_name: str, interface: str) -> bool:
        if pylink is None:
            self.last_error = "pylink-square not installed"
            return False
        try:
            self.disconnect()
            self.link = pylink.JLink()

            if self.usb_serial:
                # --usb forces direct local USB transport.
                self.link.open(serial_no=int(self.usb_serial, 0))
            else:
                self.link.open(ip_addr=f"{self.remote_host}:{self.remote_port}")

            # Re-map connection parameters configuration values
            if interface.upper() == "SWD":
                if_type = pylink.enums.JLinkInterfaces.SWD
            else:
                if_type = pylink.enums.JLinkInterfaces.JTAG

            self.link.set_tif(if_type)
            self.link.connect(chip_name, speed="auto")
            self._refresh_register_index_cache()
            self.connected = True
            self.last_error = ""
            return True
        except Exception as exc:
            self.connected = False
            self.last_error = str(exc)
            if self.link is not None:
                try:
                    self.link.close()
                except Exception:
                    pass
            self.link = None
            self.register_index_by_key = {}
            return False

    def disconnect(self) -> None:
        if self.link:
            try:
                self.link.close()
            except Exception:
                pass
        self.connected = False
        self.link = None
        self.register_index_by_key = {}

    def read_register(self, absolute_address: int, size_bits: int = 32) -> Optional[int]:
        if not self.connected or not self.link:
            return None
        try:
            if size_bits <= 8:
                return self.link.memory_read8(absolute_address, 1)[0]
            if size_bits <= 16:
                return self.link.memory_read16(absolute_address, 1)[0]
            value = self.link.memory_read32(absolute_address, 1)[0]
            if size_bits < 32:
                value &= (1 << size_bits) - 1
            return value
        except Exception:
            return None

    def read_memory_block(self, start_address: int, count: int, size_bits: int = 32) -> Optional[List[int]]:
        if not self.connected or not self.link or count <= 0:
            return None
        try:
            if size_bits <= 8:
                return list(self.link.memory_read8(start_address, count))
            if size_bits <= 16:
                return list(self.link.memory_read16(start_address, count))
            return list(self.link.memory_read32(start_address, count))
        except Exception:
            return None

    def read_core_register(self, register_index: int) -> Optional[int]:
        if not self.connected or not self.link:
            return None
        try:
            return self.link.register_read(register_index)
        except Exception:
            return None

    def read_core_register_candidates(self, register_ids: List[object]) -> Optional[int]:
        if not self.connected or not self.link:
            return None
        for register_id in register_ids:
            try:
                return self.link.register_read(register_id)
            except Exception:
                continue
        return None

    def read_core_register_by_name(self, register_name: str) -> Optional[int]:
        reg_idx = self.get_core_register_index_by_name(register_name)
        if reg_idx is None:
            return None
        return self.read_core_register(reg_idx)

    def halt(self) -> bool:
        if not self.connected or not self.link:
            self.last_error = "probe not connected"
            return False
        try:
            self.link.halt()
            self.last_error = ""
            return True
        except Exception as exc:
            self.last_error = str(exc)
            return False

    def step(self) -> bool:
        if not self.connected or not self.link:
            self.last_error = "probe not connected"
            return False
        try:
            if not self.link.halted():
                self.link.halt()
            self.link.step()
            self.last_error = ""
            return True
        except Exception as exc:
            self.last_error = str(exc)
            return False

    def go(self) -> bool:
        if not self.connected or not self.link:
            self.last_error = "probe not connected"
            return False
        try:
            # restart() is the common J-Link API entry to resume execution.
            self.link.restart()
            self.last_error = ""
            return True
        except Exception as exc:
            self.last_error = str(exc)
            return False

    def reset(self) -> bool:
        if not self.connected or not self.link:
            self.last_error = "probe not connected"
            return False
        try:
            self.link.reset()
            self.link.halt()
            self.last_error = ""
            return True
        except Exception as exc:
            self.last_error = str(exc)
            return False


class SVDDebuggerApp(App):
    """Textual TUI Application dashboard wrapper."""

    TITLE = "Jalopy - the crummy SVD aware debugger"

    # Inline style stylesheet defining clean panels and layouts
    CSS = """
    #config-bar {
        height: 1fr;
        background: $panel;
        padding: 1;
    }
    #config-bar Horizontal {
        height: auto;
        margin-bottom: 1;
        align: left middle;
    }
    .label-mgr {
        margin-right: 2;
    }
    #input-svd {
        width: 45fr;
    }
    #input-core-svd {
        width: 45fr;
    }
    #input-elf {
        width: 45fr;
    }
    #input-chip {
        width: 25fr;
    }
    #select-interface {
        width: 20fr;
    }
    #workspace {
        height: 1fr;
    }
    #command-bar {
        height: auto;
        background: $panel;
        border-bottom: solid $primary;
        padding: 1;
    }
    #command-bar Horizontal {
        height: auto;
        align: left middle;
    }
    #main-tabs {
        height: 1fr;
    }
    #tab-register-maps {
        height: 1fr;
    }
    #tab-stack-view {
        height: 1fr;
    }
    #tab-memory-view {
        height: 1fr;
    }
    #tab-rtt-view {
        height: 1fr;
    }
    #stack-view-root, #memory-view-root {
        height: 1fr;
        padding: 1;
    }
    #rtt-view-root {
        height: 1fr;
        padding: 1;
    }
    #stack-controls, #memory-controls {
        height: auto;
        margin-bottom: 1;
        align: left middle;
    }
    #rtt-controls {
        height: auto;
        margin-bottom: 1;
        align: left middle;
    }
    #input-stack-depth {
        width: 10;
    }
    #input-mem-addr {
        width: 22;
    }
    #input-mem-count {
        width: 10;
    }
    #select-mem-width {
        width: 12;
    }
    #input-rtt-cb {
        width: 20;
    }
    #input-rtt-buffer {
        width: 8;
    }
    #input-rtt-bytes {
        width: 8;
    }
    #left-pane {
        width: 30fr;
        border-right: solid $primary;
    }
    #right-pane {
        width: 70fr;
    }
    #stack-table-pane, #memory-table-pane {
        height: 1fr;
        min-height: 8;
    }
    #log-output {
        height: 6;
        background: $panel;
        border-top: solid $primary;
    }
    Input, Select, Button {
        margin-right: 2;
    }
    """

    CORE_CPU_REGISTERS = [
        ("R0", 0, "General-purpose register 0"),
        ("R1", 1, "General-purpose register 1"),
        ("R2", 2, "General-purpose register 2"),
        ("R3", 3, "General-purpose register 3"),
        ("R4", 4, "General-purpose register 4"),
        ("R5", 5, "General-purpose register 5"),
        ("R6", 6, "General-purpose register 6"),
        ("R7", 7, "General-purpose register 7"),
        ("R8", 8, "General-purpose register 8"),
        ("R9", 9, "General-purpose register 9"),
        ("R10", 10, "General-purpose register 10"),
        ("R11", 11, "General-purpose register 11"),
        ("R12", 12, "General-purpose register 12"),
        ("SP", 13, "Stack Pointer"),
        ("LR", 14, "Link Register"),
        ("PC", 15, "Program Counter"),
        ("xPSR", 16, "Program Status Register"),
    ]

    CORE_FPU_REGISTERS = [
        (f"S{i}", f"Floating-point single register S{i}")
        for i in range(32)
    ] + [
        ("FPSCR", "Floating-Point Status and Control Register")
    ]

    STACK_POINTER_CANDIDATES = {
        "MSP": ["MSP", "R13_MSP", "R13MSP"],
        "PSP": ["PSP", "R13_PSP", "R13PSP"],
    }

    def __init__(
        self,
        svd_path: str = "",
        core_svd_path: str = "",
        elf_path: str = "",
        chip_name: str = "STM32H753ZI",
        interface: str = "SWD",
        usb_serial: str = "",
        remote_host: str = "127.0.0.1",
        remote_port: int = 19020,
        auto_load_svd: bool = False,
        auto_connect: bool = False,
        auto_rtt_capture: bool = False,
        poll_interval_s: float = 0.5,
    ):
        super().__init__()
        self.jlink = JLinkController(
            remote_host=remote_host,
            remote_port=remote_port,
            usb_serial=usb_serial,
        )
        self.device_data: Optional[dict] = None
        self.core_data: dict = build_default_cortex_m7_ppb_map()
        self.active_peripheral: Optional[dict] = None
        self.active_rows: List[tuple] = []
        self.stack_rows: List[tuple] = []
        self.memory_rows: List[tuple] = []
        self.rtt_pending_text: dict[int, str] = {}
        self.initial_svd_path = svd_path
        self.initial_core_svd_path = core_svd_path
        self.initial_elf_path = elf_path
        self.initial_chip_name = chip_name
        self.initial_interface = interface.upper()
        self.auto_load_svd = auto_load_svd
        self.auto_connect = auto_connect
        self.auto_rtt_capture = auto_rtt_capture
        self.poll_interval_s = poll_interval_s

        # Grid column mapping identifiers
        self.col_name_key = None
        self.col_addr_key = None
        self.col_val_key = None
        self.col_desc_key = None
        self.col_stack_name_key = None
        self.col_stack_addr_key = None
        self.col_stack_val_key = None
        self.col_stack_desc_key = None
        self.col_mem_name_key = None
        self.col_mem_addr_key = None
        self.col_mem_val_key = None
        self.col_mem_desc_key = None
        self.poll_timer = None
        self.rtt_poll_timer = None

    def compose(self) -> ComposeResult:
        yield Header()
        with Vertical(id="workspace"):
            with Vertical(id="command-bar"):
                with Horizontal():
                    yield Button("Connect Probe", id="btn-connect", variant="success")
                    yield Button("Halt", id="btn-halt")
                    yield Button("Step", id="btn-step")
                    yield Button("Go", id="btn-go")
                    yield Button("Reset", id="btn-reset", variant="warning")

            with TabbedContent(initial="tab-config", id="main-tabs"):
                with TabPane("Config", id="tab-config"):
                    with Vertical(id="config-bar"):
                        with Horizontal():
                            yield Label("SVD XML Path:", classes="label-mgr")
                            yield Input(placeholder="Type local SVD file path location...", id="input-svd")
                            yield Button("Load SVD", id="btn-load-svd", variant="primary")
                        with Horizontal():
                            yield Label("Core SVD Path:", classes="label-mgr")
                            yield Input(placeholder="Optional Cortex-M core SVD XML path...", id="input-core-svd")
                            yield Button("Load Core SVD", id="btn-load-core-svd", variant="primary")
                        with Horizontal():
                            yield Label("ELF Path:", classes="label-mgr")
                            yield Input(placeholder="Optional ELF path for future symbol features...", id="input-elf")
                        with Horizontal():
                            yield Label("MCU Target Name:", classes="label-mgr")
                            yield Input(value="STM32H753ZI", id="input-chip")
                            yield Label("Interface Type:", classes="label-mgr")
                            yield Select([("SWD", "SWD"), ("JTAG", "JTAG")], value="SWD", id="select-interface")

                with TabPane("Register Maps", id="tab-register-maps"):
                    with Horizontal(id="workspace-registers"):
                        with Vertical(id="left-pane"):
                            yield Tree("Peripherals Hierarchies", id="tree-peripherals")
                        with Vertical(id="right-pane"):
                            yield DataTable(id="table-registers")

                with TabPane("Stack Viewer", id="tab-stack-view"):
                    with Vertical(id="stack-view-root"):
                        with Horizontal(id="stack-controls"):
                            yield Label("Depth (words):", classes="label-mgr")
                            yield Input(value="8", id="input-stack-depth")
                            yield Button("Refresh Stack", id="btn-refresh-stack", variant="primary")
                        with Vertical(id="stack-table-pane"):
                            yield DataTable(id="table-stack")

                with TabPane("Memory Viewer", id="tab-memory-view"):
                    with Vertical(id="memory-view-root"):
                        with Horizontal(id="memory-controls"):
                            yield Label("Memory Addr:", classes="label-mgr")
                            yield Input(value="0xE000ED00", id="input-mem-addr")
                            yield Label("Count:", classes="label-mgr")
                            yield Input(value="16", id="input-mem-count")
                            yield Label("Access:", classes="label-mgr")
                            yield Select([("1-byte", "1"), ("2-byte", "2"), ("4-byte", "4")], value="4", id="select-mem-width")
                            yield Button("Read Memory", id="btn-read-mem", variant="primary")
                        with Vertical(id="memory-table-pane"):
                            yield DataTable(id="table-memory")

                with TabPane("RTT Console", id="tab-rtt-view"):
                    with Vertical(id="rtt-view-root"):
                        with Horizontal(id="rtt-controls"):
                            yield Label("CB Addr:", classes="label-mgr")
                            yield Input(placeholder="Optional RTT control block address", id="input-rtt-cb")
                            yield Label("Buffer:", classes="label-mgr")
                            yield Input(value="0", id="input-rtt-buffer")
                            yield Label("Bytes:", classes="label-mgr")
                            yield Input(value="256", id="input-rtt-bytes")
                            yield Label("Continuous:", classes="label-mgr")
                            yield Switch(value=self.auto_rtt_capture, id="switch-rtt-continuous")
                            yield Button("Start RTT", id="btn-rtt-start", variant="primary")
                            yield Button("Read RTT", id="btn-rtt-read", variant="success")
                            yield Button("Stop RTT", id="btn-rtt-stop", variant="warning")
                            yield Button("Clear", id="btn-rtt-clear")
                        yield RichLog(id="rtt-log", max_lines=400, markup=True)

        yield RichLog(id="log-output", max_lines=100, markup=True)
        yield Footer()

    def on_mount(self) -> None:
        """Fires up base table parameters initialization layout hooks upon initialization."""
        table = self.query_one("#table-registers", DataTable)
        self.col_name_key = table.add_column("Name")
        self.col_addr_key = table.add_column("Address/Range")
        self.col_val_key = table.add_column("Value (Hex/Dec)")
        self.col_desc_key = table.add_column("Description")

        stack_table = self.query_one("#table-stack", DataTable)
        self.col_stack_name_key = stack_table.add_column("Name")
        self.col_stack_addr_key = stack_table.add_column("Address/Range")
        self.col_stack_val_key = stack_table.add_column("Value (Hex/Dec)")
        self.col_stack_desc_key = stack_table.add_column("Description")

        mem_table = self.query_one("#table-memory", DataTable)
        self.col_mem_name_key = mem_table.add_column("Name")
        self.col_mem_addr_key = mem_table.add_column("Address/Range")
        self.col_mem_val_key = mem_table.add_column("Value (Hex/Dec)")
        self.col_mem_desc_key = mem_table.add_column("Description")

        self.query_one("#rtt-log", RichLog).write("RTT console ready.")

        logger = self.query_one("#log-output", RichLog)
        logger.write("Terminal TUI environment interface pipeline ready.")

        # Apply startup defaults from CLI args.
        self.query_one("#input-svd", Input).value = self.initial_svd_path
        self.query_one("#input-core-svd", Input).value = self.initial_core_svd_path
        self.query_one("#input-elf", Input).value = self.initial_elf_path
        self.query_one("#input-chip", Input).value = self.initial_chip_name
        select = self.query_one("#select-interface", Select)
        select.value = "JTAG" if self.initial_interface == "JTAG" else "SWD"
        self.query_one("#switch-rtt-continuous", Switch).value = self.auto_rtt_capture
        self._sync_rtt_read_controls()

        self.populate_peripheral_tree()

        if self.auto_load_svd and self.initial_svd_path:
            self._load_svd(self.initial_svd_path)

        if self.initial_core_svd_path:
            self._load_core_svd(self.initial_core_svd_path)

        if self.auto_connect:
            self._connect_probe()

        if pylink is None:
            logger.write("[bold red]CRITICAL: 'pylink-square' library missing. Hardware communication loops disabled.[/bold red]")

    def on_unmount(self) -> None:
        if self.poll_timer is not None:
            self.poll_timer.stop()
            self.poll_timer = None
        if self.rtt_poll_timer is not None:
            self.rtt_poll_timer.stop()
            self.rtt_poll_timer = None
        self.jlink.disconnect()

    def on_button_pressed(self, event: Button.Pressed) -> None:
        """Routes interface event clicks to target function definitions."""
        if event.button.id == "btn-load-svd":
            svd_path = self.query_one("#input-svd", Input).value.strip()
            self._load_svd(svd_path)

        elif event.button.id == "btn-load-core-svd":
            core_svd_path = self.query_one("#input-core-svd", Input).value.strip()
            self._load_core_svd(core_svd_path)

        elif event.button.id == "btn-connect":
            if not self.jlink.connected:
                self._connect_probe()
            else:
                self._disconnect_probe()

        elif event.button.id == "btn-halt":
            self._control_target("halt")

        elif event.button.id == "btn-step":
            self._control_target("step")

        elif event.button.id == "btn-go":
            self._control_target("go")

        elif event.button.id == "btn-reset":
            self._control_target("reset")

        elif event.button.id == "btn-read-mem":
            self._show_memory_inspector()

        elif event.button.id == "btn-refresh-stack":
            self._show_stack_view()

        elif event.button.id == "btn-rtt-start":
            self._start_rtt_console()

        elif event.button.id == "btn-rtt-read":
            self._read_rtt_console()

        elif event.button.id == "btn-rtt-stop":
            self._stop_rtt_console()

        elif event.button.id == "btn-rtt-clear":
            self.query_one("#rtt-log", RichLog).clear()

    def on_switch_changed(self, event: Switch.Changed) -> None:
        if event.switch.id != "switch-rtt-continuous":
            return

        self.auto_rtt_capture = bool(event.value)
        self._sync_rtt_read_controls()

        if self.auto_rtt_capture and self.jlink.connected:
            self._start_rtt_console()
        elif not self.auto_rtt_capture and self.rtt_poll_timer is not None:
            self.rtt_poll_timer.stop()
            self.rtt_poll_timer = None

    def _sync_rtt_read_controls(self) -> None:
        switch = self.query_one("#switch-rtt-continuous", Switch)
        read_button = self.query_one("#btn-rtt-read", Button)
        if switch.value != self.auto_rtt_capture:
            switch.value = self.auto_rtt_capture
        read_button.disabled = self.auto_rtt_capture

    @staticmethod
    def _parse_int_input(value: str, default: int) -> int:
        try:
            return int(value.strip(), 0)
        except Exception:
            return default

    def _resolve_stack_pointer(self, pointer_name: str) -> Optional[int]:
        candidates = self.STACK_POINTER_CANDIDATES.get(pointer_name, [])
        for candidate in candidates:
            reg_val = self.jlink.read_core_register_by_name(candidate)
            if reg_val is not None:
                return reg_val & 0xFFFFFFFF

        if pointer_name == "MSP":
            # Fallback to architectural SP index if named MSP is unavailable.
            reg_val = self.jlink.read_core_register(13)
            if reg_val is not None:
                return reg_val & 0xFFFFFFFF
        return None

    def _show_memory_inspector(self) -> None:
        logger = self.query_one("#log-output", RichLog)
        table = self.query_one("#table-memory", DataTable)

        if not self.jlink.connected:
            logger.write("[yellow]Memory read ignored: probe is not connected.[/yellow]")
            return

        addr_text = self.query_one("#input-mem-addr", Input).value
        count_text = self.query_one("#input-mem-count", Input).value
        width_value = self.query_one("#select-mem-width", Select).value

        address = self._parse_int_input(addr_text, -1)
        count = self._parse_int_input(count_text, -1)
        access_size_bytes = self._parse_int_input(str(width_value), 4)
        width = access_size_bytes * 8

        if address < 0:
            logger.write("[red]Memory inspector: invalid address.[/red]")
            return
        if count <= 0 or count > 256:
            logger.write("[red]Memory inspector: count must be between 1 and 256.[/red]")
            return
        if access_size_bytes not in (1, 2, 4):
            logger.write("[red]Memory inspector: access size must be 1, 2, or 4 bytes.[/red]")
            return

        table.clear(columns=False)
        self.memory_rows = []

        step = access_size_bytes
        for idx in range(count):
            addr = address + (idx * step)
            row_key = table.add_row(f"MEM[{idx}]", hex(addr), "Reading...", f"Memory ({access_size_bytes}-byte)")
            self.memory_rows.append((row_key, {"type": "memory_row", "address": addr, "size": width}))

        logger.write(f"Memory inspector loaded: addr={hex(address)}, count={count}, access={access_size_bytes}-byte")
        self.poll_active_registers()

    def _show_stack_view(self) -> None:
        logger = self.query_one("#log-output", RichLog)
        table = self.query_one("#table-stack", DataTable)

        if not self.jlink.connected:
            logger.write("[yellow]Stack view refresh ignored: probe is not connected.[/yellow]")
            return

        depth_text = self.query_one("#input-stack-depth", Input).value
        depth_words = self._parse_int_input(depth_text, 8)
        if depth_words <= 0 or depth_words > 128:
            logger.write("[red]Stack view: depth must be between 1 and 128 words.[/red]")
            return

        table.clear(columns=False)
        self.stack_rows = []

        for pointer_name in ("MSP", "PSP"):
            ptr_row = table.add_row(pointer_name, "CoreReg", "Reading...", f"{pointer_name} stack pointer")
            self.stack_rows.append((ptr_row, {"type": "stack_ptr_row", "pointer": pointer_name}))
            for word_offset in range(depth_words):
                mem_row = table.add_row(
                    f" {pointer_name}[+{word_offset * 4}]",
                    "Stack",
                    "Reading...",
                    f"{pointer_name} memory word {word_offset}",
                )
                self.stack_rows.append(
                    (
                        mem_row,
                        {
                            "type": "stack_mem_row",
                            "pointer": pointer_name,
                            "offset_words": word_offset,
                        },
                    )
                )

        logger.write(f"Stack viewer loaded: depth={depth_words} words for MSP/PSP")
        self.poll_active_registers()

    @staticmethod
    def _read_rtt_block_address(value: str) -> Optional[int]:
        try:
            return int(value.strip(), 0)
        except Exception:
            return None

    def _start_rtt_console(self) -> None:
        logger = self.query_one("#rtt-log", RichLog)
        cb_text = self.query_one("#input-rtt-cb", Input).value.strip()
        cb_addr = self._read_rtt_block_address(cb_text) if cb_text else None

        if not self.jlink.connected:
            logger.write("[yellow]RTT start ignored: probe is not connected.[/yellow]")
            return

        if self.rtt_poll_timer is not None:
            self.rtt_poll_timer.stop()
            self.rtt_poll_timer = None

        try:
            self.jlink.link.rtt_stop()
        except Exception:
            pass

        try:
            if cb_addr is None:
                self.jlink.link.rtt_start()
                logger.write("[green]RTT started using default discovery.[/green]")
            else:
                self.jlink.link.rtt_start(cb_addr)
                logger.write(f"[green]RTT started at control block 0x{cb_addr:08X}.[/green]")

            self.rtt_pending_text.clear()

            if self.auto_rtt_capture:
                self.rtt_poll_timer = self.set_interval(self.poll_interval_s, self._read_rtt_console_silent)
                self._read_rtt_console(quiet=True)
            self._sync_rtt_read_controls()
        except Exception as exc:
            logger.write(f"[red]RTT start failed: {exc}[/red]")

    def _stop_rtt_console(self) -> None:
        logger = self.query_one("#rtt-log", RichLog)
        if self.rtt_poll_timer is not None:
            self.rtt_poll_timer.stop()
            self.rtt_poll_timer = None
        if not self.jlink.connected or not self.jlink.link:
            logger.write("[yellow]RTT stop ignored: probe is not connected.[/yellow]")
            return

        try:
            self.jlink.link.rtt_stop()
            logger.write("[green]RTT stopped.[/green]")
        except Exception as exc:
            logger.write(f"[red]RTT stop failed: {exc}[/red]")
        finally:
            self.rtt_pending_text.clear()
            self.auto_rtt_capture = False
            self._sync_rtt_read_controls()

    def _read_rtt_console_silent(self) -> None:
        self._read_rtt_console(quiet=True)

    def _restart_rtt_after_reset(self) -> None:
        """Restart RTT discovery after a reset so the console follows the new session."""
        if not self.jlink.connected or not self.jlink.link:
            return

        logger = self.query_one("#rtt-log", RichLog)
        cb_text = self.query_one("#input-rtt-cb", Input).value.strip()
        cb_addr = self._read_rtt_block_address(cb_text) if cb_text else None

        try:
            self.jlink.link.rtt_stop()
        except Exception:
            pass

        try:
            if cb_addr is None:
                self.jlink.link.rtt_start()
                logger.write("[green]RTT rediscovered after reset.[/green]")
            else:
                self.jlink.link.rtt_start(cb_addr)
                logger.write(f"[green]RTT rediscovered after reset at 0x{cb_addr:08X}.[/green]")
        except Exception as exc:
            logger.write(f"[red]RTT rediscovery after reset failed: {exc}[/red]")
            return

        self.rtt_pending_text.clear()

        if self.auto_rtt_capture:
            if self.rtt_poll_timer is not None:
                self.rtt_poll_timer.stop()
            self.rtt_poll_timer = self.set_interval(self.poll_interval_s, self._read_rtt_console_silent)

        self._read_rtt_console(quiet= self.auto_rtt_capture)

    def _read_rtt_console(self, quiet: bool = False) -> None:
        logger = self.query_one("#rtt-log", RichLog)
        if not self.jlink.connected or not self.jlink.link:
            logger.write("[yellow]RTT read ignored: probe is not connected.[/yellow]")
            return

        buffer_index = self._parse_int_input(self.query_one("#input-rtt-buffer", Input).value, 0)
        num_bytes = self._parse_int_input(self.query_one("#input-rtt-bytes", Input).value, 256)
        if buffer_index < 0:
            logger.write("[red]RTT read: buffer index must be non-negative.[/red]")
            return
        if num_bytes <= 0 or num_bytes > 4096:
            logger.write("[red]RTT read: bytes must be between 1 and 4096.[/red]")
            return

        try:
            data = self.jlink.link.rtt_read(buffer_index, num_bytes)
            payload = bytes(data)
            if not payload:
                if not quiet:
                    logger.write("[dim]RTT: no new data.[/dim]")
                return

            text = payload.decode("utf-8", errors="replace")
            pending = self.rtt_pending_text.get(buffer_index, "") + text
            normalized = pending.replace("\r\n", "\n")
            lines = normalized.split("\n")
            self.rtt_pending_text[buffer_index] = lines.pop() if lines else ""

            for line in lines:
                logger.write(line)
        except Exception as exc:
            logger.write(f"[red]RTT read failed: {exc}[/red]")

    def _load_svd(self, svd_path: str) -> None:
        logger = self.query_one("#log-output", RichLog)
        if not svd_path:
            logger.write("[red]Validation Error: Please configure a valid SVD file location target profile.[/red]")
            return

        logger.write(f"Parsing targeted register memory profiles from file: {svd_path}")
        parsed_data = SVDParser.parse(svd_path)
        if parsed_data:
            self.device_data = parsed_data
            self.populate_peripheral_tree()
            logger.write(f"[green]Successfully linked SVD structures for target: {self.device_data['name']}[/green]")
        else:
            logger.write("[red]Parser Fault: Structural error occurred processing metadata profile configuration file.[/red]")

    def _load_core_svd(self, svd_path: str) -> None:
        logger = self.query_one("#log-output", RichLog)
        if not svd_path:
            self.core_data = build_default_cortex_m7_ppb_map()
            self.populate_peripheral_tree()
            logger.write("Loaded built-in Cortex-M7 PPB core register map.")
            return

        logger.write(f"Parsing Cortex-M core register profile from file: {svd_path}")
        parsed_data = SVDParser.parse(svd_path)
        if parsed_data:
            self.core_data = merge_core_maps(build_default_cortex_m7_ppb_map(), parsed_data)
            self.populate_peripheral_tree()
            core_name = self.core_data.get("name", "Cortex-M7 PPB")
            p_count = len(self.core_data.get("peripherals", {}))
            logger.write(f"[green]Loaded core SVD structures for target: {core_name} (peripherals: {p_count})[/green]")
        else:
            logger.write("[red]Core SVD parse failure. Keeping current core register map.[/red]")

    def _connect_probe(self) -> None:
        logger = self.query_one("#log-output", RichLog)
        connect_button = self.query_one("#btn-connect", Button)
        chip = self.query_one("#input-chip", Input).value.strip()
        select_value = self.query_one("#select-interface", Select).value
        interface = str(select_value) if select_value else "SWD"
        logger.write(f"Initiating target link sequences via probe toward '{chip}' over {interface}...")

        if self.jlink.connect(chip, interface):
            transport = (
                f"USB serial {self.jlink.usb_serial}"
                if self.jlink.usb_serial
                else f"JLinkRemoteServer {self.jlink.remote_host}:{self.jlink.remote_port}"
            )
            logger.write(f"[green]Connected to target via {transport}.[/green]")
            has_fpscr, s_count = self.jlink.fpu_register_summary()
            logger.write(
                f"FPU register discovery: S regs found={s_count}/32, FPSCR={'yes' if has_fpscr else 'no'}"
            )
            connect_button.label = "Disconnect Probe"
            connect_button.variant = "error"
            if self.poll_timer is not None:
                self.poll_timer.stop()
            self.poll_timer = self.set_interval(self.poll_interval_s, self.poll_active_registers)
            if self.auto_rtt_capture:
                self._start_rtt_console()
        else:
            detail = self.jlink.last_error or "unknown error"
            logger.write(f"[red]Hardware Connection Failure: {detail}[/red]")

    def _disconnect_probe(self) -> None:
        logger = self.query_one("#log-output", RichLog)
        connect_button = self.query_one("#btn-connect", Button)
        if self.poll_timer:
            self.poll_timer.stop()
            self.poll_timer = None
        if self.rtt_poll_timer:
            self.rtt_poll_timer.stop()
            self.rtt_poll_timer = None
        try:
            if self.jlink.connected and self.jlink.link:
                self.jlink.link.rtt_stop()
        except Exception:
            pass
        self.jlink.disconnect()
        connect_button.label = "Connect Probe"
        connect_button.variant = "success"
        logger.write("J-Link hardware abstraction pipeline session teardown completed successfully.")
        self.query_one("#table-registers", DataTable).clear(columns=False)
        self.active_rows = []

    def _control_target(self, action: str) -> None:
        logger = self.query_one("#log-output", RichLog)
        if not self.jlink.connected:
            logger.write("[yellow]Target control ignored: probe is not connected.[/yellow]")
            return

        operations = {
            "halt": self.jlink.halt,
            "step": self.jlink.step,
            "go": self.jlink.go,
            "reset": self.jlink.reset,
        }
        handler = operations.get(action)
        if handler is None:
            return

        if handler():
            logger.write(f"[green]Target action completed: {action}[/green]")
            if action == "reset":
                self._restart_rtt_after_reset()
            self.poll_active_registers()
        else:
            detail = self.jlink.last_error or "unknown error"
            logger.write(f"[red]Target action failed ({action}): {detail}[/red]")

    def populate_peripheral_tree(self) -> None:
        """Maps nested architectural elements cleanly out into standard Tree component structures."""
        tree = self.query_one("#tree-peripherals", Tree)
        tree.clear()
        tree.root.label = "Register Maps"

        if self.device_data:
            dev_node = tree.root.add(f"MCU: {self.device_data['name']}", data={"type": "category"})
            for p_name, p_info in sorted(self.device_data["peripherals"].items()):
                p_node = dev_node.add(p_name, data={"type": "peripheral", "source": "mcu", "name": p_name})
                for r_name in sorted(p_info["registers"].keys()):
                    p_node.add(r_name, data={"type": "register", "source": "mcu", "peripheral": p_name, "register": r_name})

        if self.core_data:
            core_node = tree.root.add(f"Core: {self.core_data['name']}", data={"type": "category"})
            core_node.add("CPU Registers", data={"type": "core_cpu_registers", "source": "core"})
            core_node.add("FPU Registers", data={"type": "core_fpu_registers", "source": "core"})
            core_node.add("Fault Status", data={"type": "core_fault_status", "source": "core"})
            for p_name, p_info in sorted(self.core_data["peripherals"].items()):
                p_node = core_node.add(p_name, data={"type": "peripheral", "source": "core", "name": p_name})
                for r_name in sorted(p_info["registers"].keys()):
                    p_node.add(r_name, data={"type": "register", "source": "core", "peripheral": p_name, "register": r_name})

        tree.root.expand()

    def on_tree_node_selected(self, event: Tree.NodeSelected) -> None:
        """Handles structural node selections to cleanly pivot the active table context window view layout mapping structures."""
        data = event.node.data
        if not data:
            return

        if data.get("type") == "category":
            return

        source = data.get("source", "mcu")
        source_map = self.device_data if source == "mcu" else self.core_data
        if not source_map:
            return

        table = self.query_one("#table-registers", DataTable)
        table.clear(columns=False)
        self.active_rows = []

        if data["type"] == "core_cpu_registers":
            for reg_name, reg_index, reg_desc in self.CORE_CPU_REGISTERS:
                row_key = table.add_row(reg_name, f"CoreReg[{reg_index}]", "0x00000000", reg_desc)
                self.active_rows.append((row_key, {"type": "core_cpu_row", "index": reg_index}))
            self.poll_active_registers()
            return

        if data["type"] == "core_fpu_registers":
            for reg_name, reg_desc in self.CORE_FPU_REGISTERS:
                row_key = table.add_row(reg_name, "FPU", "0x00000000", reg_desc)
                self.active_rows.append((row_key, {"type": "core_fpu_row", "name": reg_name}))
            self.poll_active_registers()
            return

        if data["type"] == "core_fault_status":
            fault_regs = [
                ("CFSR", 0xE000ED28, "Configurable Fault Status Register"),
                ("HFSR", 0xE000ED2C, "HardFault Status Register"),
                ("DFSR", 0xE000ED30, "Debug Fault Status Register"),
                ("MMFAR", 0xE000ED34, "MemManage Fault Address Register"),
                ("BFAR", 0xE000ED38, "BusFault Address Register"),
            ]
            for reg_name, reg_addr, reg_desc in fault_regs:
                reg_row = table.add_row(reg_name, hex(reg_addr), "Reading...", reg_desc)
                self.active_rows.append((reg_row, {"type": "fault_reg_row", "name": reg_name, "address": reg_addr}))

            fault_flags = [
                ("HFSR", 1 << 30, "FORCED", "Escalated configurable fault"),
                ("HFSR", 1 << 1, "VECTTBL", "Fault on vector table read"),
                ("DFSR", 1 << 0, "HALTED", "Halt requested"),
                ("DFSR", 1 << 1, "BKPT", "Breakpoint encountered"),
                ("DFSR", 1 << 2, "DWTTRAP", "DWT debug event"),
                ("CFSR", 1 << 0, "IACCVIOL", "Instruction access violation"),
                ("CFSR", 1 << 1, "DACCVIOL", "Data access violation"),
                ("CFSR", 1 << 7, "MMARVALID", "MMFAR contains valid fault address"),
                ("CFSR", 1 << 8, "IBUSERR", "Instruction bus error"),
                ("CFSR", 1 << 9, "PRECISERR", "Precise data bus error"),
                ("CFSR", 1 << 10, "IMPRECISERR", "Imprecise data bus error"),
                ("CFSR", 1 << 15, "BFARVALID", "BFAR contains valid fault address"),
                ("CFSR", 1 << 16, "UNDEFINSTR", "Undefined instruction"),
                ("CFSR", 1 << 17, "INVSTATE", "Invalid state usage fault"),
                ("CFSR", 1 << 18, "INVPC", "Invalid PC load usage fault"),
                ("CFSR", 1 << 24, "UNALIGNED", "Unaligned access usage fault"),
                ("CFSR", 1 << 25, "DIVBYZERO", "Divide by zero usage fault"),
            ]
            for source_reg, mask, flag_name, flag_desc in fault_flags:
                flag_row = table.add_row(
                    f" {source_reg}.{flag_name}",
                    hex(mask),
                    "Checking...",
                    flag_desc,
                )
                self.active_rows.append(
                    (
                        flag_row,
                        {
                            "type": "fault_flag_row",
                            "source_reg": source_reg,
                            "mask": mask,
                        },
                    )
                )
            self.poll_active_registers()
            return

        if data["type"] == "peripheral":
            p_name = data["name"]
            self.active_peripheral = source_map["peripherals"][p_name]
            registers = self.active_peripheral["registers"]

            for r_name, r_info in sorted(registers.items()):
                abs_addr = self.active_peripheral["base_address"] + r_info["address_offset"]
                row_key = table.add_row(r_name, hex(abs_addr), "0x00000000 (Disconnected)", r_info["description"])
                self.active_rows.append((row_key, {"type": "register_row", "address": abs_addr, "size": r_info["size"], "info": r_info}))

        elif data["type"] == "register":
            p_name = data["peripheral"]
            r_name = data["register"]
            self.active_peripheral = source_map["peripherals"][p_name]
            r_info = self.active_peripheral["registers"][r_name]
            abs_addr = self.active_peripheral["base_address"] + r_info["address_offset"]

            # Construct top-level structural root hardware block identifier row entry
            row_key = table.add_row(f"[bold][{r_name}][/bold]", hex(abs_addr), "Fetching hardware telemetry lines...", r_info["description"])
            self.active_rows.append((row_key, {"type": "register_row", "address": abs_addr, "size": r_info["size"], "info": r_info}))

            # Map sub-nested individual register bit fields
            for field in r_info["fields"]:
                msb = field["bit_offset"] + field["bit_width"] - 1
                lsb = field["bit_offset"]
                bit_range_str = f"Bits [{msb}:{lsb}]" if field["bit_width"] > 1 else f"Bit [{lsb}]"

                f_row_key = table.add_row(f" └─ {field['name']}", bit_range_str, "-", field["description"])
                self.active_rows.append((f_row_key, {"type": "field_row", "offset": field["bit_offset"], "width": field["bit_width"]}))

        self.poll_active_registers()

    def poll_active_registers(self) -> None:
        """Periodically clocks live read sweeps directly against the microcontroller hardware pipelines."""
        if not self.jlink.connected:
            return

        table = self.query_one("#table-registers", DataTable)
        stack_table = self.query_one("#table-stack", DataTable)
        mem_table = self.query_one("#table-memory", DataTable)
        current_reg_val: Optional[int] = None
        fault_values: dict = {}

        for row_key, metadata in self.active_rows:
            if metadata["type"] == "register_row":
                addr = metadata["address"]
                size = metadata["size"]
                val = self.jlink.read_register(addr, size)

                if val is not None:
                    display_bits = 32 if size >= 32 else max(1, size)
                    display_mask = (1 << display_bits) - 1
                    unsigned_val = val & display_mask
                    current_reg_val = unsigned_val
                    hex_width = max(2, (display_bits + 3) // 4)
                    hex_str = f"0x{unsigned_val:0{hex_width}X}"
                    dec_str = f"({unsigned_val})"
                    table.update_cell(row_key, self.col_val_key, f"[bold blue]{hex_str} {dec_str}[/bold blue]")
                else:
                    table.update_cell(row_key, self.col_val_key, "[bold red]Bus Fault/Read Error[/bold red]")
                    current_reg_val = None

            elif metadata["type"] == "core_cpu_row":
                reg_index = metadata["index"]
                val = self.jlink.read_core_register(reg_index)
                if val is not None:
                    unsigned_val = val & 0xFFFFFFFF
                    hex_str = f"0x{unsigned_val:08X}"
                    dec_str = f"({unsigned_val})"
                    table.update_cell(row_key, self.col_val_key, f"[bold cyan]{hex_str} {dec_str}[/bold cyan]")
                else:
                    table.update_cell(row_key, self.col_val_key, "[bold red]Read Error/Not Halted[/bold red]")

            elif metadata["type"] == "core_fpu_row":
                reg_name = metadata["name"]
                val = self.jlink.read_core_register_by_name(reg_name)
                if val is not None:
                    unsigned_val = val & 0xFFFFFFFF
                    hex_str = f"0x{unsigned_val:08X}"
                    if reg_name.startswith("S") and reg_name[1:].isdigit():
                        float_val = struct.unpack("<f", struct.pack("<I", unsigned_val))[0]
                        table.update_cell(
                            row_key,
                            self.col_val_key,
                            f"[bold magenta]{hex_str} ({float_val:.7g})[/bold magenta]",
                        )
                    else:
                        table.update_cell(row_key, self.col_val_key, f"[bold magenta]{hex_str} ({unsigned_val})[/bold magenta]")
                else:
                    table.update_cell(row_key, self.col_val_key, "[bold red]Read Error/Not Available[/bold red]")

            elif metadata["type"] == "memory_row":
                addr = metadata["address"]
                size = metadata["size"]
                val = self.jlink.read_register(addr, size)
                if val is not None:
                    bits = max(1, int(size))
                    mask = (1 << bits) - 1
                    unsigned_val = val & mask
                    hex_width = max(2, (bits + 3) // 4)
                    mem_table.update_cell(
                        row_key,
                        self.col_mem_val_key,
                        f"[bold blue]0x{unsigned_val:0{hex_width}X} ({unsigned_val})[/bold blue]",
                    )
                else:
                    mem_table.update_cell(row_key, self.col_mem_val_key, "[bold red]Read Error[/bold red]")

            elif metadata["type"] == "stack_ptr_row":
                pointer_name = metadata["pointer"]
                ptr_val = self._resolve_stack_pointer(pointer_name)
                if ptr_val is not None:
                    stack_table.update_cell(row_key, self.col_stack_val_key, f"[bold cyan]0x{ptr_val:08X} ({ptr_val})[/bold cyan]")
                else:
                    stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Unavailable[/bold red]")

            elif metadata["type"] == "stack_mem_row":
                pointer_name = metadata["pointer"]
                offset_words = metadata["offset_words"]
                ptr_val = self._resolve_stack_pointer(pointer_name)
                if ptr_val is None:
                    stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Pointer Unavailable[/bold red]")
                else:
                    addr = ptr_val + (offset_words * 4)
                    stack_table.update_cell(row_key, self.col_stack_addr_key, hex(addr))
                    mem_val = self.jlink.read_register(addr, 32)
                    if mem_val is None:
                        stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Read Error[/bold red]")
                    else:
                        unsigned_val = mem_val & 0xFFFFFFFF
                        stack_table.update_cell(
                            row_key,
                            self.col_stack_val_key,
                            f"[bold blue]0x{unsigned_val:08X} ({unsigned_val})[/bold blue]",
                        )

            elif metadata["type"] == "fault_reg_row":
                reg_name = metadata["name"]
                addr = metadata["address"]
                reg_val = self.jlink.read_register(addr, 32)
                if reg_val is None:
                    table.update_cell(row_key, self.col_val_key, "[bold red]Read Error[/bold red]")
                    fault_values[reg_name] = None
                else:
                    unsigned_val = reg_val & 0xFFFFFFFF
                    fault_values[reg_name] = unsigned_val
                    table.update_cell(
                        row_key,
                        self.col_val_key,
                        f"[bold cyan]0x{unsigned_val:08X} ({unsigned_val})[/bold cyan]",
                    )

            elif metadata["type"] == "fault_flag_row":
                source_reg = metadata["source_reg"]
                mask = metadata["mask"]
                source_val = fault_values.get(source_reg)
                if source_val is None:
                    table.update_cell(row_key, self.col_val_key, "[bold red]Unknown[/bold red]")
                else:
                    active = (source_val & mask) != 0
                    if active:
                        table.update_cell(row_key, self.col_val_key, "[bold red]SET[/bold red]")
                    else:
                        table.update_cell(row_key, self.col_val_key, "[green]clear[/green]")

            elif metadata["type"] == "field_row" and current_reg_val is not None:
                offset = metadata["offset"]
                width = metadata["width"]
                mask = (1 << width) - 1
                field_val = (current_reg_val >> offset) & mask

                hex_f_str = f"0x{field_val:X}"
                bin_f_str = f"b{field_val:0{width}b}"
                table.update_cell(row_key, self.col_val_key, f"[bold green]{hex_f_str} ({bin_f_str})[/bold green]")

        for row_key, metadata in self.stack_rows:
            if metadata["type"] == "stack_ptr_row":
                pointer_name = metadata["pointer"]
                ptr_val = self._resolve_stack_pointer(pointer_name)
                if ptr_val is not None:
                    stack_table.update_cell(row_key, self.col_stack_val_key, f"[bold cyan]0x{ptr_val:08X} ({ptr_val})[/bold cyan]")
                else:
                    stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Unavailable[/bold red]")

            elif metadata["type"] == "stack_mem_row":
                pointer_name = metadata["pointer"]
                offset_words = metadata["offset_words"]
                ptr_val = self._resolve_stack_pointer(pointer_name)
                if ptr_val is None:
                    stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Pointer Unavailable[/bold red]")
                else:
                    addr = ptr_val + (offset_words * 4)
                    stack_table.update_cell(row_key, self.col_stack_addr_key, hex(addr))
                    mem_val = self.jlink.read_register(addr, 32)
                    if mem_val is None:
                        stack_table.update_cell(row_key, self.col_stack_val_key, "[bold red]Read Error[/bold red]")
                    else:
                        unsigned_val = mem_val & 0xFFFFFFFF
                        stack_table.update_cell(row_key, self.col_stack_val_key, f"[bold blue]0x{unsigned_val:08X} ({unsigned_val})[/bold blue]")

        for row_key, metadata in self.memory_rows:
            if metadata["type"] != "memory_row":
                continue
            addr = metadata["address"]
            size = metadata["size"]
            val = self.jlink.read_register(addr, size)
            if val is not None:
                bits = max(1, int(size))
                mask = (1 << bits) - 1
                unsigned_val = val & mask
                hex_width = max(2, (bits + 3) // 4)
                mem_table.update_cell(
                    row_key,
                    self.col_mem_val_key,
                    f"[bold blue]0x{unsigned_val:0{hex_width}X} ({unsigned_val})[/bold blue]",
                )
            else:
                mem_table.update_cell(row_key, self.col_mem_val_key, "[bold red]Read Error[/bold red]")


def build_argument_parser() -> argparse.ArgumentParser:
    parser = argparse.ArgumentParser(
        description=(
            "Textual SVD + J-Link register viewer for embedded targets. "
            "Interactive mode is always available; CLI options preconfigure startup behavior."
        )
    )
    parser.add_argument("--svd", default="", help="Path to a CMSIS-SVD XML file")
    parser.add_argument("--core-svd", default="", help="Optional path to a Cortex-M core SVD XML file")
    parser.add_argument("--elf", default="", help="Optional path to an ELF file for future symbol features")
    parser.add_argument("--chip", default="STM32H753ZI", help="Target device name passed to J-Link")
    parser.add_argument(
        "-usb",
        "--usb",
        default="",
        help="Force direct USB connection using J-Link serial number (decimal or 0xHEX)",
    )
    parser.add_argument(
        "--remote-host",
        default="127.0.0.1",
        help="J-Link Remote Server host (default: 127.0.0.1)",
    )
    parser.add_argument(
        "--remote-port",
        type=int,
        default=19020,
        help="J-Link Remote Server TCP port (default: 19020)",
    )
    parser.add_argument(
        "--interface",
        choices=["SWD", "JTAG", "swd", "jtag"],
        default="SWD",
        help="Probe transport interface",
    )
    parser.add_argument(
        "--auto-load",
        action="store_true",
        help="Automatically parse --svd at startup",
    )
    parser.add_argument(
        "--auto-connect",
        action="store_true",
        help="Automatically connect to the probe at startup",
    )
    parser.add_argument(
        "--rtt-continuous",
        "--rtt-auto-start",
        dest="rtt_continuous",
        action="store_true",
        help="Automatically start continuous RTT capture after connecting",
    )
    parser.add_argument(
        "--poll-interval",
        type=float,
        default=0.5,
        help="Register polling interval in seconds (default: 0.5)",
    )
    return parser


def parse_args(argv: Optional[List[str]] = None) -> argparse.Namespace:
    parser = build_argument_parser()
    args = parser.parse_args(argv)

    if args.poll_interval <= 0:
        parser.error("--poll-interval must be greater than 0")

    if args.remote_port <= 0 or args.remote_port > 65535:
        parser.error("--remote-port must be in the range 1..65535")

    if args.usb:
        try:
            int(args.usb, 0)
        except ValueError:
            parser.error("--usb must be a decimal or 0x-prefixed integer serial number")

    args.interface = args.interface.upper()

    if args.auto_load and not args.svd:
        parser.error("--auto-load requires --svd")

    if args.svd and not os.path.isfile(args.svd):
        parser.error(f"SVD file does not exist: {args.svd}")

    if args.core_svd and not os.path.isfile(args.core_svd):
        parser.error(f"Core SVD file does not exist: {args.core_svd}")

    if args.elf and not os.path.isfile(args.elf):
        parser.error(f"ELF file does not exist: {args.elf}")

    return args


def main(argv: Optional[List[str]] = None) -> int:
    args = parse_args(argv)

    if textual_import_error is not None:
        print(
            f"Error: textual is required to run the TUI ({textual_import_error}).",
            file=sys.stderr,
        )
        return 2

    app = SVDDebuggerApp(
        svd_path=args.svd,
        core_svd_path=args.core_svd,
        elf_path=args.elf,
        chip_name=args.chip,
        interface=args.interface,
        usb_serial=args.usb,
        remote_host=args.remote_host,
        remote_port=args.remote_port,
        auto_load_svd=args.auto_load,
        auto_connect=args.auto_connect,
        auto_rtt_capture=args.rtt_continuous,
        poll_interval_s=args.poll_interval,
    )
    app.run()
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
