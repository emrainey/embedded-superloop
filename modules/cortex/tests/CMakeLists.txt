host_unit_test(NAME cortex-googletest
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-cache.cpp
    INCLUDES
        ${CMAKE_SOURCE_DIR}/modules/jarnax/tests/include
    LIBRARIES
        strict
    GENERIC_MODULES
        memory core
    GOOGLETEST
    CONFIGURATIONS
        basic
    BOARDS
        nucleo_h753zi
)
