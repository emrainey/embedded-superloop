# This is hard-coded for now, but we should make it more flexible in the future
host_unit_test(NAME memory
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-memory.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/memory.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/modules/stm32/include # HACK For the stm32 as vendor
    DEFINES
        CORTEX_M=4 # HACK For the cortex as architecture
        STM32F407VE=1 # HACK For the stm32 as vendor
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)