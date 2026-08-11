"""
dump_ethernet.py — Read and decode all STM32H7 Ethernet peripheral registers via
J-Link, using the on-board SVD for field-level decoding.

Optionally runs to cortex::system::main first (--run-to-main) so the peripheral
has been clocked and partially initialised by the board startup code.
"""

import argparse
import os
import shutil
import subprocess
import sys
import time
import xml.etree.ElementTree as ET

from jlink_connection import add_connection_args, connect

# ---------------------------------------------------------------------------
# Paths
# ---------------------------------------------------------------------------
_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DEFAULT_SVD = os.path.normpath(
    os.path.join(_SCRIPT_DIR, "../../modules/stm32/scripts/STM32H753.svd")
)
DEFAULT_ELF = os.path.normpath(
    os.path.join(
        _SCRIPT_DIR,
        "../../build/cortex-m7-gcc-arm-none-eabi/applications/nucleo-demo"
        "/firmware-nucleo-demo-basic-nucleo_h753zi.elf",
    )
)
TOOLCHAIN_NM_CANDIDATES = [
    "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-nm",
    "/usr/bin/arm-none-eabi-nm",
    "/usr/local/bin/arm-none-eabi-nm",
]
TARGET_SYMBOL = "_ZN6cortex6system4mainEv"  # cortex::system::main — default breakpoint

# STM32H7 Ethernet block names inside the SVD
ETH_PERIPHERAL_NAMES = ["Ethernet_MAC", "Ethernet_MTL", "Ethernet_DMA"]

# Registers worth calling out explicitly in a summary section
HIGHLIGHT_REGISTERS = {
    "Ethernet_MAC": ["MACCR", "MACPFR", "MACIER", "MACPCSR", "MACRWFFR"],
    "Ethernet_MTL": ["MTLOMR", "MTLISR", "MTLTxQOMR", "MTLRxQOMR"],
    "Ethernet_DMA": ["DMAMR", "DMASBMR", "DMAISR", "DMADSR", "DMACCR",
                     "DMACTxCR", "DMACRxCR"],
}

# ---------------------------------------------------------------------------
# SVD parsing
# ---------------------------------------------------------------------------

def _parse_int(text: str, default: int = 0) -> int:
    """Parse a decimal or 0x-prefixed hex integer from SVD text."""
    if not text:
        return default
    text = text.strip().replace(" ", "")
    try:
        return int(text, 0)
    except ValueError:
        return default


def parse_svd_peripherals(svd_path: str) -> dict:
    """
    Returns a dict keyed by peripheral name:
        {
          'base': int,
          'registers': {
              reg_name: {
                  'offset': int,
                  'reset': int,
                  'description': str,
                  'fields': {
                      field_name: {'lsb': int, 'width': int, 'description': str}
                  }
              }
          }
        }
    Only the peripherals listed in ETH_PERIPHERAL_NAMES are parsed.
    """
    tree = ET.parse(svd_path)
    root = tree.getroot()
    result = {}

    for p in root.iter("peripheral"):
        name = p.findtext("name", "").strip()
        if name not in ETH_PERIPHERAL_NAMES:
            continue

        base = _parse_int(p.findtext("baseAddress", "0"))
        registers = {}

        for reg in p.iter("register"):
            rname = reg.findtext("name", "").strip()
            offset = _parse_int(reg.findtext("addressOffset", "0"))
            reset = _parse_int(reg.findtext("resetValue", "0"))
            desc = (reg.findtext("description") or "").strip()

            fields = {}
            for field in reg.iter("field"):
                fname = field.findtext("name", "").strip()
                lsb = _parse_int(field.findtext("bitOffset", "0"))
                width = _parse_int(field.findtext("bitWidth", "1"))
                fdesc = (field.findtext("description") or "").strip()
                fields[fname] = {"lsb": lsb, "width": width, "description": fdesc}

            registers[rname] = {
                "offset": offset,
                "reset": reset,
                "description": desc,
                "fields": fields,
            }

        result[name] = {"base": base, "registers": registers}

    return result


