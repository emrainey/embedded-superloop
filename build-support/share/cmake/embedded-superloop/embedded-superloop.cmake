cmake_minimum_required(VERSION 3.30)

project(embedded-superloop
        DESCRIPTION "Embedded Superloop"
        VERSION 0.3.0
        LANGUAGES CXX ASM)

set(EMBEDDED_SUPERLOOP_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# include(CMakePrintHelpers)
# C++23 with no extensions
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

# C23 with no extensions
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_STANDARD 23)
set(CMAKE_C_STANDARD_REQUIRED TRUE)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
if(BUILD_UNIT_TESTS)
    enable_testing()
endif()

add_subdirectory(third-party) # This is where we find Catch2, GoogleTest, FakeIt, etc.
add_subdirectory(external) # This is where we find staterator, Python venv, etc.

set(BANNER
    "\n"
    "░        ░░  ░░░░  ░░       ░░░        ░░       ░░░       ░░░        ░░       ░░          \n"
    "▒  ▒▒▒▒▒▒▒▒   ▒▒   ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒          \n"
    "▓      ▓▓▓▓        ▓▓       ▓▓▓      ▓▓▓▓  ▓▓▓▓  ▓▓  ▓▓▓▓  ▓▓      ▓▓▓▓  ▓▓▓▓  ▓          \n"
    "█  ████████  █  █  ██  ████  ██  ████████  ████  ██  ████  ██  ████████  ████  █          \n"
    "█        ██  ████  ██       ███        ██       ███       ███        ██       ██          \n"
    "                                                                                          \n"
    "░░      ░░░  ░░░░  ░░       ░░░        ░░       ░░░  ░░░░░░░░░      ░░░░      ░░░       ░░\n"
    "▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒▒▒▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒\n"
    "▓▓      ▓▓▓  ▓▓▓▓  ▓▓       ▓▓▓      ▓▓▓▓       ▓▓▓  ▓▓▓▓▓▓▓▓  ▓▓▓▓  ▓▓  ▓▓▓▓  ▓▓       ▓▓\n"
    "███████  ██  ████  ██  ████████  ████████  ███  ███  ████████  ████  ██  ████  ██  ███████\n"
    "██      ████      ███  ████████        ██  ████  ██        ███      ████      ███  ███████\n"
    " A small embedded super loop firmware system for ARM Cortex-M microcontrollers\n"
    "\n"
)

message(${BANNER})

# This project sets high warning standards, add more as time goes on and compilers improve
add_library(strict INTERFACE)
target_compile_options(strict
    INTERFACE
        -Wall -Wextra -Werror -pedantic
        -Walloca
        -Wcast-align
        -Wcast-align
        -Wcast-qual
        -Wconversion
        -Wctor-dtor-privacy
        -Wdeprecated-copy-dtor
        -Wdouble-promotion
        -Wenum-conversion
        -Wextra-semi
        -Wfloat-equal
        -Wformat-signedness
        -Wformat=2
        -Wmismatched-tags
        -Wmissing-braces
        -Wmultichar
        -Wnon-virtual-dtor
        -Wold-style-cast
        -Woverloaded-virtual
        -Wpointer-arith
        -Wrange-loop-construct
        -Wshadow
        -Wshadow
        -Wsign-conversion
        -Wsuggest-override
        -Wuninitialized
        -Wvla
        -Wwrite-strings
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,-Wframe-larger-than=1024,>
        $<$<CXX_COMPILER_ID:GCC>:-Wcomma-subscript>
        $<$<CXX_COMPILER_ID:GCC>:-Wduplicated-branches>
        $<$<CXX_COMPILER_ID:GCC>:-Wduplicated-cond>
        $<$<CXX_COMPILER_ID:GCC>:-Wformat-overflow=2>
        $<$<CXX_COMPILER_ID:GCC>:-Wlogical-op>
        $<$<CXX_COMPILER_ID:GCC>:-Wlogical-op>
        $<$<CXX_COMPILER_ID:GCC>:-Wnoexcept>
        $<$<CXX_COMPILER_ID:GCC>:-Wrestrict>
        $<$<CXX_COMPILER_ID:GCC>:-Wstrict-null-sentinel>
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-attribute=format>
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-attribute=malloc>
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-final-methods>
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-final-types>
        $<$<CXX_COMPILER_ID:GCC>:-Wvolatile>
        $<$<OR:$<CXX_COMPILER_ID:Clang>,$<CXX_COMPILER_ID:AppleClang>>:-Wno-unknown-attributes>
)

