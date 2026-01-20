set(CMAKE_SYSTEM_NAME Generic) # No explicit OS, used by bare-metal systems
set(CMAKE_SYSTEM_PROCESSOR arm) # 32 bit arm

include(${CMAKE_CURRENT_LIST_DIR}/arm-none-eabi.cmake)

message(NOTICE "Enabling THUMB Mode")
add_compile_options(-mthumb -mno-thumb-interwork)
add_link_options(-mthumb -mthumb-interwork)

message(NOTICE "cpu=Cortex-M4")
add_compile_options(-mcpu=cortex-m4)
add_link_options(-mcpu=cortex-m4)
set(CORTEX_M "4")
set(ARCHITECTURE "armv7e-m")

message(NOTICE "Hard Float Single Precision")
add_compile_options(-mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant)
add_link_options(-mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant)

include(${CMAKE_CURRENT_LIST_DIR}/bare-metal.cmake)
