add_board(NAME netduinoplus2
    DISABLE
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
        stm32f405rg
    GENERIC_MODULES # Don't care about the chip variant or the configuration
        core
        memory
        segger
    MODULES # Have to know the chip and the configuration
        stm32-spi-driver
        stm32-uart-driver
        stm32-usart-driver
        jarnax
        stm32
    CONFIGURATIONS
        qemu # not basic!
)
