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

/// @brief The wrapping function which is called by each handler
/// @param isr_number
ALWAYS_INLINE inline void enter(cortex::exceptions::InterruptServiceRoutine isr_number) {
#if defined(UNITTEST)
    cortex::exceptions::ExceptionReturn exc_return = cortex::exceptions::ExceptionReturn::Extract();
    cortex::exceptions::ExtendedFrame *frame;
    if (exc_return.parts.stack == cortex::modes::Stack::Main) {
        frame = reinterpret_cast<cortex::exceptions::ExtendedFrame *>(thumb::get_main_stack_pointer());
    } else {
        frame = reinterpret_cast<cortex::exceptions::ExtendedFrame *>(thumb::get_process_stack_pointer());
    }
    thumb::save_callee_registers();
    generic(isr_number, frame, exc_return);
    thumb::restore_callee_registers();
    exc_return.return_from_exception();    // [[noreturn]]
#elif defined(__arm__)
    asm volatile(
        "tst lr, #4 \r\n"
        "ite eq \r\n"
        "mrseq r1, msp \r\n"
        "mrsne r1, psp \r\n"
        "push {r4-r11, lr} \r\n"
        // setup r0, r1, r2
        "mov r0, %0 \r\n"
        "mov r2, lr \r\n"
        "bl %[handler] \r\n"
        "pop {r4-r11, pc} \r\n"
        :                                                              // outputs
        : "r"(isr_number), [handler] "i"(cortex::handlers::generic)    // inputs
        :                                                              // clobbers
    );
#endif
}

}    // namespace handlers
}    // namespace cortex

#endif    // CORTEX_HANDLERS_ENTER_HPP_