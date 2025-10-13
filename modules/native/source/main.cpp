#include <csignal>
#include <cstdio>
#include "cortex/vectors.hpp"
#include "polyfill.hpp"

// The first 16 vectors are defined in the cortex/system.hpp file
// The reset are defined per chip in the respective chip module from the vendor
// we don't know how many there could be (?)

std::int32_t interrupt{-1};

void fire_interrupt(std::int32_t irq) {
    interrupt = irq;
    // fire the signal to the process
    raise(SIGUSR1);
}

// Pretend we have have a hardware interrupt system here
void signal_handler(int sig) {
    // re-register the signal handler
    signal(SIGUSR1, signal_handler);
    printf("SIGUSR1: %d Interrupt %d\n", sig, interrupt);
    // invoke the vectors using the cortex vector table as 0-15 and the external table starting at 16
    if (interrupt > 0) {
        cortex::exceptions::InterruptServiceRoutine isr = static_cast<cortex::exceptions::InterruptServiceRoutine>(interrupt);
        interrupt = -1;
        if (isr < cortex::exceptions::InterruptServiceRoutine::BaseExternal) {
            switch (isr) {
                case cortex::exceptions::InterruptServiceRoutine::Reset:
                    cortex::vector_table.handlers.reset_entry();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::NonMaskable:
                    cortex::vector_table.handlers.non_maskable_interrupt();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::HardFault:
                    cortex::vector_table.handlers.faults.hard();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::MemoryManagement:
                    cortex::vector_table.handlers.faults.memory_management();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::BusFault:
                    cortex::vector_table.handlers.faults.bus();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::UsageFault:
                    cortex::vector_table.handlers.faults.usage();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::SupervisorCall:
                    cortex::vector_table.handlers.supervisor_call();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::PendingSupervisor:
                    cortex::vector_table.handlers.pending_supervisor();
                    break;
                case cortex::exceptions::InterruptServiceRoutine::SystemTick:
                    // increment the system tick
                    cortex::vector_table.handlers.system_tick();
                    break;
                default:
                    // others go unhandled
                    break;
            }
        } else {
            std::uint32_t index = to_underlying(isr) - to_underlying(cortex::exceptions::InterruptServiceRoutine::BaseExternal);
            if (index < cortex::variant::max_extended_vectors) {
                cortex::extended_vectors.handlers[index]();
            }
        }
    }
}

int main(int argc, char *argv[]) {
    (void)argc;
    (void)argv;

    // register signal handler for various emulated interrupts
    signal(SIGUSR1, signal_handler);
    // register SIGBUS for BusFaults?
    // register SIGFPE for Erroneous arithmetic operation => UsageFaults?
    // register SIGILL for UsageFaults?
    // register SIGSEGV for MemManageFaults?

    // enter the reset entry point
    cortex::vector_table.handlers.reset_entry();
    return 0;
}