function(set_configuration_name VAR CFG)
    set(${VAR} configuration-${CFG} PARENT_SCOPE)
endfunction()

function(set_module_name VAR NAME CFG CHIP)
    set(${VAR} module-${NAME}-${CFG}-${CHIP} PARENT_SCOPE)
endfunction()

function(set_board_name VAR NAME CFG)
    set(${VAR} board-${NAME}-${CFG} PARENT_SCOPE)
endfunction()

function(set_arch_name VAR NAME CFG CHIP)
    set(${VAR} arch-${NAME}-${CFG}-${CHIP} PARENT_SCOPE)
endfunction()

function(set_chip_name VAR CHIP)
    set(${VAR} chip-${CHIP} PARENT_SCOPE)
endfunction()

function(set_family_name VAR FAMILY)
    set(${VAR} family-${FAMILY} PARENT_SCOPE)
endfunction()

function(set_firmware_name VAR NAME CFG BOARD)
    set(${VAR} firmware-${NAME}-${CFG}-${BOARD} PARENT_SCOPE)
endfunction()

function(set_unit_test_name VAR NAME CFG BOARD)
    # it's prefixed by test to allow easy grepping by VSCode plugins, etc
    set(${VAR} test-${NAME}-${CFG}-${BOARD} PARENT_SCOPE)
endfunction()

function(append_global LIST_NAME VALUE)
    get_property(_value GLOBAL PROPERTY ${LIST_NAME})
    if (NOT _value)
        set_property(GLOBAL PROPERTY ${LIST_NAME} "${VALUE}")
    else()
        list(APPEND _value "${VALUE}")
        set_property(GLOBAL PROPERTY ${LIST_NAME} "${_value}")
    endif()
endfunction()

# Checks to make sure a variable is defined
macro(required)
    foreach (var ${ARGN})
        if(NOT DEFINED ${var})
            message(FATAL_ERROR "Required variable ${var} not defined")
        else()
            message(DEBUG "Found required variable ${var} with value '${${var}}'")
        endif()
    endforeach()
endmacro()

