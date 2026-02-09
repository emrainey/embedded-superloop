# STM32F407VE Memory Map

(Generated w/ Copilot, so if there are issues, please file a bug report!)

## Overview

The STM32F407VE microcontroller features multiple memory regions optimized for different purposes. This document details the complete memory layout as defined by the linker scripts.

## Memory Regions Summary

| Region | Start Address | End Address | Size | Type | Description |
|--------|--------------|-------------|------|------|-------------|
| FLASH | 0x08000000 | 0x0807FFFF | 512 KB | Non-Volatile | Program memory and constants |
| CCM | 0x10000000 | 0x1000FFFF | 64 KB | SRAM | Core Coupled Memory (data only, no code execution) |
| SRAM | 0x20000000 | 0x2001FFFF | 128 KB | SRAM | Main system RAM |
| BKPSRAM | 0x40024000 | 0x40024FFF | 4 KB | Battery-Backed SRAM | Backup domain memory |
| Peripherals | 0x40000000 | 0x5FFFFFFF | - | Memory-Mapped I/O | Peripheral registers |
| System | 0xE0000000 | 0xE00FFFFF | - | Memory-Mapped | Cortex-M4 system peripherals |

## FLASH Memory Layout (512 KB)

| Section | Address Range | Size | Alignment | Description |
|---------|--------------|------|-----------|-------------|
| Vector Table | 0x08000000 | ~512 bytes | 4-byte | Interrupt and exception vectors |
| .text | Follows vectors | Variable | 4-byte | Executable code |
| .rodata | Follows .text | Variable | 4-byte | Read-only data (constants, strings) |
| .init_array | Follows .rodata | Variable | 4-byte | C++ static constructor table |
| .fini_array | Follows .init_array | Variable | 4-byte | C++ static destructor table |

### FLASH Characteristics

- **Access Speed**: Zero wait states up to 30 MHz, scaled with frequency
- **Write Granularity**: Word (32-bit) or half-word (16-bit)
- **Erase Granularity**: Sector-based (16KB to 128KB sectors)
- **Executable**: Yes (XIP - Execute In Place)
- **Cache**: Instruction and data cache available

## CCM (Core Coupled Memory) Layout (64 KB)

| Section | Address Range | Size | Alignment | Description |
|---------|--------------|------|-----------|-------------|
| CCM | 0x10000000 - Variable | Variable | 4-byte | Used for Stack (Main and Process) |

### CCM Characteristics

- **Access Speed**: Single-cycle access (no wait states)
- **Bus**: Connected directly to D-bus of CPU
- **Executable**: No (data only)
- **DMA Access**: Not accessible by DMA
- **Use Case**: Time-critical data, stack for ISRs

## SRAM Layout (128 KB)

| Section | Address Range | Size | Alignment | Description |
|---------|--------------|------|-----------|-------------|
| .data | 0x20000000 - Variable | Variable | 4-byte | Initialized data (copied from FLASH) |
| .bss | Follows .data | Variable | 4-byte | Zero-initialized data |

### Stack Layout

| Stack Type | Default Size | Alignment | Description |
|-----------|--------------|-----------|-------------|
| Main Stack (MSP) | Configurable | 8-byte | Used in Handler mode and privileged Thread mode |
| Process Stack (PSP) | Configurable | 8-byte | Used in unprivileged Thread mode (RTOS tasks) |

### SRAM Characteristics

- **Access Speed**: Single-cycle access
- **Bus**: Connected to S-bus and D-bus
- **Executable**: Yes (but slower than FLASH)
- **DMA Access**: Full access
- **Parity**: Available on all SRAM

## Backup SRAM Layout (4 KB)

| Section | Address Range | Size | Description |
|---------|--------------|------|-------------|
| .bkpdata | 0x40024000 - 0x40024FFF | 4 KB | Battery-backed data |

### Backup SRAM Characteristics

- **Power Domain**: VDD or VBAT
- **Retention**: Data retained during standby/stop modes when VBAT supplied
- **Access**: Requires RCC backup domain clock enabled
- **Use Case**: Critical data retention across resets

## Peripheral Memory Map

