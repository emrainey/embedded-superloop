#ifndef CORTEX_PERIPHERALS_TIGHTLYCOUPLEDMEMORY_HPP_
#define CORTEX_PERIPHERALS_TIGHTLYCOUPLEDMEMORY_HPP_

/// @file
/// The Tightly Coupled Memory related registers

namespace cortex {
namespace peripherals {

/// @brief Tightly Coupled Memory (TCM) control register
/// @details Represents the TCM configuration register in ARM Cortex-M processors.
/// TCM provides low-latency memory directly coupled to the processor for performance-critical code and data.
struct TightlyCoupledMemory final {
    /// Default constructor - initializes to zero
    TightlyCoupledMemory()
        : whole{0} {}
    /// Copy constructor from another instance
    TightlyCoupledMemory(TightlyCoupledMemory const& other)
        : whole{other.whole} {}
    /// Copy constructor from volatile register
    TightlyCoupledMemory(TightlyCoupledMemory volatile& other)
        : whole{other.whole} {}
    /// @brief Bit field layout for the TCM control register
    struct Fields {
        std::uint32_t enable            : 1;     ///< Enable the TCM
        std::uint32_t read_modify_write : 1;     ///< Enable Read-Modify-Write for modifications which are not unit sized.
        std::uint32_t retry             : 1;     ///< Enable retry on access failure.
        std::uint32_t size              : 4;     ///< Size of the TCM in
        std::uint32_t                   : 25;    ///< Reserved bits
    };
    union {
        Fields bits;
        std::uint32_t whole;
    };

    /// @brief Returns the size of the TCM in bytes
    inline std::size_t GetSize() const {
        if (bits.size == 0) {
            return 0;
        } else {
            return static_cast<std::size_t>(1U << (bits.size + 9U));
        }
    }

    /// Assignment from copy back to registers
    void operator=(TightlyCoupledMemory const& other) volatile { whole = other.whole; }
    /// Copy from volatile register to local copy
    void operator=(TightlyCoupledMemory volatile& other) { whole = other.whole; }
};
static_assert(sizeof(TightlyCoupledMemory) == sizeof(std::uint32_t), "Must be exactly this size");

/// The ITCM Control Registers
extern TightlyCoupledMemory volatile itcm_control;

/// The DTCM Control Registers
extern TightlyCoupledMemory volatile dtcm_control;

}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_PERIPHERALS_TIGHTLYCOUPLEDMEMORY_HPP_
