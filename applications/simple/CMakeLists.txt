add_firmware(NAME spi-demo
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Demo.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
