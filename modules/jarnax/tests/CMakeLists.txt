host_unit_test(NAME jarnax-catch
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-countdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-yieldable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-superloop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-stopwatch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-transactable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/catch2-ssd1306.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
    LIBRARIES
        strict
        jarnax-interfaces
    GENERIC_MODULES
        memory core
    MODULES
        jarnax
    CATCH2
    FAKEIT
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)

host_unit_test(NAME jarnax-googletest
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-mocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-coordinator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-w25q16bv-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-lps35hw-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-lsm9ds1-statemachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    MODULES
        jarnax
    GOOGLETEST
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)