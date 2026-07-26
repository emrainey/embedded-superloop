import argparse
import pylink
import sys


def main():
    parser = argparse.ArgumentParser(description="Single-step target instructions via J-Link.")
    parser.add_argument("--count", type=int, default=1, help="Number of instructions to step (default: 1)")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    args = parser.parse_args()

    if args.count < 1:
        print("Error: --count must be at least 1.", file=sys.stderr)
        return 1

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        print(f"Connected to {args.device}.")

        if not jlink.halted():
            print("Target is running. Halting...")
            jlink.halt()
        else:
            print("Target is halted.")

        pc_initial = jlink.register_read(15)
        print(f"\nStepping {args.count} instruction(s) from PC=0x{pc_initial:08x}:\n")

        for i in range(args.count):
            pc_before = jlink.register_read(15)
            jlink.step()
            pc_after = jlink.register_read(15)
            print(f"  [{i+1}] 0x{pc_before:08x} -> 0x{pc_after:08x}")

        pc = jlink.register_read(15)
        sp = jlink.register_read(13)
        lr = jlink.register_read(14)
        xpsr = jlink.register_read(16)
        print(f"\nFinal PC: 0x{pc:08x}, SP: 0x{sp:08x}, LR: 0x{lr:08x}, xPSR: 0x{xpsr:08x}")

        return 0
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
