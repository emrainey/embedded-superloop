
#ifndef STM32_REGISTERS_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER1__HPP_
#define STM32_REGISTERS_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER1__HPP_

/// @file
/// Auto Generated Structure Definitions for UniversalSynchronousAsynchronousReceiverTransmitter from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Universal synchronous asynchronous receiver transmitter (USART1)
struct UniversalSynchronousAsynchronousReceiverTransmitter final {
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
            /// Parity error (PE)
            uint32_t parity_error             : 1;    // bit 0
            /// Framing error (FE)
            uint32_t framing_error            : 1;    // bit 1
            /// Noise detected flag (NF)
            uint32_t noise_flag               : 1;    // bit 2
            /// Overrun error (ORE)
            uint32_t overrun_error            : 1;    // bit 3
            /// IDLE line detected (IDLE)
            uint32_t idle                     : 1;    // bit 4
            /// Read data register not empty (RXNE)
            uint32_t receive_buffer_not_empty : 1;    // bit 5
            /// Transmission complete (TC)
            uint32_t transmit_complete        : 1;    // bit 6
            /// Transmit data register empty (TXE)
            uint32_t transmit_buffer_empty    : 1;    // bit 7
            /// LIN break detection flag (LBD)
            uint32_t line_break_detection     : 1;    // bit 8
            /// CTS flag (CTS)
            uint32_t clear_to_send            : 1;    // bit 9
            /// (reserved)
            uint32_t                          : 22;    // bits 10:31
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
            /// Data value (DR)
            uint32_t data : 9;    // bits 0:8
            /// (reserved)
            uint32_t      : 23;    // bits 9:31
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
    /// Baud rate register (BRR)
    struct BaudRate final {
        /// Default Constructor
        BaudRate()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BaudRate(BaudRate volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BaudRate(BaudRate const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BaudRate(BaudRate&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BaudRate(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BaudRate(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BaudRate() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// fraction of USARTDIV (DIV_Fraction)
            uint32_t div_fraction : 4;    // bits 0:3
            /// mantissa of USARTDIV (DIV_Mantissa)
            uint32_t div_mantissa : 12;    // bits 4:15
            /// (reserved)
            uint32_t              : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BaudRate& operator=(BaudRate&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BaudRate volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BaudRate const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BaudRate>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BaudRate) == 4UL, "Must be this exact size");
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
            /// Send break (SBK)
            uint32_t send_break                         : 1;    // bit 0
            /// Receiver wakeup (RWU)
            uint32_t receive_wakeup                     : 1;    // bit 1
            /// Receiver enable (RE)
            uint32_t receiver_enable                    : 1;    // bit 2
            /// Transmitter enable (TE)
            uint32_t transmitter_enable                 : 1;    // bit 3
            /// IDLE interrupt enable (IDLEIE)
            uint32_t idle_interrupt_enable              : 1;    // bit 4
            /// RXNE interrupt enable (RXNEIE)
            uint32_t receive_not_empty_interrupt_enable : 1;    // bit 5
            /// Transmission complete interrupt enable (TCIE)
            uint32_t transfer_complete_interrupt_enable : 1;    // bit 6
            /// TXE interrupt enable (TXEIE)
            uint32_t transmit_empty_interrupt_enable    : 1;    // bit 7
            /// PE interrupt enable (PEIE)
            uint32_t parity_error_interrupt_enable      : 1;    // bit 8
            /// Parity selection (PS)
            uint32_t parity_select                      : 1;    // bit 9
            /// Parity control enable (PCE)
            uint32_t parity_control_enable              : 1;    // bit 10
            /// Wakeup method (WAKE)
            uint32_t wake                               : 1;    // bit 11
            /// Word length (M)
            uint32_t word_length                        : 1;    // bit 12
            /// USART enable (UE)
            uint32_t uxart_enable                       : 1;    // bit 13
            /// (reserved)
            uint32_t                                    : 1;    // bit 14
            /// Oversampling mode (OVER8)
            uint32_t oversampling_mode                  : 1;    // bit 15
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
            /// Address of the USART node (ADD)
            uint32_t address                               : 4;    // bits 0:3
            /// (reserved)
            uint32_t                                       : 1;    // bit 4
            /// lin break detection length (LBDL)
            uint32_t line_break_detection_length           : 1;    // bit 5
            /// LIN break detection interrupt enable (LBDIE)
            uint32_t line_break_detection_interrupt_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                                       : 1;    // bit 7
            /// Last bit clock pulse (LBCL)
            uint32_t last_bit_clock_pulse                  : 1;    // bit 8
            /// Clock phase (CPHA)
            uint32_t clock_phase                           : 1;    // bit 9
            /// Clock polarity (CPOL)
            uint32_t clock_polarity                        : 1;    // bit 10
            /// Clock enable (CLKEN)
            uint32_t clock_enable                          : 1;    // bit 11
            /// STOP bits (STOP)
            uint32_t stop                                  : 2;    // bits 12:13
            /// LIN mode enable (LINEN)
            uint32_t local_interconnect_network_enable     : 1;    // bit 14
            /// (reserved)
            uint32_t                                       : 17;    // bits 15:31
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
    /// Control register 3 (CR3)
    struct Control3 final {
        /// Default Constructor
        Control3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control3(Control3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control3(Control3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control3(Control3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Error interrupt enable (EIE)
            uint32_t error_interrupt_enable              : 1;    // bit 0
            /// IrDA mode enable (IREN)
            uint32_t infrared_data_association_enable    : 1;    // bit 1
            /// IrDA low-power (IRLP)
            uint32_t infrared_data_association_low_power : 1;    // bit 2
            /// Half-duplex selection (HDSEL)
            uint32_t half_duplex_selection               : 1;    // bit 3
            /// Smartcard NACK enable (NACK)
            uint32_t smart_card_negative_acknowledge     : 1;    // bit 4
            /// Smartcard mode enable (SCEN)
            uint32_t smart_card_enable                   : 1;    // bit 5
            /// DMA enable receiver (DMAR)
            uint32_t direct_memory_access_receiver       : 1;    // bit 6
            /// DMA enable transmitter (DMAT)
            uint32_t direct_memory_access_transmitter    : 1;    // bit 7
            /// RTS enable (RTSE)
            uint32_t ready_to_send_enable                : 1;    // bit 8
            /// CTS enable (CTSE)
            uint32_t clear_to_send_enable                : 1;    // bit 9
            /// CTS interrupt enable (CTSIE)
            uint32_t clear_to_send_interrupt_enable      : 1;    // bit 10
            /// One sample bit method enable (ONEBIT)
            uint32_t onebit                              : 1;    // bit 11
            /// (reserved)
            uint32_t                                     : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control3& operator=(Control3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control3) == 4UL, "Must be this exact size");
    /// Guard time and prescaler register (GTPR)
    struct GuardTimePrescaler final {
        /// Default Constructor
        GuardTimePrescaler()
            : whole{0u} {}
        /// Copy Constructor from volatile
        GuardTimePrescaler(GuardTimePrescaler volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        GuardTimePrescaler(GuardTimePrescaler const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        GuardTimePrescaler(GuardTimePrescaler&&) = delete;
        /// Parameterized Constructor for constant references
        explicit GuardTimePrescaler(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit GuardTimePrescaler(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~GuardTimePrescaler() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Prescaler value (PSC)
            uint32_t prescaler  : 8;    // bits 0:7
            /// Guard time value (GT)
            uint32_t guard_time : 8;    // bits 8:15
            /// (reserved)
            uint32_t            : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        GuardTimePrescaler& operator=(GuardTimePrescaler&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(GuardTimePrescaler volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(GuardTimePrescaler const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<GuardTimePrescaler>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(GuardTimePrescaler) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Status register (SR)
    Status status;    // offset 0x0UL
    /// Data register (DR)
    Data data;    // offset 0x4UL
    /// Baud rate register (BRR)
    BaudRate baudrate;    // offset 0x8UL
    /// Control register 1 (CR1)
    Control1 control1;    // offset 0xcUL
    /// Control register 2 (CR2)
    Control2 control2;    // offset 0x10UL
    /// Control register 3 (CR3)
    Control3 control3;    // offset 0x14UL
    /// Guard time and prescaler register (GTPR)
    GuardTimePrescaler guard_time_prescaler;    // offset 0x18UL
    uint32_t : 32;                              // offset 0x1cUL
    uint32_t : 32;                              // offset 0x20UL
    uint32_t : 32;                              // offset 0x24UL
    uint32_t : 32;                              // offset 0x28UL
    uint32_t : 32;                              // offset 0x2cUL
    uint32_t : 32;                              // offset 0x30UL
    uint32_t : 32;                              // offset 0x34UL
    uint32_t : 32;                              // offset 0x38UL
    uint32_t : 32;                              // offset 0x3cUL
    uint32_t : 32;                              // offset 0x40UL
    uint32_t : 32;                              // offset 0x44UL
    uint32_t : 32;                              // offset 0x48UL
    uint32_t : 32;                              // offset 0x4cUL
    uint32_t : 32;                              // offset 0x50UL
    uint32_t : 32;                              // offset 0x54UL
    uint32_t : 32;                              // offset 0x58UL
    uint32_t : 32;                              // offset 0x5cUL
    uint32_t : 32;                              // offset 0x60UL
    uint32_t : 32;                              // offset 0x64UL
    uint32_t : 32;                              // offset 0x68UL
    uint32_t : 32;                              // offset 0x6cUL
    uint32_t : 32;                              // offset 0x70UL
    uint32_t : 32;                              // offset 0x74UL
    uint32_t : 32;                              // offset 0x78UL
    uint32_t : 32;                              // offset 0x7cUL
    uint32_t : 32;                              // offset 0x80UL
    uint32_t : 32;                              // offset 0x84UL
    uint32_t : 32;                              // offset 0x88UL
    uint32_t : 32;                              // offset 0x8cUL
    uint32_t : 32;                              // offset 0x90UL
    uint32_t : 32;                              // offset 0x94UL
    uint32_t : 32;                              // offset 0x98UL
    uint32_t : 32;                              // offset 0x9cUL
    uint32_t : 32;                              // offset 0xa0UL
    uint32_t : 32;                              // offset 0xa4UL
    uint32_t : 32;                              // offset 0xa8UL
    uint32_t : 32;                              // offset 0xacUL
    uint32_t : 32;                              // offset 0xb0UL
    uint32_t : 32;                              // offset 0xb4UL
    uint32_t : 32;                              // offset 0xb8UL
    uint32_t : 32;                              // offset 0xbcUL
    uint32_t : 32;                              // offset 0xc0UL
    uint32_t : 32;                              // offset 0xc4UL
    uint32_t : 32;                              // offset 0xc8UL
    uint32_t : 32;                              // offset 0xccUL
    uint32_t : 32;                              // offset 0xd0UL
    uint32_t : 32;                              // offset 0xd4UL
    uint32_t : 32;                              // offset 0xd8UL
    uint32_t : 32;                              // offset 0xdcUL
    uint32_t : 32;                              // offset 0xe0UL
    uint32_t : 32;                              // offset 0xe4UL
    uint32_t : 32;                              // offset 0xe8UL
    uint32_t : 32;                              // offset 0xecUL
    uint32_t : 32;                              // offset 0xf0UL
    uint32_t : 32;                              // offset 0xf4UL
    uint32_t : 32;                              // offset 0xf8UL
    uint32_t : 32;                              // offset 0xfcUL
    uint32_t : 32;                              // offset 0x100UL
    uint32_t : 32;                              // offset 0x104UL
    uint32_t : 32;                              // offset 0x108UL
    uint32_t : 32;                              // offset 0x10cUL
    uint32_t : 32;                              // offset 0x110UL
    uint32_t : 32;                              // offset 0x114UL
    uint32_t : 32;                              // offset 0x118UL
    uint32_t : 32;                              // offset 0x11cUL
    uint32_t : 32;                              // offset 0x120UL
    uint32_t : 32;                              // offset 0x124UL
    uint32_t : 32;                              // offset 0x128UL
    uint32_t : 32;                              // offset 0x12cUL
    uint32_t : 32;                              // offset 0x130UL
    uint32_t : 32;                              // offset 0x134UL
    uint32_t : 32;                              // offset 0x138UL
    uint32_t : 32;                              // offset 0x13cUL
    uint32_t : 32;                              // offset 0x140UL
    uint32_t : 32;                              // offset 0x144UL
    uint32_t : 32;                              // offset 0x148UL
    uint32_t : 32;                              // offset 0x14cUL
    uint32_t : 32;                              // offset 0x150UL
    uint32_t : 32;                              // offset 0x154UL
    uint32_t : 32;                              // offset 0x158UL
    uint32_t : 32;                              // offset 0x15cUL
    uint32_t : 32;                              // offset 0x160UL
    uint32_t : 32;                              // offset 0x164UL
    uint32_t : 32;                              // offset 0x168UL
    uint32_t : 32;                              // offset 0x16cUL
    uint32_t : 32;                              // offset 0x170UL
    uint32_t : 32;                              // offset 0x174UL
    uint32_t : 32;                              // offset 0x178UL
    uint32_t : 32;                              // offset 0x17cUL
    uint32_t : 32;                              // offset 0x180UL
    uint32_t : 32;                              // offset 0x184UL
    uint32_t : 32;                              // offset 0x188UL
    uint32_t : 32;                              // offset 0x18cUL
    uint32_t : 32;                              // offset 0x190UL
    uint32_t : 32;                              // offset 0x194UL
    uint32_t : 32;                              // offset 0x198UL
    uint32_t : 32;                              // offset 0x19cUL
    uint32_t : 32;                              // offset 0x1a0UL
    uint32_t : 32;                              // offset 0x1a4UL
    uint32_t : 32;                              // offset 0x1a8UL
    uint32_t : 32;                              // offset 0x1acUL
    uint32_t : 32;                              // offset 0x1b0UL
    uint32_t : 32;                              // offset 0x1b4UL
    uint32_t : 32;                              // offset 0x1b8UL
    uint32_t : 32;                              // offset 0x1bcUL
    uint32_t : 32;                              // offset 0x1c0UL
    uint32_t : 32;                              // offset 0x1c4UL
    uint32_t : 32;                              // offset 0x1c8UL
    uint32_t : 32;                              // offset 0x1ccUL
    uint32_t : 32;                              // offset 0x1d0UL
    uint32_t : 32;                              // offset 0x1d4UL
    uint32_t : 32;                              // offset 0x1d8UL
    uint32_t : 32;                              // offset 0x1dcUL
    uint32_t : 32;                              // offset 0x1e0UL
    uint32_t : 32;                              // offset 0x1e4UL
    uint32_t : 32;                              // offset 0x1e8UL
    uint32_t : 32;                              // offset 0x1ecUL
    uint32_t : 32;                              // offset 0x1f0UL
    uint32_t : 32;                              // offset 0x1f4UL
    uint32_t : 32;                              // offset 0x1f8UL
    uint32_t : 32;                              // offset 0x1fcUL
    uint32_t : 32;                              // offset 0x200UL
    uint32_t : 32;                              // offset 0x204UL
    uint32_t : 32;                              // offset 0x208UL
    uint32_t : 32;                              // offset 0x20cUL
    uint32_t : 32;                              // offset 0x210UL
    uint32_t : 32;                              // offset 0x214UL
    uint32_t : 32;                              // offset 0x218UL
    uint32_t : 32;                              // offset 0x21cUL
    uint32_t : 32;                              // offset 0x220UL
    uint32_t : 32;                              // offset 0x224UL
    uint32_t : 32;                              // offset 0x228UL
    uint32_t : 32;                              // offset 0x22cUL
    uint32_t : 32;                              // offset 0x230UL
    uint32_t : 32;                              // offset 0x234UL
    uint32_t : 32;                              // offset 0x238UL
    uint32_t : 32;                              // offset 0x23cUL
    uint32_t : 32;                              // offset 0x240UL
    uint32_t : 32;                              // offset 0x244UL
    uint32_t : 32;                              // offset 0x248UL
    uint32_t : 32;                              // offset 0x24cUL
    uint32_t : 32;                              // offset 0x250UL
    uint32_t : 32;                              // offset 0x254UL
    uint32_t : 32;                              // offset 0x258UL
    uint32_t : 32;                              // offset 0x25cUL
    uint32_t : 32;                              // offset 0x260UL
    uint32_t : 32;                              // offset 0x264UL
    uint32_t : 32;                              // offset 0x268UL
    uint32_t : 32;                              // offset 0x26cUL
    uint32_t : 32;                              // offset 0x270UL
    uint32_t : 32;                              // offset 0x274UL
    uint32_t : 32;                              // offset 0x278UL
    uint32_t : 32;                              // offset 0x27cUL
    uint32_t : 32;                              // offset 0x280UL
    uint32_t : 32;                              // offset 0x284UL
    uint32_t : 32;                              // offset 0x288UL
    uint32_t : 32;                              // offset 0x28cUL
    uint32_t : 32;                              // offset 0x290UL
    uint32_t : 32;                              // offset 0x294UL
    uint32_t : 32;                              // offset 0x298UL
    uint32_t : 32;                              // offset 0x29cUL
    uint32_t : 32;                              // offset 0x2a0UL
    uint32_t : 32;                              // offset 0x2a4UL
    uint32_t : 32;                              // offset 0x2a8UL
    uint32_t : 32;                              // offset 0x2acUL
    uint32_t : 32;                              // offset 0x2b0UL
    uint32_t : 32;                              // offset 0x2b4UL
    uint32_t : 32;                              // offset 0x2b8UL
    uint32_t : 32;                              // offset 0x2bcUL
    uint32_t : 32;                              // offset 0x2c0UL
    uint32_t : 32;                              // offset 0x2c4UL
    uint32_t : 32;                              // offset 0x2c8UL
    uint32_t : 32;                              // offset 0x2ccUL
    uint32_t : 32;                              // offset 0x2d0UL
    uint32_t : 32;                              // offset 0x2d4UL
    uint32_t : 32;                              // offset 0x2d8UL
    uint32_t : 32;                              // offset 0x2dcUL
    uint32_t : 32;                              // offset 0x2e0UL
    uint32_t : 32;                              // offset 0x2e4UL
    uint32_t : 32;                              // offset 0x2e8UL
    uint32_t : 32;                              // offset 0x2ecUL
    uint32_t : 32;                              // offset 0x2f0UL
    uint32_t : 32;                              // offset 0x2f4UL
    uint32_t : 32;                              // offset 0x2f8UL
    uint32_t : 32;                              // offset 0x2fcUL
    uint32_t : 32;                              // offset 0x300UL
    uint32_t : 32;                              // offset 0x304UL
    uint32_t : 32;                              // offset 0x308UL
    uint32_t : 32;                              // offset 0x30cUL
    uint32_t : 32;                              // offset 0x310UL
    uint32_t : 32;                              // offset 0x314UL
    uint32_t : 32;                              // offset 0x318UL
    uint32_t : 32;                              // offset 0x31cUL
    uint32_t : 32;                              // offset 0x320UL
    uint32_t : 32;                              // offset 0x324UL
    uint32_t : 32;                              // offset 0x328UL
    uint32_t : 32;                              // offset 0x32cUL
    uint32_t : 32;                              // offset 0x330UL
    uint32_t : 32;                              // offset 0x334UL
    uint32_t : 32;                              // offset 0x338UL
    uint32_t : 32;                              // offset 0x33cUL
    uint32_t : 32;                              // offset 0x340UL
    uint32_t : 32;                              // offset 0x344UL
    uint32_t : 32;                              // offset 0x348UL
    uint32_t : 32;                              // offset 0x34cUL
    uint32_t : 32;                              // offset 0x350UL
    uint32_t : 32;                              // offset 0x354UL
    uint32_t : 32;                              // offset 0x358UL
    uint32_t : 32;                              // offset 0x35cUL
    uint32_t : 32;                              // offset 0x360UL
    uint32_t : 32;                              // offset 0x364UL
    uint32_t : 32;                              // offset 0x368UL
    uint32_t : 32;                              // offset 0x36cUL
    uint32_t : 32;                              // offset 0x370UL
    uint32_t : 32;                              // offset 0x374UL
    uint32_t : 32;                              // offset 0x378UL
    uint32_t : 32;                              // offset 0x37cUL
    uint32_t : 32;                              // offset 0x380UL
    uint32_t : 32;                              // offset 0x384UL
    uint32_t : 32;                              // offset 0x388UL
    uint32_t : 32;                              // offset 0x38cUL
    uint32_t : 32;                              // offset 0x390UL
    uint32_t : 32;                              // offset 0x394UL
    uint32_t : 32;                              // offset 0x398UL
    uint32_t : 32;                              // offset 0x39cUL
    uint32_t : 32;                              // offset 0x3a0UL
    uint32_t : 32;                              // offset 0x3a4UL
    uint32_t : 32;                              // offset 0x3a8UL
    uint32_t : 32;                              // offset 0x3acUL
    uint32_t : 32;                              // offset 0x3b0UL
    uint32_t : 32;                              // offset 0x3b4UL
    uint32_t : 32;                              // offset 0x3b8UL
    uint32_t : 32;                              // offset 0x3bcUL
    uint32_t : 32;                              // offset 0x3c0UL
    uint32_t : 32;                              // offset 0x3c4UL
    uint32_t : 32;                              // offset 0x3c8UL
    uint32_t : 32;                              // offset 0x3ccUL
    uint32_t : 32;                              // offset 0x3d0UL
    uint32_t : 32;                              // offset 0x3d4UL
    uint32_t : 32;                              // offset 0x3d8UL
    uint32_t : 32;                              // offset 0x3dcUL
    uint32_t : 32;                              // offset 0x3e0UL
    uint32_t : 32;                              // offset 0x3e4UL
    uint32_t : 32;                              // offset 0x3e8UL
    uint32_t : 32;                              // offset 0x3ecUL
    uint32_t : 32;                              // offset 0x3f0UL
    uint32_t : 32;                              // offset 0x3f4UL
    uint32_t : 32;                              // offset 0x3f8UL
    uint32_t : 32;                              // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<UniversalSynchronousAsynchronousReceiverTransmitter>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, status) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, data) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, baudrate) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control1) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control2) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control3) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, guard_time_prescaler) == 0x18UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(UniversalSynchronousAsynchronousReceiverTransmitter) == 0x400UL, "Must be this exact size");

/// The external volatile USART which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart1;

/// The external volatile USART which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart2;

/// The external volatile USART which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart3;

/// The external volatile USART which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart6;

}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER1__HPP_