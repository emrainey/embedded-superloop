
add_library(board-stm32_f4ve_v2 INTERFACE)
target_include_directories(board-stm32_f4ve_v2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32_f4ve_v2
)
target_sources(board-stm32_f4ve_v2 INTERFACE
    ${CMAKE_CURRENT_SOURCE_DIR}/stm32_f4ve_v2/board.cpp
)
target_link_libraries(board-stm32_f4ve_v2 INTERFACE stm32 segger)
