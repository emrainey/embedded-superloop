
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
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/on_entry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/zero_bss.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/static_constructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/static_destructors.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/load_data.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/watermark_stack.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/simple_globals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/class_globals.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/configure.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/reset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/print.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/ticker.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/yield.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SuperLoop.cpp
        $<IF:$<BOOL:CMAKE_CROSS_BUILD>,${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp,> # Only build in on target builds
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

host_unit_test(NAME test-jarnax
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/yieldable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/superloop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/transactable.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/tests/include
    LIBRARIES
        strict core-none-all configuration-basic jarnax-interfaces
    MODULES
        jarnax
    CATCH2
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