def decode_register(value: int, fields: dict) -> list[tuple[str, int, str]]:
    """
    Return list of (field_name, field_value, description) sorted by LSB descending.
    Only non-zero fields (or single-bit fields) are returned so the output stays
    concise; reserved/zero fields are skipped.
    """
    decoded = []
    for fname, meta in fields.items():
        lsb = meta["lsb"]
        width = meta["width"]
        mask = (1 << width) - 1
        fval = (value >> lsb) & mask
        if fval != 0 or width == 1:  # always show 1-bit flags
            decoded.append((fname, fval, meta["description"]))
    decoded.sort(key=lambda x: -fields[x[0]]["lsb"])
    return decoded


# ---------------------------------------------------------------------------
# Symbol resolution (for --run-to-main)
# ---------------------------------------------------------------------------

def _find_nm() -> str | None:
    for path in TOOLCHAIN_NM_CANDIDATES:
        if os.path.isfile(path):
            return path
    return shutil.which("arm-none-eabi-nm")


def _resolve_symbol(nm_tool: str, elf: str, symbol: str) -> int | None:
    result = subprocess.run(
        [nm_tool, "--defined-only", elf],
        capture_output=True, text=True, check=False,
    )
    for line in result.stdout.splitlines():
        parts = line.split()
        if len(parts) == 3 and parts[2] == symbol:
            try:
                return int(parts[0], 16)
            except ValueError:
                return None
    return None


def run_to_main(jlink, elf: str, nm_tool: str, timeout: float,
                symbol: str = TARGET_SYMBOL) -> bool:
    """
    Resolve the given symbol from the ELF, set a breakpoint, reset and run.
    Returns True if the breakpoint was hit within timeout.
    """
    addr = _resolve_symbol(nm_tool, elf, symbol)
    if addr is None:
        print(f"Error: symbol '{symbol}' not found in {elf}", file=sys.stderr)
        return False

    bp_addr = addr & ~1  # clear Thumb LSB for the hardware breakpoint address
    print(f"  {symbol}  =>  0x{bp_addr:08x}")
    print("  Setting breakpoint, resetting and running...")
    jlink.halt()
    bp = jlink.breakpoint_set(bp_addr, thumb=True)
    jlink.reset()
    jlink.restart()

    start = time.time()
    while time.time() - start < timeout:
        if jlink.halted():
            pc = jlink.register_read(15)
            if (pc & ~1) == bp_addr:
                print(f"  Breakpoint hit!  PC = 0x{pc:08x}\n")
                jlink.breakpoint_clear(bp)
                return True
            else:
                print(
                    f"  Target halted unexpectedly at PC = 0x{pc:08x} "
                    "(fault before main?)",
                    file=sys.stderr,
                )
                jlink.breakpoint_clear(bp)
                return False
        time.sleep(0.05)

    print(f"  Timeout: main not reached within {timeout}s", file=sys.stderr)
    jlink.breakpoint_clear(bp)
    return False


# ---------------------------------------------------------------------------
# Main
# ---------------------------------------------------------------------------

