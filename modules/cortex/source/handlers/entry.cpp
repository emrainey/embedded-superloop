#include "configure.hpp"
#include "jarnax/system.hpp"
#include "cortex/thumb.hpp"
#include "memory.hpp"

namespace cortex {

namespace handlers {

// The compiler will likely try to replace this with calls to memset or memcpy!
#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC push_options
#pragma GCC optimize("O0")    // Disable all optimizations
#endif
[[noreturn]] void entry(void) {
    // =============================================================
    // State: Thread Mode (not in a Handler oddly), Privileged, Main Stack
    // Machine has set SP and the VTOR is wherever it came from (Flash probably)
    // There's no .bss or .data or consts, only immediate values and
    // values inlined in assembly. TREAD WITH CAUTION!
    // =============================================================
    thumb::interrupts::disable();
    // clear all register of previous state (processor does this but we do it for completeness)
    thumb::initialize();
    // disable all pending interrupt sources and clear all pending exceptions
    cortex::system_control_block.system_handler_control_state.whole = 0U;
    cortex::system_control_block.bus_fault_address.address = 0U;
    cortex::system_control_block.memory_management_fault_address.address = 0U;
    cortex::system_control_block.configuration_fault_status.whole = 0xFF'FF'FF'FFU;
    cortex::system_control_block.hard_fault_status.whole = 0xFF'FF'FF'FFU;
    // reinstall the vector table to the read-only version in FLASH
    cortex::system_control_block.vector_table = &cortex::vector_table;

    // IF the device had ITCM, or DTCM enable here.
    if constexpr (zero_itcm_at_boot and ::vendor::configuration::has_itcm) {
        // TODO enable here
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__itcm_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__itcm_beg);
        while (beg < end) {
            *beg++ = 0;
        }
    }
    if constexpr (zero_dtcm_at_boot and ::vendor::configuration::has_dtcm) {
        // TODO enable here
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__dtcm_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__dtcm_beg);
        while (beg < end) {
            *beg++ = 0;
        }
    }

    // IF device had ECC memory, now would the time to initialize it.

    // of course we could just zero initialize it all w/o ECC
    // IF the device has CCM clear it here
    if constexpr (zero_ccm_at_boot and ::vendor::configuration::has_ccm) {
        cortex::system_control_block.configuration_control.parts.enable_data_cache = 1U;
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__ccm_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__ccm_beg);
        while (beg < end) {
            *beg++ = 0;
        }
        if constexpr (verify_ccm_at_boot) {
            beg = reinterpret_cast<uint32_t volatile *>(__ccm_beg);
            while (beg < end) {
                if (*beg != 0) {
                    cortex::spinhalt();
                }
                beg++;
            }
        }
    }
    if constexpr (zero_sram_at_boot and ::vendor::configuration::has_sram) {
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__sram_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__sram_beg);
        while (beg < end) {
            *beg = 0;
            if (*beg != 0) {
                cortex::spinhalt();
            }
            beg++;
        }
        if constexpr (verify_ccm_at_boot) {
            beg = reinterpret_cast<uint32_t volatile *>(__sram_beg);
            while (beg < end) {
                if (*beg != 0) {
                    cortex::spinhalt();
                }
                beg++;
            }
        }
    }

    // == STACK IS NOW VALID ============
    thumb::jump(__main_stack_top, cortex::handlers::entry_after_stack);
}

[[noreturn]] void entry_after_stack(void) {
    // read the configuration control
    auto configuration_control = cortex::system_control_block.configuration_control;
    // disable the data cache
    configuration_control.parts.enable_data_cache = 0U;
    // write back the value
    cortex::system_control_block.configuration_control = configuration_control;
    // =============================================
    jarnax::initialize::watermark_stack();
    // Now the stack has been initialized and watermarked
    jarnax::initialize::zero_bss();
    // Now there's uninitialized global variables
    jarnax::initialize::load_data();
    // Now there's initialized global variables like readonly values (const)
    cortex::initialize::simple_globals();
    // Now the cortex global variables (register pointers and such) are available
    jarnax::initialize::simple_globals();
    // Now the core system global variables (but not objects yet) are available
    jarnax::initialize::static_constructors();
    // Now the complex cortex globals can be initialized
    cortex::initialize::class_globals();
    // Now the complex system globals can be initialized
    jarnax::initialize::class_globals();
    // Now The C++ objects have been initialized
    // =============================================
    // Jump to on_entry and forget this function!
    thumb::jump(__main_stack_top, jarnax::initialize::on_entry);
}
#if defined(__GNUC__) and not defined(__clang__)
#pragma GCC pop_options    // restore to what it was
#endif
}    // namespace handlers
}    // namespace cortex
