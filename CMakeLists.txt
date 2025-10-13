cmake_minimum_required(VERSION 3.28)

project(embedded-superloop-jarnax
        VERSION 0.3.0
        LANGUAGES CXX ASM)

option(BUILD_UNIT_TESTS "Build unit tests" ON)
option(BUILD_DOCUMENTATION "Build documentation" OFF)
option(BUILD_COVERAGE "Build with coverage support" OFF)
option(BUILD_SHARED_LIBS "Build modules as shared libraries" OFF)
option(BUILD_CROSS_TARGET "Build for a cross target" OFF)
option(BUILD_PRINT_PROPERTIES "Print the dependency tree during the build" OFF)

set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANDARD 17)

set(CMAKE_CXX_LINK_GROUP_USING_RESCAN_SUPPORTED TRUE)
if (CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
    message(STATUS "Using GNU C++ Link Group with RESCAN")
    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN
        "LINKER:--start-group"
        "LINKER:--end-group")
else()
    message(STATUS "Not using GNU C++ Link Group with RESCAN")
    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN FALSE)
endif()

# set(CMAKE_CXX_SCAN_FOR_MODULES ON)
add_custom_target(scrub
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up build directories")

# The following definitions control which subdirectories are included in the build, they don't define targets
# The subdirectories are added in the order they are listed here
list(APPEND LOCAL_MODULES memory core) # These don't depend on anything
list(APPEND LOCAL_MODULES cortex stm32 segger jarnax native) # These depend on config and board
list(APPEND LOCAL_APPLICATIONS simple test-timers test-i2c test-ssd1306 test-usart test-spi test-lps35hw test-debug unittests)
list(APPEND LOCAL_CONFIGURATIONS basic qemu)
list(APPEND LOCAL_CHIPS stm32f407ve stm32f405rg)
list(APPEND LOCAL_BOARDS stm32_f4ve_v2 netduinoplus2)

add_subdirectory(external) # This is where we find Catch2, GoogleTest, etc.

find_package(embedded-superloop REQUIRED)
message(STATUS "embedded-superloop found: ${embedded-superloop_VERSION}")
message(STATUS "==> family targets: ${FAMILY_TARGETS}")
message(STATUS "==> chip targets: ${CHIP_TARGETS}")
message(STATUS "==> architecture targets: ${ARCHITECTURE_TARGETS}")

message(STATUS BUILD_CROSS_TARGET=${BUILD_CROSS_TARGET})
