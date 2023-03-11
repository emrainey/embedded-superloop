#include "configure.hpp"
#include "jarnax/system.hpp"
#include "jarnax/linker.hpp"
#include "memory.hpp"

namespace jarnax {

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
    // thumb::initialize();    // clear all register of previous state
    // reinstall the vector table in case it changed
    cortex::system_control_block.vector_table = &vector_table;

    // IF the device had ITCM, or DTCM enable here.
    // IF device had ECC memory, now would the time to initialize it.
    // of course we could just zero initialize it all w/o ECC
    {
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__ccm_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__ccm_beg);
        while (beg < end) {
            *beg++ = 0;
        }
    }
    {
        uint32_t volatile const *end = reinterpret_cast<uint32_t volatile const *>(__sram_end);
        uint32_t volatile *beg = reinterpret_cast<uint32_t volatile *>(__sram_beg);
        while (beg < end) {
            *beg++ = 0;
        }
    }

    // == STACK IS NOW VALID ============

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
}    // namespace jarnax