def main() -> int:
    parser = argparse.ArgumentParser(
        description="Dump and decode STM32H7 Ethernet peripheral registers via J-Link."
    )
    parser.add_argument("--svd", default=DEFAULT_SVD, help="Path to STM32H753.svd")
    parser.add_argument("--elf", default=DEFAULT_ELF,
                        help="ELF with debug symbols (required for --run-to-main)")
    parser.add_argument("--run-to-main", action="store_true",
                        help="Reset and run to the breakpoint symbol before reading")
    parser.add_argument("--breakpoint-symbol", default=TARGET_SYMBOL,
                        help="Mangled symbol to break at before reading registers "
                             f"(default: {TARGET_SYMBOL} = cortex::system::main). "
                             "Example for Demo::Execute: _ZN4Demo7ExecuteEv")
    parser.add_argument("--nm", default=None,
                        help="Path to arm-none-eabi-nm (auto-detected if omitted)")
    parser.add_argument("--device", default="STM32H753ZI",
                        help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000,
                        help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--timeout", type=float, default=10.0,
                        help="Timeout in seconds for --run-to-main (default: 10.0)")
    parser.add_argument("--run-seconds", type=float, default=0.0,
                        help="After hitting the breakpoint, release the target and run "
                             "for this many seconds before halting to read registers. "
                             "Useful to let PHY auto-negotiate and capture incoming frames.")
    parser.add_argument("--all-fields", action="store_true",
                        help="Print all fields including zero-valued ones")
    add_connection_args(parser)
    args = parser.parse_args()

    # --- Parse SVD --------------------------------------------------------
    if not os.path.isfile(args.svd):
        print(f"Error: SVD not found: {args.svd}", file=sys.stderr)
        return 1

    print(f"Parsing SVD: {args.svd}")
    peripherals = parse_svd_peripherals(args.svd)
    if not peripherals:
        print("Error: no Ethernet peripherals found in SVD", file=sys.stderr)
        return 1
    print(f"  Found: {', '.join(peripherals.keys())}\n")

    # --- Connect ----------------------------------------------------------
    try:
        jlink = connect(args.device, args.speed, args.remote_host, args.remote_port)
        print(f"Connected to {args.device}.")

        # Halt if not already halted
        if not jlink.halted():
            jlink.halt()

        # --- Optionally run to main ---------------------------------------
        if args.run_to_main:
            nm_tool = args.nm or _find_nm()
            if not nm_tool:
                print(
                    "Error: arm-none-eabi-nm not found. "
                    "Pass --nm /path/to/arm-none-eabi-nm",
                    file=sys.stderr,
                )
                return 1
            if not os.path.isfile(args.elf):
                print(f"Error: ELF not found: {args.elf}", file=sys.stderr)
                return 1
            print(f"Running to symbol: {args.breakpoint_symbol} ...")
            if not run_to_main(jlink, args.elf, nm_tool, args.timeout, args.breakpoint_symbol):
                return 1

        # --- Optionally run free for N seconds ----------------------------
        if args.run_seconds > 0.0:
            print(f"Releasing target to run for {args.run_seconds:.1f}s "
                  "(PHY negotiation + frame capture)...")
            jlink.restart()
            end = time.time() + args.run_seconds
            while time.time() < end:
                remaining = end - time.time()
                print(f"  {remaining:.1f}s remaining...", end="\r", flush=True)
                time.sleep(0.25)
            print()
            jlink.halt()
            pc = jlink.register_read(15)
            print(f"Target halted.  PC = 0x{pc:08x}\n")

        # --- Read and decode registers ------------------------------------
        for pname in ETH_PERIPHERAL_NAMES:
            if pname not in peripherals:
                continue

            pinfo = peripherals[pname]
            base = pinfo["base"]
            regs = pinfo["registers"]

            print(f"\n{'=' * 60}")
            print(f"  {pname}  (base = 0x{base:08x})")
            print(f"{'=' * 60}")

            # Determine which registers to highlight
            highlights = set(HIGHLIGHT_REGISTERS.get(pname, []))
            highlight_first = [(n, r) for n, r in regs.items() if n in highlights]
            others = [(n, r) for n, r in regs.items() if n not in highlights]

            # Sort by offset
            all_regs = sorted(
                highlight_first + others, key=lambda x: x[1]["offset"]
            )

            for rname, rmeta in all_regs:
                addr = base + rmeta["offset"]
                try:
                    value = jlink.memory_read32(addr, 1)[0]
                except Exception as e:
                    print(f"  {rname:30s} @ 0x{addr:08x}  [READ ERROR: {e}]")
                    continue

                star = "*" if rname in highlights else " "
                reset_marker = ""
                if value != rmeta["reset"] and rmeta["reset"] != 0:
                    reset_marker = f"  (reset=0x{rmeta['reset']:08x})"

                print(f"\n{star} {rname:30s} @ 0x{addr:08x} = 0x{value:08x}{reset_marker}")
                if rmeta["description"]:
                    print(f"    // {rmeta['description'][:80]}")

                if rmeta["fields"]:
                    if args.all_fields:
                        decoded = [
                            (fn, ((value >> fm["lsb"]) & ((1 << fm["width"]) - 1)),
                             fm["description"])
                            for fn, fm in rmeta["fields"].items()
                        ]
                        decoded.sort(
                            key=lambda x: -rmeta["fields"][x[0]]["lsb"]
                        )
                    else:
                        decoded = decode_register(value, rmeta["fields"])

                    for fname, fval, fdesc in decoded:
                        width = rmeta["fields"][fname]["width"]
                        lsb = rmeta["fields"][fname]["lsb"]
                        if width == 1:
                            indicator = "[X]" if fval else "[ ]"
                            print(f"      {indicator} [{lsb}]    {fname}: {fdesc[:60]}")
                        else:
                            print(f"      [{lsb}+{width-1}:{lsb}] {fname} = {fval:#x}  {fdesc[:50]}")

        print(f"\n{'=' * 60}")

        # --- Receive activity summary ------------------------------------
        # Addresses derived from SVD: Ethernet_MAC @ 0x40028000
        _MAC = 0x40028000
        try:
            maccr       = jlink.memory_read32(_MAC + 0x000, 1)[0]
            dmacsr      = jlink.memory_read32(0x40029160, 1)[0]
            dmadsr      = jlink.memory_read32(0x4002900c, 1)[0]
            rx_unicast  = jlink.memory_read32(_MAC + 0x7C4, 1)[0]
            rx_crc_err  = jlink.memory_read32(_MAC + 0x794, 1)[0]
            tx_good     = jlink.memory_read32(_MAC + 0x768, 1)[0]

            fes   = (maccr >> 14) & 1
            dm    = (maccr >> 13) & 1
            tps0  = (dmadsr >> 12) & 0xF
            rps0  = (dmadsr >>  8) & 0xF
            ri    = (dmacsr >>  6) & 1
            rbu   = (dmacsr >>  7) & 1
            tbu   = (dmacsr >>  2) & 1
            nis   = (dmacsr >> 15) & 1
            ais   = (dmacsr >> 14) & 1

            TPS_NAMES = {0:"Stopped",1:"Fetching",3:"Reading",4:"Timestamp",5:"Reserved",6:"Suspended",7:"Closing"}
            RPS_NAMES = {0:"Stopped",1:"Fetching",3:"Waiting",4:"Suspended",5:"Closing",6:"Timestamp",7:"Queue flush"}

            print("\n  RECEIVE ACTIVITY SUMMARY")
            print(f"  {'MAC link':<24} {'100 Mbps' if fes else '10 Mbps'}, {'Full' if dm else 'Half'}-duplex")
            print(f"  {'DMA TX state':<24} {TPS_NAMES.get(tps0, str(tps0))} (TPS0={tps0})")
            print(f"  {'DMA RX state':<24} {RPS_NAMES.get(rps0, str(rps0))} (RPS0={rps0})")
            print(f"  {'RX unicast good':<24} {rx_unicast} frames")
            print(f"  {'RX CRC errors':<24} {rx_crc_err} frames")
            print(f"  {'TX good':<24} {tx_good} frames")
            print(f"  {'DMACSR flags':<24} RI={'1' if ri else '0'}  RBU={'1' if rbu else '0'}  TBU={'1' if tbu else '0'}  NIS={'1' if nis else '0'}  AIS={'1' if ais else '0'}")
            if rx_unicast > 0 or ri:
                print("\n  *** Frames received! Network stack is active. ***")
            elif rps0 == 4:
                print("\n  RX suspended — DMA is running but no frames have arrived yet.")
                print("  Check: cable connected? PHY link up? (FES/DM set correctly?)")
        except Exception as summary_err:
            print(f"  (summary read error: {summary_err})")

        print(f"\n{'=' * 60}")
        print("Done.")

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        import traceback
        traceback.print_exc()
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
