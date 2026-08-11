"""
live_dump.py — Read and decode all registers of any peripheral via J-Link,
using the SVD for field-level decoding.

Usage:
    python live_dump.py --peripheral GPIOA --svd modules/stm32/scripts/STM32H753.svd
"""

import argparse
import os
import shutil
import subprocess
import sys
import time

from jlink_connection import add_connection_args, connect

_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DEFAULT_SVD = os.path.normpath(
    os.path.join(_SCRIPT_DIR, "../../modules/stm32/scripts/STM32H753.svd")
)

import svd_query


def _decode_register(value: int, fields: dict) -> list[tuple[str, int, str]]:
    decoded = []
    for fname, meta in fields.items():
        lsb = meta["lsb"]
        width = meta["width"]
        mask = (1 << width) - 1
        fval = (value >> lsb) & mask
        if fval != 0 or width == 1:
            decoded.append((fname, fval, meta["description"]))
    decoded.sort(key=lambda x: -fields[x[0]]["lsb"])
    return decoded


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Read and decode all registers of a peripheral via J-Link."
    )
    parser.add_argument("--peripheral", required=True, help="Peripheral name (e.g. GPIOA, USART1)")
    parser.add_argument("--svd", default=DEFAULT_SVD, help="Path to SVD file")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz")
    parser.add_argument("--elf", default=None, help="ELF for --run-to-main")
    parser.add_argument("--run-to-main", action="store_true",
                        help="Reset and run to main before reading")
    parser.add_argument("--breakpoint-symbol", default="_ZN6cortex6system4mainEv",
                        help="Mangled symbol to break at")
    parser.add_argument("--nm", default=None, help="Path to arm-none-eabi-nm")
    parser.add_argument("--timeout", type=float, default=10.0,
                        help="Timeout in seconds for --run-to-main")
    parser.add_argument("--all-fields", action="store_true",
                        help="Show zero-valued fields too")
    add_connection_args(parser)
    args = parser.parse_args()

    # --- Parse SVD ---
    if not os.path.isfile(args.svd):
        print(f"Error: SVD not found: {args.svd}", file=sys.stderr)
        return 1

    peripherals = svd_query._parse_all_peripherals(args.svd)
    pinfo = peripherals.get(args.peripheral)
    if not pinfo:
        candidates = [n for n in sorted(peripherals.keys())
                      if args.peripheral.upper() in n.upper()]
        msg = f"Peripheral '{args.peripheral}' not found in {args.svd}"
        if candidates:
            msg += f"\n  Did you mean one of: {', '.join(candidates[:10])}"
        print(msg, file=sys.stderr)
        return 1

    base = pinfo["base"]
    regs = pinfo["registers"]
    if not regs:
        print(f"Peripheral '{args.peripheral}' has no registers defined in SVD.")
        return 1

    print(f"Parsed SVD: {args.svd}")
    print(f"Peripheral: {args.peripheral}  (base = 0x{base:08X}, {len(regs)} registers)\n")

    # --- Connect ---
    try:
        jlink = connect(args.device, args.speed, args.remote_host, args.remote_port)
        print(f"Connected to {args.device}.\n")

        if not jlink.halted():
            jlink.halt()

        # --- Run to main if requested ---
        if args.run_to_main:
            nm_tool = args.nm or shutil.which("arm-none-eabi-nm")
            if not nm_tool:
                print("Error: arm-none-eabi-nm not found.", file=sys.stderr)
                return 1
            if not args.elf or not os.path.isfile(args.elf):
                print(f"Error: ELF not found: {args.elf}", file=sys.stderr)
                return 1
            result = subprocess.run(
                [nm_tool, "--defined-only", args.elf],
                capture_output=True, text=True, check=False,
            )
            addr = None
            for line in result.stdout.splitlines():
                parts = line.split()
                if len(parts) == 3 and parts[2] == args.breakpoint_symbol:
                    addr = int(parts[0], 16)
                    break
            if addr is None:
                print(f"Error: symbol '{args.breakpoint_symbol}' not found in ELF",
                      file=sys.stderr)
                return 1
            bp_addr = addr & ~1
            print(f"  Running to {args.breakpoint_symbol} => 0x{bp_addr:08x} ...")
            jlink.halt()
            bp = jlink.breakpoint_set(bp_addr, thumb=True)
            jlink.reset()
            jlink.restart()
            start = time.time()
            hit = False
            while time.time() - start < args.timeout:
                if jlink.halted():
                    pc = jlink.register_read(15)
                    if (pc & ~1) == bp_addr:
                        print("  Breakpoint hit!\n")
                        hit = True
                        break
                    else:
                        print(f"  Unexpected halt at 0x{pc:08x}", file=sys.stderr)
                        break
                time.sleep(0.05)
            jlink.breakpoint_clear(bp)
            if not hit:
                print(f"  Timeout: not reached within {args.timeout}s", file=sys.stderr)
                return 1

        # --- Read and decode ---
        sorted_regs = sorted(regs.items(), key=lambda x: x[1]["offset"])
        for rname, rmeta in sorted_regs:
            addr = base + rmeta["offset"]
            try:
                value = jlink.memory_read32(addr, 1)[0]
            except Exception as e:
                print(f"  {rname:35s} @ 0x{addr:08X}  [READ ERROR: {e}]")
                continue

            reset_marker = ""
            if value != rmeta["reset"] and rmeta["reset"] != 0:
                reset_marker = f"  (reset=0x{rmeta['reset']:08X})"

            print(f"  {rname:35s} @ 0x{addr:08X} = 0x{value:08X}{reset_marker}")
            if rmeta["description"]:
                print(f"    // {rmeta['description']}")

            if rmeta["fields"]:
                if args.all_fields:
                    decoded = [
                        (fn, ((value >> fm["lsb"]) & ((1 << fm["width"]) - 1)),
                         fm["description"])
                        for fn, fm in rmeta["fields"].items()
                    ]
                    decoded.sort(key=lambda x: -rmeta["fields"][x[0]]["lsb"])
                else:
                    decoded = _decode_register(value, rmeta["fields"])

                for fname, fval, fdesc in decoded:
                    width = rmeta["fields"][fname]["width"]
                    lsb = rmeta["fields"][fname]["lsb"]
                    if width == 1:
                        indicator = "[X]" if fval else "[ ]"
                        print(f"      {indicator} [{lsb}]    {fname}: {fdesc}")
                    else:
                        print(f"      [{lsb}+{width-1}:{lsb}] {fname} = {fval:#x}  {fdesc}")

        print("\nDone.")

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        import traceback as tb
        tb.print_exc()
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
