add_module(NAME memory
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/memset.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/memcpy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/fill.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/copy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/compare.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/strlen.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    NO_BOARDS
    NO_CONFIGURATIONS
)
