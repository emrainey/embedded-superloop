# J-Link Python Debugging Tools

A collection of utility scripts built on `pylink-square` to automate target debugging, fault diagnosis, backtracing, and memory inspections for Cortex-M devices.

## Installation

These scripts require Python 3 and the SEGGER J-Link Software and Documentation Pack installed on your host system.

Install the Python dependencies:

```bash
pip install pylink-square
```

If using the workspace virtual environment, execute them using `.venv/bin/python`.

## Scripts

### 1. Target Diagnostics (`debug_target.py`)

Connects to the target, halts the CPU, dumps core registers, and decodes the System Control Block (SCB) Configurable Fault Status Register (CFSR) and HardFault Status Register (HFSR) to identify active UsageFault, BusFault, or MemManage faults.

**Usage:**

```bash
python debug_target.py --device STM32H753ZI --speed 4000
```

### 2. Stack Backtrace Resolver (`backtrace.py`)

Dumps the active stack memory and automatically resolves any code addresses found on the stack (e.g. pointing to Flash memory `0x08000000` - `0x08200000`) using `addr2line` and the debug symbols in the target ELF file.

**Usage:**

```bash
python backtrace.py --elf build/cortex-m7-gcc-arm-none-eabi/applications/nucleo-demo/firmware-nucleo-demo-basic-nucleo_h753zi.elf --device STM32H753ZI
```

### 3. Memory Dumper (`dump_memory.py`)

Reads and dumps a specified range of RAM or peripheral registers. Suppresses continuous runs of zero values to provide a clean and concise output.

**Usage:**

```bash
python dump_memory.py --address 0x2400a434 --words 258 --device STM32H753ZI
```

### 4. Run to `cortex::system::main` (`run_to_main.py`)

Resolves the address of `cortex::system::main` from the ELF debug symbols using `arm-none-eabi-nm`, sets a hardware breakpoint, resets the target, and waits until execution reaches that function. Dumps all core registers when the breakpoint is hit.

**Usage:**

```bash
python run_to_main.py --elf build/cortex-m7-gcc-arm-none-eabi/applications/nucleo-demo/firmware-nucleo-demo-basic-nucleo_h753zi.elf --device STM32H753ZI
```

Optional `--nm /Applications/ArmGNUToolchain/13.2.Rel1/arm-none-eabi/bin/arm-none-eabi-nm` if the tool is not on `$PATH`.

### 5. Breakpoint Memory Inspector (`test_breakpoint.py`)

Sets a temporary hardware breakpoint at a specific address (such as the entry of a function), resets and runs the target, and immediately dumps a memory range when the breakpoint is hit. Excellent for capturing memory state before a boot fault.

**Usage:**

```bash
python test_breakpoint.py --pc 0x08007420 --address 0x2400a434 --words 258 --device STM32H753ZI
```

## Model Context Protocol (MCP) Server

An MCP-compliant entrypoint is provided in `mcp_server.py`. This script exposes all four diagnostic tools to AI agents using standard JSON-RPC 2.0 over standard I/O.

### Exposed Tools

1. `debug_target`: Connection diagnostics, core registers, and exception/fault decoding.
2. `backtrace`: Memory stack dump and debug symbols lookup.
3. `dump_memory`: Generic memory inspection with zero-suppression.
4. `test_breakpoint`: Hardware breakpoint placement and auto-dump.

### Client Configuration Example

Add the following to your MCP client config (e.g., `claude_desktop_config.json`):

```json
{
  "mcpServers": {
    "pylink-square-mcp": {
      "command": "python3",
      "args": ["/Users/emrainey/Source/embedded-superloop/tools/pylink-square-mcp/mcp_server.py"],
      "env": {
        "PYTHONPATH": "/Users/emrainey/Source/embedded-superloop/tools/pylink-square-mcp"
      }
    }
  }
}
```

Make sure the host environment has `pylink-square` installed (`pip install pylink-square`) and standard J-Link command line utilities are available in the system path.
