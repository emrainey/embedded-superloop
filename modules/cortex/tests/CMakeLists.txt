# This is hard-coded for now, but we should make it more flexible in the future
host_unit_test(NAME memory
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-memory.cpp
        ${CMAKE_SOURCE_DIR}/modules/cortex/source/memory.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/modules/cortex/include
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)