message(">>> Defining board functions")
if(LOCAL_BOARDS)
    message(STATUS "LOCAL_BOARDS=${LOCAL_BOARDS}")
else()
    message(FATAL_ERROR "LOCAL_BOARDS not defined")
endif()

# A board defines the hardware configuration which the system will run on. It can be influenced by the system configuration.
# A board depends on a vendor which must be set.
# @param ARCH The architecture module which the board uses.
# @param CHIP The specific chip that the board has.
# @param GENERIC_MODULES Are modules that don't care about the chip variant, board or the configuration
# @param SYSTEM_MODULES Are modules that care about the configuration but not the board
# @param CHIP_MODULES Are modules that care about the board but not the configuration
# @param MODULES Are modules that care about both the configuration and the board
function(add_board)
    set(options DISABLE)
    set(singles NAME ARCH CHIP)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES CONFIGURATIONS GENERIC_MODULES SYSTEM_MODULES CHIP_MODULES MODULES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    if(ARG_DISABLE)
        message(WARNING "Board ${ARG_NAME} is disabled")
        return()
    endif()

    required(ARG_NAME ARG_ARCH ARG_CHIP ARG_CONFIGURATIONS)

    foreach(cfg IN LISTS ARG_CONFIGURATIONS)
        set_configuration_name(TARGET_CONFIGURATION ${cfg})
        set_arch_name(TARGET_ARCH ${ARG_ARCH} ${cfg} ${ARG_CHIP})
        set_board_name(LOCAL_TARGET ${ARG_NAME} ${cfg})
        message("Adding ${LOCAL_TARGET}")
        add_library(${LOCAL_TARGET} STATIC ${ARG_SOURCES})
        target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_CONFIGURATION})
        message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_CONFIGURATION}")
        # we will get chip through this
        target_link_libraries(${LOCAL_TARGET} PUBLIC ${TARGET_ARCH})
        message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_ARCH}")
        set_target_properties(${LOCAL_TARGET} PROPERTIES
            # put all the properties into the board now
            BOARD_LINKERSCRIPTS ${CMAKE_CURRENT_SOURCE_DIR}/linkerscripts
            OZONE_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/scripts/Ozone.jdebug.in
            GDB_CLIENT_TEMPLATE ${CMAKE_CURRENT_SOURCE_DIR}/scripts/client.gdb.in
        )
        inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_ARCH} PROPERTIES
           FAMILY VENDOR CORTEX_M ARCHITECTURE VENDOR_LINKERSCRIPT VENDOR_LINKERSCRIPTS
           CHIP DEVICE PACKAGE CONFIGURATION
           ARCH_LINKERSCRIPTS
        )
        if(ARG_INCLUDES)
            target_include_directories(${LOCAL_TARGET} PUBLIC ${ARG_INCLUDES})
        endif()

        if(ARG_LIBRARIES)
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${ARG_LIBRARIES})
        endif()

        if(ARG_DEFINES)
            target_compile_definitions(${LOCAL_TARGET} PUBLIC ${ARG_DEFINES})
        endif()

        foreach (module IN LISTS ARG_GENERIC_MODULES)
            set_module_name(MODULE_TARGET ${module} none all)
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
        endforeach()

        foreach(module IN LISTS ARG_CHIP_MODULES)
            set_module_name(MODULE_TARGET ${module} none ${ARG_CHIP})
            # pull the chip from the module and make sure it's for this board
            get_target_property(_CHIP ${MODULE_TARGET} CHIP)
            if(NOT _CHIP STREQUAL ARG_CHIP)
                message(FATAL_ERROR "Module ${MODULE_TARGET} is for chip ${_CHIP} but this board is for chip ${ARG_CHIP}")
            endif()
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
        endforeach()

        foreach(module IN LISTS ARG_SYSTEM_MODULES)
            set_module_name(MODULE_TARGET ${module} ${cfg} all)
            # System modules don't care what chip they are built against
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
        endforeach()

        foreach(module IN LISTS ARG_MODULES)
            set_module_name(MODULE_TARGET ${module} ${cfg} ${ARG_CHIP})
            # pull the chip from the module and make sure it's for this chip
            get_target_property(_ARCH ${MODULE_TARGET} ARCH)
            get_target_property(_CHIP ${MODULE_TARGET} CHIP)
            if(NOT _CHIP STREQUAL ARG_CHIP)
                # Prevent Linking against modules which aren't built for this ARCH/CHIP
                message(FATAL_ERROR "Module ${MODULE_TARGET} is built for chip ${_CHIP} but this board is built for chip ${ARG_CHIP}")
            endif()
            target_link_libraries(${LOCAL_TARGET} PUBLIC ${MODULE_TARGET})
            message(STATUS "Linking ${LOCAL_TARGET} to ${MODULE_TARGET}")
        endforeach()

        print_target_properties(TARGET ${LOCAL_TARGET})

    endforeach()
endfunction()
