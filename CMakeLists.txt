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


# Create the CMake Project Variables as a Header
configure_file(${CMAKE_SOURCE_DIR}/include/cmake.hpp.in
    ${CMAKE_BINARY_DIR}/generated/include/cmake.hpp)

# Parse the Git information and create a header with that information
find_package(Git REQUIRED)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse --short=7 HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_SHORT_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} rev-parse HEAD
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_FULL_HASH
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
execute_process(
    COMMAND ${GIT_EXECUTABLE} describe --tags --abbrev=32
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE GIT_TAG
    OUTPUT_STRIP_TRAILING_WHITESPACE
)
# Force Everyone to include the generated header location
include_directories(${CMAKE_BINARY_DIR}/generated/include)

# Inform all binaries what the Git information is at compile time, so it can be used in the application for logging or displaying version information.
add_compile_options(-DGIT_SHORT_HASH="${GIT_SHORT_HASH}" -DGIT_FULL_HASH="${GIT_FULL_HASH}" -DGIT_TAG="${GIT_TAG}")

if ((CMAKE_CXX_COMPILER_ID STREQUAL "GNU" AND CMAKE_CXX_COMPILER_VERSION VERSION_GREATER_EQUAL 11)
    OR (CMAKE_CXX_COMPILER_ID MATCHES "Clang" AND CMAKE_SYSTEM_NAME STREQUAL "Linux"))
    message(STATUS "Using C++ Link Group with RESCAN")
    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN_SUPPORTED TRUE)
    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN
        "LINKER:--start-group"
        "LINKER:--end-group")
else()
    message(STATUS "Not using C++ Link Group with RESCAN")
    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN_SUPPORTED FALSE)

    set(CMAKE_CXX_LINK_GROUP_USING_RESCAN FALSE)
endif()
set(CMAKE_CXX_SCAN_FOR_MODULES OFF)

# set(CMAKE_CXX_SCAN_FOR_MODULES ON)
add_custom_target(scrub
    COMMAND ${CMAKE_COMMAND} -E remove_directory ${CMAKE_BINARY_DIR}
    COMMENT "Cleaning up build directories")

find_package(embedded-superloop REQUIRED)

############

add_configuration(NAME full)
add_configuration(NAME basic)
add_configuration(NAME qemu)

add_family(FAMILY stm32f4xx
    VENDOR stm32
    DESCRIPTION "ST STM32F4xx family"
    MODULES stm32
    CORTEX_M 4
    ARCHITECTURE armv7e-m
    PRECISION SINGLE
    NAMESPACE f4xx
)

add_chip(NAME stm32f407ve
    FAMILY stm32f4xx
    DEVICE STM32F407VE
    PACKAGE LQFP100
    DEFINES CORTEX_INTERRUPT_CHANNELS=82
)

add_chip(NAME stm32f405rg
    FAMILY stm32f4xx
    DEVICE STM32F405RG
    PACKAGE LQFP64
    DEFINES CORTEX_INTERRUPT_CHANNELS=82
)

add_family(FAMILY stm32h7xx
    VENDOR stm32
    DESCRIPTION "ST STM32H7xx family"
    MODULES stm32
    CORTEX_M 7
    ARCHITECTURE armv7e-m
    PRECISION DOUBLE
    NAMESPACE h7xx
    DEFINES STM32H7_REV_V
)

add_chip(NAME stm32h753zi
    FAMILY stm32h7xx
    DEVICE STM32H753ZI
    PACKAGE LQFP144
    DEFINES CORTEX_INTERRUPT_CHANNELS=150
)

# After we define all the chips, families and configurations,
# we can export the properties so that every module doesn't have to
# list every combination of everything.

export_properties(
    CONFIGURATIONS TARGET_CONFIGURATIONS
    FAMILIES TARGET_FAMILIES
    CHIPS TARGET_CHIPS
)

# The following definitions control which subdirectories are included in the build, they don't define targets
# The subdirectories are added in the order they are listed here
# TODO scan and include automatically!
list(APPEND LOCAL_MODULES memory core segger cortex stm32 jarnax native) # These depend on config and board, but also has test dependencies on boards which don't exist yet.
list(APPEND LOCAL_BOARDS stm32_f4ve_v2 netduinoplus2 nucleo_h753zi)
list(APPEND LOCAL_APPLICATIONS simple test-timers test-i2c test-ssd1306 test-usart test-spi test-lps35hw test-debug unittests nucleo-demo)
list(APPEND LOCAL_UNITTESTS core cortex stm32 jarnax) # these have unit tests
# Pulls in each module!
foreach(module IN LISTS LOCAL_MODULES)
    add_subdirectory(${EMBEDDED_SUPERLOOP_PROJECT_ROOT}/modules/${module})
endforeach()

# Pulls in each board!
foreach(board IN LISTS LOCAL_BOARDS)
    add_subdirectory(${EMBEDDED_SUPERLOOP_PROJECT_ROOT}/boards/${board})
endforeach()

# Pulls in each application!
foreach(app IN LISTS LOCAL_APPLICATIONS)
    add_subdirectory(${EMBEDDED_SUPERLOOP_PROJECT_ROOT}/applications/${app})
endforeach()

# Pulls in the Unit Tests
foreach(test IN LISTS LOCAL_UNITTESTS)
    if (EXISTS ${EMBEDDED_SUPERLOOP_PROJECT_ROOT}/modules/${test}/tests/CMakeLists.txt)
        add_subdirectory(${EMBEDDED_SUPERLOOP_PROJECT_ROOT}/modules/${test}/tests)
    endif()
endforeach()

# Write the accumulated debug targets to a JSON file
get_property(ACCUMULATED_DEBUG_TARGETS GLOBAL PROPERTY CROSS_DEBUG_TARGETS)
string(REPLACE ";" ",\n" ACCUMULATED_TARGETS_JSON "${ACCUMULATED_DEBUG_TARGETS}")
set(JSON_CONTENT "[\n${ACCUMULATED_TARGETS_JSON}\n]\n")
file(WRITE "${CMAKE_BINARY_DIR}/debug_targets.json" "${JSON_CONTENT}")

# Generate .vscode/launch.json on configure and as a custom target
add_custom_target(generate-launch-json
    COMMAND ${STATERATOR_PYTHON} ${CMAKE_SOURCE_DIR}/scripts/generate_launch_json.py --build-dir ${CMAKE_BINARY_DIR}
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    COMMENT "Generating .vscode/launch.json from build targets"
)

if(NOT ENV{CI})
    # Run the generator script at configure time to automatically update launch.json
    execute_process(
        COMMAND ${STATERATOR_PYTHON} ${CMAKE_SOURCE_DIR}/scripts/generate_launch_json.py --build-dir ${CMAKE_BINARY_DIR}
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE GENERATE_LAUNCH_JSON_RESULT
    )
    if(NOT GENERATE_LAUNCH_JSON_RESULT EQUAL 0)
        message(WARNING "Failed to generate .vscode/launch.json")
    endif()
endif()

