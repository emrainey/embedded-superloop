
#ifndef STM32_H7XX_FLASHCONTROL__HPP_
#define STM32_H7XX_FLASHCONTROL__HPP_

/// @file
/// Auto Generated Structure Definitions for FlashControl from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Flash (FLASH)
struct FlashControl final {
    /// Access control register (ACR)
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
            /// Read latency (LATENCY)
            uint32_t latency    : 4;    // bits 0:3
            /// Flash signal delay (WRHIGHFREQ)
            uint32_t wrhighfreq : 2;    // bits 4:5
            /// (reserved)
            uint32_t            : 26;    // bits 6:31
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
    /// FLASH key register for bank 1 (KEYR1)
    struct KeyBank1 final {
        /// Default Constructor
        KeyBank1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        KeyBank1(KeyBank1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        KeyBank1(KeyBank1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        KeyBank1(KeyBank1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit KeyBank1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit KeyBank1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~KeyBank1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 access configuration unlock key (KEY1R)
            uint32_t key1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        KeyBank1& operator=(KeyBank1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(KeyBank1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(KeyBank1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<KeyBank1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(KeyBank1) == 4UL, "Must be this exact size");
    /// FLASH option key register (OPTKEYR)
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
            /// Unlock key option bytes (OPTKEYR)
            uint32_t option_key : 32;    // bits 0:31
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
    /// FLASH control register for bank 1 (CR1)
    struct Control1 final {
        /// Default Constructor
        Control1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control1(Control1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control1(Control1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control1(Control1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 configuration lock bit (LOCK1)
            uint32_t lock1       : 1;    // bit 0
            /// Bank 1 program enable bit (PG1)
            uint32_t pg1         : 1;    // bit 1
            /// Bank 1 sector erase request (SER1)
            uint32_t ser1        : 1;    // bit 2
            /// Bank 1 erase request (BER1)
            uint32_t ber1        : 1;    // bit 3
            /// Bank 1 program size (PSIZE1)
            uint32_t psize1      : 2;    // bits 4:5
            /// Bank 1 write forcing control bit (FW1)
            uint32_t fw1         : 1;    // bit 6
            /// Bank 1 bank or sector erase start control bit (START1)
            uint32_t start1      : 1;    // bit 7
            /// Bank 1 sector erase selection number (SNB1)
            uint32_t snb1        : 3;    // bits 8:10
            /// (reserved)
            uint32_t             : 4;    // bits 11:14
            /// Bank 1 CRC control bit (CRC_EN)
            uint32_t crc_enable  : 1;    // bit 15
            /// Bank 1 end-of-program interrupt control bit (EOPIE1)
            uint32_t eopie1      : 1;    // bit 16
            /// Bank 1 write protection error interrupt enable bit (WRPERRIE1)
            uint32_t wrperrie1   : 1;    // bit 17
            /// Bank 1 programming sequence error interrupt enable bit (PGSERRIE1)
            uint32_t pgserrie1   : 1;    // bit 18
            /// Bank 1 strobe error interrupt enable bit (STRBERRIE1)
            uint32_t strberrie1  : 1;    // bit 19
            /// (reserved)
            uint32_t             : 1;    // bit 20
            /// Bank 1 inconsistency error interrupt enable bit (INCERRIE1)
            uint32_t incerrie1   : 1;    // bit 21
            /// Bank 1 write/erase error interrupt enable bit (OPERRIE1)
            uint32_t operrie1    : 1;    // bit 22
            /// Bank 1 read protection error interrupt enable bit (RDPERRIE1)
            uint32_t rdperrie1   : 1;    // bit 23
            /// Bank 1 secure error interrupt enable bit (RDSERRIE1)
            uint32_t rdserrie1   : 1;    // bit 24
            /// Bank 1 ECC single correction error interrupt enable bit (SNECCERR1)
            uint32_t sneccerr1   : 1;    // bit 25
            /// Bank 1 ECC double detection error interrupt enable bit (DBECCERRIE1)
            uint32_t dbeccerrie1 : 1;    // bit 26
            /// Bank 1 end of CRC calculation interrupt enable bit (CRCENDIE1)
            uint32_t crcendie1   : 1;    // bit 27
            /// Bank 1 CRC read error interrupt enable bit When CRCRDERRIE1 bit is set to 1, an interrupt is generated when a protected area (PCROP or
            /// secure-only) has been detected during the last CRC computation on bank 1. CRCRDERRIE1 can be programmed only when LOCK1 is cleared to
            /// 0. (CRCRDERRIE1)
            uint32_t crcrderrie1 : 1;    // bit 28
            /// (reserved)
            uint32_t             : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control1& operator=(Control1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control1) == 4UL, "Must be this exact size");
    /// FLASH status register for bank 1 (SR1)
    struct Status1 final {
        /// Default Constructor
        Status1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Status1(Status1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Status1(Status1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Status1(Status1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Status1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Status1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Status1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 ongoing program flag (BSY1)
            uint32_t bsy1      : 1;    // bit 0
            /// Bank 1 write buffer not empty flag (WBNE1)
            uint32_t wbne1     : 1;    // bit 1
            /// Bank 1 wait queue flag (QW1)
            uint32_t qw1       : 1;    // bit 2
            /// Bank 1 CRC busy flag (CRC_BUSY1)
            uint32_t crc_busy1 : 1;    // bit 3
            /// (reserved)
            uint32_t           : 12;    // bits 4:15
            /// Bank 1 end-of-program flag (EOP1)
            uint32_t eop1      : 1;    // bit 16
            /// Bank 1 write protection error flag (WRPERR1)
            uint32_t wrperr1   : 1;    // bit 17
            /// Bank 1 programming sequence error flag (PGSERR1)
            uint32_t pgserr1   : 1;    // bit 18
            /// Bank 1 strobe error flag (STRBERR1)
            uint32_t strberr1  : 1;    // bit 19
            /// (reserved)
            uint32_t           : 1;    // bit 20
            /// Bank 1 inconsistency error flag (INCERR1)
            uint32_t incerr1   : 1;    // bit 21
            /// Bank 1 write/erase error flag (OPERR1)
            uint32_t operr1    : 1;    // bit 22
            /// Bank 1 read protection error flag (RDPERR1)
            uint32_t rdperr1   : 1;    // bit 23
            /// Bank 1 secure error flag (RDSERR1)
            uint32_t rdserr1   : 1;    // bit 24
            /// Bank 1 single correction error flag (SNECCERR)
            uint32_t sneccerr  : 1;    // bit 25
            /// Bank 1 ECC double detection error flag (DBECCERR1)
            uint32_t dbeccerr1 : 1;    // bit 26
            /// Bank 1 CRC-complete flag (CRCEND1)
            uint32_t crcend1   : 1;    // bit 27
            /// Bank 1 CRC read error flag CRCRDERR1 flag is raised when a word is found read protected during a CRC operation on bank 1. An interrupt
            /// is generated if CRCRDIE1 and CRCEND1 are set to 1. Writing 1 to CLR_CRCRDERR1 bit in FLASH_CCR1 register clears CRCRDERR1. Note: This
            /// flag is valid only when CRCEND1 bit is set to 1 (CRCRDERR1)
            uint32_t crcrderr1 : 1;    // bit 28
            /// (reserved)
            uint32_t           : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Status1& operator=(Status1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Status1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Status1) == 4UL, "Must be this exact size");
    /// FLASH clear control register for bank 1 (CCR1)
    struct CaptureCompare1 final {
        /// Default Constructor
        CaptureCompare1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare1(CaptureCompare1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare1(CaptureCompare1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare1(CaptureCompare1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 16;    // bits 0:15
            /// Bank 1 EOP1 flag clear bit (CLR_EOP1)
            uint32_t clr_eop1      : 1;    // bit 16
            /// Bank 1 WRPERR1 flag clear bit (CLR_WRPERR1)
            uint32_t clr_wrperr1   : 1;    // bit 17
            /// Bank 1 PGSERR1 flag clear bi (CLR_PGSERR1)
            uint32_t clr_pgserr1   : 1;    // bit 18
            /// Bank 1 STRBERR1 flag clear bit (CLR_STRBERR1)
            uint32_t clr_strberr1  : 1;    // bit 19
            /// (reserved)
            uint32_t               : 1;    // bit 20
            /// Bank 1 INCERR1 flag clear bit (CLR_INCERR1)
            uint32_t clr_incerr1   : 1;    // bit 21
            /// Bank 1 OPERR1 flag clear bit (CLR_OPERR1)
            uint32_t clr_operr1    : 1;    // bit 22
            /// Bank 1 RDPERR1 flag clear bit (CLR_RDPERR1)
            uint32_t clr_rdperr1   : 1;    // bit 23
            /// Bank 1 RDSERR1 flag clear bit (CLR_RDSERR1)
            uint32_t clr_rdserr1   : 1;    // bit 24
            /// Bank 1 SNECCERR1 flag clear bit (CLR_SNECCERR1)
            uint32_t clr_sneccerr1 : 1;    // bit 25
            /// Bank 1 DBECCERR1 flag clear bit (CLR_DBECCERR1)
            uint32_t clr_dbeccerr1 : 1;    // bit 26
            /// Bank 1 CRCEND1 flag clear bit (CLR_CRCEND1)
            uint32_t clr_crcend1   : 1;    // bit 27
            /// Bank 1 CRCRDERR1 flag clear bit Setting this bit to 1 resets to 0 CRCRDERR1 flag in FLASH_SR1 register. (CLR_CRCRDERR1)
            uint32_t clr_crcrderr1 : 1;    // bit 28
            /// (reserved)
            uint32_t               : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare1& operator=(CaptureCompare1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CaptureCompare1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare1) == 4UL, "Must be this exact size");
    /// FLASH option control register (OPTCR)
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
            /// FLASH_OPTCR lock option configuration bit (OPTLOCK)
            uint32_t optlock        : 1;    // bit 0
            /// Option byte start change option configuration bit (OPTSTART)
            uint32_t optstart       : 1;    // bit 1
            /// (reserved)
            uint32_t                : 2;    // bits 2:3
            /// Flash mass erase enable bit (MER)
            uint32_t memory_erase   : 1;    // bit 4
            /// (reserved)
            uint32_t                : 25;    // bits 5:29
            /// Option byte change error interrupt enable bit (OPTCHANGEERRIE)
            uint32_t optchangeerrie : 1;    // bit 30
            /// Bank swapping configuration bit (SWAP_BANK)
            uint32_t swap_bank      : 1;    // bit 31
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
    /// FLASH option status register (OPTSR_CUR)
    struct OPTSR_CUR final {
        /// Default Constructor
        OPTSR_CUR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTSR_CUR(OPTSR_CUR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTSR_CUR(OPTSR_CUR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTSR_CUR(OPTSR_CUR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTSR_CUR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTSR_CUR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTSR_CUR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Option byte change ongoing flag (OPT_BUSY)
            uint32_t opt_busy        : 1;    // bit 0
            /// (reserved)
            uint32_t                 : 1;    // bit 1
            /// Brownout level option status bit (BOR_LEV)
            uint32_t bor_lev         : 2;    // bits 2:3
            /// IWDG1 control option status bit (IWDG1_SW)
            uint32_t iwdg1_sw        : 1;    // bit 4
            /// (reserved)
            uint32_t                 : 1;    // bit 5
            /// D1 DStop entry reset option status bit (NRST_STOP_D1)
            uint32_t nrst_stop_d1    : 1;    // bit 6
            /// D1 DStandby entry reset option status bit (NRST_STBY_D1)
            uint32_t nrst_standby_d1 : 1;    // bit 7
            /// Readout protection level option status byte (RDP)
            uint32_t rdp             : 8;    // bits 8:15
            /// (reserved)
            uint32_t                 : 1;    // bit 16
            /// IWDG Stop mode freeze option status bit (IWDG_FZ_STOP)
            uint32_t iwdg_fz_stop    : 1;    // bit 17
            /// IWDG Standby mode freeze option status bit (IWDG_FZ_SDBY)
            uint32_t iwdg_fz_sdby    : 1;    // bit 18
            /// DTCM RAM size option status (ST_RAM_SIZE)
            uint32_t st_ram_size     : 2;    // bits 19:20
            /// Security enable option status bit (SECURITY)
            uint32_t security        : 1;    // bit 21
            /// (reserved)
            uint32_t                 : 7;    // bits 22:28
            /// I/O high-speed at low-voltage status bit (PRODUCT_BELOW_25V) (IO_HSLV)
            uint32_t io_hslv         : 1;    // bit 29
            /// Option byte change error flag (OPTCHANGEERR)
            uint32_t optchangeerr    : 1;    // bit 30
            /// Bank swapping option status bit (SWAP_BANK_OPT)
            uint32_t swap_bank_opt   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTSR_CUR& operator=(OPTSR_CUR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTSR_CUR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTSR_CUR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTSR_CUR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTSR_CUR) == 4UL, "Must be this exact size");
    /// FLASH option status register (OPTSR_PRG)
    struct OPTSR_PRG final {
        /// Default Constructor
        OPTSR_PRG()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTSR_PRG(OPTSR_PRG volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTSR_PRG(OPTSR_PRG const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTSR_PRG(OPTSR_PRG&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTSR_PRG(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTSR_PRG(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTSR_PRG() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                 : 2;    // bits 0:1
            /// BOR reset level option configuration bits (BOR_LEV)
            uint32_t bor_lev         : 2;    // bits 2:3
            /// IWDG1 option configuration bit (IWDG1_SW)
            uint32_t iwdg1_sw        : 1;    // bit 4
            /// (reserved)
            uint32_t                 : 1;    // bit 5
            /// Option byte erase after D1 DStop option configuration bit (NRST_STOP_D1)
            uint32_t nrst_stop_d1    : 1;    // bit 6
            /// Option byte erase after D1 DStandby option configuration bit (NRST_STBY_D1)
            uint32_t nrst_standby_d1 : 1;    // bit 7
            /// Readout protection level option configuration byte (RDP)
            uint32_t rdp             : 8;    // bits 8:15
            /// (reserved)
            uint32_t                 : 1;    // bit 16
            /// IWDG Stop mode freeze option configuration bit (IWDG_FZ_STOP)
            uint32_t iwdg_fz_stop    : 1;    // bit 17
            /// IWDG Standby mode freeze option configuration bit (IWDG_FZ_SDBY)
            uint32_t iwdg_fz_sdby    : 1;    // bit 18
            /// DTCM size select option configuration bits (ST_RAM_SIZE)
            uint32_t st_ram_size     : 2;    // bits 19:20
            /// Security option configuration bit (SECURITY)
            uint32_t security        : 1;    // bit 21
            /// (reserved)
            uint32_t                 : 7;    // bits 22:28
            /// I/O high-speed at low-voltage (PRODUCT_BELOW_25V) (IO_HSLV)
            uint32_t io_hslv         : 1;    // bit 29
            /// (reserved)
            uint32_t                 : 1;    // bit 30
            /// Bank swapping option configuration bit (SWAP_BANK_OPT)
            uint32_t swap_bank_opt   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTSR_PRG& operator=(OPTSR_PRG&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTSR_PRG volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTSR_PRG const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTSR_PRG>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTSR_PRG) == 4UL, "Must be this exact size");
    /// FLASH option clear control register (OPTCCR)
    struct OPTCCR final {
        /// Default Constructor
        OPTCCR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTCCR(OPTCCR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTCCR(OPTCCR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTCCR(OPTCCR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTCCR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTCCR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTCCR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                  : 30;    // bits 0:29
            /// OPTCHANGEERR reset bit (CLR_OPTCHANGEERR)
            uint32_t clr_optchangeerr : 1;    // bit 30
            /// (reserved)
            uint32_t                  : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTCCR& operator=(OPTCCR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTCCR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTCCR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTCCR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTCCR) == 4UL, "Must be this exact size");
    /// FLASH protection address for bank 1 (PRAR_CUR1)
    struct PRAR_CUR1 final {
        /// Default Constructor
        PRAR_CUR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PRAR_CUR1(PRAR_CUR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PRAR_CUR1(PRAR_CUR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PRAR_CUR1(PRAR_CUR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PRAR_CUR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PRAR_CUR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PRAR_CUR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 lowest PCROP protected address (PROT_AREA_START1)
            uint32_t prot_area_start1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                  : 4;    // bits 12:15
            /// Bank 1 highest PCROP protected address (PROT_AREA_END1)
            uint32_t prot_area_end1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                  : 3;    // bits 28:30
            /// Bank 1 PCROP protected erase enable option status bit (DMEP1)
            uint32_t dmep1            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PRAR_CUR1& operator=(PRAR_CUR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PRAR_CUR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PRAR_CUR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PRAR_CUR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PRAR_CUR1) == 4UL, "Must be this exact size");
    /// FLASH protection address for bank 1 (PRAR_PRG1)
    struct PRAR_PRG1 final {
        /// Default Constructor
        PRAR_PRG1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PRAR_PRG1(PRAR_PRG1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PRAR_PRG1(PRAR_PRG1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PRAR_PRG1(PRAR_PRG1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PRAR_PRG1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PRAR_PRG1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PRAR_PRG1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 lowest PCROP protected address configuration (PROT_AREA_START1)
            uint32_t prot_area_start1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                  : 4;    // bits 12:15
            /// Bank 1 highest PCROP protected address configuration (PROT_AREA_END1)
            uint32_t prot_area_end1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                  : 3;    // bits 28:30
            /// Bank 1 PCROP protected erase enable option configuration bit (DMEP1)
            uint32_t dmep1            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PRAR_PRG1& operator=(PRAR_PRG1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PRAR_PRG1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PRAR_PRG1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PRAR_PRG1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PRAR_PRG1) == 4UL, "Must be this exact size");
    /// FLASH secure address for bank 1 (SCAR_CUR1)
    struct SCAR_CUR1 final {
        /// Default Constructor
        SCAR_CUR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SCAR_CUR1(SCAR_CUR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SCAR_CUR1(SCAR_CUR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SCAR_CUR1(SCAR_CUR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SCAR_CUR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SCAR_CUR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SCAR_CUR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 lowest secure protected address (SEC_AREA_START1)
            uint32_t sec_area_start1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                 : 4;    // bits 12:15
            /// Bank 1 highest secure protected address (SEC_AREA_END1)
            uint32_t sec_area_end1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                 : 3;    // bits 28:30
            /// Bank 1 secure protected erase enable option status bit (DMES1)
            uint32_t dmes1           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SCAR_CUR1& operator=(SCAR_CUR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SCAR_CUR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SCAR_CUR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SCAR_CUR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SCAR_CUR1) == 4UL, "Must be this exact size");
    /// FLASH secure address for bank 1 (SCAR_PRG1)
    struct SCAR_PRG1 final {
        /// Default Constructor
        SCAR_PRG1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SCAR_PRG1(SCAR_PRG1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SCAR_PRG1(SCAR_PRG1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SCAR_PRG1(SCAR_PRG1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SCAR_PRG1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SCAR_PRG1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SCAR_PRG1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 lowest secure protected address configuration (SEC_AREA_START1)
            uint32_t sec_area_start1 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                 : 4;    // bits 12:15
            /// Bank 1 highest secure protected address configuration (SEC_AREA_END1)
            uint32_t sec_area_end1   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                 : 3;    // bits 28:30
            /// Bank 1 secure protected erase enable option configuration bit (DMES1)
            uint32_t dmes1           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SCAR_PRG1& operator=(SCAR_PRG1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SCAR_PRG1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SCAR_PRG1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SCAR_PRG1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SCAR_PRG1) == 4UL, "Must be this exact size");
    /// FLASH write sector protection for bank 1 (WPSN_CUR1R)
    struct WPSN_CUR1R final {
        /// Default Constructor
        WPSN_CUR1R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WPSN_CUR1R(WPSN_CUR1R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WPSN_CUR1R(WPSN_CUR1R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WPSN_CUR1R(WPSN_CUR1R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WPSN_CUR1R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WPSN_CUR1R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WPSN_CUR1R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 sector write protection option status byte (WRPSn1)
            uint32_t wrpsn1 : 8;    // bits 0:7
            /// (reserved)
            uint32_t        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WPSN_CUR1R& operator=(WPSN_CUR1R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WPSN_CUR1R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WPSN_CUR1R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WPSN_CUR1R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WPSN_CUR1R) == 4UL, "Must be this exact size");
    /// FLASH write sector protection for bank 1 (WPSN_PRG1R)
    struct WPSN_PRG1R final {
        /// Default Constructor
        WPSN_PRG1R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WPSN_PRG1R(WPSN_PRG1R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WPSN_PRG1R(WPSN_PRG1R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WPSN_PRG1R(WPSN_PRG1R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WPSN_PRG1R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WPSN_PRG1R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WPSN_PRG1R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 sector write protection configuration byte (WRPSn1)
            uint32_t wrpsn1 : 8;    // bits 0:7
            /// (reserved)
            uint32_t        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WPSN_PRG1R& operator=(WPSN_PRG1R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WPSN_PRG1R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WPSN_PRG1R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WPSN_PRG1R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WPSN_PRG1R) == 4UL, "Must be this exact size");
    /// FLASH register with boot address (BOOT_CURR)
    struct BOOT_CURR final {
        /// Default Constructor
        BOOT_CURR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BOOT_CURR(BOOT_CURR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BOOT_CURR(BOOT_CURR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BOOT_CURR(BOOT_CURR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BOOT_CURR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BOOT_CURR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BOOT_CURR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Boot address 0 (BOOT_ADD0)
            uint32_t boot_add0 : 16;    // bits 0:15
            /// Boot address 1 (BOOT_ADD1)
            uint32_t boot_add1 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BOOT_CURR& operator=(BOOT_CURR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BOOT_CURR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BOOT_CURR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BOOT_CURR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BOOT_CURR) == 4UL, "Must be this exact size");
    /// FLASH register with boot address (BOOT_PRGR)
    struct BOOT_PRGR final {
        /// Default Constructor
        BOOT_PRGR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BOOT_PRGR(BOOT_PRGR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BOOT_PRGR(BOOT_PRGR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BOOT_PRGR(BOOT_PRGR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BOOT_PRGR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BOOT_PRGR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BOOT_PRGR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Boot address 0 (BOOT_ADD0)
            uint32_t boot_add0 : 16;    // bits 0:15
            /// Boot address 1 (BOOT_ADD1)
            uint32_t boot_add1 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BOOT_PRGR& operator=(BOOT_PRGR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BOOT_PRGR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BOOT_PRGR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BOOT_PRGR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BOOT_PRGR) == 4UL, "Must be this exact size");
    /// FLASH CRC control register for bank 1 (CRCCR1)
    struct CRCCR1 final {
        /// Default Constructor
        CRCCR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCCR1(CRCCR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCCR1(CRCCR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCCR1(CRCCR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCCR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCCR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCCR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 CRC sector number (CRC_SECT)
            uint32_t crc_sect    : 3;    // bits 0:2
            /// (reserved)
            uint32_t             : 4;    // bits 3:6
            /// Bank 1 CRC select bit (ALL_BANK)
            uint32_t all_bank    : 1;    // bit 7
            /// Bank 1 CRC sector mode select bit (CRC_BY_SECT)
            uint32_t crc_by_sect : 1;    // bit 8
            /// Bank 1 CRC sector select bit (ADD_SECT)
            uint32_t add_sect    : 1;    // bit 9
            /// Bank 1 CRC sector list clear bit (CLEAN_SECT)
            uint32_t clean_sect  : 1;    // bit 10
            /// (reserved)
            uint32_t             : 5;    // bits 11:15
            /// Bank 1 CRC start bit (START_CRC)
            uint32_t start_crc   : 1;    // bit 16
            /// Bank 1 CRC clear bit (CLEAN_CRC)
            uint32_t clean_crc   : 1;    // bit 17
            /// (reserved)
            uint32_t             : 2;    // bits 18:19
            /// Bank 1 CRC burst size (CRC_BURST)
            uint32_t crc_burst   : 2;    // bits 20:21
            /// (reserved)
            uint32_t             : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCCR1& operator=(CRCCR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCCR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCCR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCCR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCCR1) == 4UL, "Must be this exact size");
    /// FLASH CRC start address register for bank 1 (CRCSADD1R)
    struct CRCSADD1R final {
        /// Default Constructor
        CRCSADD1R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCSADD1R(CRCSADD1R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCSADD1R(CRCSADD1R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCSADD1R(CRCSADD1R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCSADD1R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCSADD1R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCSADD1R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                : 2;    // bits 0:1
            /// CRC start address on bank 1 (CRC_START_ADDR)
            uint32_t crc_start_addr : 18;    // bits 2:19
            /// (reserved)
            uint32_t                : 12;    // bits 20:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCSADD1R& operator=(CRCSADD1R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCSADD1R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCSADD1R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCSADD1R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCSADD1R) == 4UL, "Must be this exact size");
    /// FLASH CRC end address register for bank 1 (CRCEADD1R)
    struct CRCEADD1R final {
        /// Default Constructor
        CRCEADD1R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCEADD1R(CRCEADD1R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCEADD1R(CRCEADD1R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCEADD1R(CRCEADD1R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCEADD1R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCEADD1R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCEADD1R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t              : 2;    // bits 0:1
            /// CRC end address on bank 1 (CRC_END_ADDR)
            uint32_t crc_end_addr : 18;    // bits 2:19
            /// (reserved)
            uint32_t              : 12;    // bits 20:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCEADD1R& operator=(CRCEADD1R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCEADD1R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCEADD1R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCEADD1R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCEADD1R) == 4UL, "Must be this exact size");
    /// FLASH CRC data register (CRCDATAR)
    struct CRCDATAR final {
        /// Default Constructor
        CRCDATAR()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCDATAR(CRCDATAR volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCDATAR(CRCDATAR const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCDATAR(CRCDATAR&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCDATAR(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCDATAR(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCDATAR() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC result (CRC_DATA)
            uint32_t crc_data : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCDATAR& operator=(CRCDATAR&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCDATAR volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCDATAR const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCDATAR>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCDATAR) == 4UL, "Must be this exact size");
    /// FLASH ECC fail address for bank 1 (ECC_FA1R)
    struct ECC_FA1R final {
        /// Default Constructor
        ECC_FA1R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ECC_FA1R(ECC_FA1R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ECC_FA1R(ECC_FA1R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ECC_FA1R(ECC_FA1R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ECC_FA1R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ECC_FA1R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ECC_FA1R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 1 ECC error address (FAIL_ECC_ADDR1)
            uint32_t fail_ecc_addr1 : 15;    // bits 0:14
            /// (reserved)
            uint32_t                : 17;    // bits 15:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ECC_FA1R& operator=(ECC_FA1R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ECC_FA1R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ECC_FA1R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ECC_FA1R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ECC_FA1R) == 4UL, "Must be this exact size");
    /// Access control register (ACR_)
    struct ACR_ final {
        /// Default Constructor
        ACR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ACR_(ACR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ACR_(ACR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ACR_(ACR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ACR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ACR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ACR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Read latency (LATENCY)
            uint32_t latency    : 4;    // bits 0:3
            /// Flash signal delay (WRHIGHFREQ)
            uint32_t wrhighfreq : 2;    // bits 4:5
            /// (reserved)
            uint32_t            : 26;    // bits 6:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ACR_& operator=(ACR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ACR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ACR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ACR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ACR_) == 4UL, "Must be this exact size");
    /// FLASH key register for bank 2 (KEYR2)
    struct KeyBank2 final {
        /// Default Constructor
        KeyBank2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        KeyBank2(KeyBank2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        KeyBank2(KeyBank2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        KeyBank2(KeyBank2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit KeyBank2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit KeyBank2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~KeyBank2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 access configuration unlock key (KEYR2)
            uint32_t key_bank2 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        KeyBank2& operator=(KeyBank2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(KeyBank2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(KeyBank2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<KeyBank2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(KeyBank2) == 4UL, "Must be this exact size");
    /// FLASH option key register (OPTKEYR_)
    struct OPTKEYR_ final {
        /// Default Constructor
        OPTKEYR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTKEYR_(OPTKEYR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTKEYR_(OPTKEYR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTKEYR_(OPTKEYR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTKEYR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTKEYR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTKEYR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Unlock key option bytes (OPTKEYR)
            uint32_t option_key : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTKEYR_& operator=(OPTKEYR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTKEYR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTKEYR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTKEYR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTKEYR_) == 4UL, "Must be this exact size");
    /// FLASH control register for bank 2 (CR2)
    struct Control2 final {
        /// Default Constructor
        Control2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control2(Control2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control2(Control2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control2(Control2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 configuration lock bit (LOCK2)
            uint32_t lock2       : 1;    // bit 0
            /// Bank 2 program enable bit (PG2)
            uint32_t pg2         : 1;    // bit 1
            /// Bank 2 sector erase request (SER2)
            uint32_t ser2        : 1;    // bit 2
            /// Bank 2 erase request (BER2)
            uint32_t ber2        : 1;    // bit 3
            /// Bank 2 program size (PSIZE2)
            uint32_t psize2      : 2;    // bits 4:5
            /// Bank 2 write forcing control bit (FW2)
            uint32_t fw2         : 1;    // bit 6
            /// Bank 2 bank or sector erase start control bit (START2)
            uint32_t start2      : 1;    // bit 7
            /// Bank 2 sector erase selection number (SNB2)
            uint32_t snb2        : 3;    // bits 8:10
            /// (reserved)
            uint32_t             : 3;    // bits 11:13
            /// Bank 2 special sector selection bit (SPSS2)
            uint32_t spss2       : 1;    // bit 14
            /// Bank 2 CRC control bit (CRC_EN)
            uint32_t crc_enable  : 1;    // bit 15
            /// Bank 2 end-of-program interrupt control bit (EOPIE2)
            uint32_t eopie2      : 1;    // bit 16
            /// Bank 2 write protection error interrupt enable bit (WRPERRIE2)
            uint32_t wrperrie2   : 1;    // bit 17
            /// Bank 2 programming sequence error interrupt enable bit (PGSERRIE2)
            uint32_t pgserrie2   : 1;    // bit 18
            /// Bank 2 strobe error interrupt enable bit (STRBERRIE2)
            uint32_t strberrie2  : 1;    // bit 19
            /// (reserved)
            uint32_t             : 1;    // bit 20
            /// Bank 2 inconsistency error interrupt enable bit (INCERRIE2)
            uint32_t incerrie2   : 1;    // bit 21
            /// Bank 2 write/erase error interrupt enable bit (OPERRIE2)
            uint32_t operrie2    : 1;    // bit 22
            /// Bank 2 read protection error interrupt enable bit (RDPERRIE2)
            uint32_t rdperrie2   : 1;    // bit 23
            /// Bank 2 secure error interrupt enable bit (RDSERRIE2)
            uint32_t rdserrie2   : 1;    // bit 24
            /// Bank 2 ECC single correction error interrupt enable bit (SNECCERRIE2)
            uint32_t sneccerrie2 : 1;    // bit 25
            /// Bank 2 ECC double detection error interrupt enable bit (DBECCERRIE2)
            uint32_t dbeccerrie2 : 1;    // bit 26
            /// Bank 2 end of CRC calculation interrupt enable bit (CRCENDIE2)
            uint32_t crcendie2   : 1;    // bit 27
            /// Bank 2 CRC read error interrupt enable bit (CRCRDERRIE2)
            uint32_t crcrderrie2 : 1;    // bit 28
            /// (reserved)
            uint32_t             : 3;    // bits 29:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control2& operator=(Control2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control2) == 4UL, "Must be this exact size");
    /// FLASH status register for bank 2 (SR2)
    struct Status2 final {
        /// Default Constructor
        Status2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Status2(Status2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Status2(Status2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Status2(Status2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Status2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Status2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Status2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 ongoing program flag (BSY2)
            uint32_t bsy2      : 1;    // bit 0
            /// Bank 2 write buffer not empty flag (WBNE2)
            uint32_t wbne2     : 1;    // bit 1
            /// Bank 2 wait queue flag (QW2)
            uint32_t qw2       : 1;    // bit 2
            /// Bank 2 CRC busy flag (CRC_BUSY2)
            uint32_t crc_busy2 : 1;    // bit 3
            /// (reserved)
            uint32_t           : 12;    // bits 4:15
            /// Bank 2 end-of-program flag (EOP2)
            uint32_t eop2      : 1;    // bit 16
            /// Bank 2 write protection error flag (WRPERR2)
            uint32_t wrperr2   : 1;    // bit 17
            /// Bank 2 programming sequence error flag (PGSERR2)
            uint32_t pgserr2   : 1;    // bit 18
            /// Bank 2 strobe error flag (STRBERR2)
            uint32_t strberr2  : 1;    // bit 19
            /// (reserved)
            uint32_t           : 1;    // bit 20
            /// Bank 2 inconsistency error flag (INCERR2)
            uint32_t incerr2   : 1;    // bit 21
            /// Bank 2 write/erase error flag (OPERR2)
            uint32_t operr2    : 1;    // bit 22
            /// Bank 2 read protection error flag (RDPERR2)
            uint32_t rdperr2   : 1;    // bit 23
            /// Bank 2 secure error flag (RDSERR2)
            uint32_t rdserr2   : 1;    // bit 24
            /// Bank 2 single correction error flag (SNECCERR2)
            uint32_t sneccerr2 : 1;    // bit 25
            /// Bank 2 ECC double detection error flag (DBECCERR2)
            uint32_t dbeccerr2 : 1;    // bit 26
            /// Bank 2 CRC-complete flag (CRCEND2)
            uint32_t crcend2   : 1;    // bit 27
            /// (reserved)
            uint32_t           : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Status2& operator=(Status2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Status2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Status2) == 4UL, "Must be this exact size");
    /// FLASH clear control register for bank 2 (CCR2)
    struct CaptureCompare2 final {
        /// Default Constructor
        CaptureCompare2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare2(CaptureCompare2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare2(CaptureCompare2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare2(CaptureCompare2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 16;    // bits 0:15
            /// Bank 1 EOP1 flag clear bit (CLR_EOP2)
            uint32_t clr_eop2      : 1;    // bit 16
            /// Bank 2 WRPERR1 flag clear bit (CLR_WRPERR2)
            uint32_t clr_wrperr2   : 1;    // bit 17
            /// Bank 2 PGSERR1 flag clear bi (CLR_PGSERR2)
            uint32_t clr_pgserr2   : 1;    // bit 18
            /// Bank 2 STRBERR1 flag clear bit (CLR_STRBERR2)
            uint32_t clr_strberr2  : 1;    // bit 19
            /// (reserved)
            uint32_t               : 1;    // bit 20
            /// Bank 2 INCERR1 flag clear bit (CLR_INCERR2)
            uint32_t clr_incerr2   : 1;    // bit 21
            /// Bank 2 OPERR1 flag clear bit (CLR_OPERR2)
            uint32_t clr_operr2    : 1;    // bit 22
            /// Bank 2 RDPERR1 flag clear bit (CLR_RDPERR2)
            uint32_t clr_rdperr2   : 1;    // bit 23
            /// Bank 1 RDSERR1 flag clear bit (CLR_RDSERR1)
            uint32_t clr_rdserr1   : 1;    // bit 24
            /// Bank 2 SNECCERR1 flag clear bit (CLR_SNECCERR2)
            uint32_t clr_sneccerr2 : 1;    // bit 25
            /// Bank 1 DBECCERR1 flag clear bit (CLR_DBECCERR1)
            uint32_t clr_dbeccerr1 : 1;    // bit 26
            /// Bank 2 CRCEND1 flag clear bit (CLR_CRCEND2)
            uint32_t clr_crcend2   : 1;    // bit 27
            /// (reserved)
            uint32_t               : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare2& operator=(CaptureCompare2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CaptureCompare2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare2) == 4UL, "Must be this exact size");
    /// FLASH option control register (OPTCR_)
    struct OPTCR_ final {
        /// Default Constructor
        OPTCR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTCR_(OPTCR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTCR_(OPTCR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTCR_(OPTCR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTCR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTCR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTCR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// FLASH_OPTCR lock option configuration bit (OPTLOCK)
            uint32_t optlock        : 1;    // bit 0
            /// Option byte start change option configuration bit (OPTSTART)
            uint32_t optstart       : 1;    // bit 1
            /// (reserved)
            uint32_t                : 2;    // bits 2:3
            /// Flash mass erase enable bit (MER)
            uint32_t memory_erase   : 1;    // bit 4
            /// (reserved)
            uint32_t                : 25;    // bits 5:29
            /// Option byte change error interrupt enable bit (OPTCHANGEERRIE)
            uint32_t optchangeerrie : 1;    // bit 30
            /// Bank swapping configuration bit (SWAP_BANK)
            uint32_t swap_bank      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTCR_& operator=(OPTCR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTCR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTCR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTCR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTCR_) == 4UL, "Must be this exact size");
    /// FLASH option status register (OPTSR_CUR_)
    struct OPTSR_CUR_ final {
        /// Default Constructor
        OPTSR_CUR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTSR_CUR_(OPTSR_CUR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTSR_CUR_(OPTSR_CUR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTSR_CUR_(OPTSR_CUR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTSR_CUR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTSR_CUR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTSR_CUR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Option byte change ongoing flag (OPT_BUSY)
            uint32_t opt_busy        : 1;    // bit 0
            /// (reserved)
            uint32_t                 : 1;    // bit 1
            /// Brownout level option status bit (BOR_LEV)
            uint32_t bor_lev         : 2;    // bits 2:3
            /// IWDG1 control option status bit (IWDG1_SW)
            uint32_t iwdg1_sw        : 1;    // bit 4
            /// (reserved)
            uint32_t                 : 1;    // bit 5
            /// D1 DStop entry reset option status bit (NRST_STOP_D1)
            uint32_t nrst_stop_d1    : 1;    // bit 6
            /// D1 DStandby entry reset option status bit (NRST_STBY_D1)
            uint32_t nrst_standby_d1 : 1;    // bit 7
            /// Readout protection level option status byte (RDP)
            uint32_t rdp             : 8;    // bits 8:15
            /// (reserved)
            uint32_t                 : 1;    // bit 16
            /// IWDG Stop mode freeze option status bit (IWDG_FZ_STOP)
            uint32_t iwdg_fz_stop    : 1;    // bit 17
            /// IWDG Standby mode freeze option status bit (IWDG_FZ_SDBY)
            uint32_t iwdg_fz_sdby    : 1;    // bit 18
            /// DTCM RAM size option status (ST_RAM_SIZE)
            uint32_t st_ram_size     : 2;    // bits 19:20
            /// Security enable option status bit (SECURITY)
            uint32_t security        : 1;    // bit 21
            /// (reserved)
            uint32_t                 : 7;    // bits 22:28
            /// I/O high-speed at low-voltage status bit (PRODUCT_BELOW_25V) (IO_HSLV)
            uint32_t io_hslv         : 1;    // bit 29
            /// Option byte change error flag (OPTCHANGEERR)
            uint32_t optchangeerr    : 1;    // bit 30
            /// Bank swapping option status bit (SWAP_BANK_OPT)
            uint32_t swap_bank_opt   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTSR_CUR_& operator=(OPTSR_CUR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTSR_CUR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTSR_CUR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTSR_CUR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTSR_CUR_) == 4UL, "Must be this exact size");
    /// FLASH option status register (OPTSR_PRG_)
    struct OPTSR_PRG_ final {
        /// Default Constructor
        OPTSR_PRG_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTSR_PRG_(OPTSR_PRG_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTSR_PRG_(OPTSR_PRG_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTSR_PRG_(OPTSR_PRG_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTSR_PRG_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTSR_PRG_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTSR_PRG_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t               : 2;    // bits 0:1
            /// BOR reset level option configuration bits (BOR_LEV)
            uint32_t bor_lev       : 2;    // bits 2:3
            /// IWDG1 option configuration bit (IWDG1_SW)
            uint32_t iwdg1_sw      : 1;    // bit 4
            /// (reserved)
            uint32_t               : 1;    // bit 5
            /// Option byte erase after D1 DStop option configuration bit (nRST_STOP)
            uint32_t nrst_stop     : 1;    // bit 6
            /// Option byte erase after D1 DStandby option configuration bit (nRST_STDY)
            uint32_t nrst_stdy     : 1;    // bit 7
            /// Readout protection level option configuration byte (RDP)
            uint32_t rdp           : 8;    // bits 8:15
            /// (reserved)
            uint32_t               : 1;    // bit 16
            /// IWDG Stop mode freeze option configuration bit (FZ_IWDG_STOP)
            uint32_t fz_iwdg_stop  : 1;    // bit 17
            /// IWDG Standby mode freeze option configuration bit (FZ_IWDG_SDBY)
            uint32_t fz_iwdg_sdby  : 1;    // bit 18
            /// DTCM size select option configuration bits (ST_RAM_SIZE)
            uint32_t st_ram_size   : 2;    // bits 19:20
            /// Security option configuration bit (SECURITY)
            uint32_t security      : 1;    // bit 21
            /// (reserved)
            uint32_t               : 7;    // bits 22:28
            /// I/O high-speed at low-voltage (PRODUCT_BELOW_25V) (IO_HSLV)
            uint32_t io_hslv       : 1;    // bit 29
            /// (reserved)
            uint32_t               : 1;    // bit 30
            /// Bank swapping option configuration bit (SWAP_BANK_OPT)
            uint32_t swap_bank_opt : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTSR_PRG_& operator=(OPTSR_PRG_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTSR_PRG_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTSR_PRG_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTSR_PRG_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTSR_PRG_) == 4UL, "Must be this exact size");
    /// FLASH option clear control register (OPTCCR_)
    struct OPTCCR_ final {
        /// Default Constructor
        OPTCCR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OPTCCR_(OPTCCR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OPTCCR_(OPTCCR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OPTCCR_(OPTCCR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OPTCCR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OPTCCR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OPTCCR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                  : 30;    // bits 0:29
            /// OPTCHANGEERR reset bit (CLR_OPTCHANGEERR)
            uint32_t clr_optchangeerr : 1;    // bit 30
            /// (reserved)
            uint32_t                  : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OPTCCR_& operator=(OPTCCR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OPTCCR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OPTCCR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OPTCCR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OPTCCR_) == 4UL, "Must be this exact size");
    /// FLASH protection address for bank 1 (PRAR_CUR2)
    struct PRAR_CUR2 final {
        /// Default Constructor
        PRAR_CUR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PRAR_CUR2(PRAR_CUR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PRAR_CUR2(PRAR_CUR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PRAR_CUR2(PRAR_CUR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PRAR_CUR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PRAR_CUR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PRAR_CUR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 lowest PCROP protected address (PROT_AREA_START2)
            uint32_t prot_area_start2 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                  : 4;    // bits 12:15
            /// Bank 2 highest PCROP protected address (PROT_AREA_END2)
            uint32_t prot_area_end2   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                  : 3;    // bits 28:30
            /// Bank 2 PCROP protected erase enable option status bit (DMEP2)
            uint32_t dmep2            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PRAR_CUR2& operator=(PRAR_CUR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PRAR_CUR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PRAR_CUR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PRAR_CUR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PRAR_CUR2) == 4UL, "Must be this exact size");
    /// FLASH protection address for bank 2 (PRAR_PRG2)
    struct PRAR_PRG2 final {
        /// Default Constructor
        PRAR_PRG2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PRAR_PRG2(PRAR_PRG2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PRAR_PRG2(PRAR_PRG2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PRAR_PRG2(PRAR_PRG2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PRAR_PRG2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PRAR_PRG2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PRAR_PRG2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 lowest PCROP protected address configuration (PROT_AREA_START2)
            uint32_t prot_area_start2 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                  : 4;    // bits 12:15
            /// Bank 2 highest PCROP protected address configuration (PROT_AREA_END2)
            uint32_t prot_area_end2   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                  : 3;    // bits 28:30
            /// Bank 2 PCROP protected erase enable option configuration bit (DMEP2)
            uint32_t dmep2            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PRAR_PRG2& operator=(PRAR_PRG2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PRAR_PRG2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PRAR_PRG2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PRAR_PRG2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PRAR_PRG2) == 4UL, "Must be this exact size");
    /// FLASH secure address for bank 2 (SCAR_CUR2)
    struct SCAR_CUR2 final {
        /// Default Constructor
        SCAR_CUR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SCAR_CUR2(SCAR_CUR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SCAR_CUR2(SCAR_CUR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SCAR_CUR2(SCAR_CUR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SCAR_CUR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SCAR_CUR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SCAR_CUR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 lowest secure protected address (SEC_AREA_START2)
            uint32_t sec_area_start2 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                 : 4;    // bits 12:15
            /// Bank 2 highest secure protected address (SEC_AREA_END2)
            uint32_t sec_area_end2   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                 : 3;    // bits 28:30
            /// Bank 2 secure protected erase enable option status bit (DMES2)
            uint32_t dmes2           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SCAR_CUR2& operator=(SCAR_CUR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SCAR_CUR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SCAR_CUR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SCAR_CUR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SCAR_CUR2) == 4UL, "Must be this exact size");
    /// FLASH secure address for bank 2 (SCAR_PRG2)
    struct SCAR_PRG2 final {
        /// Default Constructor
        SCAR_PRG2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SCAR_PRG2(SCAR_PRG2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SCAR_PRG2(SCAR_PRG2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SCAR_PRG2(SCAR_PRG2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SCAR_PRG2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SCAR_PRG2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SCAR_PRG2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 lowest secure protected address configuration (SEC_AREA_START2)
            uint32_t sec_area_start2 : 12;    // bits 0:11
            /// (reserved)
            uint32_t                 : 4;    // bits 12:15
            /// Bank 2 highest secure protected address configuration (SEC_AREA_END2)
            uint32_t sec_area_end2   : 12;    // bits 16:27
            /// (reserved)
            uint32_t                 : 3;    // bits 28:30
            /// Bank 2 secure protected erase enable option configuration bit (DMES2)
            uint32_t dmes2           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SCAR_PRG2& operator=(SCAR_PRG2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SCAR_PRG2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SCAR_PRG2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SCAR_PRG2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SCAR_PRG2) == 4UL, "Must be this exact size");
    /// FLASH write sector protection for bank 2 (WPSN_CUR2R)
    struct WPSN_CUR2R final {
        /// Default Constructor
        WPSN_CUR2R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WPSN_CUR2R(WPSN_CUR2R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WPSN_CUR2R(WPSN_CUR2R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WPSN_CUR2R(WPSN_CUR2R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WPSN_CUR2R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WPSN_CUR2R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WPSN_CUR2R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 sector write protection option status byte (WRPSn2)
            uint32_t wrpsn2 : 8;    // bits 0:7
            /// (reserved)
            uint32_t        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WPSN_CUR2R& operator=(WPSN_CUR2R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WPSN_CUR2R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WPSN_CUR2R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WPSN_CUR2R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WPSN_CUR2R) == 4UL, "Must be this exact size");
    /// FLASH write sector protection for bank 2 (WPSN_PRG2R)
    struct WPSN_PRG2R final {
        /// Default Constructor
        WPSN_PRG2R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WPSN_PRG2R(WPSN_PRG2R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WPSN_PRG2R(WPSN_PRG2R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WPSN_PRG2R(WPSN_PRG2R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WPSN_PRG2R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WPSN_PRG2R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WPSN_PRG2R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 sector write protection configuration byte (WRPSn2)
            uint32_t wrpsn2 : 8;    // bits 0:7
            /// (reserved)
            uint32_t        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WPSN_PRG2R& operator=(WPSN_PRG2R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WPSN_PRG2R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WPSN_PRG2R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WPSN_PRG2R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WPSN_PRG2R) == 4UL, "Must be this exact size");
    /// FLASH register with boot address (BOOT_CURR_)
    struct BOOT_CURR_ final {
        /// Default Constructor
        BOOT_CURR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BOOT_CURR_(BOOT_CURR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BOOT_CURR_(BOOT_CURR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BOOT_CURR_(BOOT_CURR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BOOT_CURR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BOOT_CURR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BOOT_CURR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Boot address 0 (BOOT_ADD0)
            uint32_t boot_add0 : 16;    // bits 0:15
            /// Boot address 1 (BOOT_ADD1)
            uint32_t boot_add1 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BOOT_CURR_& operator=(BOOT_CURR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BOOT_CURR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BOOT_CURR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BOOT_CURR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BOOT_CURR_) == 4UL, "Must be this exact size");
    /// FLASH register with boot address (BOOT_PRGR_)
    struct BOOT_PRGR_ final {
        /// Default Constructor
        BOOT_PRGR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BOOT_PRGR_(BOOT_PRGR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BOOT_PRGR_(BOOT_PRGR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BOOT_PRGR_(BOOT_PRGR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BOOT_PRGR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BOOT_PRGR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BOOT_PRGR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Boot address 0 (BOOT_ADD0)
            uint32_t boot_add0 : 16;    // bits 0:15
            /// Boot address 1 (BOOT_ADD1)
            uint32_t boot_add1 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BOOT_PRGR_& operator=(BOOT_PRGR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BOOT_PRGR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BOOT_PRGR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BOOT_PRGR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BOOT_PRGR_) == 4UL, "Must be this exact size");
    /// FLASH CRC control register for bank 1 (CRCCR2)
    struct CRCCR2 final {
        /// Default Constructor
        CRCCR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCCR2(CRCCR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCCR2(CRCCR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCCR2(CRCCR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCCR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCCR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCCR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 CRC sector number (CRC_SECT)
            uint32_t crc_sect    : 3;    // bits 0:2
            /// (reserved)
            uint32_t             : 4;    // bits 3:6
            /// Bank 2 CRC select bit (ALL_BANK)
            uint32_t all_bank    : 1;    // bit 7
            /// Bank 2 CRC sector mode select bit (CRC_BY_SECT)
            uint32_t crc_by_sect : 1;    // bit 8
            /// Bank 2 CRC sector select bit (ADD_SECT)
            uint32_t add_sect    : 1;    // bit 9
            /// Bank 2 CRC sector list clear bit (CLEAN_SECT)
            uint32_t clean_sect  : 1;    // bit 10
            /// (reserved)
            uint32_t             : 5;    // bits 11:15
            /// Bank 2 CRC start bit (START_CRC)
            uint32_t start_crc   : 1;    // bit 16
            /// Bank 2 CRC clear bit (CLEAN_CRC)
            uint32_t clean_crc   : 1;    // bit 17
            /// (reserved)
            uint32_t             : 2;    // bits 18:19
            /// Bank 2 CRC burst size (CRC_BURST)
            uint32_t crc_burst   : 2;    // bits 20:21
            /// (reserved)
            uint32_t             : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCCR2& operator=(CRCCR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCCR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCCR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCCR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCCR2) == 4UL, "Must be this exact size");
    /// FLASH CRC start address register for bank 2 (CRCSADD2R)
    struct CRCSADD2R final {
        /// Default Constructor
        CRCSADD2R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCSADD2R(CRCSADD2R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCSADD2R(CRCSADD2R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCSADD2R(CRCSADD2R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCSADD2R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCSADD2R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCSADD2R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                : 2;    // bits 0:1
            /// CRC start address on bank 2 (CRC_START_ADDR)
            uint32_t crc_start_addr : 18;    // bits 2:19
            /// (reserved)
            uint32_t                : 12;    // bits 20:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCSADD2R& operator=(CRCSADD2R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCSADD2R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCSADD2R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCSADD2R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCSADD2R) == 4UL, "Must be this exact size");
    /// FLASH CRC end address register for bank 2 (CRCEADD2R)
    struct CRCEADD2R final {
        /// Default Constructor
        CRCEADD2R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCEADD2R(CRCEADD2R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCEADD2R(CRCEADD2R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCEADD2R(CRCEADD2R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCEADD2R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCEADD2R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCEADD2R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t              : 2;    // bits 0:1
            /// CRC end address on bank 2 (CRC_END_ADDR)
            uint32_t crc_end_addr : 18;    // bits 2:19
            /// (reserved)
            uint32_t              : 12;    // bits 20:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCEADD2R& operator=(CRCEADD2R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCEADD2R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCEADD2R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCEADD2R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCEADD2R) == 4UL, "Must be this exact size");
    /// FLASH CRC data register (CRCDATAR_)
    struct CRCDATAR_ final {
        /// Default Constructor
        CRCDATAR_()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CRCDATAR_(CRCDATAR_ volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CRCDATAR_(CRCDATAR_ const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CRCDATAR_(CRCDATAR_&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CRCDATAR_(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CRCDATAR_(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CRCDATAR_() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC result (CRC_DATA)
            uint32_t crc_data : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CRCDATAR_& operator=(CRCDATAR_&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CRCDATAR_ volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CRCDATAR_ const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CRCDATAR_>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CRCDATAR_) == 4UL, "Must be this exact size");
    /// FLASH ECC fail address for bank 2 (ECC_FA2R)
    struct ECC_FA2R final {
        /// Default Constructor
        ECC_FA2R()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ECC_FA2R(ECC_FA2R volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ECC_FA2R(ECC_FA2R const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ECC_FA2R(ECC_FA2R&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ECC_FA2R(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ECC_FA2R(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ECC_FA2R() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bank 2 ECC error address (FAIL_ECC_ADDR2)
            uint32_t fail_ecc_addr2 : 15;    // bits 0:14
            /// (reserved)
            uint32_t                : 17;    // bits 15:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ECC_FA2R& operator=(ECC_FA2R&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ECC_FA2R volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ECC_FA2R const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ECC_FA2R>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ECC_FA2R) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Access control register (ACR)
    AccessControl access_control;    // offset 0x0UL
    /// FLASH key register for bank 1 (KEYR1)
    KeyBank1 key_bank1;    // offset 0x4UL
    /// FLASH option key register (OPTKEYR)
    OptionKey option_key;    // offset 0x8UL
    /// FLASH control register for bank 1 (CR1)
    Control1 control1;    // offset 0xcUL
    /// FLASH status register for bank 1 (SR1)
    Status1 status1;    // offset 0x10UL
    /// FLASH clear control register for bank 1 (CCR1)
    CaptureCompare1 capture_compare1;    // offset 0x14UL
    /// FLASH option control register (OPTCR)
    OPTCR optcr;    // offset 0x18UL
    /// FLASH option status register (OPTSR_CUR)
    OPTSR_CUR optsr_cur;    // offset 0x1cUL
    /// FLASH option status register (OPTSR_PRG)
    OPTSR_PRG optsr_prg;    // offset 0x20UL
    /// FLASH option clear control register (OPTCCR)
    OPTCCR optccr;    // offset 0x24UL
    /// FLASH protection address for bank 1 (PRAR_CUR1)
    PRAR_CUR1 prar_cur1;    // offset 0x28UL
    /// FLASH protection address for bank 1 (PRAR_PRG1)
    PRAR_PRG1 prar_prg1;    // offset 0x2cUL
    /// FLASH secure address for bank 1 (SCAR_CUR1)
    SCAR_CUR1 scar_cur1;    // offset 0x30UL
    /// FLASH secure address for bank 1 (SCAR_PRG1)
    SCAR_PRG1 scar_prg1;    // offset 0x34UL
    /// FLASH write sector protection for bank 1 (WPSN_CUR1R)
    WPSN_CUR1R wpsn_cur1r;    // offset 0x38UL
    /// FLASH write sector protection for bank 1 (WPSN_PRG1R)
    WPSN_PRG1R wpsn_prg1r;    // offset 0x3cUL
    /// FLASH register with boot address (BOOT_CURR)
    BOOT_CURR boot_curr;    // offset 0x40UL
    /// FLASH register with boot address (BOOT_PRGR)
    BOOT_PRGR boot_prgr;    // offset 0x44UL
    uint32_t : 32;          // offset 0x48UL
    uint32_t : 32;          // offset 0x4cUL
    /// FLASH CRC control register for bank 1 (CRCCR1)
    CRCCR1 crccr1;    // offset 0x50UL
    /// FLASH CRC start address register for bank 1 (CRCSADD1R)
    CRCSADD1R crcsadd1r;    // offset 0x54UL
    /// FLASH CRC end address register for bank 1 (CRCEADD1R)
    CRCEADD1R crceadd1r;    // offset 0x58UL
    /// FLASH CRC data register (CRCDATAR)
    CRCDATAR crcdatar;    // offset 0x5cUL
    /// FLASH ECC fail address for bank 1 (ECC_FA1R)
    ECC_FA1R ecc_fa1r;    // offset 0x60UL
    uint32_t : 32;        // offset 0x64UL
    uint32_t : 32;        // offset 0x68UL
    uint32_t : 32;        // offset 0x6cUL
    uint32_t : 32;        // offset 0x70UL
    uint32_t : 32;        // offset 0x74UL
    uint32_t : 32;        // offset 0x78UL
    uint32_t : 32;        // offset 0x7cUL
    uint32_t : 32;        // offset 0x80UL
    uint32_t : 32;        // offset 0x84UL
    uint32_t : 32;        // offset 0x88UL
    uint32_t : 32;        // offset 0x8cUL
    uint32_t : 32;        // offset 0x90UL
    uint32_t : 32;        // offset 0x94UL
    uint32_t : 32;        // offset 0x98UL
    uint32_t : 32;        // offset 0x9cUL
    uint32_t : 32;        // offset 0xa0UL
    uint32_t : 32;        // offset 0xa4UL
    uint32_t : 32;        // offset 0xa8UL
    uint32_t : 32;        // offset 0xacUL
    uint32_t : 32;        // offset 0xb0UL
    uint32_t : 32;        // offset 0xb4UL
    uint32_t : 32;        // offset 0xb8UL
    uint32_t : 32;        // offset 0xbcUL
    uint32_t : 32;        // offset 0xc0UL
    uint32_t : 32;        // offset 0xc4UL
    uint32_t : 32;        // offset 0xc8UL
    uint32_t : 32;        // offset 0xccUL
    uint32_t : 32;        // offset 0xd0UL
    uint32_t : 32;        // offset 0xd4UL
    uint32_t : 32;        // offset 0xd8UL
    uint32_t : 32;        // offset 0xdcUL
    uint32_t : 32;        // offset 0xe0UL
    uint32_t : 32;        // offset 0xe4UL
    uint32_t : 32;        // offset 0xe8UL
    uint32_t : 32;        // offset 0xecUL
    uint32_t : 32;        // offset 0xf0UL
    uint32_t : 32;        // offset 0xf4UL
    uint32_t : 32;        // offset 0xf8UL
    uint32_t : 32;        // offset 0xfcUL
    /// Access control register (ACR_)
    ACR_ acr_;    // offset 0x100UL
    /// FLASH key register for bank 2 (KEYR2)
    KeyBank2 key_bank2;    // offset 0x104UL
    /// FLASH option key register (OPTKEYR_)
    OPTKEYR_ optkeyr_;    // offset 0x108UL
    /// FLASH control register for bank 2 (CR2)
    Control2 control2;    // offset 0x10cUL
    /// FLASH status register for bank 2 (SR2)
    Status2 status2;    // offset 0x110UL
    /// FLASH clear control register for bank 2 (CCR2)
    CaptureCompare2 capture_compare2;    // offset 0x114UL
    /// FLASH option control register (OPTCR_)
    OPTCR_ optcr_;    // offset 0x118UL
    /// FLASH option status register (OPTSR_CUR_)
    OPTSR_CUR_ optsr_cur_;    // offset 0x11cUL
    /// FLASH option status register (OPTSR_PRG_)
    OPTSR_PRG_ optsr_prg_;    // offset 0x120UL
    /// FLASH option clear control register (OPTCCR_)
    OPTCCR_ optccr_;    // offset 0x124UL
    /// FLASH protection address for bank 1 (PRAR_CUR2)
    PRAR_CUR2 prar_cur2;    // offset 0x128UL
    /// FLASH protection address for bank 2 (PRAR_PRG2)
    PRAR_PRG2 prar_prg2;    // offset 0x12cUL
    /// FLASH secure address for bank 2 (SCAR_CUR2)
    SCAR_CUR2 scar_cur2;    // offset 0x130UL
    /// FLASH secure address for bank 2 (SCAR_PRG2)
    SCAR_PRG2 scar_prg2;    // offset 0x134UL
    /// FLASH write sector protection for bank 2 (WPSN_CUR2R)
    WPSN_CUR2R wpsn_cur2r;    // offset 0x138UL
    /// FLASH write sector protection for bank 2 (WPSN_PRG2R)
    WPSN_PRG2R wpsn_prg2r;    // offset 0x13cUL
    /// FLASH register with boot address (BOOT_CURR_)
    BOOT_CURR_ boot_curr_;    // offset 0x140UL
    /// FLASH register with boot address (BOOT_PRGR_)
    BOOT_PRGR_ boot_prgr_;    // offset 0x144UL
    uint32_t : 32;            // offset 0x148UL
    uint32_t : 32;            // offset 0x14cUL
    /// FLASH CRC control register for bank 1 (CRCCR2)
    CRCCR2 crccr2;    // offset 0x150UL
    /// FLASH CRC start address register for bank 2 (CRCSADD2R)
    CRCSADD2R crcsadd2r;    // offset 0x154UL
    /// FLASH CRC end address register for bank 2 (CRCEADD2R)
    CRCEADD2R crceadd2r;    // offset 0x158UL
    /// FLASH CRC data register (CRCDATAR_)
    CRCDATAR_ crcdatar_;    // offset 0x15cUL
    /// FLASH ECC fail address for bank 2 (ECC_FA2R)
    ECC_FA2R ecc_fa2r;    // offset 0x160UL
    uint32_t : 32;        // offset 0x164UL
    uint32_t : 32;        // offset 0x168UL
    uint32_t : 32;        // offset 0x16cUL
    uint32_t : 32;        // offset 0x170UL
    uint32_t : 32;        // offset 0x174UL
    uint32_t : 32;        // offset 0x178UL
    uint32_t : 32;        // offset 0x17cUL
    uint32_t : 32;        // offset 0x180UL
    uint32_t : 32;        // offset 0x184UL
    uint32_t : 32;        // offset 0x188UL
    uint32_t : 32;        // offset 0x18cUL
    uint32_t : 32;        // offset 0x190UL
    uint32_t : 32;        // offset 0x194UL
    uint32_t : 32;        // offset 0x198UL
    uint32_t : 32;        // offset 0x19cUL
    uint32_t : 32;        // offset 0x1a0UL
    uint32_t : 32;        // offset 0x1a4UL
    uint32_t : 32;        // offset 0x1a8UL
    uint32_t : 32;        // offset 0x1acUL
    uint32_t : 32;        // offset 0x1b0UL
    uint32_t : 32;        // offset 0x1b4UL
    uint32_t : 32;        // offset 0x1b8UL
    uint32_t : 32;        // offset 0x1bcUL
    uint32_t : 32;        // offset 0x1c0UL
    uint32_t : 32;        // offset 0x1c4UL
    uint32_t : 32;        // offset 0x1c8UL
    uint32_t : 32;        // offset 0x1ccUL
    uint32_t : 32;        // offset 0x1d0UL
    uint32_t : 32;        // offset 0x1d4UL
    uint32_t : 32;        // offset 0x1d8UL
    uint32_t : 32;        // offset 0x1dcUL
    uint32_t : 32;        // offset 0x1e0UL
    uint32_t : 32;        // offset 0x1e4UL
    uint32_t : 32;        // offset 0x1e8UL
    uint32_t : 32;        // offset 0x1ecUL
    uint32_t : 32;        // offset 0x1f0UL
    uint32_t : 32;        // offset 0x1f4UL
    uint32_t : 32;        // offset 0x1f8UL
    uint32_t : 32;        // offset 0x1fcUL
    uint32_t : 32;        // offset 0x200UL
    uint32_t : 32;        // offset 0x204UL
    uint32_t : 32;        // offset 0x208UL
    uint32_t : 32;        // offset 0x20cUL
    uint32_t : 32;        // offset 0x210UL
    uint32_t : 32;        // offset 0x214UL
    uint32_t : 32;        // offset 0x218UL
    uint32_t : 32;        // offset 0x21cUL
    uint32_t : 32;        // offset 0x220UL
    uint32_t : 32;        // offset 0x224UL
    uint32_t : 32;        // offset 0x228UL
    uint32_t : 32;        // offset 0x22cUL
    uint32_t : 32;        // offset 0x230UL
    uint32_t : 32;        // offset 0x234UL
    uint32_t : 32;        // offset 0x238UL
    uint32_t : 32;        // offset 0x23cUL
    uint32_t : 32;        // offset 0x240UL
    uint32_t : 32;        // offset 0x244UL
    uint32_t : 32;        // offset 0x248UL
    uint32_t : 32;        // offset 0x24cUL
    uint32_t : 32;        // offset 0x250UL
    uint32_t : 32;        // offset 0x254UL
    uint32_t : 32;        // offset 0x258UL
    uint32_t : 32;        // offset 0x25cUL
    uint32_t : 32;        // offset 0x260UL
    uint32_t : 32;        // offset 0x264UL
    uint32_t : 32;        // offset 0x268UL
    uint32_t : 32;        // offset 0x26cUL
    uint32_t : 32;        // offset 0x270UL
    uint32_t : 32;        // offset 0x274UL
    uint32_t : 32;        // offset 0x278UL
    uint32_t : 32;        // offset 0x27cUL
    uint32_t : 32;        // offset 0x280UL
    uint32_t : 32;        // offset 0x284UL
    uint32_t : 32;        // offset 0x288UL
    uint32_t : 32;        // offset 0x28cUL
    uint32_t : 32;        // offset 0x290UL
    uint32_t : 32;        // offset 0x294UL
    uint32_t : 32;        // offset 0x298UL
    uint32_t : 32;        // offset 0x29cUL
    uint32_t : 32;        // offset 0x2a0UL
    uint32_t : 32;        // offset 0x2a4UL
    uint32_t : 32;        // offset 0x2a8UL
    uint32_t : 32;        // offset 0x2acUL
    uint32_t : 32;        // offset 0x2b0UL
    uint32_t : 32;        // offset 0x2b4UL
    uint32_t : 32;        // offset 0x2b8UL
    uint32_t : 32;        // offset 0x2bcUL
    uint32_t : 32;        // offset 0x2c0UL
    uint32_t : 32;        // offset 0x2c4UL
    uint32_t : 32;        // offset 0x2c8UL
    uint32_t : 32;        // offset 0x2ccUL
    uint32_t : 32;        // offset 0x2d0UL
    uint32_t : 32;        // offset 0x2d4UL
    uint32_t : 32;        // offset 0x2d8UL
    uint32_t : 32;        // offset 0x2dcUL
    uint32_t : 32;        // offset 0x2e0UL
    uint32_t : 32;        // offset 0x2e4UL
    uint32_t : 32;        // offset 0x2e8UL
    uint32_t : 32;        // offset 0x2ecUL
    uint32_t : 32;        // offset 0x2f0UL
    uint32_t : 32;        // offset 0x2f4UL
    uint32_t : 32;        // offset 0x2f8UL
    uint32_t : 32;        // offset 0x2fcUL
    uint32_t : 32;        // offset 0x300UL
    uint32_t : 32;        // offset 0x304UL
    uint32_t : 32;        // offset 0x308UL
    uint32_t : 32;        // offset 0x30cUL
    uint32_t : 32;        // offset 0x310UL
    uint32_t : 32;        // offset 0x314UL
    uint32_t : 32;        // offset 0x318UL
    uint32_t : 32;        // offset 0x31cUL
    uint32_t : 32;        // offset 0x320UL
    uint32_t : 32;        // offset 0x324UL
    uint32_t : 32;        // offset 0x328UL
    uint32_t : 32;        // offset 0x32cUL
    uint32_t : 32;        // offset 0x330UL
    uint32_t : 32;        // offset 0x334UL
    uint32_t : 32;        // offset 0x338UL
    uint32_t : 32;        // offset 0x33cUL
    uint32_t : 32;        // offset 0x340UL
    uint32_t : 32;        // offset 0x344UL
    uint32_t : 32;        // offset 0x348UL
    uint32_t : 32;        // offset 0x34cUL
    uint32_t : 32;        // offset 0x350UL
    uint32_t : 32;        // offset 0x354UL
    uint32_t : 32;        // offset 0x358UL
    uint32_t : 32;        // offset 0x35cUL
    uint32_t : 32;        // offset 0x360UL
    uint32_t : 32;        // offset 0x364UL
    uint32_t : 32;        // offset 0x368UL
    uint32_t : 32;        // offset 0x36cUL
    uint32_t : 32;        // offset 0x370UL
    uint32_t : 32;        // offset 0x374UL
    uint32_t : 32;        // offset 0x378UL
    uint32_t : 32;        // offset 0x37cUL
    uint32_t : 32;        // offset 0x380UL
    uint32_t : 32;        // offset 0x384UL
    uint32_t : 32;        // offset 0x388UL
    uint32_t : 32;        // offset 0x38cUL
    uint32_t : 32;        // offset 0x390UL
    uint32_t : 32;        // offset 0x394UL
    uint32_t : 32;        // offset 0x398UL
    uint32_t : 32;        // offset 0x39cUL
    uint32_t : 32;        // offset 0x3a0UL
    uint32_t : 32;        // offset 0x3a4UL
    uint32_t : 32;        // offset 0x3a8UL
    uint32_t : 32;        // offset 0x3acUL
    uint32_t : 32;        // offset 0x3b0UL
    uint32_t : 32;        // offset 0x3b4UL
    uint32_t : 32;        // offset 0x3b8UL
    uint32_t : 32;        // offset 0x3bcUL
    uint32_t : 32;        // offset 0x3c0UL
    uint32_t : 32;        // offset 0x3c4UL
    uint32_t : 32;        // offset 0x3c8UL
    uint32_t : 32;        // offset 0x3ccUL
    uint32_t : 32;        // offset 0x3d0UL
    uint32_t : 32;        // offset 0x3d4UL
    uint32_t : 32;        // offset 0x3d8UL
    uint32_t : 32;        // offset 0x3dcUL
    uint32_t : 32;        // offset 0x3e0UL
    uint32_t : 32;        // offset 0x3e4UL
    uint32_t : 32;        // offset 0x3e8UL
    uint32_t : 32;        // offset 0x3ecUL
    uint32_t : 32;        // offset 0x3f0UL
    uint32_t : 32;        // offset 0x3f4UL
    uint32_t : 32;        // offset 0x3f8UL
    uint32_t : 32;        // offset 0x3fcUL
    uint32_t : 32;        // offset 0x400UL
    uint32_t : 32;        // offset 0x404UL
    uint32_t : 32;        // offset 0x408UL
    uint32_t : 32;        // offset 0x40cUL
    uint32_t : 32;        // offset 0x410UL
    uint32_t : 32;        // offset 0x414UL
    uint32_t : 32;        // offset 0x418UL
    uint32_t : 32;        // offset 0x41cUL
    uint32_t : 32;        // offset 0x420UL
    uint32_t : 32;        // offset 0x424UL
    uint32_t : 32;        // offset 0x428UL
    uint32_t : 32;        // offset 0x42cUL
    uint32_t : 32;        // offset 0x430UL
    uint32_t : 32;        // offset 0x434UL
    uint32_t : 32;        // offset 0x438UL
    uint32_t : 32;        // offset 0x43cUL
    uint32_t : 32;        // offset 0x440UL
    uint32_t : 32;        // offset 0x444UL
    uint32_t : 32;        // offset 0x448UL
    uint32_t : 32;        // offset 0x44cUL
    uint32_t : 32;        // offset 0x450UL
    uint32_t : 32;        // offset 0x454UL
    uint32_t : 32;        // offset 0x458UL
    uint32_t : 32;        // offset 0x45cUL
    uint32_t : 32;        // offset 0x460UL
    uint32_t : 32;        // offset 0x464UL
    uint32_t : 32;        // offset 0x468UL
    uint32_t : 32;        // offset 0x46cUL
    uint32_t : 32;        // offset 0x470UL
    uint32_t : 32;        // offset 0x474UL
    uint32_t : 32;        // offset 0x478UL
    uint32_t : 32;        // offset 0x47cUL
    uint32_t : 32;        // offset 0x480UL
    uint32_t : 32;        // offset 0x484UL
    uint32_t : 32;        // offset 0x488UL
    uint32_t : 32;        // offset 0x48cUL
    uint32_t : 32;        // offset 0x490UL
    uint32_t : 32;        // offset 0x494UL
    uint32_t : 32;        // offset 0x498UL
    uint32_t : 32;        // offset 0x49cUL
    uint32_t : 32;        // offset 0x4a0UL
    uint32_t : 32;        // offset 0x4a4UL
    uint32_t : 32;        // offset 0x4a8UL
    uint32_t : 32;        // offset 0x4acUL
    uint32_t : 32;        // offset 0x4b0UL
    uint32_t : 32;        // offset 0x4b4UL
    uint32_t : 32;        // offset 0x4b8UL
    uint32_t : 32;        // offset 0x4bcUL
    uint32_t : 32;        // offset 0x4c0UL
    uint32_t : 32;        // offset 0x4c4UL
    uint32_t : 32;        // offset 0x4c8UL
    uint32_t : 32;        // offset 0x4ccUL
    uint32_t : 32;        // offset 0x4d0UL
    uint32_t : 32;        // offset 0x4d4UL
    uint32_t : 32;        // offset 0x4d8UL
    uint32_t : 32;        // offset 0x4dcUL
    uint32_t : 32;        // offset 0x4e0UL
    uint32_t : 32;        // offset 0x4e4UL
    uint32_t : 32;        // offset 0x4e8UL
    uint32_t : 32;        // offset 0x4ecUL
    uint32_t : 32;        // offset 0x4f0UL
    uint32_t : 32;        // offset 0x4f4UL
    uint32_t : 32;        // offset 0x4f8UL
    uint32_t : 32;        // offset 0x4fcUL
    uint32_t : 32;        // offset 0x500UL
    uint32_t : 32;        // offset 0x504UL
    uint32_t : 32;        // offset 0x508UL
    uint32_t : 32;        // offset 0x50cUL
    uint32_t : 32;        // offset 0x510UL
    uint32_t : 32;        // offset 0x514UL
    uint32_t : 32;        // offset 0x518UL
    uint32_t : 32;        // offset 0x51cUL
    uint32_t : 32;        // offset 0x520UL
    uint32_t : 32;        // offset 0x524UL
    uint32_t : 32;        // offset 0x528UL
    uint32_t : 32;        // offset 0x52cUL
    uint32_t : 32;        // offset 0x530UL
    uint32_t : 32;        // offset 0x534UL
    uint32_t : 32;        // offset 0x538UL
    uint32_t : 32;        // offset 0x53cUL
    uint32_t : 32;        // offset 0x540UL
    uint32_t : 32;        // offset 0x544UL
    uint32_t : 32;        // offset 0x548UL
    uint32_t : 32;        // offset 0x54cUL
    uint32_t : 32;        // offset 0x550UL
    uint32_t : 32;        // offset 0x554UL
    uint32_t : 32;        // offset 0x558UL
    uint32_t : 32;        // offset 0x55cUL
    uint32_t : 32;        // offset 0x560UL
    uint32_t : 32;        // offset 0x564UL
    uint32_t : 32;        // offset 0x568UL
    uint32_t : 32;        // offset 0x56cUL
    uint32_t : 32;        // offset 0x570UL
    uint32_t : 32;        // offset 0x574UL
    uint32_t : 32;        // offset 0x578UL
    uint32_t : 32;        // offset 0x57cUL
    uint32_t : 32;        // offset 0x580UL
    uint32_t : 32;        // offset 0x584UL
    uint32_t : 32;        // offset 0x588UL
    uint32_t : 32;        // offset 0x58cUL
    uint32_t : 32;        // offset 0x590UL
    uint32_t : 32;        // offset 0x594UL
    uint32_t : 32;        // offset 0x598UL
    uint32_t : 32;        // offset 0x59cUL
    uint32_t : 32;        // offset 0x5a0UL
    uint32_t : 32;        // offset 0x5a4UL
    uint32_t : 32;        // offset 0x5a8UL
    uint32_t : 32;        // offset 0x5acUL
    uint32_t : 32;        // offset 0x5b0UL
    uint32_t : 32;        // offset 0x5b4UL
    uint32_t : 32;        // offset 0x5b8UL
    uint32_t : 32;        // offset 0x5bcUL
    uint32_t : 32;        // offset 0x5c0UL
    uint32_t : 32;        // offset 0x5c4UL
    uint32_t : 32;        // offset 0x5c8UL
    uint32_t : 32;        // offset 0x5ccUL
    uint32_t : 32;        // offset 0x5d0UL
    uint32_t : 32;        // offset 0x5d4UL
    uint32_t : 32;        // offset 0x5d8UL
    uint32_t : 32;        // offset 0x5dcUL
    uint32_t : 32;        // offset 0x5e0UL
    uint32_t : 32;        // offset 0x5e4UL
    uint32_t : 32;        // offset 0x5e8UL
    uint32_t : 32;        // offset 0x5ecUL
    uint32_t : 32;        // offset 0x5f0UL
    uint32_t : 32;        // offset 0x5f4UL
    uint32_t : 32;        // offset 0x5f8UL
    uint32_t : 32;        // offset 0x5fcUL
    uint32_t : 32;        // offset 0x600UL
    uint32_t : 32;        // offset 0x604UL
    uint32_t : 32;        // offset 0x608UL
    uint32_t : 32;        // offset 0x60cUL
    uint32_t : 32;        // offset 0x610UL
    uint32_t : 32;        // offset 0x614UL
    uint32_t : 32;        // offset 0x618UL
    uint32_t : 32;        // offset 0x61cUL
    uint32_t : 32;        // offset 0x620UL
    uint32_t : 32;        // offset 0x624UL
    uint32_t : 32;        // offset 0x628UL
    uint32_t : 32;        // offset 0x62cUL
    uint32_t : 32;        // offset 0x630UL
    uint32_t : 32;        // offset 0x634UL
    uint32_t : 32;        // offset 0x638UL
    uint32_t : 32;        // offset 0x63cUL
    uint32_t : 32;        // offset 0x640UL
    uint32_t : 32;        // offset 0x644UL
    uint32_t : 32;        // offset 0x648UL
    uint32_t : 32;        // offset 0x64cUL
    uint32_t : 32;        // offset 0x650UL
    uint32_t : 32;        // offset 0x654UL
    uint32_t : 32;        // offset 0x658UL
    uint32_t : 32;        // offset 0x65cUL
    uint32_t : 32;        // offset 0x660UL
    uint32_t : 32;        // offset 0x664UL
    uint32_t : 32;        // offset 0x668UL
    uint32_t : 32;        // offset 0x66cUL
    uint32_t : 32;        // offset 0x670UL
    uint32_t : 32;        // offset 0x674UL
    uint32_t : 32;        // offset 0x678UL
    uint32_t : 32;        // offset 0x67cUL
    uint32_t : 32;        // offset 0x680UL
    uint32_t : 32;        // offset 0x684UL
    uint32_t : 32;        // offset 0x688UL
    uint32_t : 32;        // offset 0x68cUL
    uint32_t : 32;        // offset 0x690UL
    uint32_t : 32;        // offset 0x694UL
    uint32_t : 32;        // offset 0x698UL
    uint32_t : 32;        // offset 0x69cUL
    uint32_t : 32;        // offset 0x6a0UL
    uint32_t : 32;        // offset 0x6a4UL
    uint32_t : 32;        // offset 0x6a8UL
    uint32_t : 32;        // offset 0x6acUL
    uint32_t : 32;        // offset 0x6b0UL
    uint32_t : 32;        // offset 0x6b4UL
    uint32_t : 32;        // offset 0x6b8UL
    uint32_t : 32;        // offset 0x6bcUL
    uint32_t : 32;        // offset 0x6c0UL
    uint32_t : 32;        // offset 0x6c4UL
    uint32_t : 32;        // offset 0x6c8UL
    uint32_t : 32;        // offset 0x6ccUL
    uint32_t : 32;        // offset 0x6d0UL
    uint32_t : 32;        // offset 0x6d4UL
    uint32_t : 32;        // offset 0x6d8UL
    uint32_t : 32;        // offset 0x6dcUL
    uint32_t : 32;        // offset 0x6e0UL
    uint32_t : 32;        // offset 0x6e4UL
    uint32_t : 32;        // offset 0x6e8UL
    uint32_t : 32;        // offset 0x6ecUL
    uint32_t : 32;        // offset 0x6f0UL
    uint32_t : 32;        // offset 0x6f4UL
    uint32_t : 32;        // offset 0x6f8UL
    uint32_t : 32;        // offset 0x6fcUL
    uint32_t : 32;        // offset 0x700UL
    uint32_t : 32;        // offset 0x704UL
    uint32_t : 32;        // offset 0x708UL
    uint32_t : 32;        // offset 0x70cUL
    uint32_t : 32;        // offset 0x710UL
    uint32_t : 32;        // offset 0x714UL
    uint32_t : 32;        // offset 0x718UL
    uint32_t : 32;        // offset 0x71cUL
    uint32_t : 32;        // offset 0x720UL
    uint32_t : 32;        // offset 0x724UL
    uint32_t : 32;        // offset 0x728UL
    uint32_t : 32;        // offset 0x72cUL
    uint32_t : 32;        // offset 0x730UL
    uint32_t : 32;        // offset 0x734UL
    uint32_t : 32;        // offset 0x738UL
    uint32_t : 32;        // offset 0x73cUL
    uint32_t : 32;        // offset 0x740UL
    uint32_t : 32;        // offset 0x744UL
    uint32_t : 32;        // offset 0x748UL
    uint32_t : 32;        // offset 0x74cUL
    uint32_t : 32;        // offset 0x750UL
    uint32_t : 32;        // offset 0x754UL
    uint32_t : 32;        // offset 0x758UL
    uint32_t : 32;        // offset 0x75cUL
    uint32_t : 32;        // offset 0x760UL
    uint32_t : 32;        // offset 0x764UL
    uint32_t : 32;        // offset 0x768UL
    uint32_t : 32;        // offset 0x76cUL
    uint32_t : 32;        // offset 0x770UL
    uint32_t : 32;        // offset 0x774UL
    uint32_t : 32;        // offset 0x778UL
    uint32_t : 32;        // offset 0x77cUL
    uint32_t : 32;        // offset 0x780UL
    uint32_t : 32;        // offset 0x784UL
    uint32_t : 32;        // offset 0x788UL
    uint32_t : 32;        // offset 0x78cUL
    uint32_t : 32;        // offset 0x790UL
    uint32_t : 32;        // offset 0x794UL
    uint32_t : 32;        // offset 0x798UL
    uint32_t : 32;        // offset 0x79cUL
    uint32_t : 32;        // offset 0x7a0UL
    uint32_t : 32;        // offset 0x7a4UL
    uint32_t : 32;        // offset 0x7a8UL
    uint32_t : 32;        // offset 0x7acUL
    uint32_t : 32;        // offset 0x7b0UL
    uint32_t : 32;        // offset 0x7b4UL
    uint32_t : 32;        // offset 0x7b8UL
    uint32_t : 32;        // offset 0x7bcUL
    uint32_t : 32;        // offset 0x7c0UL
    uint32_t : 32;        // offset 0x7c4UL
    uint32_t : 32;        // offset 0x7c8UL
    uint32_t : 32;        // offset 0x7ccUL
    uint32_t : 32;        // offset 0x7d0UL
    uint32_t : 32;        // offset 0x7d4UL
    uint32_t : 32;        // offset 0x7d8UL
    uint32_t : 32;        // offset 0x7dcUL
    uint32_t : 32;        // offset 0x7e0UL
    uint32_t : 32;        // offset 0x7e4UL
    uint32_t : 32;        // offset 0x7e8UL
    uint32_t : 32;        // offset 0x7ecUL
    uint32_t : 32;        // offset 0x7f0UL
    uint32_t : 32;        // offset 0x7f4UL
    uint32_t : 32;        // offset 0x7f8UL
    uint32_t : 32;        // offset 0x7fcUL
    uint32_t : 32;        // offset 0x800UL
    uint32_t : 32;        // offset 0x804UL
    uint32_t : 32;        // offset 0x808UL
    uint32_t : 32;        // offset 0x80cUL
    uint32_t : 32;        // offset 0x810UL
    uint32_t : 32;        // offset 0x814UL
    uint32_t : 32;        // offset 0x818UL
    uint32_t : 32;        // offset 0x81cUL
    uint32_t : 32;        // offset 0x820UL
    uint32_t : 32;        // offset 0x824UL
    uint32_t : 32;        // offset 0x828UL
    uint32_t : 32;        // offset 0x82cUL
    uint32_t : 32;        // offset 0x830UL
    uint32_t : 32;        // offset 0x834UL
    uint32_t : 32;        // offset 0x838UL
    uint32_t : 32;        // offset 0x83cUL
    uint32_t : 32;        // offset 0x840UL
    uint32_t : 32;        // offset 0x844UL
    uint32_t : 32;        // offset 0x848UL
    uint32_t : 32;        // offset 0x84cUL
    uint32_t : 32;        // offset 0x850UL
    uint32_t : 32;        // offset 0x854UL
    uint32_t : 32;        // offset 0x858UL
    uint32_t : 32;        // offset 0x85cUL
    uint32_t : 32;        // offset 0x860UL
    uint32_t : 32;        // offset 0x864UL
    uint32_t : 32;        // offset 0x868UL
    uint32_t : 32;        // offset 0x86cUL
    uint32_t : 32;        // offset 0x870UL
    uint32_t : 32;        // offset 0x874UL
    uint32_t : 32;        // offset 0x878UL
    uint32_t : 32;        // offset 0x87cUL
    uint32_t : 32;        // offset 0x880UL
    uint32_t : 32;        // offset 0x884UL
    uint32_t : 32;        // offset 0x888UL
    uint32_t : 32;        // offset 0x88cUL
    uint32_t : 32;        // offset 0x890UL
    uint32_t : 32;        // offset 0x894UL
    uint32_t : 32;        // offset 0x898UL
    uint32_t : 32;        // offset 0x89cUL
    uint32_t : 32;        // offset 0x8a0UL
    uint32_t : 32;        // offset 0x8a4UL
    uint32_t : 32;        // offset 0x8a8UL
    uint32_t : 32;        // offset 0x8acUL
    uint32_t : 32;        // offset 0x8b0UL
    uint32_t : 32;        // offset 0x8b4UL
    uint32_t : 32;        // offset 0x8b8UL
    uint32_t : 32;        // offset 0x8bcUL
    uint32_t : 32;        // offset 0x8c0UL
    uint32_t : 32;        // offset 0x8c4UL
    uint32_t : 32;        // offset 0x8c8UL
    uint32_t : 32;        // offset 0x8ccUL
    uint32_t : 32;        // offset 0x8d0UL
    uint32_t : 32;        // offset 0x8d4UL
    uint32_t : 32;        // offset 0x8d8UL
    uint32_t : 32;        // offset 0x8dcUL
    uint32_t : 32;        // offset 0x8e0UL
    uint32_t : 32;        // offset 0x8e4UL
    uint32_t : 32;        // offset 0x8e8UL
    uint32_t : 32;        // offset 0x8ecUL
    uint32_t : 32;        // offset 0x8f0UL
    uint32_t : 32;        // offset 0x8f4UL
    uint32_t : 32;        // offset 0x8f8UL
    uint32_t : 32;        // offset 0x8fcUL
    uint32_t : 32;        // offset 0x900UL
    uint32_t : 32;        // offset 0x904UL
    uint32_t : 32;        // offset 0x908UL
    uint32_t : 32;        // offset 0x90cUL
    uint32_t : 32;        // offset 0x910UL
    uint32_t : 32;        // offset 0x914UL
    uint32_t : 32;        // offset 0x918UL
    uint32_t : 32;        // offset 0x91cUL
    uint32_t : 32;        // offset 0x920UL
    uint32_t : 32;        // offset 0x924UL
    uint32_t : 32;        // offset 0x928UL
    uint32_t : 32;        // offset 0x92cUL
    uint32_t : 32;        // offset 0x930UL
    uint32_t : 32;        // offset 0x934UL
    uint32_t : 32;        // offset 0x938UL
    uint32_t : 32;        // offset 0x93cUL
    uint32_t : 32;        // offset 0x940UL
    uint32_t : 32;        // offset 0x944UL
    uint32_t : 32;        // offset 0x948UL
    uint32_t : 32;        // offset 0x94cUL
    uint32_t : 32;        // offset 0x950UL
    uint32_t : 32;        // offset 0x954UL
    uint32_t : 32;        // offset 0x958UL
    uint32_t : 32;        // offset 0x95cUL
    uint32_t : 32;        // offset 0x960UL
    uint32_t : 32;        // offset 0x964UL
    uint32_t : 32;        // offset 0x968UL
    uint32_t : 32;        // offset 0x96cUL
    uint32_t : 32;        // offset 0x970UL
    uint32_t : 32;        // offset 0x974UL
    uint32_t : 32;        // offset 0x978UL
    uint32_t : 32;        // offset 0x97cUL
    uint32_t : 32;        // offset 0x980UL
    uint32_t : 32;        // offset 0x984UL
    uint32_t : 32;        // offset 0x988UL
    uint32_t : 32;        // offset 0x98cUL
    uint32_t : 32;        // offset 0x990UL
    uint32_t : 32;        // offset 0x994UL
    uint32_t : 32;        // offset 0x998UL
    uint32_t : 32;        // offset 0x99cUL
    uint32_t : 32;        // offset 0x9a0UL
    uint32_t : 32;        // offset 0x9a4UL
    uint32_t : 32;        // offset 0x9a8UL
    uint32_t : 32;        // offset 0x9acUL
    uint32_t : 32;        // offset 0x9b0UL
    uint32_t : 32;        // offset 0x9b4UL
    uint32_t : 32;        // offset 0x9b8UL
    uint32_t : 32;        // offset 0x9bcUL
    uint32_t : 32;        // offset 0x9c0UL
    uint32_t : 32;        // offset 0x9c4UL
    uint32_t : 32;        // offset 0x9c8UL
    uint32_t : 32;        // offset 0x9ccUL
    uint32_t : 32;        // offset 0x9d0UL
    uint32_t : 32;        // offset 0x9d4UL
    uint32_t : 32;        // offset 0x9d8UL
    uint32_t : 32;        // offset 0x9dcUL
    uint32_t : 32;        // offset 0x9e0UL
    uint32_t : 32;        // offset 0x9e4UL
    uint32_t : 32;        // offset 0x9e8UL
    uint32_t : 32;        // offset 0x9ecUL
    uint32_t : 32;        // offset 0x9f0UL
    uint32_t : 32;        // offset 0x9f4UL
    uint32_t : 32;        // offset 0x9f8UL
    uint32_t : 32;        // offset 0x9fcUL
    uint32_t : 32;        // offset 0xa00UL
    uint32_t : 32;        // offset 0xa04UL
    uint32_t : 32;        // offset 0xa08UL
    uint32_t : 32;        // offset 0xa0cUL
    uint32_t : 32;        // offset 0xa10UL
    uint32_t : 32;        // offset 0xa14UL
    uint32_t : 32;        // offset 0xa18UL
    uint32_t : 32;        // offset 0xa1cUL
    uint32_t : 32;        // offset 0xa20UL
    uint32_t : 32;        // offset 0xa24UL
    uint32_t : 32;        // offset 0xa28UL
    uint32_t : 32;        // offset 0xa2cUL
    uint32_t : 32;        // offset 0xa30UL
    uint32_t : 32;        // offset 0xa34UL
    uint32_t : 32;        // offset 0xa38UL
    uint32_t : 32;        // offset 0xa3cUL
    uint32_t : 32;        // offset 0xa40UL
    uint32_t : 32;        // offset 0xa44UL
    uint32_t : 32;        // offset 0xa48UL
    uint32_t : 32;        // offset 0xa4cUL
    uint32_t : 32;        // offset 0xa50UL
    uint32_t : 32;        // offset 0xa54UL
    uint32_t : 32;        // offset 0xa58UL
    uint32_t : 32;        // offset 0xa5cUL
    uint32_t : 32;        // offset 0xa60UL
    uint32_t : 32;        // offset 0xa64UL
    uint32_t : 32;        // offset 0xa68UL
    uint32_t : 32;        // offset 0xa6cUL
    uint32_t : 32;        // offset 0xa70UL
    uint32_t : 32;        // offset 0xa74UL
    uint32_t : 32;        // offset 0xa78UL
    uint32_t : 32;        // offset 0xa7cUL
    uint32_t : 32;        // offset 0xa80UL
    uint32_t : 32;        // offset 0xa84UL
    uint32_t : 32;        // offset 0xa88UL
    uint32_t : 32;        // offset 0xa8cUL
    uint32_t : 32;        // offset 0xa90UL
    uint32_t : 32;        // offset 0xa94UL
    uint32_t : 32;        // offset 0xa98UL
    uint32_t : 32;        // offset 0xa9cUL
    uint32_t : 32;        // offset 0xaa0UL
    uint32_t : 32;        // offset 0xaa4UL
    uint32_t : 32;        // offset 0xaa8UL
    uint32_t : 32;        // offset 0xaacUL
    uint32_t : 32;        // offset 0xab0UL
    uint32_t : 32;        // offset 0xab4UL
    uint32_t : 32;        // offset 0xab8UL
    uint32_t : 32;        // offset 0xabcUL
    uint32_t : 32;        // offset 0xac0UL
    uint32_t : 32;        // offset 0xac4UL
    uint32_t : 32;        // offset 0xac8UL
    uint32_t : 32;        // offset 0xaccUL
    uint32_t : 32;        // offset 0xad0UL
    uint32_t : 32;        // offset 0xad4UL
    uint32_t : 32;        // offset 0xad8UL
    uint32_t : 32;        // offset 0xadcUL
    uint32_t : 32;        // offset 0xae0UL
    uint32_t : 32;        // offset 0xae4UL
    uint32_t : 32;        // offset 0xae8UL
    uint32_t : 32;        // offset 0xaecUL
    uint32_t : 32;        // offset 0xaf0UL
    uint32_t : 32;        // offset 0xaf4UL
    uint32_t : 32;        // offset 0xaf8UL
    uint32_t : 32;        // offset 0xafcUL
    uint32_t : 32;        // offset 0xb00UL
    uint32_t : 32;        // offset 0xb04UL
    uint32_t : 32;        // offset 0xb08UL
    uint32_t : 32;        // offset 0xb0cUL
    uint32_t : 32;        // offset 0xb10UL
    uint32_t : 32;        // offset 0xb14UL
    uint32_t : 32;        // offset 0xb18UL
    uint32_t : 32;        // offset 0xb1cUL
    uint32_t : 32;        // offset 0xb20UL
    uint32_t : 32;        // offset 0xb24UL
    uint32_t : 32;        // offset 0xb28UL
    uint32_t : 32;        // offset 0xb2cUL
    uint32_t : 32;        // offset 0xb30UL
    uint32_t : 32;        // offset 0xb34UL
    uint32_t : 32;        // offset 0xb38UL
    uint32_t : 32;        // offset 0xb3cUL
    uint32_t : 32;        // offset 0xb40UL
    uint32_t : 32;        // offset 0xb44UL
    uint32_t : 32;        // offset 0xb48UL
    uint32_t : 32;        // offset 0xb4cUL
    uint32_t : 32;        // offset 0xb50UL
    uint32_t : 32;        // offset 0xb54UL
    uint32_t : 32;        // offset 0xb58UL
    uint32_t : 32;        // offset 0xb5cUL
    uint32_t : 32;        // offset 0xb60UL
    uint32_t : 32;        // offset 0xb64UL
    uint32_t : 32;        // offset 0xb68UL
    uint32_t : 32;        // offset 0xb6cUL
    uint32_t : 32;        // offset 0xb70UL
    uint32_t : 32;        // offset 0xb74UL
    uint32_t : 32;        // offset 0xb78UL
    uint32_t : 32;        // offset 0xb7cUL
    uint32_t : 32;        // offset 0xb80UL
    uint32_t : 32;        // offset 0xb84UL
    uint32_t : 32;        // offset 0xb88UL
    uint32_t : 32;        // offset 0xb8cUL
    uint32_t : 32;        // offset 0xb90UL
    uint32_t : 32;        // offset 0xb94UL
    uint32_t : 32;        // offset 0xb98UL
    uint32_t : 32;        // offset 0xb9cUL
    uint32_t : 32;        // offset 0xba0UL
    uint32_t : 32;        // offset 0xba4UL
    uint32_t : 32;        // offset 0xba8UL
    uint32_t : 32;        // offset 0xbacUL
    uint32_t : 32;        // offset 0xbb0UL
    uint32_t : 32;        // offset 0xbb4UL
    uint32_t : 32;        // offset 0xbb8UL
    uint32_t : 32;        // offset 0xbbcUL
    uint32_t : 32;        // offset 0xbc0UL
    uint32_t : 32;        // offset 0xbc4UL
    uint32_t : 32;        // offset 0xbc8UL
    uint32_t : 32;        // offset 0xbccUL
    uint32_t : 32;        // offset 0xbd0UL
    uint32_t : 32;        // offset 0xbd4UL
    uint32_t : 32;        // offset 0xbd8UL
    uint32_t : 32;        // offset 0xbdcUL
    uint32_t : 32;        // offset 0xbe0UL
    uint32_t : 32;        // offset 0xbe4UL
    uint32_t : 32;        // offset 0xbe8UL
    uint32_t : 32;        // offset 0xbecUL
    uint32_t : 32;        // offset 0xbf0UL
    uint32_t : 32;        // offset 0xbf4UL
    uint32_t : 32;        // offset 0xbf8UL
    uint32_t : 32;        // offset 0xbfcUL
    uint32_t : 32;        // offset 0xc00UL
    uint32_t : 32;        // offset 0xc04UL
    uint32_t : 32;        // offset 0xc08UL
    uint32_t : 32;        // offset 0xc0cUL
    uint32_t : 32;        // offset 0xc10UL
    uint32_t : 32;        // offset 0xc14UL
    uint32_t : 32;        // offset 0xc18UL
    uint32_t : 32;        // offset 0xc1cUL
    uint32_t : 32;        // offset 0xc20UL
    uint32_t : 32;        // offset 0xc24UL
    uint32_t : 32;        // offset 0xc28UL
    uint32_t : 32;        // offset 0xc2cUL
    uint32_t : 32;        // offset 0xc30UL
    uint32_t : 32;        // offset 0xc34UL
    uint32_t : 32;        // offset 0xc38UL
    uint32_t : 32;        // offset 0xc3cUL
    uint32_t : 32;        // offset 0xc40UL
    uint32_t : 32;        // offset 0xc44UL
    uint32_t : 32;        // offset 0xc48UL
    uint32_t : 32;        // offset 0xc4cUL
    uint32_t : 32;        // offset 0xc50UL
    uint32_t : 32;        // offset 0xc54UL
    uint32_t : 32;        // offset 0xc58UL
    uint32_t : 32;        // offset 0xc5cUL
    uint32_t : 32;        // offset 0xc60UL
    uint32_t : 32;        // offset 0xc64UL
    uint32_t : 32;        // offset 0xc68UL
    uint32_t : 32;        // offset 0xc6cUL
    uint32_t : 32;        // offset 0xc70UL
    uint32_t : 32;        // offset 0xc74UL
    uint32_t : 32;        // offset 0xc78UL
    uint32_t : 32;        // offset 0xc7cUL
    uint32_t : 32;        // offset 0xc80UL
    uint32_t : 32;        // offset 0xc84UL
    uint32_t : 32;        // offset 0xc88UL
    uint32_t : 32;        // offset 0xc8cUL
    uint32_t : 32;        // offset 0xc90UL
    uint32_t : 32;        // offset 0xc94UL
    uint32_t : 32;        // offset 0xc98UL
    uint32_t : 32;        // offset 0xc9cUL
    uint32_t : 32;        // offset 0xca0UL
    uint32_t : 32;        // offset 0xca4UL
    uint32_t : 32;        // offset 0xca8UL
    uint32_t : 32;        // offset 0xcacUL
    uint32_t : 32;        // offset 0xcb0UL
    uint32_t : 32;        // offset 0xcb4UL
    uint32_t : 32;        // offset 0xcb8UL
    uint32_t : 32;        // offset 0xcbcUL
    uint32_t : 32;        // offset 0xcc0UL
    uint32_t : 32;        // offset 0xcc4UL
    uint32_t : 32;        // offset 0xcc8UL
    uint32_t : 32;        // offset 0xcccUL
    uint32_t : 32;        // offset 0xcd0UL
    uint32_t : 32;        // offset 0xcd4UL
    uint32_t : 32;        // offset 0xcd8UL
    uint32_t : 32;        // offset 0xcdcUL
    uint32_t : 32;        // offset 0xce0UL
    uint32_t : 32;        // offset 0xce4UL
    uint32_t : 32;        // offset 0xce8UL
    uint32_t : 32;        // offset 0xcecUL
    uint32_t : 32;        // offset 0xcf0UL
    uint32_t : 32;        // offset 0xcf4UL
    uint32_t : 32;        // offset 0xcf8UL
    uint32_t : 32;        // offset 0xcfcUL
    uint32_t : 32;        // offset 0xd00UL
    uint32_t : 32;        // offset 0xd04UL
    uint32_t : 32;        // offset 0xd08UL
    uint32_t : 32;        // offset 0xd0cUL
    uint32_t : 32;        // offset 0xd10UL
    uint32_t : 32;        // offset 0xd14UL
    uint32_t : 32;        // offset 0xd18UL
    uint32_t : 32;        // offset 0xd1cUL
    uint32_t : 32;        // offset 0xd20UL
    uint32_t : 32;        // offset 0xd24UL
    uint32_t : 32;        // offset 0xd28UL
    uint32_t : 32;        // offset 0xd2cUL
    uint32_t : 32;        // offset 0xd30UL
    uint32_t : 32;        // offset 0xd34UL
    uint32_t : 32;        // offset 0xd38UL
    uint32_t : 32;        // offset 0xd3cUL
    uint32_t : 32;        // offset 0xd40UL
    uint32_t : 32;        // offset 0xd44UL
    uint32_t : 32;        // offset 0xd48UL
    uint32_t : 32;        // offset 0xd4cUL
    uint32_t : 32;        // offset 0xd50UL
    uint32_t : 32;        // offset 0xd54UL
    uint32_t : 32;        // offset 0xd58UL
    uint32_t : 32;        // offset 0xd5cUL
    uint32_t : 32;        // offset 0xd60UL
    uint32_t : 32;        // offset 0xd64UL
    uint32_t : 32;        // offset 0xd68UL
    uint32_t : 32;        // offset 0xd6cUL
    uint32_t : 32;        // offset 0xd70UL
    uint32_t : 32;        // offset 0xd74UL
    uint32_t : 32;        // offset 0xd78UL
    uint32_t : 32;        // offset 0xd7cUL
    uint32_t : 32;        // offset 0xd80UL
    uint32_t : 32;        // offset 0xd84UL
    uint32_t : 32;        // offset 0xd88UL
    uint32_t : 32;        // offset 0xd8cUL
    uint32_t : 32;        // offset 0xd90UL
    uint32_t : 32;        // offset 0xd94UL
    uint32_t : 32;        // offset 0xd98UL
    uint32_t : 32;        // offset 0xd9cUL
    uint32_t : 32;        // offset 0xda0UL
    uint32_t : 32;        // offset 0xda4UL
    uint32_t : 32;        // offset 0xda8UL
    uint32_t : 32;        // offset 0xdacUL
    uint32_t : 32;        // offset 0xdb0UL
    uint32_t : 32;        // offset 0xdb4UL
    uint32_t : 32;        // offset 0xdb8UL
    uint32_t : 32;        // offset 0xdbcUL
    uint32_t : 32;        // offset 0xdc0UL
    uint32_t : 32;        // offset 0xdc4UL
    uint32_t : 32;        // offset 0xdc8UL
    uint32_t : 32;        // offset 0xdccUL
    uint32_t : 32;        // offset 0xdd0UL
    uint32_t : 32;        // offset 0xdd4UL
    uint32_t : 32;        // offset 0xdd8UL
    uint32_t : 32;        // offset 0xddcUL
    uint32_t : 32;        // offset 0xde0UL
    uint32_t : 32;        // offset 0xde4UL
    uint32_t : 32;        // offset 0xde8UL
    uint32_t : 32;        // offset 0xdecUL
    uint32_t : 32;        // offset 0xdf0UL
    uint32_t : 32;        // offset 0xdf4UL
    uint32_t : 32;        // offset 0xdf8UL
    uint32_t : 32;        // offset 0xdfcUL
    uint32_t : 32;        // offset 0xe00UL
    uint32_t : 32;        // offset 0xe04UL
    uint32_t : 32;        // offset 0xe08UL
    uint32_t : 32;        // offset 0xe0cUL
    uint32_t : 32;        // offset 0xe10UL
    uint32_t : 32;        // offset 0xe14UL
    uint32_t : 32;        // offset 0xe18UL
    uint32_t : 32;        // offset 0xe1cUL
    uint32_t : 32;        // offset 0xe20UL
    uint32_t : 32;        // offset 0xe24UL
    uint32_t : 32;        // offset 0xe28UL
    uint32_t : 32;        // offset 0xe2cUL
    uint32_t : 32;        // offset 0xe30UL
    uint32_t : 32;        // offset 0xe34UL
    uint32_t : 32;        // offset 0xe38UL
    uint32_t : 32;        // offset 0xe3cUL
    uint32_t : 32;        // offset 0xe40UL
    uint32_t : 32;        // offset 0xe44UL
    uint32_t : 32;        // offset 0xe48UL
    uint32_t : 32;        // offset 0xe4cUL
    uint32_t : 32;        // offset 0xe50UL
    uint32_t : 32;        // offset 0xe54UL
    uint32_t : 32;        // offset 0xe58UL
    uint32_t : 32;        // offset 0xe5cUL
    uint32_t : 32;        // offset 0xe60UL
    uint32_t : 32;        // offset 0xe64UL
    uint32_t : 32;        // offset 0xe68UL
    uint32_t : 32;        // offset 0xe6cUL
    uint32_t : 32;        // offset 0xe70UL
    uint32_t : 32;        // offset 0xe74UL
    uint32_t : 32;        // offset 0xe78UL
    uint32_t : 32;        // offset 0xe7cUL
    uint32_t : 32;        // offset 0xe80UL
    uint32_t : 32;        // offset 0xe84UL
    uint32_t : 32;        // offset 0xe88UL
    uint32_t : 32;        // offset 0xe8cUL
    uint32_t : 32;        // offset 0xe90UL
    uint32_t : 32;        // offset 0xe94UL
    uint32_t : 32;        // offset 0xe98UL
    uint32_t : 32;        // offset 0xe9cUL
    uint32_t : 32;        // offset 0xea0UL
    uint32_t : 32;        // offset 0xea4UL
    uint32_t : 32;        // offset 0xea8UL
    uint32_t : 32;        // offset 0xeacUL
    uint32_t : 32;        // offset 0xeb0UL
    uint32_t : 32;        // offset 0xeb4UL
    uint32_t : 32;        // offset 0xeb8UL
    uint32_t : 32;        // offset 0xebcUL
    uint32_t : 32;        // offset 0xec0UL
    uint32_t : 32;        // offset 0xec4UL
    uint32_t : 32;        // offset 0xec8UL
    uint32_t : 32;        // offset 0xeccUL
    uint32_t : 32;        // offset 0xed0UL
    uint32_t : 32;        // offset 0xed4UL
    uint32_t : 32;        // offset 0xed8UL
    uint32_t : 32;        // offset 0xedcUL
    uint32_t : 32;        // offset 0xee0UL
    uint32_t : 32;        // offset 0xee4UL
    uint32_t : 32;        // offset 0xee8UL
    uint32_t : 32;        // offset 0xeecUL
    uint32_t : 32;        // offset 0xef0UL
    uint32_t : 32;        // offset 0xef4UL
    uint32_t : 32;        // offset 0xef8UL
    uint32_t : 32;        // offset 0xefcUL
    uint32_t : 32;        // offset 0xf00UL
    uint32_t : 32;        // offset 0xf04UL
    uint32_t : 32;        // offset 0xf08UL
    uint32_t : 32;        // offset 0xf0cUL
    uint32_t : 32;        // offset 0xf10UL
    uint32_t : 32;        // offset 0xf14UL
    uint32_t : 32;        // offset 0xf18UL
    uint32_t : 32;        // offset 0xf1cUL
    uint32_t : 32;        // offset 0xf20UL
    uint32_t : 32;        // offset 0xf24UL
    uint32_t : 32;        // offset 0xf28UL
    uint32_t : 32;        // offset 0xf2cUL
    uint32_t : 32;        // offset 0xf30UL
    uint32_t : 32;        // offset 0xf34UL
    uint32_t : 32;        // offset 0xf38UL
    uint32_t : 32;        // offset 0xf3cUL
    uint32_t : 32;        // offset 0xf40UL
    uint32_t : 32;        // offset 0xf44UL
    uint32_t : 32;        // offset 0xf48UL
    uint32_t : 32;        // offset 0xf4cUL
    uint32_t : 32;        // offset 0xf50UL
    uint32_t : 32;        // offset 0xf54UL
    uint32_t : 32;        // offset 0xf58UL
    uint32_t : 32;        // offset 0xf5cUL
    uint32_t : 32;        // offset 0xf60UL
    uint32_t : 32;        // offset 0xf64UL
    uint32_t : 32;        // offset 0xf68UL
    uint32_t : 32;        // offset 0xf6cUL
    uint32_t : 32;        // offset 0xf70UL
    uint32_t : 32;        // offset 0xf74UL
    uint32_t : 32;        // offset 0xf78UL
    uint32_t : 32;        // offset 0xf7cUL
    uint32_t : 32;        // offset 0xf80UL
    uint32_t : 32;        // offset 0xf84UL
    uint32_t : 32;        // offset 0xf88UL
    uint32_t : 32;        // offset 0xf8cUL
    uint32_t : 32;        // offset 0xf90UL
    uint32_t : 32;        // offset 0xf94UL
    uint32_t : 32;        // offset 0xf98UL
    uint32_t : 32;        // offset 0xf9cUL
    uint32_t : 32;        // offset 0xfa0UL
    uint32_t : 32;        // offset 0xfa4UL
    uint32_t : 32;        // offset 0xfa8UL
    uint32_t : 32;        // offset 0xfacUL
    uint32_t : 32;        // offset 0xfb0UL
    uint32_t : 32;        // offset 0xfb4UL
    uint32_t : 32;        // offset 0xfb8UL
    uint32_t : 32;        // offset 0xfbcUL
    uint32_t : 32;        // offset 0xfc0UL
    uint32_t : 32;        // offset 0xfc4UL
    uint32_t : 32;        // offset 0xfc8UL
    uint32_t : 32;        // offset 0xfccUL
    uint32_t : 32;        // offset 0xfd0UL
    uint32_t : 32;        // offset 0xfd4UL
    uint32_t : 32;        // offset 0xfd8UL
    uint32_t : 32;        // offset 0xfdcUL
    uint32_t : 32;        // offset 0xfe0UL
    uint32_t : 32;        // offset 0xfe4UL
    uint32_t : 32;        // offset 0xfe8UL
    uint32_t : 32;        // offset 0xfecUL
    uint32_t : 32;        // offset 0xff0UL
    uint32_t : 32;        // offset 0xff4UL
    uint32_t : 32;        // offset 0xff8UL
    uint32_t : 32;        // offset 0xffcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<FlashControl>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(FlashControl, access_control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, key_bank1) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, option_key) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, control1) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, status1) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, capture_compare1) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optcr) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optsr_cur) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optsr_prg) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optccr) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, prar_cur1) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, prar_prg1) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, scar_cur1) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, scar_prg1) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, wpsn_cur1r) == 0x38UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, wpsn_prg1r) == 0x3cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, boot_curr) == 0x40UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, boot_prgr) == 0x44UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crccr1) == 0x50UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crcsadd1r) == 0x54UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crceadd1r) == 0x58UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crcdatar) == 0x5cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, ecc_fa1r) == 0x60UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, acr_) == 0x100UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, key_bank2) == 0x104UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optkeyr_) == 0x108UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, control2) == 0x10cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, status2) == 0x110UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, capture_compare2) == 0x114UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optcr_) == 0x118UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optsr_cur_) == 0x11cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optsr_prg_) == 0x120UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, optccr_) == 0x124UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, prar_cur2) == 0x128UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, prar_prg2) == 0x12cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, scar_cur2) == 0x130UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, scar_prg2) == 0x134UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, wpsn_cur2r) == 0x138UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, wpsn_prg2r) == 0x13cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, boot_curr_) == 0x140UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, boot_prgr_) == 0x144UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crccr2) == 0x150UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crcsadd2r) == 0x154UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crceadd2r) == 0x158UL, "Must be located at this offset");
static_assert(offsetof(FlashControl, crcdatar_) == 0x15cUL, "Must be located at this offset");
static_assert(offsetof(FlashControl, ecc_fa2r) == 0x160UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(FlashControl) == 0x1000UL, "Must be this exact size");

/// The external volatile flash_control which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern FlashControl volatile flash_control;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_FLASHCONTROL__HPP_
