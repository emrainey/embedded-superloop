set(CMAKE_SYSTEM_NAME ${CMAKE_HOST_SYSTEM_NAME})
set(CMAKE_SYSTEM_PROCESSOR ${CMAKE_HOST_SYSTEM_PROCESSOR})

find_program(CMAKE_C_COMPILER NAMES clang REQUIRED)
find_program(CMAKE_CXX_COMPILER NAMES clang++ REQUIRED)
find_program(CMAKE_OBJDUMP NAMES llvm-objdump REQUIRED)

set(CMAKE_TRY_COMPILE_TARGET_TYPE STATIC_LIBRARY)
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM NEVER)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_PACKAGE ONLY)

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

# Add debug flags
add_compile_options(
    -glldb
)