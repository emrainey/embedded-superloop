add_module(NAME segger
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/segger/rtt.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    GENERIC_MODULES
        core
    MODULES
        stm32
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
