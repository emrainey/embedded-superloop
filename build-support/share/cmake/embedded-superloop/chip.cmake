message(">>> Defining chip functions")

define_property(TARGET PROPERTY CHIP INHERITED BRIEF_DOCS "The name of the chip (for targets)")
define_property(TARGET PROPERTY DEVICE INHERITED BRIEF_DOCS "The exact device name of the chip for tools like JLink, OpenOCD")
define_property(TARGET PROPERTY PACKAGE INHERITED BRIEF_DOCS "The package type of the chip for tools like CubeMX")

# A Chip is a specific microcontroller from a vendor
# @param CHIP the name of the chip (for targets)
# @param DEVICE the exact device name of the chip for tools like JLink, OpenOCD
# @param FAMILY the family of the chip. When making dependencies on the chip this can be used to select a family of chips.
# @param PACKAGE the package type of the chip for tools like CubeMX
# @param HEADER the main header file to include for this chip (defaults to ${VENDOR}/${DEVICE}.hpp)
# @param DEFINES any preprocessor defines to set for this chip
function(add_chip)
    set(options "")
    set(singles NAME DEVICE PACKAGE FAMILY)
    set(multiples DEFINES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})
    required(ARG_NAME ARG_DEVICE ARG_PACKAGE ARG_FAMILY)

    # Create a target INTERFACE for the chip which pulls in the vendor defines and paths
    set_chip_name(LOCAL_TARGET ${ARG_NAME})
    # Create the family name and make sure it exists
    set_family_name(TARGET_FAMILY ${ARG_FAMILY})
    if (NOT TARGET ${TARGET_FAMILY})
        message("XXX Skipping chip ${ARG_NAME} as ${TARGET_FAMILY} not found")
        return()
    endif()
    add_library(${LOCAL_TARGET} INTERFACE)
    message("Adding ${LOCAL_TARGET} for ${ARG_DEVICE} within ${TARGET_FAMILY}")
    if (NOT ARG_NAME STREQUAL "all")
        target_compile_definitions(${LOCAL_TARGET} INTERFACE ${ARG_DEFINES} CHIP=${ARG_NAME} ${ARG_DEVICE}=1 ${ARG_DEVICE}${ARG_PACKAGE}=1)
        target_link_libraries(${LOCAL_TARGET} INTERFACE ${TARGET_FAMILY})
        message(STATUS "Linking ${LOCAL_TARGET} to ${TARGET_FAMILY}")
    endif()
    set_target_properties(${LOCAL_TARGET} PROPERTIES
        # TRANSITIVE_COMPILE_PROPERTIES "CHIP;DEVICE;PACKAGE"
        # TRANSITIVE_LINK_PROPERTIES "CHIP;DEVICE;PACKAGE"
        # COMPATIBLE_INTERFACE_STRING "CHIP;DEVICE;PACKAGE"
        CHIP ${ARG_NAME} # The name of the chip (for targets)
        DEVICE ${ARG_DEVICE} # The exact device name of the chip for tools like JLink, OpenOCD
        PACKAGE ${ARG_PACKAGE} # The package type of the chip for tools like CubeMX
    )
    # print_target_properties(TARGET ${LOCAL_TARGET})
    inherit_target_properties(CHILD ${LOCAL_TARGET} PARENT ${TARGET_FAMILY} PROPERTIES
        FAMILY VENDOR CORTEX_M ARCHITECTURE VENDOR_LINKERSCRIPT VENDOR_LINKERSCRIPTS
    )

    print_target_properties(TARGET ${LOCAL_TARGET})
    append_global(TARGET_CHIPS ${ARG_NAME})
endfunction()
