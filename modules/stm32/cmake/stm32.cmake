set(CMAKE_SYSTEM_NAME Generic)
set(CMAKE_SYSTEM_PROCESSOR arm)

find_program(CMAKE_C_COMPILER
    NAMES
        arm-none-eabi-gcc
    REQUIRED
    HINTS
        /Applications/ArmGNUToolchain/12.3.rel1/arm-none-eabi/bin  # 12.3.1
        /Applications/ARM/bin # 10.3.1
)
find_program(CMAKE_CXX_COMPILER
    NAMES
        arm-none-eabi-g++
    REQUIRED
    HINTS
        /Applications/ArmGNUToolchain/12.3.rel1/arm-none-eabi/bin  # 12.3.1
        /Applications/ARM/bin # 10.3.1
)
find_program(CMAKE_OBJDUMP
    NAMES
        arm-none-eabi-objdump
    REQUIRED
    HINTS
        /Applications/ArmGNUToolchain/12.3.rel1/arm-none-eabi/bin  # 12.3.1
        /Applications/ARM/bin # 10.3.1
)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

set(CMAKE_CROSS_BUILD TRUE)

message(NOTICE "Enabling THUMB Mode")
add_compile_options(-mthumb -mno-thumb-interwork)
add_link_options(-mthumb -mthumb-interwork)

message(NOTICE "cpu=Cortex-M4")
add_compile_options(-mcpu=cortex-m4)
add_link_options(-mcpu=cortex-m4)

message(NOTICE "Hard Float Single Precision")
add_compile_options(-mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant)
add_link_options(-mfpu=fpv4-sp-d16 -mfloat-abi=hard -fsingle-precision-constant)

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions -fno-rtti)

message(STATUS "Additional Flags for Stack, Statics, Linkage")
add_compile_options(
    -ffunction-sections
    -fdata-sections
    -flto
    -fno-threadsafe-statics
    -fno-use-cxa-atexit
    -fomit-frame-pointer
    -fstack-usage
    -Wstack-usage=32768
)

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
    -Wl,--build-id=none
    -Wl,--enable-new-dtags
    -Wl,--sort-section=name
    -Wl,--no-undefined
    -Wl,--as-needed
    -Wl,--hash-style=gnu
    #-Wl,-z,relro
    -Wl,-z,now
)

set(COMPILER_MATH_LIB gcc)