
add_library(stm32 INTERFACE)
target_sources(stm32 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/source/initialize.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/timer.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/gpio.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/watchdog.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/can.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/RandomNumberGenerator.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/source/backup.cpp
    # ${CMAKE_CURRENT_SOURCE_DIR}/source/stm32/source/indicator.cpp
)
target_include_directories(stm32 INTERFACE ${CMAKE_CURRENT_SOURCE_DIR}/include)
target_link_libraries(stm32 INTERFACE arch-cortex)
