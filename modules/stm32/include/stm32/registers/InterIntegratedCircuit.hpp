
#ifndef STM32_REGISTERS_INTERINTEGRATEDCIRCUIT_HPP_
#define STM32_REGISTERS_INTERINTEGRATEDCIRCUIT_HPP_

/// @file
/// Auto Generated Structure Definitions for InterIntegratedCircuit from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Inter-integrated circuit (I2C1)
struct InterIntegratedCircuit final {
    /// Control register 1 (CR1)
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
            /// Peripheral enable (PE)
            uint32_t peripheral_enable                  : 1;    // bit 0
            /// SMBus mode (SMBUS)
            uint32_t system_management_bus              : 1;    // bit 1
            /// (reserved)
            uint32_t                                    : 1;    // bit 2
            /// SMBus type (SMBTYPE)
            uint32_t system_management_bus_type         : 1;    // bit 3
            /// ARP enable (ENARP)
            uint32_t enable_address_resolution_protocol : 1;    // bit 4
            /// PEC enable (ENPEC)
            uint32_t enable_packet_error_code           : 1;    // bit 5
            /// General call enable (ENGC)
            uint32_t enable_general_call                : 1;    // bit 6
            /// Clock stretching disable (Slave mode) (NOSTRETCH)
            uint32_t no_stretch                         : 1;    // bit 7
            /// Start generation (START)
            uint32_t start                              : 1;    // bit 8
            /// Stop generation (STOP)
            uint32_t stop                               : 1;    // bit 9
            /// Acknowledge enable (ACK)
            uint32_t acknowledge                        : 1;    // bit 10
            /// Acknowledge/PEC Position (for data reception) (POS)
            uint32_t position                           : 1;    // bit 11
            /// Packet error checking (PEC)
            uint32_t packet_error_checking              : 1;    // bit 12
            /// SMBus alert (ALERT)
            uint32_t alert                              : 1;    // bit 13
            /// (reserved)
            uint32_t                                    : 1;    // bit 14
            /// Software reset (SWRST)
            uint32_t software_reset                     : 1;    // bit 15
            /// (reserved)
            uint32_t                                    : 16;    // bits 16:31
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
    /// Control register 2 (CR2)
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
            /// Peripheral clock frequency (FREQ)
            uint32_t frequency                   : 6;    // bits 0:5
            /// (reserved)
            uint32_t                             : 2;    // bits 6:7
            /// Error interrupt enable (ITERREN)
            uint32_t error_interrupt_enable      : 1;    // bit 8
            /// Event interrupt enable (ITEVTEN)
            uint32_t event_interrupt_enable      : 1;    // bit 9
            /// Buffer interrupt enable (ITBUFEN)
            uint32_t buffer_interrupt_enable     : 1;    // bit 10
            /// DMA requests enable (DMAEN)
            uint32_t direct_memory_access_enable : 1;    // bit 11
            /// DMA last transfer (LAST)
            uint32_t last                        : 1;    // bit 12
            /// (reserved)
            uint32_t                             : 19;    // bits 13:31
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
    /// Own address register 1 (OAR1)
    struct OurAddress1 final {
        /// Default Constructor
        OurAddress1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OurAddress1(OurAddress1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OurAddress1(OurAddress1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OurAddress1(OurAddress1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OurAddress1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OurAddress1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OurAddress1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Interface address (ADD0)
            uint32_t address0        : 1;    // bit 0
            /// Interface address (ADD7)
            uint32_t address7        : 7;    // bits 1:7
            /// Interface address (ADD10)
            uint32_t address10       : 2;    // bits 8:9
            /// (reserved)
            uint32_t                 : 5;    // bits 10:14
            /// Addressing mode (slave mode) (ADDMODE)
            uint32_t addressing_mode : 1;    // bit 15
            /// (reserved)
            uint32_t                 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OurAddress1& operator=(OurAddress1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OurAddress1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OurAddress1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OurAddress1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OurAddress1) == 4UL, "Must be this exact size");
    /// Own address register 2 (OAR2)
    struct OurAddress2 final {
        /// Default Constructor
        OurAddress2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OurAddress2(OurAddress2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OurAddress2(OurAddress2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OurAddress2(OurAddress2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OurAddress2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OurAddress2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OurAddress2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Dual addressing mode enable (ENDUAL)
            uint32_t enable_dual_address_mode : 1;    // bit 0
            /// Interface address (ADD2)
            uint32_t address2                 : 7;    // bits 1:7
            /// (reserved)
            uint32_t                          : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OurAddress2& operator=(OurAddress2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OurAddress2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OurAddress2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OurAddress2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OurAddress2) == 4UL, "Must be this exact size");
    /// Data register (DR)
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
            /// 8-bit data register (DR)
            uint32_t data : 8;    // bits 0:7
            /// (reserved)
            uint32_t      : 24;    // bits 8:31
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
    /// Status register 1 (SR1)
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
            /// Start bit (Master mode) (SB)
            uint32_t start_bit                   : 1;    // bit 0
            /// Address sent (master mode)/matched (slave mode) (ADDR)
            uint32_t address                     : 1;    // bit 1
            /// Byte transfer finished (BTF)
            uint32_t byte_transfer_finished      : 1;    // bit 2
            /// 10-bit header sent (Master mode) (ADD10)
            uint32_t address10                   : 1;    // bit 3
            /// Stop detection (slave mode) (STOPF)
            uint32_t stop_detection              : 1;    // bit 4
            /// (reserved)
            uint32_t                             : 1;    // bit 5
            /// Data register not empty (receivers) (RxNE)
            uint32_t receive_not_empty           : 1;    // bit 6
            /// Data register empty (transmitters) (TxE)
            uint32_t transmit_empty              : 1;    // bit 7
            /// Bus error (BERR)
            uint32_t bus_error                   : 1;    // bit 8
            /// Arbitration lost (master mode) (ARLO)
            uint32_t arbitration_lost            : 1;    // bit 9
            /// Acknowledge failure (AF)
            uint32_t acknowledge_failure         : 1;    // bit 10
            /// Overrun/Underrun (OVR)
            uint32_t overrun                     : 1;    // bit 11
            /// PEC Error in reception (PECERR)
            uint32_t packet_error_code_error     : 1;    // bit 12
            /// (reserved)
            uint32_t                             : 1;    // bit 13
            /// Timeout or Tlow error (TIMEOUT)
            uint32_t timeout                     : 1;    // bit 14
            /// SMBus alert (SMBALERT)
            uint32_t system_management_bus_alert : 1;    // bit 15
            /// (reserved)
            uint32_t                             : 16;    // bits 16:31
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
    /// Status register 2 (SR2)
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
            /// Master/slave (MSL)
            uint32_t leader_follower_mode          : 1;    // bit 0
            /// Bus busy (BUSY)
            uint32_t busy                          : 1;    // bit 1
            /// Transmitter/receiver (TRA)
            uint32_t transmit_receive_mode         : 1;    // bit 2
            /// (reserved)
            uint32_t                               : 1;    // bit 3
            /// General call address (Slave mode) (GENCALL)
            uint32_t general_call                  : 1;    // bit 4
            /// SMBus device default address (Slave mode) (SMBDEFAULT)
            uint32_t system_management_bus_default : 1;    // bit 5
            /// SMBus host header (Slave mode) (SMBHOST)
            uint32_t system_management_bus_host    : 1;    // bit 6
            /// Dual flag (Slave mode) (DUALF)
            uint32_t dual_flag                     : 1;    // bit 7
            /// Packet error checking register (PEC)
            uint32_t packet_error_checking         : 8;    // bits 8:15
            /// (reserved)
            uint32_t                               : 16;    // bits 16:31
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
    /// Clock control register (CCR)
    struct ClockControl final {
        /// Default Constructor
        ClockControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ClockControl(ClockControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ClockControl(ClockControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ClockControl(ClockControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ClockControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ClockControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ClockControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Clock control register in Fast/Standard mode (Master mode) (CCR)
            uint32_t clock_control      : 12;    // bits 0:11
            /// (reserved)
            uint32_t                    : 2;    // bits 12:13
            /// Fast mode duty cycle (DUTY)
            uint32_t duty               : 1;    // bit 14
            /// I2C master mode selection (F_S)
            uint32_t fast_standard_mode : 1;    // bit 15
            /// (reserved)
            uint32_t                    : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ClockControl& operator=(ClockControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ClockControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ClockControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ClockControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ClockControl) == 4UL, "Must be this exact size");
    /// TRISE register (TRISE)
    struct RiseTime final {
        /// Default Constructor
        RiseTime()
            : whole{0u} {}
        /// Copy Constructor from volatile
        RiseTime(RiseTime volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        RiseTime(RiseTime const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        RiseTime(RiseTime&&) = delete;
        /// Parameterized Constructor for constant references
        explicit RiseTime(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit RiseTime(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~RiseTime() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Maximum rise time in Fast/Standard mode (Master mode) (TRISE)
            uint32_t rise_time : 6;    // bits 0:5
            /// (reserved)
            uint32_t           : 26;    // bits 6:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        RiseTime& operator=(RiseTime&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(RiseTime volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(RiseTime const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<RiseTime>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(RiseTime) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// Control register 2 (CR2)
    Control2 control2;    // offset 0x4UL
    /// Own address register 1 (OAR1)
    OurAddress1 our_address1;    // offset 0x8UL
    /// Own address register 2 (OAR2)
    OurAddress2 our_address2;    // offset 0xcUL
    /// Data register (DR)
    Data data;    // offset 0x10UL
    /// Status register 1 (SR1)
    Status1 status1;    // offset 0x14UL
    /// Status register 2 (SR2)
    Status2 status2;    // offset 0x18UL
    /// Clock control register (CCR)
    ClockControl clock_control;    // offset 0x1cUL
    /// TRISE register (TRISE)
    RiseTime rise_time;    // offset 0x20UL
    uint32_t : 32;         // offset 0x24UL
    uint32_t : 32;         // offset 0x28UL
    uint32_t : 32;         // offset 0x2cUL
    uint32_t : 32;         // offset 0x30UL
    uint32_t : 32;         // offset 0x34UL
    uint32_t : 32;         // offset 0x38UL
    uint32_t : 32;         // offset 0x3cUL
    uint32_t : 32;         // offset 0x40UL
    uint32_t : 32;         // offset 0x44UL
    uint32_t : 32;         // offset 0x48UL
    uint32_t : 32;         // offset 0x4cUL
    uint32_t : 32;         // offset 0x50UL
    uint32_t : 32;         // offset 0x54UL
    uint32_t : 32;         // offset 0x58UL
    uint32_t : 32;         // offset 0x5cUL
    uint32_t : 32;         // offset 0x60UL
    uint32_t : 32;         // offset 0x64UL
    uint32_t : 32;         // offset 0x68UL
    uint32_t : 32;         // offset 0x6cUL
    uint32_t : 32;         // offset 0x70UL
    uint32_t : 32;         // offset 0x74UL
    uint32_t : 32;         // offset 0x78UL
    uint32_t : 32;         // offset 0x7cUL
    uint32_t : 32;         // offset 0x80UL
    uint32_t : 32;         // offset 0x84UL
    uint32_t : 32;         // offset 0x88UL
    uint32_t : 32;         // offset 0x8cUL
    uint32_t : 32;         // offset 0x90UL
    uint32_t : 32;         // offset 0x94UL
    uint32_t : 32;         // offset 0x98UL
    uint32_t : 32;         // offset 0x9cUL
    uint32_t : 32;         // offset 0xa0UL
    uint32_t : 32;         // offset 0xa4UL
    uint32_t : 32;         // offset 0xa8UL
    uint32_t : 32;         // offset 0xacUL
    uint32_t : 32;         // offset 0xb0UL
    uint32_t : 32;         // offset 0xb4UL
    uint32_t : 32;         // offset 0xb8UL
    uint32_t : 32;         // offset 0xbcUL
    uint32_t : 32;         // offset 0xc0UL
    uint32_t : 32;         // offset 0xc4UL
    uint32_t : 32;         // offset 0xc8UL
    uint32_t : 32;         // offset 0xccUL
    uint32_t : 32;         // offset 0xd0UL
    uint32_t : 32;         // offset 0xd4UL
    uint32_t : 32;         // offset 0xd8UL
    uint32_t : 32;         // offset 0xdcUL
    uint32_t : 32;         // offset 0xe0UL
    uint32_t : 32;         // offset 0xe4UL
    uint32_t : 32;         // offset 0xe8UL
    uint32_t : 32;         // offset 0xecUL
    uint32_t : 32;         // offset 0xf0UL
    uint32_t : 32;         // offset 0xf4UL
    uint32_t : 32;         // offset 0xf8UL
    uint32_t : 32;         // offset 0xfcUL
    uint32_t : 32;         // offset 0x100UL
    uint32_t : 32;         // offset 0x104UL
    uint32_t : 32;         // offset 0x108UL
    uint32_t : 32;         // offset 0x10cUL
    uint32_t : 32;         // offset 0x110UL
    uint32_t : 32;         // offset 0x114UL
    uint32_t : 32;         // offset 0x118UL
    uint32_t : 32;         // offset 0x11cUL
    uint32_t : 32;         // offset 0x120UL
    uint32_t : 32;         // offset 0x124UL
    uint32_t : 32;         // offset 0x128UL
    uint32_t : 32;         // offset 0x12cUL
    uint32_t : 32;         // offset 0x130UL
    uint32_t : 32;         // offset 0x134UL
    uint32_t : 32;         // offset 0x138UL
    uint32_t : 32;         // offset 0x13cUL
    uint32_t : 32;         // offset 0x140UL
    uint32_t : 32;         // offset 0x144UL
    uint32_t : 32;         // offset 0x148UL
    uint32_t : 32;         // offset 0x14cUL
    uint32_t : 32;         // offset 0x150UL
    uint32_t : 32;         // offset 0x154UL
    uint32_t : 32;         // offset 0x158UL
    uint32_t : 32;         // offset 0x15cUL
    uint32_t : 32;         // offset 0x160UL
    uint32_t : 32;         // offset 0x164UL
    uint32_t : 32;         // offset 0x168UL
    uint32_t : 32;         // offset 0x16cUL
    uint32_t : 32;         // offset 0x170UL
    uint32_t : 32;         // offset 0x174UL
    uint32_t : 32;         // offset 0x178UL
    uint32_t : 32;         // offset 0x17cUL
    uint32_t : 32;         // offset 0x180UL
    uint32_t : 32;         // offset 0x184UL
    uint32_t : 32;         // offset 0x188UL
    uint32_t : 32;         // offset 0x18cUL
    uint32_t : 32;         // offset 0x190UL
    uint32_t : 32;         // offset 0x194UL
    uint32_t : 32;         // offset 0x198UL
    uint32_t : 32;         // offset 0x19cUL
    uint32_t : 32;         // offset 0x1a0UL
    uint32_t : 32;         // offset 0x1a4UL
    uint32_t : 32;         // offset 0x1a8UL
    uint32_t : 32;         // offset 0x1acUL
    uint32_t : 32;         // offset 0x1b0UL
    uint32_t : 32;         // offset 0x1b4UL
    uint32_t : 32;         // offset 0x1b8UL
    uint32_t : 32;         // offset 0x1bcUL
    uint32_t : 32;         // offset 0x1c0UL
    uint32_t : 32;         // offset 0x1c4UL
    uint32_t : 32;         // offset 0x1c8UL
    uint32_t : 32;         // offset 0x1ccUL
    uint32_t : 32;         // offset 0x1d0UL
    uint32_t : 32;         // offset 0x1d4UL
    uint32_t : 32;         // offset 0x1d8UL
    uint32_t : 32;         // offset 0x1dcUL
    uint32_t : 32;         // offset 0x1e0UL
    uint32_t : 32;         // offset 0x1e4UL
    uint32_t : 32;         // offset 0x1e8UL
    uint32_t : 32;         // offset 0x1ecUL
    uint32_t : 32;         // offset 0x1f0UL
    uint32_t : 32;         // offset 0x1f4UL
    uint32_t : 32;         // offset 0x1f8UL
    uint32_t : 32;         // offset 0x1fcUL
    uint32_t : 32;         // offset 0x200UL
    uint32_t : 32;         // offset 0x204UL
    uint32_t : 32;         // offset 0x208UL
    uint32_t : 32;         // offset 0x20cUL
    uint32_t : 32;         // offset 0x210UL
    uint32_t : 32;         // offset 0x214UL
    uint32_t : 32;         // offset 0x218UL
    uint32_t : 32;         // offset 0x21cUL
    uint32_t : 32;         // offset 0x220UL
    uint32_t : 32;         // offset 0x224UL
    uint32_t : 32;         // offset 0x228UL
    uint32_t : 32;         // offset 0x22cUL
    uint32_t : 32;         // offset 0x230UL
    uint32_t : 32;         // offset 0x234UL
    uint32_t : 32;         // offset 0x238UL
    uint32_t : 32;         // offset 0x23cUL
    uint32_t : 32;         // offset 0x240UL
    uint32_t : 32;         // offset 0x244UL
    uint32_t : 32;         // offset 0x248UL
    uint32_t : 32;         // offset 0x24cUL
    uint32_t : 32;         // offset 0x250UL
    uint32_t : 32;         // offset 0x254UL
    uint32_t : 32;         // offset 0x258UL
    uint32_t : 32;         // offset 0x25cUL
    uint32_t : 32;         // offset 0x260UL
    uint32_t : 32;         // offset 0x264UL
    uint32_t : 32;         // offset 0x268UL
    uint32_t : 32;         // offset 0x26cUL
    uint32_t : 32;         // offset 0x270UL
    uint32_t : 32;         // offset 0x274UL
    uint32_t : 32;         // offset 0x278UL
    uint32_t : 32;         // offset 0x27cUL
    uint32_t : 32;         // offset 0x280UL
    uint32_t : 32;         // offset 0x284UL
    uint32_t : 32;         // offset 0x288UL
    uint32_t : 32;         // offset 0x28cUL
    uint32_t : 32;         // offset 0x290UL
    uint32_t : 32;         // offset 0x294UL
    uint32_t : 32;         // offset 0x298UL
    uint32_t : 32;         // offset 0x29cUL
    uint32_t : 32;         // offset 0x2a0UL
    uint32_t : 32;         // offset 0x2a4UL
    uint32_t : 32;         // offset 0x2a8UL
    uint32_t : 32;         // offset 0x2acUL
    uint32_t : 32;         // offset 0x2b0UL
    uint32_t : 32;         // offset 0x2b4UL
    uint32_t : 32;         // offset 0x2b8UL
    uint32_t : 32;         // offset 0x2bcUL
    uint32_t : 32;         // offset 0x2c0UL
    uint32_t : 32;         // offset 0x2c4UL
    uint32_t : 32;         // offset 0x2c8UL
    uint32_t : 32;         // offset 0x2ccUL
    uint32_t : 32;         // offset 0x2d0UL
    uint32_t : 32;         // offset 0x2d4UL
    uint32_t : 32;         // offset 0x2d8UL
    uint32_t : 32;         // offset 0x2dcUL
    uint32_t : 32;         // offset 0x2e0UL
    uint32_t : 32;         // offset 0x2e4UL
    uint32_t : 32;         // offset 0x2e8UL
    uint32_t : 32;         // offset 0x2ecUL
    uint32_t : 32;         // offset 0x2f0UL
    uint32_t : 32;         // offset 0x2f4UL
    uint32_t : 32;         // offset 0x2f8UL
    uint32_t : 32;         // offset 0x2fcUL
    uint32_t : 32;         // offset 0x300UL
    uint32_t : 32;         // offset 0x304UL
    uint32_t : 32;         // offset 0x308UL
    uint32_t : 32;         // offset 0x30cUL
    uint32_t : 32;         // offset 0x310UL
    uint32_t : 32;         // offset 0x314UL
    uint32_t : 32;         // offset 0x318UL
    uint32_t : 32;         // offset 0x31cUL
    uint32_t : 32;         // offset 0x320UL
    uint32_t : 32;         // offset 0x324UL
    uint32_t : 32;         // offset 0x328UL
    uint32_t : 32;         // offset 0x32cUL
    uint32_t : 32;         // offset 0x330UL
    uint32_t : 32;         // offset 0x334UL
    uint32_t : 32;         // offset 0x338UL
    uint32_t : 32;         // offset 0x33cUL
    uint32_t : 32;         // offset 0x340UL
    uint32_t : 32;         // offset 0x344UL
    uint32_t : 32;         // offset 0x348UL
    uint32_t : 32;         // offset 0x34cUL
    uint32_t : 32;         // offset 0x350UL
    uint32_t : 32;         // offset 0x354UL
    uint32_t : 32;         // offset 0x358UL
    uint32_t : 32;         // offset 0x35cUL
    uint32_t : 32;         // offset 0x360UL
    uint32_t : 32;         // offset 0x364UL
    uint32_t : 32;         // offset 0x368UL
    uint32_t : 32;         // offset 0x36cUL
    uint32_t : 32;         // offset 0x370UL
    uint32_t : 32;         // offset 0x374UL
    uint32_t : 32;         // offset 0x378UL
    uint32_t : 32;         // offset 0x37cUL
    uint32_t : 32;         // offset 0x380UL
    uint32_t : 32;         // offset 0x384UL
    uint32_t : 32;         // offset 0x388UL
    uint32_t : 32;         // offset 0x38cUL
    uint32_t : 32;         // offset 0x390UL
    uint32_t : 32;         // offset 0x394UL
    uint32_t : 32;         // offset 0x398UL
    uint32_t : 32;         // offset 0x39cUL
    uint32_t : 32;         // offset 0x3a0UL
    uint32_t : 32;         // offset 0x3a4UL
    uint32_t : 32;         // offset 0x3a8UL
    uint32_t : 32;         // offset 0x3acUL
    uint32_t : 32;         // offset 0x3b0UL
    uint32_t : 32;         // offset 0x3b4UL
    uint32_t : 32;         // offset 0x3b8UL
    uint32_t : 32;         // offset 0x3bcUL
    uint32_t : 32;         // offset 0x3c0UL
    uint32_t : 32;         // offset 0x3c4UL
    uint32_t : 32;         // offset 0x3c8UL
    uint32_t : 32;         // offset 0x3ccUL
    uint32_t : 32;         // offset 0x3d0UL
    uint32_t : 32;         // offset 0x3d4UL
    uint32_t : 32;         // offset 0x3d8UL
    uint32_t : 32;         // offset 0x3dcUL
    uint32_t : 32;         // offset 0x3e0UL
    uint32_t : 32;         // offset 0x3e4UL
    uint32_t : 32;         // offset 0x3e8UL
    uint32_t : 32;         // offset 0x3ecUL
    uint32_t : 32;         // offset 0x3f0UL
    uint32_t : 32;         // offset 0x3f4UL
    uint32_t : 32;         // offset 0x3f8UL
    uint32_t : 32;         // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<InterIntegratedCircuit>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(InterIntegratedCircuit, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, our_address1) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, our_address2) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, data) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, status1) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, status2) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, clock_control) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, rise_time) == 0x20UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(InterIntegratedCircuit) == 0x400UL, "Must be this exact size");

/// The external volatile inter_integrated_circuit1 which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern InterIntegratedCircuit volatile i2c1;

/// The external volatile inter_integrated_circuit2 which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern InterIntegratedCircuit volatile i2c2;

/// The external volatile inter_integrated_circuit3 which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern InterIntegratedCircuit volatile i2c3;

}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_INTERINTEGRATEDCIRCUIT_HPP_