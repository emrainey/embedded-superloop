cmake_minimum_required(VERSION 3.22)

project(embedded-superloop
        DESCRIPTION "Embedded Superloop"
        VERSION 0.1.50
        LANGUAGES CXX ASM)

set(EMBEDDED_SUPERLOOP_PROJECT_ROOT ${CMAKE_CURRENT_SOURCE_DIR})
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

function(set_configuration_name VAR CFG)
    set(${VAR} configuration-${CFG} PARENT_SCOPE)
endfunction()

function(set_target_name VAR NAME CFG BOARD)
    set(${VAR} ${NAME}-${CFG}-${BOARD} PARENT_SCOPE)
endfunction()

function(set_board_name VAR NAME CFG)
    set(${VAR} board-${NAME}-${CFG} PARENT_SCOPE)
endfunction()

function(set_arch_name VAR NAME CFG)
    set(${VAR} arch-${NAME}-${CFG}-all PARENT_SCOPE)
endfunction()

# Add an empty library to handle no configuration
add_library(configuration-none INTERFACE)
target_include_directories(configuration-none INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(configuration-none INTERFACE strict)

# Create an interface library per configuration
foreach (cfg IN LISTS LOCAL_CONFIGURATIONS)
    set_configuration_name(LOCAL_TARGET ${cfg})
    message("Adding configuration ${LOCAL_TARGET}")
    add_library(${LOCAL_TARGET} INTERFACE)
    target_compile_definitions(${LOCAL_TARGET} INTERFACE CONFIGURATION_${cfg})
    target_include_directories(${LOCAL_TARGET} INTERFACE ${CMAKE_SOURCE_DIR}/configurations/${cfg})
    target_link_libraries(${LOCAL_TARGET} INTERFACE configuration-none)
endforeach()

# An architecture is a set of hardware features that are common to a set of microcontrollers.
# An architecture is influenced by the system configuration but not by the board configuration.
# The architecture is an interface library.
function(add_architecture)
    set(options NO_BOARDS)
    set(singles NAME VENDOR)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES GENERIC_MODULES CONFIGURATIONS) # has no BOARD options
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT DEFINED ARG_VENDOR)
        message(FATAL_ERROR "No vendor specified for board ${ARG_NAME}")
    endif()
    foreach (cfg IN LISTS ARG_CONFIGURATIONS)
        set_arch_name(LOCAL_TARGET ${ARG_NAME} ${cfg})
        message("Adding architecture ${LOCAL_TARGET}")
        add_library(${LOCAL_TARGET} INTERFACE)
        target_sources(${LOCAL_TARGET} INTERFACE ${ARG_SOURCES})
        set_target_properties(${LOCAL_TARGET} PROPERTIES VENDOR ${ARG_VENDOR})
        set_configuration_name(LOCAL_CONFIGURATION ${cfg})
        target_link_libraries(${LOCAL_TARGET} INTERFACE ${LOCAL_CONFIGURATION})
        if (DEFINED ARG_INCLUDES)
            target_include_directories(${LOCAL_TARGET} INTERFACE ${ARG_INCLUDES})
        endif()
        if (DEFINED ARG_LIBRARIES)
            target_link_libraries(${LOCAL_TARGET} INTERFACE ${ARG_LIBRARIES})
        endif()
        if (DEFINED ARG_DEFINES)
            target_compile_definitions(${LOCAL_TARGET} INTERFACE ${ARG_DEFINES})
        endif()
        foreach (module IN LISTS ARG_GENERIC_MODULES)
            set_target_name(_MOD ${module} none all)
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} INTERFACE ${_MOD})
            endif()
        endforeach()
        foreach (module IN LISTS ARG_SYSTEM_MODULES)
            set_target_name(_MOD ${module} ${cfg} all)
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} INTERFACE ${_MOD})
            endif()
        endforeach()
    endforeach()
endfunction()

