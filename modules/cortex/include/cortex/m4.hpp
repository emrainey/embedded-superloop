#ifndef CORTEX_M4_HPP_
#define CORTEX_M4_HPP_

/// @file
/// The Cortex M4 Variant Header

#include <cstdint>

namespace cortex {

/// Cortex M4 Specialized Namespace
namespace m4 {

/// @brief The CPU ID Feature set
struct CentralProcessingUnitIdentification final {
    std::uint32_t PFR[2];          /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
    std::uint32_t DFR;             /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
    std::uint32_t ADR;             /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
    std::uint32_t MMFR[4];         /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
    std::uint32_t ISAR[5];         /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
    std::uint32_t _reserved[5];    ///< Reserved Fields
};

/// The Auxiliary Control Register (ACTLR) is outside the SCB.
struct AuxiliaryControl final {
    struct Fields final {
        std::uint32_t disable_interruption_multicycle_instructions : 1U;
        std::uint32_t disable_write_buffer_default_memory_map      : 1U;
        std::uint32_t disable_folding_instruction                  : 1U;
        std::uint32_t                                              : 5U;
        std::uint32_t disable_floating_pointer_out_of_order        : 1U;
        std::uint32_t disable_lazy_stacking_float_context          : 1U;
        std::uint32_t                                              : 21U;
    };
    union {
        Fields bits;
        std::uint32_t whole;
    };
};

}    // namespace m4

/// Use the M4 as the variant in the Core register definition.
namespace variant = m4;

}    // namespace cortex

/// This must be included after the definitions above
#include "cortex/mcu.hpp"

#endif    // CORTEX_M4_HPP_