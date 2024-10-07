cmake_minimum_required(VERSION 3.28)


project(jarnax-bare-metal-apps
        VERSION 0.1.49
        LANGUAGES CXX ASM)

set(CMAKE_C_STANARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)
set(CMAKE_CXX_STANDARD 20)
# set(CMAKE_CXX_SCAN_FOR_MODULES ON)

list(APPEND LOCAL_MODULES memory core) # These don't depend on anything
list(APPEND LOCAL_MODULES cortex stm32 segger jarnax native) # These depend on config and board
list(APPEND LOCAL_APPLICATIONS unittests simple)
list(APPEND LOCAL_CONFIGURATIONS basic)
list(APPEND LOCAL_BOARDS stm32_f4ve_v2)

find_package(jarnax REQUIRED)

message(STATUS CMAKE_CROSS_BUILD=${CMAKE_CROSS_BUILD})
