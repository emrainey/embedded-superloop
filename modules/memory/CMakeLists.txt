add_module(NAME memory
    SOURCES
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,${CMAKE_CURRENT_SOURCE_DIR}/source/memset.cpp,>
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,${CMAKE_CURRENT_SOURCE_DIR}/source/memcpy.cpp,>
        $<IF:$<BOOL:${BUILD_CROSS_TARGET}>,${CMAKE_CURRENT_SOURCE_DIR}/source/memmove.cpp,>
        ${CMAKE_CURRENT_SOURCE_DIR}/source/fill.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/copy.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/compare.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/strlen.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/last_character.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
    NO_CONFIGURATIONS
)
