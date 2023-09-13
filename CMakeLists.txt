cmake_minimum_required(VERSION 3.22)

project(jarnax
        VERSION 0.1.48
        LANGUAGES CXX ASM)

# include(CMakePrintHelpers)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

if (NOT CMAKE_CROSS_BUILD)
enable_testing()
endif()

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

list(APPEND LOCAL_MODULES memory core cortex jarnax segger stm32 board native)

foreach(module IN LISTS LOCAL_MODULES)
add_subdirectory(modules/${module})
endforeach()

function(add_firmware)
    set(options "")
    set(singles NAME VENDOR)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES)
    cmake_parse_arguments(
        FW
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    add_executable(${FW_NAME}.elf ${FW_SOURCES})
    target_link_libraries(${FW_NAME}.elf PUBLIC ${FW_LIBRARIES} ${COMPILER_MATH_LIB})
    target_include_directories(${FW_NAME}.elf PRIVATE ${FW_INCLUDES})
    target_compile_definitions(${FW_NAME}.elf PRIVATE ${FW_DEFINES})
    target_compile_options(${FW_NAME}.elf PRIVATE # -fverbose-asm -save-temps)
        -fmacro-prefix-map=${CMAKE_SOURCE_DIR}=. # trims __FILE__ to be relative and deterministic
    )
    if (CMAKE_CROSS_BUILD)
        set(FW_LINKERSCRIPT ${CMAKE_SOURCE_DIR}/modules/${FW_VENDOR}/linkerscripts/gcc.ld)
        target_link_options(${FW_NAME}.elf PRIVATE
            -nostdlib
            # --spec=nosys
            $<$<CXX_COMPILER_ID:GNU>:-Wl,-T,${FW_LINKERSCRIPT}>
            -Wl,-Map,${CMAKE_BINARY_DIR}/${FW_NAME}.map
            -Wl,--print-memory-usage
            # -Wl,--print-map
            -Wl,-gc-sections
            -Wl,-cref
        )
        # add_dependencies(${FW_NAME}.elf ${FW_NAME}-ld-script)
        set(FW_ELF ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.elf)
        set(FW_DISASM ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.s)
        add_custom_command(
            OUTPUT ${FW_DISASM}
            DEPENDS ${FW_ELF}
            COMMAND ${CMAKE_OBJDUMP} -d ${FW_ELF} -marm -C -z > ${FW_DISASM}
            COMMENT "Creating Dissembly of ${FW_ELF}"
        )
        # add_dependencies(${FW_NAME}.elf ${FW_LINKERSCRIPT})
        add_custom_target(disassembly-${FW_NAME} DEPENDS ${FW_DISASM})
        # File the relative path from the build directory to the binary
        file(RELATIVE_PATH FW_MODULE ${CMAKE_BINARY_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.elf)
        # Generate a debug file for the Ozone debugger for this firmware
        configure_file(${CMAKE_SOURCE_DIR}/scripts/Ozone.jdebug.in ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.jdebug @ONLY)
        add_custom_target(ozone-${FW_NAME}
            COMMAND /Applications/SEGGER/Ozone/Ozone.app/Contents/MacOS/Ozone ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.jdebug
            DEPENDS ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.jdebug ${CMAKE_CURRENT_BINARY_DIR}/${FW_NAME}.elf)
    else()
        target_compile_definitions(${FW_NAME}.elf
            PUBLIC
                register= # Remove the keyword for compatibility reasons
                UNITTEST)
        target_link_libraries(${FW_NAME}.elf PUBLIC native)
    endif()
endfunction()

#set(CMAKE_CXX_CLANG_TIDY clang-tidy -checks=-*,readability-*)

list(APPEND LOCAL_APPLICATIONS unittests)
foreach(app IN LISTS LOCAL_APPLICATIONS)
    add_subdirectory(applications/${app})
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
