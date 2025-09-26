if (NOT BUILD_CROSS_TARGET)
add_module(NAME native
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        qemu
    BOARDS
        netduinoplus2
)
endif()