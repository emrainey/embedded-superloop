"""
clock_tree.py — Read and decode the clock tree configuration for STM32
devices via J-Link. Auto-detects the MCU family from the device name.
"""

import argparse
import os
import sys

import pylink

import svd_query

_SCRIPT_DIR = os.path.dirname(os.path.abspath(__file__))
DEFAULT_SVD_H7 = os.path.normpath(
    os.path.join(_SCRIPT_DIR, "../../modules/stm32/scripts/STM32H753.svd")
)
DEFAULT_SVD_F4 = os.path.normpath(
    os.path.join(_SCRIPT_DIR, "../../modules/stm32/scripts/STM32F407.svd")
)


def _detect_family(device: str) -> str:
    upper = device.upper()
    if upper.startswith("STM32H") or "H7" in upper:
        return "h7"
    if upper.startswith("STM32F4") or "F4" in upper:
        return "f4"
    if upper.startswith("STM32F3") or "F3" in upper:
        return "f4"
    return "h7"


def main() -> int:
    parser = argparse.ArgumentParser(
        description="Read and decode the STM32 clock tree via J-Link."
    )
    parser.add_argument("--device", default="STM32H753ZI",
                        help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--svd", default=None,
                        help="Path to SVD file (auto-detected from device if omitted)")
    parser.add_argument("--speed", type=int, default=4000,
                        help="J-Link speed in kHz (default: 4000)")
    args = parser.parse_args()

    family = _detect_family(args.device)

    if args.svd:
        svd_path = args.svd
    elif family == "h7":
        svd_path = DEFAULT_SVD_H7
    else:
        svd_path = DEFAULT_SVD_F4

    if not os.path.isfile(svd_path):
        print(f"Error: SVD not found: {svd_path}", file=sys.stderr)
        return 1

    svd_peripherals = svd_query._parse_all_peripherals(svd_path)
    if "RCC" not in svd_peripherals:
        print("Error: no RCC peripheral found in SVD", file=sys.stderr)
        return 1

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        print(f"Connected to {args.device}.\n")

        if not jlink.halted():
            jlink.halt()

        if family == "h7":
            from clock_tree_stm32h7 import dump_clock_tree
        else:
            from clock_tree_stm32f4 import dump_clock_tree

        output = dump_clock_tree(jlink, svd_peripherals)
        print(output)

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        import traceback as tb
        tb.print_exc()
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
