include(FetchContent)

# Function to print variables with a given prefix
function(print_variables_with_prefix prefix)
    get_cmake_property(vars VARIABLES)

    foreach(var ${vars})
        if("${var}" MATCHES "^${prefix}")
            message(STATUS "${var} = ${${var}}")
        endif()
    endforeach()
endfunction()

# function to find all targets with a given prefix
function(print_targets_with_prefix prefix directory)
    get_property(all_targets DIRECTORY ${directory} PROPERTY BUILDSYSTEM_TARGETS)

    foreach(target ${all_targets})
        if("${target}" MATCHES "^${prefix}")
            message(STATUS "Target: ${target}")
        endif()
    endforeach()

    get_property(all_targets DIRECTORY ${directory} PROPERTY IMPORTED_TARGETS)

    foreach(target ${all_targets})
        if("${target}" MATCHES "^${prefix}")
            message(STATUS "Imported Target: ${target}")
        endif()
    endforeach()
endfunction()

# Declare External Dependencies and how to fetch them
if(NOT BUILD_CROSS_TARGET) # Only fetch these dependencies if we are not cross-compiling
    FetchContent_Declare(
        Catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2/
        GIT_TAG v3.11.0
    )
    FetchContent_MakeAvailable(Catch2) # This will define the Catch2::Catch2 target
    print_variables_with_prefix("Catch2_")
    print_targets_with_prefix("Catch2_" ${Catch2_SOURCE_DIR})

    # Googletest now is called gtest and gmock
    FetchContent_Declare(
        gtest
        DOWNLOAD_EXTRACT_TIMESTAMP ON
        GIT_REPOSITORY https://github.com/google/googletest/
        GIT_TAG v1.17.0
    )
    FetchContent_MakeAvailable(gtest) # This will define the gtest and gmock targets
    print_variables_with_prefix("gtest_")
    print_targets_with_prefix("gtest_" ${gtest_SOURCE_DIR})

    # Use GTest::gtest and GTest::gmock targets
    FetchContent_Declare(
        FakeIt
        GIT_REPOSITORY https://github.com/eranpeer/FakeIt/
        GIT_TAG 2.4.1
    )
    FetchContent_MakeAvailable(FakeIt) # This will define the FakeIt::FakeIt target
    print_variables_with_prefix("FakeIt")
    print_targets_with_prefix("FakeIt" ${FakeIt_SOURCE_DIR})

    # does not provide a target
    add_library(Catch2FakeIt INTERFACE)
    target_compile_definitions(Catch2FakeIt INTERFACE FAKEIT_USE_CATCH2)
    target_include_directories(Catch2FakeIt INTERFACE ${FakeIt_SOURCE_DIR}/single_header/catch) # FakeIt is a single header library but we'll use it with Catch2 (above)
endif()

# Found on https://discourse.cmake.org/t/possible-to-create-a-python-virtual-env-from-cmake-and-then-find-it-with-findpython3/1132/2
# Find just the interpreter first
find_package(Python3 REQUIRED Interpreter)
# Print the version and create the virtual environment
execute_process (
    COMMAND_ECHO STDOUT
    COMMAND ${Python3_EXECUTABLE} --version
    COMMAND ${Python3_EXECUTABLE} -m venv ${CMAKE_BINARY_DIR}/venv
)
# This mimics the activation of the venv
set(ENV{VIRTUAL_ENV} "${CMAKE_BINARY_DIR}/venv")
# changes the context of the search
set(Python3_FIND_VIRTUALENV FIRST)
# gets rid of the previous find
unset(Python3_EXECUTABLE)
## Launch a new search
find_package (Python3 COMPONENTS Interpreter Development)
# Print the version and the install the pips
execute_process (
    COMMAND_ECHO STDOUT
    OUTPUT_STRIP_TRAILING_WHITESPACE
    COMMAND ${Python3_EXECUTABLE} --version
    COMMAND ${Python3_EXECUTABLE} -m pip install jinja2 pyyaml
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
)

