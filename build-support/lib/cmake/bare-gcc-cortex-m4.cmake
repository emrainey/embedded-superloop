set(CMAKE_SYSTEM_NAME Generic) # No explicit OS, used by bare-metal systems
set(CMAKE_SYSTEM_PROCESSOR arm)

find_program(CMAKE_C_COMPILER NAMES arm-none-eabi-gcc REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES arm-none-eabi-g++ REQUIRED)
find_program(CMAKE_ASM_COMPILER NAMES arm-none-eabi-g++ REQUIRED)
find_program(CMAKE_OBJDUMP NAMES arm-none-eabi-objdump REQUIRED)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(BUILD_CROSS_TARGET TRUE)
set(CMAKE_BUILD_TYPE Debug)

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

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions -fno-rtti)

message(STATUS "Additional Flags for Stack, Statics, Linkage")
add_compile_options(
    # -ffreestanding
    -ffunction-sections
    -fdata-sections
    # -flto
    -fno-threadsafe-statics
    -fno-use-cxa-atexit
    -fomit-frame-pointer
    -fstack-usage
    -Wstack-usage=32768
    # -fno-inline
)

if (CMAKE_BUILD_TYPE STREQUAL "Debug")
add_compile_options(-O1 -g3 -ggdb3)
endif()

message(STATUS "Enable reproducible build flags")
add_compile_options(
    -fdebug-prefix-map=./=
    -ffile-prefix-map=./=
    -fno-stack-protector
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-ident
)
add_link_options(
    LINKER:--build-id=none
    LINKER:--enable-new-dtags
    LINKER:--sort-section=name
    LINKER:--no-undefined
    # LINKER:--as-needed
    LINKER:--hash-style=gnu
    #LINKER:-z,relro
    LINKER:-z,now
)

list(APPEND COMPILER_MATH_LIBS gcc m)