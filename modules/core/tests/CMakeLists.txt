file(GLOB_RECURSE _GENERATED_CORE_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests/*.cpp)
list(SORT _GENERATED_CORE_TESTS) # for reproducibility

host_unit_test(NAME core
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-avl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-container.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-conversions.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-countdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-doublelink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-enums.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-folds.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-intervals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-pool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-ring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-span.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-split.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-statechart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-status.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-tokenizer.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/catch2-units.cpp # requires information from the Configuration and Architecture
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-variants.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-vsnprint.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/conversions.cpp
        ${_GENERATED_CORE_TESTS}
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME events
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-events.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME heap
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-buffer.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-heap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-print.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    FAKEIT
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME fraction
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-fraction.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    GOOGLETEST
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME generated-statechart
    SOURCES
        ${CMAKE_BINARY_DIR}/generated/core/tests/gtest_ExampleStateChart.cpp
        ${CMAKE_BINARY_DIR}/generated/core/tests/ExampleStateChart.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    GOOGLETEST
    NO_CONFIGURATIONS
    NO_BOARDS
)

# This is hard-coded for now, but we should make it more flexible in the future
host_unit_test(NAME bounds-checker
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-boundschecker.cpp
        ${CMAKE_SOURCE_DIR}/modules/core/source/BoundsChecker.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    CATCH2
    NO_CONFIGURATIONS
    NO_BOARDS
)
