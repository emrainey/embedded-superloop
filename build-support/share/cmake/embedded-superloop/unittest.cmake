message(">>> Defining host unit test function")

function(host_unit_test)
    set(options DISABLE CATCH2 FAKEIT GOOGLETEST NO_CONFIGURATIONS NO_BOARDS)
    set(singles NAME)
    set(multiples SOURCES DEFINES INCLUDES LIBRARIES GENERIC_MODULES CHIP_MODULES SYSTEM_MODULES MODULES EXCLUDES TEST_ARGUMENTS CONFIGURATIONS BOARDS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    if(ARG_DISABLE)
        message(WARNING "Unit test ${ARG_NAME} is disabled")
        return()
    endif()

    required(ARG_NAME ARG_SOURCES)

    if(NOT ARG_CONFIGURATIONS AND NOT ARG_NO_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for unit test ${ARG_NAME}")
    endif()

    if(NOT ARG_BOARDS AND NOT ARG_NO_BOARDS)
        message(FATAL_ERROR "No boards specified for unit test ${ARG_NAME}")
    endif()

    if(ARG_NO_CONFIGURATIONS AND NOT DEFINED ARG_CONFIGURATIONS)
        set(ARG_CONFIGURATIONS none)
    endif()

    if(ARG_NO_BOARDS AND NOT DEFINED ARG_BOARDS)
        set(ARG_BOARDS all)
    endif()

    if(NOT BUILD_CROSS_TARGET)
        # message(STATUS "Adding host unit test ${ARG_NAME} ${ARG_CONFIGURATIONS} ${ARG_BOARDS}")
        foreach(cfg IN LISTS ARG_CONFIGURATIONS)
            set_configuration_name(TARGET_CONFIG ${cfg})
            foreach(board IN LISTS ARG_BOARDS)
                # Get the board name
                set_board_name(TARGET_BOARD ${board} ${cfg})
                set_unit_test_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${board})
                message("Adding ${LOCAL_TARGET} for ${cfg} ${board}")
                add_executable(${LOCAL_TARGET})
                target_sources(${LOCAL_TARGET} PRIVATE ${ARG_SOURCES})
                # Track only local/project library targets for whole-archive linking.
                # External test framework libraries (GTest, Catch2, etc.) are linked normally.
                set(TARGET_LOCAL_LIBRARIES)
                # Whole-archive is intentionally narrow: only board archives are forced in.
                # Applying whole-archive broadly to core/jarnax/stm32 causes duplicate
                # symbols in tests that provide local overrides/mocks.
                set(TARGET_WHOLE_LIBRARIES)
                # Link to the Configuration and the Board
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_CONFIG})
                list(APPEND TARGET_LOCAL_LIBRARIES ${TARGET_CONFIG})
                message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_CONFIG}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_BOARD})
                list(APPEND TARGET_LOCAL_LIBRARIES ${TARGET_BOARD})
                message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_BOARD}")
                if(TARGET ${TARGET_BOARD})
                    get_target_property(_BOARD_TARGET_TYPE ${TARGET_BOARD} TYPE)
                    if(_BOARD_TARGET_TYPE STREQUAL "STATIC_LIBRARY" OR _BOARD_TARGET_TYPE STREQUAL "OBJECT_LIBRARY")
                        list(APPEND TARGET_WHOLE_LIBRARIES ${TARGET_BOARD})
                    endif()
                endif()
                if (TARGET ${TARGET_BOARD})
                    inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_BOARD} PROPERTIES
                            FAMILY VENDOR CORTEX_M ARCHITECTURE
                            CHIP DEVICE PACKAGE CONFIGURATION
                    )
                    get_target_property(chip ${TARGET_BOARD} CHIP)
                else()
                    message(WARNING "Board target ${TARGET_BOARD} not found, skipping inheritence of properties")
                    set(chip all)
                endif()

                if(ARG_DEFINES)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE ${ARG_DEFINES})
                endif()

                foreach(lib IN LISTS ARG_LIBRARIES)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${lib})
                    list(APPEND TARGET_LOCAL_LIBRARIES ${lib})
                    message(STATUS "Linking ${LOCAL_TARGET} to ${lib}")
                endforeach()

                if(ARG_INCLUDES)
                    target_include_directories(${LOCAL_TARGET} PRIVATE ${ARG_INCLUDES})
                endif()

                foreach(module IN LISTS ARG_GENERIC_MODULES)
                    set_module_name(MODULE_TARGET ${module} none all)
                    target_link_libraries(${LOCAL_TARGET} PRIVATE ${MODULE_TARGET})
                    list(APPEND TARGET_LOCAL_LIBRARIES ${MODULE_TARGET})
                    message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                endforeach()

                foreach(module IN LISTS ARG_CHIP_MODULES)
                    set_module_name(MODULE_TARGET ${module} none ${chip})
                    target_link_libraries(${LOCAL_TARGET} PRIVATE ${MODULE_TARGET})
                    list(APPEND TARGET_LOCAL_LIBRARIES ${MODULE_TARGET})
                    message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                endforeach()

                foreach(module IN LISTS ARG_SYSTEM_MODULES)
                    set_module_name(MODULE_TARGET ${module} ${cfg} all)
                    target_link_libraries(${LOCAL_TARGET} PRIVATE ${MODULE_TARGET})
                    list(APPEND TARGET_LOCAL_LIBRARIES ${MODULE_TARGET})
                    message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                endforeach()

                foreach(module IN LISTS ARG_MODULES)
                    set_module_name(MODULE_TARGET ${module} ${cfg} ${chip})
                    target_link_libraries(${LOCAL_TARGET} PRIVATE ${MODULE_TARGET})
                    list(APPEND TARGET_LOCAL_LIBRARIES ${MODULE_TARGET})
                    message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                endforeach()

                if(ARG_CATCH2)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE CATCH2)
                    # External — linked normally, not whole-archived
                    target_link_libraries(${LOCAL_TARGET} PUBLIC Catch2::Catch2WithMain)
                endif()

                if(ARG_FAKEIT)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE FAKEIT)
                    # External — linked normally, not whole-archived
                    target_link_libraries(${LOCAL_TARGET} PRIVATE Catch2FakeIt)
                endif()

                if(ARG_GOOGLETEST)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE GOOGLETEST)
                    # External — linked normally, not whole-archived
                    target_link_libraries(${LOCAL_TARGET} PUBLIC GTest::gtest GTest::gmock GTest::gtest_main)
                endif()

                if(TARGET_WHOLE_LIBRARIES)
                    target_link_whole_libraries(${LOCAL_TARGET} ${TARGET_WHOLE_LIBRARIES})
                endif()

                print_target_properties(TARGET ${LOCAL_TARGET})
                append_global(TARGET_UNIT_TESTS ${ARG_NAME})

                if(NOT DEFINED UNIT_TEST_TARGETS)
                    set(UNIT_TEST_TARGETS "")
                    include(CTest)
                endif()

                list(APPEND UNIT_TEST_TARGETS ${LOCAL_TARGET})

                # CTest
                add_test(NAME ${LOCAL_TARGET} COMMAND ${LOCAL_TARGET} ${ARG_TEST_ARGUMENTS})

                foreach(excl IN LISTS ARG_EXCLUDES)
                    list(APPEND EXCLUDES --exclude ${excl})
                endforeach()

                # list(APPEND EXCLUDES --exclude '/tests/*' --exclude '*/catch2/*' --exclude '*/unittests/** --exclude **/googletest/*')
                # message(STATUS "Defining coverage-${ARG_NAME}")
                add_custom_target(coverage-${LOCAL_TARGET}
                    COMMAND mkdir -p ${CMAKE_BINARY_DIR}/coverage/
                    COMMAND gcovr --root ${CMAKE_CURRENT_SOURCE_DIR}
                        --exclude ${CMAKE_CURRENT_SOURCE_DIR}/tests
                        --exclude ${CMAKE_CURRENT_SOURCE_DIR}/generated/tests
                        --object-directory ${CMAKE_CURRENT_BINARY_DIR}
                        --xml-pretty --xml ${CMAKE_BINARY_DIR}/coverage/coverage-${LOCAL_TARGET}.xml
                        --html-details ${CMAKE_BINARY_DIR}/coverage/coverage-${LOCAL_TARGET}.html
                    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                    DEPENDS ${LOCAL_TARGET}
                )
                add_dependencies(coverage coverage-${LOCAL_TARGET})
            endforeach()
        endforeach()
    else()
        message("XX Skipping host unit test ${ARG_NAME} because BUILD_CROSS_TARGET=${BUILD_CROSS_TARGET}")
    endif()
endfunction()
