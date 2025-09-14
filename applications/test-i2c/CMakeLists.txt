add_firmware(NAME test-i2c
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/I2CTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)
