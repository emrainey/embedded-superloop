add_board(NAME nucleo_h753zi
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/BoardContext.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    ARCH
        cortex
    CHIP
        stm32h753zi
    GENERIC_MODULES # Don't care about the chip variant or the configuration
        core
        memory
        segger
        jarnax-lps35hw-driver
        jarnax-w25q16bv-driver
        jarnax-ssd1306-driver
        jarnax-lsm9ds1-driver
        jarnax-lan8742a-driver
    MODULES # Have to know the chip and the configuration
        stm32-spi-driver
        stm32-i2c-driver
        # stm32-uart-driver # no UARTs on the H753ZI, only USART
        stm32-usart-driver
        stm32-ethernet-driver
        jarnax
        stm32
    CONFIGURATIONS
        basic # not qemu!
)
