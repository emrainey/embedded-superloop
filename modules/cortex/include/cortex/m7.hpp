#ifndef CORTEX_M7_HPP_
#define CORTEX_M7_HPP_

/// @file
/// The Cortex M7 Variant Header

#include <cstdint>

#define CORTEX_HAS_FLASH 1
#define CORTEX_HAS_ITCM 1
#define CORTEX_HAS_DTCM 1
#undef CORTEX_HAS_CCM
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
    std::uint32_t PFR[2];          /*!< Offset: 0x040 (R/ )  Processor Feature Register                            */
    std::uint32_t DFR;             /*!< Offset: 0x048 (R/ )  Debug Feature Register                                */
    std::uint32_t ADR;             /*!< Offset: 0x04C (R/ )  Auxiliary Feature Register                            */
    std::uint32_t MMFR[4];         /*!< Offset: 0x050 (R/ )  Memory Model Feature Register                         */
    std::uint32_t ISAR[5];         /*!< Offset: 0x060 (R/ )  Instruction Set Attributes Register                   */
    std::uint32_t _reserved[5];    ///< Reserved Fields
};

/// The Auxiliary Control Register (ACTLR) is outside the System Control Block (SCB)
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

/// Auxiliary Bus Fault Status Register (ABFSR) bitfield
struct AuxiliaryBusFaultStatus final {
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

    union {
        Fields bits;            ///< Access the individual bits of the register
        std::uint32_t whole;    ///< Access the whole 32 bits as a single value
    };
};

/// @TODO Eliminate the need for this namespace?
/// ONLY the linker should know these values.
/// The primary reason they are know is due to the MPU and the need to have large address
/// ranges defined as constexprs for compile time use.
namespace address {

/// Base Code Address
constexpr static uintptr_t code = 0x00000000;

/// Base SRAM Address
constexpr static uintptr_t sram = 0x20000000;

/// Base Peripherals Address
constexpr static uintptr_t peripheral = 0x40000000;

/// Base RAM0 Address
constexpr static uintptr_t ram0 = 0x60000000;

/// Base Device0 Address
constexpr static uintptr_t device_shared = 0xA0000000;

/// Base System Address
constexpr static uintptr_t system = 0xE0000000;

/// Vendor Region (Vendor_SYS) Address
constexpr static uintptr_t vendor = 0xE0100000;

}    // namespace address

/// @brief The sizes of the Ranges of the Processor
namespace sizes {
/// Code space is defined as 256 MB
constexpr static std::uint32_t code = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t sram = 256U * iso::prefix::mebi;

/// Peripheral space is defined as 256 MB
constexpr static std::uint32_t peripheral = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t ram0 = 256U * iso::prefix::mebi;

/// SRAM space is defined as 256 MB
constexpr static std::uint32_t ram1 = 256U * iso::prefix::mebi;

/// System space is defined as 1 MB
constexpr static std::uint32_t system = 1U * iso::prefix::mebi;

/// Private Peripheral Bus space is defined as 1 MB
constexpr static std::uint32_t private_peripheral = 1U * iso::prefix::mebi;

/// Vendor System space is defined as 256 MB minus 1 MB
constexpr static std::uint32_t vendor = (256U * iso::prefix::mebi) - private_peripheral;

/// @brief The sizes represented as powers of 2
namespace power2 {

/// The Power of 2 of the code section
constexpr static std::uint32_t code = polyfill::log2(cortex::sizes::code);

/// The Power of 2 of the SRAM section
constexpr static std::uint32_t sram = polyfill::log2(cortex::sizes::sram);

/// The Power of 2 of the Peripheral space
constexpr static std::uint32_t peripheral = polyfill::log2(cortex::sizes::peripheral);

/// The Power of 2 of the System section
constexpr static std::uint32_t system = polyfill::log2(cortex::sizes::system);

/// The Power of 2 of the Private Peripherals section
constexpr static std::uint32_t private_peripheral = polyfill::log2(cortex::sizes::private_peripheral);
}    // namespace power2

}    // namespace sizes

/// @brief The Cortex Microcontroller processor memory regions
/// @note The order of the regions is important for the MPU
/// @todo Construct this table in the linkerscript, not in C++ as we really do not need to know these addresses.
constexpr core::Interval unsorted_memory_regions_array[] = {
    {cortex::address::code, cortex::address::code + cortex::sizes::code - 1U},
    {cortex::address::sram, cortex::address::sram + cortex::sizes::sram - 1U},
    {cortex::address::peripheral, cortex::address::peripheral + cortex::sizes::peripheral - 1U},
    {cortex::address::ram0, cortex::address::ram0 + cortex::sizes::ram0 - 1U},
    {cortex::address::ram1, cortex::address::ram1 + cortex::sizes::ram1 - 1U},
    {cortex::address::system, cortex::address::system + cortex::sizes::system - 1U},
    {cortex::address::vendor, cortex::address::vendor + cortex::sizes::vendor - 1U},
};

/// @brief The unsorted memory regions
constexpr core::Array<core::Interval, dimof(unsorted_memory_regions_array)> unsorted_memory_regions{unsorted_memory_regions_array};
/// @brief The sorted memory regions. These were sorted by a constexpr function at compile time.
constexpr core::Array<core::Interval, dimof(unsorted_memory_regions_array)> sorted_memory_regions = core::Sort(unsorted_memory_regions);
static_assert(core::IsSortedAndNonOverlapping(sorted_memory_regions), "Must be sorted and non-overlapping");

}    // namespace m7

/// Use the M7 as the variant in the Core register definition.
namespace variant = m7;

/// Each bit maps to an (AFSR) bit somewhere in the documentation.
using AuxiliaryFaultStatus = cortex::m7::AuxiliaryBusFaultStatus;

/// @brief The default number of MPU regions allowed on a Cortex Microcontroller processor
constexpr static size_t DefaultRegionLimit{16U};

/// The pointer to the Auxiliary Control Register
extern variant::AuxiliaryControl volatile auxiliary_control;

}    // namespace cortex

#endif    // CORTEX_M7_HPP_
