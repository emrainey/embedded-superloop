if (NOT CMAKE_CROSS_BUILD)
add_module(NAME native
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
endif()