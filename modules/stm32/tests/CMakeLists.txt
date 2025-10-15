## Unit Tests

host_unit_test(NAME stm32-i2c
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-stm32-i2c.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    MODULES
        jarnax stm32 stm32-i2c-driver
    GOOGLETEST
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)

host_unit_test(NAME stm32-spi
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-stm32-spi.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    MODULES
        jarnax stm32 stm32-spi-driver
    GOOGLETEST
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)
