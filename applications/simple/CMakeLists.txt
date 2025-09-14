add_firmware(NAME simple
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Demo.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)
