
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
        . = ORIGIN(AHB1) + 0x6000;
        _stm32_dma1 = . ;
        . = ORIGIN(AHB1) + 0x6400;
        _stm32_dma2 = . ;
        . = ORIGIN(AHB1) + 0x8000;
        _stm32_ethernet = . ;
        . = ORIGIN(AHB1) + 0xB000;
        _stm32_dma2d = . ;
    } > AHB1

    /* Provide as the base for an array of peripherals */
    PROVIDE(_ZN5stm329registers28general_purpose_input_outputE = _stm32_gpio);
    PROVIDE(_ZN5stm329registers23reset_and_clock_controlE = _stm32_reset_and_clock_control);
    PROVIDE(_ZN5stm329registers13flash_controlE = _stm32_flash_control);
    ASSERT((_stm32_bkpsram_end - _stm32_bkpsram_start) <= BKPRSRAM_SIZE, ".bkpsram has overrun!")
    /* Provide as the base for an array of peripherals */
    PROVIDE(_ZN5stm329registers20direct_memory_accessE = _stm32_dma1);
    PROVIDE(_ZN5stm329registers21direct_memory_access1E = _stm32_dma1);
    PROVIDE(_ZN5stm329registers21direct_memory_access2E = _stm32_dma2);
    PROVIDE(_ZN5stm329registers8ethernetE = _stm32_ethernet);
    PROVIDE(_ZN5stm329registers143dma2d_controlE = _stm32_dma2d);

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

    /* Private Peripheral Block for Cortex M */
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