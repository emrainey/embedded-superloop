message(">>> Defining configuration features")

define_property(TARGET PROPERTY CONFIGURATION INHERITED BRIEF_DOCS "The configuration name")

# Add an empty library to handle no configuration
add_library(configuration-none INTERFACE)
target_include_directories(configuration-none INTERFACE ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(configuration-none INTERFACE strict)
set_target_properties(configuration-none  PROPERTIES
    CONFIGURATION none # The configuration name
)
print_target_properties(TARGET configuration-none)

if(LOCAL_CONFIGURATIONS)
    message(STATUS "LOCAL_CONFIGURATIONS=${LOCAL_CONFIGURATIONS}")
else()
    message(FATAL_ERROR "LOCAL_CONFIGURATIONS not defined, there must be at least one configuration")
endif()

# Create an interface library per configuration
foreach(cfg IN LISTS LOCAL_CONFIGURATIONS)
    set_configuration_name(LOCAL_TARGET ${cfg})
    message("Adding configuration ${LOCAL_TARGET}")
    add_library(${LOCAL_TARGET} INTERFACE)
    target_compile_definitions(${LOCAL_TARGET} INTERFACE CONFIGURATION=${cfg})
    target_include_directories(${LOCAL_TARGET} INTERFACE
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/configurations/${cfg}
    )
    target_link_libraries(${LOCAL_TARGET} INTERFACE strict)
    set_target_properties(${LOCAL_TARGET} PROPERTIES
        CONFIGURATION ${cfg} # The configuration name
    )
    print_target_properties(TARGET ${LOCAL_TARGET})
endforeach()
