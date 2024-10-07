#ifndef CORTEX_BIST_HPP_
#define CORTEX_BIST_HPP_

#include <cstdint>

namespace cortex {

/// Used to self-test on boot. The system will attempt to trigger each type of handler listed and collect the results.
struct BuiltInSelfTest final {
    /// Used to hold information about a specific test.
    struct Element final {
        bool is_testing{false};    //!< Indicates that the element is under test
        bool has_passed{false};    //!< Indicates that the test was able to pass
    };
    Element trigger_non_maskable_interrupt{};     //!< Tests triggered the NMI
    Element trigger_hard_fault{};                 //!< Tests triggering the hard-fault
    Element trigger_memory_management_fault{};    //!< Tests triggering the memory management
                                                  //!< (must happen *after* MPU is initialized)
    Element trigger_bus_fault{};                  //!< Tests triggering the bus fault
    Element trigger_usage_fault{};                //!< Tests triggering the usage fault
    Element trigger_supervisor_call{};            //!< Test triggering the supervisor call
    Element trigger_pending_supervisor{};         //!< Test triggering the pending supervisor
    Element trigger_system_tick{};                //!< Test triggering the system tick
};

/// Built In Self Test. Implemented to self-test the system during @see main.
/// @warning Called during boot, but can be called later as well.
/// @return True if bist passes. False otherwise.
bool bist(bool is_system_initialized, bool is_system_configured);

/// A known pattern used to detect correct stacking of the svc call @{
constexpr static std::uint32_t kBistArg0 = 0xFF'FF'FF'FFUL;
constexpr static std::uint32_t kBistArg1 = 0x11'11'11'11UL;
constexpr static std::uint32_t kBistArg2 = 0x22'22'22'22UL;
constexpr static std::uint32_t kBistArg3 = 0x33'33'33'33UL;
/// @}

}    // namespace cortex

#endif    // CORTEX_BIST_HPP_