
add_library(segger INTERFACE)
target_sources(segger INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/segger/rtt.cpp
)
target_include_directories(segger INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(segger INTERFACE core arch-cortex)
