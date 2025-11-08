#include "cortex/mcu.hpp"

namespace cortex {
namespace cache {
namespace instruction {
void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // invalidate the instruction cache
    // @todo invalidate the Cortex M7 instruction cache
    // enable the instruction cache
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 1U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 0U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(void) {
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way invalidation for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(std::uintptr_t address, std::size_t size) {
    static_cast<void>(address);
    static_cast<void>(size);
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way invalidation for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

}    // namespace instruction

namespace data {
void invalidate(void) {
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way invalidation for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void invalidate(std::uintptr_t address, std::size_t size) {
    static_cast<void>(address);
    static_cast<void>(size);
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way invalidation for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void clean(void) {
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way clean for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void clean(std::uintptr_t address, std::size_t size) {
    static_cast<void>(address);
    static_cast<void>(size);
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way clean for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void flush(void) {
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way clean and invalidate for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void flush(std::uintptr_t address, std::size_t size) {
    static_cast<void>(address);
    static_cast<void>(size);
    thumb::data_synchronization_barrier();
    /// @todo Add per set/way clean and invalidate for Cortex M7
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 0U;
    peripherals::system_control_block.configuration_control.whole = ccr.whole;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = peripherals::system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 1U;
    peripherals::system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}
}    // namespace data
}    // namespace cache
}    // namespace cortex
