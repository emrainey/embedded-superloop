host_unit_test(NAME jarnax-catch
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-countdown.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-yieldable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-superloop.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-stopwatch.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-transactable.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-ssd1306.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-monitor.cpp
        ${CMAKE_SOURCE_DIR}/modules/core/tests/source/conversions.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/modules/core/tests/include/
    LIBRARIES
        strict
        jarnax-interfaces
    GENERIC_MODULES
        memory core
    MODULES
        jarnax
    CATCH2
    FAKEIT
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)

host_unit_test(NAME jarnax-network
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-net-arp-entry.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-net-arp-table.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-net-ip-v4-address.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/catch2-net-eui-address.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/../source/Driver.cpp # HACK to get the jarnax::Driver
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
    LIBRARIES
        strict
        jarnax-interfaces
    GENERIC_MODULES
        memory core jarnax-net
    CATCH2
    FAKEIT
    NO_CONFIGURATIONS
    NO_BOARDS
)

host_unit_test(NAME jarnax-googletest
    SOURCES
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-mocks.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-coordinator.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-ssd1306-driver.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-ssd1306-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-w25q16bv-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-lps35hw-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-lsm9ds1-statemachine.cpp
        ${CMAKE_CURRENT_SOURCE_DIR}/gtest-lan8742a-statemachine.cpp
    INCLUDES
        ${CMAKE_CURRENT_SOURCE_DIR}/include
        ${CMAKE_CURRENT_SOURCE_DIR}/mocks
    LIBRARIES
        strict jarnax-interfaces
    GENERIC_MODULES
        memory core jarnax-lan8742a-driver
    MODULES
        jarnax
    GOOGLETEST
    CONFIGURATIONS
        basic
    BOARDS
        stm32_f4ve_v2
)