add_firmware(NAME test-ssd1306
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/DisplayTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    DEFINES
        DEBUG_MASK=0x0000000200030217ULL
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)
