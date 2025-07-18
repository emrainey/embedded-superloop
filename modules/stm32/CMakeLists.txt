add_module(NAME stm32
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/vectors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/clocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/nvic.cpp
        # Objects
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio/Pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Indicator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/RandomNumberGenerator.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Manager.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/dma/Resource.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/i2c/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/spi/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/uart/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/usart/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Timer2.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/backup.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax-interfaces
    GENERIC_MODULES
        core
    ARCH
        cortex
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
