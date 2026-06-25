import argparse
import pylink
import sys
import time

def main():
    parser = argparse.ArgumentParser(description="Set a breakpoint on a target, run, and dump memory upon hitting.")
    parser.add_argument("--pc", required=True, help="Breakpoint PC address in hex (e.g. 0x08007420)")
    parser.add_argument("--address", required=True, help="Address to dump memory from when breakpoint is hit (e.g. 0x2400a434)")
    parser.add_argument("--words", type=int, default=128, help="Number of words to read from --address (default: 128)")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--timeout", type=float, default=5.0, help="Breakpoint wait timeout in seconds (default: 5.0)")
    args = parser.parse_args()

    try:
        bp_addr = int(args.pc, 16)
    except ValueError:
        print(f"Error: Invalid breakpoint address '{args.pc}'.", file=sys.stderr)
        return 1

    try:
        dump_addr = int(args.address, 16)
    except ValueError:
        print(f"Error: Invalid dump address '{args.address}'.", file=sys.stderr)
        return 1

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        
        print("Connected. Halting target...")
        jlink.halt()
        
        print(f"Setting breakpoint at 0x{bp_addr:08x}...")
        bp_handle = jlink.breakpoint_set(bp_addr)
        
        print("Resetting and running target...")
        jlink.reset()
        jlink.restart()
        
        # Wait up to timeout seconds for breakpoint hit
        start_time = time.time()
        hit = False
        while time.time() - start_time < args.timeout:
            if jlink.halted():
                pc = jlink.register_read(15) # PC
                if pc == bp_addr:
                    print(f"Breakpoint hit at PC: 0x{pc:08x}!")
                    hit = True
                    break
            time.sleep(0.1)
            
        if not hit:
            print(f"Failed to hit breakpoint within {args.timeout}s. Current PC: {hex(jlink.register_read(15))}")
            jlink.breakpoint_clear(bp_handle)
            return 1
            
        print(f"--- Memory Dump at Breakpoint: Address 0x{dump_addr:08x} ({args.words} words) ---")
        words = jlink.memory_read32(dump_addr, args.words)
        
        zero_run = 0
        for i, val in enumerate(words):
            curr_addr = dump_addr + i*4
            if val != 0:
                if zero_run > 0:
                    print(f"[0x{curr_addr - zero_run*4:08x} - 0x{curr_addr - 4:08x}]: ALL ZERO ({zero_run} words)")
                    zero_run = 0
                print(f"[0x{curr_addr:08x}]: 0x{val:08x}")
            else:
                zero_run += 1
        if zero_run > 0:
            print(f"[0x{dump_addr + len(words)*4 - zero_run*4:08x} - 0x{dump_addr + len(words)*4 - 4:08x}]: ALL ZERO ({zero_run} words)")
            
        # Clean up breakpoint
        jlink.breakpoint_clear(bp_handle)
        
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
