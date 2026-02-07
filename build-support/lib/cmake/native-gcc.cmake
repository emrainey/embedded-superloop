set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

message(STATUS "PATH=$ENV{PATH}")

find_program(CMAKE_C_COMPILER REQUIRED
    NAMES gcc-13 gcc-14 gcc-15 gcc
    PATHS /opt/homebrew/bin
          /usr/bin/
)
find_program(CMAKE_CXX_COMPILER REQUIRED
    NAMES g++-13 g++-14 g++-15 g++
    PATHS /opt/homebrew/bin
          /usr/bin/
)
find_program(CMAKE_AR REQUIRED
    NAMES ar-13 ar-14 ar-15 ar
    PATHS /opt/homebrew/bin
          /usr/bin/
)
find_program(CMAKE_NM REQUIRED
    NAMES nm-13 nm-14 nm-15 nm
    PATHS /opt/homebrew/bin
          /usr/bin/
)

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions -fno-rtti)

message(NOTICE "Turn off poor features")
# add_compile_options(-Wno-deprecated-register)
# add_compile_options(-Wno-free-nonheap-object)

message(NOTICE "Enable Unit Test Features")
add_compile_definitions(UNITTEST=1)

message(NOTICE "Enable coverage all the time")
add_compile_options(-Wno-unknown-pragmas -fprofile-arcs -ftest-coverage)
link_libraries(--coverage)

# no default math lib is needed?
unset(COMPILER_MATH_LIBS)