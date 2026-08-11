import argparse
import sys
import time

from jlink_connection import add_connection_args, connect


def main():
    parser = argparse.ArgumentParser(
        description="Run target for a set duration then halt and report state via J-Link."
    )
    parser.add_argument("--seconds", type=float, required=True, help="Seconds to let target run before halting")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--reset", action="store_true", help="Reset target before running")
    add_connection_args(parser)
    args = parser.parse_args()

    if args.seconds <= 0:
        print("Error: --seconds must be positive.", file=sys.stderr)
        return 1

    try:
        jlink = connect(args.device, args.speed, args.remote_host, args.remote_port)
        print(f"Connected to {args.device}.")

        if args.reset:
            print("Resetting target...")
            jlink.reset()
            jlink.restart()
        else:
            if jlink.halted():
                print("Target is halted. Restarting execution...")
                jlink.restart()
            else:
                print("Target is already running.")

        print(f"Running for {args.seconds}s ...")
        time.sleep(args.seconds)

        print("Halting target...")
        jlink.halt()

        pc = jlink.register_read(15)
        sp = jlink.register_read(13)
        lr = jlink.register_read(14)
        xpsr = jlink.register_read(16)

        print(f"\n--- Target State After {args.seconds}s Run ---")
        print(f"  PC  : 0x{pc:08x}")
        print(f"  SP  : 0x{sp:08x}")
        print(f"  LR  : 0x{lr:08x}")
        print(f"  xPSR: 0x{xpsr:08x}")

        if xpsr & 0xFF:
            ipsr = xpsr & 0xFF
            names = {0: "Thread", 3: "HardFault", 6: "UsageFault",
                     11: "SVCall", 12: "DebugMonitor", 14: "PendSV", 15: "SysTick"}
            exc_name = names.get(ipsr, f"IRQ{ipsr - 16}")
            print(f"  Exception: {exc_name} (IPSR={ipsr})")
        else:
            print(f"  Exception: Thread mode")

        return 0
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1


if __name__ == "__main__":
    sys.exit(main())
