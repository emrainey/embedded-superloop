import sys
import json
import traceback
import io
import contextlib

# Import the main functions of our scripts
try:
    from debug_target import main as debug_target_main
except ImportError:
    import os
    sys.path.append(os.path.dirname(os.path.abspath(__file__)))
    from debug_target import main as debug_target_main

from backtrace import main as backtrace_main
from dump_memory import main as dump_memory_main
from test_breakpoint import main as test_breakpoint_main
from run_to_main import main as run_to_main_main
from dump_ethernet import main as dump_ethernet_main

def log(msg):
    sys.stderr.write(f"[MCP-Server] {msg}\n")
    sys.stderr.flush()

def run_tool_main(main_func, args):
    """
    Runs a tool's main function with mocked sys.argv and captures its stdout/stderr.
    """
    f = io.StringIO()
    log(f"Running tool {main_func.__name__} with args: {args}")
    with contextlib.redirect_stdout(f), contextlib.redirect_stderr(f):
        orig_argv = sys.argv
        sys.argv = [main_func.__name__] + args
        try:
            exit_code = main_func()
        except SystemExit as e:
            exit_code = e.code
        except Exception as e:
            print(f"Exception during execution: {e}")
            traceback.print_exc()
            exit_code = 1
        finally:
            sys.argv = orig_argv
    return exit_code, f.getvalue()

def handle_debug_target(arguments):
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)
    args = ["--device", str(device), "--speed", str(speed)]
    return run_tool_main(debug_target_main, args)

def handle_backtrace(arguments):
    elf = arguments.get("elf")
    if not elf:
        return 1, "Error: 'elf' argument is required."
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)
    words = arguments.get("words", 64)
    args = ["--elf", str(elf), "--device", str(device), "--speed", str(speed), "--words", str(words)]
    return run_tool_main(backtrace_main, args)

def handle_dump_memory(arguments):
    address = arguments.get("address")
    if not address:
        return 1, "Error: 'address' argument is required."
    words = arguments.get("words", 256)
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)

    args = ["--address", str(address), "--words", str(words), "--device", str(device), "--speed", str(speed)]
    if arguments.get("show_zeros", False):
        args.append("--show-zeros")
    return run_tool_main(dump_memory_main, args)

def handle_dump_ethernet(arguments):
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)
    timeout = arguments.get("timeout", 10.0)
    run_to_main = arguments.get("run_to_main", False)
    run_seconds = arguments.get("run_seconds", 0.0)
    all_fields = arguments.get("all_fields", False)
    elf = arguments.get("elf", None)
    nm = arguments.get("nm", None)
    svd = arguments.get("svd", None)
    breakpoint_symbol = arguments.get("breakpoint_symbol", None)
    args = ["--device", str(device), "--speed", str(speed), "--timeout", str(timeout)]
    if run_to_main:
        args.append("--run-to-main")
    if run_seconds > 0.0:
        args += ["--run-seconds", str(run_seconds)]
    if all_fields:
        args.append("--all-fields")
    if elf:
        args += ["--elf", str(elf)]
    if nm:
        args += ["--nm", str(nm)]
    if svd:
        args += ["--svd", str(svd)]
    if breakpoint_symbol:
        args += ["--breakpoint-symbol", str(breakpoint_symbol)]
    return run_tool_main(dump_ethernet_main, args)


def handle_run_to_main(arguments):
    elf = arguments.get("elf")
    if not elf:
        return 1, "Error: 'elf' argument is required."
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)
    timeout = arguments.get("timeout", 10.0)
    nm = arguments.get("nm", None)
    symbol = arguments.get("symbol", None)
    args = ["--elf", str(elf), "--device", str(device), "--speed", str(speed), "--timeout", str(timeout)]
    if nm:
        args += ["--nm", str(nm)]
    if symbol:
        args += ["--symbol", str(symbol)]
    return run_tool_main(run_to_main_main, args)


def handle_test_breakpoint(arguments):
    pc = arguments.get("pc")
    address = arguments.get("address")
    if not pc or not address:
        return 1, "Error: 'pc' and 'address' arguments are required."
    words = arguments.get("words", 128)
    device = arguments.get("device", "STM32H753ZI")
    speed = arguments.get("speed", 4000)
    timeout = arguments.get("timeout", 5.0)

    args = [
        "--pc", str(pc),
        "--address", str(address),
        "--words", str(words),
        "--device", str(device),
        "--speed", str(speed),
        "--timeout", str(timeout)
    ]
    return run_tool_main(test_breakpoint_main, args)