| Bus | Address Range | Description |
|-----|--------------|-------------|
| APB1 | 0x40000000 - 0x40007FFF | Low-speed peripherals (TIM2-7, 12-14, RTC, WWDG, IWDG, SPI2-3, USART2-3, UART4-5, I2C1-3, CAN1-2, PWR, DAC) |
| APB2 | 0x40010000 - 0x40016BFF | High-speed peripherals (TIM1, 8-11, USART1, 6, ADC1-3, SDIO, SPI1, SYSCFG, EXTI) |
| AHB1 | 0x40020000 - 0x4007FFFF | DMA1-2, RCC, FLASH interface, CRC, GPIO ports, Ethernet MAC |
| AHB2 | 0x50000000 - 0x50060FFF | USB OTG FS, DCMI, CRYP, HASH, RNG |
| AHB3 | 0x60000000 - 0xDFFFFFFF | FSMC, External memory |

## System Memory Map

| Peripheral | Address Range | Description |
|-----------|--------------|-------------|
| ITM | 0xE0000000 - 0xE0000FFF | Instrumentation Trace Macrocell |
| DWT | 0xE0001000 - 0xE0001FFF | Data Watchpoint and Trace |
| FPB | 0xE0002000 - 0xE0002FFF | Flash Patch and Breakpoint |
| SCS | 0xE000E000 - 0xE000EFFF | System Control Space |
| - SysTick | 0xE000E010 - 0xE000E0FF | System timer |
| - NVIC | 0xE000E100 - 0xE000ECFF | Interrupt controller |
| - SCB | 0xE000ED00 - 0xE000ED8F | System Control Block |
| - MPU | 0xE000ED90 - 0xE000EDEF | Memory Protection Unit |
| - FPU | 0xE000EF30 - 0xE000EF7F | Floating Point Unit |

## Linker Script Sections

### Input Sections Mapping

| Output Section | Input Sections | Memory Region | Attributes |
|---------------|----------------|---------------|------------|
| .isr_vector | .isr_vector | FLASH | READONLY |
| .text | .text, .text.*, .rodata, .rodata.* | FLASH | READONLY, EXECUTE |
| .init_array | .init_array, .ctors | FLASH | READONLY |
| .fini_array | .fini_array, .dtors | FLASH | READONLY |
| .data | .data, .data.* | SRAM (VMA), FLASH (LMA) | READWRITE |
| .bss | .bss, .bss.*, COMMON | SRAM | READWRITE, NOLOAD |

### Special Symbols

The following symbols are defined by the linker script and declared in `modules/cortex/include/cortex/linker.hpp`:

#### Memory Region Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__vector_table_start` | uint32_t[] | Start of interrupt vector table | VTOR configuration, startup |
| `__vector_table_limit` | uint32_t[] | Limit of interrupt vector table | Vector table bounds |
| `__ccm_start` | uint32_t[] | Start of Core Coupled Memory region | Memory bounds checking |
| `__ccm_limit` | uint32_t[] | Limit of Core Coupled Memory region | Memory bounds checking |
| `__itcm_start` | uint32_t[] | Start of Instruction Tightly Coupled Memory | Memory bounds checking |
| `__itcm_limit` | uint32_t[] | Limit of Instruction Tightly Coupled Memory | Memory bounds checking |
| `__dtcm_start` | uint32_t[] | Start of Data Tightly Coupled Memory | Memory bounds checking |
| `__dtcm_limit` | uint32_t[] | Limit of Data Tightly Coupled Memory | Memory bounds checking |
| `__sram_start` | uint32_t[] | Start of System RAM (0x20000000) | Memory bounds checking |
| `__sram_limit` | uint32_t[] | Limit of System RAM | Memory bounds checking |

#### Data Section Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__static_data_start` | uint32_t[] | Start of uninitialized data (.bss) | Startup: zero initialization |
| `__static_data_limit` | uint32_t[] | Limit of uninitialized data (.bss) | Startup: zero initialization |
| `__const_static_data_start` | uint32_t[] | Start of initialized data (.data) in SRAM (VMA) | Startup: copy destination |
| `__const_static_data_limit` | uint32_t[] | Limit of initialized data (.data) in SRAM | Startup: copy end marker |
| `__const_static_data_load` | uint32_t[] | Load address of initialized data in FLASH (LMA) | Startup: copy source |

#### Stack Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__main_stack_bottom` | uint32_t[] | Bottom of main stack (MSP, low address) | Stack overflow detection |
| `__main_stack_top` | uint32_t[] | Top of main stack (one word past end) | Initial MSP value |
| `__main_stack_ceiling` | uint32_t[] | Ceiling of main stack (last available word) | Stack limit checking |
| `__main_stack_size` | uint32_t[] | Size of main stack in bytes | Stack configuration |
| `__main_stack_size_pow2` | uint32_t[] | Power of 2 size of main stack | MPU region alignment |
| `__process_stack_bottom` | uint32_t[] | Bottom of process stack (PSP, low address) | Stack overflow detection |
| `__process_stack_top` | uint32_t[] | Top of process stack (one word past end) | Initial PSP value |
| `__process_stack_ceiling` | uint32_t[] | Ceiling of process stack (last available word) | Stack limit checking |
| `__process_stack_size` | uint32_t[] | Size of process stack in bytes | Stack configuration |
| `__process_stack_size_pow2` | uint32_t[] | Power of 2 size of process stack | MPU region alignment |

