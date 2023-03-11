
add_library(native INTERFACE)
target_sources(native INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/peripherals.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/symbols.cpp
)
target_include_directories(native INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
target_link_libraries(native INTERFACE core stm32)
