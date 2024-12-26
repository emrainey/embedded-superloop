
#ifndef STM32_REGISTERS_SPI_HPP_
#define STM32_REGISTERS_SPI_HPP_

/// @file
/// Auto Generated Structure Definitions for SPI1 from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Serial peripheral interface (SPI1)
struct SerialPeripheralInterface final {
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
            /// Clock phase (CPHA)
            uint32_t clock_phase                      : 1;    // bit 0
            /// Clock polarity (CPOL)
            uint32_t clock_polarity                   : 1;    // bit 1
            /// Master selection (MSTR)
            uint32_t leader                           : 1;    // bit 2
            /// Baud rate control (BR)
            uint32_t baud_rate                        : 3;    // bits 3:5
            /// SPI enable (SPE)
            uint32_t spi_enable                       : 1;    // bit 6
            /// Frame format (LSBFIRST)
            uint32_t lsbfirst                         : 1;    // bit 7
            /// Internal slave select (SSI)
            uint32_t internal_follower_select         : 1;    // bit 8
            /// Software slave management (SSM)
            uint32_t software_follower_management     : 1;    // bit 9
            /// Receive only (RXONLY)
            uint32_t rxonly                           : 1;    // bit 10
            /// Data frame format (DFF)
            uint32_t data_frame_format                : 1;    // bit 11
            /// CRC transfer next (CRCNEXT)
            uint32_t crc_next                         : 1;    // bit 12
            /// Hardware CRC calculation enable (CRCEN)
            uint32_t crc_enable                       : 1;    // bit 13
            /// Output enable in bidirectional mode (BIDIOE)
            uint32_t bidirectional_data_output_enable : 1;    // bit 14
            /// Bidirectional data mode enable (BIDIMODE)
            uint32_t bidirectional_data_mode          : 1;    // bit 15
            /// (reserved)
            uint32_t                                  : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
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
        /// Converts the baud rate divider to a uint32_t divisor
        inline uint32_t baud_rate_divider(void) const { return (1U << (bits.baud_rate + 1U)); }
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
            /// Rx buffer DMA enable (RXDMAEN)
            uint32_t receive_dma_enable                        : 1;    // bit 0
            /// Tx buffer DMA enable (TXDMAEN)
            uint32_t transmit_dma_enable                       : 1;    // bit 1
            /// SS output enable (SSOE)
            uint32_t follower_output_enable                    : 1;    // bit 2
            /// (reserved)
            uint32_t                                           : 1;    // bit 3
            /// Frame format (FRF)
            uint32_t frame_format                              : 1;    // bit 4
            /// Error interrupt enable (ERRIE)
            uint32_t error_interrupt_enable                    : 1;    // bit 5
            /// RX buffer not empty interrupt enable (RXNEIE)
            uint32_t receive_buffer_not_empty_interrupt_enable : 1;    // bit 6
            /// Tx buffer empty interrupt enable (TXEIE)
            uint32_t transmit_buffer_empty_interrupt_enable    : 1;    // bit 7
            /// (reserved)
            uint32_t                                           : 24;    // bits 8:31
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
    /// status register (SR)
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
            /// Receive buffer not empty (RXNE)
            uint32_t receive_buffer_not_empty    : 1;    // bit 0
            /// Transmit buffer empty (TXE)
            uint32_t transmit_buffer_empty       : 1;    // bit 1
            /// Channel side (CHSIDE)
            uint32_t channel_side                : 1;    // bit 2
            /// Underrun flag (UDR)
            uint32_t underrun                    : 1;    // bit 3
            /// CRC error flag (CRCERR)
            uint32_t crc_error                   : 1;    // bit 4
            /// Mode fault (MODF)
            uint32_t mode_fault                  : 1;    // bit 5
            /// Overrun flag (OVR)
            uint32_t overrun                     : 1;    // bit 6
            /// Busy flag (BSY)
            uint32_t busy                        : 1;    // bit 7
            /// TI frame format error (TIFRFE)
            uint32_t transmit_frame_format_error : 1;    // bit 8
            /// (reserved)
            uint32_t                             : 23;    // bits 9:31
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
    /// data register (DR)
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
            /// Data register (DR)
            uint32_t data : 16;    // bits 0:15
            /// (reserved)
            uint32_t      : 16;    // bits 16:31
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
    /// CRC polynomial register (CRCPR)
    struct CrcPolynomial final {
        /// Default Constructor
        CrcPolynomial()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CrcPolynomial(CrcPolynomial volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CrcPolynomial(CrcPolynomial const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CrcPolynomial(CrcPolynomial&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CrcPolynomial(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CrcPolynomial(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CrcPolynomial() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CRC polynomial register (CRCPOLY)
            uint32_t coefficients : 16;    // bits 0:15
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
        CrcPolynomial& operator=(CrcPolynomial&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CrcPolynomial volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CrcPolynomial const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CrcPolynomial>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CrcPolynomial) == 4UL, "Must be this exact size");
    /// RX CRC register (RXCRCR)
    struct ReceiveCRC final {
        /// Default Constructor
        ReceiveCRC()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveCRC(ReceiveCRC volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveCRC(ReceiveCRC const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveCRC(ReceiveCRC&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveCRC(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveCRC(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveCRC() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Rx CRC register (RxCRC)
            uint32_t crc_value : 16;    // bits 0:15
            /// (reserved)
            uint32_t           : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveCRC& operator=(ReceiveCRC&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveCRC volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveCRC const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveCRC>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveCRC) == 4UL, "Must be this exact size");
    /// TX CRC register (TXCRCR)
    struct TransmitCRC final {
        /// Default Constructor
        TransmitCRC()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitCRC(TransmitCRC volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitCRC(TransmitCRC const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitCRC(TransmitCRC&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitCRC(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitCRC(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitCRC() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Tx CRC register (TxCRC)
            uint32_t crc_value : 16;    // bits 0:15
            /// (reserved)
            uint32_t           : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitCRC& operator=(TransmitCRC&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitCRC volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitCRC const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitCRC>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitCRC) == 4UL, "Must be this exact size");
    /// I2S configuration register (I2SCFGR)
    struct InterIntegratedCircuitSoundConfiguration final {
        /// Default Constructor
        InterIntegratedCircuitSoundConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterIntegratedCircuitSoundConfiguration(InterIntegratedCircuitSoundConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterIntegratedCircuitSoundConfiguration(InterIntegratedCircuitSoundConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterIntegratedCircuitSoundConfiguration(InterIntegratedCircuitSoundConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterIntegratedCircuitSoundConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterIntegratedCircuitSoundConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterIntegratedCircuitSoundConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Channel length (number of bits per audio channel) (CHLEN)
            uint32_t chlen      : 1;    // bit 0
            /// Data length to be transferred (DATLEN)
            uint32_t datlen     : 2;    // bits 1:2
            /// Steady state clock polarity (CKPOL)
            uint32_t ckpol      : 1;    // bit 3
            /// I2S standard selection (I2SSTD)
            uint32_t i2sstd     : 2;    // bits 4:5
            /// (reserved)
            uint32_t            : 1;    // bit 6
            /// PCM frame synchronization (PCMSYNC)
            uint32_t pcmsync    : 1;    // bit 7
            /// I2S configuration mode (I2SCFG)
            uint32_t i2scfg     : 2;    // bits 8:9
            /// I2S Enable (I2SE)
            uint32_t i2s_enable : 1;    // bit 10
            /// I2S mode selection (I2SMOD)
            uint32_t i2smod     : 1;    // bit 11
            /// (reserved)
            uint32_t            : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterIntegratedCircuitSoundConfiguration& operator=(InterIntegratedCircuitSoundConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterIntegratedCircuitSoundConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterIntegratedCircuitSoundConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterIntegratedCircuitSoundConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterIntegratedCircuitSoundConfiguration) == 4UL, "Must be this exact size");
    /// I2S prescaler register (I2SPR)
    struct InterIntegratedCircuitSoundPrescaler final {
        /// Default Constructor
        InterIntegratedCircuitSoundPrescaler()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterIntegratedCircuitSoundPrescaler(InterIntegratedCircuitSoundPrescaler volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterIntegratedCircuitSoundPrescaler(InterIntegratedCircuitSoundPrescaler const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterIntegratedCircuitSoundPrescaler(InterIntegratedCircuitSoundPrescaler&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterIntegratedCircuitSoundPrescaler(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterIntegratedCircuitSoundPrescaler(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterIntegratedCircuitSoundPrescaler() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// I2S Linear prescaler (I2SDIV)
            uint32_t i2s_divider                : 8;    // bits 0:7
            /// Odd factor for the prescaler (ODD)
            uint32_t odd                        : 1;    // bit 8
            /// Master clock output enable (MCKOE)
            uint32_t leader_clock_output_enable : 1;    // bit 9
            /// (reserved)
            uint32_t                            : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterIntegratedCircuitSoundPrescaler& operator=(InterIntegratedCircuitSoundPrescaler&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterIntegratedCircuitSoundPrescaler volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterIntegratedCircuitSoundPrescaler const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterIntegratedCircuitSoundPrescaler>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterIntegratedCircuitSoundPrescaler) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// control register 2 (CR2)
    Control2 control2;    // offset 0x4UL
    /// status register (SR)
    Status status;    // offset 0x8UL
    /// data register (DR)
    Data data;    // offset 0xcUL
    /// CRC polynomial register (CRCPR)
    CrcPolynomial crc_polynomial;    // offset 0x10UL
    /// RX CRC register (RXCRCR)
    ReceiveCRC receive_crc;    // offset 0x14UL
    /// TX CRC register (TXCRCR)
    TransmitCRC transmit_crc;    // offset 0x18UL
    /// I2S configuration register (I2SCFGR)
    InterIntegratedCircuitSoundConfiguration i2s_configuration;    // offset 0x1cUL
    /// I2S prescaler register (I2SPR)
    InterIntegratedCircuitSoundPrescaler i2s_prescaler;    // offset 0x20UL
    uint32_t : 32;                                         // offset 0x24UL
    uint32_t : 32;                                         // offset 0x28UL
    uint32_t : 32;                                         // offset 0x2cUL
    uint32_t : 32;                                         // offset 0x30UL
    uint32_t : 32;                                         // offset 0x34UL
    uint32_t : 32;                                         // offset 0x38UL
    uint32_t : 32;                                         // offset 0x3cUL
    uint32_t : 32;                                         // offset 0x40UL
    uint32_t : 32;                                         // offset 0x44UL
    uint32_t : 32;                                         // offset 0x48UL
    uint32_t : 32;                                         // offset 0x4cUL
    uint32_t : 32;                                         // offset 0x50UL
    uint32_t : 32;                                         // offset 0x54UL
    uint32_t : 32;                                         // offset 0x58UL
    uint32_t : 32;                                         // offset 0x5cUL
    uint32_t : 32;                                         // offset 0x60UL
    uint32_t : 32;                                         // offset 0x64UL
    uint32_t : 32;                                         // offset 0x68UL
    uint32_t : 32;                                         // offset 0x6cUL
    uint32_t : 32;                                         // offset 0x70UL
    uint32_t : 32;                                         // offset 0x74UL
    uint32_t : 32;                                         // offset 0x78UL
    uint32_t : 32;                                         // offset 0x7cUL
    uint32_t : 32;                                         // offset 0x80UL
    uint32_t : 32;                                         // offset 0x84UL
    uint32_t : 32;                                         // offset 0x88UL
    uint32_t : 32;                                         // offset 0x8cUL
    uint32_t : 32;                                         // offset 0x90UL
    uint32_t : 32;                                         // offset 0x94UL
    uint32_t : 32;                                         // offset 0x98UL
    uint32_t : 32;                                         // offset 0x9cUL
    uint32_t : 32;                                         // offset 0xa0UL
    uint32_t : 32;                                         // offset 0xa4UL
    uint32_t : 32;                                         // offset 0xa8UL
    uint32_t : 32;                                         // offset 0xacUL
    uint32_t : 32;                                         // offset 0xb0UL
    uint32_t : 32;                                         // offset 0xb4UL
    uint32_t : 32;                                         // offset 0xb8UL
    uint32_t : 32;                                         // offset 0xbcUL
    uint32_t : 32;                                         // offset 0xc0UL
    uint32_t : 32;                                         // offset 0xc4UL
    uint32_t : 32;                                         // offset 0xc8UL
    uint32_t : 32;                                         // offset 0xccUL
    uint32_t : 32;                                         // offset 0xd0UL
    uint32_t : 32;                                         // offset 0xd4UL
    uint32_t : 32;                                         // offset 0xd8UL
    uint32_t : 32;                                         // offset 0xdcUL
    uint32_t : 32;                                         // offset 0xe0UL
    uint32_t : 32;                                         // offset 0xe4UL
    uint32_t : 32;                                         // offset 0xe8UL
    uint32_t : 32;                                         // offset 0xecUL
    uint32_t : 32;                                         // offset 0xf0UL
    uint32_t : 32;                                         // offset 0xf4UL
    uint32_t : 32;                                         // offset 0xf8UL
    uint32_t : 32;                                         // offset 0xfcUL
    uint32_t : 32;                                         // offset 0x100UL
    uint32_t : 32;                                         // offset 0x104UL
    uint32_t : 32;                                         // offset 0x108UL
    uint32_t : 32;                                         // offset 0x10cUL
    uint32_t : 32;                                         // offset 0x110UL
    uint32_t : 32;                                         // offset 0x114UL
    uint32_t : 32;                                         // offset 0x118UL
    uint32_t : 32;                                         // offset 0x11cUL
    uint32_t : 32;                                         // offset 0x120UL
    uint32_t : 32;                                         // offset 0x124UL
    uint32_t : 32;                                         // offset 0x128UL
    uint32_t : 32;                                         // offset 0x12cUL
    uint32_t : 32;                                         // offset 0x130UL
    uint32_t : 32;                                         // offset 0x134UL
    uint32_t : 32;                                         // offset 0x138UL
    uint32_t : 32;                                         // offset 0x13cUL
    uint32_t : 32;                                         // offset 0x140UL
    uint32_t : 32;                                         // offset 0x144UL
    uint32_t : 32;                                         // offset 0x148UL
    uint32_t : 32;                                         // offset 0x14cUL
    uint32_t : 32;                                         // offset 0x150UL
    uint32_t : 32;                                         // offset 0x154UL
    uint32_t : 32;                                         // offset 0x158UL
    uint32_t : 32;                                         // offset 0x15cUL
    uint32_t : 32;                                         // offset 0x160UL
    uint32_t : 32;                                         // offset 0x164UL
    uint32_t : 32;                                         // offset 0x168UL
    uint32_t : 32;                                         // offset 0x16cUL
    uint32_t : 32;                                         // offset 0x170UL
    uint32_t : 32;                                         // offset 0x174UL
    uint32_t : 32;                                         // offset 0x178UL
    uint32_t : 32;                                         // offset 0x17cUL
    uint32_t : 32;                                         // offset 0x180UL
    uint32_t : 32;                                         // offset 0x184UL
    uint32_t : 32;                                         // offset 0x188UL
    uint32_t : 32;                                         // offset 0x18cUL
    uint32_t : 32;                                         // offset 0x190UL
    uint32_t : 32;                                         // offset 0x194UL
    uint32_t : 32;                                         // offset 0x198UL
    uint32_t : 32;                                         // offset 0x19cUL
    uint32_t : 32;                                         // offset 0x1a0UL
    uint32_t : 32;                                         // offset 0x1a4UL
    uint32_t : 32;                                         // offset 0x1a8UL
    uint32_t : 32;                                         // offset 0x1acUL
    uint32_t : 32;                                         // offset 0x1b0UL
    uint32_t : 32;                                         // offset 0x1b4UL
    uint32_t : 32;                                         // offset 0x1b8UL
    uint32_t : 32;                                         // offset 0x1bcUL
    uint32_t : 32;                                         // offset 0x1c0UL
    uint32_t : 32;                                         // offset 0x1c4UL
    uint32_t : 32;                                         // offset 0x1c8UL
    uint32_t : 32;                                         // offset 0x1ccUL
    uint32_t : 32;                                         // offset 0x1d0UL
    uint32_t : 32;                                         // offset 0x1d4UL
    uint32_t : 32;                                         // offset 0x1d8UL
    uint32_t : 32;                                         // offset 0x1dcUL
    uint32_t : 32;                                         // offset 0x1e0UL
    uint32_t : 32;                                         // offset 0x1e4UL
    uint32_t : 32;                                         // offset 0x1e8UL
    uint32_t : 32;                                         // offset 0x1ecUL
    uint32_t : 32;                                         // offset 0x1f0UL
    uint32_t : 32;                                         // offset 0x1f4UL
    uint32_t : 32;                                         // offset 0x1f8UL
    uint32_t : 32;                                         // offset 0x1fcUL
    uint32_t : 32;                                         // offset 0x200UL
    uint32_t : 32;                                         // offset 0x204UL
    uint32_t : 32;                                         // offset 0x208UL
    uint32_t : 32;                                         // offset 0x20cUL
    uint32_t : 32;                                         // offset 0x210UL
    uint32_t : 32;                                         // offset 0x214UL
    uint32_t : 32;                                         // offset 0x218UL
    uint32_t : 32;                                         // offset 0x21cUL
    uint32_t : 32;                                         // offset 0x220UL
    uint32_t : 32;                                         // offset 0x224UL
    uint32_t : 32;                                         // offset 0x228UL
    uint32_t : 32;                                         // offset 0x22cUL
    uint32_t : 32;                                         // offset 0x230UL
    uint32_t : 32;                                         // offset 0x234UL
    uint32_t : 32;                                         // offset 0x238UL
    uint32_t : 32;                                         // offset 0x23cUL
    uint32_t : 32;                                         // offset 0x240UL
    uint32_t : 32;                                         // offset 0x244UL
    uint32_t : 32;                                         // offset 0x248UL
    uint32_t : 32;                                         // offset 0x24cUL
    uint32_t : 32;                                         // offset 0x250UL
    uint32_t : 32;                                         // offset 0x254UL
    uint32_t : 32;                                         // offset 0x258UL
    uint32_t : 32;                                         // offset 0x25cUL
    uint32_t : 32;                                         // offset 0x260UL
    uint32_t : 32;                                         // offset 0x264UL
    uint32_t : 32;                                         // offset 0x268UL
    uint32_t : 32;                                         // offset 0x26cUL
    uint32_t : 32;                                         // offset 0x270UL
    uint32_t : 32;                                         // offset 0x274UL
    uint32_t : 32;                                         // offset 0x278UL
    uint32_t : 32;                                         // offset 0x27cUL
    uint32_t : 32;                                         // offset 0x280UL
    uint32_t : 32;                                         // offset 0x284UL
    uint32_t : 32;                                         // offset 0x288UL
    uint32_t : 32;                                         // offset 0x28cUL
    uint32_t : 32;                                         // offset 0x290UL
    uint32_t : 32;                                         // offset 0x294UL
    uint32_t : 32;                                         // offset 0x298UL
    uint32_t : 32;                                         // offset 0x29cUL
    uint32_t : 32;                                         // offset 0x2a0UL
    uint32_t : 32;                                         // offset 0x2a4UL
    uint32_t : 32;                                         // offset 0x2a8UL
    uint32_t : 32;                                         // offset 0x2acUL
    uint32_t : 32;                                         // offset 0x2b0UL
    uint32_t : 32;                                         // offset 0x2b4UL
    uint32_t : 32;                                         // offset 0x2b8UL
    uint32_t : 32;                                         // offset 0x2bcUL
    uint32_t : 32;                                         // offset 0x2c0UL
    uint32_t : 32;                                         // offset 0x2c4UL
    uint32_t : 32;                                         // offset 0x2c8UL
    uint32_t : 32;                                         // offset 0x2ccUL
    uint32_t : 32;                                         // offset 0x2d0UL
    uint32_t : 32;                                         // offset 0x2d4UL
    uint32_t : 32;                                         // offset 0x2d8UL
    uint32_t : 32;                                         // offset 0x2dcUL
    uint32_t : 32;                                         // offset 0x2e0UL
    uint32_t : 32;                                         // offset 0x2e4UL
    uint32_t : 32;                                         // offset 0x2e8UL
    uint32_t : 32;                                         // offset 0x2ecUL
    uint32_t : 32;                                         // offset 0x2f0UL
    uint32_t : 32;                                         // offset 0x2f4UL
    uint32_t : 32;                                         // offset 0x2f8UL
    uint32_t : 32;                                         // offset 0x2fcUL
    uint32_t : 32;                                         // offset 0x300UL
    uint32_t : 32;                                         // offset 0x304UL
    uint32_t : 32;                                         // offset 0x308UL
    uint32_t : 32;                                         // offset 0x30cUL
    uint32_t : 32;                                         // offset 0x310UL
    uint32_t : 32;                                         // offset 0x314UL
    uint32_t : 32;                                         // offset 0x318UL
    uint32_t : 32;                                         // offset 0x31cUL
    uint32_t : 32;                                         // offset 0x320UL
    uint32_t : 32;                                         // offset 0x324UL
    uint32_t : 32;                                         // offset 0x328UL
    uint32_t : 32;                                         // offset 0x32cUL
    uint32_t : 32;                                         // offset 0x330UL
    uint32_t : 32;                                         // offset 0x334UL
    uint32_t : 32;                                         // offset 0x338UL
    uint32_t : 32;                                         // offset 0x33cUL
    uint32_t : 32;                                         // offset 0x340UL
    uint32_t : 32;                                         // offset 0x344UL
    uint32_t : 32;                                         // offset 0x348UL
    uint32_t : 32;                                         // offset 0x34cUL
    uint32_t : 32;                                         // offset 0x350UL
    uint32_t : 32;                                         // offset 0x354UL
    uint32_t : 32;                                         // offset 0x358UL
    uint32_t : 32;                                         // offset 0x35cUL
    uint32_t : 32;                                         // offset 0x360UL
    uint32_t : 32;                                         // offset 0x364UL
    uint32_t : 32;                                         // offset 0x368UL
    uint32_t : 32;                                         // offset 0x36cUL
    uint32_t : 32;                                         // offset 0x370UL
    uint32_t : 32;                                         // offset 0x374UL
    uint32_t : 32;                                         // offset 0x378UL
    uint32_t : 32;                                         // offset 0x37cUL
    uint32_t : 32;                                         // offset 0x380UL
    uint32_t : 32;                                         // offset 0x384UL
    uint32_t : 32;                                         // offset 0x388UL
    uint32_t : 32;                                         // offset 0x38cUL
    uint32_t : 32;                                         // offset 0x390UL
    uint32_t : 32;                                         // offset 0x394UL
    uint32_t : 32;                                         // offset 0x398UL
    uint32_t : 32;                                         // offset 0x39cUL
    uint32_t : 32;                                         // offset 0x3a0UL
    uint32_t : 32;                                         // offset 0x3a4UL
    uint32_t : 32;                                         // offset 0x3a8UL
    uint32_t : 32;                                         // offset 0x3acUL
    uint32_t : 32;                                         // offset 0x3b0UL
    uint32_t : 32;                                         // offset 0x3b4UL
    uint32_t : 32;                                         // offset 0x3b8UL
    uint32_t : 32;                                         // offset 0x3bcUL
    uint32_t : 32;                                         // offset 0x3c0UL
    uint32_t : 32;                                         // offset 0x3c4UL
    uint32_t : 32;                                         // offset 0x3c8UL
    uint32_t : 32;                                         // offset 0x3ccUL
    uint32_t : 32;                                         // offset 0x3d0UL
    uint32_t : 32;                                         // offset 0x3d4UL
    uint32_t : 32;                                         // offset 0x3d8UL
    uint32_t : 32;                                         // offset 0x3dcUL
    uint32_t : 32;                                         // offset 0x3e0UL
    uint32_t : 32;                                         // offset 0x3e4UL
    uint32_t : 32;                                         // offset 0x3e8UL
    uint32_t : 32;                                         // offset 0x3ecUL
    uint32_t : 32;                                         // offset 0x3f0UL
    uint32_t : 32;                                         // offset 0x3f4UL
    uint32_t : 32;                                         // offset 0x3f8UL
    uint32_t : 32;                                         // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<SerialPeripheralInterface>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(SerialPeripheralInterface, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, status) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, data) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, crc_polynomial) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, receive_crc) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, transmit_crc) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, i2s_configuration) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(SerialPeripheralInterface, i2s_prescaler) == 0x20UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(SerialPeripheralInterface) == 0x400UL, "Must be this exact size");

/// @{The external volatile spiX which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern SerialPeripheralInterface volatile spi1;
extern SerialPeripheralInterface volatile spi2;
extern SerialPeripheralInterface volatile spi3;
extern SerialPeripheralInterface volatile spi4;
extern SerialPeripheralInterface volatile spi5;
extern SerialPeripheralInterface volatile spi6;
/// @}
}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_SPI1__HPP_