# A board defines the hardware configuration which the system will run on. It can be influenced by the system configuration.
# A board depends on a vendor which must be set.
function(add_board)
    set(options "")
    set(singles NAME VENDOR)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES CONFIGURATIONS GENERIC_MODULES SYSTEM_MODULES BOARD_MODULES MODULES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT DEFINED ARG_VENDOR)
        message(FATAL_ERROR "No vendor specified for board ${ARG_NAME}")
    endif()
    if (NOT DEFINED ARG_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for module ${ARG_NAME}")
    endif()
    foreach (cfg IN LISTS ARG_CONFIGURATIONS)
        set_board_name(LOCAL_TARGET ${ARG_NAME} ${cfg})
        message("Adding board ${LOCAL_TARGET}")
        add_library(${LOCAL_TARGET} STATIC ${ARG_SOURCES})
        set_target_properties(${LOCAL_TARGET} PROPERTIES VENDOR ${ARG_VENDOR})
        target_link_libraries(${LOCAL_TARGET} PUBLIC configuration-${cfg})
        if (DEFINED ARG_INCLUDES)
            target_include_directories(${LOCAL_TARGET} PUBLIC ${ARG_INCLUDES})
        endif()
        if (DEFINED ARG_LIBRARIES)
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
        endif()
        if (DEFINED ARG_DEFINES)
            target_compile_definitions(${LOCAL_TARGET} PUBLIC ${ARG_DEFINES})
        endif()
        foreach (module IN LISTS ARG_GENERIC_MODULES)
            set_target_name(_MOD ${module} none all)
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endif()
        endforeach()
        foreach (module IN LISTS ARG_BOARD_MODULES)
            set_target_name(_MOD ${module} none ${ARG_NAME})
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endif()
        endforeach()
        foreach (module IN LISTS ARG_SYSTEM_MODULES)
            set_target_name(_MOD ${module} ${cfg} all)
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endif()
        endforeach()
        foreach (module IN LISTS ARG_MODULES)
            set_target_name(_MOD ${module} ${cfg} ${ARG_NAME})
            if (NOT TARGET ${_MOD})
                message(FATAL_ERROR "Module ${_MOD} not found while making ${LOCAL_TARGET}")
            else()
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endif()
        endforeach()
    endforeach()
endfunction()

# A module is a component that could be influenced by the system configuration and the board configuration
# A module with no configurations and no board is a generic module that can be used in anywhere and has the -none-all postfix.
# A module with no configurations and some board is a board module and has a -none-$board postfix.
# A module with some configurations and no board is a system module and has a -$cfg-all postfix.
# A module with some configurations and some board is a normal module and has a -$cfg-$board postfix.
function(add_module)
    set(options NO_CONFIGURATIONS NO_BOARDS)
    set(singles NAME ARCH)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES CONFIGURATIONS BOARDS GENERIC_MODULES BOARD_MODULES SYSTEM_MODULES MODULES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT ARG_CONFIGURATIONS AND NOT ARG_NO_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for module ${ARG_NAME}")
    endif()
    if (NOT ARG_BOARDS AND NOT ARG_NO_BOARDS)
        message(FATAL_ERROR "No boards specified for module ${ARG_NAME}")
    endif()
    if (ARG_NO_CONFIGURATIONS)
        set(ARG_CONFIGURATIONS none)
    endif()
    if (ARG_NO_BOARDS)
        set(ARG_BOARDS all)
    endif()
    # message("Possible module ${ARG_NAME}")
    foreach (cfg IN LISTS ARG_CONFIGURATIONS)
        foreach (board IN LISTS ARG_BOARDS)
            set_target_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${board})
            message("Adding module ${LOCAL_TARGET}")
            add_library(${LOCAL_TARGET} STATIC ${ARG_SOURCES})
            if (ARG_INCLUDES)
                target_include_directories(${LOCAL_TARGET} PUBLIC ${ARG_INCLUDES})
            endif()
            if (ARG_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
            endif()
            if (ARG_DEFINES)
                target_compile_definitions(${LOCAL_TARGET} PUBLIC ${ARG_DEFINES})
            endif()
            if (NOT ARG_NO_CONFIGURATIONS)
                set_configuration_name(LOCAL_CONFIGURATION ${cfg})
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${LOCAL_CONFIGURATION})
            endif()
            if (NOT ARG_NO_BOARDS)
                set_board_name(LOCAL_BOARD ${board} ${cfg})
                message(STATUS "Linking ${LOCAL_TARGET} to ${LOCAL_BOARD}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${LOCAL_BOARD})
            endif()
            if (ARG_ARCH)
                set_arch_name(LOCAL_ARCH ${ARG_ARCH} ${cfg})
                target_link_libraries(${LOCAL_TARGET} INTERFACE ${LOCAL_ARCH})
            endif()
            foreach (module IN LISTS ARG_GENERIC_MODULES)
                set_target_name(_MOD ${module} none all)
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_BOARD_MODULES)
                set_target_name(_MOD ${module} none ${board})
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_SYSTEM_MODULES)
                set_target_name(_MOD ${module} ${cfg} all)
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_MODULES)
                set_target_name(_MOD ${module} ${cfg} ${board})
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
            endforeach()
        endforeach()
    endforeach()
