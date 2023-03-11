#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {

/// The local copy of the Frame Data which is copied from the stack upon exception.
ATTRIBUTE((section(".privileged_data"))) cortex::exceptions::ExtendedFrame exception_frame;
ATTRIBUTE((section(".privileged_data"))) bool is_basic_frame;

namespace handlers {

/// Determined if an address value is aligned to a specific types alignment requirement
template <typename TYPE>
constexpr bool is_address_aligned(uintptr_t address) {
    size_t alignment_mask = alignof(TYPE) - 1U;
    return ((address & alignment_mask) == 0U);
}
static_assert(is_address_aligned<std::uint8_t>(0x3U), "Must be true");
static_assert(is_address_aligned<std::uint16_t>(0x2U), "Must be true");
static_assert(is_address_aligned<std::uint32_t>(0x4U), "Must be true");
static_assert(is_address_aligned<std::uint32_t>(0x8U), "Must be true");    // NOLINT

/// A local function which can return the stack frame of the exception
/// The Extended Frame format is always used as a type, but the basic frame
/// may be the only part filled in.
inline void get_exception_frame(void) {
    cortex::Control control = thumb::get_control();
    bool force_alignment = false;

    // Find out the size of the stack frame
    size_t size = 0U;
    if (control.parts.float_active) {
        size = sizeof(cortex::exceptions::ExtendedFrame);
        force_alignment = true;
    } else {
        cortex::SystemControlBlock::ConfigurationControl ctrl;
        ctrl = cortex::system_control_block.configuration_control;
        size = sizeof(cortex::exceptions::BasicFrame);
        force_alignment = (ctrl.parts.stack_pointer_is_guaranteed_8_byte_aligned == 1U);
    }

    // obtain the address from the registers
    uintptr_t addr = 0U;
    if (control.parts.stack == cortex::modes::Stack::Process and
        control.parts.privilege == cortex::modes::Privileged::High) {
        addr = thumb::get_process_stack_address();
    } else {    // if (control.parts.stack == cortex::modes::Stack::Main) {
        addr = thumb::get_main_stack_address();
    }

    // adjust the address to account for alignment issues if they are not aligned
    if ((not is_address_aligned<std::uint64_t>(addr)) or force_alignment) {
        uintptr_t mask = ~(sizeof(std::uint64_t) - 1U);
        addr = (addr - size) & mask;
    } else {
        addr = (addr - size);
    }

    // copy into the local singleton
    memory::copy(&exception_frame, reinterpret_cast<void *>(addr), size);
}    // namespace handlers

}    // namespace handlers
}    // namespace jarnax
