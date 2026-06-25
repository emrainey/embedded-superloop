import argparse
import pylink
import sys

def main():
    parser = argparse.ArgumentParser(description="Dump a range of memory from a target device.")
    parser.add_argument("--address", required=True, help="Start address (in hex, e.g. 0x2400a434)")
    parser.add_argument("--words", type=int, default=256, help="Number of 32-bit words to read (default: 256)")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--show-zeros", action="store_true", help="Print all zero words instead of suppressing them")
    args = parser.parse_args()

    try:
        addr = int(args.address, 16)
    except ValueError:
        print(f"Error: Invalid start address '{args.address}'. Must be a hexadecimal number (e.g. 0x24000000).", file=sys.stderr)
        return 1

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        
        if not jlink.halted():
            jlink.halt()
            
        print(f"--- Memory Dump from 0x{addr:08x} ({args.words} words) ---")
        words = jlink.memory_read32(addr, args.words)
        
        zero_run = 0
        for i, val in enumerate(words):
            curr_addr = addr + i*4
            if val != 0 or args.show_zeros:
                if zero_run > 0:
                    print(f"[0x{curr_addr - zero_run*4:08x} - 0x{curr_addr - 4:08x}]: ALL ZERO ({zero_run} words)")
                    zero_run = 0
                print(f"[0x{curr_addr:08x}]: 0x{val:08x}")
            else:
                zero_run += 1
        if zero_run > 0:
            print(f"[0x{addr + len(words)*4 - zero_run*4:08x} - 0x{addr + len(words)*4 - 4:08x}]: ALL ZERO ({zero_run} words)")
            
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
