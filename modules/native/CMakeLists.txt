if (NOT BUILD_CROSS_TARGET)
# This module allows us to build firmware into a host executeable that we can "boot"
# by providing main() and executing the reset handler
add_module(NAME native
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    ARCH
        cortex
    CHIPS
        ${TARGET_CHIPS}
    CONFIGURATIONS
        ${TARGET_CONFIGURATIONS}
)
endif()