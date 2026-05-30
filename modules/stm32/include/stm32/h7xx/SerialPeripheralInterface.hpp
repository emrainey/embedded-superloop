
#ifndef STM32_H7XX_SERIALPERIPHERALINTERFACE__HPP_
#define STM32_H7XX_SERIALPERIPHERALINTERFACE__HPP_

/// @file
/// Auto Generated Structure Definitions for SerialPeripheralInterface from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Serial peripheral interface
struct SerialPeripheralInterface final {
    /// Baud Rate Divider
    enum class BaudRateDivider : uint32_t {
        By2 = 0U,      ///< f_pclk / 2
        By4 = 1U,      ///< f_pclk / 4
        By8 = 2U,      ///< f_pclk / 8
        By16 = 3U,     ///< f_pclk / 16
        By32 = 4U,     ///< f_pclk / 32
        By64 = 5U,     ///< f_pclk / 64
        By128 = 6U,    ///< f_pclk / 128
        By256 = 7U,    ///< f_pclk / 256
    };

    /// control register 1 (CR1)
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
            /// Serial Peripheral Enable (SPE)
            uint32_t serial_peripheral_interface_enable     : 1;    // bit 0
            /// (reserved)
            uint32_t                                        : 7;    // bits 1:7
            /// Master automatic SUSP in Receive mode (MASRX)
            uint32_t leader_receive_auto_suspend            : 1;    // bit 8
            /// Master transfer start (CSTART)
            uint32_t communication_start                    : 1;    // bit 9
            /// Master SUSPend request (CSUSP)
            uint32_t communication_suspend                  : 1;    // bit 10
            /// Rx/Tx direction at Half-duplex mode (HDDIR)
            uint32_t half_duplex_direction                  : 1;    // bit 11
            /// Internal SS signal input level (SSI)
            uint32_t internal_follower_select               : 1;    // bit 12
            /// 32-bit CRC polynomial configuration (CRC33_17)
            uint32_t cyclic_redundancy_check_bits_33_to_17  : 1;    // bit 13
            /// CRC calculation initialization pattern control for receiver (RCRCI)
            uint32_t receive_cyclic_redundancy_check_clear  : 1;    // bit 14
            /// CRC calculation initialization pattern control for transmitter (TCRCI)
            uint32_t transmit_cyclic_redundancy_check_clear : 1;    // bit 15
            /// Locking the AF configuration of associated IOs (IOLOCK)
            uint32_t input_output_lock                      : 1;    // bit 16
            /// (reserved)
            uint32_t                                        : 15;    // bits 17:31
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
    /// control register 2 (CR2)
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
            /// Number of data at current transfer (TSIZE)
            uint32_t transfer_size          : 16;    // bits 0:15
            /// Number of data transfer extension to be reload into TSIZE just when a previous (TSER)
            uint32_t transfer_serialization : 16;    // bits 16:31
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
    /// configuration register 1 (CFG1)
    struct Configuration1 final {
        /// Default Constructor
        Configuration1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Configuration1(Configuration1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Configuration1(Configuration1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Configuration1(Configuration1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Configuration1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Configuration1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Configuration1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Number of bits in at single SPI data frame (DSIZE)
            uint32_t data_size                            : 5;    // bits 0:4
            /// threshold level (FTHVL)
            uint32_t fifo_threshold_level                 : 4;    // bits 5:8
            /// Behavior of slave transmitter at underrun condition (UDRCFG)
            uint32_t underrun_configuration               : 2;    // bits 9:10
            /// Detection of underrun condition at slave transmitter (UDRDET)
            uint32_t underrun_detection                   : 2;    // bits 11:12
            /// (reserved)
            uint32_t                                      : 1;    // bit 13
            /// Rx DMA stream enable (RXDMAEN)
            uint32_t receive_direct_memory_access_enable  : 1;    // bit 14
            /// Tx DMA stream enable (TXDMAEN)
            uint32_t transmit_direct_memory_access_enable : 1;    // bit 15
            /// Length of CRC frame to be transacted and compared (CRCSIZE)
            uint32_t cyclic_redundancy_check_size         : 5;    // bits 16:20
            /// (reserved)
            uint32_t                                      : 1;    // bit 21
            /// Hardware CRC computation enable (CRCEN)
            uint32_t cyclic_redundancy_check_enable       : 1;    // bit 22
            /// (reserved)
            uint32_t                                      : 5;    // bits 23:27
            /// Master baud rate (MBR)
            uint32_t baud_rate_prescaler                  : 3;    // bits 28:30
            /// (reserved)
            uint32_t                                      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Configuration1& operator=(Configuration1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Configuration1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Configuration1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Configuration1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Configuration1) == 4UL, "Must be this exact size");
    /// configuration register 2 (CFG2)
    struct Configuration2 final {
        /// Default Constructor
        Configuration2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Configuration2(Configuration2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Configuration2(Configuration2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Configuration2(Configuration2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Configuration2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Configuration2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Configuration2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Master SS Idleness (MSSI)
            uint32_t leader_inter_data_idleness        : 4;    // bits 0:3
            /// Master Inter-Data Idleness (MIDI)
            uint32_t minimum_inter_data_idleness       : 4;    // bits 4:7
            /// (reserved)
            uint32_t                                   : 7;    // bits 8:14
            /// Swap functionality of MISO and MOSI pins (IOSWP)
            uint32_t input_output_swap                 : 1;    // bit 15
            /// (reserved)
            uint32_t                                   : 1;    // bit 16
            /// SPI Communication Mode (COMM)
            uint32_t communication_mode                : 2;    // bits 17:18
            /// Serial Protocol (SP)
            uint32_t serial_protocol                   : 3;    // bits 19:21
            /// SPI Master (MASTER)
            uint32_t leader_mode                       : 1;    // bit 22
            /// Data frame format (LSBFRST)
            uint32_t least_significant_bit_first       : 1;    // bit 23
            /// Clock phase (CPHA)
            uint32_t clock_phase                       : 1;    // bit 24
            /// Clock polarity (CPOL)
            uint32_t clock_polarity                    : 1;    // bit 25
            /// Software management of SS signal input (SSM)
            uint32_t software_follower_management      : 1;    // bit 26
            /// (reserved)
            uint32_t                                   : 1;    // bit 27
            /// SS input/output polarity (SSIOP)
            uint32_t internal_follower_select_polarity : 1;    // bit 28
            /// SS output enable (SSOE)
            uint32_t follower_output_enable            : 1;    // bit 29
            /// SS output management in master mode (SSOM)
            uint32_t follower_select_output_management : 1;    // bit 30
            /// Alternate function GPIOs control (AFCNTR)
            uint32_t alternative_function_control      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Configuration2& operator=(Configuration2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Configuration2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Configuration2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Configuration2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Configuration2) == 4UL, "Must be this exact size");
    /// Interrupt Enable Register (IER)
    struct InterruptEnable final {
        /// Default Constructor
        InterruptEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptEnable(InterruptEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptEnable(InterruptEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptEnable(InterruptEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXP Interrupt Enable (RXPIE)
            uint32_t receive_packet_interrupt_enable                : 1;    // bit 0
            /// TXP interrupt enable (TXPIE)
            uint32_t transmit_packet_interrupt_enable               : 1;    // bit 1
            /// DXP interrupt enabled (DPXPIE)
            uint32_t duplex_packet_interrupt_enable                 : 1;    // bit 2
            /// EOT, SUSP and TXC interrupt enable (EOTIE)
            uint32_t end_of_transfer_interrupt_enable               : 1;    // bit 3
            /// TXTFIE interrupt enable (TXTFIE)
            uint32_t transmit_transfer_filled_interrupt_enable      : 1;    // bit 4
            /// UDR interrupt enable (UDRIE)
            uint32_t underrun_interrupt_enable                      : 1;    // bit 5
            /// OVR interrupt enable (OVRIE)
            uint32_t overrun_interrupt_enable                       : 1;    // bit 6
            /// CRC Interrupt enable (CRCEIE)
            uint32_t cyclic_redundancy_check_error_interrupt_enable : 1;    // bit 7
            /// TIFRE interrupt enable (TIFREIE)
            uint32_t ti_frame_format_error_interrupt_enable         : 1;    // bit 8
            /// Mode Fault interrupt enable (MODFIE)
            uint32_t mode_fault_interrupt_enable                    : 1;    // bit 9
            /// Additional number of transactions reload interrupt enable (TSERFIE)
            uint32_t transfer_serialization_flag_interrupt_enable   : 1;    // bit 10
            /// (reserved)
            uint32_t                                                : 21;    // bits 11:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptEnable& operator=(InterruptEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptEnable) == 4UL, "Must be this exact size");
    /// Status Register (SR)
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
            /// Rx-Packet available (RXP)
            uint32_t receive_packet_available      : 1;    // bit 0
            /// Tx-Packet space available (TXP)
            uint32_t transmit_packet_available     : 1;    // bit 1
            /// Duplex Packet (DXP)
            uint32_t duplex_packet_available       : 1;    // bit 2
            /// End Of Transfer (EOT)
            uint32_t end_of_transfer               : 1;    // bit 3
            /// Transmission Transfer Filled (TXTF)
            uint32_t transmit_transfer_filled      : 1;    // bit 4
            /// Underrun at slave transmission mode (UDR)
            uint32_t underrun                      : 1;    // bit 5
            /// Overrun (OVR)
            uint32_t overrun                       : 1;    // bit 6
            /// CRC Error (CRCE)
            uint32_t cyclic_redundancy_check_error : 1;    // bit 7
            /// TI frame format error (TIFRE)
            uint32_t ti_frame_format_error         : 1;    // bit 8
            /// Mode Fault (MODF)
            uint32_t mode_fault                    : 1;    // bit 9
            /// Additional number of SPI data to be transacted was reload (TSERF)
            uint32_t transfer_serialization_flag   : 1;    // bit 10
            /// SUSPend (SUSP)
            uint32_t suspend_status                : 1;    // bit 11
            /// TxFIFO transmission complete (TXC)
            uint32_t transmit_complete             : 1;    // bit 12
            /// RxFIFO Packing LeVeL (RXPLVL)
            uint32_t receive_packet_level          : 2;    // bits 13:14
            /// RxFIFO Word Not Empty (RXWNE)
            uint32_t receive_word_not_empty        : 1;    // bit 15
            /// Number of data frames remaining in current TSIZE session (CTSIZE)
            uint32_t current_transfer_size         : 16;    // bits 16:31
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
    /// Interrupt/Status Flags Clear Register (IFCR)
    struct InterruptFlagClear final {
        /// Default Constructor
        InterruptFlagClear()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptFlagClear(InterruptFlagClear volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptFlagClear(InterruptFlagClear const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptFlagClear(InterruptFlagClear&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptFlagClear(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptFlagClear(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptFlagClear() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                     : 3;    // bits 0:2
            /// End Of Transfer flag clear (EOTC)
            uint32_t end_of_transfer_clear               : 1;    // bit 3
            /// Transmission Transfer Filled flag clear (TXTFC)
            uint32_t transmit_transfer_filled_clear      : 1;    // bit 4
            /// Underrun flag clear (UDRC)
            uint32_t underrun_clear                      : 1;    // bit 5
            /// Overrun flag clear (OVRC)
            uint32_t overrun_clear                       : 1;    // bit 6
            /// CRC Error flag clear (CRCEC)
            uint32_t cyclic_redundancy_check_error_clear : 1;    // bit 7
            /// TI frame format error flag clear (TIFREC)
            uint32_t ti_frame_format_error_clear         : 1;    // bit 8
            /// Mode Fault flag clear (MODFC)
            uint32_t mode_fault_clear                    : 1;    // bit 9
            /// TSERFC flag clear (TSERFC)
            uint32_t transfer_serialization_flag_clear   : 1;    // bit 10
            /// SUSPend flag clear (SUSPC)
            uint32_t suspend_clear                       : 1;    // bit 11
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
        InterruptFlagClear& operator=(InterruptFlagClear&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptFlagClear volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptFlagClear const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptFlagClear>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptFlagClear) == 4UL, "Must be this exact size");
    /// Transmit Data Register (TXDR)
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
            /// Transmit data register (TXDR)
            uint32_t transmit_data : 32;    // bits 0:31
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
    /// Receive Data Register (RXDR)
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
            /// Receive data register (RXDR)
            uint32_t receive_data : 32;    // bits 0:31
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
    /// Polynomial Register (CRCPOLY)
    struct CyclicRedundancyCheckPolynomial final {
        /// Default Constructor
        CyclicRedundancyCheckPolynomial()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CyclicRedundancyCheckPolynomial(CyclicRedundancyCheckPolynomial volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CyclicRedundancyCheckPolynomial(CyclicRedundancyCheckPolynomial const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CyclicRedundancyCheckPolynomial(CyclicRedundancyCheckPolynomial&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CyclicRedundancyCheckPolynomial(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CyclicRedundancyCheckPolynomial(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CyclicRedundancyCheckPolynomial() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC polynomial register (CRCPOLY)
            uint32_t coefficients : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CyclicRedundancyCheckPolynomial& operator=(CyclicRedundancyCheckPolynomial&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CyclicRedundancyCheckPolynomial volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CyclicRedundancyCheckPolynomial const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CyclicRedundancyCheckPolynomial>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CyclicRedundancyCheckPolynomial) == 4UL, "Must be this exact size");
    /// Transmitter CRC Register (TXCRC)
    struct TransmitCyclicRedundancyCheck final {
        /// Default Constructor
        TransmitCyclicRedundancyCheck()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitCyclicRedundancyCheck(TransmitCyclicRedundancyCheck volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitCyclicRedundancyCheck(TransmitCyclicRedundancyCheck const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitCyclicRedundancyCheck(TransmitCyclicRedundancyCheck&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitCyclicRedundancyCheck(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitCyclicRedundancyCheck(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitCyclicRedundancyCheck() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC register for transmitter (TXCRC)
            uint32_t transmit_cyclic_redundancy_check : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitCyclicRedundancyCheck& operator=(TransmitCyclicRedundancyCheck&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitCyclicRedundancyCheck volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitCyclicRedundancyCheck const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitCyclicRedundancyCheck>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitCyclicRedundancyCheck) == 4UL, "Must be this exact size");
    /// Receiver CRC Register (RXCRC)
    struct ReceiveCyclicRedundancyCheck final {
        /// Default Constructor
        ReceiveCyclicRedundancyCheck()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveCyclicRedundancyCheck(ReceiveCyclicRedundancyCheck volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveCyclicRedundancyCheck(ReceiveCyclicRedundancyCheck const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveCyclicRedundancyCheck(ReceiveCyclicRedundancyCheck&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveCyclicRedundancyCheck(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveCyclicRedundancyCheck(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveCyclicRedundancyCheck() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC register for receiver (RXCRC)
            uint32_t receive_cyclic_redundancy_check : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveCyclicRedundancyCheck& operator=(ReceiveCyclicRedundancyCheck&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveCyclicRedundancyCheck volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveCyclicRedundancyCheck const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveCyclicRedundancyCheck>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveCyclicRedundancyCheck) == 4UL, "Must be this exact size");
    /// Underrun Data Register (UDRDR)
    struct UnderrunData final {
        /// Default Constructor
        UnderrunData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        UnderrunData(UnderrunData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        UnderrunData(UnderrunData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        UnderrunData(UnderrunData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit UnderrunData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit UnderrunData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~UnderrunData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Data at slave underrun condition (UDRDR)
            uint32_t underrun_data : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        UnderrunData& operator=(UnderrunData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(UnderrunData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(UnderrunData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<UnderrunData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(UnderrunData) == 4UL, "Must be this exact size");
    /// configuration register (CGFR)
    struct Configuration final {
        /// Default Constructor
        Configuration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Configuration(Configuration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Configuration(Configuration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Configuration(Configuration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Configuration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Configuration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Configuration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// I2S mode selection (I2SMOD)
            uint32_t i2s_mode                                    : 1;    // bit 0
            /// I2S configuration mode (I2SCFG)
            uint32_t i2s_configuration_mode                      : 3;    // bits 1:3
            /// I2S standard selection (I2SSTD)
            uint32_t i2s_standard_selection                      : 2;    // bits 4:5
            /// (reserved)
            uint32_t                                             : 1;    // bit 6
            /// PCM frame synchronization (PCMSYNC)
            uint32_t pulse_code_modulation_frame_synchronization : 1;    // bit 7
            /// Data length to be transferred (DATLEN)
            uint32_t data_length                                 : 2;    // bits 8:9
            /// Channel length (number of bits per audio channel) (CHLEN)
            uint32_t channel_length                              : 1;    // bit 10
            /// Serial audio clock polarity (CKPOL)
            uint32_t clock_polarity                              : 1;    // bit 11
            /// Word select inversion (FIXCH)
            uint32_t fixed_channel                               : 1;    // bit 12
            /// Fixed channel length in SLAVE (WSINV)
            uint32_t word_select_inversion                       : 1;    // bit 13
            /// Data format (DATFMT)
            uint32_t data_format                                 : 1;    // bit 14
            /// (reserved)
            uint32_t                                             : 1;    // bit 15
            /// I2S linear prescaler (I2SDIV)
            uint32_t i2s_divider                                 : 8;    // bits 16:23
            /// Odd factor for the prescaler (ODD)
            uint32_t odd                                         : 1;    // bit 24
            /// Master clock output enable (MCKOE)
            uint32_t leader_clock_output_enable                  : 1;    // bit 25
            /// (reserved)
            uint32_t                                             : 6;    // bits 26:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Configuration& operator=(Configuration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Configuration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Configuration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Configuration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Configuration) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// control register 2 (CR2)
    Control2 control2;    // offset 0x4UL
    /// configuration register 1 (CFG1)
    Configuration1 configuration1;    // offset 0x8UL
    /// configuration register 2 (CFG2)
    Configuration2 configuration2;    // offset 0xcUL
    /// Interrupt Enable Register (IER)
    InterruptEnable interrupt_enable;    // offset 0x10UL
    /// Status Register (SR)
    Status status;    // offset 0x14UL
    /// Interrupt/Status Flags Clear Register (IFCR)
    InterruptFlagClear interrupt_flag_clear;    // offset 0x18UL
    uint32_t : 32;                              // offset 0x1cUL
    /// Transmit Data Register (TXDR)
    TransmitData transmit_data;    // offset 0x20UL
    uint32_t : 32;                 // offset 0x24UL
    uint32_t : 32;                 // offset 0x28UL
    uint32_t : 32;                 // offset 0x2cUL
    /// Receive Data Register (RXDR)
    ReceiveData receive_data;    // offset 0x30UL
    uint32_t : 32;               // offset 0x34UL
    uint32_t : 32;               // offset 0x38UL
    uint32_t : 32;               // offset 0x3cUL
    /// Polynomial Register (CRCPOLY)
    CyclicRedundancyCheckPolynomial coefficients;    // offset 0x40UL
    /// Transmitter CRC Register (TXCRC)
    TransmitCyclicRedundancyCheck transmit_cyclic_redundancy_check;    // offset 0x44UL
    /// Receiver CRC Register (RXCRC)
    ReceiveCyclicRedundancyCheck receive_cyclic_redundancy_check;    // offset 0x48UL
    /// Underrun Data Register (UDRDR)
    UnderrunData underrun_data;    // offset 0x4cUL
    /// configuration register (CGFR)
    Configuration configuration;    // offset 0x50UL
    uint32_t : 32;                  // offset 0x54UL
    uint32_t : 32;                  // offset 0x58UL
    uint32_t : 32;                  // offset 0x5cUL
    uint32_t : 32;                  // offset 0x60UL
    uint32_t : 32;                  // offset 0x64UL
    uint32_t : 32;                  // offset 0x68UL
    uint32_t : 32;                  // offset 0x6cUL
    uint32_t : 32;                  // offset 0x70UL
    uint32_t : 32;                  // offset 0x74UL
    uint32_t : 32;                  // offset 0x78UL
    uint32_t : 32;                  // offset 0x7cUL
    uint32_t : 32;                  // offset 0x80UL
    uint32_t : 32;                  // offset 0x84UL
    uint32_t : 32;                  // offset 0x88UL
    uint32_t : 32;                  // offset 0x8cUL
    uint32_t : 32;                  // offset 0x90UL
    uint32_t : 32;                  // offset 0x94UL
    uint32_t : 32;                  // offset 0x98UL
    uint32_t : 32;                  // offset 0x9cUL
    uint32_t : 32;                  // offset 0xa0UL
    uint32_t : 32;                  // offset 0xa4UL
    uint32_t : 32;                  // offset 0xa8UL
    uint32_t : 32;                  // offset 0xacUL
    uint32_t : 32;                  // offset 0xb0UL
    uint32_t : 32;                  // offset 0xb4UL
    uint32_t : 32;                  // offset 0xb8UL
    uint32_t : 32;                  // offset 0xbcUL
    uint32_t : 32;                  // offset 0xc0UL
    uint32_t : 32;                  // offset 0xc4UL
    uint32_t : 32;                  // offset 0xc8UL
    uint32_t : 32;                  // offset 0xccUL
    uint32_t : 32;                  // offset 0xd0UL
    uint32_t : 32;                  // offset 0xd4UL
    uint32_t : 32;                  // offset 0xd8UL
    uint32_t : 32;                  // offset 0xdcUL
    uint32_t : 32;                  // offset 0xe0UL
    uint32_t : 32;                  // offset 0xe4UL
    uint32_t : 32;                  // offset 0xe8UL
    uint32_t : 32;                  // offset 0xecUL
    uint32_t : 32;                  // offset 0xf0UL
    uint32_t : 32;                  // offset 0xf4UL
    uint32_t : 32;                  // offset 0xf8UL
    uint32_t : 32;                  // offset 0xfcUL
    uint32_t : 32;                  // offset 0x100UL
    uint32_t : 32;                  // offset 0x104UL
    uint32_t : 32;                  // offset 0x108UL
    uint32_t : 32;                  // offset 0x10cUL
    uint32_t : 32;                  // offset 0x110UL
    uint32_t : 32;                  // offset 0x114UL
    uint32_t : 32;                  // offset 0x118UL
    uint32_t : 32;                  // offset 0x11cUL
    uint32_t : 32;                  // offset 0x120UL
    uint32_t : 32;                  // offset 0x124UL
    uint32_t : 32;                  // offset 0x128UL
    uint32_t : 32;                  // offset 0x12cUL
    uint32_t : 32;                  // offset 0x130UL
    uint32_t : 32;                  // offset 0x134UL
    uint32_t : 32;                  // offset 0x138UL
    uint32_t : 32;                  // offset 0x13cUL
    uint32_t : 32;                  // offset 0x140UL
    uint32_t : 32;                  // offset 0x144UL
    uint32_t : 32;                  // offset 0x148UL
    uint32_t : 32;                  // offset 0x14cUL
    uint32_t : 32;                  // offset 0x150UL
    uint32_t : 32;                  // offset 0x154UL
    uint32_t : 32;                  // offset 0x158UL
    uint32_t : 32;                  // offset 0x15cUL
    uint32_t : 32;                  // offset 0x160UL
    uint32_t : 32;                  // offset 0x164UL
    uint32_t : 32;                  // offset 0x168UL
    uint32_t : 32;                  // offset 0x16cUL
    uint32_t : 32;                  // offset 0x170UL
    uint32_t : 32;                  // offset 0x174UL
    uint32_t : 32;                  // offset 0x178UL
    uint32_t : 32;                  // offset 0x17cUL
    uint32_t : 32;                  // offset 0x180UL
    uint32_t : 32;                  // offset 0x184UL
    uint32_t : 32;                  // offset 0x188UL
    uint32_t : 32;                  // offset 0x18cUL
    uint32_t : 32;                  // offset 0x190UL
    uint32_t : 32;                  // offset 0x194UL
    uint32_t : 32;                  // offset 0x198UL
    uint32_t : 32;                  // offset 0x19cUL
    uint32_t : 32;                  // offset 0x1a0UL
    uint32_t : 32;                  // offset 0x1a4UL
    uint32_t : 32;                  // offset 0x1a8UL
    uint32_t : 32;                  // offset 0x1acUL
    uint32_t : 32;                  // offset 0x1b0UL
    uint32_t : 32;                  // offset 0x1b4UL
    uint32_t : 32;                  // offset 0x1b8UL
    uint32_t : 32;                  // offset 0x1bcUL
    uint32_t : 32;                  // offset 0x1c0UL
    uint32_t : 32;                  // offset 0x1c4UL
    uint32_t : 32;                  // offset 0x1c8UL
    uint32_t : 32;                  // offset 0x1ccUL
    uint32_t : 32;                  // offset 0x1d0UL
    uint32_t : 32;                  // offset 0x1d4UL
    uint32_t : 32;                  // offset 0x1d8UL
    uint32_t : 32;                  // offset 0x1dcUL
    uint32_t : 32;                  // offset 0x1e0UL
    uint32_t : 32;                  // offset 0x1e4UL
    uint32_t : 32;                  // offset 0x1e8UL
    uint32_t : 32;                  // offset 0x1ecUL
    uint32_t : 32;                  // offset 0x1f0UL
    uint32_t : 32;                  // offset 0x1f4UL
    uint32_t : 32;                  // offset 0x1f8UL
    uint32_t : 32;                  // offset 0x1fcUL
    uint32_t : 32;                  // offset 0x200UL
    uint32_t : 32;                  // offset 0x204UL
    uint32_t : 32;                  // offset 0x208UL
    uint32_t : 32;                  // offset 0x20cUL
    uint32_t : 32;                  // offset 0x210UL
    uint32_t : 32;                  // offset 0x214UL
    uint32_t : 32;                  // offset 0x218UL
    uint32_t : 32;                  // offset 0x21cUL
    uint32_t : 32;                  // offset 0x220UL
    uint32_t : 32;                  // offset 0x224UL
    uint32_t : 32;                  // offset 0x228UL
    uint32_t : 32;                  // offset 0x22cUL
    uint32_t : 32;                  // offset 0x230UL
    uint32_t : 32;                  // offset 0x234UL
    uint32_t : 32;                  // offset 0x238UL
    uint32_t : 32;                  // offset 0x23cUL
    uint32_t : 32;                  // offset 0x240UL
    uint32_t : 32;                  // offset 0x244UL
    uint32_t : 32;                  // offset 0x248UL
    uint32_t : 32;                  // offset 0x24cUL
    uint32_t : 32;                  // offset 0x250UL
    uint32_t : 32;                  // offset 0x254UL
    uint32_t : 32;                  // offset 0x258UL
    uint32_t : 32;                  // offset 0x25cUL
    uint32_t : 32;                  // offset 0x260UL
    uint32_t : 32;                  // offset 0x264UL
    uint32_t : 32;                  // offset 0x268UL
    uint32_t : 32;                  // offset 0x26cUL
    uint32_t : 32;                  // offset 0x270UL
    uint32_t : 32;                  // offset 0x274UL
    uint32_t : 32;                  // offset 0x278UL
    uint32_t : 32;                  // offset 0x27cUL
    uint32_t : 32;                  // offset 0x280UL
    uint32_t : 32;                  // offset 0x284UL
    uint32_t : 32;                  // offset 0x288UL
    uint32_t : 32;                  // offset 0x28cUL
    uint32_t : 32;                  // offset 0x290UL
    uint32_t : 32;                  // offset 0x294UL
    uint32_t : 32;                  // offset 0x298UL
    uint32_t : 32;                  // offset 0x29cUL
    uint32_t : 32;                  // offset 0x2a0UL
    uint32_t : 32;                  // offset 0x2a4UL
    uint32_t : 32;                  // offset 0x2a8UL
    uint32_t : 32;                  // offset 0x2acUL
    uint32_t : 32;                  // offset 0x2b0UL
    uint32_t : 32;                  // offset 0x2b4UL
    uint32_t : 32;                  // offset 0x2b8UL
    uint32_t : 32;                  // offset 0x2bcUL
    uint32_t : 32;                  // offset 0x2c0UL
    uint32_t : 32;                  // offset 0x2c4UL
    uint32_t : 32;                  // offset 0x2c8UL
    uint32_t : 32;                  // offset 0x2ccUL
    uint32_t : 32;                  // offset 0x2d0UL
    uint32_t : 32;                  // offset 0x2d4UL
    uint32_t : 32;                  // offset 0x2d8UL
    uint32_t : 32;                  // offset 0x2dcUL
    uint32_t : 32;                  // offset 0x2e0UL
    uint32_t : 32;                  // offset 0x2e4UL
    uint32_t : 32;                  // offset 0x2e8UL
    uint32_t : 32;                  // offset 0x2ecUL
    uint32_t : 32;                  // offset 0x2f0UL
    uint32_t : 32;                  // offset 0x2f4UL
    uint32_t : 32;                  // offset 0x2f8UL
    uint32_t : 32;                  // offset 0x2fcUL
    uint32_t : 32;                  // offset 0x300UL
    uint32_t : 32;                  // offset 0x304UL
    uint32_t : 32;                  // offset 0x308UL
    uint32_t : 32;                  // offset 0x30cUL
    uint32_t : 32;                  // offset 0x310UL
    uint32_t : 32;                  // offset 0x314UL
    uint32_t : 32;                  // offset 0x318UL
    uint32_t : 32;                  // offset 0x31cUL
    uint32_t : 32;                  // offset 0x320UL
    uint32_t : 32;                  // offset 0x324UL
    uint32_t : 32;                  // offset 0x328UL
    uint32_t : 32;                  // offset 0x32cUL
    uint32_t : 32;                  // offset 0x330UL
    uint32_t : 32;                  // offset 0x334UL
    uint32_t : 32;                  // offset 0x338UL
    uint32_t : 32;                  // offset 0x33cUL
    uint32_t : 32;                  // offset 0x340UL
    uint32_t : 32;                  // offset 0x344UL
    uint32_t : 32;                  // offset 0x348UL
    uint32_t : 32;                  // offset 0x34cUL
    uint32_t : 32;                  // offset 0x350UL
    uint32_t : 32;                  // offset 0x354UL
    uint32_t : 32;                  // offset 0x358UL
    uint32_t : 32;                  // offset 0x35cUL
    uint32_t : 32;                  // offset 0x360UL
    uint32_t : 32;                  // offset 0x364UL
    uint32_t : 32;                  // offset 0x368UL
    uint32_t : 32;                  // offset 0x36cUL
    uint32_t : 32;                  // offset 0x370UL
    uint32_t : 32;                  // offset 0x374UL
    uint32_t : 32;                  // offset 0x378UL
    uint32_t : 32;                  // offset 0x37cUL
    uint32_t : 32;                  // offset 0x380UL
    uint32_t : 32;                  // offset 0x384UL
    uint32_t : 32;                  // offset 0x388UL
    uint32_t : 32;                  // offset 0x38cUL
    uint32_t : 32;                  // offset 0x390UL
    uint32_t : 32;                  // offset 0x394UL
    uint32_t : 32;                  // offset 0x398UL
    uint32_t : 32;                  // offset 0x39cUL
    uint32_t : 32;                  // offset 0x3a0UL
    uint32_t : 32;                  // offset 0x3a4UL
    uint32_t : 32;                  // offset 0x3a8UL
    uint32_t : 32;                  // offset 0x3acUL
    uint32_t : 32;                  // offset 0x3b0UL
    uint32_t : 32;                  // offset 0x3b4UL
    uint32_t : 32;                  // offset 0x3b8UL
    uint32_t : 32;                  // offset 0x3bcUL
    uint32_t : 32;                  // offset 0x3c0UL
    uint32_t : 32;                  // offset 0x3c4UL
    uint32_t : 32;                  // offset 0x3c8UL
    uint32_t : 32;                  // offset 0x3ccUL
    uint32_t : 32;                  // offset 0x3d0UL
    uint32_t : 32;                  // offset 0x3d4UL
    uint32_t : 32;                  // offset 0x3d8UL
    uint32_t : 32;                  // offset 0x3dcUL
    uint32_t : 32;                  // offset 0x3e0UL
    uint32_t : 32;                  // offset 0x3e4UL
    uint32_t : 32;                  // offset 0x3e8UL
    uint32_t : 32;                  // offset 0x3ecUL
    uint32_t : 32;                  // offset 0x3f0UL
    uint32_t : 32;                  // offset 0x3f4UL
    uint32_t : 32;                  // offset 0x3f8UL
    uint32_t : 32;                  // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<SerialPeripheralInterface>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(SerialPeripheralInterface, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, configuration1) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, configuration2) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, interrupt_enable) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, status) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, interrupt_flag_clear) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, transmit_data) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, receive_data) == 0x30UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, coefficients) == 0x40UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, transmit_cyclic_redundancy_check) == 0x44UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, receive_cyclic_redundancy_check) == 0x48UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, underrun_data) == 0x4cUL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, configuration) == 0x50UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(SerialPeripheralInterface) == 0x400UL, "Must be this exact size");

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_SERIALPERIPHERALINTERFACE__HPP_
