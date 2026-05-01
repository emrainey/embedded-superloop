add_firmware(NAME nucleo-demo
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Demo.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    CONFIGURATIONS
        basic
    BOARDS
        nucleo_h753zi
)
