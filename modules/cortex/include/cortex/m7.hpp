#ifndef CORTEX_M7_HPP_
#define CORTEX_M7_HPP_

/// @file
/// The Cortex M7 Variant Header

#include <cstdint>
#include <iso.hpp>
#include "core/Intervals.hpp"
#include "cortex/peripherals/CacheInformation.hpp"
#include "cortex/peripherals/TightlyCoupledMemory.hpp"

/// Indicates this Cortex-M7 has Flash memory
#define CORTEX_HAS_FLASH 1
/// Indicates this Cortex-M7 has Instruction Tightly Coupled Memory
#define CORTEX_HAS_ITCM 1
/// Indicates this Cortex-M7 has Data Tightly Coupled Memory
#define CORTEX_HAS_DTCM 1
/// Cortex-M7 does not have Core Coupled Memory
#undef CORTEX_HAS_CCM
/// Indicates this Cortex-M7 has SRAM
#define CORTEX_HAS_SRAM 1

namespace cortex {

/// Cortex M7 Specialized Namespace
namespace m7 {

namespace configuration {
constexpr static bool has_flash{true};
constexpr static bool has_ccm{false};
constexpr static bool has_itcm{true};
constexpr static bool has_dtcm{true};
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

/// Pull the M7 definition into the variant definition.
using CacheInformation = peripherals::CacheInformation;

/// The Data and Instruction Cache Control Register (DCIMVAC, DCCMVAC, DCCSW, DCCISW, ICIALLU, ICIMVAU, DCIMVAC, DCISW)
struct DataAndInstructionCacheControl final {
    /// The Set-Way structure for cache operations
    struct SetWay {
        std::uint32_t  : 5;     // bits 0:4
        uint32_t way   : 9;     // bits 5:13
        uint32_t       : 16;    // bits 14:29
        uint32_t level : 2;     // bits 30:31
    };

    std::uint32_t invalidate_whole_instruction_cache;             ///< I-Cache Invalidate All to PoU by writing any value (ICIALLU)
    std::uint32_t : 32;                                           ///< Reserved field
    std::uintptr_t invalidate_instruction_cache_by_address;       ///< I-Cache Invalidate by Address (ICIMVAU)
    std::uintptr_t invalidate_data_cache_by_address;              ///< D-Cache Invalidate by Address to Point of Coherency (DCIMVAC)
    std::uintptr_t invalidate_data_cache_by_setway;               ///< D-Cache Invalidate by Set-way (DCISW)
    std::uintptr_t clean_data_cache_to_unity_by_address;          ///< D-Cache Invalidute Clean by Address (DCCMVAU)
    std::uintptr_t clean_data_cache_to_coherency_by_address;      ///< D-Cache Clean by MVA to PoC (DCCMVAC)
    std::uintptr_t clean_data_cache_by_setway;                    ///< D-Cache Clean by Set-way (DCCSW)
    std::uintptr_t clean_and_invalidate_data_cache_by_address;    ///< D-Cache Clean and Invalidate by Address (DCCIMVAC)
    std::uintptr_t clean_and_invalidate_data_cache_by_setway;     ///< D-Cache Clean and Invalidate by Set-way (DCCISW)
    std::uint32_t : 32;                                           ///< Reserved field (BPIALL)
    std::uint32_t : 32;                                           ///< Reserved field
};
#if defined(__arm__)
static_assert(sizeof(DataAndInstructionCacheControl) == 0x30UL, "Must be this exact size");
#endif

/// Memory-mapped register block for cache control operations
extern DataAndInstructionCacheControl volatile data_and_instruction_cache_control;

/// The Auxiliary Control Register (ACTLR) is outside the System Control Block (SCB)
/// @warning Only use these if you know EXACTLY what you are doing!
struct AuxiliaryControl final {
    /// The bit fields of the Auxiliary Control Register
    struct Fields final {
        std::uint32_t                                               : 2U;    // Reserved
        std::uint32_t                                               : 1U;    // DISFOLD (0==Normal)
        std::uint32_t                                               : 7U;    // Reserved
        std::uint32_t disable_floating_point_exception_outputs      : 1U;
        std::uint32_t disable_dynamic_read_allocate_mode_wbwa       : 1U;
        std::uint32_t disable_itm_and_dwt_atb_flush                 : 1U;
        std::uint32_t disable_btac_read                             : 1U;
        std::uint32_t disable_btac_alloc                            : 1U;
        std::uint32_t disable_critical_axi_read_under_read          : 1U;
        // 16
        std::uint32_t disable_dual_issue_direct_braches             : 1U;
        std::uint32_t disable_dual_issue_indirect_branches          : 1U;
        std::uint32_t disable_dual_issue_loads_to_PC                : 1U;
        std::uint32_t disable_dual_issue_integer_MAC_and_MUL        : 1U;
        std::uint32_t disable_dual_issue_VFP                        : 1U;
        std::uint32_t disable_instruction_issue_direct_branch       : 1U;
        std::uint32_t disable_instruction_issue_indirect_branch     : 1U;
        std::uint32_t disable_instruction_issue_loads_PC            : 1U;
        std::uint32_t disable_instruction_issue_integer_MAC_and_MUL : 1U;
        std::uint32_t disable_instruction_issue_VFP                 : 1U;
        std::uint32_t disable_dynamic_allocation_of_ADD_SUB         : 1U;
        std::uint32_t disable_critical_axi_read_under_write         : 1U;
        std::uint32_t                                               : 1U;    // DISFPUISSOPT (0=Normal)
        std::uint32_t                                               : 3U;
    };
    // === MEMORY LAYOUT ===
    union {
        Fields bits;
        std::uint32_t whole;
    };
    // === MEMORY LAYOUT ===
};

/// Auxiliary Bus Fault Status Register (ABFSR) bitfield
struct AuxiliaryBusFaultStatus final {
    /// The bit fields of the Auxiliary Bus Fault Status Register
    struct Fields {
        std::uint32_t itcm     : 1U;     ///< Bit 0: ITCM Fault
        std::uint32_t dtcm     : 1U;     ///< Bit 1: DTCM Fault
        std::uint32_t ahbp     : 1U;     ///< Bit 2: AHB Master Fault
        std::uint32_t axim     : 1U;     ///< Bit 3: AXIM Fault
        std::uint32_t eppb     : 1U;     ///< Bit 4: EPPB Fault
        std::uint32_t          : 3U;     ///< Bit 5-7: Reserved
        std::uint32_t aximtype : 2U;     ///< Bits 8-9: AXIM Type
        std::uint32_t          : 22U;    ///< Bits 10-31: Reserved
    };
    // === MEMORY LAYOUT ===
    union {
        Fields bits;            ///< Access the individual bits of the register
        std::uint32_t whole;    ///< Access the whole 32 bits as a single value
    };
    // === MEMORY LAYOUT ===
};

/// Each bit maps to an (AFSR) bit somewhere in the documentation.
using AuxiliaryFaultStatus = cortex::m7::AuxiliaryBusFaultStatus;

/// The maximum number of external interrupts supported by the M7 Architecture
constexpr static size_t max_extended_vectors{240U};

/// @brief The default number of MPU regions allowed on a Cortex Microcontroller processor
constexpr static size_t DefaultRegionLimit{16U};

}    // namespace m7

/// Use the M7 as the variant in the Core register definition.
namespace variant = m7;

/// The pointer to the Auxiliary Control Register
extern variant::AuxiliaryControl volatile auxiliary_control;

}    // namespace cortex

#endif    // CORTEX_M7_HPP_
