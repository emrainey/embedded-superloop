import argparse
import sys
import os
import shutil
import subprocess

from jlink_connection import add_connection_args, connect


OBJCOPY_PATHS = [
    "/Applications/ArmGNUToolchain/15.2.rel1/arm-none-eabi/bin/arm-none-eabi-objcopy",
    "/Applications/ArmGNUToolchain/14.2.rel1/arm-none-eabi/bin/arm-none-eabi-objcopy",
    "/Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-objcopy",
    "/Applications/ArmGNUToolchain/12.3.rel1/arm-none-eabi/bin/arm-none-eabi-objcopy",
    "/Applications/ARM/bin/arm-none-eabi-objcopy",
    "/usr/local/bin/arm-none-eabi-objcopy",
    "/usr/bin/arm-none-eabi-objcopy",
]


def find_objcopy():
    for path in OBJCOPY_PATHS:
        if os.path.isfile(path):
            return path
    return shutil.which("arm-none-eabi-objcopy")


def convert_to_hex(objcopy, elf_path):
    hex_path = elf_path + ".hex"
    result = subprocess.run(
        [objcopy, "-O", "ihex", elf_path, hex_path],
        capture_output=True, text=True, check=False
    )
    if result.returncode != 0:
        print(f"Error converting ELF to HEX: {result.stderr.strip()}", file=sys.stderr)
        return None
    return hex_path


def main():
    parser = argparse.ArgumentParser(description="Flash firmware to target via J-Link.")
    parser.add_argument("--file", required=True, help="Path to firmware file (.elf, .hex, .bin)")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--address", type=lambda x: int(x, 0), default=0,
                        help="Flash address for .bin files (default: 0). Ignored for .elf/.hex.")
    parser.add_argument("--objcopy", default=None, help="Path to arm-none-eabi-objcopy (auto-detected if omitted)")
    add_connection_args(parser)
    args = parser.parse_args()

    file_path = args.file
    if not os.path.isfile(file_path):
        print(f"Error: file not found: {file_path}", file=sys.stderr)
        return 1

    ext = os.path.splitext(file_path)[1].lower()
    hex_cleanup = False
    flash_addr = args.address

    if ext == ".elf":
        objcopy = args.objcopy or find_objcopy()
        if not objcopy:
            print(
                "Error: arm-none-eabi-objcopy not found. "
                "Install ARM toolchain or pass --objcopy.",
                file=sys.stderr
            )
            return 1
        print(f"Converting ELF to HEX using {objcopy} ...")
        hex_path = convert_to_hex(objcopy, file_path)
        if not hex_path:
            return 1
        file_path = hex_path
        hex_cleanup = True
        flash_addr = 0
    elif ext == ".hex":
        flash_addr = 0

    try:
        jlink = connect(args.device, args.speed, args.remote_host, args.remote_port)
        print(f"Connected to {args.device}.")

        print(f"Flashing {file_path} (addr=0x{flash_addr:x}) ...")
        jlink.flash_file(file_path, flash_addr)
        print("Flash complete.")

        return 0
    except Exception as e:
        print(f"Error: {e}", file=sys.stderr)
        return 1
    finally:
        if hex_cleanup and os.path.isfile(file_path):
            os.remove(file_path)


if __name__ == "__main__":
    sys.exit(main())
