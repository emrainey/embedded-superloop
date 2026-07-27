message(STATUS "Configuring bare-metal build")

message(NOTICE "No Exceptions and No RTTI")
add_compile_options(-fno-exceptions)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-rtti")

message(STATUS "Additional Flags for Stack, Statics, Linkage")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-threadsafe-statics -fno-use-cxa-atexit")
add_compile_options(
    # -ffreestanding
    -ffunction-sections
    -fdata-sections
    # -flto
    -fomit-frame-pointer
    -fstack-usage
    -Wstack-usage=32768
    $<$<CONFIG:Debug>:-fno-inline>
    # -fdiagnostics-all-candidates
    $<$<CONFIG:Debug>:-g3>
    $<$<CONFIG:Debug>:-ggdb3>
    $<$<CONFIG:Debug>:-O0>
    $<$<CONFIG:Debug>:-ftemplate-backtrace-limit=0>
)

message(STATUS "Enable reproducible build flags")
add_compile_options(
    -fdebug-prefix-map=./=
    -ffile-prefix-map=./=
    -fno-stack-protector
    -fno-unwind-tables
    -fno-asynchronous-unwind-tables
    -fno-ident
)
add_link_options(
    LINKER:--build-id=none
    LINKER:--enable-new-dtags
    LINKER:--sort-section=name
    LINKER:--no-undefined
    # LINKER:--as-needed
    LINKER:--hash-style=gnu
    #LINKER:-z,relro
    LINKER:-z,now
)

list(APPEND COMPILER_MATH_LIBS gcc m)
