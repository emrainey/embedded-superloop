
#ifndef STM32_REGISTERS_DEBUG__HPP_
#define STM32_REGISTERS_DEBUG__HPP_

/// @file
/// Auto Generated Structure Definitions for Debug from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>


namespace stm32 {
namespace registers {

/// Debug support (DBG)
struct Debug final {

/// IDCODE (DBGMCU_IDCODE)
struct DebugMcu_Identity final {

    /// Default Constructor
    DebugMcu_Identity() : whole{0u} {}
    /// Copy Constructor from volatile
    DebugMcu_Identity(DebugMcu_Identity volatile const& other) : whole{other.whole} {}
    /// Copy Construction from nonvolatile
    DebugMcu_Identity(DebugMcu_Identity const& other) : whole{other.whole} {}
    /// Move Constructor is deleted
    DebugMcu_Identity(DebugMcu_Identity&&) = delete;
    /// Parameterized Constructor for constant references
    explicit DebugMcu_Identity(uint32_t const& value) : whole{value} {}
    /// Parameterized Constructor for volatile references
    explicit DebugMcu_Identity(uint32_t volatile& value) : whole{value} {}
    /// Destructor is empty
    ~DebugMcu_Identity() = default;

    /// The internal bitfield for the register
    struct Fields final {
        /// DEV_ID (DEV_ID)
        uint32_t device_id : 12; // bits 0:11
        /// (reserved)
        uint32_t  : 4; // bits 12:15
        /// REV_ID (REV_ID)
        uint32_t revision_id : 16; // bits 16:31
    };
    //+=MEMORY======================================+
    union {
        Fields bits;
        uint32_t whole;
    };
    //+=MEMORY======================================+
    /// Move Assignment is deleted
    DebugMcu_Identity& operator=(DebugMcu_Identity&&) = delete;
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(DebugMcu_Identity volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(DebugMcu_Identity const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an uint32_t.
    inline explicit operator uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an uint32_t
    inline explicit operator uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<DebugMcu_Identity>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(DebugMcu_Identity) == 4UL, "Must be this exact size");
/// Control Register (DBGMCU_CR)
struct DebugMcu_Control final {

    /// Default Constructor
    DebugMcu_Control() : whole{0u} {}
    /// Copy Constructor from volatile
    DebugMcu_Control(DebugMcu_Control volatile const& other) : whole{other.whole} {}
    /// Copy Construction from nonvolatile
    DebugMcu_Control(DebugMcu_Control const& other) : whole{other.whole} {}
    /// Move Constructor is deleted
    DebugMcu_Control(DebugMcu_Control&&) = delete;
    /// Parameterized Constructor for constant references
    explicit DebugMcu_Control(uint32_t const& value) : whole{value} {}
    /// Parameterized Constructor for volatile references
    explicit DebugMcu_Control(uint32_t volatile& value) : whole{value} {}
    /// Destructor is empty
    ~DebugMcu_Control() = default;

    /// The internal bitfield for the register
    struct Fields final {
        /// DBG_SLEEP (DBG_SLEEP)
        uint32_t dbg_sleep : 1; // bit 0
        /// DBG_STOP (DBG_STOP)
        uint32_t dbg_stop : 1; // bit 1
        /// DBG_STANDBY (DBG_STANDBY)
        uint32_t dbg_standby : 1; // bit 2
        /// (reserved)
        uint32_t  : 2; // bits 3:4
        /// TRACE_IOEN (TRACE_IOEN)
        uint32_t trace_ioen : 1; // bit 5
        /// TRACE_MODE (TRACE_MODE)
        uint32_t trace_mode : 2; // bits 6:7
        /// (reserved)
        uint32_t  : 8; // bits 8:15
        /// DBG_I2C2_SMBUS_TIMEOUT (DBG_I2C2_SMBUS_TIMEOUT)
        uint32_t dbg_i2c2_smbus_timeout : 1; // bit 16
        /// DBG_TIM8_STOP (DBG_TIM8_STOP)
        uint32_t dbg_tim8_stop : 1; // bit 17
        /// DBG_TIM5_STOP (DBG_TIM5_STOP)
        uint32_t dbg_tim5_stop : 1; // bit 18
        /// DBG_TIM6_STOP (DBG_TIM6_STOP)
        uint32_t dbg_tim6_stop : 1; // bit 19
        /// DBG_TIM7_STOP (DBG_TIM7_STOP)
        uint32_t dbg_tim7_stop : 1; // bit 20
        /// (reserved)
        uint32_t  : 11; // bits 21:31
    };
    //+=MEMORY======================================+
    union {
        Fields bits;
        uint32_t whole;
    };
    //+=MEMORY======================================+
    /// Move Assignment is deleted
    DebugMcu_Control& operator=(DebugMcu_Control&&) = delete;
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(DebugMcu_Control volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(DebugMcu_Control const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an uint32_t.
    inline explicit operator uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an uint32_t
    inline explicit operator uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<DebugMcu_Control>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(DebugMcu_Control) == 4UL, "Must be this exact size");
/// Debug MCU APB1 Freeze registe (DBGMCU_APB1_FZ)
struct DebugMcu_APB1_Freeze final {

    /// Default Constructor
    DebugMcu_APB1_Freeze() : whole{0u} {}
    /// Copy Constructor from volatile
    DebugMcu_APB1_Freeze(DebugMcu_APB1_Freeze volatile const& other) : whole{other.whole} {}
    /// Copy Construction from nonvolatile
    DebugMcu_APB1_Freeze(DebugMcu_APB1_Freeze const& other) : whole{other.whole} {}
    /// Move Constructor is deleted
    DebugMcu_APB1_Freeze(DebugMcu_APB1_Freeze&&) = delete;
    /// Parameterized Constructor for constant references
    explicit DebugMcu_APB1_Freeze(uint32_t const& value) : whole{value} {}
    /// Parameterized Constructor for volatile references
    explicit DebugMcu_APB1_Freeze(uint32_t volatile& value) : whole{value} {}
    /// Destructor is empty
    ~DebugMcu_APB1_Freeze() = default;

    /// The internal bitfield for the register
    struct Fields final {
        /// DBG_TIM2_STOP (DBG_TIM2_STOP)
        uint32_t dbg_tim2_stop : 1; // bit 0
        /// DBG_TIM3 _STOP (DBG_TIM3_STOP)
        uint32_t dbg_tim3_stop : 1; // bit 1
        /// DBG_TIM4_STOP (DBG_TIM4_STOP)
        uint32_t dbg_tim4_stop : 1; // bit 2
        /// DBG_TIM5_STOP (DBG_TIM5_STOP)
        uint32_t dbg_tim5_stop : 1; // bit 3
        /// DBG_TIM6_STOP (DBG_TIM6_STOP)
        uint32_t dbg_tim6_stop : 1; // bit 4
        /// DBG_TIM7_STOP (DBG_TIM7_STOP)
        uint32_t dbg_tim7_stop : 1; // bit 5
        /// DBG_TIM12_STOP (DBG_TIM12_STOP)
        uint32_t dbg_tim12_stop : 1; // bit 6
        /// DBG_TIM13_STOP (DBG_TIM13_STOP)
        uint32_t dbg_tim13_stop : 1; // bit 7
        /// DBG_TIM14_STOP (DBG_TIM14_STOP)
        uint32_t dbg_tim14_stop : 1; // bit 8
        /// (reserved)
        uint32_t  : 2; // bits 9:10
        /// DBG_WWDG_STOP (DBG_WWDG_STOP)
        uint32_t dbg_wwdg_stop : 1; // bit 11
        /// DBG_IWDEG_STOP (DBG_IWDEG_STOP)
        uint32_t dbg_iwdeg_stop : 1; // bit 12
        /// (reserved)
        uint32_t  : 8; // bits 13:20
        /// DBG_J2C1_SMBUS_TIMEOUT (DBG_J2C1_SMBUS_TIMEOUT)
        uint32_t dbg_j2c1_smbus_timeout : 1; // bit 21
        /// DBG_J2C2_SMBUS_TIMEOUT (DBG_J2C2_SMBUS_TIMEOUT)
        uint32_t dbg_j2c2_smbus_timeout : 1; // bit 22
        /// DBG_J2C3SMBUS_TIMEOUT (DBG_J2C3SMBUS_TIMEOUT)
        uint32_t dbg_j2c3smbus_timeout : 1; // bit 23
        /// (reserved)
        uint32_t  : 1; // bit 24
        /// DBG_CAN1_STOP (DBG_CAN1_STOP)
        uint32_t dbg_can1_stop : 1; // bit 25
        /// DBG_CAN2_STOP (DBG_CAN2_STOP)
        uint32_t dbg_can2_stop : 1; // bit 26
        /// (reserved)
        uint32_t  : 5; // bits 27:31
    };
    //+=MEMORY======================================+
    union {
        Fields bits;
        uint32_t whole;
    };
    //+=MEMORY======================================+
    /// Move Assignment is deleted
    DebugMcu_APB1_Freeze& operator=(DebugMcu_APB1_Freeze&&) = delete;
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(DebugMcu_APB1_Freeze volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(DebugMcu_APB1_Freeze const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an uint32_t.
    inline explicit operator uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an uint32_t
    inline explicit operator uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<DebugMcu_APB1_Freeze>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(DebugMcu_APB1_Freeze) == 4UL, "Must be this exact size");
/// Debug MCU APB2 Freeze registe (DBGMCU_APB2_FZ)
struct DebugMcu_APB2_Freeze final {

    /// Default Constructor
    DebugMcu_APB2_Freeze() : whole{0u} {}
    /// Copy Constructor from volatile
    DebugMcu_APB2_Freeze(DebugMcu_APB2_Freeze volatile const& other) : whole{other.whole} {}
    /// Copy Construction from nonvolatile
    DebugMcu_APB2_Freeze(DebugMcu_APB2_Freeze const& other) : whole{other.whole} {}
    /// Move Constructor is deleted
    DebugMcu_APB2_Freeze(DebugMcu_APB2_Freeze&&) = delete;
    /// Parameterized Constructor for constant references
    explicit DebugMcu_APB2_Freeze(uint32_t const& value) : whole{value} {}
    /// Parameterized Constructor for volatile references
    explicit DebugMcu_APB2_Freeze(uint32_t volatile& value) : whole{value} {}
    /// Destructor is empty
    ~DebugMcu_APB2_Freeze() = default;

    /// The internal bitfield for the register
    struct Fields final {
        /// TIM1 counter stopped when core is halted (DBG_TIM1_STOP)
        uint32_t dbg_tim1_stop : 1; // bit 0
        /// TIM8 counter stopped when core is halted (DBG_TIM8_STOP)
        uint32_t dbg_tim8_stop : 1; // bit 1
        /// (reserved)
        uint32_t  : 14; // bits 2:15
        /// TIM9 counter stopped when core is halted (DBG_TIM9_STOP)
        uint32_t dbg_tim9_stop : 1; // bit 16
        /// TIM10 counter stopped when core is halted (DBG_TIM10_STOP)
        uint32_t dbg_tim10_stop : 1; // bit 17
        /// TIM11 counter stopped when core is halted (DBG_TIM11_STOP)
        uint32_t dbg_tim11_stop : 1; // bit 18
        /// (reserved)
        uint32_t  : 13; // bits 19:31
    };
    //+=MEMORY======================================+
    union {
        Fields bits;
        uint32_t whole;
    };
    //+=MEMORY======================================+
    /// Move Assignment is deleted
    DebugMcu_APB2_Freeze& operator=(DebugMcu_APB2_Freeze&&) = delete;
    /// Assignment from a volatile to a non volatile copy of the register.
    /// @note Does not return a reference
    inline void operator=(DebugMcu_APB2_Freeze volatile& other) {
        whole = other.whole;
    }
    /// Assignment from a non volatile to a volatile register
    /// @note Does not return a reference
    inline void operator=(DebugMcu_APB2_Freeze const& other) volatile {
        whole = other.whole;
    }
    /// Copy Assign a complete value from the base type uint32_t into a volatile version
    /// This allows you to assign the whole register to a literal value or a known constant of the same type.
    /// @note Does not return a reference
    inline void operator=(uint32_t const& value) volatile {
        whole = value;
    }
    /// Returns a copy of the register as an uint32_t.
    inline explicit operator uint32_t(void) const {
        return whole;
    }
    /// Returns a copy of the volatile register as an uint32_t
    inline explicit operator uint32_t(void) volatile {
        return whole;
    }
    /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
    static bool validate(void);
};
// Ensure the register is in standard layout format
static_assert(std::is_standard_layout<DebugMcu_APB2_Freeze>::value, "Must be standard layout");
// Ensure the sizeof the entire register is correct.
static_assert(sizeof(DebugMcu_APB2_Freeze) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// IDCODE (DBGMCU_IDCODE)
    DebugMcu_Identity dbgmcu_identity; // offset 0x0UL
    /// Control Register (DBGMCU_CR)
    DebugMcu_Control dbgmcu_control; // offset 0x4UL
    /// Debug MCU APB1 Freeze registe (DBGMCU_APB1_FZ)
    DebugMcu_APB1_Freeze dbgmcu_apb1_freeze; // offset 0x8UL
    /// Debug MCU APB2 Freeze registe (DBGMCU_APB2_FZ)
    DebugMcu_APB2_Freeze dbgmcu_apb2_freeze; // offset 0xcUL
    uint32_t : 32; // offset 0x10UL
    uint32_t : 32; // offset 0x14UL
    uint32_t : 32; // offset 0x18UL
    uint32_t : 32; // offset 0x1cUL
    uint32_t : 32; // offset 0x20UL
    uint32_t : 32; // offset 0x24UL
    uint32_t : 32; // offset 0x28UL
    uint32_t : 32; // offset 0x2cUL
    uint32_t : 32; // offset 0x30UL
    uint32_t : 32; // offset 0x34UL
    uint32_t : 32; // offset 0x38UL
    uint32_t : 32; // offset 0x3cUL
    uint32_t : 32; // offset 0x40UL
    uint32_t : 32; // offset 0x44UL
    uint32_t : 32; // offset 0x48UL
    uint32_t : 32; // offset 0x4cUL
    uint32_t : 32; // offset 0x50UL
    uint32_t : 32; // offset 0x54UL
    uint32_t : 32; // offset 0x58UL
    uint32_t : 32; // offset 0x5cUL
    uint32_t : 32; // offset 0x60UL
    uint32_t : 32; // offset 0x64UL
    uint32_t : 32; // offset 0x68UL
    uint32_t : 32; // offset 0x6cUL
    uint32_t : 32; // offset 0x70UL
    uint32_t : 32; // offset 0x74UL
    uint32_t : 32; // offset 0x78UL
    uint32_t : 32; // offset 0x7cUL
    uint32_t : 32; // offset 0x80UL
    uint32_t : 32; // offset 0x84UL
    uint32_t : 32; // offset 0x88UL
    uint32_t : 32; // offset 0x8cUL
    uint32_t : 32; // offset 0x90UL
    uint32_t : 32; // offset 0x94UL
    uint32_t : 32; // offset 0x98UL
    uint32_t : 32; // offset 0x9cUL
    uint32_t : 32; // offset 0xa0UL
    uint32_t : 32; // offset 0xa4UL
    uint32_t : 32; // offset 0xa8UL
    uint32_t : 32; // offset 0xacUL
    uint32_t : 32; // offset 0xb0UL
    uint32_t : 32; // offset 0xb4UL
    uint32_t : 32; // offset 0xb8UL
    uint32_t : 32; // offset 0xbcUL
    uint32_t : 32; // offset 0xc0UL
    uint32_t : 32; // offset 0xc4UL
    uint32_t : 32; // offset 0xc8UL
    uint32_t : 32; // offset 0xccUL
    uint32_t : 32; // offset 0xd0UL
    uint32_t : 32; // offset 0xd4UL
    uint32_t : 32; // offset 0xd8UL
    uint32_t : 32; // offset 0xdcUL
    uint32_t : 32; // offset 0xe0UL
    uint32_t : 32; // offset 0xe4UL
    uint32_t : 32; // offset 0xe8UL
    uint32_t : 32; // offset 0xecUL
    uint32_t : 32; // offset 0xf0UL
    uint32_t : 32; // offset 0xf4UL
    uint32_t : 32; // offset 0xf8UL
    uint32_t : 32; // offset 0xfcUL
    uint32_t : 32; // offset 0x100UL
    uint32_t : 32; // offset 0x104UL
    uint32_t : 32; // offset 0x108UL
    uint32_t : 32; // offset 0x10cUL
    uint32_t : 32; // offset 0x110UL
    uint32_t : 32; // offset 0x114UL
    uint32_t : 32; // offset 0x118UL
    uint32_t : 32; // offset 0x11cUL
    uint32_t : 32; // offset 0x120UL
    uint32_t : 32; // offset 0x124UL
    uint32_t : 32; // offset 0x128UL
    uint32_t : 32; // offset 0x12cUL
    uint32_t : 32; // offset 0x130UL
    uint32_t : 32; // offset 0x134UL
    uint32_t : 32; // offset 0x138UL
    uint32_t : 32; // offset 0x13cUL
    uint32_t : 32; // offset 0x140UL
    uint32_t : 32; // offset 0x144UL
    uint32_t : 32; // offset 0x148UL
    uint32_t : 32; // offset 0x14cUL
    uint32_t : 32; // offset 0x150UL
    uint32_t : 32; // offset 0x154UL
    uint32_t : 32; // offset 0x158UL
    uint32_t : 32; // offset 0x15cUL
    uint32_t : 32; // offset 0x160UL
    uint32_t : 32; // offset 0x164UL
    uint32_t : 32; // offset 0x168UL
    uint32_t : 32; // offset 0x16cUL
    uint32_t : 32; // offset 0x170UL
    uint32_t : 32; // offset 0x174UL
    uint32_t : 32; // offset 0x178UL
    uint32_t : 32; // offset 0x17cUL
    uint32_t : 32; // offset 0x180UL
    uint32_t : 32; // offset 0x184UL
    uint32_t : 32; // offset 0x188UL
    uint32_t : 32; // offset 0x18cUL
    uint32_t : 32; // offset 0x190UL
    uint32_t : 32; // offset 0x194UL
    uint32_t : 32; // offset 0x198UL
    uint32_t : 32; // offset 0x19cUL
    uint32_t : 32; // offset 0x1a0UL
    uint32_t : 32; // offset 0x1a4UL
    uint32_t : 32; // offset 0x1a8UL
    uint32_t : 32; // offset 0x1acUL
    uint32_t : 32; // offset 0x1b0UL
    uint32_t : 32; // offset 0x1b4UL
    uint32_t : 32; // offset 0x1b8UL
    uint32_t : 32; // offset 0x1bcUL
    uint32_t : 32; // offset 0x1c0UL
    uint32_t : 32; // offset 0x1c4UL
    uint32_t : 32; // offset 0x1c8UL
    uint32_t : 32; // offset 0x1ccUL
    uint32_t : 32; // offset 0x1d0UL
    uint32_t : 32; // offset 0x1d4UL
    uint32_t : 32; // offset 0x1d8UL
    uint32_t : 32; // offset 0x1dcUL
    uint32_t : 32; // offset 0x1e0UL
    uint32_t : 32; // offset 0x1e4UL
    uint32_t : 32; // offset 0x1e8UL
    uint32_t : 32; // offset 0x1ecUL
    uint32_t : 32; // offset 0x1f0UL
    uint32_t : 32; // offset 0x1f4UL
    uint32_t : 32; // offset 0x1f8UL
    uint32_t : 32; // offset 0x1fcUL
    uint32_t : 32; // offset 0x200UL
    uint32_t : 32; // offset 0x204UL
    uint32_t : 32; // offset 0x208UL
    uint32_t : 32; // offset 0x20cUL
    uint32_t : 32; // offset 0x210UL
    uint32_t : 32; // offset 0x214UL
    uint32_t : 32; // offset 0x218UL
    uint32_t : 32; // offset 0x21cUL
    uint32_t : 32; // offset 0x220UL
    uint32_t : 32; // offset 0x224UL
    uint32_t : 32; // offset 0x228UL
    uint32_t : 32; // offset 0x22cUL
    uint32_t : 32; // offset 0x230UL
    uint32_t : 32; // offset 0x234UL
    uint32_t : 32; // offset 0x238UL
    uint32_t : 32; // offset 0x23cUL
    uint32_t : 32; // offset 0x240UL
    uint32_t : 32; // offset 0x244UL
    uint32_t : 32; // offset 0x248UL
    uint32_t : 32; // offset 0x24cUL
    uint32_t : 32; // offset 0x250UL
    uint32_t : 32; // offset 0x254UL
    uint32_t : 32; // offset 0x258UL
    uint32_t : 32; // offset 0x25cUL
    uint32_t : 32; // offset 0x260UL
    uint32_t : 32; // offset 0x264UL
    uint32_t : 32; // offset 0x268UL
    uint32_t : 32; // offset 0x26cUL
    uint32_t : 32; // offset 0x270UL
    uint32_t : 32; // offset 0x274UL
    uint32_t : 32; // offset 0x278UL
    uint32_t : 32; // offset 0x27cUL
    uint32_t : 32; // offset 0x280UL
    uint32_t : 32; // offset 0x284UL
    uint32_t : 32; // offset 0x288UL
    uint32_t : 32; // offset 0x28cUL
    uint32_t : 32; // offset 0x290UL
    uint32_t : 32; // offset 0x294UL
    uint32_t : 32; // offset 0x298UL
    uint32_t : 32; // offset 0x29cUL
    uint32_t : 32; // offset 0x2a0UL
    uint32_t : 32; // offset 0x2a4UL
    uint32_t : 32; // offset 0x2a8UL
    uint32_t : 32; // offset 0x2acUL
    uint32_t : 32; // offset 0x2b0UL
    uint32_t : 32; // offset 0x2b4UL
    uint32_t : 32; // offset 0x2b8UL
    uint32_t : 32; // offset 0x2bcUL
    uint32_t : 32; // offset 0x2c0UL
    uint32_t : 32; // offset 0x2c4UL
    uint32_t : 32; // offset 0x2c8UL
    uint32_t : 32; // offset 0x2ccUL
    uint32_t : 32; // offset 0x2d0UL
    uint32_t : 32; // offset 0x2d4UL
    uint32_t : 32; // offset 0x2d8UL
    uint32_t : 32; // offset 0x2dcUL
    uint32_t : 32; // offset 0x2e0UL
    uint32_t : 32; // offset 0x2e4UL
    uint32_t : 32; // offset 0x2e8UL
    uint32_t : 32; // offset 0x2ecUL
    uint32_t : 32; // offset 0x2f0UL
    uint32_t : 32; // offset 0x2f4UL
    uint32_t : 32; // offset 0x2f8UL
    uint32_t : 32; // offset 0x2fcUL
    uint32_t : 32; // offset 0x300UL
    uint32_t : 32; // offset 0x304UL
    uint32_t : 32; // offset 0x308UL
    uint32_t : 32; // offset 0x30cUL
    uint32_t : 32; // offset 0x310UL
    uint32_t : 32; // offset 0x314UL
    uint32_t : 32; // offset 0x318UL
    uint32_t : 32; // offset 0x31cUL
    uint32_t : 32; // offset 0x320UL
    uint32_t : 32; // offset 0x324UL
    uint32_t : 32; // offset 0x328UL
    uint32_t : 32; // offset 0x32cUL
    uint32_t : 32; // offset 0x330UL
    uint32_t : 32; // offset 0x334UL
    uint32_t : 32; // offset 0x338UL
    uint32_t : 32; // offset 0x33cUL
    uint32_t : 32; // offset 0x340UL
    uint32_t : 32; // offset 0x344UL
    uint32_t : 32; // offset 0x348UL
    uint32_t : 32; // offset 0x34cUL
    uint32_t : 32; // offset 0x350UL
    uint32_t : 32; // offset 0x354UL
    uint32_t : 32; // offset 0x358UL
    uint32_t : 32; // offset 0x35cUL
    uint32_t : 32; // offset 0x360UL
    uint32_t : 32; // offset 0x364UL
    uint32_t : 32; // offset 0x368UL
    uint32_t : 32; // offset 0x36cUL
    uint32_t : 32; // offset 0x370UL
    uint32_t : 32; // offset 0x374UL
    uint32_t : 32; // offset 0x378UL
    uint32_t : 32; // offset 0x37cUL
    uint32_t : 32; // offset 0x380UL
    uint32_t : 32; // offset 0x384UL
    uint32_t : 32; // offset 0x388UL
    uint32_t : 32; // offset 0x38cUL
    uint32_t : 32; // offset 0x390UL
    uint32_t : 32; // offset 0x394UL
    uint32_t : 32; // offset 0x398UL
    uint32_t : 32; // offset 0x39cUL
    uint32_t : 32; // offset 0x3a0UL
    uint32_t : 32; // offset 0x3a4UL
    uint32_t : 32; // offset 0x3a8UL
    uint32_t : 32; // offset 0x3acUL
    uint32_t : 32; // offset 0x3b0UL
    uint32_t : 32; // offset 0x3b4UL
    uint32_t : 32; // offset 0x3b8UL
    uint32_t : 32; // offset 0x3bcUL
    uint32_t : 32; // offset 0x3c0UL
    uint32_t : 32; // offset 0x3c4UL
    uint32_t : 32; // offset 0x3c8UL
    uint32_t : 32; // offset 0x3ccUL
    uint32_t : 32; // offset 0x3d0UL
    uint32_t : 32; // offset 0x3d4UL
    uint32_t : 32; // offset 0x3d8UL
    uint32_t : 32; // offset 0x3dcUL
    uint32_t : 32; // offset 0x3e0UL
    uint32_t : 32; // offset 0x3e4UL
    uint32_t : 32; // offset 0x3e8UL
    uint32_t : 32; // offset 0x3ecUL
    uint32_t : 32; // offset 0x3f0UL
    uint32_t : 32; // offset 0x3f4UL
    uint32_t : 32; // offset 0x3f8UL
    uint32_t : 32; // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Debug>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Debug, dbgmcu_identity) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(Debug, dbgmcu_control) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(Debug, dbgmcu_apb1_freeze) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(Debug, dbgmcu_apb2_freeze) == 0xcUL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Debug) == 0x400UL, "Must be this exact size");



/// The external volatile debug which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern Debug volatile debug;
} // namespace registers
} // namespace stm32
#endif // STM32_REGISTERS_DEBUG__HPP_