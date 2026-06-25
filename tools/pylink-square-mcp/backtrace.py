import argparse
import pylink
import sys
import subprocess
import shutil

def find_addr2line():
    for tool in ["arm-none-eabi-addr2line", "llvm-addr2line", "addr2line"]:
        resolved = shutil.which(tool)
        if resolved:
            return resolved
    return None

def resolve_address(addr2line_tool, elf_path, addr):
    cmd = [addr2line_tool, "-e", elf_path, "-f", "-C", f"0x{addr:x}"]
    result = subprocess.run(cmd, capture_output=True, text=True, check=False)
    if result.returncode == 0:
        lines = [line.strip() for line in result.stdout.splitlines() if line.strip()]
        if len(lines) >= 2:
            return f"{lines[0]} @ {lines[1]}"
        elif len(lines) == 1:
            return lines[0]
    return "??:0"

def main():
    parser = argparse.ArgumentParser(description="Dump target stack memory and resolve code addresses.")
    parser.add_argument("--elf", required=True, help="Path to the compiled ELF file containing debug symbols")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--words", type=int, default=64, help="Number of stack words to dump (default: 64)")
    args = parser.parse_args()

    addr2line_tool = find_addr2line()
    if not addr2line_tool:
        print("Error: addr2line tool not found.", file=sys.stderr)
        return 1

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        
        if not jlink.halted():
            jlink.halt()
            
        sp = jlink.register_read(13) # SP
        print(f"Current SP: 0x{sp:08x}")
        
        # Read words from stack
        words = jlink.memory_read32(sp, args.words)
        
        print("\n--- Stack Dump & Symbol Resolution ---")
        for i, val in enumerate(words):
            addr = sp + i * 4
            symbol_info = ""
            # If the value looks like a flash code address
            if 0x08000000 <= val <= 0x08200000:
                symbol_info = f" -> {resolve_address(addr2line_tool, args.elf, val)}"
            print(f"[SP + 0x{i*4:02x}] (0x{addr:08x}): 0x{val:08x}{symbol_info}")
            
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
