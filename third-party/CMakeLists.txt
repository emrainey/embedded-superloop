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

include(FetchContent)

# Use git submodules under third-party/ as the source for FetchContent
set(THIRD_PARTY_DIR "${CMAKE_CURRENT_SOURCE_DIR}")

if(NOT BUILD_CROSS_TARGET) # Only fetch these dependencies if we are not cross-compiling
    FetchContent_Declare(
        Catch2
        SOURCE_DIR ${THIRD_PARTY_DIR}/Catch2
    )
    FetchContent_MakeAvailable(Catch2) # This will define the Catch2::Catch2 target
    print_variables_with_prefix("Catch2_")
    print_targets_with_prefix("Catch2_" ${Catch2_SOURCE_DIR})

    # Googletest now is called gtest and gmock
    # On macOS, force googletest to use libc++ instead of libstdc++
    if(APPLE AND NOT BUILD_CROSS_TARGET)
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -stdlib=libc++" CACHE STRING "" FORCE)
    endif()
    FetchContent_Declare(
        gtest
        SOURCE_DIR ${THIRD_PARTY_DIR}/googletest
    )
    FetchContent_MakeAvailable(gtest) # This will define the gtest and gmock targets
    print_variables_with_prefix("gtest_")
    print_targets_with_prefix("gtest_" ${gtest_SOURCE_DIR})

    # Use GTest::gtest and GTest::gmock targets
    FetchContent_Declare(
        FakeIt
        SOURCE_DIR ${THIRD_PARTY_DIR}/FakeIt
    )
    FetchContent_MakeAvailable(FakeIt) # This will define the FakeIt::FakeIt target
    print_variables_with_prefix("FakeIt")
    print_targets_with_prefix("FakeIt" ${FakeIt_SOURCE_DIR})

    # does not provide a target
    add_library(Catch2FakeIt INTERFACE)
    target_compile_definitions(Catch2FakeIt INTERFACE FAKEIT_USE_CATCH2)
    target_include_directories(Catch2FakeIt INTERFACE ${FakeIt_SOURCE_DIR}/single_header/catch) # FakeIt is a single header library but we'll use it with Catch2 (above)
endif()

# Hypha IP stack - light-weight IP stack for Cyphal/UDP
# This is used by target firmware as the Ethernet/IP layer instead of jarnax-net
# NOTE: libhypha's own CMakeLists.txt uses CMAKE_SOURCE_DIR which breaks when brought in
# via add_subdirectory, so we build it directly here.
set(HYPHA_LIB_THIRD_PARTY ${THIRD_PARTY_DIR}/libhypha)

# Define the hypha-ip-defs interface (compile definitions shared with consumers)
add_library(hypha-ip-defs INTERFACE)
target_compile_definitions(hypha-ip-defs INTERFACE
    HYPHA_IP_TTL=128
    HYPHA_IP_MTU=1500
    HYPHA_IP_USE_VLAN=0
)

# Define the hypha-ip-rules interface (compiler flags for hypha itself)
add_library(hypha-ip-rules INTERFACE)
target_compile_options(hypha-ip-rules INTERFACE
    -Wall -Wextra -Wconversion -Wformat=2 -Wshadow
    -Wunused-parameter -Wunused-variable -Wstrict-prototypes -Wredundant-decls
    -pedantic
    -fdiagnostics-color=always
)

# Build the hypha-ip static library
add_library(hypha-ip STATIC
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_api.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_arp.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_checksum.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_eth.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_flip.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_icmp.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_igmp.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_ip.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_print.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_span.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_status.c
    ${HYPHA_LIB_THIRD_PARTY}/source/hypha_udp.c
)

target_include_directories(hypha-ip PUBLIC
    $<BUILD_INTERFACE:${HYPHA_LIB_THIRD_PARTY}/include>
)

target_include_directories(hypha-ip PRIVATE
    ${HYPHA_LIB_THIRD_PARTY}/source/include
)

target_link_libraries(hypha-ip PUBLIC hypha-ip-defs)
target_link_libraries(hypha-ip PRIVATE hypha-ip-rules)

# LibUDPard - Cyphal/UDP transport layer
# The library is a single .c/.h file with no build system; we provide one here.
add_subdirectory(${THIRD_PARTY_DIR}/libudpard)
