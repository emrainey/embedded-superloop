host_unit_test(NAME cyphal-heartbeat
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-cyphal-heartbeat.cpp
    LIBRARIES
        cyphal-dsdl
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)
