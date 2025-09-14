message(">>> Defining architecture functions")

# An architecture is a set of hardware features that are common to a set of microcontrollers.
# An architecture is influenced by the system configuration but not by the board configuration.
# The architecture is an interface library.
function(add_architecture)
    set(options DISABLE)
    set(singles NAME SYSTEM)
    set(multiples SOURCES CHIPS INCLUDES DEFINES LIBRARIES CONFIGURATIONS GENERIC_MODULES SYSTEM_MODULES CHIP_MODULES MODULES) # has no BOARD options
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if(ARG_DISABLE)
        message(WARNING "Architecture ${ARG_NAME} is disabled")
        return()
    endif()

    required(ARG_NAME ARG_SYSTEM ARG_CONFIGURATIONS ARG_CHIPS)

    foreach(cfg IN LISTS ARG_CONFIGURATIONS)
        set_configuration_name(TARGET_CONFIGURATION ${cfg})
        foreach(chip IN LISTS ARG_CHIPS)
            set_chip_name(TARGET_CHIP ${chip})
            set_arch_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${chip})
            add_library(${LOCAL_TARGET} STATIC ${ARG_SOURCES})
            message("Adding architecture ${LOCAL_TARGET}")
            target_compile_definitions(${LOCAL_TARGET} PUBLIC ${ARG_DEFINES} ARCHITECTURE=${ARG_NAME})
            set_target_properties(${LOCAL_TARGET} PROPERTIES
                # TRANSITIVE_LINK_PROPERTIES "ARCH_LINKERSCRIPTS"
                ARCH_LINKERSCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/linkerscripts
            )
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_CHIP})
            message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_CHIP}")

            # Should work transitively through chip
            # target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_FAMILY})
            # message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_FAMILY}")

            target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_CONFIGURATION})
            message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_CONFIGURATION}")

            inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_CHIP} PROPERTIES
               FAMILY VENDOR CORTEX_M ARCHITECTURE VENDOR_LINKERSCRIPT VENDOR_LINKERSCRIPTS
               CHIP DEVICE PACKAGE
            )
            inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_CONFIGURATION} PROPERTIES
               CONFIGURATION
            )

            if (ARG_SYSTEM)
                set_module_name(SYSTEM_TARGET ${ARG_SYSTEM} ${cfg} ${chip})
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${SYSTEM_TARGET})
                message(STATUS "Linking ${LOCAL_TARGET} to system ${SYSTEM_TARGET}")
            endif()

            if(DEFINED ARG_INCLUDES)
                target_include_directories(${LOCAL_TARGET} PUBLIC ${ARG_INCLUDES})
            endif()

            if(DEFINED ARG_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
            endif()

            foreach(module IN LISTS ARG_GENERIC_MODULES)
                set_module_name(MODULE_TARGET ${module} none all)
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            foreach(module IN LISTS ARG_SYSTEM_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} all)
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            foreach(module IN LISTS ARG_CHIP_MODULES)
                set_module_name(MODULE_TARGET ${module} none ${chip})
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            foreach(module IN LISTS ARG_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} ${chip})
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            # print_target_properties(TARGET ${LOCAL_TARGET})
        endforeach()
    endforeach()
endfunction()

# add_architecture(NAME cortex
#     CHIPS all
#     CONFIGURATIONS
#         none ${LOCAL_CONFIGURATIONS}
# )