#### Privileged Data Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__privileged_data_start` | uint32_t[] | Start of privileged data section | MPU configuration |
| `__privileged_data_limit` | uint32_t[] | Limit of privileged data section | MPU configuration |
| `__privileged_data_size` | uint32_t[] | Size of privileged data section | MPU configuration |
| `__privileged_data_size_pow2` | uint32_t[] | Power of 2 size of privileged data | MPU region alignment |

#### Constructor/Destructor Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__preinit_array_start` | cortex::constructor[] | Start of preinit array | Early initialization, before main |
| `__preinit_array_limit` | cortex::constructor[] | Limit of preinit array | Early initialization |
| `__init_array_start` | cortex::constructor[] | Start of C++ static constructor array | Startup: call constructors |
| `__init_array_limit` | cortex::constructor[] | Limit of C++ static constructor array | Startup: call constructors |
| `__fini_array_start` | cortex::destructor[] | Start of C++ static destructor array | Shutdown: call destructors |
| `__fini_array_limit` | cortex::destructor[] | Limit of C++ static destructor array | Shutdown: call destructors |

#### Cortex-M Architecture Symbols

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__cortex_flash_start` | uint32_t[] | Start of FLASH region | MPU configuration |
| `__cortex_flash_limit` | uint32_t[] | Limit of FLASH region (past last valid byte) | MPU configuration |
| `__cortex_flash_size` | uint32_t[] | Size of FLASH in bytes | Memory reporting |
| `__cortex_flash_pow2` | uint32_t[] | Power of 2 size of FLASH | MPU region alignment |
| `__cortex_stack_start` | uint32_t[] | Start of stack region | Stack configuration |
| `__cortex_stack_limit` | uint32_t[] | Limit of stack region (past last valid byte) | Stack configuration |
| `__cortex_stack_size` | uint32_t[] | Size of stack in bytes | Stack monitoring |
| `__cortex_stack_pow2` | uint32_t[] | Power of 2 size of stack | MPU region alignment |
| `__cortex_sram_start` | uint32_t[] | Start of SRAM region | MPU configuration |
| `__cortex_sram_limit` | uint32_t[] | Limit of SRAM region (past last valid byte) | MPU configuration |
| `__cortex_sram_size` | uint32_t[] | Size of SRAM in bytes | Memory reporting |
| `__cortex_sram_pow2` | uint32_t[] | Power of 2 size of SRAM | MPU region alignment |
| `__cortex_system_start` | uint32_t[] | Start of System Private Peripheral Bus | MPU configuration |
| `__cortex_system_limit` | uint32_t[] | Limit of System Private Peripheral Bus | MPU configuration |
| `__cortex_system_size` | uint32_t[] | Size of System Peripheral region | Memory reporting |
| `__cortex_system_pow2` | uint32_t[] | Power of 2 size of System region | MPU region alignment |
| `__cortex_peripheral_start` | uint32_t[] | Start of Peripheral Bus | MPU configuration |
| `__cortex_peripheral_limit` | uint32_t[] | Limit of Peripheral Bus (past last valid byte) | MPU configuration |
| `__cortex_peripheral_size` | uint32_t[] | Size of Peripheral region | Memory reporting |
| `__cortex_peripheral_pow2` | uint32_t[] | Power of 2 size of Peripheral region | MPU region alignment |
| `__cortex_backup_start` | uint32_t[] | Start of Backup SRAM | Backup data access |
| `__cortex_backup_limit` | uint32_t[] | Limit of Backup SRAM (past last valid byte) | Backup data bounds |
| `__cortex_backup_used` | uint32_t[] | Used size of Backup SRAM | Memory tracking |
| `__cortex_backup_size` | uint32_t[] | Total size of Backup SRAM | Memory reporting |
| `__cortex_backup_pow2` | uint32_t[] | Power of 2 size of Backup SRAM | MPU region alignment |

#### Zero Initialization Table

| Symbol | Type | Description | Used By |
|--------|------|-------------|---------|
| `__zero_table_start` | ZeroEntry[] | Start of zero initialization table | Startup: batch zero init |
| `__zero_table_limit` | ZeroEntry[] | Limit of zero initialization table | Startup: batch zero init |

The `ZeroEntry` structure is defined as:

```cpp
struct ZeroEntry {
    std::uintptr_t start;  // Starting address of memory region to zero
    std::uintptr_t limit;  // Ending address of memory region to zero
};
```

### Symbol Naming Convention

The project uses consistent naming patterns:

- **Double underscore prefix**: `__symbol` to indicate linker-defined symbols.
- **Array notation**: Symbols declared as `extern type symbol[]` (or `type *symbol` in UNITTEST mode)
- **Suffix conventions**:
  - `_start`: Beginning of region
  - `_limit`: Limit of region (past last valid element)
  - `_ceiling`: Last valid element in region
  - `_size`: Size in bytes
  - `_pow2`: Power of 2 size for MPU alignment
- **LINKER_SYMBOL macro**: Abstracts difference between on-target (`type[]`) and unit test (`type*`) declarations

### Usage in Startup Code

Example initialization using these symbols:

```cpp
// Zero-initialize .bss section
for (uint32_t* p = __static_data_start; p < __static_data_limit; ++p) {
    *p = 0;
}

