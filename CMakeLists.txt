cmake_minimum_required(3.22.0 REQUIRED)

project(jarnax VERSION 1.0 LANGUAGES CXX ASM)

add_library(eabi INTERFACE)
target_compile_options(eabi
    INTERFACE
        -mthumb -mcpu=cortex-m4 # -mfpu=fpv5.nodp
        -fno-exceptions -fno-rtti
)

add_library(strict INTERFACE)
target_compile_options(strict
    INTERFACE
        -Wall -Wextra -Werror -pedantic
        -Wcast-align
        -Wconversion
        -Wsign-conversion
        -Wold-style-cast
        -Wshadow
        -Wlogical-op
        -Wsuggest-override
        -Wsuggest-final-types
        -Wsuggest-final-methods
)

add_library(firmware INTERFACE)
target_link_options(firmware
    INTERFACE
        -nostdlib
        --spec=nosys
        -Tsource/boot/gcc.ld
        -ffunction-sections
        -fdata-sections
        -gc-sections
        -fno-threadsafe-statics
        -fno-use-cxa-atexit
)

add_library(system
    PUBLIC
        source/boot/vector.cpp
        source/boot/initialize.cpp
        source/boot/configure.cpp
        source/boot/system.cpp
)
target_include_directories(system PUBLIC include)
target_link_libraries(system PUBLIC eabi strict)

add_executable(jarnax.elf PUBLIC apps/main.cpp)
target_link_libraries(jarnax.elf PUBLIC system firmware)

