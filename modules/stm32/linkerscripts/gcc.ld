
/**
 * The GNU Linker Script for this system
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

BKPRSRAM_SIZE = 4k;
STACK_SIZE = 32K;

MEMORY {
    FLASH         (rx) : ORIGIN = 0x08000000, LENGTH = 1M
    CCM           (rw) : ORIGIN = 0x10000000, LENGTH = 64K
    SRAM          (rw) : ORIGIN = 0x20000000, LENGTH = 128K
    APB1          (rw) : ORIGIN = 0x40000000, LENGTH = 0x00010000
    APB2          (rw) : ORIGIN = 0x40010000, LENGTH = 0x00010000
    AHB1          (rw) : ORIGIN = 0x40020000, LENGTH = 0x00009400
    USB_OTG_HS    (rw) : ORIGIN = 0x40040000, LENGTH = 0x00040000
    USB_OTG_FS    (rw) : ORIGIN = 0x50000000, LENGTH = 0x00040000
    AHB2          (rw) : ORIGIN = 0x50050000, LENGTH = 0x00060C00
    AHB3          (rw) : ORIGIN = 0x60000000, LENGTH = 0x40001000
    PPB           (rw) : ORIGIN = 0xE0000000, LENGTH = 1M
    VENDOR        (rw) : ORIGIN = 0xE0100000, LENGTH = 0x1FF00000
}

REGION_ALIAS("REGION_TEXT",    FLASH);
REGION_ALIAS("REGION_RODATA",  FLASH);
REGION_ALIAS("REGION_DATA",    SRAM);
REGION_ALIAS("REGION_BSS",     SRAM);
REGION_ALIAS("REGION_STACK",   CCM);
REGION_ALIAS("REGION_SYSTEM",  PPB);

ENTRY(reset_entry)

/* +===================================================================+ */
/* This linker script does not support Heaps, C++ Exceptions or C++ RTTI */
/* +===================================================================+ */
SECTIONS {
    /* Vector Table(s) */
    .tables : {
        __vector_table_start = .;
        KEEP(*(.vectors))
        KEEP(*(.extended_vectors))
        __vector_table_end = .;
    } >REGION_TEXT
    /* Program Code (aligned at next 1KB) */
    .text ALIGN(1024) : {
        *(.text)
        *(.text.*)
    } >REGION_TEXT

    .preinit_array ALIGN(4) : { /* meant to run before shared object dependencies... (we don't have those) */
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } >REGION_TEXT

    .init_array ALIGN(4) : {
        KEEP(*(.init)) /* process initialization (we don't need) */
        *(SORT(.ctors.*))
        *(.ctors)
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
    } >REGION_TEXT

    .fini_array ALIGN(4) : {
        KEEP(*(.fini)) /* process teardown (we don't need) */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        *(SORT(.dtors.*))
        *(.dtors)
        . = ALIGN(4);
    } >REGION_TEXT

    /* Intialized Constant Static Storage */
    .rodata ALIGN(4) : {
        __data_load = .;
        *(.rodata)
        *(.rodata.*)
    } >REGION_TEXT

    /* Intialized Static Storage */
    .data : {
        __data_start = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        __data_end = .;
    } >REGION_DATA

    /* The privileged memory section contains data which only Privileged mode should access.
     * It needs to be aligned to a larger power of 2, like 1K to support making an MPU region
     */
    .privileged_data ALIGN(1024) : {
        __privileged_data_start = .;
        *(.privileged_data)
        . = ALIGN(1024);
        __privileged_data_end = .;
    } >REGION_DATA
    __privileged_data_size = SIZEOF(.privileged_data);
    __privileged_data_size_pow2 = LOG2CEIL(__privileged_data_size);

    /* Unintialized Static Storage */
    .bss (NOLOAD) : {
        __bss_start = ALIGN(4);
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        __bss_end = .;
    } >REGION_BSS

    /* Process Stack */
    .process_stack (NOLOAD) : {
        __process_stack_bottom = .;
        . = . + STACK_SIZE - 8;
        __process_stack_ceiling = .;
        . = . + 8;
        __process_stack_top = .;
    } >REGION_STACK
    __process_stack_size = SIZEOF(.process_stack);
    __process_stack_size_pow2 = LOG2CEIL(__process_stack_size);

    /* Main Stack Guard */
    .main_stack (NOLOAD) : {
        __main_stack_bottom = .;
        . = . + STACK_SIZE - 64;
        __main_stack_ceiling = .;
        . = . + 64;
        __main_stack_top = .;
    } >REGION_STACK
    __main_stack_size = SIZEOF(.main_stack);
    __main_stack_size_pow2 = LOG2CEIL(__main_stack_size);

    /* Arm Private Bus 1 */
    .apb1 (NOLOAD) : {
        . = ORIGIN(APB1) + 0x0000;
        _stm32_tim2 = . ;
        . = ORIGIN(APB1) + 0x0400;
        _stm32_tim3 = . ;
        . = ORIGIN(APB1) + 0x0800;
        _stm32_tim4 = . ;
        . = ORIGIN(APB1) + 0x0C00;
        _stm32_tim5 = . ;
        . = ORIGIN(APB1) + 0x1000;
        _stm32_tim6 = . ;
        . = ORIGIN(APB1) + 0x1400;
        _stm32_tim7 = . ;
        . = ORIGIN(APB1) + 0x1800;
        _stm32_tim12 = . ;
        . = ORIGIN(APB1) + 0x1C00;
        _stm32_tim13 = . ;
        . = ORIGIN(APB1) + 0x2000;
        _stm32_tim14 = . ;
        . = ORIGIN(APB1) + 0x2800;
        _stm32_rtc_bkp = . ;
        . = ORIGIN(APB1) + 0x2C00;
        _stm32_wwdg = . ;
        . = ORIGIN(APB1) + 0x3000;
        _stm32_iwdg = . ;
        . = ORIGIN(APB1) + 0x3400;
        _stm32_i2s2_ext = . ;
        . = ORIGIN(APB1) + 0x3800;
        _stm32_spi2_i2s2 = . ;
        . = ORIGIN(APB1) + 0x3C00;
        _stm32_spi3_i2s3 = . ;
        . = ORIGIN(APB1) + 0x4000;
        _stm32_i2s3_ext = . ;
        . = ORIGIN(APB1) + 0x4400;
        _stm32_usart2 = . ;
        . = ORIGIN(APB1) + 0x4800;
        _stm32_usart3 = . ;
        . = ORIGIN(APB1) + 0x4C00;
        _stm32_uart4 = . ;
        . = ORIGIN(APB1) + 0x5000;
        _stm32_uart5 = . ;
        . = ORIGIN(APB1) + 0x5400;
        _stm32_i2c1 = . ;
        . = ORIGIN(APB1) + 0x5800;
        _stm32_i2c2 = . ;
        . = ORIGIN(APB1) + 0x5C00;
        _stm32_i2c3 = . ;
        . = ORIGIN(APB1) + 0x6400;
        _stm32_can1 = . ;
        . = ORIGIN(APB1) + 0x6800;
        _stm32_can2 = . ;
        . = ORIGIN(APB1) + 0x7000;
        _stm32_pwr = . ;
        . = ORIGIN(APB1) + 0x7400;
        _stm32_dac = . ;
    } > APB1

    PROVIDE(_ZN5stm329registers6timer2E = _stm32_tim2);

    /* Arm Private Bus 2 */
    .apb2 (NOLOAD) : {
        . = ORIGIN(APB2) + 0x0000;
        _stm32_tim1 = . ;
        . = ORIGIN(APB2) + 0x0400;
        _stm32_tim8 = . ;
        . = ORIGIN(APB2) + 0x1000;
        _stm32_usart1 = . ;
        . = ORIGIN(APB2) + 0x1400;
        _stm32_usart6 = . ;
        . = ORIGIN(APB2) + 0x2000;
        _stm32_adc1 = . ;
        . = ORIGIN(APB2) + 0x2C00;
        _stm32_sdio = . ;
        . = ORIGIN(APB2) + 0x3000;
        _stm32_spi1 = . ;
        . = ORIGIN(APB2) + 0x3400;
        _stm32_spi4 = . ;
        . = ORIGIN(APB2) + 0x3800;
        _stm32_syscfg = . ;
        . = ORIGIN(APB2) + 0x3C00;
        _stm32_exti = . ;
        . = ORIGIN(APB2) + 0x4000;
        _stm32_tim9 = . ;
        . = ORIGIN(APB2) + 0x4400;
        _stm32_tim10 = . ;
        . = ORIGIN(APB2) + 0x4800;
        _stm32_tim11 = . ;
        . = ORIGIN(APB2) + 0x5000;
        _stm32_spi5 = . ;
        . = ORIGIN(APB2) + 0x5400;
        _stm32_spi6 = . ;
        . = ORIGIN(APB2) + 0x5800;
        _stm32_sai1 = . ;
        . = ORIGIN(APB2) + 0x6800;
        _stm32_lcd = . ;
    } > APB2

    PROVIDE(_ZN5stm329registers6timer1E = _stm32_tim1);
    PROVIDE(_ZN5stm329registers4spi1E = _stm32_spi1);

    /* Arm High Performance Bus 1 */
    .ahb1 (NOLOAD) : {
        . = ORIGIN(AHB1) + 0x0000;
        _stm32_gpio = . ;
        . = ORIGIN(AHB1) + 0x3000;
        _stm32_crc = . ;
        . = ORIGIN(AHB1) + 0x3800;
        _stm32_reset_and_clock_control = . ;
        . = ORIGIN(AHB1) + 0x3C00;
        _stm32_flash_control = . ;
        . = ORIGIN(AHB1) + 0x4000;
        _stm32_bkpsram_start = . ;
        KEEP(*(.bkpsram))
        _stm32_bkpsram_end = . ;
    } > AHB1

    PROVIDE(_ZN5stm329registers28general_purpose_input_outputE = _stm32_gpio);
    PROVIDE(_ZN5stm329registers23reset_and_clock_controlE = _stm32_reset_and_clock_control);
    PROVIDE(_ZN5stm329registers13flash_controlE = _stm32_flash_control);
    ASSERT((_stm32_bkpsram_end - _stm32_bkpsram_start) <= BKPRSRAM_SIZE, ".bkpsram has overrun!")

    /* Arm High Performance Bus 2 */
    .ahb2 (NOLOAD) : {
        . = ORIGIN(AHB2) + 0x00000;
        _stm32_dcmi = . ;
        . = ORIGIN(AHB2) + 0x10000;
        _stm32_crypto = . ;
        . = ORIGIN(AHB2) + 0x10400;
        _stm32_hash = . ;
        . = ORIGIN(AHB2) + 0x10800;
        _stm32_rng = . ;
    } > AHB2

    PROVIDE_HIDDEN(_ZN5stm329registers23random_number_generatorE = _stm32_rng);

    /* USB On-The-Go High Speed */
    .usb_otg_hs (NOLOAD) : {
        . = ORIGIN(USB_OTG_HS) + 0x0000;
        _stm32_usb_otg_hs_device = . ;
    } > USB_OTG_HS


    /* USB On-The-Go Full Speed */
    .usb_otg_fs (NOLOAD) : {
        . = ORIGIN(USB_OTG_FS) + 0x0000;
        _stm32_usb_otg_fs_device = . ;
    } > USB_OTG_FS

    /* Arm High Performance Bus 3 */
    .ahb3 (NOLOAD) : {
        . = ORIGIN(AHB3) + 0x00000000;
        _stm32_fsmc_bank_1 = . ;
        . = ORIGIN(AHB3) + 0x10000000;
        _stm32_fsmc_bank_2 = . ;
        . = ORIGIN(AHB3) + 0x20000000;
        _stm32_fsmc_bank_3 = . ;
        . = ORIGIN(AHB3) + 0x30000000;
        _stm32_fsmc_bank_4 = . ;
        . = ORIGIN(AHB3) + 0x40000000;
        _stm32_fsmc_control_block = . ;
    } > AHB3

    /* These are used to zero initialize memory */
    __ccm_beg = ORIGIN(CCM);
    __ccm_end = ORIGIN(CCM) + LENGTH(CCM);
    __sram_beg = ORIGIN(SRAM);
    __sram_end = ORIGIN(SRAM) + LENGTH(SRAM);

    /* Private Peripheral Block for Cortex M7 */
    .ppb (NOLOAD) : {
        . = ORIGIN(PPB) + 0x00000;
        _cortex_instruction_trace_macrocell = . ;
        . = ORIGIN(PPB) + 0x01000;
        _cortex_debug_watch_and_trace = . ;
        . = ORIGIN(PPB) + 0x0E010;
        _cortex_system_tick = . ;
        . = ORIGIN(PPB) + 0x0E100;
        _cortex_nested_interrupt_vector_controller = . ;
        . = ORIGIN(PPB) + 0x0ED00;
        _cortex_system_control_block = . ;
        . = ORIGIN(PPB) + 0x0ED90;
        _cortex_memory_protection_unit = . ;
        . = ORIGIN(PPB) + 0x0EDF0;
        _cortex_debug_system = . ;
        . = ORIGIN(PPB) + 0x0EF00;
        _cortex_software_trigger_interrupt = . ;
        . = ORIGIN(PPB) + 0x0EF34;
        _cortex_floating_point = . ;
        . = ORIGIN(PPB) + 0x40000;
        _cortex_trace_port_inferface_unit = . ;
        . = ORIGIN(PPB) + 0x42000;
        _stm32_debug = . ;
    } > PPB
    /* Provide the C++ mangled names */
    PROVIDE(_ZN6cortex27instruction_trace_macrocellE = _cortex_instruction_trace_macrocell);
    PROVIDE(_ZN6cortex20data_watch_and_traceE = _cortex_debug_watch_and_trace);
    PROVIDE(_ZN6cortex11system_tickE = _cortex_system_tick);
    PROVIDE(_ZN6cortex34nested_interrupt_vector_controllerE = _cortex_nested_interrupt_vector_controller);
    PROVIDE(_ZN6cortex20system_control_blockE = _cortex_system_control_block);
    PROVIDE(_ZN6cortex22memory_protection_unitE = _cortex_memory_protection_unit);
    PROVIDE(_ZN6cortex12debug_systemE = _cortex_debug_system);
    PROVIDE(_ZN6cortex22software_triggered_interruptE = _cortex_software_triggered_interrupt);
    PROVIDE(_ZN6cortex14floating_pointE = _cortex_floating_point);
    PROVIDE(_ZN6cortex25trace_port_interface_unitE = _cortex_trace_port_inferface_unit);
    PROVIDE(_ZN5stm329registers5debugE = _stm32_debug);
}
