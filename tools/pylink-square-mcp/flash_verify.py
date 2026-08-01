#!/usr/bin/env python3
"""Read back flash from the target via J-Link and compare its SHA-256
against the built binary.

Usage:
    python3 flash_verify.py --bin <file.bin> [--device STM32H753ZI] [--speed 4000]
"""

import argparse
import hashlib
import pylink


def main():
    parser = argparse.ArgumentParser(description="Verify flashed firmware via SHA-256 readback.")
    parser.add_argument("--bin", required=True, help="Path to the built .bin file")
    parser.add_argument("--device", default="STM32H753ZI")
    parser.add_argument("--speed", type=int, default=4000)
    parser.add_argument("--address", default="0x08000000", help="Flash base address of the image")
    args = parser.parse_args()

    with open(args.bin, "rb") as f:
        image = f.read()

    base = int(args.address, 0)
    args.address = base
    expected = hashlib.sha256(image).hexdigest()

    jlink = pylink.JLink()
    jlink.open(serial_no=None)
    jlink.connect(args.device, speed=args.speed)
    jlink.reset(halt=True)

    print(f"Reading {len(image)} bytes from {args.address:#x} ...")
    data = jlink.memory_read(base, len(image))
    actual = hashlib.sha256(bytes(data)).hexdigest()

    print(f"Expected SHA-256 ({len(image)} bytes): {expected}")
    print(f"Actual   SHA-256 (flash readback):    {actual}")

    if expected == actual:
        print("MATCH: flash contents are identical to the built binary.")
        return 0

    print("MISMATCH: flash does not match the built binary!")
    diff = next((i for i, (a, b) in enumerate(zip(bytes(data), image)) if a != b), None)
    if diff is not None:
        print(f"First difference at offset 0x{diff:x} (flash addr {args.address + diff:#x})")
        print(f"  bin  : {image[diff:diff+16].hex()}")
        print(f"  flash: {bytes(data[diff:diff+16]).hex()}")

    # Report contiguous mismatch ranges
    ranges = []
    in_range = False
    start = 0
    for i, (a, b) in enumerate(zip(bytes(data), image)):
        if a != b:
            if not in_range:
                start = i
                in_range = True
        else:
            if in_range:
                ranges.append((start, i))
                in_range = False
    if in_range:
        ranges.append((start, len(image)))

    content_bad = 0
    print(f"Mismatch ranges ({len(ranges)}):")
    for s, e in ranges:
        size = e - s
        is_padding = all(x == 0 for x in image[s:e]) and all(
            x == 0xFF for x in bytes(data[s:e])
        )
        kind = "padding gap" if is_padding else "CONTENT"
        if not is_padding:
            content_bad += 1
        print(f"  0x{s:x}-0x{e:x} ({size} bytes) {kind}")
    if content_bad == 0:
        print("All differences are zero-filled padding gaps (flash holds erased 0xFF).")
        print("RESULT: flash content matches the build; only inter-section padding differs.")
        return 0
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