endfunction()

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
    set(singles NAME LINKERSCRIPT)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES MODULES CONFIGURATIONS BOARDS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT ARG_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for firmware ${ARG_TARGET}")
    endif()
    if (NOT ARG_BOARDS)
        message(FATAL_ERROR "No boards specified for firmware ${ARG_TARGET}")
    endif()
    foreach (cfg IN LISTS ARG_CONFIGURATIONS)
        foreach (board IN LISTS ARG_BOARDS)
            set_board_name(LOCAL_BOARD ${board} ${cfg})
            get_target_property(BOARD_VENDOR ${LOCAL_BOARD} VENDOR)
            if (NOT ARG_LINKERSCRIPT)
                set(ARG_LINKERSCRIPT ${CMAKE_SOURCE_DIR}/modules/${BOARD_VENDOR}/linkerscripts/gcc.ld)
            endif()
            if (CMAKE_CROSS_BUILD)
                set(LOCAL_TARGET ${ARG_NAME}-${BOARD_VENDOR}-${cfg}-${board})
            else()
                set(LOCAL_TARGET ${ARG_NAME}-native-${cfg}-${board})
            endif()
            message("Adding firmware ${LOCAL_TARGET}")
            add_executable(${LOCAL_TARGET}.elf ${ARG_SOURCES})
            if (ARG_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${ARG_LIBRARIES})
            endif()
            if (DEFINED COMPILER_MATH_LIBS AND NOT COMPILER_MATH_LIBS STREQUAL "")
                message(STATUS "Linking with math libraries ${COMPILER_MATH_LIBS}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${COMPILER_MATH_LIBS})
            endif()
            if (ARG_INCLUDES)
                target_include_directories(${LOCAL_TARGET}.elf PRIVATE ${ARG_INCLUDES})
            endif()
            if (ARG_DEFINES)
                target_compile_definitions(${LOCAL_TARGET}.elf PRIVATE ${ARG_DEFINES})
            endif()
            foreach (module IN LISTS ARG_GENERIC_MODULES)
                set_target_name(_MOD ${module} none all)
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_BOARD_MODULES)
                set_target_name(_MOD ${module} none ${board})
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_SYSTEM_MODULES)
                set_target_name(_MOD ${module} ${cfg} all)
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${_MOD})
            endforeach()
            foreach (module IN LISTS ARG_MODULES)
                set_target_name(_MOD ${module} ${cfg} ${board})
                message(STATUS "Depends on ${_MOD}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${_MOD})
            endforeach()
            target_compile_options(${LOCAL_TARGET}.elf PRIVATE # -fverbose-asm -save-temps)
                -fmacro-prefix-map=${CMAKE_SOURCE_DIR}=. # trims __FILE__ to be relative and deterministic
            )
            if (CMAKE_CROSS_BUILD)
                target_link_options(${LOCAL_TARGET}.elf PRIVATE
                    -nostdlib
                    # --spec=nosys
                    $<$<CXX_COMPILER_ID:GNU>:-Wl,-T,${ARG_LINKERSCRIPT}>
                    -Wl,-Map,${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.map
                    -Wl,--print-memory-usage
                    # -Wl,--print-map
                    -Wl,-gc-sections
                    -Wl,-cref
                )
                # Set the INTERFACE_LINK_DEPENDS property
                set_target_properties(${LOCAL_TARGET}.elf PROPERTIES
                    INTERFACE_LINK_DEPENDS "${ARG_LINKERSCRIPT}"
                )
                # add_dependencies(${ARG_NAME}.elf ${ARG_NAME}-ld-script)
                set(ARG_ELF ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.elf)
                set(ARG_DISASM ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.s)
                add_custom_command(
                    OUTPUT ${ARG_DISASM}
                    DEPENDS ${ARG_ELF}
                    COMMAND ${CMAKE_OBJDUMP} -d ${ARG_ELF} -marm -C -z > ${ARG_DISASM}
                    COMMENT "Creating Dissembly of ${ARG_ELF}"
                )
                # add_dependencies(${ARG_NAME}.elf ${ARG_LINKERSCRIPT})
                add_custom_target(disassembly-${LOCAL_TARGET} ALL DEPENDS ${ARG_DISASM})
                # File the relative path from the build directory to the binary
                file(RELATIVE_PATH LOCAL_TARGET_BINARY_PATH ${CMAKE_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.elf)
                # Generate a debug file for the Ozone debugger for this firmware
                configure_file(${CMAKE_SOURCE_DIR}/scripts/Ozone.jdebug.in ${CMAKE_SOURCE_DIR}/${LOCAL_TARGET}.jdebug @ONLY)
                add_custom_target(ozone-${LOCAL_TARGET}
                    COMMAND /Applications/SEGGER/Ozone/Ozone.app/Contents/MacOS/Ozone ${CMAKE_SOURCE_DIR}/${LOCAL_TARGET}.jdebug
                    DEPENDS ${CMAKE_SOURCE_DIR}/${LOCAL_TARGET}.jdebug ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.elf)
            else()
                target_compile_definitions(${LOCAL_TARGET}.elf
                    PUBLIC
                        register= # Remove the keyword for compatibility reasons
                        UNITTEST)
                set_target_name(LOCAL_BOARD native ${cfg} ${board})
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${LOCAL_BOARD})
            endif()
        endforeach()
    endforeach()
endfunction()

if (NOT TARGET test AND CMAKE_CROSS_BUILD)
    add_custom_target(test)
endif()

if (NOT TARGET coverage)
    add_custom_target(coverage)
    add_dependencies(coverage test)
endif()

function(host_unit_test)
    set(options CATCH2 FAKEIT GOOGLETEST NO_CONFIGURATIONS NO_BOARDS)
    set(singles NAME)
    set(multiples SOURCES INCLUDES LIBRARIES MODULES EXCLUDES DEFINES TEST_ARGUMENTS CONFIGURATIONS BOARDS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT ARG_CONFIGURATIONS AND NOT ARG_NO_CONFIGURATIONS)
            message(FATAL_ERROR "No configurations specified for unit test ${ARG_TARGET}")
    endif()
    if (NOT ARG_BOARDS AND NOT ARG_NO_BOARDS)
            message(FATAL_ERROR "No boards specified for unit test ${ARG_TARGET}")
    endif()
    if (ARG_NO_CONFIGURATIONS AND NOT DEFINED ARG_CONFIGURATIONS)
        set(ARG_CONFIGURATIONS none)
    endif()
    if (ARG_NO_BOARDS AND NOT DEFINED ARG_BOARDS)
        set(ARG_BOARDS all)
    endif()
    if (NOT CMAKE_CROSS_BUILD)
        # message(STATUS "Adding host unit test ${ARG_NAME} ${ARG_CONFIGURATIONS} ${ARG_BOARDS}")
        foreach (cfg IN LISTS ARG_CONFIGURATIONS)
            foreach (board IN LISTS ARG_BOARDS)
                set_target_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${board})
                message("Adding host unit test ${LOCAL_TARGET} for ${cfg} ${board}")
                add_executable(${LOCAL_TARGET} ${ARG_SOURCES})
                if (ARG_INCLUDES)
                    target_include_directories(${LOCAL_TARGET} PRIVATE ${ARG_INCLUDES})
                endif()
                if (ARG_LIBRARIES)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
                endif()
                foreach (module IN LISTS ARG_GENERIC_MODULES)
                    set_target_name(_MOD ${module} none all)
                    message(STATUS "Depends on ${_MOD}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
                endforeach()
                foreach (module IN LISTS ARG_BOARD_MODULES)
                    set_target_name(_MOD ${module} none ${board})
                    message(STATUS "Depends on ${_MOD}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
                endforeach()
                foreach (module IN LISTS ARG_SYSTEM_MODULES)
                    set_target_name(_MOD ${module} ${cfg} all)
                    message(STATUS "Depends on ${_MOD}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
                endforeach()
                foreach (module IN LISTS ARG_MODULES)
                    set_target_name(_MOD ${module} ${cfg} ${board})
                    message(STATUS "Depends on ${_MOD}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${_MOD})
                endforeach()
                if (ARG_CATCH2)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE CATCH2)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC Catch2::Catch2WithMain)
                endif()
                if (ARG_FAKEIT)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE FAKEIT)
                    target_link_libraries(${LOCAL_TARGET} PRIVATE Catch2FakeIt)
                endif()
                if (ARG_GOOGLETEST)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE GOOGLETEST)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC GTest::gtest GTest::gmock GTest::gtest_main)
                endif()
                target_compile_definitions(${LOCAL_TARGET} PRIVATE UNITTEST ${ARG_DEFINES})

                if (NOT DEFINED UNIT_TEST_TARGETS)
                    set(UNIT_TEST_TARGETS "")
                    include(CTest)
                endif()
                list(APPEND UNIT_TEST_TARGETS ${LOCAL_TARGET})

                # CTest
                add_test(NAME ${LOCAL_TARGET} COMMAND ${LOCAL_TARGET} ${ARG_TEST_ARGUMENTS})

                foreach (excl IN LISTS ARG_EXCLUDES)
                    list(APPEND EXCLUDES --exclude ${excl})
                endforeach()
                # list(APPEND EXCLUDES --exclude '/tests/*' --exclude '*/catch2/*' --exclude '*/unittests/** --exclude **/googletest/*')
                # message(STATUS "Defining coverage-${ARG_NAME}")
                add_custom_target(coverage-${LOCAL_TARGET}
                    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage/
                    COMMAND gcovr --root ${CMAKE_CURRENT_SOURCE_DIR}
                        --exclude ${CMAKE_CURRENT_SOURCE_DIR}/tests
                        --exclude ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests
                        --object-directory ${CMAKE_CURRENT_BINARY_DIR}
                        --xml-pretty --xml ${CMAKE_BINARY_DIR}/coverage/coverage-${LOCAL_TARGET}.xml
                        --html-details ${CMAKE_BINARY_DIR}/coverage/coverage-${LOCAL_TARGET}.html
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    DEPENDS ${LOCAL_TARGET}
                )
                add_dependencies(coverage coverage-${LOCAL_TARGET})
            endforeach()
        endforeach()
    else()
        message(STATUS "Skipping host unit test ${ARG_NAME} because CMAKE_CROSS_BUILD=${CMAKE_CROSS_BUILD}")
    endif()
