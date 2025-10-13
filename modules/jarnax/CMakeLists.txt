
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/jarnax/version.hpp.in
    ${CMAKE_CURRENT_BINARY_DIR}/include/jarnax/version.hpp)

# Drivers and other modules that are not part of the jarnax module but need it's interface definitions take
# a dependency on this library.
add_library(jarnax-interfaces INTERFACE)
target_include_directories(jarnax-interfaces INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)

add_module(NAME jarnax
    SOURCES
        # These implement features required by the cortex module
        ${CMAKE_CURRENT_SOURCE_DIR}/source/configure.cpp
        # these are the core jarnax features
        ${CMAKE_CURRENT_SOURCE_DIR}/source/print.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/yield.cpp
        # The main application and Jarnax features
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp,> # Only build in on target builds
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Ticker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SuperLoop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/CountDown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/StopWatch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Monitor.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Driver.cpp
        # Driver infrastructure
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/i2c/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/spi/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/services/UsartConsole.cpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks,>
        $<IF:$<BOOL:${BUILD_UNIT_TESTS}>,${CMAKE_CURRENT_SOURCE_DIR}/tests/include,>
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
        segger
    LIBRARIES
        # $<IF:$<CXX_COMPILER_ID:GNU>,gcc m,> # GCC specific libraries to provide things like __aeabi_d2f
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    ARCH
        cortex
    CHIPS
        ${LOCAL_CHIPS}
)

add_module(NAME jarnax-ssd1306-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/ssd1306.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/ssd1306/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/ssd1306/StateMachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    NO_CONFIGURATIONS
)

add_module(NAME jarnax-w25q16bv-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/w25q16bv/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/w25q16bv/StateMachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    NO_CONFIGURATIONS
)

add_module(NAME jarnax-lps35hw-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/lps35hw/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/lps35hw/StateMachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    NO_CONFIGURATIONS
)

generate_statechart(
    YAML_ROOT ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/lsm9ds1/ag/
    YAML_FILE StateChart.yaml
    GENERATED_DIR ${CMAKE_CURRENT_SOURCE_DIR}/generated/drivers/lsm9ds1/ag/
    TYPES CPP HPP PLANTUML GTEST
)

add_module(NAME jarnax-lsm9ds1-driver
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/lsm9ds1/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/lsm9ds1/StateChart.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/generated/drivers/lsm9ds1/ag/StateChart.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    NO_CONFIGURATIONS
    NO_BOARDS
)

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
    NO_BOARDS
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
    NO_BOARDS
)