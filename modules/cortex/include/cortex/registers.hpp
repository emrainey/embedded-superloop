#ifndef CORTEX_REGISTERS_HPP_
#define CORTEX_REGISTERS_HPP_

/// @file
/// The Cortex Microcontroller Register Header. These are not peripheral registers, but core registers, adjacent to the r0-13 registers.

#include <cstddef>
#include <cstdint>
#include "cortex/exceptions.hpp"

namespace cortex {

/// The Cortex Microcontroller Registers
namespace registers {

/// The Program Status Registers
struct ProgramStatus final {
    /// The Application Status Register (APSR)
    struct Application final {
        std::uint32_t            : 16U;    ///< Reserved field
        std::uint32_t ge_flags   : 4U;     //!< GE
        std::uint32_t            : 7U;     ///< Reserved field
        std::uint32_t saturation : 1U;     //!< aka Q
        std::uint32_t overflow   : 1U;     //!< aka V
        std::uint32_t carry      : 1U;     //!< aka C
        std::uint32_t zero       : 1U;     //!< aka Z
        std::uint32_t negative   : 1U;     //!< aka N
    };
    /// The Interrupt Status Register (IPSR)
    struct Interrupt final {
        /// @see cortex::m4::IRQn or processor specific enum
        exceptions::InterruptServiceRoutine interrupt_service_routine : 9U;
        /// Reserved field
        std::uint32_t                                                 : 23U;
    };
    /// The Execution Status Register (EPSR)
    struct Execution final {
        std::uint32_t        : 10U;    ///< Reserved field
        std::uint32_t bottom : 6U;     //!< Bottom ICI/IT bits
        std::uint32_t        : 8U;     ///< Reserved field
        std::uint32_t thumb  : 1U;     //!< Thumb Mode
        std::uint32_t top    : 2U;     //!< Top ICI/IT Bits
        std::uint32_t        : 5U;     ///< Reserved field

        inline std::uint32_t get(void) const {
            std::uint32_t tmp = static_cast<uint32_t>(top << 6U);
            tmp |= bottom;
            return tmp;
        }
    };
};

// The Mask Register Set
struct Masks final {
    /// The Priority Mask Register (PRIMASK)
    struct Priority final {
        std::uint32_t mask : 1;
        std::uint32_t      : 31;    ///< Reserved field
    };
    /// The Fault Mask Register (FAULTMASK)
    struct Fault final {
        std::uint32_t mask : 1;
        std::uint32_t      : 31;    ///< Reserved field
    };
    /// The Base Priority Mask Register (BASEPRI)
    struct BasePriority final {
        std::uint32_t mask : 8U;     //!< Not a bit mask but _masks_ priorities less than this value
        std::uint32_t      : 24U;    ///< Reserved field
    };
};

/// The special purpose Control Register (CONTROL)
struct Control final {
    /// @brief Default constructor
    constexpr Control()
        : whole{0U} {}
    /// @brief Parameterized constructor
    /// @param reg The value to put in the register
    Control(cortex::word reg)
        : whole{reg} {}
    /// @brief The bitfield definition of the register
    struct Fields final {
        modes::Privileged privilege : 1;     ///< Execution Privilege in Thread Mode
        modes::Stack stack          : 1;     ///< 0 is Main, 1 is Process
        std::uint32_t float_active  : 1;     ///< Floating Point Active
        std::uint32_t               : 29;    ///< Reserved field
    };
    /// @brief The union of the bitfield and the register as a whole.
    union {
        Fields parts;
        cortex::word whole;    ///< This is used via thumb instructions and thus should be a processor word and not a
                               ///< memory mapped register
    };
};

/// (FPSCR) Floating Point Status and Control Register
/// @see VMRS and VMSR thumb instructions
struct FloatingPointStatusControl final {
    /// @brief The bitfield definition of the register
    struct Fields final {
        std::uint32_t invalid_cumulative        : 1U;     ///< Invalid Operation
        std::uint32_t divide_by_zero_cumulative : 1U;     ///< Divide by Zero
        std::uint32_t overflow_cumulative       : 1U;     ///< Overflow
        std::uint32_t underflow_cumulative      : 1U;     ///< Underflow cumulative
        std::uint32_t inexact_cumulative        : 1U;     ///< Inexact cumulative
        std::uint32_t                           : 2U;     ///< Reserved
        std::uint32_t input_denormal_cumulative : 1U;     ///< Input denormal cumulative
        std::uint32_t                           : 14U;    ///< Reserved
        modes::Rounding rounding                : 2U;     ///< Rounding mode
        std::uint32_t flush_to_zero             : 1U;     ///< Flush to zero
        std::uint32_t default_nan               : 1U;     ///< Default NaN
        std::uint32_t half_precision            : 1U;     ///< Half precision
        std::uint32_t                           : 1U;     /// Reserved
        std::uint32_t overflow                  : 1U;     ///< Overflow
        std::uint32_t carry                     : 1U;     ///< Carry
        std::uint32_t zero                      : 1U;     ///< Zero
        std::uint32_t negative                  : 1U;     ///< Negative
    };
    /// @brief The union of the bitfield and the register as a whole.
    union {
        Fields parts;
        std::uint32_t whole;
    };
};

}    // namespace registers
}    // namespace cortex

#endif    // CORTEX_REGISTERS_HPP_
