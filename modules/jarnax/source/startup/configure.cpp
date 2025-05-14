#include "segger/rtt.hpp"
#include "jarnax/system.hpp"
#include "cortex/vectors.hpp"

namespace jarnax {

void configure(void) {
    rtt::initialize();
    jarnax::print("\r\nEmbedded SuperLoop Booting...\r\n");

    cortex::SystemControlBlock::CpuIDBase cpu_id;
    cpu_id = cortex::system_control_block.cpu_id_base;    // read
    jarnax::print(
        "CPUID: CortexM Revision:%u PartNumber:%u Variant:%u Implementor:%u\r\n",
        cpu_id.parts.revision,
        cpu_id.parts.part_number,
        cpu_id.parts.variant,
        cpu_id.parts.implementer
    );

    jarnax::print("Vector Table @ %p\r\n", static_cast<void const *>(&cortex::vector_table));
    // each vendors clock tree is a unique and confusing flower, let them deal with it!
    vendor::initialize::clocks();
    jarnax::print("Core Clock Frequency is %lu Hz\r\n", vendor::GetClockFrequency().value());
    jarnax::print("System Clock Frequency is %lu Hz\r\n", vendor::GetSystemClockFrequency().value());
    // Set the clock frequency from the vendor
    cortex::SetClockFrequency(vendor::GetClockFrequency());
    cortex::SetSystemClockFrequency(vendor::GetSystemClockFrequency());
    // initialize the system tick
    jarnax::print("Initializing Tick @ %lu/sec from %lu\r\n", cortex::ticks_per_second.value(), cortex::GetSystemClockFrequency().value());
    cortex::initialize::tick(cortex::ticks_per_second, cortex::GetSystemClockFrequency());
    cortex::initialize::swo(cortex::swo::baudrate, cortex::GetClockFrequency());
    // vendor::initialize::watchdog();
    vendor::initialize::gpio();
    vendor::initialize::drivers();
    // once enabled statically configured drivers can start to receive interrupts
    cortex::initialize::nvic();
    vendor::initialize::nvic();    // install vendor NVIC settings
    jarnax::print("Configured\r\n");
}

}    // namespace jarnax
