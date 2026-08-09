host_unit_test(NAME cyphal-heartbeat
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-cyphal-heartbeat.cpp
    LIBRARIES
        cyphal-dsdl
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME cyphal-getinfo-server
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-cyphal-getinfo-server.cpp
    LIBRARIES
        cyphal-dsdl
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME cyphal-getinfo-client
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-cyphal-getinfo-client.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../source/GetInfoScanner.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/../include
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)
