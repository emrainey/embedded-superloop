#include <cstddef>
#include <cstdint>

#include "cortex/partnumber.hpp"
#include "cortex/peripherals/SystemControlBlock.hpp"
#include "cortex/processor.hpp"

namespace cortex {
namespace processor {

PartNumber GetPartNumber() {
    cortex::peripherals::SystemControlBlock::CpuIDBase cpu_id;
    cpu_id = cortex::peripherals::system_control_block.cpu_id_base;    // read whole register
    return static_cast<cortex::PartNumber>(cpu_id.parts.part_number & 0xFFFU);
}

Revision GetRevision() {
    cortex::peripherals::SystemControlBlock::CpuIDBase cpu_id;
    cpu_id = cortex::peripherals::system_control_block.cpu_id_base;                                                        // read whole register
    return Revision{static_cast<std::uint8_t>(cpu_id.parts.revision), static_cast<std::uint8_t>(cpu_id.parts.variant)};    // Create Revision
}

}    // namespace processor
}    // namespace cortex
