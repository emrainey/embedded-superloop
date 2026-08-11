import argparse
import shutil
import subprocess
import sys
import time

from jlink_connection import add_connection_args, connect


TOOLCHAIN_PATHS = [
    "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-nm",
    "/usr/bin/arm-none-eabi-nm",
    "/usr/local/bin/arm-none-eabi-nm",
]

DEFAULT_SYMBOL = "_ZN6cortex6system4mainEv"  # cortex::system::main


def find_nm():
    for path in TOOLCHAIN_PATHS:
        import os
        if os.path.isfile(path):
            return path
    return shutil.which("arm-none-eabi-nm")


def resolve_symbol_address(nm_tool, elf_path, symbol):
    """Use nm to find the address of a specific mangled symbol in the ELF."""
    result = subprocess.run(
        [nm_tool, "--defined-only", elf_path],
        capture_output=True, text=True, check=False
    )
    if result.returncode != 0:
        print(f"Error running nm: {result.stderr.strip()}", file=sys.stderr)
        return None

    for line in result.stdout.splitlines():
        parts = line.split()
        # nm output: [address] [type] [name]
        if len(parts) == 3 and parts[2] == symbol:
            try:
                return int(parts[0], 16)
            except ValueError:
                return None
    return None


def demangle_symbol(nm_tool, elf_path, symbol):
    """Return demangled name using c++filt if available, else return mangled name."""
    cppfilt = shutil.which("arm-none-eabi-c++filt") or shutil.which("c++filt")
    if not cppfilt:
        return symbol
    result = subprocess.run([cppfilt, symbol], capture_output=True, text=True, check=False)
    return result.stdout.strip() if result.returncode == 0 else symbol


def main():
    parser = argparse.ArgumentParser(
        description="Reset target and run to a symbol via J-Link hardware breakpoint."
    )
    parser.add_argument("--elf", required=True, help="Path to the compiled ELF file containing debug symbols")
    parser.add_argument("--symbol", default=DEFAULT_SYMBOL,
                        help=f"Mangled symbol to break at (default: {DEFAULT_SYMBOL} = cortex::system::main)")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--timeout", type=float, default=10.0, help="Timeout in seconds to wait for breakpoint (default: 10.0)")
    parser.add_argument("--nm", default=None, help="Path to arm-none-eabi-nm (auto-detected if not provided)")
    add_connection_args(parser)
    args = parser.parse_args()

    nm_tool = args.nm or find_nm()
    if not nm_tool:
        print(
            "Error: arm-none-eabi-nm not found. "
            "Install the ARM toolchain or pass --nm /path/to/arm-none-eabi-nm",
            file=sys.stderr
        )
        return 1

    print(f"Using nm: {nm_tool}")
    print(f"Resolving symbol '{args.symbol}' from {args.elf} ...")

    addr = resolve_symbol_address(nm_tool, args.elf, args.symbol)
    if addr is None:
        print(f"Error: symbol '{args.symbol}' not found in {args.elf}", file=sys.stderr)
        return 1

    demangled = demangle_symbol(nm_tool, args.elf, args.symbol)
    print(f"Found: {demangled}  =>  0x{addr:08x}")

    # Cortex-M Thumb addresses have LSB set in the symbol table but the
    # actual instruction address used for breakpoints must have LSB cleared.
    bp_addr = addr & ~1

    try:
        jlink = connect(args.device, args.speed, args.remote_host, args.remote_port)
        print(f"Connected to {args.device}.")

        print("Halting target...")
        jlink.halt()

        print(f"Setting breakpoint at 0x{bp_addr:08x} ...")
        bp_handle = jlink.breakpoint_set(bp_addr, thumb=True)

        print("Resetting and running target...")
        jlink.reset()
        jlink.restart()

        # Poll for halt (breakpoint hit)
        start = time.time()
        hit = False
        while time.time() - start < args.timeout:
            if jlink.halted():
                pc = jlink.register_read(15)  # PC
                if (pc & ~1) == bp_addr:
                    print(f"\nBreakpoint hit! PC = 0x{pc:08x}")
                    hit = True
                    break
                else:
                    # Halted for another reason (e.g. fault) — report and stop
                    print(f"\nTarget halted unexpectedly at PC = 0x{pc:08x} (not our breakpoint)")
                    break
            time.sleep(0.05)

        if not hit:
            print(f"\nTimeout: breakpoint not hit within {args.timeout}s.")
            pc = jlink.register_read(15)
            print(f"Current PC: 0x{pc:08x}")
            jlink.breakpoint_clear(bp_handle)
            return 1

        # Dump all core registers
        reg_names = [
            "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7",
            "R8", "R9", "R10", "R11", "R12", "SP", "LR", "PC", "xPSR"
        ]
        print("\n--- Core Registers ---")
        for i, name in enumerate(reg_names):
            val = jlink.register_read(i)
            print(f"  {name:4s}: 0x{val:08x}")

        jlink.breakpoint_clear(bp_handle)
        print(f"\nTarget is halted at {demangled} and ready for inspection.")

    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1

    return 0


if __name__ == "__main__":
    sys.exit(main())
