#ifndef THUMB_HPP_
#define THUMB_HPP_

/// @file
/// Thumb Inline Assembly Header
/// @see https://gcc.gnu.org/onlinedocs/gcc/Extended-Asm.html
/// @see https://www.ibiblio.org/gferg/ldp/GCC-Inline-Assembly-HOWTO.html
/// @see https://github.com/ARM-software/CMSIS_5/blob/develop/CMSIS/Core/Include
/// @see https://gcc.gnu.org/onlinedocs/gcc/Other-Builtins.html

#include "cortex/core.hpp"

/// @brief The THUMB Inline Assembly Namespace
namespace thumb {

/// Disables Interrupts
ALWAYS_INLINE inline void initialize(void) {
#if defined(__arm__)
    asm volatile(
        "mov r0, #0 \r\n"
        "mov r1, #0 \r\n"
        "mov r2, #0 \r\n"
        "mov r3, #0 \r\n"
        "mov r4, #0 \r\n"
        "mov r5, #0 \r\n"
        "mov r6, #0 \r\n"
        "mov r7, #0 \r\n"
        "mov r8, #0 \r\n"
        "mov r9, #0 \r\n"
        "mov r10, #0 \r\n"
        "mov r11, #0 \r\n"
        "mov r12, #0 \r\n"
        "mov lr, #0xFFFFFFFF \r\n"
        :                                                                                          // outputs
        :                                                                                          // inputs
        : "r0", "r1", "r2", "r3", "r4", "r5", "r6", "r7", "r8", "r9", "r10", "r11", "r12", "lr"    // clobbers
    );
#endif
}

/// @brief A subgroup dealing with the interrupt related instructions
namespace interrupts {

/// Disables Interrupts
ALWAYS_INLINE inline void disable(void) {
#if defined(__arm__)
    asm volatile("cpsid if" :::);
#endif
}

/// Enables Interrupts
ALWAYS_INLINE inline void enable(void) {
#if defined(__arm__)
    asm volatile("cpsie if" :::);
#endif
}
}    // namespace interrupts

/// Causes a breakpoint
/// @tparam IMM The immediate value
template <std::uint8_t IMM>
ALWAYS_INLINE inline void breakpoint(void) {
#if defined(__arm__)
    asm volatile("bkpt %0" : : "n"(IMM) :);
#endif
}

/// Injects an instruction barrier
ALWAYS_INLINE inline void instruction_barrier(void) {
#if defined(__arm__)
    asm volatile("isb sy" :::);
#endif
}

/// Injects a data memory barrier
ALWAYS_INLINE inline void data_memory_barrier(void) {
#if defined(__arm__)
    asm volatile("dmb" :::);
#endif
}

/// Injects a data synchronization barrier
ALWAYS_INLINE inline void data_synchronization_barrier(void) {
#if defined(__arm__)
    asm volatile("dsb" :::);
#endif
}

/// Injects a Wait for Event Mode
ALWAYS_INLINE inline void wait_for_event_mode(void) {
#if defined(__arm__)
    asm volatile("wfe" :::);
#endif
}

/// The No-Operation instruction
ALWAYS_INLINE inline void nop(void) {
#if defined(__arm__)
    asm volatile("nop" :::);
#endif
}

/// @brief A set of 4 word sized parameters used in exceptions which typically contains exception related information.
struct Stacked {
    cortex::word parameters[4];
};

/// Invokes a Supervisor Call
/// @tparam IMM The immediate value
template <std::int8_t IMM>
ALWAYS_INLINE inline std::uint32_t supervisor(Stacked* stacked) {
    static_assert(IMM >= 0, "Must be a value between 0 and 127");
    std::uint32_t ret = 0;
    data_synchronization_barrier();
#if defined(__arm__)
    // moving into themselves is partially redundant however it prevents dropping the parameters
    asm volatile(
        "ldm %1, {r0-r3} \r\n"
        "svc %2 \r\n"
        "mov %0, r0 \r\n"
        : "=r"(ret)                           // outputs
        : "r"(stacked), "i"(IMM)              // inputs
        : "r0", "r1", "r2", "r3", "memory"    // clobbers (don't let r0 be noted as clobbered)
    );
#else
    // call the SVC
    (void)stacked;
    // FIXME call the supervisor handler
#endif
    return ret;
}

/// Jumps to a function without capturing the return address, and reseting the stack
/// @param stack The (top of the) stack to use.
/// @param func The function to jump to.
[[noreturn]] inline void jump(void* stack, void (*func)(void)) {
#if defined(__arm__)
    asm volatile(
        "mov sp, %0 \r\n"
        "bx %1 \r\n"
        :                          // outputs
        : "r"(stack), "r"(func)    // inputs
        : "cc"                     // clobbers
    );
    __builtin_unreachable();
#else
    (void)stack;
    func();
    do {
    } while (1);
#endif
}

/// Configures the MSP and PSP stacks
ALWAYS_INLINE inline void stacks(void* main_stack, void* process_stack) {
#if defined(__arm__)
    asm volatile(
        "msr msp, %0 \r\n"
        "msr psp, %1 \r\n"
        :                                        // outputs
        : "r"(main_stack), "r"(process_stack)    // inputs
        : "cc", "memory"                         // clobbers
    );
#else
    (void)main_stack;
    (void)process_stack;
#endif
}

/// Obtains the Control Register through the Thumb instruction
ALWAYS_INLINE inline cortex::word get_control() {
    cortex::word value{0u};
#if defined(__arm__)
    asm volatile("mrs %0, control    \r\n"
                 : "=r"(value)       // outputs
                 :                   // inputs
                 : "cc", "memory"    // clobbers
    );
#endif
    return value;
}

/// Sets the Control Register through the Thumb instruction
/// @warning This is a privileged instruction that will result in a fault if not in privileged mode
ALWAYS_INLINE inline void set_control(cortex::word value) {
#if defined(__arm__)
    asm volatile("msr control, %0    \r\n"
                 :                   // outputs
                 : "r"(value)        // inputs
                 : "cc", "memory"    // clobbers
    );
#else
    (void)value;
#endif
}

/// Obtains the link return from the registers
inline uintptr_t get_link_return(void) {
    uintptr_t link_return = 0U;
#if defined(__arm__)
    asm volatile("mov %0, lr\r\n"
                 : "=r"(link_return)    // outputs
                 :                      // inputs
                 : "cc", "memory"       // clobbers
    );
#endif
    return link_return;
}

/// Obtains the current stack pointer and returns it
inline std::uint32_t* get_current_stack_pointer(void) {
    std::uint32_t* sp = nullptr;
#if defined(__arm__)
    asm volatile("mov %0, sp\r\n"
                 : "=r"(sp)          // outputs
                 :                   // inputs
                 : "cc", "memory"    // clobbers
    );
#endif
    return sp;
}

/// Obtains the stack address from the registers
inline uintptr_t get_current_stack_address(void) {
    uintptr_t stack_address = 0U;
#if defined(__arm__)
    asm volatile("mov %0, sp\r\n"
                 : "=r"(stack_address)    // outputs
                 :                        // inputs
                 : "cc", "memory"         // clobbers
    );
#endif
    return stack_address;
}

/// Obtains the main stack address from the registers
inline uintptr_t get_main_stack_address(void) {
    uintptr_t stack_address = 0U;
#if defined(__arm__)
    asm volatile("mrs %0, msp \r\n"
                 : "=r"(stack_address)    // outputs
                 :                        // inputs
                 : "cc", "memory"         // clobbers
    );
#endif
    return stack_address;
}

/// Obtains the main stack address from the registers
inline void* get_main_stack_pointer(void) {
    void* stack_address = 0U;
#if defined(__arm__)
    asm volatile("mrs %0, msp\r\n"
                 : "=r"(stack_address)    // outputs
                 :                        // inputs
                 : "cc", "memory"         // clobbers
    );
#endif
    return stack_address;
}

/// Obtains the process stack address from the registers
inline uintptr_t get_process_stack_address(void) {
    uintptr_t stack_address = 0U;
#if defined(__arm__)
    asm volatile("mrs %0, psp\r\n"
                 : "=r"(stack_address)    // outputs
                 :                        // inputs
                 : "cc", "memory"         // clobbers
    );
#endif
    return stack_address;
}

/// Obtains the main stack address from the registers
inline void* get_process_stack_pointer(void) {
    void* stack_address = 0U;
#if defined(__arm__)
    asm volatile("mrs %0, psp \r\n"
                 : "=r"(stack_address)    // outputs
                 :                        // inputs
                 : "cc", "memory"         // clobbers
    );
#endif
    return stack_address;
}

/// Converts an unsigned 32 bit value to a float (not bit-direct!)
inline float convert(std::uint32_t value) {
    float out = 0.0f;
#if defined(__arm__)
    asm volatile(
        "vmov s0, %1\r\n"            // move value to s0
        "vcvt.f32.u32 s0, s0\r\n"    // convert to float
        "vmov %0, s0\r\n"            // move float back to arm for output
        : "=r"(out)                  // output
        : "r"(value)                 // input
        : "cc", "memory", "s0"       // clobbers
    );
#else
    out = static_cast<float>(value);
#endif
    return out;
}

/// Saves the Callee-Saved Registers
ALWAYS_INLINE inline void save_callee_registers(void) {
#if defined(__arm__)
    asm volatile("push {r4-r11}\r\n" :::);
#endif
}

/// Restores the Callee-Saved Registers
ALWAYS_INLINE inline void restore_callee_registers(void) {
#if defined(__arm__)
    asm volatile("pop {r4-r11}\r\n" :::);
#endif
}

/// @brief Returns the void typed Exception Frame from the Stack
/// @return
template <typename TYPE>
ALWAYS_INLINE inline TYPE* get_exception_frame(void) {
    TYPE* frame = nullptr;
#if defined(__arm__)
    asm volatile(
        "tst lr, #4 \r\n"       // check if the stack is supposed to use MSP or PSP
        "ite eq \r\n"           // if equal to zero
        "mrseq %0, msp \r\n"    // use MSP
        "mrsne %0, psp \r\n"    // else use PSP
        : "=r"(frame)           // outputs
        :                       // inputs
        : "cc", "memory"        // clobbers
    );
#endif
    return frame;
}

/// @brief Saves the context from before the interrupt service routine
ALWAYS_INLINE inline void interrupt_service_routine_context_save(void) {
#if defined(__arm__)
    asm volatile("push {r4-r11, lr} \r\n"
                 :    // outputs
                 :    // inputs
                 :    // clobbers
    );
#endif
}

/// @brief Restores the context after the interrupt service routine
ALWAYS_INLINE inline void interrupt_service_routine_context_restore(void) {
#if defined(__arm__)
    asm volatile("pop {r4-r11, pc} \r\n"
                 :    // outputs
                 :    // inputs
                 :    // clobbers
    );
#endif
}
}    // namespace thumb

#endif    // THUMB_HPP_
