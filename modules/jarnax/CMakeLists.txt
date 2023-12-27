
configure_file(${CMAKE_CURRENT_SOURCE_DIR}/include/jarnax/version.hpp.in
               ${CMAKE_CURRENT_BINARY_DIR}/include/jarnax/version.hpp)

add_library(jarnax INTERFACE)
target_sources(jarnax INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/on_entry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/zero_bss.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/static_constructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/static_destructors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/load_data.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/watermark_stack.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/simple_globals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize/class_globals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/configure.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/entry.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/non_maskable_interrupt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/hard.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/bus.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/memory_management.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/faults/usage.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/supervisor/call.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/supervisor/pending.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/generic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/dummy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/get_exception_frame.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/handlers/tick.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/spinhalt.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/bist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/print.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/ticker.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Superloop.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/Status.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/bist.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/deescalate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/escalate.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/supervisor/restore.cpp
)
target_include_directories(jarnax INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_BINARY_DIR}/include
)
target_link_libraries(jarnax INTERFACE strict core memory segger)


if (NOT CMAKE_CROSS_BUILD)
# If we're not cross compiling, then use Catch2 to generate some unit tests
find_package(Catch2 3 REQUIRED)
add_executable(test-jarnax
    ${CMAKE_CURRENT_SOURCE_DIR}/tests/yieldable.cpp
)
target_compile_definitions(test-jarnax PUBLIC UNITTEST)
target_include_directories(test-jarnax PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    # ${CMAKE_CURRENT_BINARY_DIR}/include
)
target_link_libraries(test-jarnax core Catch2::Catch2WithMain)
# include(CTest)
# include(Catch)
# catch_discover_tests(tests)

endif()
