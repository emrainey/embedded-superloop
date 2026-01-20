set(CMAKE_SYSTEM_NAME Generic) # No explicit OS, used by bare-metal systems
set(CMAKE_SYSTEM_PROCESSOR arm) # 32 bit arm

include(${CMAKE_CURRENT_LIST_DIR}/arm-none-eabi.cmake)

message(NOTICE "Enabling THUMB Mode")
add_compile_options(-mthumb -mno-thumb-interwork)
add_link_options(-mthumb -mthumb-interwork)

message(NOTICE "cpu=Cortex-M7")
add_compile_options(-mcpu=cortex-m7)
add_link_options(-mcpu=cortex-m7)
set(CORTEX_M "7")
set(ARCHITECTURE "armv7e-m")

message(NOTICE "Hard Float Double Precision")
add_compile_options(-mfpu=fpv5-d16 -mfloat-abi=hard)
add_link_options(-mfpu=fpv5-d16 -mfloat-abi=hard)

include(${CMAKE_CURRENT_LIST_DIR}/bare-metal.cmake)
