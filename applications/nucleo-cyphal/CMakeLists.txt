add_firmware(NAME nucleo-cyphal
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/CyphalApp.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        hypha-ip
        udpard
    CONFIGURATIONS
        basic
    BOARDS
        nucleo_h753zi
)
