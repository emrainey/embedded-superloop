
add_library(core INTERFACE)
target_sources(core INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/new.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/eabi.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/constexpr_tests.cpp
)
target_include_directories(core INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
#target_link_libraries(core INTERFACE)

message(STATUS CMAKE_CROSS_BUILD=${CMAKE_CROSS_BUILD})
if (NOT CMAKE_CROSS_BUILD)
# If we're not cross compiling, then use Catch2 to generate some unit tests
find_package(Catch2 3 REQUIRED)
add_executable(test-core
    tests/span.cpp
    tests/array.cpp
    tests/ring.cpp
    tests/stack.cpp
)
target_compile_definitions(test-core PUBLIC UNITTEST)
target_link_libraries(test-core core Catch2::Catch2WithMain)
# include(CTest)
# include(Catch)
# catch_discover_tests(tests)
endif()
