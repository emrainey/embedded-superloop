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
endfunction()

# Declare External Dependencies and how to fetch them
if (NOT CMAKE_CROSS_BUILD) # Only fetch these dependencies if we are not cross-compiling
FetchContent_Declare(
    Catch2
    GIT_REPOSITORY  https://github.com/catchorg/Catch2/
    GIT_TAG v3.7.1
)
FetchContent_MakeAvailable(Catch2) # This will define the Catch2::Catch2 target
print_variables_with_prefix("Catch2_")
print_targets_with_prefix("Catch2_" ${Catch2_SOURCE_DIR})

# Googletest now is called gtest and gmock
FetchContent_Declare(
    gtest
    DOWNLOAD_EXTRACT_TIMESTAMP ON
    GIT_REPOSITORY https://github.com/google/googletest/
    GIT_TAG v1.15.2
)
FetchContent_MakeAvailable(gtest) # This will define the gtest and gmock targets
print_variables_with_prefix("gtest_")
print_targets_with_prefix("gtest_" ${gtest_SOURCE_DIR})

FetchContent_Declare(
    FakeIt
    GIT_REPOSITORY https://github.com/eranpeer/FakeIt/
    GIT_TAG 2.4.1
)
FetchContent_MakeAvailable(FakeIt) # This will define the FakeIt::FakeIt target
print_variables_with_prefix("FakeIt_")
print_targets_with_prefix("FakeIt_" ${FakeIt_SOURCE_DIR})
# does not provide a target
add_library(FakeIt::FakeIt INTERFACE IMPORTED)
target_include_directories(FakeIt::FakeIt INTERFACE ${FakeIt_SOURCE_DIR}/single_header/catch) # FakeIt is a single header library but we'll use it with Catch2 (above)
endif()
