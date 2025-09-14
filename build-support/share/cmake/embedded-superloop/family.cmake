message(">>> Defining family functions")

define_property(TARGET PROPERTY FAMILY INHERITED BRIEF_DOCS "The family name of the chips")
define_property(TARGET PROPERTY VENDOR INHERITED BRIEF_DOCS "The vendor of the chip")
define_property(TARGET PROPERTY CORTEX_M INHERITED BRIEF_DOCS "The Cortex-M type of the chips for use with the arch cortex module")
define_property(TARGET PROPERTY ARCHITECTURE INHERITED BRIEF_DOCS "The architecture of the chip for use with compilers")
define_property(TARGET PROPERTY VENDOR_LINKERSCRIPTS INHERITED BRIEF_DOCS "The linkerscripts directory for the vendor")

# Defines a interface library for a family of chips
# @param FAMILY The family name of the chips
# @param VENDOR The vendor of the chips (one of the modules in the build)
# @param CORTEX_M The Cortex-M type of the chips in this family
# @param ARCHITECTURE The architecture of the chips in this family
function(add_family)
    set(options "")
    set(singles FAMILY VENDOR CORTEX_M ARCHITECTURE)
    set(multiples DEFINES INCLUDES)
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    required(ARG_FAMILY ARG_VENDOR ARG_CORTEX_M ARG_ARCHITECTURE)

    if (NOT CORTEX_M STREQUAL ARG_CORTEX_M)
        message(STATUS "Skipping chip ${ARG_CHIP} because it is for Cortex-M${ARG_CORTEX_M} but toolchain is for Cortex-M${CORTEX_M}")
        return()
    endif()

    set_family_name(LOCAL_TARGET ${ARG_FAMILY})
    message("Adding ${LOCAL_TARGET}")
    add_library(${LOCAL_TARGET} INTERFACE)
    target_compile_definitions(${LOCAL_TARGET} INTERFACE ${ARG_DEFINES} FAMILY=${ARG_FAMILY} CORTEX_M=${ARG_CORTEX_M})
    target_include_directories(${LOCAL_TARGET} INTERFACE ${ARG_INCLUDES} ${CMAKE_SOURCE_DIR}/modules/${ARG_VENDOR}/include)
    set_target_properties(${LOCAL_TARGET} PROPERTIES
        # TRANSITIVE_COMPILE_PROPERTIES "VENDOR;CORTEX_M;ARCHITECTURE"
        # TRANSITIVE_LINK_PROPERTIES "FAMILY;VENDOR;CORTEX_M;ARCHITECTURE;VENDOR_LINKERSCRIPT;VENDOR_LINKERSCRIPTS"
        # COMPATIBLE_INTERFACE_STRING "FAMILY;VENDOR;CORTEX_M;ARCHITECTURE"
        FAMILY ${ARG_FAMILY} # The family name of the chips
        VENDOR ${ARG_VENDOR} # The vendor of the chip
        CORTEX_M ${ARG_CORTEX_M} # The Cortex-M type of the chip for use with the arch cortex module
        ARCHITECTURE ${ARG_ARCHITECTURE} # The architecture of the chip for use with compilers
        VENDOR_LINKERSCRIPTS ${CMAKE_SOURCE_DIR}/modules/${ARG_VENDOR}/linkerscripts
        VENDOR_LINKERSCRIPT ${CMAKE_SOURCE_DIR}/modules/${ARG_VENDOR}/linkerscripts/gcc.ld
     )

    print_target_properties(TARGET ${LOCAL_TARGET})

endfunction()

add_family(FAMILY cortex
    VENDOR cortex
    CORTEX_M ${CORTEX_M}
    ARCHITECTURE ${ARCHITECTURE}
)