TOOLS = [
    {
        "name": "debug_target",
        "description": "Query target registers and exception/fault status (CFSR/HFSR) via J-Link.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000}
            }
        },
        "handler": handle_debug_target
    },
    {
        "name": "backtrace",
        "description": "Dump target stack memory and resolve code addresses using an ELF file.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to the ELF file with debug symbols"},
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000},
                "words": {"type": "integer", "description": "Number of stack words to dump", "default": 64}
            },
            "required": ["elf"]
        },
        "handler": handle_backtrace
    },
    {
        "name": "dump_memory",
        "description": "Read a range of memory (RAM or peripheral registers) and dump it, suppressing continuous zeros.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "address": {"type": "string", "description": "Target memory address in hex (e.g. '0x2400a434')"},
                "words": {"type": "integer", "description": "Number of 32-bit words to read", "default": 256},
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000},
                "show_zeros": {"type": "boolean", "description": "Show all zero words instead of suppressing them", "default": False}
            },
            "required": ["address"]
        },
        "handler": handle_dump_memory
    },
    {
        "name": "dump_ethernet",
        "description": "Read and decode all STM32H7 Ethernet MAC/MTL/DMA registers using the on-board SVD. Optionally runs to cortex::system::main first.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000},
                "timeout": {"type": "number", "description": "Seconds to wait for breakpoint (with run_to_main)", "default": 10.0},
                "run_to_main": {"type": "boolean", "description": "Reset and run to the breakpoint symbol before reading registers", "default": False},
                "run_seconds": {"type": "number", "description": "After the breakpoint, release and run for this many seconds before halting (allows PHY to negotiate and frames to arrive)", "default": 0.0},
                "breakpoint_symbol": {"type": "string", "description": "Mangled symbol to break at (default: cortex::system::main). E.g. '_ZN4Demo7ExecuteEv' for Demo::Execute"},
                "all_fields": {"type": "boolean", "description": "Print all fields including zero-valued ones", "default": False},
                "elf": {"type": "string", "description": "Path to ELF (required when run_to_main is true)"},
                "nm": {"type": "string", "description": "Optional path to arm-none-eabi-nm"},
                "svd": {"type": "string", "description": "Path to STM32H753.svd (auto-detected if omitted)"}
            }
        },
        "handler": handle_dump_ethernet
    },
    {
        "name": "run_to_main",
        "description": "Reset target and run to a symbol (default: cortex::system::main) using a symbol-resolved hardware breakpoint.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "elf": {"type": "string", "description": "Path to the ELF file with debug symbols"},
                "symbol": {"type": "string", "description": "Mangled symbol to break at (default: _ZN6cortex6system4mainEv = cortex::system::main). E.g. '_ZN4Demo7ExecuteEv' for Demo::Execute"},
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000},
                "timeout": {"type": "number", "description": "Seconds to wait for breakpoint hit", "default": 10.0},
                "nm": {"type": "string", "description": "Optional path to arm-none-eabi-nm (auto-detected if omitted)"}
            },
            "required": ["elf"]
        },
        "handler": handle_run_to_main
    },
    {
        "name": "test_breakpoint",
        "description": "Set a temporary hardware breakpoint at an address, reset/run target, and dump memory when hit.",
        "inputSchema": {
            "type": "object",
            "properties": {
                "pc": {"type": "string", "description": "Breakpoint PC address in hex (e.g. '0x08007420')"},
                "address": {"type": "string", "description": "Target memory address to dump when breakpoint is hit (hex, e.g. '0x2400a434')"},
                "words": {"type": "integer", "description": "Number of words to dump", "default": 128},
                "device": {"type": "string", "description": "Target device name", "default": "STM32H753ZI"},
                "speed": {"type": "integer", "description": "J-Link speed in kHz", "default": 4000},
                "timeout": {"type": "number", "description": "Breakpoint wait timeout in seconds", "default": 5.0}
            },
            "required": ["pc", "address"]
        },
        "handler": handle_test_breakpoint
    }
]

def main():
    log("pylink-square-mcp server starting...")
    for line in sys.stdin:
        if not line.strip():
            continue
        try:
            request = json.loads(line)
        except Exception as e:
            log(f"Failed to parse JSON: {line.strip()}. Error: {e}")
            continue

        method = request.get("method")
        req_id = request.get("id")

        if method == "initialize":
            response = {
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {
                    "protocolVersion": "2024-11-05",
                    "capabilities": {
                        "tools": {}
                    },
                    "serverInfo": {
                        "name": "pylink-square-mcp",
                        "version": "0.1.0"
                    }
                }
            }
            sys.stdout.write(json.dumps(response) + "\n")
            sys.stdout.flush()
            log("Initialized protocol session.")

        elif method == "notifications/initialized":
            log("Received notifications/initialized from client.")
            # No response needed

        elif method == "tools/list":
            # Strip handler from schema representation
            tools_list = []
            for t in TOOLS:
                tools_list.append({
                    "name": t["name"],
                    "description": t["description"],
                    "inputSchema": t["inputSchema"]
                })
            response = {
                "jsonrpc": "2.0",
                "id": req_id,
                "result": {
                    "tools": tools_list
                }
            }
            sys.stdout.write(json.dumps(response) + "\n")
            sys.stdout.flush()
            log(f"Listed {len(tools_list)} tools.")

        elif method == "tools/call":
            params = request.get("params", {})
            name = params.get("name")
            arguments = params.get("arguments", {})
            log(f"Calling tool '{name}'...")

            tool = next((t for t in TOOLS if t["name"] == name), None)
            if not tool:
                response = {
                    "jsonrpc": "2.0",
                    "id": req_id,
                    "error": {
                        "code": -32601,
                        "message": f"Method not found: {name}"
                    }
                }
            else:
                try:
                    exit_code, output = tool["handler"](arguments)
                    response = {
                        "jsonrpc": "2.0",
                        "id": req_id,
                        "result": {
                            "content": [
                                {
                                    "type": "text",
                                    "text": output
                                }
                            ],
                            "isError": exit_code != 0
                        }
                    }
                except Exception as e:
                    log(f"Error handling tool '{name}': {e}\n{traceback.format_exc()}")
                    response = {
                        "jsonrpc": "2.0",
                        "id": req_id,
                        "result": {
                            "content": [
                                {
                                    "type": "text",
                                    "text": f"Internal error executing tool '{name}': {e}\n{traceback.format_exc()}"
                                }
                            ],
                            "isError": True
                        }
                    }
            sys.stdout.write(json.dumps(response) + "\n")
            sys.stdout.flush()
            log(f"Tool '{name}' finished execution.")

        else:
            if req_id is not None:
                response = {
                    "jsonrpc": "2.0",
                    "id": req_id,
                    "error": {
                        "code": -32601,
                        "message": f"Unsupported or unknown method: {method}"
                    }
                }
                sys.stdout.write(json.dumps(response) + "\n")
                sys.stdout.flush()

if __name__ == "__main__":
    main()
