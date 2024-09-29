cmake_minimum_required(VERSION 3.22)

project(jarnax-bare-metal-apps
        VERSION 0.1.49
        LANGUAGES CXX ASM)

find_package(jarnax REQUIRED)

# Add all the local applications (modules will be added by the jarnax)
list(APPEND LOCAL_APPLICATIONS unittests)
foreach(app IN LISTS LOCAL_APPLICATIONS)
    add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/applications/${app})
endforeach()
