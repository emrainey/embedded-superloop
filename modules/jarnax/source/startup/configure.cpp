#include "segger/rtt.hpp"
#include "jarnax/system.hpp"
#include "cortex/vectors.hpp"

namespace jarnax {

void configure(void) {
    rtt::initialize();
    jarnax::print("\r\nEmbedded SuperLoop Booting...\r\n");
    // TODO move to cortex function
    cortex::SystemControlBlock::CpuIDBase cpu_id;
    cpu_id = cortex::system_control_block.cpu_id_base;    // read
    jarnax::print(
        "CPUID: CortexM Revision:%d PartNumber:%d Variant:%d Implementor:%d\r\n",
        cpu_id.parts.revision,
        cpu_id.parts.part_number,
        cpu_id.parts.variant,
        cpu_id.parts.implementer
    );

    jarnax::print("Vector Table @ %p\r\n", static_cast<void const *>(&cortex::vector_table));
    if constexpr (cortex::initialize_system_clocks) {
        jarnax::print("Initializing System Clocks\r\n");
     // each vendors clock tree is a unique and confusing flower, let them deal with it!
        vendor::initialize::clocks();
        jarnax::print("Core Clock Frequency is %lu Hz\r\n", vendor::GetClockFrequency().value());
        jarnax::print("System Clock Frequency is %lu Hz\r\n", vendor::GetSystemClockFrequency().value());
        // Set the clock frequency from the vendor
        cortex::SetClockFrequency(vendor::GetClockFrequency());
        cortex::SetSystemClockFrequency(vendor::GetSystemClockFrequency());
    } else {
        using namespace core::units;
        jarnax::print("Skipping System Clocks Initialization\r\n");
        // Set the clock frequency from the vendor
        cortex::SetClockFrequency(1_MHz);
        cortex::SetSystemClockFrequency(1_MHz);
    }

    // initialize the system tick
    jarnax::print("Initializing Tick @ %lu/sec from %lu\r\n", cortex::GetTickRate().value(), cortex::GetSystemClockFrequency().value());
    cortex::initialize::tick(cortex::GetTickRate(), cortex::GetSystemClockFrequency());
    cortex::initialize::swo(cortex::swo::baudrate, cortex::GetClockFrequency());
    // vendor::initialize::watchdog();
    vendor::initialize::gpio();
    // calls the vendor and board specific driver setup
    vendor::initialize::drivers();
    // once enabled statically configured drivers can start to receive interrupts
    cortex::initialize::nvic();
    // install vendor NVIC settings
    // TODO move to Board initialization as the vendor init doesn't know what the board wants
    vendor::initialize::nvic();
    jarnax::print("Configured\r\n");
}

}    // namespace jarnax
