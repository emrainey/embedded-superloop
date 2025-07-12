
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
        # The startup code
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/on_entry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/zero_bss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/static_constructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/static_destructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/load_data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/watermark_stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/simple_globals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/class_globals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/jump.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/startup/configure.cpp
        # System Functions
        ${CMAKE_CURRENT_SOURCE_DIR}/source/reset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/print.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/yield.cpp
        $<IF:$<BOOL:BUILD_CROSS_TARGET>,${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp,> # Only build in on target builds
        # System Classes
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Ticker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SuperLoop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/CountDown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/StopWatch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/Monitor.cpp
        # Drivers
        # Winbond SPI Flash Driver
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/WinbondDriver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/WinbondStateMachine.cpp
        # SSD1306 OLED Display Driver
        ${CMAKE_CURRENT_SOURCE_DIR}/source/ssd1306.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/ssd1306/Driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/drivers/ssd1306/StateMachine.cpp

    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/include # Internal includes
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core
    MODULES
        segger
    LIBRARIES
        $<IF:$<CXX_COMPILER_ID:GNU>,gcc m,> # GCC specific libraries to provide things like __aeabi_d2f
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)

host_unit_test(NAME test-jarnax-catch
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
        strict core-none-all configuration-basic jarnax-interfaces
    MODULES
        jarnax
    CATCH2
    FAKEIT
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)

host_unit_test(NAME test-jarnax-googletest
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-mocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-coordinator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/gtest-winbondstatemachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/mocks
    LIBRARIES
        strict memory-none-all core-none-all jarnax-interfaces
    MODULES
        jarnax
    GOOGLETEST
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)