// Copy initialized .data from FLASH to SRAM
uint32_t* src = __const_static_data_load;
uint32_t* dst = __const_static_data_start;
while (dst < __const_static_data_limit) {
    *dst++ = *src++;
}

// Call C++ static constructors
for (cortex::constructor* ctor = __init_array_start; ctor < __init_array_limit; ++ctor) {
    (*ctor)();
}

// Use zero table for batch initialization
for (ZeroEntry* entry = __zero_table_start; entry < __zero_table_limit; ++entry) {
    for (uint32_t* p = reinterpret_cast<uint32_t*>(entry->start);
         p < reinterpret_cast<uint32_t*>(entry->limit); ++p) {
        *p = 0;
    }
}
```

### Symbol Usage by Component

| Component | Primary Symbols | Purpose |
|-----------|----------------|---------|
| Startup Code | `__const_static_data_*`, `__static_data_*`, `__zero_table_*` | Initialize RAM from FLASH |
| C++ Runtime | `__preinit_array_*`, `__init_array_*`, `__fini_array_*` | Call static constructors/destructors |
| Stack Monitor | `__main_stack_*`, `__process_stack_*` | Detect stack overflow, configure limits |
| MPU Configuration | All `_pow2` symbols, region start/limit pairs | Configure memory protection regions |
| Memory Diagnostics | All `_size` and region boundary symbols | Report memory usage, debug assistance |

## Memory Usage Guidelines

### FLASH Usage

- Store all executable code
- Store constant data (const variables, string literals)
- Store initial values for initialized variables
- Keep frequently accessed code for best performance

### CCM Usage (M4 only)

- Main Stack (MSP) for ISRs and critical code
- Process Stack (PSP) for RTOS tasks or unprivileged threads
- This allows for zero-wait access to stack variables, improving ISR latency and is quite large for embedded projects, allowing some sizable Stack objects. The CCM is not accessible by DMA, so it should not be used for data that needs to be transferred by peripherals.

### SRAM Usage

- General purpose variables (globals, statics)
- DMA buffers (carved out of cacheable area in MPU)

### Backup SRAM Usage

- Configuration data that must survive reset
- Error logs or diagnostic data
- RTC data or timestamps
- Calibration values

## Memory Access Timing

| Memory | CPU Read | CPU Write | DMA Access | Cache |
|--------|----------|-----------|------------|-------|
| FLASH | 0-7 WS* | N/A | No | Yes (I/D) |
| CCM | 0 WS | 0 WS | No | No |
| SRAM | 0 WS | 0 WS | Yes | No |
| Backup SRAM | 0 WS | 0 WS | No | No |

*Wait states depend on system clock frequency and voltage

## Notes

1. **Alignment**: All sections are aligned to 4-byte boundaries minimum
2. **CCM Limitations**: Cannot execute code, no DMA access
3. **Stack Growth**: Stacks grow downward (from high to low addresses)
4. **No Heap**: Heap is not defined. Dynamic memory can be used by statically allocating the @ref core::BitMapHeap objects of a defined size.
5. **MPU**: Can be configured to protect memory regions
6. **FPU**: Uses separate register stack for context switching
7. **System Memory**: Access to system peripherals is through memory-mapped registers