endfunction()

if (LOCAL_MODULES)
    message(STATUS "LOCAL_MODULES=${LOCAL_MODULES}")
else()
    message(FATAL_ERROR "LOCAL_MODULES not defined")
endif()

if (LOCAL_APPLICATIONS)
    message(STATUS "LOCAL_APPLICATIONS=${LOCAL_APPLICATIONS}")
else()
    message(FATAL_ERROR "LOCAL_APPLICATIONS not defined")
endif()

if (LOCAL_CONFIGURATIONS)
    message(STATUS "LOCAL_CONFIGURATIONS=${LOCAL_CONFIGURATIONS}")
else()
    message(FATAL_ERROR "LOCAL_CONFIGURATIONS not defined")
endif()

if (LOCAL_BOARDS)
    message(STATUS "LOCAL_BOARDS=${LOCAL_BOARDS}")
else()
    message(FATAL_ERROR "LOCAL_BOARDS not defined")
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
    foreach (_mod IN LISTS LOCAL_MODULES)
        file(GLOB_RECURSE _MOD_INCLUDES ${CMAKE_CURRENT_SOURCE_DIR}/modules/${_mod}/include/**/*.hpp)
        list(APPEND DOXYGEN_INCLUDES ${_MOD_INCLUDES})
        file(GLOB_RECURSE _MOD_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/modules/${_mod}/source/*.cpp)
        list(APPEND DOXYGEN_SOURCES ${_MOD_SOURCES})
    endforeach()
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
