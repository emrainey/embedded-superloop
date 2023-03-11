
add_library(memory INTERFACE)
target_sources(memory INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/memset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/memcpy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/fill.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/copy.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/compare.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/strlen.cpp
)
target_include_directories(memory INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
