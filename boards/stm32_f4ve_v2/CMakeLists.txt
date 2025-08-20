add_board(NAME stm32_f4ve_v2
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/BoardContext.cpp
        $<IF:$<BOOL:BUILD_CROSS_TARGET>,${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals.cpp,>
        $<IF:$<BOOL:BUILD_CROSS_TARGET>,${CMAKE_CURRENT_SOURCE_DIR}/source/symbols.cpp,>
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    CHIP # the module with the chip definitions
        stm32
    DEVICE
        stm32f407ve
    GENERIC_MODULES
        memory
    MODULES
        stm32 segger jarnax
        stm32-spi-driver
        stm32-i2c-driver
        stm32-uart-driver
        stm32-usart-driver
        jarnax-lps35hw-driver
        jarnax-w25q16bv-driver
        jarnax-ssd1306-driver
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
)
