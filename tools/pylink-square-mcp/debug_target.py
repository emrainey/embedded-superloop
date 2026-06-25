import argparse
import pylink
import sys

def main():
    parser = argparse.ArgumentParser(description="Query Cortex-M target register and exception status via J-Link.")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    args = parser.parse_args()

    try:
        jlink = pylink.JLink()
        # Open connection to the J-Link
        jlink.open()
        
        # Connect to the target
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)
        
        print(f"Successfully connected to {args.device} target.")
        print(f"Target CPU ID: {hex(jlink.core_id())}")
        
        # Halt the CPU to read registers reliably
        if jlink.halted():
            print("CPU is already halted.")
        else:
            print("Halting CPU...")
            jlink.halt()
            
        print(f"Is CPU halted? {jlink.halted()}")
        
        # Read core registers
        print("\n--- Core Registers ---")
        regs = [
            "R0", "R1", "R2", "R3", "R4", "R5", "R6", "R7",
            "R8", "R9", "R10", "R11", "R12", "SP", "LR", "PC", "xPSR"
        ]
        for i, name in enumerate(regs):
            val = jlink.register_read(i)
            print(f"{name:4}: 0x{val:08x}")
            
        # Read SCB registers
        # CFSR is at 0xE000ED28
        # HFSR is at 0xE000ED2C
        # MMFAR is at 0xE000ED34
        # BFAR is at 0xE000ED38
        
        cfsr = jlink.memory_read32(0xE000ED28, 1)[0]
        hfsr = jlink.memory_read32(0xE000ED2C, 1)[0]
        mmfar = jlink.memory_read32(0xE000ED34, 1)[0]
        bfar = jlink.memory_read32(0xE000ED38, 1)[0]
        
        print("\n--- Fault Registers ---")
        print(f"CFSR  (Configurable Fault Status): 0x{cfsr:08x}")
        print(f"HFSR  (HardFault Status):         0x{hfsr:08x}")
        print(f"MMFAR (MemManage Fault Address):  0x{mmfar:08x}")
        print(f"BFAR  (BusFault Address):       0x{bfar:08x}")
        
        # Decode CFSR
        ufsr = (cfsr >> 16) & 0xFFFF
        bfsr = (cfsr >> 8) & 0xFF
        mmfsr = cfsr & 0xFF
        
        print("\n--- UsageFault Decode ---")
        if ufsr & (1 << 9): # DIVBYZERO
            print("  [X] DIVBYZERO: Divide by zero fault occurred")
        if ufsr & (1 << 8): # UNALIGNED
            print("  [X] UNALIGNED: Unaligned access fault occurred")
        if ufsr & (1 << 3): # NOCP
            print("  [X] NOCP: Coprocessor access fault occurred (tried to access FPU without enabling it?)")
        if ufsr & (1 << 2): # INVPC
            print("  [X] INVPC: Invalid PC load fault occurred")
        if ufsr & (1 << 1): # INVSTATE
            print("  [X] INVSTATE: Invalid state fault occurred (e.g. EPSR.T Thumb state cleared)")
        if ufsr & (1 << 0): # UNDEFINSTR
            print("  [X] UNDEFINSTR: Undefined instruction fault occurred")
        if ufsr == 0:
            print("  No UsageFault active in CFSR.")
            
        print("\n--- BusFault Decode ---")
        if bfsr & (1 << 7):
            print("  [X] BFARVALID: BFAR register contains a valid fault address")
        if bfsr & (1 << 5):
            print("  [X] LSPERR: Lazy state preservation error occurred")
        if bfsr & (1 << 4):
            print("  [X] STKERR: Stack error occurred")
        if bfsr & (1 << 3):
            print("  [X] UNSTKERR: Unstack error occurred")
        if bfsr & (1 << 2):
            print("  [X] IMPREISERR: Imprecise data bus error occurred")
        if bfsr & (1 << 1):
            print("  [X] PRECISERR: Precise data bus error occurred")
        if bfsr & (1 << 0):
            print("  [X] IBUSERR: Instruction bus error occurred")
            
    except Exception as e:
        print(f"Error during J-Link operations: {e}", file=sys.stderr)
        return 1
    return 0

if __name__ == '__main__':
    sys.exit(main())
