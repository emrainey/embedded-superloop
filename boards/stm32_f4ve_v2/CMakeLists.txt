add_board(NAME stm32_f4ve_v2
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/board.cpp
        $<IF:$<BOOL:CMAKE_CROSS_BUILD>,${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals.cpp,>
        $<IF:$<BOOL:CMAKE_CROSS_BUILD>,${CMAKE_CURRENT_SOURCE_DIR}/source/symbols.cpp,>
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    CHIP # the module with the chip definitions
        stm32
    DEVICE
        stm32f407ve
    GENERIC_MODULES
        memory
    MODULES
        stm32 segger
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
)
