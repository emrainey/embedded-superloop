add_family(FAMILY stm32f40x
    VENDOR stm32
    DESCRIPTION "ST STM32F4xx family"
    MODULES stm32
    CORTEX_M 4
    ARCHITECTURE armv7e-m
)

add_chip(CHIP stm32f407ve
    FAMILY stm32f40x
    DEVICE STM32F407VE
    PACKAGE LQFP100
)

add_chip(CHIP stm32f405rg
    FAMILY stm32f40x
    DEVICE STM32F405RG
    PACKAGE LQFP64
)

# The set of all cortex source files
set(CORTEX_SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/source/vectors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/globals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/trigger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/swo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/nvic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/mpu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/memory.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/spinhalt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/bist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ticks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/conversions.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/clocks.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/semihosting.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/on_startup.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/zero_bss.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/watermark_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/static_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/static_destructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/load_data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/dummy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/tick.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/entry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/non_maskable_interrupt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/hard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/bus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/memory_management.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/usage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/supervisor/call.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/supervisor/pending.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/dummy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/get_exception_frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/bist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/deescalate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/escalate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/query.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/restore.cpp
)

add_architecture(NAME cortex
    SOURCES
        ${CORTEX_SOURCES}
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    CHIPS
        stm32f405rg stm32f407ve
    GENERIC_MODULES
        core
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    SYSTEM
        jarnax
)

# if (NOT BUILD_CROSS_TARGET)
# add_architecture(NAME host
#     SOURCES
#         ${CORTEX_SOURCES}
#     INCLUDES
#         ${CMAKE_CURRENT_SOURCE_DIR}/include
#     CHIPS
#         all
#     CONFIGURATIONS
#         ${LOCAL_CONFIGURATIONS}
#     SYSTEM
#         jarnax
# )
# endif()

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