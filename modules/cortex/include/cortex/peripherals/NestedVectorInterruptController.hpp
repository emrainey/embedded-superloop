#ifndef CORTEX_PERIPHERALS_NESTED_VECTOR_INTERRUPT_CONTROLLER_HPP_
#define CORTEX_PERIPHERALS_NESTED_VECTOR_INTERRUPT_CONTROLLER_HPP_

/// @file
/// The Cortex Microcontroller Nested Vector Interrupt Controller Header

#include <cstdint>

namespace cortex {
namespace peripherals {

namespace nvic {
/// @brief The normal shift size for all registers
constexpr static uint32_t shift = 5U;
/// @brief The mask for all registers
constexpr static uint32_t mask = (1U << shift) - 1U;
/// @brief The limit to the number of external interrupts (as defined by ARM it is 480)
constexpr static uint32_t limit = 496U;
}    // namespace nvic

/// The Nested Vector Interrupt Controller peripheral
struct NestedVectorInterruptController final {
    std::uint32_t enable[16];                //!< Offset 0x0 to 0x3C inclusive
    std::uint32_t _reserved1[16];            ///< Reserved Fields
    std::uint32_t clear[16];                 //!< Offsets 0x80 to 0xBC inclusive
    std::uint32_t _reserved2[16];            ///< Reserved Fields
    std::uint32_t pending[16];               //!< Offset 0x100 to 0x13C inclusive
    std::uint32_t _reserved3[16];            ///< Reserved Fields
    std::uint32_t cancel[16];                //!< Offset 0x180 to 0x1BC inclusive
    std::uint32_t _reserved4[16];            ///< Reserved Fields
    std::uint32_t /* const */ active[16];    //!< Offset 0x200 to 0x23C inclusive
    std::uint32_t _reserved5[48];            ///< Reserved Fields
    std::uint8_t priority[nvic::limit];      //!< Offset 0x300 to 0x4EC inclusive
    std::uint32_t _reserved6[452];           ///< Reserved Fields
};
static_assert(sizeof(NestedVectorInterruptController) == 0xC00, "Must be this size");

/// The peripheral NVIC as defined in Linker
extern NestedVectorInterruptController volatile nested_vector_interrupt_controller;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_PERIPHERALS_NESTED_VECTOR_INTERRUPT_CONTROLLER_HPP_
