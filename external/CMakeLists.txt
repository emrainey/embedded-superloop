# Found on https://discourse.cmake.org/t/possible-to-create-a-python-virtual-env-from-cmake-and-then-find-it-with-findpython3/1132/2
# Find just the interpreter first
find_package(Python3 REQUIRED Interpreter)
set(PYTHON_VENV "${CMAKE_SOURCE_DIR}/.venv")
# Print the version and create the virtual environment
execute_process (
    COMMAND_ECHO STDOUT
    COMMAND ${Python3_EXECUTABLE} --version
    COMMAND ${Python3_EXECUTABLE} -m venv ${PYTHON_VENV}
)
# This mimics the activation of the venv
set(ENV{VIRTUAL_ENV} "${PYTHON_VENV}")
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
    COMMAND ${Python3_EXECUTABLE} -m pip install --upgrade pip
    COMMAND ${Python3_EXECUTABLE} -m pip install jinja2 pyyaml jlink-mcp pylink-square pytest pytest-cov pyserial nunavut pydsdl
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

# Cyphal DSDL code generation via nunavut (nnvg)
set(CYPHAL_DSDL_ROOT ${CMAKE_SOURCE_DIR}/third-party/public_regulated_data_types CACHE PATH "Path to the Cyphal DSDL data types")
set(CYPHAL_DSDL_GENERATED_DIR ${CMAKE_BINARY_DIR}/generated/cyphal-dsdl CACHE PATH "Path to the generated Cyphal DSDL C headers")

function(generate_cyphal_dsdl)
    if (NOT EXISTS ${CYPHAL_DSDL_ROOT}/uavcan/node/7509.Heartbeat.1.0.dsdl)
        message(FATAL_ERROR "Cyphal DSDL types not found at ${CYPHAL_DSDL_ROOT}. Ensure the public_regulated_data_types submodule is checked out.")
    endif()
    message("Generating Cyphal DSDL C headers from ${CYPHAL_DSDL_ROOT} to ${CYPHAL_DSDL_GENERATED_DIR}")
    file(GLOB_RECURSE DSDL_FILES ${CYPHAL_DSDL_ROOT}/uavcan/*.dsdl)
    list(APPEND CMAKE_CONFIGURE_DEPENDS ${DSDL_FILES})
    execute_process(
        COMMAND ${CMAKE_COMMAND} -E make_directory ${CYPHAL_DSDL_GENERATED_DIR}
        COMMAND ${STATERATOR_PYTHON} -m nunavut
                --target-language c
                --outdir ${CYPHAL_DSDL_GENERATED_DIR}
                ${CYPHAL_DSDL_ROOT}/uavcan
        WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
        RESULT_VARIABLE NNVG_RESULT
        OUTPUT_VARIABLE NNVG_OUTPUT
        ERROR_VARIABLE NNVG_ERROR
    )
    if(NOT NNVG_RESULT EQUAL 0)
        message(FATAL_ERROR "Cyphal DSDL code generation failed: ${NNVG_OUTPUT} ${NNVG_ERROR}")
    endif()
endfunction()

generate_cyphal_dsdl()

# Header-only library exposing the generated Cyphal DSDL C headers so that both
# the on-target firmware and the host unit tests can consume them.
if (NOT TARGET cyphal-dsdl)
    add_library(cyphal-dsdl INTERFACE)
    target_include_directories(cyphal-dsdl SYSTEM INTERFACE ${CYPHAL_DSDL_GENERATED_DIR})
endif()
