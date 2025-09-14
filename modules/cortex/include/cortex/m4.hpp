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

/// Base RAM1 Address
constexpr static uintptr_t ram1 = 0x80000000;

/// Base Device0 Address
constexpr static uintptr_t device_shared = 0xA0000000;

/// Base Device1 Address
constexpr static uintptr_t device_unshared = 0xC0000000;

/// Base System Address
constexpr static uintptr_t system = 0xE0000000;

/// Instruction Trace Macrocell (ITM) Address
constexpr static uintptr_t itm = 0xE0000000;

/// Debug Watch and Trace (DWT) Address
constexpr static uintptr_t dwt = 0xE0001000;

/// Flash Patch and Breakpoint (FPB) Address
constexpr static uintptr_t fpb = 0xE0002000;

/// The Interrupt Control Type (ICTR) Address
constexpr static uintptr_t ictr = 0xE000E004;

/// The Auxiliary Control (ACTLR) Address
constexpr static uintptr_t actlr = 0xE000E008;

/// The System Tick (Sys_TICK) Address
constexpr static uintptr_t systick = 0xE000E010;

/// The Nested Interrupt Controller
constexpr static uintptr_t nvic = 0xE000E100;

/// System Control Block (SCB) Address
constexpr static uintptr_t scb = 0xE000ED00;

/// Memory Protected Unit (MPU) Address
constexpr static uintptr_t mpu = 0xE000ED90;

/// Debug System Registers (DSR) Address
constexpr static uintptr_t dsr = 0xE000EDF0;

/// Software Triggered Interrupt Register
constexpr static uintptr_t stir = 0xE000EF00;

/// Floating Point Extension Registers
constexpr static uintptr_t fp = 0xE000EF34;

/// Trace Protocol Interface Unit (TPIU) Address
constexpr static uintptr_t tpiu = 0xE0040000;

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
constexpr static std::uint32_t code = polyfill::log2(sizes::code);

/// The Power of 2 of the SRAM section
constexpr static std::uint32_t sram = polyfill::log2(sizes::sram);

/// The Power of 2 of the Peripheral space
constexpr static std::uint32_t peripheral = polyfill::log2(sizes::peripheral);

/// The Power of 2 of the System section
constexpr static std::uint32_t system = polyfill::log2(sizes::system);

/// The Power of 2 of the Private Peripherals section
constexpr static std::uint32_t private_peripheral = polyfill::log2(sizes::private_peripheral);
}    // namespace power2

}    // namespace sizes

/// @brief The Cortex Microcontroller processor memory regions
/// @note The order of the regions is important for the MPU
/// @todo Construct this table in the linkerscript, not in C++ as we really do not need to know these addresses.
constexpr core::Interval unsorted_memory_regions_array[] = {
    {address::code, address::code + sizes::code - 1U},
    {address::sram, address::sram + sizes::sram - 1U},
    {address::peripheral, address::peripheral + sizes::peripheral - 1U},
    {address::ram0, address::ram0 + sizes::ram0 - 1U},
    {address::ram1, address::ram1 + sizes::ram1 - 1U},
    {address::system, address::system + sizes::system - 1U},
    {address::vendor, address::vendor + sizes::vendor - 1U},
};

/// @brief The unsorted memory regions
constexpr core::Array<core::Interval, dimof(unsorted_memory_regions_array)> unsorted_memory_regions{unsorted_memory_regions_array};
/// @brief The sorted memory regions. These were sorted by a constexpr function at compile time.
constexpr core::Array<core::Interval, dimof(unsorted_memory_regions_array)> sorted_memory_regions = core::Sort(unsorted_memory_regions);
static_assert(core::IsSortedAndNonOverlapping(sorted_memory_regions), "Must be sorted and non-overlapping");

/// Each bit maps to an (AFSR) bit somewhere in the documentation.
using AuxiliaryFaultStatus = std::uint32_t;

}    // namespace m4

/// Use the M4 as the variant in the Core register definition.
namespace variant = m4;

/// @brief The default number of MPU regions allowed on a Cortex Microcontroller processor
constexpr static size_t DefaultRegionLimit{8U};

/// The pointer to the Auxiliary Control Register
extern variant::AuxiliaryControl volatile auxiliary_control;

}    // namespace cortex

#endif    // CORTEX_M4_HPP_
