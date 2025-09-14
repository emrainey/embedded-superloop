cmake_minimum_required(VERSION 3.30)

project(embedded-superloop
        DESCRIPTION "Embedded Superloop"
        VERSION 0.3.0
        LANGUAGES CXX ASM)

set(EMBEDDED_SUPERLOOP_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})

# include(CMakePrintHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANARD 17)
set(CMAKE_CXX_EXTENSIONS ON)

# set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)
if(BUILD_UNIT_TESTS)
    enable_testing()
endif()

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

    get_target_property(LOCAL_INTERFACES ${LOCAL_TARGET} INTERFACE_LINK_LIBRARIES)
    message(STATUS "  <==> ${LOCAL_TARGET} interfaces: ${LOCAL_INTERFACES}")

    get_target_property(LOCAL_LIBS ${LOCAL_TARGET} LINK_LIBRARIES)
    message(STATUS "  <=> ${LOCAL_TARGET} libraries: ${LOCAL_LIBS}")

    get_target_property(LOCAL_INTERFACE_DEFINES ${LOCAL_TARGET} LINK_INTERFACE_LIBRARIES)
    message(STATUS "  <==> ${LOCAL_TARGET} link interface defines: ${LOCAL_INTERFACE_DEFINES}")

    get_target_property(LOCAL_INTERFACE_INCLUDES ${LOCAL_TARGET} INTERFACE_INCLUDE_DIRECTORIES)
    message(STATUS "  ### ${LOCAL_TARGET} includes: ${LOCAL_INTERFACE_INCLUDES}")

    get_target_property(LOCAL_INCLUDES ${LOCAL_TARGET} INCLUDE_DIRECTORIES)
    message(STATUS "  ## ${LOCAL_TARGET} includes: ${LOCAL_INCLUDES}")

    get_target_property(LOCAL_INTERFACE_COMPILE_DEFINITIONS ${LOCAL_TARGET} INTERFACE_COMPILE_DEFINITIONS)
    message(STATUS "  !!! ${LOCAL_TARGET} interface compile definitions: ${LOCAL_INTERFACE_COMPILE_DEFINITIONS}")

    get_target_property(LOCAL_COMPILE_DEFINITIONS ${LOCAL_TARGET} COMPILE_DEFINITIONS)
    message(STATUS "  !! ${LOCAL_TARGET} compile definitions: ${LOCAL_COMPILE_DEFINITIONS}")

    get_target_property(LOCAL_CONFIGURATION ${LOCAL_TARGET} CONFIGURATION)
    message(STATUS "  $$$ ${LOCAL_TARGET} configuration: ${LOCAL_CONFIGURATION}")

    get_target_property(LOCAL_FAMILY ${LOCAL_TARGET} FAMILY)
    message(STATUS "  >> ${LOCAL_TARGET} family: ${LOCAL_FAMILY}")

    get_target_property(LOCAL_VENDOR ${LOCAL_TARGET} VENDOR)
    message(STATUS "  >> ${LOCAL_TARGET} vendor: ${LOCAL_VENDOR}")

    get_target_property(LOCAL_CORTEX_M ${LOCAL_TARGET} CORTEX_M)
    message(STATUS "  >> ${LOCAL_TARGET} cortex_m: ${LOCAL_CORTEX_M}")

    get_target_property(LOCAL_ARCHITECTURE ${LOCAL_TARGET} ARCHITECTURE)
    message(STATUS "  >> ${LOCAL_TARGET} architecture: ${LOCAL_ARCHITECTURE}")

    get_target_property(LOCAL_CHIP ${LOCAL_TARGET} CHIP)
    message(STATUS "  >> ${LOCAL_TARGET} chip: ${LOCAL_CHIP}")

    get_target_property(LOCAL_DEVICE ${LOCAL_TARGET} DEVICE)
    message(STATUS "  >> ${LOCAL_TARGET} device: ${LOCAL_DEVICE}")

    get_target_property(LOCAL_PACKAGE ${LOCAL_TARGET} PACKAGE)
    message(STATUS "  >> ${LOCAL_TARGET} package: ${LOCAL_PACKAGE}")

    get_target_property(LOCAL_VENDOR_LINKERSCRIPT ${LOCAL_TARGET} VENDOR_LINKERSCRIPT)
    message(STATUS "  == ${LOCAL_TARGET} vendor linkerscript: ${LOCAL_VENDOR_LINKERSCRIPT}")

    get_target_property(LOCAL_VENDOR_LINKERSCRIPTS ${LOCAL_TARGET} VENDOR_LINKERSCRIPTS)
    message(STATUS "  == ${LOCAL_TARGET} vendor linkerscripts: ${LOCAL_VENDOR_LINKERSCRIPTS}")

    get_target_property(LOCAL_BOARD_LINKERSCRIPTS ${LOCAL_TARGET} BOARD_LINKERSCRIPTS)
    message(STATUS "  == ${LOCAL_TARGET} board linkerscripts: ${LOCAL_BOARD_LINKERSCRIPTS}")

    get_target_property(LOCAL_ARCH_LINKERSCRIPTS ${LOCAL_TARGET} ARCH_LINKERSCRIPTS)
    message(STATUS "  == ${LOCAL_TARGET} arch linkerscripts: ${LOCAL_ARCH_LINKERSCRIPTS}")

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
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/applications/${app})
endforeach()

# Documentation
find_package(Doxygen)

if(Doxygen_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_PROJECT_BRIEF "A simple C++ only Microcontroller System")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_DISABLE_SEARCH NO)
    set(DOXYGEN_FULL_SIDEBAR NO)
    set(DOXYGEN_HTML_EXTRA_STYLESHEET documentation/doxygen-awesome-css/doxygen-awesome.css)
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_PREDEFINED "__attribute__(x)=")
    set(DOXYGEN_IMAGE_PATH "documentation/images")

    foreach(_mod IN LISTS LOCAL_MODULES)
        file(GLOB_RECURSE _MOD_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/modules/${_mod}/include/**/*.hpp)
        list(APPEND DOXYGEN_INCLUDES ${_MOD_INCLUDES})
        file(GLOB_RECURSE _MOD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/${_mod}/source/*.cpp)
        list(APPEND DOXYGEN_SOURCES ${_MOD_SOURCES})
    endforeach()

    # message(STATUS "DOXYGEN_INCLUDES=${DOXYGEN_INCLUDES}")
    # message(STATUS "DOXYGEN_SOURCES=${DOXYGEN_SOURCES}")
    doxygen_add_docs(docs

        # FILES
        README.md
        ${DOXYGEN_INCLUDES}
        ${DOXYGEN_SOURCES}
        USE_STAMP_FILE
        COMMENT "Doxygen Generation")
endif()
