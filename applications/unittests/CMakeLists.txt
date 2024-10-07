add_firmware(NAME jarnax-unittest
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/source/GlobalContext.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/SelfTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/LibcTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/TickTest.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/source/StackTest.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    MODULES
        jarnax
    CONFIGURATIONS
        ${LOCAL_CONFIGURATIONS}
    BOARDS
        ${LOCAL_BOARDS}
)
