host_unit_test(NAME memory
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-strings.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        memory
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)
