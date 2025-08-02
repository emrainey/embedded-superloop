add_board(NAME netduinoplus2
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
        stm32f405rg
    GENERIC_MODULES
        memory
    MODULES
        stm32 segger jarnax
        stm32-i2c-driver
        stm32-spi-driver
        stm32-uart-driver
        stm32-usart-driver
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
)