function(inherit_target_properties)
    set(options "")
    set(singles PARENT CHILD)
    set(multiples PROPERTIES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    required(ARG_PARENT ARG_CHILD)

    if (NOT TARGET ${ARG_PARENT})
        message(FATAL_ERROR "No target ${ARG_PARENT} found to inherit properties from")
    endif()
    if (NOT TARGET ${ARG_CHILD})
        message(FATAL_ERROR "No target ${ARG_CHILD} found to inherit properties to")
    endif()

    if(ARG_PROPERTIES)
         message(DEBUG "Inheriting properties ${ARG_PROPERTIES} from ${ARG_CHILD} to ${ARG_PARENT}")
     else()
         message(FATAL_ERROR "No properties ${ARG_PROPERTIES} found on ${ARG_CHILD} to inherit to ${ARG_PARENT}")
     endif()
    foreach (prop IN LISTS ARG_PROPERTIES)
        if(NOT prop MATCHES "^[A-Z_]+$")
            message(FATAL_ERROR "Property ${prop} is not a valid CMake property name")
        endif()

        get_target_property(LOCAL_PROP ${ARG_PARENT} ${prop})
        if (LOCAL_PROP STREQUAL "LOCAL_PROP-NOTFOUND")
            message(FATAL_ERROR "No property ${prop} found on ${ARG_PARENT} to inherit to ${ARG_CHILD}")
        else()
            # does the child already have this property?
            get_target_property(CHILD_PROP ${ARG_CHILD} ${prop})
            if (NOT CHILD_PROP STREQUAL "CHILD_PROP-NOTFOUND")
                message(WARNING "Child ${ARG_CHILD} already has property ${prop} with value ${CHILD_PROP}, skipping inherit from ${ARG_PARENT} with value ${LOCAL_PROP}")
                continue()
            endif()
            message(DEBUG "Inheriting property ${prop} with value '${LOCAL_PROP}' from ${ARG_PARENT} to ${ARG_CHILD}")
            set_target_properties(${ARG_CHILD} PROPERTIES
                ${prop} "${LOCAL_PROP}"
            )
        endif()
    endforeach()
endfunction()

function(print_target_properties)
    set(options "")
    set(singles TARGET)
    set(multiples "")
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    required(ARG_TARGET)

    if(NOT BUILD_PRINT_PROPERTIES)
        return()
    endif()

    message(STATUS "TARGET ${ARG_TARGET} has these properties")

    get_target_property(LOCAL_INTERFACES ${ARG_TARGET} INTERFACE_LINK_LIBRARIES)
    message(STATUS "  <==> ${ARG_TARGET} interfaces: ${LOCAL_INTERFACES}")

    get_target_property(LOCAL_LIBS ${ARG_TARGET} LINK_LIBRARIES)
    message(STATUS "  <=> ${ARG_TARGET} libraries: ${LOCAL_LIBS}")

    get_target_property(LOCAL_INTERFACE_DEFINES ${ARG_TARGET} LINK_INTERFACE_LIBRARIES)
    message(STATUS "  <==> ${ARG_TARGET} link interface defines: ${LOCAL_INTERFACE_DEFINES}")

    get_target_property(LOCAL_INTERFACE_INCLUDES ${ARG_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "  ### ${ARG_TARGET} includes: ${LOCAL_INTERFACE_INCLUDES}")

    get_target_property(LOCAL_INCLUDES ${ARG_TARGET} INCLUDE_DIRECTORIES)
    message(STATUS "  ## ${ARG_TARGET} includes: ${LOCAL_INCLUDES}")

    get_target_property(LOCAL_INTERFACE_COMPILE_DEFINITIONS ${ARG_TARGET} INTERFACE_COMPILE_DEFINITIONS)
    message(STATUS "  !!! ${ARG_TARGET} interface compile definitions: ${LOCAL_INTERFACE_COMPILE_DEFINITIONS}")

    get_target_property(LOCAL_COMPILE_DEFINITIONS ${ARG_TARGET} COMPILE_DEFINITIONS)
    message(STATUS "  !! ${ARG_TARGET} compile definitions: ${LOCAL_COMPILE_DEFINITIONS}")

    get_target_property(LOCAL_CONFIGURATION ${ARG_TARGET} CONFIGURATION)
    message(STATUS "  $$$ ${ARG_TARGET} configuration: ${LOCAL_CONFIGURATION}")

    get_target_property(LOCAL_FAMILY ${ARG_TARGET} FAMILY)
    message(STATUS "  >> ${ARG_TARGET} family: ${LOCAL_FAMILY}")

    get_target_property(LOCAL_VENDOR ${ARG_TARGET} VENDOR)
    message(STATUS "  >> ${ARG_TARGET} vendor: ${LOCAL_VENDOR}")

    get_target_property(LOCAL_CORTEX_M ${ARG_TARGET} CORTEX_M)
    message(STATUS "  >> ${ARG_TARGET} cortex_m: ${LOCAL_CORTEX_M}")

    get_target_property(LOCAL_ARCHITECTURE ${ARG_TARGET} ARCHITECTURE)
    message(STATUS "  >> ${ARG_TARGET} architecture: ${LOCAL_ARCHITECTURE}")

    get_target_property(LOCAL_CHIP ${ARG_TARGET} CHIP)
    message(STATUS "  >> ${ARG_TARGET} chip: ${LOCAL_CHIP}")

    get_target_property(LOCAL_DEVICE ${ARG_TARGET} DEVICE)
    message(STATUS "  >> ${ARG_TARGET} device: ${LOCAL_DEVICE}")

    get_target_property(LOCAL_PACKAGE ${ARG_TARGET} PACKAGE)
    message(STATUS "  >> ${ARG_TARGET} package: ${LOCAL_PACKAGE}")

    get_target_property(LOCAL_VENDOR_LINKERSCRIPT ${ARG_TARGET} VENDOR_LINKERSCRIPT)
    message(STATUS "  == ${ARG_TARGET} vendor linkerscript: ${LOCAL_VENDOR_LINKERSCRIPT}")

    get_target_property(LOCAL_VENDOR_LINKERSCRIPTS ${ARG_TARGET} VENDOR_LINKERSCRIPTS)
    message(STATUS "  == ${ARG_TARGET} vendor linkerscripts: ${LOCAL_VENDOR_LINKERSCRIPTS}")

    get_target_property(LOCAL_BOARD_LINKERSCRIPTS ${ARG_TARGET} BOARD_LINKERSCRIPTS)
    message(STATUS "  == ${ARG_TARGET} board linkerscripts: ${LOCAL_BOARD_LINKERSCRIPTS}")

    get_target_property(LOCAL_ARCH_LINKERSCRIPTS ${ARG_TARGET} ARCH_LINKERSCRIPTS)
    message(STATUS "  == ${ARG_TARGET} arch linkerscripts: ${LOCAL_ARCH_LINKERSCRIPTS}")

endfunction()

# Links each library in the list to TARGET using --whole-archive / --no-whole-archive so
# that every object file in each archive is unconditionally included.  This is required
# when a library's inline code (e.g. inlined destructors that reference vtables) pulls in
# symbols that live in sibling archives which the linker would otherwise skip.
#
# On linkers that support the CMake WHOLE_ARCHIVE link-library feature (CMake >= 3.24,
# GNU ld, lld) the generator-expression form is used.  On others the raw
# -Wl,--whole-archive / -Wl,--no-whole-archive flags are emitted directly.
#
# Usage:
#   target_link_whole_libraries(<target> <lib1> [<lib2> ...])
function(target_link_whole_libraries TARGET)
    if(CMAKE_CXX_LINK_LIBRARY_USING_WHOLE_ARCHIVE_SUPPORTED)
        foreach(lib IN LISTS ARGN)
            target_link_libraries(${TARGET} PRIVATE "$<LINK_LIBRARY:WHOLE_ARCHIVE,${lib}>")
            message(STATUS "Whole-archive linking ${TARGET} to ${lib}")
        endforeach()
    else()
        # Fallback: emit raw linker flags around each archive individually.
        foreach(lib IN LISTS ARGN)
            target_link_libraries(${TARGET} PRIVATE
                "-Wl,--whole-archive" "${lib}" "-Wl,--no-whole-archive"
            )
            message(STATUS "Whole-archive (raw flags) linking ${TARGET} to ${lib}")
        endforeach()
    endif()
endfunction()

include(${CMAKE_CURRENT_LIST_DIR}/configuration.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/family.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/chip.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/architecture.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/board.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/module.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/firmware.cmake)
include(${CMAKE_CURRENT_LIST_DIR}/unittest.cmake)

if(NOT TARGET test AND BUILD_CROSS_TARGET)
    # in this case, there's no test target, so we create a custom target
    add_custom_target(test)
endif()

if(NOT TARGET coverage AND BUILD_COVERAGE)
    add_custom_target(coverage)
    add_dependencies(coverage test)
endif()


# This should be called AFTER all the configuration, family and chips are defined
function(export_properties)
    set(options "")
    set(singles FAMILIES CHIPS CONFIGURATIONS)
    set(multiples "")
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    get_property(${ARG_CONFIGURATIONS} GLOBAL PROPERTY TARGET_CONFIGURATIONS)
    set(${ARG_CONFIGURATIONS} ${${ARG_CONFIGURATIONS}} PARENT_SCOPE)
    message(STATUS "==> configuration targets: ${ARG_CONFIGURATIONS}=${${ARG_CONFIGURATIONS}}")

    get_property(${ARG_FAMILIES} GLOBAL PROPERTY TARGET_FAMILIES)
    set(${ARG_FAMILIES} ${${ARG_FAMILIES}} PARENT_SCOPE)
    message(STATUS "==> family targets: ${ARG_FAMILIES}=${${ARG_FAMILIES}}")

    get_property(${ARG_CHIPS} GLOBAL PROPERTY TARGET_CHIPS)
    set(${ARG_CHIPS} ${${ARG_CHIPS}} PARENT_SCOPE)
    message(STATUS "==> chip targets: ${ARG_CHIPS}=${${ARG_CHIPS}}")
endfunction()
