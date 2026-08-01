import argparse
import pylink
import sys
import os
import json
import time
import struct

from models import models

STATE_DIR = os.path.join(os.path.dirname(os.path.abspath(__file__)), ".rtt_state")
STATE_FILE = os.path.join(STATE_DIR, "rtt_read_state.json")

def load_state():
    if os.path.exists(STATE_FILE):
        try:
            with open(STATE_FILE, "r") as f:
                return json.load(f)
        except (json.JSONDecodeError, OSError):
            pass
    return {"last_read_offset": 0, "total_bytes_read": 0}

def save_state(state):
    os.makedirs(STATE_DIR, exist_ok=True)
    with open(STATE_FILE, "w") as f:
        json.dump(state, f)

def reset_state():
    if os.path.exists(STATE_FILE):
        os.remove(STATE_FILE)

def main():
    parser = argparse.ArgumentParser(description="Read SEGGER RTT output from target.")
    parser.add_argument("--device", default="STM32H753ZI", help="Target device name (default: STM32H753ZI)")
    parser.add_argument("--speed", type=int, default=4000, help="J-Link speed in kHz (default: 4000)")
    parser.add_argument("--elf", default=None, help="Path to ELF file (optional, for symbol lookup)")
    parser.add_argument("--since", type=str, default=None,
                        help="Reset tracked offset to 0. Pass 'reset' to clear. Otherwise auto-tracks.")
    parser.add_argument("--continuous", type=float, default=0,
                        help="If > 0, poll continuously for N seconds, returning new data each poll cycle.")
    args = parser.parse_args()

    assert(args.device in models), f"Device {args.device} not supported. Supported devices: {list(models.keys())}"

    if args.since == "reset":
        reset_state()
        print("RTT state reset.")
        return 0

    state = load_state()
    last_read_offset = state.get("last_read_offset", 0)
    total_bytes_read = state.get("total_bytes_read", 0)

    try:
        jlink = pylink.JLink()
        jlink.open()
        jlink.set_tif(pylink.enums.JLinkInterfaces.SWD)
        jlink.connect(args.device, speed=args.speed)

        if not jlink.halted():
            jlink.halt()

        # Read known RTT control block location (from rtt.cpp: control_block in BSS)
        # The control_block is at a known link-time address; we search for "SEGGER RTT"
        # in all RAM ranges for the device if not found at known locations.

        cb_addr = None
        # Try known locations first (from BSS symbol)
        known_cb_candidates = [
            0x24000808,  # known from previous runs
            0x24000c08,  # from _ZN3rtt13control_blockE in current firmware
        ]
        for cand in known_cb_candidates:
            try:
                data = jlink.memory_read8(cand, 16)
                sig = bytes(data).decode("ascii", errors="ignore")
                if sig.startswith("SEGGER RTT"):
                    cb_addr = cand
                    break
            except Exception:
                pass

        if cb_addr is None:
            # Scan RAM for the signature
            step = 0x1000
            sram_ranges = models[args.device]["ram"]
            for base, end in sram_ranges:
                for addr in range(base, end, step):
                    try:
                        data = jlink.memory_read8(addr, 16)
                        sig = bytes(data).decode("ascii", errors="ignore")
                        if sig.startswith("SEGGER RTT"):
                            cb_addr = addr
                            break
                    except Exception:
                        pass

        if cb_addr is None:
            print("ERROR: Could not find SEGGER RTT Control Block in target memory.")
            return 1

        # Parse ControlBlock (rtt.hpp layout):
        # offset 0x00: char id[16]  (already read)
        # offset 0x10: uint32_t maximum_up_buffers_count (native endian)
        # offset 0x14: uint32_t maximum_down_buffers_count (native endian)
        # offset 0x18: BufferInfo up_[0] (24 bytes each on 32-bit ARM)
        #   +0x00: char const* name_     (4 bytes)
        #   +0x04: uint8_t* data_        (4 bytes)
        #   +0x08: SizeType size_        (4 bytes, uint32_t on ARM)
        #   +0x0C: SizeType volatile write_offset_ (4 bytes)
        #   +0x10: SizeType volatile read_offset_  (4 bytes)
        #   +0x14: Flags flags_          (4 bytes)

        buf_info_addr = cb_addr + 0x18
        buf_info = jlink.memory_read32(buf_info_addr, 6)

        name_ptr       = buf_info[0]
        data_ptr       = buf_info[1]
        buffer_size    = buf_info[2]
        write_offset   = buf_info[3]
        read_offset    = buf_info[4]
        flags          = buf_info[5]

        end_time = time.time() + args.continuous if args.continuous > 0 else None
        first_pass = True

        while True:
            now = time.time()

            # Re-read offsets each cycle in case they changed while target was running
            buf_info_fresh = jlink.memory_read32(buf_info_addr, 6)
            write_offset   = buf_info_fresh[3]
            read_offset    = buf_info_fresh[4]

            if write_offset >= buffer_size:
                wrapped = True
                write_pos = write_offset - buffer_size
            else:
                wrapped = False
                write_pos = write_offset

            new_data = b""
            if write_offset > last_read_offset and not wrapped:
                # No wrap, simple contiguous read
                bytes_avail = write_offset - last_read_offset
                new_data = bytes(jlink.memory_read8(data_ptr + last_read_offset, bytes_avail))
            elif wrapped:
                # Buffer has wrapped; read from last_read_offset to end, then from 0 to write_pos
                bytes_to_end = buffer_size - last_read_offset
                if bytes_to_end > 0:
                    new_data += bytes(jlink.memory_read8(data_ptr + last_read_offset, bytes_to_end))
                if write_pos > 0:
                    new_data += bytes(jlink.memory_read8(data_ptr, write_pos))
            elif write_offset > last_read_offset:
                bytes_avail = write_offset - last_read_offset
                new_data = bytes(jlink.memory_read8(data_ptr + last_read_offset, bytes_avail))

            if new_data:
                timestamp = time.strftime("%H:%M:%S", time.localtime(now))
                text = new_data.decode("utf-8", errors="replace")
                for line in text.split("\n"):
                    line = line.rstrip("\r").rstrip()
                    if line:
                        print(f"[{timestamp}] {line}")
                    else:
                        print()

                total_bytes_read += len(new_data)
                last_read_offset = write_offset

            if end_time is not None and now < end_time and not first_pass:
                # Sleep and poll again
                time.sleep(0.5)
                first_pass = False
                continue
            elif end_time is not None and now >= end_time:
                break
            elif end_time is not None and first_pass:
                # Resume the target so new data can be produced between polls
                jlink.restart()
                time.sleep(0.5)
                first_pass = False
                continue

            break  # non-continuous: exit after first read

        # Save state
        state["last_read_offset"] = last_read_offset
        state["total_bytes_read"] = total_bytes_read
        save_state(state)

        return 0

    except Exception as e:
        print(f"Error reading RTT: {e}", file=sys.stderr)
        return 1

if __name__ == "__main__":
    sys.exit(main())
