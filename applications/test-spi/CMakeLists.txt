add_firmware(NAME test-spi
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SPITest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
