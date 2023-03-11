target remote localhost:2331
file build/jarnax.elf
load
layout asm
set print asm-demangle

# break jarnax::initialize
# break jarnax::initialize::static_constructors
# break cortex::initialize::swo
# break jarnax::configure
# break cortex::initialize::mpu
# break TickTest::Test
break jarnax::main
# break jarnax::GetTicker
break StackTest::Test

monitor swo EnableTarget 0 0 0xFFFFFFFF 0
monitor swo start 168000000 64000
monitor reset