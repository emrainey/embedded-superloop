
#ifndef STM32_REGISTERS_RANDOMNUMBERGENERATOR_HPP_
#define STM32_REGISTERS_RANDOMNUMBERGENERATOR_HPP_

/// @file
/// Auto Generated Structure Definitions for RandomNumberGenerator from the Peripheralyzer.
/// @copyright 

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Random number generator (RNG)
struct RandomNumberGenerator final {
/// control register (CR)
struct Control final {

    /// Default Constructor
    Control() : whole{0u} {}
    /// Parameterized Constructor
    Control(std::uint32_t const& value) : whole{value} {}
    /// The internal bitfield for the register
    struct Fields final {
        /// (reserved)
        std::uint32_t  : 2; // bits 0:1
        /// Random number generator enable (RNGEN)
        std::uint32_t enable : 1; // bit 2
        /// Interrupt enable (IE)
        std::uint32_t interrupt_enable : 1; // bit 3
        /// (reserved)
        std::uint32_t  : 28; // bits 4:31
    };
    //==MEMORY==========================
    union {
        Fields bits;
        std::uint32_t whole;
    };
    //==================================
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(Control volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(Control const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(std::uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an std::uint32_t.
    inline explicit operator std::uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an std::uint32_t
    inline explicit operator std::uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<Control>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(Control) == 4UL, "Must be this exact size");/// status register (SR)
struct Status final {

    /// Default Constructor
    Status() : whole{0u} {}
    /// Parameterized Constructor
    Status(std::uint32_t const& value) : whole{value} {}
    /// The internal bitfield for the register
    struct Fields final {
        /// Data ready (DRDY)
        std::uint32_t data_ready : 1; // bit 0
        /// Clock error current status (CECS)
        std::uint32_t clock_error_current_status : 1; // bit 1
        /// Seed error current status (SECS)
        std::uint32_t seed_error_current_status : 1; // bit 2
        /// (reserved)
        std::uint32_t  : 2; // bits 3:4
        /// Clock error interrupt status (CEIS)
        std::uint32_t clock_error_interrupt_status : 1; // bit 5
        /// Seed error interrupt status (SEIS)
        std::uint32_t seed_error_interrupt_status : 1; // bit 6
        /// (reserved)
        std::uint32_t  : 25; // bits 7:31
    };
    //==MEMORY==========================
    union {
        Fields bits;
        std::uint32_t whole;
    };
    //==================================
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(Status volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(Status const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(std::uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an std::uint32_t.
    inline explicit operator std::uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an std::uint32_t
    inline explicit operator std::uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<Status>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(Status) == 4UL, "Must be this exact size");/// data register (DR)
struct DR final {

    /// Default Constructor
    DR() : whole{0u} {}
    /// Parameterized Constructor
    DR(std::uint32_t const& value) : whole{value} {}
    /// The internal bitfield for the register
    struct Fields final {
        /// Random data (RNDATA)
        std::uint32_t rndata : 32; // bits 0:31
    };
    //==MEMORY==========================
    union {
        Fields bits;
        std::uint32_t whole;
    };
    //==================================
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(DR volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(DR const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type std::uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(std::uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an std::uint32_t.
    inline explicit operator std::uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an std::uint32_t
    inline explicit operator std::uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<DR>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(DR) == 4UL, "Must be this exact size");

    /// control register (CR)
    Control control; // offset 0x0UL
    /// status register (SR)
    Status status; // offset 0x4UL
    /// data register (DR)
    DR dr; // offset 0x8UL
    std::uint32_t : 32; // offset 0xcUL
    std::uint32_t : 32; // offset 0x10UL
    std::uint32_t : 32; // offset 0x14UL
    std::uint32_t : 32; // offset 0x18UL
    std::uint32_t : 32; // offset 0x1cUL
    std::uint32_t : 32; // offset 0x20UL
    std::uint32_t : 32; // offset 0x24UL
    std::uint32_t : 32; // offset 0x28UL
    std::uint32_t : 32; // offset 0x2cUL
    std::uint32_t : 32; // offset 0x30UL
    std::uint32_t : 32; // offset 0x34UL
    std::uint32_t : 32; // offset 0x38UL
    std::uint32_t : 32; // offset 0x3cUL
    std::uint32_t : 32; // offset 0x40UL
    std::uint32_t : 32; // offset 0x44UL
    std::uint32_t : 32; // offset 0x48UL
    std::uint32_t : 32; // offset 0x4cUL
    std::uint32_t : 32; // offset 0x50UL
    std::uint32_t : 32; // offset 0x54UL
    std::uint32_t : 32; // offset 0x58UL
    std::uint32_t : 32; // offset 0x5cUL
    std::uint32_t : 32; // offset 0x60UL
    std::uint32_t : 32; // offset 0x64UL
    std::uint32_t : 32; // offset 0x68UL
    std::uint32_t : 32; // offset 0x6cUL
    std::uint32_t : 32; // offset 0x70UL
    std::uint32_t : 32; // offset 0x74UL
    std::uint32_t : 32; // offset 0x78UL
    std::uint32_t : 32; // offset 0x7cUL
    std::uint32_t : 32; // offset 0x80UL
    std::uint32_t : 32; // offset 0x84UL
    std::uint32_t : 32; // offset 0x88UL
    std::uint32_t : 32; // offset 0x8cUL
    std::uint32_t : 32; // offset 0x90UL
    std::uint32_t : 32; // offset 0x94UL
    std::uint32_t : 32; // offset 0x98UL
    std::uint32_t : 32; // offset 0x9cUL
    std::uint32_t : 32; // offset 0xa0UL
    std::uint32_t : 32; // offset 0xa4UL
    std::uint32_t : 32; // offset 0xa8UL
    std::uint32_t : 32; // offset 0xacUL
    std::uint32_t : 32; // offset 0xb0UL
    std::uint32_t : 32; // offset 0xb4UL
    std::uint32_t : 32; // offset 0xb8UL
    std::uint32_t : 32; // offset 0xbcUL
    std::uint32_t : 32; // offset 0xc0UL
    std::uint32_t : 32; // offset 0xc4UL
    std::uint32_t : 32; // offset 0xc8UL
    std::uint32_t : 32; // offset 0xccUL
    std::uint32_t : 32; // offset 0xd0UL
    std::uint32_t : 32; // offset 0xd4UL
    std::uint32_t : 32; // offset 0xd8UL
    std::uint32_t : 32; // offset 0xdcUL
    std::uint32_t : 32; // offset 0xe0UL
    std::uint32_t : 32; // offset 0xe4UL
    std::uint32_t : 32; // offset 0xe8UL
    std::uint32_t : 32; // offset 0xecUL
    std::uint32_t : 32; // offset 0xf0UL
    std::uint32_t : 32; // offset 0xf4UL
    std::uint32_t : 32; // offset 0xf8UL
    std::uint32_t : 32; // offset 0xfcUL
    std::uint32_t : 32; // offset 0x100UL
    std::uint32_t : 32; // offset 0x104UL
    std::uint32_t : 32; // offset 0x108UL
    std::uint32_t : 32; // offset 0x10cUL
    std::uint32_t : 32; // offset 0x110UL
    std::uint32_t : 32; // offset 0x114UL
    std::uint32_t : 32; // offset 0x118UL
    std::uint32_t : 32; // offset 0x11cUL
    std::uint32_t : 32; // offset 0x120UL
    std::uint32_t : 32; // offset 0x124UL
    std::uint32_t : 32; // offset 0x128UL
    std::uint32_t : 32; // offset 0x12cUL
    std::uint32_t : 32; // offset 0x130UL
    std::uint32_t : 32; // offset 0x134UL
    std::uint32_t : 32; // offset 0x138UL
    std::uint32_t : 32; // offset 0x13cUL
    std::uint32_t : 32; // offset 0x140UL
    std::uint32_t : 32; // offset 0x144UL
    std::uint32_t : 32; // offset 0x148UL
    std::uint32_t : 32; // offset 0x14cUL
    std::uint32_t : 32; // offset 0x150UL
    std::uint32_t : 32; // offset 0x154UL
    std::uint32_t : 32; // offset 0x158UL
    std::uint32_t : 32; // offset 0x15cUL
    std::uint32_t : 32; // offset 0x160UL
    std::uint32_t : 32; // offset 0x164UL
    std::uint32_t : 32; // offset 0x168UL
    std::uint32_t : 32; // offset 0x16cUL
    std::uint32_t : 32; // offset 0x170UL
    std::uint32_t : 32; // offset 0x174UL
    std::uint32_t : 32; // offset 0x178UL
    std::uint32_t : 32; // offset 0x17cUL
    std::uint32_t : 32; // offset 0x180UL
    std::uint32_t : 32; // offset 0x184UL
    std::uint32_t : 32; // offset 0x188UL
    std::uint32_t : 32; // offset 0x18cUL
    std::uint32_t : 32; // offset 0x190UL
    std::uint32_t : 32; // offset 0x194UL
    std::uint32_t : 32; // offset 0x198UL
    std::uint32_t : 32; // offset 0x19cUL
    std::uint32_t : 32; // offset 0x1a0UL
    std::uint32_t : 32; // offset 0x1a4UL
    std::uint32_t : 32; // offset 0x1a8UL
    std::uint32_t : 32; // offset 0x1acUL
    std::uint32_t : 32; // offset 0x1b0UL
    std::uint32_t : 32; // offset 0x1b4UL
    std::uint32_t : 32; // offset 0x1b8UL
    std::uint32_t : 32; // offset 0x1bcUL
    std::uint32_t : 32; // offset 0x1c0UL
    std::uint32_t : 32; // offset 0x1c4UL
    std::uint32_t : 32; // offset 0x1c8UL
    std::uint32_t : 32; // offset 0x1ccUL
    std::uint32_t : 32; // offset 0x1d0UL
    std::uint32_t : 32; // offset 0x1d4UL
    std::uint32_t : 32; // offset 0x1d8UL
    std::uint32_t : 32; // offset 0x1dcUL
    std::uint32_t : 32; // offset 0x1e0UL
    std::uint32_t : 32; // offset 0x1e4UL
    std::uint32_t : 32; // offset 0x1e8UL
    std::uint32_t : 32; // offset 0x1ecUL
    std::uint32_t : 32; // offset 0x1f0UL
    std::uint32_t : 32; // offset 0x1f4UL
    std::uint32_t : 32; // offset 0x1f8UL
    std::uint32_t : 32; // offset 0x1fcUL
    std::uint32_t : 32; // offset 0x200UL
    std::uint32_t : 32; // offset 0x204UL
    std::uint32_t : 32; // offset 0x208UL
    std::uint32_t : 32; // offset 0x20cUL
    std::uint32_t : 32; // offset 0x210UL
    std::uint32_t : 32; // offset 0x214UL
    std::uint32_t : 32; // offset 0x218UL
    std::uint32_t : 32; // offset 0x21cUL
    std::uint32_t : 32; // offset 0x220UL
    std::uint32_t : 32; // offset 0x224UL
    std::uint32_t : 32; // offset 0x228UL
    std::uint32_t : 32; // offset 0x22cUL
    std::uint32_t : 32; // offset 0x230UL
    std::uint32_t : 32; // offset 0x234UL
    std::uint32_t : 32; // offset 0x238UL
    std::uint32_t : 32; // offset 0x23cUL
    std::uint32_t : 32; // offset 0x240UL
    std::uint32_t : 32; // offset 0x244UL
    std::uint32_t : 32; // offset 0x248UL
    std::uint32_t : 32; // offset 0x24cUL
    std::uint32_t : 32; // offset 0x250UL
    std::uint32_t : 32; // offset 0x254UL
    std::uint32_t : 32; // offset 0x258UL
    std::uint32_t : 32; // offset 0x25cUL
    std::uint32_t : 32; // offset 0x260UL
    std::uint32_t : 32; // offset 0x264UL
    std::uint32_t : 32; // offset 0x268UL
    std::uint32_t : 32; // offset 0x26cUL
    std::uint32_t : 32; // offset 0x270UL
    std::uint32_t : 32; // offset 0x274UL
    std::uint32_t : 32; // offset 0x278UL
    std::uint32_t : 32; // offset 0x27cUL
    std::uint32_t : 32; // offset 0x280UL
    std::uint32_t : 32; // offset 0x284UL
    std::uint32_t : 32; // offset 0x288UL
    std::uint32_t : 32; // offset 0x28cUL
    std::uint32_t : 32; // offset 0x290UL
    std::uint32_t : 32; // offset 0x294UL
    std::uint32_t : 32; // offset 0x298UL
    std::uint32_t : 32; // offset 0x29cUL
    std::uint32_t : 32; // offset 0x2a0UL
    std::uint32_t : 32; // offset 0x2a4UL
    std::uint32_t : 32; // offset 0x2a8UL
    std::uint32_t : 32; // offset 0x2acUL
    std::uint32_t : 32; // offset 0x2b0UL
    std::uint32_t : 32; // offset 0x2b4UL
    std::uint32_t : 32; // offset 0x2b8UL
    std::uint32_t : 32; // offset 0x2bcUL
    std::uint32_t : 32; // offset 0x2c0UL
    std::uint32_t : 32; // offset 0x2c4UL
    std::uint32_t : 32; // offset 0x2c8UL
    std::uint32_t : 32; // offset 0x2ccUL
    std::uint32_t : 32; // offset 0x2d0UL
    std::uint32_t : 32; // offset 0x2d4UL
    std::uint32_t : 32; // offset 0x2d8UL
    std::uint32_t : 32; // offset 0x2dcUL
    std::uint32_t : 32; // offset 0x2e0UL
    std::uint32_t : 32; // offset 0x2e4UL
    std::uint32_t : 32; // offset 0x2e8UL
    std::uint32_t : 32; // offset 0x2ecUL
    std::uint32_t : 32; // offset 0x2f0UL
    std::uint32_t : 32; // offset 0x2f4UL
    std::uint32_t : 32; // offset 0x2f8UL
    std::uint32_t : 32; // offset 0x2fcUL
    std::uint32_t : 32; // offset 0x300UL
    std::uint32_t : 32; // offset 0x304UL
    std::uint32_t : 32; // offset 0x308UL
    std::uint32_t : 32; // offset 0x30cUL
    std::uint32_t : 32; // offset 0x310UL
    std::uint32_t : 32; // offset 0x314UL
    std::uint32_t : 32; // offset 0x318UL
    std::uint32_t : 32; // offset 0x31cUL
    std::uint32_t : 32; // offset 0x320UL
    std::uint32_t : 32; // offset 0x324UL
    std::uint32_t : 32; // offset 0x328UL
    std::uint32_t : 32; // offset 0x32cUL
    std::uint32_t : 32; // offset 0x330UL
    std::uint32_t : 32; // offset 0x334UL
    std::uint32_t : 32; // offset 0x338UL
    std::uint32_t : 32; // offset 0x33cUL
    std::uint32_t : 32; // offset 0x340UL
    std::uint32_t : 32; // offset 0x344UL
    std::uint32_t : 32; // offset 0x348UL
    std::uint32_t : 32; // offset 0x34cUL
    std::uint32_t : 32; // offset 0x350UL
    std::uint32_t : 32; // offset 0x354UL
    std::uint32_t : 32; // offset 0x358UL
    std::uint32_t : 32; // offset 0x35cUL
    std::uint32_t : 32; // offset 0x360UL
    std::uint32_t : 32; // offset 0x364UL
    std::uint32_t : 32; // offset 0x368UL
    std::uint32_t : 32; // offset 0x36cUL
    std::uint32_t : 32; // offset 0x370UL
    std::uint32_t : 32; // offset 0x374UL
    std::uint32_t : 32; // offset 0x378UL
    std::uint32_t : 32; // offset 0x37cUL
    std::uint32_t : 32; // offset 0x380UL
    std::uint32_t : 32; // offset 0x384UL
    std::uint32_t : 32; // offset 0x388UL
    std::uint32_t : 32; // offset 0x38cUL
    std::uint32_t : 32; // offset 0x390UL
    std::uint32_t : 32; // offset 0x394UL
    std::uint32_t : 32; // offset 0x398UL
    std::uint32_t : 32; // offset 0x39cUL
    std::uint32_t : 32; // offset 0x3a0UL
    std::uint32_t : 32; // offset 0x3a4UL
    std::uint32_t : 32; // offset 0x3a8UL
    std::uint32_t : 32; // offset 0x3acUL
    std::uint32_t : 32; // offset 0x3b0UL
    std::uint32_t : 32; // offset 0x3b4UL
    std::uint32_t : 32; // offset 0x3b8UL
    std::uint32_t : 32; // offset 0x3bcUL
    std::uint32_t : 32; // offset 0x3c0UL
    std::uint32_t : 32; // offset 0x3c4UL
    std::uint32_t : 32; // offset 0x3c8UL
    std::uint32_t : 32; // offset 0x3ccUL
    std::uint32_t : 32; // offset 0x3d0UL
    std::uint32_t : 32; // offset 0x3d4UL
    std::uint32_t : 32; // offset 0x3d8UL
    std::uint32_t : 32; // offset 0x3dcUL
    std::uint32_t : 32; // offset 0x3e0UL
    std::uint32_t : 32; // offset 0x3e4UL
    std::uint32_t : 32; // offset 0x3e8UL
    std::uint32_t : 32; // offset 0x3ecUL
    std::uint32_t : 32; // offset 0x3f0UL
    std::uint32_t : 32; // offset 0x3f4UL
    std::uint32_t : 32; // offset 0x3f8UL
    std::uint32_t : 32; // offset 0x3fcUL
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<RandomNumberGenerator>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(RandomNumberGenerator, control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(RandomNumberGenerator, status) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(RandomNumberGenerator, dr) == 0x8UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(RandomNumberGenerator) == 0x400UL, "Must be this exact size");



/// The external volatile random_number_generator which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern RandomNumberGenerator volatile random_number_generator;
}  // namespace registers
}  // namespace stm32
#endif // STM32_REGISTERS_RANDOMNUMBERGENERATOR_HPP_