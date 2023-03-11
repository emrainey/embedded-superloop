
add_library(arch-cortex INTERFACE)
target_sources(arch-cortex INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/vectors.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/reset.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/cache.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/trigger.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/swo.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/nvic.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/mpu.cpp
)
target_include_directories(arch-cortex INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)
