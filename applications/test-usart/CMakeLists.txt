add_firmware(NAME test-usart
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/UsartTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)
