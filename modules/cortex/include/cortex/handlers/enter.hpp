#ifndef CORTEX_HANDLERS_ENTER_HPP_
#define CORTEX_HANDLERS_ENTER_HPP_

/// @file
/// The System Interface

#include <cstdint>
#include <cstddef>

#include "configure.hpp"
#include "compiler.hpp"
#include "cortex/vectors.hpp"

/// The namespace of the system level functions
namespace cortex {
namespace handlers {

/// @brief The wrapping function which is called some handlers.
/// @param extended_handler The function to call to handle the exception
ALWAYS_INLINE inline void enter(cortex::exceptions::ExtendedHandler extended_handler) {
#if defined(UNITTEST)
    cortex::exceptions::ExceptionReturn exc_return = cortex::exceptions::ExceptionReturn::Extract();
    cortex::exceptions::ExtendedFrame *frame;
    if (exc_return.parts.stack == cortex::modes::Stack::Main) {
        frame = reinterpret_cast<cortex::exceptions::ExtendedFrame *>(thumb::get_main_stack_pointer());
    } else {
        frame = reinterpret_cast<cortex::exceptions::ExtendedFrame *>(thumb::get_process_stack_pointer());
    }
    thumb::save_callee_registers();
    extended_handler(frame, exc_return);
    thumb::restore_callee_registers();
    exc_return.return_from_exception();    // [[noreturn]]
#elif defined(__arm__)
    // volatile == do not optimize the assembly
    asm volatile(
        "tst lr, #4 \r\n"
        "ite eq \r\n"
        "mrseq r0, msp \r\n"
        "mrsne r0, psp \r\n"
        "push {r4-r11, lr} \r\n"
        // setup r0, r1
        "mov r1, lr \r\n"
        "bl %[handler] \r\n"
        "pop {r4-r11, pc} \r\n"
        :                                    // outputs
        : [handler] "i"(extended_handler)    // inputs
        : "r0", "r1", "cc", "memory"         // clobbers
        // :    // clobbers
    );
#endif
}

}    // namespace handlers
}    // namespace cortex

#endif    // CORTEX_HANDLERS_ENTER_HPP_