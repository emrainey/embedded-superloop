
#ifndef STM32_REGISTERS_FLASHCONTROL__HPP_
#define STM32_REGISTERS_FLASHCONTROL__HPP_

/// @file
/// Auto Generated Structure Definitions for FlashControl from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// FLASH (FLASH)
struct FlashControl final {
    /// Flash access control register (ACR)
    struct AccessControl final {
        /// Default Constructor
        AccessControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AccessControl(AccessControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AccessControl(AccessControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AccessControl(AccessControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AccessControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AccessControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AccessControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Latency (LATENCY)
            uint32_t latency                  : 3;    // bits 0:2
            /// (reserved)
            uint32_t                          : 5;    // bits 3:7
            /// Prefetch enable (PRFTEN)
            uint32_t prefetch_enable          : 1;    // bit 8
            /// Instruction cache enable (ICEN)
            uint32_t instruction_cache_enable : 1;    // bit 9
            /// Data cache enable (DCEN)
            uint32_t data_cache_enable        : 1;    // bit 10
            /// Instruction cache reset (ICRST)
            uint32_t icrst                    : 1;    // bit 11
            /// Data cache reset (DCRST)
            uint32_t dcrst                    : 1;    // bit 12
            /// (reserved)
            uint32_t                          : 19;    // bits 13:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AccessControl& operator=(AccessControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AccessControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AccessControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AccessControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AccessControl) == 4UL, "Must be this exact size");
    /// Flash key register (KEYR)
    struct Key final {
        /// Default Constructor
        Key()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Key(Key volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Key(Key const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Key(Key&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Key(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Key(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Key() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// FPEC key (KEY)
            uint32_t key : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Key& operator=(Key&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Key volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Key const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Key>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Key) == 4UL, "Must be this exact size");
    /// Flash option key register (OPTKEYR)
    struct OptionKey final {
        /// Default Constructor
        OptionKey()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OptionKey(OptionKey volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OptionKey(OptionKey const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OptionKey(OptionKey&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OptionKey(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OptionKey(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OptionKey() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Option byte key (OPTKEY)
            uint32_t optkey : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OptionKey& operator=(OptionKey&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OptionKey volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OptionKey const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OptionKey>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OptionKey) == 4UL, "Must be this exact size");
    /// Status register (SR)
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
            /// End of operation (EOP)
            uint32_t eop    : 1;    // bit 0
            /// Operation error (OPERR)
            uint32_t operr  : 1;    // bit 1
            /// (reserved)
            uint32_t        : 2;    // bits 2:3
            /// Write protection error (WRPERR)
            uint32_t wrperr : 1;    // bit 4
            /// Programming alignment error (PGAERR)
            uint32_t pgaerr : 1;    // bit 5
            /// Programming parallelism error (PGPERR)
            uint32_t pgperr : 1;    // bit 6
            /// Programming sequence error (PGSERR)
            uint32_t pgserr : 1;    // bit 7
            /// (reserved)
            uint32_t        : 8;    // bits 8:15
            /// Busy (BSY)
            uint32_t bsy    : 1;    // bit 16
            /// (reserved)
            uint32_t        : 15;    // bits 17:31
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
    /// Control register (CR)
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
            /// Programming (PG)
            uint32_t pg    : 1;    // bit 0
            /// Sector Erase (SER)
            uint32_t ser   : 1;    // bit 1
            /// Mass Erase (MER)
            uint32_t mer   : 1;    // bit 2
            /// Sector number (SNB)
            uint32_t snb   : 4;    // bits 3:6
            /// (reserved)
            uint32_t       : 1;    // bit 7
            /// Program size (PSIZE)
            uint32_t psize : 2;    // bits 8:9
            /// (reserved)
            uint32_t       : 6;    // bits 10:15
            /// Start (STRT)
            uint32_t strt  : 1;    // bit 16
            /// (reserved)
            uint32_t       : 7;    // bits 17:23
            /// End of operation interrupt enable (EOPIE)
            uint32_t eopie : 1;    // bit 24
            /// Error interrupt enable (ERRIE)
            uint32_t errie : 1;    // bit 25
            /// (reserved)
            uint32_t       : 5;    // bits 26:30
            /// Lock (LOCK)
            uint32_t lock  : 1;    // bit 31
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
    /// Flash option control register (OPTCR)
    struct OPTCR final {
        /// Default Constructor
        OPTCR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTCR(OPTCR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTCR(OPTCR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTCR(OPTCR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTCR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTCR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTCR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Option lock (OPTLOCK)
            uint32_t optlock    : 1;    // bit 0
            /// Option start (OPTSTRT)
            uint32_t optstrt    : 1;    // bit 1
            /// BOR reset Level (BOR_LEV)
            uint32_t bor_lev    : 2;    // bits 2:3
            /// (reserved)
            uint32_t            : 1;    // bit 4
            /// WDG_SW User option bytes (WDG_SW)
            uint32_t wdg_sw     : 1;    // bit 5
            /// nRST_STOP User option bytes (nRST_STOP)
            uint32_t nrst_stop  : 1;    // bit 6
            /// nRST_STDBY User option bytes (nRST_STDBY)
            uint32_t nrst_stdby : 1;    // bit 7
            /// Read protect (RDP)
            uint32_t rdp        : 8;    // bits 8:15
            /// Not write protect (nWRP)
            uint32_t nwrp       : 12;    // bits 16:27
            /// (reserved)
            uint32_t            : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTCR& operator=(OPTCR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTCR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTCR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTCR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTCR) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Flash access control register (ACR)
    AccessControl access_control;    // offset 0x0UL
    /// Flash key register (KEYR)
    Key key;    // offset 0x4UL
    /// Flash option key register (OPTKEYR)
    OptionKey option_key;    // offset 0x8UL
    /// Status register (SR)
    Status status;    // offset 0xcUL
    /// Control register (CR)
    Control control;    // offset 0x10UL
    /// Flash option control register (OPTCR)
    OPTCR optcr;      // offset 0x14UL
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
static_assert(std::is_standard_layout<FlashControl>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(FlashControl, access_control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, key) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, option_key) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, status) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, control) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optcr) == 0x14UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(FlashControl) == 0x400UL, "Must be this exact size");

/// The external volatile flash_control which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern FlashControl volatile flash_control;
}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_FLASHCONTROL__HPP_