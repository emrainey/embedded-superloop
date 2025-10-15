message(">>> Defining configuration features")

define_property(TARGET PROPERTY CONFIGURATION INHERITED BRIEF_DOCS "The configuration name")

function(add_configuration)
    set(options "")
    set(singles NAME)
    set(multiples "")
    cmake_parse_arguments(
        ARG
        "${options}"
        "${singles}"
        "${multiples}"
        ${ARGN})

    required(ARG_NAME)

    set_configuration_name(LOCAL_TARGET ${ARG_NAME})
    message("Adding configuration ${LOCAL_TARGET}")
    add_library(${LOCAL_TARGET} INTERFACE)
    target_link_libraries(${LOCAL_TARGET} INTERFACE strict)
    target_include_directories(${LOCAL_TARGET} INTERFACE
        ${CMAKE_SOURCE_DIR}/include
    )
    set_target_properties(${LOCAL_TARGET} PROPERTIES
        CONFIGURATION ${ARG_NAME} # The configuration name
    )
    if (EXISTS ${CMAKE_SOURCE_DIR}/configurations/${ARG_NAME})
        target_compile_definitions(${LOCAL_TARGET} INTERFACE CONFIGURATION=${ARG_NAME})
        target_include_directories(${LOCAL_TARGET} INTERFACE
            ${CMAKE_SOURCE_DIR}/configurations/${ARG_NAME}
        )
        append_global(TARGET_CONFIGURATIONS ${ARG_NAME}) # None should not be added to this
    endif()
    print_target_properties(TARGET ${LOCAL_TARGET})
endfunction()

# the None configuration is a special INTERFACE target which is used
# so that modules can be built without a configuration.
add_configuration(NAME none)