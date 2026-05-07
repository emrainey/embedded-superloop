
# define hookpost-connect
#     monitor swo EnableTarget 0 0 0xFFFFFFFF 0
#     monitor swo start 480000000 64000
# end

define reset
    target remote localhost:2331
    # Reset configuration
    monitor reset halt
    monitor flash probe 0
    load @LOCAL_TARGET_BINARY_PATH@
    monitor rtt server stop 2333
    monitor rtt setup 0x24000000 0x80000 "SEGGER RTT"
    monitor rtt start
    monitor rtt server start 2333 0
end

define setup
    file @LOCAL_TARGET_BINARY_PATH@
    break cortex::initialize::on_startup
    break vendor::initialize::clocks
    break cortex::system::main
    layout split
    set print asm-demangle on
    set print frame-arguments all
    # Users may have their own breakpoints, so we want to load those after the reset sequence
    source -s -v testing/breakpoints.gdb
end

