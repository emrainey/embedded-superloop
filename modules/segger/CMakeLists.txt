add_module(NAME segger
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/segger/rtt.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/modules/cortex/include # HACK!
        # This module doesn't care about configuration or the board,
        # it just needs the path to the thumb header.
    LIBRARIES
        strict
    GENERIC_MODULES
        core memory
    NO_CONFIGURATIONS
)
