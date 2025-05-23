#include "cortex/mcu.hpp"
#include "cortex/thumb.hpp"

namespace cortex {
namespace cache {
namespace instruction {
void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    // invalidate the instruction cache
    // @todo invalidate the Cortex M7 instruction cache
    // enable the instruction cache
    auto ccr = system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 1U;
    system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = system_control_block.configuration_control;
    ccr.parts.enable_instruction_cache = 0U;
    system_control_block.configuration_control = ccr;
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

void disable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 0U;
    system_control_block.configuration_control.whole = ccr.whole;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void enable(void) {
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
    auto ccr = system_control_block.configuration_control;
    ccr.parts.enable_data_cache = 1U;
    system_control_block.configuration_control = ccr;
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}
}    // namespace data
}    // namespace cache
}    // namespace cortex
