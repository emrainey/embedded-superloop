file(GLOB_RECURSE _GENERATED_CORE_TESTS ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests/*.cpp)
list(SORT _GENERATED_CORE_TESTS) # for reproducibility

host_unit_test(NAME core
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-array.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-avl.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-container.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-countdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-doublelink.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-enums.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-folds.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-intervals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-pool.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-ring.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-span.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-statechart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-status.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-tokenizer.cpp
        # ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-units.cpp # requires information from the Configuration and Architecture
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-variants.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-events.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-heap.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-print.cpp
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
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-fraction.cpp
    LIBRARIES
        strict
    GENERIC_MODULES
        core
    GOOGLETEST
    NO_CONFIGURATIONS
    NO_BOARDS
)

generate_statechart(
    YAML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/tests
    YAML_FILE ExampleStateChart.yaml
    GENERATED_DIR ${CMAKE_BINARY_DIR}/generated/core/tests
    TYPES CPP HPP DOT D2 PLANTUML GTEST
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