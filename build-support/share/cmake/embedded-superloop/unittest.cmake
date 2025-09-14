
function(host_unit_test)
    set(options DISABLE CATCH2 FAKEIT GOOGLETEST NO_CONFIGURATIONS NO_BOARDS)
    set(singles NAME)
    set(multiples SOURCES INCLUDES LIBRARIES MODULES EXCLUDES DEFINES TEST_ARGUMENTS CONFIGURATIONS BOARDS)
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
            foreach(board IN LISTS ARG_BOARDS)
                set_module_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${board})
                message("Adding host unit test ${LOCAL_TARGET} for ${cfg} ${board}")
                add_executable(${LOCAL_TARGET} ${ARG_SOURCES})

                if(ARG_INCLUDES)
                    target_include_directories(${LOCAL_TARGET} PRIVATE ${ARG_INCLUDES})
                endif()

                if(ARG_LIBRARIES)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
                endif()

                foreach(module IN LISTS ARG_GENERIC_MODULES)
                    set_module_name(MODULE_TARGET ${module} none all)
                    message(STATUS "Depends on ${MODULE_TARGET}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
                endforeach()

                foreach(module IN LISTS ARG_CHIP_MODULES)
                    set_module_name(MODULE_TARGET ${module} none ${board})
                    message(STATUS "Depends on ${MODULE_TARGET}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
                endforeach()

                foreach(module IN LISTS ARG_SYSTEM_MODULES)
                    set_module_name(MODULE_TARGET ${module} ${cfg} all)
                    message(STATUS "Depends on ${MODULE_TARGET}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
                endforeach()

                foreach(module IN LISTS ARG_MODULES)
                    set_module_name(MODULE_TARGET ${module} ${cfg} ${board})
                    message(STATUS "Depends on ${MODULE_TARGET}")
                    target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
                endforeach()

                if(ARG_CATCH2)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE CATCH2)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC Catch2::Catch2WithMain)
                endif()

                if(ARG_FAKEIT)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE FAKEIT)
                    target_link_libraries(${LOCAL_TARGET} PRIVATE Catch2FakeIt)
                endif()

                if(ARG_GOOGLETEST)
                    target_compile_definitions(${LOCAL_TARGET} PRIVATE GOOGLETEST)
                    target_link_libraries(${LOCAL_TARGET} PUBLIC GTest::gtest GTest::gmock GTest::gtest_main)
                endif()

                target_compile_definitions(${LOCAL_TARGET} PRIVATE UNITTEST ${ARG_DEFINES})

                print_target_properties(TARGET ${LOCAL_TARGET})

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
        message(STATUS "Skipping host unit test ${ARG_NAME} because BUILD_CROSS_TARGET=${BUILD_CROSS_TARGET}")
    endif()
endfunction()
