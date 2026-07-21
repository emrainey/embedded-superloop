add_module(NAME stm32
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/vectors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/power.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/clocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio/Pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Conversions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Indicator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/RandomNumberGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Resource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Timer2.cpp
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/peripherals.cpp,>
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        # Add the tests/mocks/ folder if the build is for unit testing
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks,>
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32f405rg stm32f407ve
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/vectors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/power.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/clocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio/Pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Conversions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Indicator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/RandomNumberGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Resource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Timer2.cpp
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/peripherals.cpp,>
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        # Add the tests/mocks/ folder if the build is for unit testing
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks,>
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32h753zi
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)


add_module(NAME stm32-spi-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/spi/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32f405rg stm32f407ve
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)


add_module(NAME stm32-spi-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/spi/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32h753zi
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)


add_module(NAME stm32-i2c-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/i2c/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32f405rg stm32f407ve
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32-i2c-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/i2c/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32h753zi
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32-uart-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/uart/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32f405rg stm32f407ve
        # stm32h753zi doesn't have any!
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32-usart-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32f4xx/usart/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32f405rg stm32f407ve
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32-usart-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/usart/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32h753zi
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)

add_module(NAME stm32-ethernet-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32h7xx/ethernet/Driver.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CHIPS
        stm32h753zi
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)