# we capture these now so that they can't get changed later
set(STATERATOR_PYTHON ${Python3_EXECUTABLE} CACHE PATH "Path to the python executable to use with staterator")
set(STATERATOR_ROOT ${CMAKE_SOURCE_DIR}/external/staterator CACHE PATH "Path to the staterator root directory")
set(STATERATOR_SCRIPT ${STATERATOR_ROOT}/staterator.py CACHE PATH "Path to the staterator script")
set(STATERATOR_TEMPLATE_ROOT ${STATERATOR_ROOT}/templates CACHE PATH "Path to the staterator template directory")
file(GLOB STATERATOR_TEMPLATES ${STATERATOR_TEMPLATE_ROOT}/*)
message(STATUS "Using Python interpreter: ${STATERATOR_PYTHON}")
message(STATUS "Using staterator root: ${STATERATOR_ROOT}")
message(STATUS "Using staterator template root: ${STATERATOR_TEMPLATE_ROOT}")
message(STATUS "Using staterator templates: ${STATERATOR_TEMPLATES}")
foreach(template ${STATERATOR_TEMPLATES})
    message(STATUS "  Template: ${template}")
    list(APPEND CMAKE_CONFIGURE_DEPENDS ${template})
endforeach()
list(APPEND CMAKE_CONFIGURE_DEPENDS ${STATERATOR_SCRIPT})

function(generate_statechart)
    set(options "")
    set(singles YAML_ROOT YAML_FILE GENERATED_DIR)
    set(multiples TYPES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if (NOT ARG_GENERATED_DIR)
        set(ARG_GENERATED_DIR "${CMAKE_BINARY_DIR}/generated")
    endif()
    if (NOT ARG_TYPES)
        set(ARG_TYPES CPP HPP DOT D2 CMAKE GTEST)
    endif()
    if (NOT EXISTS ${ARG_YAML_ROOT}/${ARG_YAML_FILE})
        message(FATAL_ERROR "YAML file ${ARG_YAML_ROOT}/${ARG_YAML_FILE} does not exist")
    endif()
    message("Generating statechart from ${ARG_YAML_FILE} to ${ARG_GENERATED_DIR} for types: ${ARG_TYPES}")
    execute_process(COMMAND ${CMAKE_COMMAND} -E make_directory ${ARG_GENERATED_DIR})
    list(APPEND CMAKE_CONFIGURE_DEPENDS ${ARG_YAML_ROOT}/${ARG_YAML_FILE})
    # get the base name of the yaml file
    get_filename_component(YAML_BASENAME ${ARG_YAML_FILE} NAME_WE)
    foreach(type ${ARG_TYPES})
        if (type STREQUAL "CPP")
            set(template StateChart.cpp.jinja)
            set(output "${YAML_BASENAME}.cpp")
        elseif(type STREQUAL "HPP")
            set(template StateChart.hpp.jinja)
            set(output "${YAML_BASENAME}.hpp")
        elseif(type STREQUAL "DOT")
            set(template StateChart.dot.jinja)
            set(output "${YAML_BASENAME}.dot")
        elseif(type STREQUAL "D2")
            set(template StateChart.d2.jinja)
            set(output "${YAML_BASENAME}.d2")
        elseif(type STREQUAL "CMAKE")
            set(template CMakeLists.txt.jinja)
            set(output "CMakeLists.txt")
        elseif(type STREQUAL "GTEST")
            set(template gtest_statechart.cpp.jinja)
            set(output "gtest_${YAML_BASENAME}.cpp")
        elseif(type STREQUAL "PLANTUML")
            set(template StateChart.puml.jinja)
            set(output "${YAML_BASENAME}.puml")
        else()
            message(FATAL_ERROR "Unknown type specified: ${type}. Supported types are CXX, DOT, D2, CMAKE, GTEST")
        endif()
        message(STATUS "Generating ${output} using ${template} for type ${type}")
        execute_process(
            # COMMAND_ECHO STDOUT
            OUTPUT_STRIP_TRAILING_WHITESPACE
            # COMMAND ${STATERATOR_PYTHON} --version
            COMMAND ${STATERATOR_PYTHON} ${STATERATOR_SCRIPT}
                    --yaml-root ${ARG_YAML_ROOT}
                    --yaml-file ${ARG_YAML_FILE}
                    --generated ${ARG_GENERATED_DIR}
                    --template-root ${STATERATOR_TEMPLATE_ROOT}
                    --template-file ${template}
                    --output ${output}
            WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        )
    endforeach()
endfunction()
