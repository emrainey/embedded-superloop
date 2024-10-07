set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

# Set the C and CXX compilers in the command line
# find_program(CMAKE_C_COMPILER NAME gcc REQUIRED)
# find_program(CMAKE_CXX_COMPILER NAME g++ REQUIRED)

set(CMAKE_CROSS_BUILD FALSE)

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions -fno-rtti)

message(NOTICE "Turn off poor features")
add_compile_options(-Wno-deprecated-register)

message(NOTICE "Enable Unit Test Features")
add_compile_definitions(UNITTEST=1)

message(NOTICE "Enable coverage all the time")
add_compile_options(-Wno-unknown-pragmas -fprofile-arcs -ftest-coverage)
link_libraries(--coverage)

# no default math lib is needed?
unset(COMPILER_MATH_LIBS)