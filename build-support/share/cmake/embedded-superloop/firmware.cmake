message(">>> Defining firmware functions")

#
# Creates a firmware target
# @param NAME The name of the firmware
# @param VENDOR The vendor of the firmware
# @param SOURCES The source files for the firmware
# @param INCLUDES The include directories for the firmware
# @param DEFINES The preprocessor definitions for the firmware
# @param LIBRARIES The libraries to link against
function(add_firmware)
    set(options DISABLE)
    set(singles NAME)
    set(multiples SOURCES INCLUDES DEFINES LIBRARIES MODULES GENERIC_MODULES CHIP_MODULES SYSTEM_MODULES CONFIGURATIONS BOARDS)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    if(NOT ARG_CONFIGURATIONS)
        message(FATAL_ERROR "No configurations specified for firmware ${ARG_TARGET}")
    endif()

    if(NOT ARG_BOARDS)
        message(FATAL_ERROR "No boards specified for firmware ${ARG_TARGET}")
    endif()

    if(ARG_DISABLE)
        message(WARNING "Firmware ${ARG_NAME} is disabled")
        return()
    endif()

    foreach(cfg IN LISTS ARG_CONFIGURATIONS)
        set_configuration_name(TARGET_CONFIG ${cfg})
        foreach(board IN LISTS ARG_BOARDS)
            # Get the board name
            set_board_name(TARGET_BOARD ${board} ${cfg})
            set_firmware_name(LOCAL_TARGET ${ARG_NAME} ${cfg} ${board})
            if (BUILD_CROSS_TARGET)
                if (NOT TARGET ${TARGET_BOARD})
                    message("XX Skipping ${LOCAL_TARGET}")
                    continue()
                endif()
            endif()
            message("Adding ${LOCAL_TARGET}.elf for ${cfg} ${board}")
            add_executable(${LOCAL_TARGET}.elf)
            target_sources(${LOCAL_TARGET}.elf PRIVATE ${ARG_SOURCES})
            # Track linked targets in declaration order so supported linkers can rescan archives.
            set(TARGET_LIBRARIES)
            # Link to the Configuration and the Board
            target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${TARGET_CONFIG})
            list(APPEND TARGET_LIBRARIES ${TARGET_CONFIG})
            message(STATUS "Linking ${LOCAL_TARGET}.elf to ${TARGET_CONFIG}")
            target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${TARGET_BOARD})
            list(APPEND TARGET_LIBRARIES ${TARGET_BOARD})
            message(STATUS "Linking ${LOCAL_TARGET}.elf to ${TARGET_BOARD}")

            inherit_target_properties(CHILD ${LOCAL_TARGET}.elf PARENT ${TARGET_BOARD} PROPERTIES
                FAMILY FAMILY_NAMESPACE VENDOR CORTEX_M ARCHITECTURE VENDOR_LINKERSCRIPT VENDOR_LINKERSCRIPTS
                CHIP DEVICE PACKAGE CONFIGURATION
                ARCH_LINKERSCRIPTS BOARD_LINKERSCRIPTS
            )
            get_target_property(chip ${TARGET_BOARD} CHIP)

            if(ARG_DEFINES)
                target_compile_definitions(${LOCAL_TARGET}.elf PRIVATE ${ARG_DEFINES})
            endif()

            foreach(lib IN LISTS ARG_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE ${lib})
                list(APPEND TARGET_LIBRARIES ${lib})
                message(STATUS "Linking ${LOCAL_TARGET}.elf to ${lib}")
            endforeach()

            if(ARG_INCLUDES)
                target_include_directories(${LOCAL_TARGET}.elf PRIVATE ${ARG_INCLUDES})
            endif()

            foreach(module IN LISTS ARG_GENERIC_MODULES)
                set_module_name(MODULE_TARGET ${module} none all)
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE ${MODULE_TARGET})
                list(APPEND TARGET_LIBRARIES ${MODULE_TARGET})
                message(STATUS "Linking ${LOCAL_TARGET}.elf to ${MODULE_TARGET}")
            endforeach()

            foreach(module IN LISTS ARG_CHIP_MODULES)
                set_module_name(MODULE_TARGET ${module} none ${chip})
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE ${MODULE_TARGET})
                list(APPEND TARGET_LIBRARIES ${MODULE_TARGET})
                message(STATUS "Linking ${LOCAL_TARGET}.elf to ${MODULE_TARGET}")
            endforeach()

            foreach(module IN LISTS ARG_SYSTEM_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} all)
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE ${MODULE_TARGET})
                list(APPEND TARGET_LIBRARIES ${MODULE_TARGET})
                message(STATUS "Linking ${LOCAL_TARGET}.elf to ${MODULE_TARGET}")
            endforeach()

            foreach(module IN LISTS ARG_MODULES)
                set_module_name(MODULE_TARGET ${module} ${cfg} ${chip})
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE ${MODULE_TARGET})
                list(APPEND TARGET_LIBRARIES ${MODULE_TARGET})
                message(STATUS "Linking ${LOCAL_TARGET}.elf to ${MODULE_TARGET}")
            endforeach()

            target_compile_options(${LOCAL_TARGET}.elf PRIVATE # -fverbose-asm -save-temps)
                -fmacro-prefix-map=${CMAKE_SOURCE_DIR}=. # trims __FILE__ to be relative and deterministic
            )

            if(DEFINED COMPILER_MATH_LIBS AND NOT COMPILER_MATH_LIBS STREQUAL "")
                message(STATUS "Linking with math libraries ${COMPILER_MATH_LIBS}")
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${COMPILER_MATH_LIBS})
                list(APPEND TARGET_LIBRARIES ${COMPILER_MATH_LIBS})
            endif()

            if(CMAKE_CXX_LINK_GROUP_USING_RESCAN_SUPPORTED AND TARGET_LIBRARIES)
                target_link_libraries(${LOCAL_TARGET}.elf PRIVATE
                    "$<LINK_GROUP:RESCAN,${TARGET_LIBRARIES}>"
                )
            endif()

            if(BUILD_CROSS_TARGET)
                get_target_property(ARCH_LINKERSCRIPTS ${LOCAL_TARGET}.elf ARCH_LINKERSCRIPTS)
                get_target_property(BOARD_LINKERSCRIPTS ${LOCAL_TARGET}.elf BOARD_LINKERSCRIPTS)
                get_target_property(VENDOR_LINKERSCRIPTS ${LOCAL_TARGET}.elf VENDOR_LINKERSCRIPTS)
                get_target_property(VENDOR_LINKERSCRIPT ${LOCAL_TARGET}.elf VENDOR_LINKERSCRIPT)
                get_target_property(BOARD_DEVICE ${LOCAL_TARGET}.elf DEVICE)
                # Pull the set of linkerscript paths from the board and the chip modules
                # Sadly, this is a bit of a hack since ld can't handle the -L option correctly.
                # (It only uses the values stated *before* the -T option)
                # If it could we would just use the target_link_options() to set the -L options
                target_link_options(${LOCAL_TARGET}.elf PRIVATE
                    -v -nostdlib
                    # --specs=nosys
                    LINKER:-V
                    LINKER:-L,${ARCH_LINKERSCRIPTS}
                    LINKER:-L,${BOARD_LINKERSCRIPTS}
                    LINKER:-L,${VENDOR_LINKERSCRIPTS}
                    $<$<CXX_COMPILER_ID:GNU>:LINKER:-T,${VENDOR_LINKERSCRIPT}>
                    LINKER:-Map,${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.map
                    LINKER:--print-memory-usage
                    # LINKER:--print-map
                    LINKER:--stats
                    LINKER:-gc-sections
                    LINKER:-cref
                )

                # Get the all the .ld files in the linkerscripts directories in order to form dependencies on them
                file(GLOB_RECURSE LINKERSCRIPTS ${ARCH_LINKERSCRIPTS}/cortex-m${CORTEX_M}*.ld ${BOARD_LINKERSCRIPTS}/*.ld ${VENDOR_LINKERSCRIPTS}/${BOARD_DEVICE}*.ld)
                foreach(LINKERSCRIPT ${LINKERSCRIPTS})
                    message(STATUS "  Linker script dependency: ${LINKERSCRIPT}")
                    # Set the INTERFACE_LINK_DEPENDS property
                    set_target_properties(${LOCAL_TARGET}.elf PROPERTIES
                        INTERFACE_LINK_DEPENDS ${LINKERSCRIPT}
                    )
                endforeach()


                # add_dependencies(${ARG_NAME}.elf ${ARG_NAME}-ld-script)
                set(ARG_ELF ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.elf)
                set(ARG_DISASM ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.s)
                add_custom_command(
                    OUTPUT ${ARG_DISASM}
                    DEPENDS ${ARG_ELF}
                    COMMAND ${CMAKE_OBJDUMP} -D ${ARG_ELF} -s -marm -C -z > ${ARG_DISASM}
                    COMMENT "Creating Disassembly of ${ARG_ELF}"
                )

                # add_dependencies(${ARG_NAME}.elf ${ARG_LINKERSCRIPT})
                add_custom_target(disassembly-${LOCAL_TARGET} ALL DEPENDS ${ARG_DISASM})

                # File the relative path from the build directory to the binary
                file(RELATIVE_PATH LOCAL_TARGET_BINARY_PATH ${CMAKE_SOURCE_DIR} ${ARG_ELF})

                # Generate a debug file for the Ozone debugger for this firmware
                get_target_property(LOCAL_BOARD_OZONE ${TARGET_BOARD} OZONE_TEMPLATE)
                set(JDEBUG_FILE ${CMAKE_SOURCE_DIR}/testing/${LOCAL_TARGET}.jdebug)
                configure_file(${LOCAL_BOARD_OZONE} ${JDEBUG_FILE} @ONLY)
                get_target_property(LOCAL_BOARD_GDB_CLIENT ${TARGET_BOARD} GDB_CLIENT_TEMPLATE)
                set(GDB_FILE ${CMAKE_SOURCE_DIR}/testing/${LOCAL_TARGET}.gdb)
                configure_file(${LOCAL_BOARD_GDB_CLIENT} ${GDB_FILE} @ONLY)
                add_custom_target(ozone-${LOCAL_TARGET}
                    COMMAND /Applications/SEGGER/Ozone/Ozone.app/Contents/MacOS/Ozone ${JDEBUG_FILE}
                    DEPENDS ${JDEBUG_FILE} ${ARG_ELF})

                if(NOT TARGET gdb-server-${BOARD_DEVICE})
                    message(STATUS "Adding gdb-server-${BOARD_DEVICE}")
                    add_custom_target(gdb-server-${BOARD_DEVICE}
                        # Default ports 2331, 2332, 2333
                        COMMAND JLinkGDBServer -if SWD -device ${BOARD_DEVICE} -speed 20000 -usb -NoGUI=1 -ir -halt -vd
                    )
                endif()

                add_custom_target(gdb-client-${LOCAL_TARGET}
                    COMMAND arm-none-eabi-gdb ${ARG_ELF} -x ${GDB_FILE}
                    DEPENDS ${GDB_FILE} ${ARG_ELF})
                list(APPEND REMOVE_SECTIONS)
                set(ARG_BIN ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.bin)
                add_custom_command(
                    OUTPUT ${ARG_BIN}
                    DEPENDS ${ARG_ELF}
                    COMMAND ${CMAKE_OBJCOPY} -O binary ${ARG_ELF} ${REMOVE_SECTIONS} ${ARG_BIN}
                    COMMENT "Creating Binary of ${LOCAL_TARGET}.elf"
                )
                add_custom_target(binary-${LOCAL_TARGET} ALL DEPENDS ${ARG_BIN})
                set(ARG_HEX ${CMAKE_CURRENT_BINARY_DIR}/${LOCAL_TARGET}.hex)
                add_custom_command(
                    OUTPUT ${ARG_HEX}
                    DEPENDS ${ARG_ELF}
                    COMMAND ${CMAKE_OBJCOPY} -O ihex ${ARG_ELF} ${REMOVE_SECTIONS} ${ARG_HEX}
                    COMMENT "Creating Hex of ${LOCAL_TARGET}.elf"
                )
                add_custom_target(hex-${LOCAL_TARGET} ALL DEPENDS ${ARG_HEX})
                message(STATUS "Adding hex-${LOCAL_TARGET}")

                # Accumulate debug target information for generate_launch_json.py
                set(TARGET_JSON_OBJ "  {\n    \"name\": \"${LOCAL_TARGET}\",\n    \"device\": \"${BOARD_DEVICE}\",\n    \"executable\": \"${ARG_ELF}\"\n  }")
                append_global(CROSS_DEBUG_TARGETS "${TARGET_JSON_OBJ}")
            else()
                target_compile_definitions(${LOCAL_TARGET}.elf
                    PUBLIC
                        register= # Remove the keyword for compatibility reasons
                        UNITTEST)
                # Native is not really a board, but we need to link against it to get the right settings
                set_module_name(TARGET_BOARD native ${cfg} ${chip})
                target_link_libraries(${LOCAL_TARGET}.elf PUBLIC ${TARGET_BOARD})
            endif()

            print_target_properties(TARGET ${LOCAL_TARGET}.elf)
            append_global(TARGET_FIRMWARES ${LOCAL_TARGET})
        endforeach()
    endforeach()
endfunction()
