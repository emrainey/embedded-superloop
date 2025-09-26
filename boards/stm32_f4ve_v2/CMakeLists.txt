add_board(NAME stm32_f4ve_v2
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/BoardContext.cpp
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,,${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals.cpp>
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,,${CMAKE_CURRENT_SOURCE_DIR}/source/symbols.cpp>
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    ARCH
        cortex
    CHIP
        stm32f407ve
    GENERIC_MODULES # Don't care about the chip variant or the configuration
        core
        memory
        segger
        jarnax-lps35hw-driver
        jarnax-w25q16bv-driver
        jarnax-ssd1306-driver
        jarnax-lsm9ds1-driver
    MODULES # Have to know the chip and the configuration
        stm32-spi-driver
        stm32-i2c-driver
        stm32-uart-driver
        stm32-usart-driver
        jarnax
        stm32
    CONFIGURATIONS
        basic # not qemu!
)
