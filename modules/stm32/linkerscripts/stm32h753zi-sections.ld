
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
        . = ORIGIN(APB1) + 0x2400;
        _stm32_lptim1 = . ;
        . = ORIGIN(APB1) + 0x2C00;
        /* reserved */
        . = ORIGIN(APB1) + 0x3800;
        _stm32_spi2_i2s2 = . ;
        . = ORIGIN(APB1) + 0x3C00;
        _stm32_spi3_i2s3 = . ;
        . = ORIGIN(APB1) + 0x4000;
        _stm32_spdifrx1 = . ;
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
        /* reserved */
        . = ORIGIN(APB1) + 0x6800;
        /* reserved */
        . = ORIGIN(APB1) + 0x6C00;
        _stm32_hdmi_cec = .;
        . = ORIGIN(APB1) + 0x7000;
        /* reserved */
        . = ORIGIN(APB1) + 0x7400;
        _stm32_dac1 = . ;
        . = ORIGIN(APB1) + 0x7800;
        _stm32_uart7 = . ;
        . = ORIGIN(APB1) + 0x7C00;
        _stm32_uart8 = . ;
        . = ORIGIN(APB1) + 0x8000;
        /* reserved */
        . = ORIGIN(APB1) + 0x8400;
        _stm32_crs = . ;
        . = ORIGIN(APB1) + 0x8800;
        _stm32_swpmi = . ;
        . = ORIGIN(APB1) + 0x8C00;
        /* reserved */
        . = ORIGIN(APB1) + 0x9000;
        _stm32_opamp = . ;
        . = ORIGIN(APB1) + 0x9400;
        _stm32_mdios = . ;
        . = ORIGIN(APB1) + 0x9800;
        /* reserved */
        . = ORIGIN(APB1) + 0x9C00;
        /* reserved */
        . = ORIGIN(APB1) + 0xA000;
        _stm32_fdcan1 = . ;
        . = ORIGIN(APB1) + 0xA400;
        _stm32_fdcan2 = . ;
        . = ORIGIN(APB1) + 0xA800;
        _stm32_can_ccu = . ;
        . = ORIGIN(APB1) + 0xAC00;
        _stm32_can_ram = . ;
        . = ORIGIN(APB1) + 0xD400;
    } > APB1

    PROVIDE(_ZN5stm324h7xx6timer2E = _stm32_tim2);
    PROVIDE(_ZN5stm324h7xx4spi2E = _stm32_spi2_i2s2);
    PROVIDE(_ZN5stm324h7xx4spi3E = _stm32_spi3_i2s3);
    PROVIDE(_ZN5stm324h7xx6usart2E = _stm32_usart2);
    PROVIDE(_ZN5stm324h7xx6usart3E = _stm32_usart3);
    PROVIDE(_ZN5stm324h7xx5uart4E = _stm32_uart4);
    PROVIDE(_ZN5stm324h7xx5uart5E = _stm32_uart5);
    PROVIDE(_ZN5stm324h7xx5uart7E = _stm32_uart7);
    PROVIDE(_ZN5stm324h7xx5uart8E = _stm32_uart8);
    PROVIDE(_ZN5stm324h7xx4i2c1E = _stm32_i2c1);
    PROVIDE(_ZN5stm324h7xx4i2c2E = _stm32_i2c2);
    PROVIDE(_ZN5stm324h7xx4i2c3E = _stm32_i2c3);

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
        . = ORIGIN(APB2) + 0x3000;
        _stm32_spi1 = . ;
        . = ORIGIN(APB2) + 0x3400;
        _stm32_spi4 = . ;
        . = ORIGIN(APB2) + 0x4000;
        _stm32_tim15 = . ;
        . = ORIGIN(APB2) + 0x4400;
        _stm32_tim16 = . ;
        . = ORIGIN(APB2) + 0x4800;
        _stm32_tim17 = . ;
        . = ORIGIN(APB2) + 0x5000;
        _stm32_spi5 = . ;
        . = ORIGIN(APB2) + 0x5800;
        _stm32_sai1 = . ;
        . = ORIGIN(APB2) + 0x5C00;
        _stm32_sai2 = . ;
        . = ORIGIN(APB2) + 0x6000;
        _stm32_sai3 = . ;
        . = ORIGIN(APB2) + 0x7000;
        _stm32_dfsdm1 = . ;
        . = ORIGIN(APB2) + 0x7400;
        _stm32_hrtim1 = . ;
    } > APB2

    PROVIDE(_ZN5stm324h7xx6timer1E = _stm32_tim1);
    PROVIDE(_ZN5stm324h7xx4spi1E = _stm32_spi1);
    PROVIDE(_ZN5stm324h7xx4spi4E = _stm32_spi4);
    PROVIDE(_ZN5stm324h7xx4spi5E = _stm32_spi5);
    PROVIDE(_ZN5stm324h7xx4spi6E = _stm32_spi6);
    PROVIDE(_ZN5stm324h7xx6usart1E = _stm32_usart1);
    PROVIDE(_ZN5stm324h7xx6usart6E = _stm32_usart6);

    /* Arm High Performance Bus 1 */
    .ahb1 (NOLOAD) : {
        . = ORIGIN(AHB1) + 0x0000;
        _stm32_dma1 = . ;
        . = ORIGIN(AHB1) + 0x0400;
        _stm32_dma2 = . ;
        . = ORIGIN(AHB1) + 0x0800;
        _stm32_dmamux1 = . ;
        . = ORIGIN(AHB1) + 0x2000;
        _stm32_adc1 = . ;
        . = ORIGIN(AHB1) + 0x2200;
        _stm32_adc2 = . ;
        . = ORIGIN(AHB1) + 0x2800;
        _stm32_ethernet = . ;
    } > AHB1

    /* USB On-The-Go Full Speed */
    .usb_otg_fs (NOLOAD) : {
        . = ORIGIN(USB_OTG_FS) + 0x0000;
        _stm32_usb_otg_fs_device = . ;
    } > USB_OTG_FS

    /* USB On-The-Go High Speed */
    .usb_otg_hs (NOLOAD) : {
        . = ORIGIN(USB_OTG_HS) + 0x0000;
        _stm32_usb_otg_hs_device = . ;
    } > USB_OTG_HS

    .bkup_sram (NOLOAD) : {
        _stm32_bkpsram_start = . ;
        KEEP(*(.bkpsram))
        _stm32_bkpsram_end = .;
    } > BKUP

    /* Provide as the base for an array of peripherals */
    PROVIDE(_ZN5stm324h7xx28general_purpose_input_outputE = _stm32_gpio);
    PROVIDE(_ZN5stm324h7xx23reset_and_clock_controlE = _stm32_reset_and_clock_control);
    PROVIDE(_ZN5stm324h7xx13flash_controlE = _stm32_flash_control);
    ASSERT((_stm32_bkpsram_end - _stm32_bkpsram_start) <= BKPRSRAM_SIZE, ".bkpsram has overrun!")
    __cortex_backup_start = _stm32_bkpsram_start;
    __cortex_backup_limit = _stm32_bkpsram_start + BKPRSRAM_SIZE;
    __cortex_backup_used = _stm32_bkpsram_end - _stm32_bkpsram_start;
    __cortex_backup_size = __cortex_backup_limit - __cortex_backup_start;
    __cortex_backup_pow2  = LOG2CEIL(__cortex_backup_size);
    /* Provide as the base for an array of peripherals */
    PROVIDE(_ZN5stm324h7xx20direct_memory_accessE = _stm32_dma1);
    PROVIDE(_ZN5stm324h7xx21direct_memory_access1E = _stm32_dma1);
    PROVIDE(_ZN5stm324h7xx21direct_memory_access2E = _stm32_dma2);
    PROVIDE(_ZN5stm324h7xx8ethernetE = _stm32_ethernet);
    PROVIDE(_ZN5stm324h7xx143dma2d_controlE = _stm32_dma2d);

    /* Arm High Performance Bus 2 */
    .ahb2 (NOLOAD) : {
        . = ORIGIN(AHB2) + 0x00000;
        _stm32_dcmi = . ;
        . = ORIGIN(AHB2) + 0x1000;
        _stm32_crypto = . ;
        . = ORIGIN(AHB2) + 0x1040;
        _stm32_hash = . ;
        . = ORIGIN(AHB2) + 0x1800;
        _stm32_rng = . ;
        . = ORIGIN(AHB2) + 0x2400;
        _stm32_sdmmc2 = . ;
        . = ORIGIN(AHB2) + 0x3000;
        _stm32_ramecc2 = . ;
    } > AHB2

    PROVIDE_HIDDEN(_ZN5stm324h7xx23random_number_generatorE = _stm32_rng);


    /* Arm Private Bus 3 */
    .apb3 (NOLOAD) : {
        . = ORIGIN(APB3) + 0x0000;
        _stm32_ltdc = . ;
        . = ORIGIN(APB3) + 0x3000;
        _stm32_wwdg1 = . ;
    } > APB3

    /* Arm High Performance Bus 3 */
    .ahb3 (NOLOAD) : {
        . = ORIGIN(AHB3) + 0x00000000;
        _stm32_gpv = . ;
        . = ORIGIN(AHB3) + 0x01000000;
        _stm32_mdma = . ;
        . = ORIGIN(AHB3) + 0x01001000;
        _stm32_dma2d = . ;
        . = ORIGIN(AHB3) + 0x01002000;
        _stm32_flash_control = . ;
        . = ORIGIN(AHB3) + 0x01003000;
        _stm32_jpeg = . ;
        . = ORIGIN(AHB3) + 0x01004000;
        _stm32_fmc = . ;
        . = ORIGIN(AHB3) + 0x01005000;
        _stm32_quadspi = . ;
        . = ORIGIN(AHB3) + 0x01007000;
        _stm32_sdmmc1 = . ;
        . = ORIGIN(AHB3) + 0x01009000;
        _stm32_ramecc1 = . ;
    } > AHB3

    /* Arm Peripheral Bus 4 */
    .apb4 (NOLOAD) : {
        . = ORIGIN(APB4) + 0x0000;
        _stm32_etxi = . ;
        . = ORIGIN(APB4) + 0x0400;
        _stm32_syscfg = . ;
        . = ORIGIN(APB4) + 0x0C00;
        _stm32_lpuart1 = . ;
        . = ORIGIN(APB4) + 0x1400;
        _stm32_spi6 = . ;
        . = ORIGIN(APB4) + 0x1C00;
        _stm32_i2c4 = . ;
        . = ORIGIN(APB4) + 0x2400;
        _stm32_lptimer2 = . ;
        . = ORIGIN(APB4) + 0x2800;
        _stm32_lptimer3 = . ;
        . = ORIGIN(APB4) + 0x2C00;
        _stm32_lptimer4 = . ;
        . = ORIGIN(APB4) + 0x3000;
        _stm32_lptimer5 = . ;
        . = ORIGIN(APB4) + 0x3800;
        _stm32_comp1 = . ;
        . = ORIGIN(APB4) + 0x3A00;
        _stm32_comp2 = . ;
        . = ORIGIN(APB4) + 0x3C00;
        _stm32_vref = . ;
        . = ORIGIN(APB4) + 0x4000;
        _stm32_rtc = . ;
        . = ORIGIN(APB4) + 0x4800;
        _stm32_iwdg1 = . ;
        . = ORIGIN(APB4) + 0x5400;
        _stm32_sai4 = . ;
    } > APB4

    /* Arm High Performance Bus 4 */
    .ahb4 (NOLOAD) : {
        . = ORIGIN(AHB4) + 0x0000;
        _stm32_gpio = . ;
        . = ORIGIN(AHB4) + 0x4400;
        _stm32_reset_and_clock_control = . ;
        . = ORIGIN(AHB4) + 0x4800;
        _stm32_power_control = . ;
        . = ORIGIN(AHB4) + 0x4C00;
        _stm32_crc = . ;
        . = ORIGIN(AHB4) + 0x5400;
        _stm32_bdma = . ;
        . = ORIGIN(AHB4) + 0x5800;
        _stm32_dmamux2 = . ;
        . = ORIGIN(AHB4) + 0x6000;
        _stm32_adc3 = . ;
        . = ORIGIN(AHB4) + 0x6400;
        _stm32_hsem = . ;
        . = ORIGIN(AHB4) + 0x7000;
        _stm32_ramecc3 = . ;
    } > AHB4

    PROVIDE(_ZN5stm324h7xx16power_controllerE = _stm32_power_control);

    /* Private Peripheral Block for Cortex M */
    .ppb (NOLOAD) : {
        . = ORIGIN(PPB) + 0x00000;
        _cortex_instruction_trace_macrocell = . ;
        . = ORIGIN(PPB) + 0x01000;
        _cortex_debug_watch_and_trace = . ;
        . = ORIGIN(PPB) + 0x0E010;
        _cortex_system_tick = . ;
        . = ORIGIN(PPB) + 0x0E100;
        _cortex_nested_vector_interrupt_controller = . ;
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
        . = ORIGIN(PPB) + 0x0EF50;
        _cortex_data_and_instruction_cache_control = . ;
        . = ORIGIN(PPB) + 0x0EF90;
        _cortex_itcm_control = . ;
        . = ORIGIN(PPB) + 0x0EF94;
        _cortex_dtcm_control = . ;
        . = ORIGIN(PPB) + 0x40000;
        _cortex_trace_port_inferface_unit = . ;
        . = ORIGIN(PPB) + 0x42000;
        _stm32_debug = . ;
    } > PPB
    /* Provide the C++ mangled names */
    PROVIDE(_ZN6cortex11peripherals27instruction_trace_macrocellE = _cortex_instruction_trace_macrocell);
    PROVIDE(_ZN6cortex11peripherals20data_watch_and_traceE = _cortex_debug_watch_and_trace);
    PROVIDE(_ZN6cortex11peripherals11system_tickE = _cortex_system_tick);
    PROVIDE(_ZN6cortex11peripherals34nested_vector_interrupt_controllerE = _cortex_nested_vector_interrupt_controller);
    PROVIDE(_ZN6cortex11peripherals20system_control_blockE = _cortex_system_control_block);
    PROVIDE(_ZN6cortex11peripherals22memory_protection_unitE = _cortex_memory_protection_unit);
    PROVIDE(_ZN6cortex11peripherals12debug_systemE = _cortex_debug_system);
    PROVIDE(_ZN6cortex11peripherals22software_triggered_interruptE = _cortex_software_triggered_interrupt);
    PROVIDE(_ZN6cortex11peripherals14floating_pointE = _cortex_floating_point);
    PROVIDE(_ZN6cortex11peripherals34data_and_instruction_cache_controlE = _cortex_data_and_instruction_cache_control);
    PROVIDE(_ZN6cortex11peripherals12itcm_controlE = _cortex_itcm_control);
    PROVIDE(_ZN6cortex11peripherals12dtcm_controlE = _cortex_dtcm_control);
    PROVIDE(_ZN6cortex11peripherals25trace_port_interface_unitE = _cortex_trace_port_inferface_unit);
    PROVIDE(_ZN5stm324h7xx5debugE = _stm32_debug);