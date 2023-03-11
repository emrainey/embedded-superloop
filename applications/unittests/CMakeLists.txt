
if (CMAKE_CROSS_BUILD)
add_firmware(NAME jarnax-unittest-stm32
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SelfTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/LibcTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/TickTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/StackTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax board-stm32_f4ve_v2
    VENDOR stm32
)
else()
add_firmware(NAME jarnax-unittest-native
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SelfTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/LibcTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/TickTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/StackTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        jarnax board-stm32_f4ve_v2 native
    VENDOR stm32
)
endif()
