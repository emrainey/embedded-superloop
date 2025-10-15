message(">>> Defining module functions")

# A module is a component that could be influenced by the system configuration and the board configuration
# A module with no configurations and no board is a generic module that can be used in anywhere and has the -none-all postfix.
# A module with no configurations and some board is a board module and has a -none-$board postfix.
# A module with some configurations and no board is a system module and has a -$cfg-all postfix.
# A module with some configurations and some board is a normal module and has a -$cfg-$board postfix.
function(add_module)
    set(options DISABLE NO_CONFIGURATIONS)
    set(singles NAME ARCH)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES CONFIGURATIONS BOARDS GENERIC_MODULES CHIP_MODULES SYSTEM_MODULES MODULES CHIPS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    if(ARG_DISABLE)
        message(WARNING "Module ${ARG_NAME} is disabled")
        return()
    endif()

    # required(NAME SOURCES)

    if(NOT ARG_CONFIGURATIONS AND NOT ARG_NO_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for module ${ARG_NAME}")
    endif()

    if(ARG_NO_CONFIGURATIONS)
        set(ARG_CONFIGURATIONS none)
    endif()

    if (NOT ARG_CHIPS)
        set(ARG_CHIPS all)
    endif()

    foreach (cfg IN LISTS ARG_CONFIGURATIONS)
        set_configuration_name(TARGET_CONFIGURATION ${cfg})
        foreach (chip IN LISTS ARG_CHIPS)
            if (cfg STREQUAL "none" AND chip STREQUAL "all")
                set(MODULE_TYPE GENERIC)
            elseif (cfg STREQUAL "none" AND NOT chip STREQUAL "all")
                set(MODULE_TYPE CHIP)
            elseif (NOT cfg STREQUAL "none" AND chip STREQUAL "all")
                set(MODULE_TYPE SYSTEM)
            else()
                set(MODULE_TYPE SPECIFIC)
            endif()
            set_module_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${chip})
            add_library(${LOCAL_TARGET})
            target_sources(${LOCAL_TARGET} PRIVATE ${ARG_SOURCES})
            message("Adding ${LOCAL_TARGET} as ${MODULE_TYPE} module")
            if(ARG_DEFINES)
                target_compile_definitions(${LOCAL_TARGET} PUBLIC ${ARG_DEFINES})
            endif()
            foreach(lib IN LISTS ARG_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${lib})
                message(STATUS "Linking ${LOCAL_TARGET} to ${lib}")
            endforeach()
            if(ARG_INCLUDES)
                target_include_directories(${LOCAL_TARGET} PUBLIC ${ARG_INCLUDES})
            endif()
            set_target_properties(${LOCAL_TARGET} PROPERTIES
                # TRANSITIVE_LINK_PROPERTIES "ARCH_LINKERSCRIPTS"
                # The type of module this is (GENERIC, CHIP, SYSTEM, SPECIFIC)
                MODULE_TYPE ${MODULE_TYPE}
            )
            if(ARG_ARCH)
                set_arch_name(TARGET_ARCH ${ARG_ARCH} ${cfg} ${chip})
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_ARCH})
                message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_ARCH}")
                inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_ARCH} PROPERTIES
                    FAMILY VENDOR CORTEX_M ARCHITECTURE
                    CHIP DEVICE PACKAGE CONFIGURATION
                )
            endif()
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_CONFIGURATION})
            message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_CONFIGURATION}")

            # Everyone can depend on generic modules
            foreach(module IN LISTS ARG_GENERIC_MODULES)
                set_module_name(MODULE_TARGET ${module} none all)
                message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            # Generic modules cannot have board or system or specific modules
            if (MODULE_TYPE STREQUAL "GENERIC")
                if (ARG_CHIP_MODULES)
                    message(FATAL_ERROR "Generic module ${ARG_NAME} cannot have board modules: ${ARG_CHIP_MODULES}")
                endif()
                if (ARG_SYSTEM_MODULES)
                    message(FATAL_ERROR "Generic module ${ARG_NAME} cannot have system modules: ${ARG_SYSTEM_MODULES}")
                endif()
                if (ARG_MODULES)
                    message(FATAL_ERROR "Generic module ${ARG_NAME} cannot have specific modules: ${ARG_MODULES}")
                endif()
            endif()

            # Board modules cannot have system or specific modules as both require configurations
            if (MODULE_TYPE STREQUAL "CHIP")
                if (ARG_SYSTEM_MODULES)
                    message(FATAL_ERROR "Chip module ${ARG_NAME} cannot have SYSTEM modules: ${ARG_SYSTEM_MODULES}")
                endif()
                if (ARG_MODULES)
                    message(FATAL_ERROR "Chip module ${ARG_NAME} cannot have specific modules: ${ARG_MODULES}")
                endif()
            endif()

            # System modules cannot have specific modules or board modules as they don't have a board
            if (MODULE_TYPE STREQUAL "SYSTEM")
                if (ARG_CHIP_MODULES)
                    message(FATAL_ERROR "System module ${ARG_NAME} cannot have CHIP modules: ${ARG_CHIP_MODULES}")
                endif()
                if (ARG_MODULES)
                    message(FATAL_ERROR "System module ${ARG_NAME} cannot have specific modules: ${ARG_MODULES}")
                endif()
            endif()

            foreach(module IN LISTS ARG_CHIP_MODULES)
                set_module_name(MODULE_TARGET ${module} none ${board})
                message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            foreach(module IN LISTS ARG_SYSTEM_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} all)
                message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            foreach(module IN LISTS ARG_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} ${board})
                message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
                target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            endforeach()

            print_target_properties(TARGET ${LOCAL_TARGET})
            append_global(TARGET_MODULES ${ARG_NAME})
        endforeach()
    endforeach()
endfunction()
