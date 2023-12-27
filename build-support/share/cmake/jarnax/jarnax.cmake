cmake_minimum_required(VERSION 3.22)

project(jarnax
        VERSION 0.1.48
        LANGUAGES CXX ASM)

set(JARAX_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
# include(CMakePrintHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_C_STANARD 17)
set(CMAKE_CXX_EXTENSIONS ON)
#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

if (NOT CMAKE_CROSS_BUILD)
enable_testing()
endif()

set(BANNER
"\n"
"░        ░░░      ░░░       ░░░   ░░░  ░░░      ░░░  ░░░░  ░\n"
"▒▒▒▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒  ▒▒▒▒  ▒▒    ▒▒  ▒▒  ▒▒▒▒  ▒▒▒  ▒▒  ▒▒\n"
"▓▓▓▓▓▓▓  ▓▓  ▓▓▓▓  ▓▓       ▓▓▓  ▓  ▓  ▓▓  ▓▓▓▓  ▓▓▓▓    ▓▓▓\n"
"█  ████  ██        ██  ███  ███  ██    ██        ███  ██  ██\n"
"██      ███  ████  ██  ████  ██  ███   ██  ████  ██  ████  █\n"
" A small embedded super loop firmware system for ARM Cortex-M microcontrollers\n"
"\n"
)

message(${BANNER})

# Jarnax sets high warning standards
add_library(strict INTERFACE)
target_compile_options(strict
    INTERFACE
        -Wall -Wextra -Werror -pedantic
        -Wcast-align
        -Wconversion
        -Wsign-conversion
        -Wold-style-cast
        -Wshadow
        $<$<CXX_COMPILER_ID:GCC>:-Wlogical-op>
        -Wsuggest-override
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-final-types>
        $<$<CXX_COMPILER_ID:GCC>:-Wsuggest-final-methods>
)

#
# Creates a firmware target
# @param NAME The name of the firmware
# @param VENDOR The vendor of the firmware
# @param SOURCES The source files for the firmware
# @param INCLUDES The include directories for the firmware
# @param DEFINES The preprocessor definitions for the firmware
# @param LIBRARIES The libraries to link against
# @param LINKERSCRIPT The linker script to use
#
function(add_firmware)
    set(options "")
    set(singles NAME VENDOR LINKERSCRIPT)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT ARG_LINKERSCRIPT)
        set(ARG_LINKERSCRIPT ${CMAKE_SOURCE_DIR}/modules/${ARG_VENDOR}/linkerscripts/gcc.ld)
    endif()
    add_executable(${ARG_NAME}.elf ${ARG_SOURCES})
    target_link_libraries(${ARG_NAME}.elf PUBLIC ${ARG_LIBRARIES} ${COMPILER_MATH_LIB})
    target_include_directories(${ARG_NAME}.elf PRIVATE ${ARG_INCLUDES})
    target_compile_definitions(${ARG_NAME}.elf PRIVATE ${ARG_DEFINES})
    target_compile_options(${ARG_NAME}.elf PRIVATE # -fverbose-asm -save-temps)
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}=. # trims __FILE__ to be relative and deterministic
    )
    if (CMAKE_CROSS_BUILD)
        target_link_options(${ARG_NAME}.elf PRIVATE
            -nostdlib
            # --spec=nosys
            $<$<CXX_COMPILER_ID:GNU>:-Wl,-T,${ARG_LINKERSCRIPT}>
            -Wl,-Map,${CMAKE_BINARY_DIR}/${ARG_NAME}.map
            -Wl,--print-memory-usage
            # -Wl,--print-map
            -Wl,-gc-sections
            -Wl,-cref
        )
        # add_dependencies(${ARG_NAME}.elf ${ARG_NAME}-ld-script)
        set(ARG_ELF ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.elf)
        set(ARG_DISASM ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.s)
        add_custom_command(
            OUTPUT ${ARG_DISASM}
            DEPENDS ${ARG_ELF}
            COMMAND ${CMAKE_OBJDUMP} -d ${ARG_ELF} -marm -C -z > ${ARG_DISASM}
            COMMENT "Creating Dissembly of ${ARG_ELF}"
        )
        # add_dependencies(${ARG_NAME}.elf ${ARG_LINKERSCRIPT})
        add_custom_target(disassembly-${ARG_NAME} DEPENDS ${ARG_DISASM})
        # File the relative path from the build directory to the binary
        file(RELATIVE_PATH ARG_MODULE ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.elf)
        # Generate a debug file for the Ozone debugger for this firmware
        configure_file(${CMAKE_SOURCE_DIR}/scripts/Ozone.jdebug.in ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.jdebug @ONLY)
        add_custom_target(ozone-${ARG_NAME}
            COMMAND /Applications/SEGGER/Ozone/Ozone.app/Contents/MacOS/Ozone ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.jdebug
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.jdebug ${CMAKE_CURRENT_BINARY_DIR}/${ARG_NAME}.elf)
    else()
        target_compile_definitions(${ARG_NAME}.elf
            PUBLIC
                register= # Remove the keyword for compatibility reasons
                UNITTEST)
        target_link_libraries(${ARG_NAME}.elf PUBLIC native)
    endif()
endfunction()


list(APPEND LOCAL_MODULES memory core cortex jarnax segger stm32 board native)

foreach(module IN LISTS LOCAL_MODULES)
add_subdirectory(${JARAX_PROJECT_ROOT}/modules/${module})
endforeach()

# Documentation
find_package(Doxygen)
if (Doxygen_FOUND)
    set(DOXYGEN_GENERATE_HTML YES)
    set(DOXYGEN_GENERATE_MAN NO)
    set(DOXYGEN_PROJECT_BRIEF "A simple C++ only Microcontroller System")
    set(DOXYGEN_USE_MDFILE_AS_MAINPAGE README.md)
    set(DOXYGEN_GENERATE_TREEVIEW YES)
    set(DOXYGEN_DISABLE_SEARCH NO)
    set(DOXYGEN_FULL_SIDEBAR NO)
    set(DOXYGEN_HTML_EXTRA_STYLESHEET doxygen-awesome-css/doxygen-awesome.css)
    set(DOXYGEN_HTML_COLORSTYLE LIGHT)
    set(DOXYGEN_PREDEFINED "__attribute__(x)=")
    set(DOXYGEN_IMAGE_PATH "documentation/images")
    file(GLOB_RECURSE DOXYGEN_INCLUDES
        modules/jarnax/include/**/*.hpp
        modules/core/include/**/*.hpp
        modules/memory/include/**/*.hpp
        modules/cortex/include/**/*.hpp
        modules/stm32/include/**/*.hpp
    )
    file(GLOB_RECURSE DOXYGEN_SOURCES
        modules/jarnax/source/*.cpp
        modules/core/source/*.cpp
        modules/memory/source/*.cpp
        modules/cortex/source/*.cpp
        modules/stm32/source/*.cpp
    )
    # message(STATUS "DOXYGEN_INCLUDES=${DOXYGEN_INCLUDES}")
    # message(STATUS "DOXYGEN_SOURCES=${DOXYGEN_SOURCES}")
    doxygen_add_docs(docs
        #FILES
        README.md
        ${DOXYGEN_INCLUDES}
        ${DOXYGEN_SOURCES}
        USE_STAMP_FILE
        COMMENT "Doxygen Generation")
endif()
