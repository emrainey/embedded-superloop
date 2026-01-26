#ifndef CORTEX_M4_HPP_
#define CORTEX_M4_HPP_

/// @file
/// The Cortex M4 Variant Header

#include <cstdint>
#include <iso.hpp>
#include "core/Intervals.hpp"

#define CORTEX_HAS_FLASH 1
#undef CORTEX_HAS_ITCM
#undef CORTEX_HAS_DTCM
#define CORTEX_HAS_CCM 1
#define CORTEX_HAS_SRAM 1

namespace cortex {

/// Cortex M4 Specialized Namespace
namespace m4 {

namespace configuration {
constexpr static bool has_flash{true};
constexpr static bool has_ccm{true};
constexpr static bool has_itcm{false};
constexpr static bool has_dtcm{false};
constexpr static bool has_sram{true};
}    // namespace configuration

/// @brief The CPU ID Feature set (CPUID)
/// This definition is located *inside* the System Control Block (SCB) and as such this header cannot include that!
struct CentralProcessingUnitIdentification final {
    std::uint32_t PFR[2];  /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
    std::uint32_t DFR;     /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
    std::uint32_t ADR;     /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
    std::uint32_t MMFR[4]; /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
    std::uint32_t ISAR[5]; /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
};

/// The Auxiliary Control Register (ACTLR) is outside the System Control Block (SCB)
struct AuxiliaryControl final {
    /// The bit fields of the Auxiliary Control Register
    struct Fields final {
        std::uint32_t disable_interruption_multicycle_instructions : 1U;
        std::uint32_t disable_write_buffer_default_memory_map      : 1U;
        std::uint32_t disable_folding_instruction                  : 1U;
        std::uint32_t                                              : 5U;
        std::uint32_t disable_floating_pointer_out_of_order        : 1U;
        std::uint32_t disable_lazy_stacking_float_context          : 1U;
        std::uint32_t                                              : 21U;
    };
    // === MEMORY LAYOUT ===
    union {
        Fields bits;
        std::uint32_t whole;
    };
    // === MEMORY LAYOUT ===
};

/// Each bit maps to an (AFSR) bit somewhere in the documentation.
using AuxiliaryFaultStatus = std::uint32_t;

/// The maximum number of external interrupts supported by the M4 Architecture
constexpr static size_t max_extended_vectors{240U};

/// @brief The default number of MPU regions allowed on a Cortex Microcontroller processor
constexpr static size_t DefaultRegionLimit{8U};

}    // namespace m4

/// Use the M4 as the variant in the Core register definition.
namespace variant = m4;

/// The pointer to the Auxiliary Control Register
extern variant::AuxiliaryControl volatile auxiliary_control;

}    // namespace cortex

#endif    // CORTEX_M4_HPP_
