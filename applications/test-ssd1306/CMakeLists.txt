add_firmware(NAME test-ssd1306
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/DisplayTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../../modules/jarnax/source/ssd1306.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
