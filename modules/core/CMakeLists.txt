# Generates a bunch of header files based on the UNIT_COMBOS list
unset(UNIT_COMBOS)
list(APPEND UNIT_COMBOS Amperes:float:1)
list(APPEND UNIT_COMBOS Celsius:float:1)
list(APPEND UNIT_COMBOS CubicMeters:float:3)
list(APPEND UNIT_COMBOS Degrees:float:1)
list(APPEND UNIT_COMBOS Gauss:float:1)
list(APPEND UNIT_COMBOS Hertz:uint32_t:1)
list(APPEND UNIT_COMBOS Iota:uint64_t:1)
list(APPEND UNIT_COMBOS Meters:float:1)
list(APPEND UNIT_COMBOS MicroSeconds:uint64_t:1)
list(APPEND UNIT_COMBOS MilliSeconds:uint32_t:1)
list(APPEND UNIT_COMBOS Ohms:float:1)
list(APPEND UNIT_COMBOS Pascals:float:1)
list(APPEND UNIT_COMBOS Seconds:float:1)
list(APPEND UNIT_COMBOS SquareMeters:float:2)
list(APPEND UNIT_COMBOS Ticks:uint32_t:1)
list(APPEND UNIT_COMBOS Volts:float:1)
list(APPEND UNIT_COMBOS Watts:float:1)

foreach(combo IN LISTS UNIT_COMBOS)
    string(REPLACE ":" ";" combo ${combo})
    list(GET combo 0 UNIT_NAME)
    list(GET combo 1 UNIT_STORAGE)
    list(GET combo 2 UNIT_POWER)
    set(_UNIT_HEADER ${CMAKE_CURRENT_SOURCE_DIR}/generated/include/core/units/${UNIT_NAME}.hpp)
    message(STATUS "Generating ${_UNIT_HEADER}")
    configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/Unit.in
        ${_UNIT_HEADER}
        @ONLY)
    set(_UNIT_TEST_FILE ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests/${UNIT_NAME}.cpp)
    message(STATUS "Generating ${_UNIT_TEST_FILE}")

    if(${UNIT_STORAGE} STREQUAL "float")
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UnitTest.float.in
            ${_UNIT_TEST_FILE}
            @ONLY)
    else()
        configure_file(${CMAKE_CURRENT_SOURCE_DIR}/cmake/UnitTest.unsigned.in
            ${_UNIT_TEST_FILE}
            @ONLY)
    endif()
endforeach()

# Creates the core module, doesn't depend on any configuration or board.
# Any configuration must be passed in as DEFINES
add_module(NAME core
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/new.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/eabi.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/constexpr_tests.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Status.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Allocator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/CountDown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/vsnprint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Intervals.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/include # for generated headers like Units above
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/tests/include,>
    DEFINES
        DEFAULT_ALLOCATION_BLOCK_SIZE=32
        DEFAULT_ALLOCATION_BLOCK_COUNT=1024
    GENERIC_MODULES
        memory
    LIBRARIES
        $<$<CXX_COMPILER_ID:GNU>:gcc>
        $<$<CXX_COMPILER_ID:GNU>:m> # GCC specific libraries to provide things like __aeabi_d2f
    NO_CONFIGURATIONS
)

generate_statechart(
    YAML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tests
    YAML_FILE ExampleStateChart.yaml
    GENERATED_DIR ${CMAKE_BINARY_DIR}/generated/core/tests
    TYPES CPP HPP DOT D2 PLANTUML GTEST
)
