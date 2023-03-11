set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_PROCESSOR x86_64)

set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)

set(CMAKE_C_STANDARD 17)
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CROSS_BUILD FALSE)

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions -fno-rtti)

message(NOTICE "Turn off poor features")
add_compile_options(-Wno-deprecated-register)

message(NOTICE "Enable Unit Test Features")
add_compile_definitions(UNITTEST=1)

add_compile_options(-Wno-unknown-pragmas)

# no default math lib is needed?
set(COMPILER_MATH_LIB "")