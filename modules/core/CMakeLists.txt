
# Generates a bunch of header files based on the UNIT_COMBOS list
unset(UNIT_COMBOS)
list(APPEND UNIT_COMBOS Volts:float:1)
list(APPEND UNIT_COMBOS Amperes:float:1)
list(APPEND UNIT_COMBOS Volts:float:1)
list(APPEND UNIT_COMBOS Watts:float:1)
list(APPEND UNIT_COMBOS Ohms:float:1)
list(APPEND UNIT_COMBOS Hertz:uint32_t:1)
list(APPEND UNIT_COMBOS Ticks:uint32_t:1)
list(APPEND UNIT_COMBOS Iota:uint64_t:1)
list(APPEND UNIT_COMBOS Seconds:float:1)
list(APPEND UNIT_COMBOS MicroSeconds:uint64_t:1)
list(APPEND UNIT_COMBOS Meters:float:1)
list(APPEND UNIT_COMBOS SquareMeters:float:2)
list(APPEND UNIT_COMBOS CubicMeters:float:3)
foreach (combo IN LISTS UNIT_COMBOS)
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
    if (${UNIT_STORAGE} STREQUAL "float")
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
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/include # for generated headers like Units above
    DEFINES
        DEFAULT_ALLOCATION_BLOCK_SIZE=32
        DEFAULT_ALLOCATION_BLOCK_COUNT=1024
    MODULES
        memory
    LIBRARIES
        configuration-none
    NO_CONFIGURATIONS
    NO_BOARDS
)

file(GLOB_RECURSE _GENERATED_CORE_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests/*.cpp)
list(SORT _GENERATED_CORE_TESTS) # for reproducibility

host_unit_test(NAME test-core
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/avl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/container.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/doublelink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/enums.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/folds.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/intervals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/pool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/ring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/span.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/status.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/units.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/variants.cpp
        ${_GENERATED_CORE_TESTS}
    LIBRARIES
        strict core-none-all
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME test-events
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/events.cpp
    LIBRARIES
        strict core-none-all
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME test-heap
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/heap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/print.cpp
    LIBRARIES
        strict core-none-all
    CATCH2
    FAKEIT
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME test-fraction
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/fraction.cpp
    LIBRARIES
        strict core-none-all
    GOOGLETEST
    NO_CONFIGURATIONS
    NO_BOARDS
)