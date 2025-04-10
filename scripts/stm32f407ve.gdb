target remote localhost:2331
file build/cortex-gcc-arm-none-eabi-13/applications/simple/spi-demo-stm32-basic-stm32_f4ve_v2.elf
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