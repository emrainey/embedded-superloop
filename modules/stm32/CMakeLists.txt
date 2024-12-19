add_module(NAME stm32
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/vectors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/clocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/nvic.cpp
        # Objects
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Pin.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Indicator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Button.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/RandomNumberGenerator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/DmaDriver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SpiDriver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Timer.cpp
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
