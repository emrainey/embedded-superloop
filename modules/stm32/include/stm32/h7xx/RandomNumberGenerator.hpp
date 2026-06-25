
#ifndef STM32_H7XX_RANDOMNUMBERGENERATOR__HPP_
#define STM32_H7XX_RANDOMNUMBERGENERATOR__HPP_

/// @file
/// Auto Generated Structure Definitions for RandomNumberGenerator from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// RNG (RNG)
struct RandomNumberGenerator final {
    /// RNG control register (CR)
    struct Control final {
        /// Default Constructor
        Control()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control(Control volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control(Control const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control(Control&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                : 2;    // bits 0:1
            /// Random number generator enable (RNGEN)
            uint32_t random_number_generator_enable : 1;    // bit 2
            /// Interrupt enable (IE)
            uint32_t interrupt_enable               : 1;    // bit 3
            /// (reserved)
            uint32_t                                : 1;    // bit 4
            /// Clock error detection Note: The clock error detection can be used only when ck_rc48 or ck_pll1_q (ck_pll1_q = 48MHz) source is
            /// selected otherwise, CED bit must be equal to 1. The clock error detection cannot be enabled nor disabled on the fly when RNG
            /// peripheral is enabled, to enable or disable CED the RNG must be disabled. (CED)
            uint32_t clock_error_detection          : 1;    // bit 5
            /// (reserved)
            uint32_t                                : 26;    // bits 6:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control& operator=(Control&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Control>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control) == 4UL, "Must be this exact size");
    /// RNG status register (SR)
    struct Status final {
        /// Default Constructor
        Status()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Status(Status volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Status(Status const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Status(Status&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Status(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Status(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Status() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Data ready Note: If IE=1 in RNG_CR, an interrupt is generated when DRDY=1. It can rise when the peripheral is disabled. When the
            /// output buffer becomes empty (after reading RNG_DR), this bit returns to 0 until a new random value is generated. (DRDY)
            uint32_t data_ready                   : 1;    // bit 0
            /// Clock error current status Note: This bit is meaningless if CED (Clock error detection) bit in RNG_CR is equal to 1. (CECS)
            uint32_t clock_error_current_status   : 1;    // bit 1
            /// Seed error current status ** More than 64 consecutive bits at the same value (0 or 1) ** More than 32 consecutive alternances of 0 and
            /// 1 (0101010101...01) (SECS)
            uint32_t seed_error_current_status    : 1;    // bit 2
            /// (reserved)
            uint32_t                              : 2;    // bits 3:4
            /// Clock error interrupt status This bit is set at the same time as CECS. It is cleared by writing it to 0. An interrupt is pending if IE
            /// = 1 in the RNG_CR register. Note: This bit is meaningless if CED (Clock error detection) bit in RNG_CR is equal to 1. (CEIS)
            uint32_t clock_error_interrupt_status : 1;    // bit 5
            /// Seed error interrupt status This bit is set at the same time as SECS. It is cleared by writing it to 0. ** More than 64 consecutive
            /// bits at the same value (0 or 1) ** More than 32 consecutive alternances of 0 and 1 (0101010101...01) An interrupt is pending if IE = 1
            /// in the RNG_CR register. (SEIS)
            uint32_t seed_error_interrupt_status  : 1;    // bit 6
            /// (reserved)
            uint32_t                              : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Status& operator=(Status&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Status>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Status) == 4UL, "Must be this exact size");
    /// The RNG_DR register is a read-only register that delivers a 32-bit random value when read. The content of this register is valid when DRDY= 1,
    /// even if RNGEN=0. (DR)
    struct Data final {
        /// Default Constructor
        Data()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Data(Data volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Data(Data const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Data(Data&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Data(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Data(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Data() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Random data 32-bit random data which are valid when DRDY=1. (RNDATA)
            uint32_t random_number_data : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Data& operator=(Data&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Data volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Data const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Data>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Data) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// RNG control register (CR)
    Control control;    // offset 0x0UL
    /// RNG status register (SR)
    Status status;    // offset 0x4UL
    /// The RNG_DR register is a read-only register that delivers a 32-bit random value when read. The content of this register is valid when DRDY= 1,
    /// even if RNGEN=0. (DR)
    Data data;        // offset 0x8UL
    uint32_t : 32;    // offset 0xcUL
    uint32_t : 32;    // offset 0x10UL
    uint32_t : 32;    // offset 0x14UL
    uint32_t : 32;    // offset 0x18UL
    uint32_t : 32;    // offset 0x1cUL
    uint32_t : 32;    // offset 0x20UL
    uint32_t : 32;    // offset 0x24UL
    uint32_t : 32;    // offset 0x28UL
    uint32_t : 32;    // offset 0x2cUL
    uint32_t : 32;    // offset 0x30UL
    uint32_t : 32;    // offset 0x34UL
    uint32_t : 32;    // offset 0x38UL
    uint32_t : 32;    // offset 0x3cUL
    uint32_t : 32;    // offset 0x40UL
    uint32_t : 32;    // offset 0x44UL
    uint32_t : 32;    // offset 0x48UL
    uint32_t : 32;    // offset 0x4cUL
    uint32_t : 32;    // offset 0x50UL
    uint32_t : 32;    // offset 0x54UL
    uint32_t : 32;    // offset 0x58UL
    uint32_t : 32;    // offset 0x5cUL
    uint32_t : 32;    // offset 0x60UL
    uint32_t : 32;    // offset 0x64UL
    uint32_t : 32;    // offset 0x68UL
    uint32_t : 32;    // offset 0x6cUL
    uint32_t : 32;    // offset 0x70UL
    uint32_t : 32;    // offset 0x74UL
    uint32_t : 32;    // offset 0x78UL
    uint32_t : 32;    // offset 0x7cUL
    uint32_t : 32;    // offset 0x80UL
    uint32_t : 32;    // offset 0x84UL
    uint32_t : 32;    // offset 0x88UL
    uint32_t : 32;    // offset 0x8cUL
    uint32_t : 32;    // offset 0x90UL
    uint32_t : 32;    // offset 0x94UL
    uint32_t : 32;    // offset 0x98UL
    uint32_t : 32;    // offset 0x9cUL
    uint32_t : 32;    // offset 0xa0UL
    uint32_t : 32;    // offset 0xa4UL
    uint32_t : 32;    // offset 0xa8UL
    uint32_t : 32;    // offset 0xacUL
    uint32_t : 32;    // offset 0xb0UL
    uint32_t : 32;    // offset 0xb4UL
    uint32_t : 32;    // offset 0xb8UL
    uint32_t : 32;    // offset 0xbcUL
    uint32_t : 32;    // offset 0xc0UL
    uint32_t : 32;    // offset 0xc4UL
    uint32_t : 32;    // offset 0xc8UL
    uint32_t : 32;    // offset 0xccUL
    uint32_t : 32;    // offset 0xd0UL
    uint32_t : 32;    // offset 0xd4UL
    uint32_t : 32;    // offset 0xd8UL
    uint32_t : 32;    // offset 0xdcUL
    uint32_t : 32;    // offset 0xe0UL
    uint32_t : 32;    // offset 0xe4UL
    uint32_t : 32;    // offset 0xe8UL
    uint32_t : 32;    // offset 0xecUL
    uint32_t : 32;    // offset 0xf0UL
    uint32_t : 32;    // offset 0xf4UL
    uint32_t : 32;    // offset 0xf8UL
    uint32_t : 32;    // offset 0xfcUL
    uint32_t : 32;    // offset 0x100UL
    uint32_t : 32;    // offset 0x104UL
    uint32_t : 32;    // offset 0x108UL
    uint32_t : 32;    // offset 0x10cUL
    uint32_t : 32;    // offset 0x110UL
    uint32_t : 32;    // offset 0x114UL
    uint32_t : 32;    // offset 0x118UL
    uint32_t : 32;    // offset 0x11cUL
    uint32_t : 32;    // offset 0x120UL
    uint32_t : 32;    // offset 0x124UL
    uint32_t : 32;    // offset 0x128UL
    uint32_t : 32;    // offset 0x12cUL
    uint32_t : 32;    // offset 0x130UL
    uint32_t : 32;    // offset 0x134UL
    uint32_t : 32;    // offset 0x138UL
    uint32_t : 32;    // offset 0x13cUL
    uint32_t : 32;    // offset 0x140UL
    uint32_t : 32;    // offset 0x144UL
    uint32_t : 32;    // offset 0x148UL
    uint32_t : 32;    // offset 0x14cUL
    uint32_t : 32;    // offset 0x150UL
    uint32_t : 32;    // offset 0x154UL
    uint32_t : 32;    // offset 0x158UL
    uint32_t : 32;    // offset 0x15cUL
    uint32_t : 32;    // offset 0x160UL
    uint32_t : 32;    // offset 0x164UL
    uint32_t : 32;    // offset 0x168UL
    uint32_t : 32;    // offset 0x16cUL
    uint32_t : 32;    // offset 0x170UL
    uint32_t : 32;    // offset 0x174UL
    uint32_t : 32;    // offset 0x178UL
    uint32_t : 32;    // offset 0x17cUL
    uint32_t : 32;    // offset 0x180UL
    uint32_t : 32;    // offset 0x184UL
    uint32_t : 32;    // offset 0x188UL
    uint32_t : 32;    // offset 0x18cUL
    uint32_t : 32;    // offset 0x190UL
    uint32_t : 32;    // offset 0x194UL
    uint32_t : 32;    // offset 0x198UL
    uint32_t : 32;    // offset 0x19cUL
    uint32_t : 32;    // offset 0x1a0UL
    uint32_t : 32;    // offset 0x1a4UL
    uint32_t : 32;    // offset 0x1a8UL
    uint32_t : 32;    // offset 0x1acUL
    uint32_t : 32;    // offset 0x1b0UL
    uint32_t : 32;    // offset 0x1b4UL
    uint32_t : 32;    // offset 0x1b8UL
    uint32_t : 32;    // offset 0x1bcUL
    uint32_t : 32;    // offset 0x1c0UL
    uint32_t : 32;    // offset 0x1c4UL
    uint32_t : 32;    // offset 0x1c8UL
    uint32_t : 32;    // offset 0x1ccUL
    uint32_t : 32;    // offset 0x1d0UL
    uint32_t : 32;    // offset 0x1d4UL
    uint32_t : 32;    // offset 0x1d8UL
    uint32_t : 32;    // offset 0x1dcUL
    uint32_t : 32;    // offset 0x1e0UL
    uint32_t : 32;    // offset 0x1e4UL
    uint32_t : 32;    // offset 0x1e8UL
    uint32_t : 32;    // offset 0x1ecUL
    uint32_t : 32;    // offset 0x1f0UL
    uint32_t : 32;    // offset 0x1f4UL
    uint32_t : 32;    // offset 0x1f8UL
    uint32_t : 32;    // offset 0x1fcUL
    uint32_t : 32;    // offset 0x200UL
    uint32_t : 32;    // offset 0x204UL
    uint32_t : 32;    // offset 0x208UL
    uint32_t : 32;    // offset 0x20cUL
    uint32_t : 32;    // offset 0x210UL
    uint32_t : 32;    // offset 0x214UL
    uint32_t : 32;    // offset 0x218UL
    uint32_t : 32;    // offset 0x21cUL
    uint32_t : 32;    // offset 0x220UL
    uint32_t : 32;    // offset 0x224UL
    uint32_t : 32;    // offset 0x228UL
    uint32_t : 32;    // offset 0x22cUL
    uint32_t : 32;    // offset 0x230UL
    uint32_t : 32;    // offset 0x234UL
    uint32_t : 32;    // offset 0x238UL
    uint32_t : 32;    // offset 0x23cUL
    uint32_t : 32;    // offset 0x240UL
    uint32_t : 32;    // offset 0x244UL
    uint32_t : 32;    // offset 0x248UL
    uint32_t : 32;    // offset 0x24cUL
    uint32_t : 32;    // offset 0x250UL
    uint32_t : 32;    // offset 0x254UL
    uint32_t : 32;    // offset 0x258UL
    uint32_t : 32;    // offset 0x25cUL
    uint32_t : 32;    // offset 0x260UL
    uint32_t : 32;    // offset 0x264UL
    uint32_t : 32;    // offset 0x268UL
    uint32_t : 32;    // offset 0x26cUL
    uint32_t : 32;    // offset 0x270UL
    uint32_t : 32;    // offset 0x274UL
    uint32_t : 32;    // offset 0x278UL
    uint32_t : 32;    // offset 0x27cUL
    uint32_t : 32;    // offset 0x280UL
    uint32_t : 32;    // offset 0x284UL
    uint32_t : 32;    // offset 0x288UL
    uint32_t : 32;    // offset 0x28cUL
    uint32_t : 32;    // offset 0x290UL
    uint32_t : 32;    // offset 0x294UL
    uint32_t : 32;    // offset 0x298UL
    uint32_t : 32;    // offset 0x29cUL
    uint32_t : 32;    // offset 0x2a0UL
    uint32_t : 32;    // offset 0x2a4UL
    uint32_t : 32;    // offset 0x2a8UL
    uint32_t : 32;    // offset 0x2acUL
    uint32_t : 32;    // offset 0x2b0UL
    uint32_t : 32;    // offset 0x2b4UL
    uint32_t : 32;    // offset 0x2b8UL
    uint32_t : 32;    // offset 0x2bcUL
    uint32_t : 32;    // offset 0x2c0UL
    uint32_t : 32;    // offset 0x2c4UL
    uint32_t : 32;    // offset 0x2c8UL
    uint32_t : 32;    // offset 0x2ccUL
    uint32_t : 32;    // offset 0x2d0UL
    uint32_t : 32;    // offset 0x2d4UL
    uint32_t : 32;    // offset 0x2d8UL
    uint32_t : 32;    // offset 0x2dcUL
    uint32_t : 32;    // offset 0x2e0UL
    uint32_t : 32;    // offset 0x2e4UL
    uint32_t : 32;    // offset 0x2e8UL
    uint32_t : 32;    // offset 0x2ecUL
    uint32_t : 32;    // offset 0x2f0UL
    uint32_t : 32;    // offset 0x2f4UL
    uint32_t : 32;    // offset 0x2f8UL
    uint32_t : 32;    // offset 0x2fcUL
    uint32_t : 32;    // offset 0x300UL
    uint32_t : 32;    // offset 0x304UL
    uint32_t : 32;    // offset 0x308UL
    uint32_t : 32;    // offset 0x30cUL
    uint32_t : 32;    // offset 0x310UL
    uint32_t : 32;    // offset 0x314UL
    uint32_t : 32;    // offset 0x318UL
    uint32_t : 32;    // offset 0x31cUL
    uint32_t : 32;    // offset 0x320UL
    uint32_t : 32;    // offset 0x324UL
    uint32_t : 32;    // offset 0x328UL
    uint32_t : 32;    // offset 0x32cUL
    uint32_t : 32;    // offset 0x330UL
    uint32_t : 32;    // offset 0x334UL
    uint32_t : 32;    // offset 0x338UL
    uint32_t : 32;    // offset 0x33cUL
    uint32_t : 32;    // offset 0x340UL
    uint32_t : 32;    // offset 0x344UL
    uint32_t : 32;    // offset 0x348UL
    uint32_t : 32;    // offset 0x34cUL
    uint32_t : 32;    // offset 0x350UL
    uint32_t : 32;    // offset 0x354UL
    uint32_t : 32;    // offset 0x358UL
    uint32_t : 32;    // offset 0x35cUL
    uint32_t : 32;    // offset 0x360UL
    uint32_t : 32;    // offset 0x364UL
    uint32_t : 32;    // offset 0x368UL
    uint32_t : 32;    // offset 0x36cUL
    uint32_t : 32;    // offset 0x370UL
    uint32_t : 32;    // offset 0x374UL
    uint32_t : 32;    // offset 0x378UL
    uint32_t : 32;    // offset 0x37cUL
    uint32_t : 32;    // offset 0x380UL
    uint32_t : 32;    // offset 0x384UL
    uint32_t : 32;    // offset 0x388UL
    uint32_t : 32;    // offset 0x38cUL
    uint32_t : 32;    // offset 0x390UL
    uint32_t : 32;    // offset 0x394UL
    uint32_t : 32;    // offset 0x398UL
    uint32_t : 32;    // offset 0x39cUL
    uint32_t : 32;    // offset 0x3a0UL
    uint32_t : 32;    // offset 0x3a4UL
    uint32_t : 32;    // offset 0x3a8UL
    uint32_t : 32;    // offset 0x3acUL
    uint32_t : 32;    // offset 0x3b0UL
    uint32_t : 32;    // offset 0x3b4UL
    uint32_t : 32;    // offset 0x3b8UL
    uint32_t : 32;    // offset 0x3bcUL
    uint32_t : 32;    // offset 0x3c0UL
    uint32_t : 32;    // offset 0x3c4UL
    uint32_t : 32;    // offset 0x3c8UL
    uint32_t : 32;    // offset 0x3ccUL
    uint32_t : 32;    // offset 0x3d0UL
    uint32_t : 32;    // offset 0x3d4UL
    uint32_t : 32;    // offset 0x3d8UL
    uint32_t : 32;    // offset 0x3dcUL
    uint32_t : 32;    // offset 0x3e0UL
    uint32_t : 32;    // offset 0x3e4UL
    uint32_t : 32;    // offset 0x3e8UL
    uint32_t : 32;    // offset 0x3ecUL
    uint32_t : 32;    // offset 0x3f0UL
    uint32_t : 32;    // offset 0x3f4UL
    uint32_t : 32;    // offset 0x3f8UL
    uint32_t : 32;    // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<RandomNumberGenerator>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(RandomNumberGenerator, control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(RandomNumberGenerator, status) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(RandomNumberGenerator, data) == 0x8UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(RandomNumberGenerator) == 0x400UL, "Must be this exact size");

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_RANDOMNUMBERGENERATOR__HPP_
