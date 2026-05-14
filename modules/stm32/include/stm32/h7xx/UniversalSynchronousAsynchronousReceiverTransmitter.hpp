
#ifndef STM32_H7XX_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER__HPP_
#define STM32_H7XX_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER__HPP_

/// @file
/// Auto Generated Structure Definitions for UniversalSynchronousAsynchronousReceiverTransmitter from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Universal synchronous asynchronous receiver transmitter
struct UniversalSynchronousAsynchronousReceiverTransmitter final {
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
            /// USART enable (UE)
            uint32_t usart_enable                         : 1;    // bit 0
            /// USART enable in Stop mode (UESM)
            uint32_t usart_enable_in_stop_mode            : 1;    // bit 1
            /// Receiver enable (RE)
            uint32_t receiver_enable                      : 1;    // bit 2
            /// Transmitter enable (TE)
            uint32_t transmitter_enable                   : 1;    // bit 3
            /// IDLE interrupt enable (IDLEIE)
            uint32_t idle_interrupt_enable                : 1;    // bit 4
            /// RXNE interrupt enable (RXNEIE)
            uint32_t receive_not_empty_interrupt_enable   : 1;    // bit 5
            /// Transmission complete interrupt enable (TCIE)
            uint32_t transfer_complete_interrupt_enable   : 1;    // bit 6
            /// interrupt enable (TXEIE)
            uint32_t transmit_empty_interrupt_enable      : 1;    // bit 7
            /// PE interrupt enable (PEIE)
            uint32_t parity_error_interrupt_enable        : 1;    // bit 8
            /// Parity selection (PS)
            uint32_t parity_select                        : 1;    // bit 9
            /// Parity control enable (PCE)
            uint32_t parity_control_enable                : 1;    // bit 10
            /// Receiver wakeup method (WAKE)
            uint32_t wakeup_method                        : 1;    // bit 11
            /// Word length (M0)
            uint32_t word_length_bit_0                    : 1;    // bit 12
            /// Mute mode enable (MME)
            uint32_t mute_mode_enable                     : 1;    // bit 13
            /// Character match interrupt enable (CMIE)
            uint32_t character_match_interrupt_enable     : 1;    // bit 14
            /// Oversampling mode (OVER8)
            uint32_t oversampling_mode                    : 1;    // bit 15
            /// DEDT0 (DEDT0)
            uint32_t driver_enable_deassertion_time_0     : 1;    // bit 16
            /// DEDT1 (DEDT1)
            uint32_t driver_enable_deassertion_time_1     : 1;    // bit 17
            /// DEDT2 (DEDT2)
            uint32_t driver_enable_deassertion_time_2     : 1;    // bit 18
            /// DEDT3 (DEDT3)
            uint32_t driver_enable_deassertion_time_3     : 1;    // bit 19
            /// Driver Enable de-assertion time (DEDT4)
            uint32_t driver_enable_deassertion_time_4     : 1;    // bit 20
            /// DEAT0 (DEAT0)
            uint32_t driver_enable_assertion_time_0       : 1;    // bit 21
            /// DEAT1 (DEAT1)
            uint32_t driver_enable_assertion_time_1       : 1;    // bit 22
            /// DEAT2 (DEAT2)
            uint32_t driver_enable_assertion_time_2       : 1;    // bit 23
            /// DEAT3 (DEAT3)
            uint32_t driver_enable_assertion_time_3       : 1;    // bit 24
            /// Driver Enable assertion time (DEAT4)
            uint32_t driver_enable_assertion_time_4       : 1;    // bit 25
            /// Receiver timeout interrupt enable (RTOIE)
            uint32_t receiver_timeout_interrupt_enable    : 1;    // bit 26
            /// End of Block interrupt enable (EOBIE)
            uint32_t end_of_block_interrupt_enable        : 1;    // bit 27
            /// Word length (M1)
            uint32_t word_length_bit_1                    : 1;    // bit 28
            /// FIFO mode enable (FIFOEN)
            uint32_t fifo_enable                          : 1;    // bit 29
            /// TXFIFO empty interrupt enable (TXFEIE)
            uint32_t transmit_fifo_empty_interrupt_enable : 1;    // bit 30
            /// RXFIFO Full interrupt enable (RXFFIE)
            uint32_t receive_fifo_full_interrupt_enable   : 1;    // bit 31
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
            /// Synchronous Slave mode enable (SLVEN)
            uint32_t synchronous_follower_enable                                      : 1;    // bit 0
            /// (reserved)
            uint32_t                                                                  : 2;    // bits 1:2
            /// When the DSI_NSS bit is set, the NSS pin input is ignored (DIS_NSS)
            uint32_t disable_nss                                                      : 1;    // bit 3
            /// 7-bit Address Detection/4-bit Address Detection (ADDM7)
            uint32_t address_detection_mode_7_bit                                     : 1;    // bit 4
            /// LIN break detection length (LBDL)
            uint32_t local_interconnect_network_line_break_detection_length           : 1;    // bit 5
            /// LIN break detection interrupt enable (LBDIE)
            uint32_t local_interconnect_network_line_break_detection_interrupt_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                                                                  : 1;    // bit 7
            /// Last bit clock pulse (LBCL)
            uint32_t last_bit_clock_pulse                                             : 1;    // bit 8
            /// Clock phase (CPHA)
            uint32_t clock_phase                                                      : 1;    // bit 9
            /// Clock polarity (CPOL)
            uint32_t clock_polarity                                                   : 1;    // bit 10
            /// Clock enable (CLKEN)
            uint32_t clock_enable                                                     : 1;    // bit 11
            /// STOP bits (STOP)
            uint32_t stop                                                             : 2;    // bits 12:13
            /// LIN mode enable (LINEN)
            uint32_t local_interconnect_network_enable                                : 1;    // bit 14
            /// Swap TX/RX pins (SWAP)
            uint32_t swap_transmit_receive_pins                                       : 1;    // bit 15
            /// RX pin active level inversion (RXINV)
            uint32_t receive_pin_active_level_inversion                               : 1;    // bit 16
            /// TX pin active level inversion (TXINV)
            uint32_t transmit_pin_active_level_inversion                              : 1;    // bit 17
            /// Binary data inversion (DATAINV)
            uint32_t data_active_level_inversion                                      : 1;    // bit 18
            /// Most significant bit first (MSBFIRST)
            uint32_t most_significant_bit_first                                       : 1;    // bit 19
            /// Auto baud rate enable (ABREN)
            uint32_t auto_baud_rate_enable                                            : 1;    // bit 20
            /// ABRMOD0 (ABRMOD0)
            uint32_t auto_baud_rate_mode_0                                            : 1;    // bit 21
            /// Auto baud rate mode (ABRMOD1)
            uint32_t auto_baud_rate_mode_1                                            : 1;    // bit 22
            /// Receiver timeout enable (RTOEN)
            uint32_t receiver_timeout_enable                                          : 1;    // bit 23
            /// Address of the USART node (ADD0_3)
            uint32_t address_bits_0_to_3                                              : 4;    // bits 24:27
            /// Address of the USART node (ADD4_7)
            uint32_t address_bits_4_to_7                                              : 4;    // bits 28:31
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
            uint32_t error_interrupt_enable                                   : 1;    // bit 0
            /// Ir mode enable (IREN)
            uint32_t infrared_data_association_enable                         : 1;    // bit 1
            /// Ir low-power (IRLP)
            uint32_t infrared_data_association_low_power                      : 1;    // bit 2
            /// Half-duplex selection (HDSEL)
            uint32_t half_duplex_selection                                    : 1;    // bit 3
            /// Smartcard NACK enable (NACK)
            uint32_t smart_card_nack                                          : 1;    // bit 4
            /// Smartcard mode enable (SCEN)
            uint32_t smart_card_mode_enable                                   : 1;    // bit 5
            /// DMA enable receiver (DMAR)
            uint32_t direct_memory_access_receiver                            : 1;    // bit 6
            /// DMA enable transmitter (DMAT)
            uint32_t direct_memory_access_transmitter                         : 1;    // bit 7
            /// RTS enable (RTSE)
            uint32_t ready_to_send_enable                                     : 1;    // bit 8
            /// CTS enable (CTSE)
            uint32_t clear_to_send_enable                                     : 1;    // bit 9
            /// CTS interrupt enable (CTSIE)
            uint32_t clear_to_send_interrupt_enable                           : 1;    // bit 10
            /// One sample bit method enable (ONEBIT)
            uint32_t one_bit_sampling                                         : 1;    // bit 11
            /// Overrun Disable (OVRDIS)
            uint32_t overrun_disable                                          : 1;    // bit 12
            /// DMA Disable on Reception Error (DDRE)
            uint32_t dma_disable_on_reception_error                           : 1;    // bit 13
            /// Driver enable mode (DEM)
            uint32_t driver_enable_mode                                       : 1;    // bit 14
            /// Driver enable polarity selection (DEP)
            uint32_t driver_enable_polarity                                   : 1;    // bit 15
            /// (reserved)
            uint32_t                                                          : 1;    // bit 16
            /// Smartcard auto-retry count (SCARCNT)
            uint32_t smart_card_auto_retry_count                              : 3;    // bits 17:19
            /// Wakeup from Stop mode interrupt flag selection (WUS)
            uint32_t wakeup_from_stop_selection                               : 2;    // bits 20:21
            /// Wakeup from Stop mode interrupt enable (WUFIE)
            uint32_t wakeup_from_stop_interrupt_enable                        : 1;    // bit 22
            /// TXFIFO threshold interrupt enable (TXFTIE)
            uint32_t transmit_fifo_threshold_interrupt_enable                 : 1;    // bit 23
            /// Transmission Complete before guard time, interrupt enable (TCBGTIE)
            uint32_t transmission_complete_before_guard_time_interrupt_enable : 1;    // bit 24
            /// Receive FIFO threshold configuration (RXFTCFG)
            uint32_t receive_fifo_threshold_configuration                     : 3;    // bits 25:27
            /// RXFIFO threshold interrupt enable (RXFTIE)
            uint32_t receive_fifo_threshold_interrupt_enable                  : 1;    // bit 28
            /// TXFIFO threshold configuration (TXFTCFG)
            uint32_t transmit_fifo_threshold_configuration                    : 3;    // bits 29:31
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
            /// DIV_Fraction (BRR_0_3)
            uint32_t baud_rate_fraction_bits_0_to_3  : 4;    // bits 0:3
            /// DIV_Mantissa (BRR_4_15)
            uint32_t baud_rate_mantissa_bits_4_to_15 : 12;    // bits 4:15
            /// (reserved)
            uint32_t                                 : 16;    // bits 16:31
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
    /// Guard time and prescaler register (GTPR)
    struct GuardTimeAndPrescaler final {
        /// Default Constructor
        GuardTimeAndPrescaler()
            : whole{0u} {}
        /// Copy Constructor from volatile
        GuardTimeAndPrescaler(GuardTimeAndPrescaler volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        GuardTimeAndPrescaler(GuardTimeAndPrescaler const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        GuardTimeAndPrescaler(GuardTimeAndPrescaler&&) = delete;
        /// Parameterized Constructor for constant references
        explicit GuardTimeAndPrescaler(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit GuardTimeAndPrescaler(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~GuardTimeAndPrescaler() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Prescaler value (PSC)
            uint32_t prescaler_value : 8;    // bits 0:7
            /// Guard time value (GT)
            uint32_t guard_time      : 8;    // bits 8:15
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
        GuardTimeAndPrescaler& operator=(GuardTimeAndPrescaler&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(GuardTimeAndPrescaler volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(GuardTimeAndPrescaler const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<GuardTimeAndPrescaler>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(GuardTimeAndPrescaler) == 4UL, "Must be this exact size");
    /// Receiver timeout register (RTOR)
    struct ReceiveTimeout final {
        /// Default Constructor
        ReceiveTimeout()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveTimeout(ReceiveTimeout volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveTimeout(ReceiveTimeout const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveTimeout(ReceiveTimeout&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveTimeout(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveTimeout(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveTimeout() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Receiver timeout value (RTO)
            uint32_t receiver_timeout_value : 24;    // bits 0:23
            /// Block Length (BLEN)
            uint32_t block_length           : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveTimeout& operator=(ReceiveTimeout&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveTimeout volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveTimeout const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveTimeout>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveTimeout) == 4UL, "Must be this exact size");
    /// Request register (RQR)
    struct RequestRegister final {
        /// Default Constructor
        RequestRegister()
            : whole{0u} {}
        /// Copy Constructor from volatile
        RequestRegister(RequestRegister volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        RequestRegister(RequestRegister const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        RequestRegister(RequestRegister&&) = delete;
        /// Parameterized Constructor for constant references
        explicit RequestRegister(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit RequestRegister(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~RequestRegister() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Auto baud rate request (ABRRQ)
            uint32_t auto_baud_rate_request      : 1;    // bit 0
            /// Send break request (SBKRQ)
            uint32_t send_break_request          : 1;    // bit 1
            /// Mute mode request (MMRQ)
            uint32_t mute_mode_request           : 1;    // bit 2
            /// Receive data flush request (RXFRQ)
            uint32_t receive_data_flush_request  : 1;    // bit 3
            /// Transmit data flush request (TXFRQ)
            uint32_t transmit_data_flush_request : 1;    // bit 4
            /// (reserved)
            uint32_t                             : 27;    // bits 5:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        RequestRegister& operator=(RequestRegister&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(RequestRegister volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(RequestRegister const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<RequestRegister>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(RequestRegister) == 4UL, "Must be this exact size");
    /// Interrupt & status register (ISR)
    struct InterruptStatus final {
        /// Default Constructor
        InterruptStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptStatus(InterruptStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptStatus(InterruptStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptStatus(InterruptStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PE (PE)
            uint32_t parity_error                                 : 1;    // bit 0
            /// FE (FE)
            uint32_t framing_error                                : 1;    // bit 1
            /// NF (NF)
            uint32_t noise_flag                                   : 1;    // bit 2
            /// ORE (ORE)
            uint32_t overrun_error                                : 1;    // bit 3
            /// IDLE (IDLE)
            uint32_t idle                                         : 1;    // bit 4
            /// RXNE (RXNE)
            uint32_t receive_buffer_not_empty                     : 1;    // bit 5
            /// TC (TC)
            uint32_t transmit_complete                            : 1;    // bit 6
            /// TXE (TXE)
            uint32_t transmit_buffer_empty                        : 1;    // bit 7
            /// LBDF (LBDF)
            uint32_t local_interconnect_network_break_detect_flag : 1;    // bit 8
            /// CTSIF (CTSIF)
            uint32_t clear_to_send_interrupt_flag                 : 1;    // bit 9
            /// CTS (CTS)
            uint32_t clear_to_send                                : 1;    // bit 10
            /// RTOF (RTOF)
            uint32_t receiver_timeout_flag                        : 1;    // bit 11
            /// EOBF (EOBF)
            uint32_t end_of_block_flag                            : 1;    // bit 12
            /// SPI slave underrun error flag (UDR)
            uint32_t underrun                                     : 1;    // bit 13
            /// ABRE (ABRE)
            uint32_t auto_baud_rate_error                         : 1;    // bit 14
            /// ABRF (ABRF)
            uint32_t auto_baud_rate_detected                      : 1;    // bit 15
            /// BUSY (BUSY)
            uint32_t busy                                         : 1;    // bit 16
            /// CMF (CMF)
            uint32_t character_match_flag                         : 1;    // bit 17
            /// SBKF (SBKF)
            uint32_t send_break_flag                              : 1;    // bit 18
            /// RWU (RWU)
            uint32_t receive_wakeup                               : 1;    // bit 19
            /// WUF (WUF)
            uint32_t wakeup_flag                                  : 1;    // bit 20
            /// TEACK (TEACK)
            uint32_t transmitter_enable_acknowledge               : 1;    // bit 21
            /// REACK (REACK)
            uint32_t receiver_enable_acknowledge                  : 1;    // bit 22
            /// TXFIFO Empty (TXFE)
            uint32_t transmit_fifo_empty                          : 1;    // bit 23
            /// RXFIFO Full (RXFF)
            uint32_t receive_fifo_full                            : 1;    // bit 24
            /// Transmission complete before guard time flag (TCBGT)
            uint32_t transmission_complete_before_guard_time      : 1;    // bit 25
            /// RXFIFO threshold flag (RXFT)
            uint32_t receive_fifo_threshold_flag                  : 1;    // bit 26
            /// TXFIFO threshold flag (TXFT)
            uint32_t transmit_fifo_threshold_flag                 : 1;    // bit 27
            /// (reserved)
            uint32_t                                              : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptStatus& operator=(InterruptStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptStatus) == 4UL, "Must be this exact size");
    /// Interrupt flag clear register (ICR)
    struct InterruptClear final {
        /// Default Constructor
        InterruptClear()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptClear(InterruptClear volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptClear(InterruptClear const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptClear(InterruptClear&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptClear(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptClear(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptClear() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Parity error clear flag (PECF)
            uint32_t parity_error_clear_flag                            : 1;    // bit 0
            /// Framing error clear flag (FECF)
            uint32_t framing_error_clear_flag                           : 1;    // bit 1
            /// Noise detected clear flag (NCF)
            uint32_t noise_clear_flag                                   : 1;    // bit 2
            /// Overrun error clear flag (ORECF)
            uint32_t overrun_error_clear_flag                           : 1;    // bit 3
            /// Idle line detected clear flag (IDLECF)
            uint32_t idle_line_clear_flag                               : 1;    // bit 4
            /// TXFIFO empty clear flag (TXFECF)
            uint32_t transmit_fifo_empty_clear_flag                     : 1;    // bit 5
            /// Transmission complete clear flag (TCCF)
            uint32_t transmission_complete_clear_flag                   : 1;    // bit 6
            /// Transmission complete before Guard time clear flag (TCBGTC)
            uint32_t transmission_complete_before_guard_time_clear_flag : 1;    // bit 7
            /// LIN break detection clear flag (LBDCF)
            uint32_t lin_break_detection_clear_flag                     : 1;    // bit 8
            /// CTS clear flag (CTSCF)
            uint32_t clear_to_send_clear_flag                           : 1;    // bit 9
            /// (reserved)
            uint32_t                                                    : 1;    // bit 10
            /// Receiver timeout clear flag (RTOCF)
            uint32_t receiver_timeout_clear_flag                        : 1;    // bit 11
            /// End of block clear flag (EOBCF)
            uint32_t end_of_block_clear_flag                            : 1;    // bit 12
            /// SPI slave underrun clear flag (UDRCF)
            uint32_t underrun_clear_flag                                : 1;    // bit 13
            /// (reserved)
            uint32_t                                                    : 3;    // bits 14:16
            /// Character match clear flag (CMCF)
            uint32_t character_match_clear_flag                         : 1;    // bit 17
            /// (reserved)
            uint32_t                                                    : 2;    // bits 18:19
            /// Wakeup from Stop mode clear flag (WUCF)
            uint32_t wakeup_from_stop_clear_flag                        : 1;    // bit 20
            /// (reserved)
            uint32_t                                                    : 11;    // bits 21:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptClear& operator=(InterruptClear&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptClear volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptClear const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptClear>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptClear) == 4UL, "Must be this exact size");
    /// Receive data register (RDR)
    struct ReceiveData final {
        /// Default Constructor
        ReceiveData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveData(ReceiveData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveData(ReceiveData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveData(ReceiveData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Receive data value (RDR)
            uint32_t receive_data : 9;    // bits 0:8
            /// (reserved)
            uint32_t              : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveData& operator=(ReceiveData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveData) == 4UL, "Must be this exact size");
    /// Transmit data register (TDR)
    struct TransmitData final {
        /// Default Constructor
        TransmitData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitData(TransmitData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitData(TransmitData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitData(TransmitData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Transmit data value (TDR)
            uint32_t transmit_data : 9;    // bits 0:8
            /// (reserved)
            uint32_t               : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitData& operator=(TransmitData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitData) == 4UL, "Must be this exact size");
    /// USART prescaler register (PRESC)
    struct Prescaler final {
        /// Default Constructor
        Prescaler()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Prescaler(Prescaler volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Prescaler(Prescaler const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Prescaler(Prescaler&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Prescaler(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Prescaler(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Prescaler() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Clock prescaler (PRESCALER)
            uint32_t prescaler_value : 4;    // bits 0:3
            /// (reserved)
            uint32_t                 : 28;    // bits 4:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Prescaler& operator=(Prescaler&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Prescaler volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Prescaler const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Prescaler>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Prescaler) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// Control register 2 (CR2)
    Control2 control2;    // offset 0x4UL
    /// Control register 3 (CR3)
    Control3 control3;    // offset 0x8UL
    /// Baud rate register (BRR)
    BaudRate baud_rate;    // offset 0xcUL
    /// Guard time and prescaler register (GTPR)
    GuardTimeAndPrescaler guard_time_and_prescaler;    // offset 0x10UL
    /// Receiver timeout register (RTOR)
    ReceiveTimeout receive_timeout;    // offset 0x14UL
    /// Request register (RQR)
    RequestRegister request_register;    // offset 0x18UL
    /// Interrupt & status register (ISR)
    InterruptStatus interrupt_status;    // offset 0x1cUL
    /// Interrupt flag clear register (ICR)
    InterruptClear interrupt_clear;    // offset 0x20UL
    /// Receive data register (RDR)
    ReceiveData receive_data;    // offset 0x24UL
    /// Transmit data register (TDR)
    TransmitData transmit_data;    // offset 0x28UL
    /// USART prescaler register (PRESC)
    Prescaler prescaler;    // offset 0x2cUL
    uint32_t : 32;          // offset 0x30UL
    uint32_t : 32;          // offset 0x34UL
    uint32_t : 32;          // offset 0x38UL
    uint32_t : 32;          // offset 0x3cUL
    uint32_t : 32;          // offset 0x40UL
    uint32_t : 32;          // offset 0x44UL
    uint32_t : 32;          // offset 0x48UL
    uint32_t : 32;          // offset 0x4cUL
    uint32_t : 32;          // offset 0x50UL
    uint32_t : 32;          // offset 0x54UL
    uint32_t : 32;          // offset 0x58UL
    uint32_t : 32;          // offset 0x5cUL
    uint32_t : 32;          // offset 0x60UL
    uint32_t : 32;          // offset 0x64UL
    uint32_t : 32;          // offset 0x68UL
    uint32_t : 32;          // offset 0x6cUL
    uint32_t : 32;          // offset 0x70UL
    uint32_t : 32;          // offset 0x74UL
    uint32_t : 32;          // offset 0x78UL
    uint32_t : 32;          // offset 0x7cUL
    uint32_t : 32;          // offset 0x80UL
    uint32_t : 32;          // offset 0x84UL
    uint32_t : 32;          // offset 0x88UL
    uint32_t : 32;          // offset 0x8cUL
    uint32_t : 32;          // offset 0x90UL
    uint32_t : 32;          // offset 0x94UL
    uint32_t : 32;          // offset 0x98UL
    uint32_t : 32;          // offset 0x9cUL
    uint32_t : 32;          // offset 0xa0UL
    uint32_t : 32;          // offset 0xa4UL
    uint32_t : 32;          // offset 0xa8UL
    uint32_t : 32;          // offset 0xacUL
    uint32_t : 32;          // offset 0xb0UL
    uint32_t : 32;          // offset 0xb4UL
    uint32_t : 32;          // offset 0xb8UL
    uint32_t : 32;          // offset 0xbcUL
    uint32_t : 32;          // offset 0xc0UL
    uint32_t : 32;          // offset 0xc4UL
    uint32_t : 32;          // offset 0xc8UL
    uint32_t : 32;          // offset 0xccUL
    uint32_t : 32;          // offset 0xd0UL
    uint32_t : 32;          // offset 0xd4UL
    uint32_t : 32;          // offset 0xd8UL
    uint32_t : 32;          // offset 0xdcUL
    uint32_t : 32;          // offset 0xe0UL
    uint32_t : 32;          // offset 0xe4UL
    uint32_t : 32;          // offset 0xe8UL
    uint32_t : 32;          // offset 0xecUL
    uint32_t : 32;          // offset 0xf0UL
    uint32_t : 32;          // offset 0xf4UL
    uint32_t : 32;          // offset 0xf8UL
    uint32_t : 32;          // offset 0xfcUL
    uint32_t : 32;          // offset 0x100UL
    uint32_t : 32;          // offset 0x104UL
    uint32_t : 32;          // offset 0x108UL
    uint32_t : 32;          // offset 0x10cUL
    uint32_t : 32;          // offset 0x110UL
    uint32_t : 32;          // offset 0x114UL
    uint32_t : 32;          // offset 0x118UL
    uint32_t : 32;          // offset 0x11cUL
    uint32_t : 32;          // offset 0x120UL
    uint32_t : 32;          // offset 0x124UL
    uint32_t : 32;          // offset 0x128UL
    uint32_t : 32;          // offset 0x12cUL
    uint32_t : 32;          // offset 0x130UL
    uint32_t : 32;          // offset 0x134UL
    uint32_t : 32;          // offset 0x138UL
    uint32_t : 32;          // offset 0x13cUL
    uint32_t : 32;          // offset 0x140UL
    uint32_t : 32;          // offset 0x144UL
    uint32_t : 32;          // offset 0x148UL
    uint32_t : 32;          // offset 0x14cUL
    uint32_t : 32;          // offset 0x150UL
    uint32_t : 32;          // offset 0x154UL
    uint32_t : 32;          // offset 0x158UL
    uint32_t : 32;          // offset 0x15cUL
    uint32_t : 32;          // offset 0x160UL
    uint32_t : 32;          // offset 0x164UL
    uint32_t : 32;          // offset 0x168UL
    uint32_t : 32;          // offset 0x16cUL
    uint32_t : 32;          // offset 0x170UL
    uint32_t : 32;          // offset 0x174UL
    uint32_t : 32;          // offset 0x178UL
    uint32_t : 32;          // offset 0x17cUL
    uint32_t : 32;          // offset 0x180UL
    uint32_t : 32;          // offset 0x184UL
    uint32_t : 32;          // offset 0x188UL
    uint32_t : 32;          // offset 0x18cUL
    uint32_t : 32;          // offset 0x190UL
    uint32_t : 32;          // offset 0x194UL
    uint32_t : 32;          // offset 0x198UL
    uint32_t : 32;          // offset 0x19cUL
    uint32_t : 32;          // offset 0x1a0UL
    uint32_t : 32;          // offset 0x1a4UL
    uint32_t : 32;          // offset 0x1a8UL
    uint32_t : 32;          // offset 0x1acUL
    uint32_t : 32;          // offset 0x1b0UL
    uint32_t : 32;          // offset 0x1b4UL
    uint32_t : 32;          // offset 0x1b8UL
    uint32_t : 32;          // offset 0x1bcUL
    uint32_t : 32;          // offset 0x1c0UL
    uint32_t : 32;          // offset 0x1c4UL
    uint32_t : 32;          // offset 0x1c8UL
    uint32_t : 32;          // offset 0x1ccUL
    uint32_t : 32;          // offset 0x1d0UL
    uint32_t : 32;          // offset 0x1d4UL
    uint32_t : 32;          // offset 0x1d8UL
    uint32_t : 32;          // offset 0x1dcUL
    uint32_t : 32;          // offset 0x1e0UL
    uint32_t : 32;          // offset 0x1e4UL
    uint32_t : 32;          // offset 0x1e8UL
    uint32_t : 32;          // offset 0x1ecUL
    uint32_t : 32;          // offset 0x1f0UL
    uint32_t : 32;          // offset 0x1f4UL
    uint32_t : 32;          // offset 0x1f8UL
    uint32_t : 32;          // offset 0x1fcUL
    uint32_t : 32;          // offset 0x200UL
    uint32_t : 32;          // offset 0x204UL
    uint32_t : 32;          // offset 0x208UL
    uint32_t : 32;          // offset 0x20cUL
    uint32_t : 32;          // offset 0x210UL
    uint32_t : 32;          // offset 0x214UL
    uint32_t : 32;          // offset 0x218UL
    uint32_t : 32;          // offset 0x21cUL
    uint32_t : 32;          // offset 0x220UL
    uint32_t : 32;          // offset 0x224UL
    uint32_t : 32;          // offset 0x228UL
    uint32_t : 32;          // offset 0x22cUL
    uint32_t : 32;          // offset 0x230UL
    uint32_t : 32;          // offset 0x234UL
    uint32_t : 32;          // offset 0x238UL
    uint32_t : 32;          // offset 0x23cUL
    uint32_t : 32;          // offset 0x240UL
    uint32_t : 32;          // offset 0x244UL
    uint32_t : 32;          // offset 0x248UL
    uint32_t : 32;          // offset 0x24cUL
    uint32_t : 32;          // offset 0x250UL
    uint32_t : 32;          // offset 0x254UL
    uint32_t : 32;          // offset 0x258UL
    uint32_t : 32;          // offset 0x25cUL
    uint32_t : 32;          // offset 0x260UL
    uint32_t : 32;          // offset 0x264UL
    uint32_t : 32;          // offset 0x268UL
    uint32_t : 32;          // offset 0x26cUL
    uint32_t : 32;          // offset 0x270UL
    uint32_t : 32;          // offset 0x274UL
    uint32_t : 32;          // offset 0x278UL
    uint32_t : 32;          // offset 0x27cUL
    uint32_t : 32;          // offset 0x280UL
    uint32_t : 32;          // offset 0x284UL
    uint32_t : 32;          // offset 0x288UL
    uint32_t : 32;          // offset 0x28cUL
    uint32_t : 32;          // offset 0x290UL
    uint32_t : 32;          // offset 0x294UL
    uint32_t : 32;          // offset 0x298UL
    uint32_t : 32;          // offset 0x29cUL
    uint32_t : 32;          // offset 0x2a0UL
    uint32_t : 32;          // offset 0x2a4UL
    uint32_t : 32;          // offset 0x2a8UL
    uint32_t : 32;          // offset 0x2acUL
    uint32_t : 32;          // offset 0x2b0UL
    uint32_t : 32;          // offset 0x2b4UL
    uint32_t : 32;          // offset 0x2b8UL
    uint32_t : 32;          // offset 0x2bcUL
    uint32_t : 32;          // offset 0x2c0UL
    uint32_t : 32;          // offset 0x2c4UL
    uint32_t : 32;          // offset 0x2c8UL
    uint32_t : 32;          // offset 0x2ccUL
    uint32_t : 32;          // offset 0x2d0UL
    uint32_t : 32;          // offset 0x2d4UL
    uint32_t : 32;          // offset 0x2d8UL
    uint32_t : 32;          // offset 0x2dcUL
    uint32_t : 32;          // offset 0x2e0UL
    uint32_t : 32;          // offset 0x2e4UL
    uint32_t : 32;          // offset 0x2e8UL
    uint32_t : 32;          // offset 0x2ecUL
    uint32_t : 32;          // offset 0x2f0UL
    uint32_t : 32;          // offset 0x2f4UL
    uint32_t : 32;          // offset 0x2f8UL
    uint32_t : 32;          // offset 0x2fcUL
    uint32_t : 32;          // offset 0x300UL
    uint32_t : 32;          // offset 0x304UL
    uint32_t : 32;          // offset 0x308UL
    uint32_t : 32;          // offset 0x30cUL
    uint32_t : 32;          // offset 0x310UL
    uint32_t : 32;          // offset 0x314UL
    uint32_t : 32;          // offset 0x318UL
    uint32_t : 32;          // offset 0x31cUL
    uint32_t : 32;          // offset 0x320UL
    uint32_t : 32;          // offset 0x324UL
    uint32_t : 32;          // offset 0x328UL
    uint32_t : 32;          // offset 0x32cUL
    uint32_t : 32;          // offset 0x330UL
    uint32_t : 32;          // offset 0x334UL
    uint32_t : 32;          // offset 0x338UL
    uint32_t : 32;          // offset 0x33cUL
    uint32_t : 32;          // offset 0x340UL
    uint32_t : 32;          // offset 0x344UL
    uint32_t : 32;          // offset 0x348UL
    uint32_t : 32;          // offset 0x34cUL
    uint32_t : 32;          // offset 0x350UL
    uint32_t : 32;          // offset 0x354UL
    uint32_t : 32;          // offset 0x358UL
    uint32_t : 32;          // offset 0x35cUL
    uint32_t : 32;          // offset 0x360UL
    uint32_t : 32;          // offset 0x364UL
    uint32_t : 32;          // offset 0x368UL
    uint32_t : 32;          // offset 0x36cUL
    uint32_t : 32;          // offset 0x370UL
    uint32_t : 32;          // offset 0x374UL
    uint32_t : 32;          // offset 0x378UL
    uint32_t : 32;          // offset 0x37cUL
    uint32_t : 32;          // offset 0x380UL
    uint32_t : 32;          // offset 0x384UL
    uint32_t : 32;          // offset 0x388UL
    uint32_t : 32;          // offset 0x38cUL
    uint32_t : 32;          // offset 0x390UL
    uint32_t : 32;          // offset 0x394UL
    uint32_t : 32;          // offset 0x398UL
    uint32_t : 32;          // offset 0x39cUL
    uint32_t : 32;          // offset 0x3a0UL
    uint32_t : 32;          // offset 0x3a4UL
    uint32_t : 32;          // offset 0x3a8UL
    uint32_t : 32;          // offset 0x3acUL
    uint32_t : 32;          // offset 0x3b0UL
    uint32_t : 32;          // offset 0x3b4UL
    uint32_t : 32;          // offset 0x3b8UL
    uint32_t : 32;          // offset 0x3bcUL
    uint32_t : 32;          // offset 0x3c0UL
    uint32_t : 32;          // offset 0x3c4UL
    uint32_t : 32;          // offset 0x3c8UL
    uint32_t : 32;          // offset 0x3ccUL
    uint32_t : 32;          // offset 0x3d0UL
    uint32_t : 32;          // offset 0x3d4UL
    uint32_t : 32;          // offset 0x3d8UL
    uint32_t : 32;          // offset 0x3dcUL
    uint32_t : 32;          // offset 0x3e0UL
    uint32_t : 32;          // offset 0x3e4UL
    uint32_t : 32;          // offset 0x3e8UL
    uint32_t : 32;          // offset 0x3ecUL
    uint32_t : 32;          // offset 0x3f0UL
    uint32_t : 32;          // offset 0x3f4UL
    uint32_t : 32;          // offset 0x3f8UL
    uint32_t : 32;          // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<UniversalSynchronousAsynchronousReceiverTransmitter>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, control3) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, baud_rate) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, guard_time_and_prescaler) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, receive_timeout) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, request_register) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, interrupt_status) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, interrupt_clear) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, receive_data) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, transmit_data) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(UniversalSynchronousAsynchronousReceiverTransmitter, prescaler) == 0x2cUL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(UniversalSynchronousAsynchronousReceiverTransmitter) == 0x400UL, "Must be this exact size");

/// The external volatile universal_synchronous_asynchronous_receiver_transmitter which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart1;

/// The external volatile universal_synchronous_asynchronous_receiver_transmitter which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart2;

/// The external volatile universal_synchronous_asynchronous_receiver_transmitter which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart3;

/// The external volatile universal_synchronous_asynchronous_receiver_transmitter which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern UniversalSynchronousAsynchronousReceiverTransmitter volatile usart6;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_UNIVERSALSYNCHRONOUSASYNCHRONOUSRECEIVERTRANSMITTER__HPP_
