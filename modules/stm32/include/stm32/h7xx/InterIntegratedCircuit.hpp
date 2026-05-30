
#ifndef STM32_H7XX_INTERINTEGRATEDCIRCUIT__HPP_
#define STM32_H7XX_INTERINTEGRATEDCIRCUIT__HPP_

/// @file
/// Auto Generated Structure Definitions for InterIntegratedCircuit from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// I2C
struct InterIntegratedCircuit final {
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (CR1)
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
            /// Peripheral enable Note: When PE=0, the I2C SCL and SDA lines are released. Internal state machines and status bits are put back to
            /// their reset value. When cleared, PE must be kept low for at least 3 APB clock cycles. (PE)
            uint32_t peripheral_enable                    : 1;    // bit 0
            /// TX Interrupt enable (TXIE)
            uint32_t transmit_interrupt_enable            : 1;    // bit 1
            /// RX Interrupt enable (RXIE)
            uint32_t receive_interrupt_enable             : 1;    // bit 2
            /// Address match Interrupt enable (slave only) (ADDRIE)
            uint32_t address_match_interrupt_enable       : 1;    // bit 3
            /// Not acknowledge received Interrupt enable (NACKIE)
            uint32_t nack_interrupt_enable                : 1;    // bit 4
            /// STOP detection Interrupt enable (STOPIE)
            uint32_t stop_interrupt_enable                : 1;    // bit 5
            /// Transfer Complete interrupt enable Note: Any of these events will generate an interrupt: Transfer Complete (TC) Transfer Complete
            /// Reload (TCR) (TCIE)
            uint32_t transfer_complete_interrupt_enable   : 1;    // bit 6
            /// Error interrupts enable Note: Any of these errors generate an interrupt: Arbitration Loss (ARLO) Bus Error detection (BERR)
            /// Overrun/Underrun (OVR) Timeout detection (TIMEOUT) PEC error detection (PECERR) Alert pin event detection (ALERT) (ERRIE)
            uint32_t error_interrupt_enable               : 1;    // bit 7
            /// Digital noise filter These bits are used to configure the digital noise filter on SDA and SCL input. The digital filter will filter
            /// spikes with a length of up to DNF[3:0] * tI2CCLK ... Note: If the analog filter is also enabled, the digital filter is added to the
            /// analog filter. This filter can only be programmed when the I2C is disabled (PE = 0). (DNF)
            uint32_t digital_noise_filter                 : 4;    // bits 8:11
            /// Analog noise filter OFF Note: This bit can only be programmed when the I2C is disabled (PE = 0). (ANFOFF)
            uint32_t analog_noise_filter                  : 1;    // bit 12
            /// (reserved)
            uint32_t                                      : 1;    // bit 13
            /// DMA transmission requests enable (TXDMAEN)
            uint32_t transmit_direct_memory_access_enable : 1;    // bit 14
            /// DMA reception requests enable (RXDMAEN)
            uint32_t receive_direct_memory_access_enable  : 1;    // bit 15
            /// Slave byte control This bit is used to enable hardware byte control in slave mode. (SBC)
            uint32_t smart_card_byte_count                : 1;    // bit 16
            /// Clock stretching disable This bit is used to disable clock stretching in slave mode. It must be kept cleared in master mode. Note:
            /// This bit can only be programmed when the I2C is disabled (PE = 0). (NOSTRETCH)
            uint32_t no_stretch                           : 1;    // bit 17
            /// Wakeup from Stop mode enable Note: If the Wakeup from Stop mode feature is not supported, this bit is reserved and forced by hardware
            /// to 0. Please refer to Section25.3: I2C implementation. Note: WUPEN can be set only when DNF = 0000 (WUPEN)
            uint32_t wakeup_enable                        : 1;    // bit 18
            /// General call enable (GCEN)
            uint32_t general_call_enable                  : 1;    // bit 19
            /// SMBus Host address enable Note: If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0. Please refer
            /// to Section25.3: I2C implementation. (SMBHEN)
            uint32_t smbus_host_address_enable            : 1;    // bit 20
            /// SMBus Device Default address enable Note: If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0.
            /// Please refer to Section25.3: I2C implementation. (SMBDEN)
            uint32_t smbus_default_address_enable         : 1;    // bit 21
            /// SMBus alert enable Device mode (SMBHEN=0): Host mode (SMBHEN=1): Note: When ALERTEN=0, the SMBA pin can be used as a standard GPIO. If
            /// the SMBus feature is not supported, this bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation.
            /// (ALERTEN)
            uint32_t alert_enable                         : 1;    // bit 22
            /// PEC enable Note: If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0. Please refer to Section25.3:
            /// I2C implementation. (PECEN)
            uint32_t parity_error_check_enable            : 1;    // bit 23
            /// (reserved)
            uint32_t                                      : 8;    // bits 24:31
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
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (CR2)
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
            /// Follower address bit 0 (leader mode) In 7-bit addressing mode (ADD10 = 0): This bit is dont care In 10-bit addressing mode (ADD10 =
            /// 1): This bit should be written with bit 0 of the follower address to be sent Note: Changing these bits when the START bit is set is
            /// not allowed. (SADD0-9)
            uint32_t follower_address : 10;    // bit 0-9
            /// Transfer direction (leader mode) Note: Changing this bit when the START bit is set is not allowed. (RD_WRN)
            uint32_t read_write       : 1;    // bit 10
            /// 10-bit addressing mode (leader mode) Note: Changing this bit when the START bit is set is not allowed. (ADD10)
            uint32_t address10        : 1;    // bit 11
            /// 10-bit address header only read direction (leader receiver mode) Note: Changing this bit when the START bit is set is not allowed.
            /// (HEAD10R)
            uint32_t head10r          : 1;    // bit 12
            /// Start generation This bit is set by software, and cleared by hardware after the Start followed by the address sequence is sent, by an
            /// arbitration loss, by a timeout error detection, or when PE = 0. It can also be cleared by software by writing 1 to the ADDRCF bit in
            /// the I2C_ICR register. If the I2C is already in master mode with AUTOEND = 0, setting this bit generates a Repeated Start condition
            /// when RELOAD=0, after the end of the NBYTES transfer. Otherwise setting this bit will generate a START condition once the bus is free.
            /// Note: Writing 0 to this bit has no effect. The START bit can be set even if the bus is BUSY or I2C is in slave mode. This bit has no
            /// effect when RELOAD is set. (START)
            uint32_t start            : 1;    // bit 13
            /// Stop generation (master mode) The bit is set by software, cleared by hardware when a Stop condition is detected, or when PE = 0. In
            /// Master Mode: Note: Writing 0 to this bit has no effect. (STOP)
            uint32_t stop             : 1;    // bit 14
            /// NACK generation (slave mode) The bit is set by software, cleared by hardware when the NACK is sent, or when a STOP condition or an
            /// Address matched is received, or when PE=0. Note: Writing 0 to this bit has no effect. This bit is used in slave mode only: in master
            /// receiver mode, NACK is automatically generated after last byte preceding STOP or RESTART condition, whatever the NACK bit value. When
            /// an overrun occurs in slave receiver NOSTRETCH mode, a NACK is automatically generated whatever the NACK bit value. When hardware PEC
            /// checking is enabled (PECBYTE=1), the PEC acknowledge value does not depend on the NACK value. (NACK)
            uint32_t smart_card_nack  : 1;    // bit 15
            /// Number of bytes The number of bytes to be transmitted/received is programmed there. This field is dont care in slave mode with SBC=0.
            /// Note: Changing these bits when the START bit is set is not allowed. (NBYTES)
            uint32_t byte_count       : 8;    // bits 16:23
            /// NBYTES reload mode This bit is set and cleared by software. (RELOAD)
            uint32_t transfer_reload  : 1;    // bit 24
            /// Automatic end mode (master mode) This bit is set and cleared by software. Note: This bit has no effect in slave mode or when the
            /// RELOAD bit is set. (AUTOEND)
            uint32_t autoend          : 1;    // bit 25
            /// Packet error checking byte This bit is set by software, and cleared by hardware when the PEC is transferred, or when a STOP condition
            /// or an Address matched is received, also when PE=0. Note: Writing 0 to this bit has no effect. This bit has no effect when RELOAD is
            /// set. This bit has no effect is slave mode when SBC=0. If the SMBus feature is not supported, this bit is reserved and forced by
            /// hardware to 0. Please refer to Section25.3: I2C implementation. (PECBYTE)
            uint32_t pecbyte          : 1;    // bit 26
            /// (reserved)
            uint32_t                  : 5;    // bits 27:31
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
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (OAR1)
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
            /// Interface address 7-bit addressing mode: dont care 10-bit addressing mode: bits 9:8 of address Note: These bits can be written only
            /// when OA1EN=0. OA1[7:1]: Interface address Bits 7:1 of address Note: These bits can be written only when OA1EN=0. OA1[0]: Interface
            /// address 7-bit addressing mode: dont care 10-bit addressing mode: bit 0 of address Note: This bit can be written only when OA1EN=0.
            /// (OA1)
            uint32_t own_address1        : 10;    // bits 0:9
            /// Own Address 1 10-bit mode Note: This bit can be written only when OA1EN=0. (OA1MODE)
            uint32_t oa1mode             : 1;    // bit 10
            /// (reserved)
            uint32_t                     : 4;    // bits 11:14
            /// Own Address 1 enable (OA1EN)
            uint32_t own_address1_enable : 1;    // bit 15
            /// (reserved)
            uint32_t                     : 16;    // bits 16:31
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
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (OAR2)
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
            /// (reserved)
            uint32_t                     : 1;    // bit 0
            /// Interface address bits 7:1 of address Note: These bits can be written only when OA2EN=0. (OA2)
            uint32_t own_address2        : 7;    // bits 1:7
            /// Own Address 2 masks Note: These bits can be written only when OA2EN=0. As soon as OA2MSK is not equal to 0, the reserved I2C addresses
            /// (0b0000xxx and 0b1111xxx) are not acknowledged even if the comparison matches. (OA2MSK)
            uint32_t own_address2_mask   : 3;    // bits 8:10
            /// (reserved)
            uint32_t                     : 4;    // bits 11:14
            /// Own Address 2 enable (OA2EN)
            uint32_t own_address2_enable : 1;    // bit 15
            /// (reserved)
            uint32_t                     : 16;    // bits 16:31
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
    /// Access: No wait states (TIMINGR)
    struct Timing final {
        /// Default Constructor
        Timing()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Timing(Timing volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Timing(Timing const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Timing(Timing&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Timing(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Timing(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Timing() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SCL low period (master mode) This field is used to generate the SCL low period in master mode. tSCLL = (SCLL+1) x tPRESC Note: SCLL is
            /// also used to generate tBUF and tSU:STA timings. (SCLL)
            uint32_t scl_low_period  : 8;    // bits 0:7
            /// SCL high period (master mode) This field is used to generate the SCL high period in master mode. tSCLH = (SCLH+1) x tPRESC Note: SCLH
            /// is also used to generate tSU:STO and tHD:STA timing. (SCLH)
            uint32_t scl_high_period : 8;    // bits 8:15
            /// Data hold time This field is used to generate the delay tSDADEL between SCL falling edge and SDA edge. In master mode and in slave
            /// mode with NOSTRETCH = 0, the SCL line is stretched low during tSDADEL. tSDADEL= SDADEL x tPRESC Note: SDADEL is used to generate
            /// tHD:DAT timing. (SDADEL)
            uint32_t sda_fall_time   : 4;    // bits 16:19
            /// Data setup time This field is used to generate a delay tSCLDEL between SDA edge and SCL rising edge. In master mode and in slave mode
            /// with NOSTRETCH = 0, the SCL line is stretched low during tSCLDEL. tSCLDEL = (SCLDEL+1) x tPRESC Note: tSCLDEL is used to generate
            /// tSU:DAT timing. (SCLDEL)
            uint32_t scl_rise_time   : 4;    // bits 20:23
            /// (reserved)
            uint32_t                 : 4;    // bits 24:27
            /// Timing prescaler This field is used to prescale I2CCLK in order to generate the clock period tPRESC used for data setup and hold
            /// counters (refer to I2C timings on page9) and for SCL high and low level counters (refer to I2C master initialization on page24).
            /// tPRESC = (PRESC+1) x tI2CCLK (PRESC)
            uint32_t prescaler       : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Timing& operator=(Timing&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Timing volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Timing const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Timing>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Timing) == 4UL, "Must be this exact size");
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (TIMEOUTR)
    struct Timeout final {
        /// Default Constructor
        Timeout()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Timeout(Timeout volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Timeout(Timeout const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Timeout(Timeout&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Timeout(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Timeout(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Timeout() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Bus Timeout A This field is used to configure: The SCL low timeout condition tTIMEOUT when TIDLE=0 tTIMEOUT= (TIMEOUTA+1) x 2048 x
            /// tI2CCLK The bus idle condition (both SCL and SDA high) when TIDLE=1 tIDLE= (TIMEOUTA+1) x 4 x tI2CCLK Note: These bits can be written
            /// only when TIMOUTEN=0. (TIMEOUTA)
            uint32_t timeout_a              : 12;    // bits 0:11
            /// Idle clock timeout detection Note: This bit can be written only when TIMOUTEN=0. (TIDLE)
            uint32_t idle_timeout           : 1;    // bit 12
            /// (reserved)
            uint32_t                        : 2;    // bits 13:14
            /// Clock timeout enable (TIMOUTEN)
            uint32_t timeout_enable         : 1;    // bit 15
            /// Bus timeout B This field is used to configure the cumulative clock extension timeout: In master mode, the master cumulative clock low
            /// extend time (tLOW:MEXT) is detected In slave mode, the slave cumulative clock low extend time (tLOW:SEXT) is detected tLOW:EXT=
            /// (TIMEOUTB+1) x 2048 x tI2CCLK Note: These bits can be written only when TEXTEN=0. (TIMEOUTB)
            uint32_t timeout_b              : 12;    // bits 16:27
            /// (reserved)
            uint32_t                        : 3;    // bits 28:30
            /// Extended clock timeout enable (TEXTEN)
            uint32_t extended_clock_timeout : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Timeout& operator=(Timeout&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Timeout volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Timeout const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Timeout>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Timeout) == 4UL, "Must be this exact size");
    /// Access: No wait states (ISR)
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
            /// Transmit data register empty (transmitters) This bit is set by hardware when the I2C_TXDR register is empty. It is cleared when the
            /// next data to be sent is written in the I2C_TXDR register. This bit can be written to 1 by software in order to flush the transmit data
            /// register I2C_TXDR. Note: This bit is set by hardware when PE=0. (TXE)
            uint32_t transmit_buffer_empty     : 1;    // bit 0
            /// Transmit interrupt status (transmitters) This bit is set by hardware when the I2C_TXDR register is empty and the data to be
            /// transmitted must be written in the I2C_TXDR register. It is cleared when the next data to be sent is written in the I2C_TXDR register.
            /// This bit can be written to 1 by software when NOSTRETCH=1 only, in order to generate a TXIS event (interrupt if TXIE=1 or DMA request
            /// if TXDMAEN=1). Note: This bit is cleared by hardware when PE=0. (TXIS)
            uint32_t transmit_interrupt_status : 1;    // bit 1
            /// Receive data register not empty (receivers) This bit is set by hardware when the received data is copied into the I2C_RXDR register,
            /// and is ready to be read. It is cleared when I2C_RXDR is read. Note: This bit is cleared by hardware when PE=0. (RXNE)
            uint32_t receive_buffer_not_empty  : 1;    // bit 2
            /// Address matched (slave mode) This bit is set by hardware as soon as the received slave address matched with one of the enabled slave
            /// addresses. It is cleared by software by setting ADDRCF bit. Note: This bit is cleared by hardware when PE=0. (ADDR)
            uint32_t address                   : 1;    // bit 3
            /// Not Acknowledge received flag This flag is set by hardware when a NACK is received after a byte transmission. It is cleared by
            /// software by setting the NACKCF bit. Note: This bit is cleared by hardware when PE=0. (NACKF)
            uint32_t nack_flag                 : 1;    // bit 4
            /// Stop detection flag This flag is set by hardware when a Stop condition is detected on the bus and the peripheral is involved in this
            /// transfer: either as a master, provided that the STOP condition is generated by the peripheral. or as a slave, provided that the
            /// peripheral has been addressed previously during this transfer. It is cleared by software by setting the STOPCF bit. Note: This bit is
            /// cleared by hardware when PE=0. (STOPF)
            uint32_t stop_detection            : 1;    // bit 5
            /// Transfer Complete (master mode) This flag is set by hardware when RELOAD=0, AUTOEND=0 and NBYTES data have been transferred. It is
            /// cleared by software when START bit or STOP bit is set. Note: This bit is cleared by hardware when PE=0. (TC)
            uint32_t transmit_complete         : 1;    // bit 6
            /// Transfer Complete Reload This flag is set by hardware when RELOAD=1 and NBYTES data have been transferred. It is cleared by software
            /// when NBYTES is written to a non-zero value. Note: This bit is cleared by hardware when PE=0. This flag is only for master mode, or for
            /// slave mode when the SBC bit is set. (TCR)
            uint32_t transfer_control          : 1;    // bit 7
            /// Bus error This flag is set by hardware when a misplaced Start or Stop condition is detected whereas the peripheral is involved in the
            /// transfer. The flag is not set during the address phase in slave mode. It is cleared by software by setting BERRCF bit. Note: This bit
            /// is cleared by hardware when PE=0. (BERR)
            uint32_t bus_error                 : 1;    // bit 8
            /// Arbitration lost This flag is set by hardware in case of arbitration loss. It is cleared by software by setting the ARLOCF bit. Note:
            /// This bit is cleared by hardware when PE=0. (ARLO)
            uint32_t arbitration_lost          : 1;    // bit 9
            /// Overrun/Underrun (slave mode) This flag is set by hardware in slave mode with NOSTRETCH=1, when an overrun/underrun error occurs. It
            /// is cleared by software by setting the OVRCF bit. Note: This bit is cleared by hardware when PE=0. (OVR)
            uint32_t overrun                   : 1;    // bit 10
            /// PEC Error in reception This flag is set by hardware when the received PEC does not match with the PEC register content. A NACK is
            /// automatically sent after the wrong PEC reception. It is cleared by software by setting the PECCF bit. Note: This bit is cleared by
            /// hardware when PE=0. If the SMBus feature is not supported, this bit is reserved and forced by hardware to 0. Please refer to
            /// Section25.3: I2C implementation. (PECERR)
            uint32_t packet_error_code_error   : 1;    // bit 11
            /// Timeout or tLOW detection flag This flag is set by hardware when a timeout or extended clock timeout occurred. It is cleared by
            /// software by setting the TIMEOUTCF bit. Note: This bit is cleared by hardware when PE=0. If the SMBus feature is not supported, this
            /// bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation. (TIMEOUT)
            uint32_t timeout                   : 1;    // bit 12
            /// SMBus alert This flag is set by hardware when SMBHEN=1 (SMBus host configuration), ALERTEN=1 and a SMBALERT event (falling edge) is
            /// detected on SMBA pin. It is cleared by software by setting the ALERTCF bit. Note: This bit is cleared by hardware when PE=0. If the
            /// SMBus feature is not supported, this bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation.
            /// (ALERT)
            uint32_t alert                     : 1;    // bit 13
            /// (reserved)
            uint32_t                           : 1;    // bit 14
            /// Bus busy This flag indicates that a communication is in progress on the bus. It is set by hardware when a START condition is detected.
            /// It is cleared by hardware when a Stop condition is detected, or when PE=0. (BUSY)
            uint32_t busy                      : 1;    // bit 15
            /// Transfer direction (Slave mode) This flag is updated when an address match event occurs (ADDR=1). (DIR)
            uint32_t data_transfer_direction   : 1;    // bit 16
            /// Address match code (Slave mode) These bits are updated with the received address when an address match event occurs (ADDR = 1). In the
            /// case of a 10-bit address, ADDCODE provides the 10-bit header followed by the 2 MSBs of the address. (ADDCODE)
            uint32_t addcode                   : 7;    // bits 17:23
            /// (reserved)
            uint32_t                           : 8;    // bits 24:31
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
    /// Access: No wait states (ICR)
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
            /// (reserved)
            uint32_t                        : 3;    // bits 0:2
            /// Address matched flag clear Writing 1 to this bit clears the ADDR flag in the I2C_ISR register. Writing 1 to this bit also clears the
            /// START bit in the I2C_CR2 register. (ADDRCF)
            uint32_t address_match_clear    : 1;    // bit 3
            /// Not Acknowledge flag clear Writing 1 to this bit clears the ACKF flag in I2C_ISR register. (NACKCF)
            uint32_t nack_clear             : 1;    // bit 4
            /// Stop detection flag clear Writing 1 to this bit clears the STOPF flag in the I2C_ISR register. (STOPCF)
            uint32_t stop_condition_clear   : 1;    // bit 5
            /// (reserved)
            uint32_t                        : 2;    // bits 6:7
            /// Bus error flag clear Writing 1 to this bit clears the BERRF flag in the I2C_ISR register. (BERRCF)
            uint32_t bus_error_clear        : 1;    // bit 8
            /// Arbitration Lost flag clear Writing 1 to this bit clears the ARLO flag in the I2C_ISR register. (ARLOCF)
            uint32_t arbitration_lost_clear : 1;    // bit 9
            /// Overrun/Underrun flag clear Writing 1 to this bit clears the OVR flag in the I2C_ISR register. (OVRCF)
            uint32_t overrun_clear          : 1;    // bit 10
            /// PEC Error flag clear Writing 1 to this bit clears the PECERR flag in the I2C_ISR register. Note: If the SMBus feature is not
            /// supported, this bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation. (PECCF)
            uint32_t parity_error_clear     : 1;    // bit 11
            /// Timeout detection flag clear Writing 1 to this bit clears the TIMEOUT flag in the I2C_ISR register. Note: If the SMBus feature is not
            /// supported, this bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation. (TIMOUTCF)
            uint32_t timeout_flag           : 1;    // bit 12
            /// Alert flag clear Writing 1 to this bit clears the ALERT flag in the I2C_ISR register. Note: If the SMBus feature is not supported,
            /// this bit is reserved and forced by hardware to 0. Please refer to Section25.3: I2C implementation. (ALERTCF)
            uint32_t alert_flag_clear       : 1;    // bit 13
            /// (reserved)
            uint32_t                        : 18;    // bits 14:31
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
    /// Access: No wait states (PECR)
    struct PacketErrorCheck final {
        /// Default Constructor
        PacketErrorCheck()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PacketErrorCheck(PacketErrorCheck volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PacketErrorCheck(PacketErrorCheck const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PacketErrorCheck(PacketErrorCheck&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PacketErrorCheck(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PacketErrorCheck(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PacketErrorCheck() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Packet error checking register This field contains the internal PEC when PECEN=1. The PEC is cleared by hardware when PE=0. (PEC)
            uint32_t packet_error_checking : 8;    // bits 0:7
            /// (reserved)
            uint32_t                       : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PacketErrorCheck& operator=(PacketErrorCheck&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PacketErrorCheck volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PacketErrorCheck const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PacketErrorCheck>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PacketErrorCheck) == 4UL, "Must be this exact size");
    /// Access: No wait states (RXDR)
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
            /// 8-bit receive data Data byte received from the I2C bus. (RXDATA)
            uint32_t receive_data_buffer : 8;    // bits 0:7
            /// (reserved)
            uint32_t                     : 24;    // bits 8:31
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
    /// Access: No wait states (TXDR)
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
            /// 8-bit transmit data Data byte to be transmitted to the I2C bus. Note: These bits can be written only when TXE=1. (TXDATA)
            uint32_t transmit_data_buffer : 8;    // bits 0:7
            /// (reserved)
            uint32_t                      : 24;    // bits 8:31
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

    //+=MEMORY======================================+
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (CR1)
    Control1 control1;    // offset 0x0UL
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (CR2)
    Control2 control2;    // offset 0x4UL
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (OAR1)
    OurAddress1 our_address1;    // offset 0x8UL
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (OAR2)
    OurAddress2 our_address2;    // offset 0xcUL
    /// Access: No wait states (TIMINGR)
    Timing timing;    // offset 0x10UL
    /// Access: No wait states, except if a write access occurs while a write access to this register is ongoing. In this case, wait states are
    /// inserted in the second write access until the previous one is completed. The latency of the second write access can be up to 2 x PCLK1 + 6 x
    /// I2CCLK. (TIMEOUTR)
    Timeout timeout;    // offset 0x14UL
    /// Access: No wait states (ISR)
    InterruptStatus interrupt_status;    // offset 0x18UL
    /// Access: No wait states (ICR)
    InterruptClear interrupt_clear;    // offset 0x1cUL
    /// Access: No wait states (PECR)
    PacketErrorCheck packet_error_check;    // offset 0x20UL
    /// Access: No wait states (RXDR)
    ReceiveData receive_data;    // offset 0x24UL
    /// Access: No wait states (TXDR)
    TransmitData transmit_data;    // offset 0x28UL
    uint32_t : 32;                 // offset 0x2cUL
    uint32_t : 32;                 // offset 0x30UL
    uint32_t : 32;                 // offset 0x34UL
    uint32_t : 32;                 // offset 0x38UL
    uint32_t : 32;                 // offset 0x3cUL
    uint32_t : 32;                 // offset 0x40UL
    uint32_t : 32;                 // offset 0x44UL
    uint32_t : 32;                 // offset 0x48UL
    uint32_t : 32;                 // offset 0x4cUL
    uint32_t : 32;                 // offset 0x50UL
    uint32_t : 32;                 // offset 0x54UL
    uint32_t : 32;                 // offset 0x58UL
    uint32_t : 32;                 // offset 0x5cUL
    uint32_t : 32;                 // offset 0x60UL
    uint32_t : 32;                 // offset 0x64UL
    uint32_t : 32;                 // offset 0x68UL
    uint32_t : 32;                 // offset 0x6cUL
    uint32_t : 32;                 // offset 0x70UL
    uint32_t : 32;                 // offset 0x74UL
    uint32_t : 32;                 // offset 0x78UL
    uint32_t : 32;                 // offset 0x7cUL
    uint32_t : 32;                 // offset 0x80UL
    uint32_t : 32;                 // offset 0x84UL
    uint32_t : 32;                 // offset 0x88UL
    uint32_t : 32;                 // offset 0x8cUL
    uint32_t : 32;                 // offset 0x90UL
    uint32_t : 32;                 // offset 0x94UL
    uint32_t : 32;                 // offset 0x98UL
    uint32_t : 32;                 // offset 0x9cUL
    uint32_t : 32;                 // offset 0xa0UL
    uint32_t : 32;                 // offset 0xa4UL
    uint32_t : 32;                 // offset 0xa8UL
    uint32_t : 32;                 // offset 0xacUL
    uint32_t : 32;                 // offset 0xb0UL
    uint32_t : 32;                 // offset 0xb4UL
    uint32_t : 32;                 // offset 0xb8UL
    uint32_t : 32;                 // offset 0xbcUL
    uint32_t : 32;                 // offset 0xc0UL
    uint32_t : 32;                 // offset 0xc4UL
    uint32_t : 32;                 // offset 0xc8UL
    uint32_t : 32;                 // offset 0xccUL
    uint32_t : 32;                 // offset 0xd0UL
    uint32_t : 32;                 // offset 0xd4UL
    uint32_t : 32;                 // offset 0xd8UL
    uint32_t : 32;                 // offset 0xdcUL
    uint32_t : 32;                 // offset 0xe0UL
    uint32_t : 32;                 // offset 0xe4UL
    uint32_t : 32;                 // offset 0xe8UL
    uint32_t : 32;                 // offset 0xecUL
    uint32_t : 32;                 // offset 0xf0UL
    uint32_t : 32;                 // offset 0xf4UL
    uint32_t : 32;                 // offset 0xf8UL
    uint32_t : 32;                 // offset 0xfcUL
    uint32_t : 32;                 // offset 0x100UL
    uint32_t : 32;                 // offset 0x104UL
    uint32_t : 32;                 // offset 0x108UL
    uint32_t : 32;                 // offset 0x10cUL
    uint32_t : 32;                 // offset 0x110UL
    uint32_t : 32;                 // offset 0x114UL
    uint32_t : 32;                 // offset 0x118UL
    uint32_t : 32;                 // offset 0x11cUL
    uint32_t : 32;                 // offset 0x120UL
    uint32_t : 32;                 // offset 0x124UL
    uint32_t : 32;                 // offset 0x128UL
    uint32_t : 32;                 // offset 0x12cUL
    uint32_t : 32;                 // offset 0x130UL
    uint32_t : 32;                 // offset 0x134UL
    uint32_t : 32;                 // offset 0x138UL
    uint32_t : 32;                 // offset 0x13cUL
    uint32_t : 32;                 // offset 0x140UL
    uint32_t : 32;                 // offset 0x144UL
    uint32_t : 32;                 // offset 0x148UL
    uint32_t : 32;                 // offset 0x14cUL
    uint32_t : 32;                 // offset 0x150UL
    uint32_t : 32;                 // offset 0x154UL
    uint32_t : 32;                 // offset 0x158UL
    uint32_t : 32;                 // offset 0x15cUL
    uint32_t : 32;                 // offset 0x160UL
    uint32_t : 32;                 // offset 0x164UL
    uint32_t : 32;                 // offset 0x168UL
    uint32_t : 32;                 // offset 0x16cUL
    uint32_t : 32;                 // offset 0x170UL
    uint32_t : 32;                 // offset 0x174UL
    uint32_t : 32;                 // offset 0x178UL
    uint32_t : 32;                 // offset 0x17cUL
    uint32_t : 32;                 // offset 0x180UL
    uint32_t : 32;                 // offset 0x184UL
    uint32_t : 32;                 // offset 0x188UL
    uint32_t : 32;                 // offset 0x18cUL
    uint32_t : 32;                 // offset 0x190UL
    uint32_t : 32;                 // offset 0x194UL
    uint32_t : 32;                 // offset 0x198UL
    uint32_t : 32;                 // offset 0x19cUL
    uint32_t : 32;                 // offset 0x1a0UL
    uint32_t : 32;                 // offset 0x1a4UL
    uint32_t : 32;                 // offset 0x1a8UL
    uint32_t : 32;                 // offset 0x1acUL
    uint32_t : 32;                 // offset 0x1b0UL
    uint32_t : 32;                 // offset 0x1b4UL
    uint32_t : 32;                 // offset 0x1b8UL
    uint32_t : 32;                 // offset 0x1bcUL
    uint32_t : 32;                 // offset 0x1c0UL
    uint32_t : 32;                 // offset 0x1c4UL
    uint32_t : 32;                 // offset 0x1c8UL
    uint32_t : 32;                 // offset 0x1ccUL
    uint32_t : 32;                 // offset 0x1d0UL
    uint32_t : 32;                 // offset 0x1d4UL
    uint32_t : 32;                 // offset 0x1d8UL
    uint32_t : 32;                 // offset 0x1dcUL
    uint32_t : 32;                 // offset 0x1e0UL
    uint32_t : 32;                 // offset 0x1e4UL
    uint32_t : 32;                 // offset 0x1e8UL
    uint32_t : 32;                 // offset 0x1ecUL
    uint32_t : 32;                 // offset 0x1f0UL
    uint32_t : 32;                 // offset 0x1f4UL
    uint32_t : 32;                 // offset 0x1f8UL
    uint32_t : 32;                 // offset 0x1fcUL
    uint32_t : 32;                 // offset 0x200UL
    uint32_t : 32;                 // offset 0x204UL
    uint32_t : 32;                 // offset 0x208UL
    uint32_t : 32;                 // offset 0x20cUL
    uint32_t : 32;                 // offset 0x210UL
    uint32_t : 32;                 // offset 0x214UL
    uint32_t : 32;                 // offset 0x218UL
    uint32_t : 32;                 // offset 0x21cUL
    uint32_t : 32;                 // offset 0x220UL
    uint32_t : 32;                 // offset 0x224UL
    uint32_t : 32;                 // offset 0x228UL
    uint32_t : 32;                 // offset 0x22cUL
    uint32_t : 32;                 // offset 0x230UL
    uint32_t : 32;                 // offset 0x234UL
    uint32_t : 32;                 // offset 0x238UL
    uint32_t : 32;                 // offset 0x23cUL
    uint32_t : 32;                 // offset 0x240UL
    uint32_t : 32;                 // offset 0x244UL
    uint32_t : 32;                 // offset 0x248UL
    uint32_t : 32;                 // offset 0x24cUL
    uint32_t : 32;                 // offset 0x250UL
    uint32_t : 32;                 // offset 0x254UL
    uint32_t : 32;                 // offset 0x258UL
    uint32_t : 32;                 // offset 0x25cUL
    uint32_t : 32;                 // offset 0x260UL
    uint32_t : 32;                 // offset 0x264UL
    uint32_t : 32;                 // offset 0x268UL
    uint32_t : 32;                 // offset 0x26cUL
    uint32_t : 32;                 // offset 0x270UL
    uint32_t : 32;                 // offset 0x274UL
    uint32_t : 32;                 // offset 0x278UL
    uint32_t : 32;                 // offset 0x27cUL
    uint32_t : 32;                 // offset 0x280UL
    uint32_t : 32;                 // offset 0x284UL
    uint32_t : 32;                 // offset 0x288UL
    uint32_t : 32;                 // offset 0x28cUL
    uint32_t : 32;                 // offset 0x290UL
    uint32_t : 32;                 // offset 0x294UL
    uint32_t : 32;                 // offset 0x298UL
    uint32_t : 32;                 // offset 0x29cUL
    uint32_t : 32;                 // offset 0x2a0UL
    uint32_t : 32;                 // offset 0x2a4UL
    uint32_t : 32;                 // offset 0x2a8UL
    uint32_t : 32;                 // offset 0x2acUL
    uint32_t : 32;                 // offset 0x2b0UL
    uint32_t : 32;                 // offset 0x2b4UL
    uint32_t : 32;                 // offset 0x2b8UL
    uint32_t : 32;                 // offset 0x2bcUL
    uint32_t : 32;                 // offset 0x2c0UL
    uint32_t : 32;                 // offset 0x2c4UL
    uint32_t : 32;                 // offset 0x2c8UL
    uint32_t : 32;                 // offset 0x2ccUL
    uint32_t : 32;                 // offset 0x2d0UL
    uint32_t : 32;                 // offset 0x2d4UL
    uint32_t : 32;                 // offset 0x2d8UL
    uint32_t : 32;                 // offset 0x2dcUL
    uint32_t : 32;                 // offset 0x2e0UL
    uint32_t : 32;                 // offset 0x2e4UL
    uint32_t : 32;                 // offset 0x2e8UL
    uint32_t : 32;                 // offset 0x2ecUL
    uint32_t : 32;                 // offset 0x2f0UL
    uint32_t : 32;                 // offset 0x2f4UL
    uint32_t : 32;                 // offset 0x2f8UL
    uint32_t : 32;                 // offset 0x2fcUL
    uint32_t : 32;                 // offset 0x300UL
    uint32_t : 32;                 // offset 0x304UL
    uint32_t : 32;                 // offset 0x308UL
    uint32_t : 32;                 // offset 0x30cUL
    uint32_t : 32;                 // offset 0x310UL
    uint32_t : 32;                 // offset 0x314UL
    uint32_t : 32;                 // offset 0x318UL
    uint32_t : 32;                 // offset 0x31cUL
    uint32_t : 32;                 // offset 0x320UL
    uint32_t : 32;                 // offset 0x324UL
    uint32_t : 32;                 // offset 0x328UL
    uint32_t : 32;                 // offset 0x32cUL
    uint32_t : 32;                 // offset 0x330UL
    uint32_t : 32;                 // offset 0x334UL
    uint32_t : 32;                 // offset 0x338UL
    uint32_t : 32;                 // offset 0x33cUL
    uint32_t : 32;                 // offset 0x340UL
    uint32_t : 32;                 // offset 0x344UL
    uint32_t : 32;                 // offset 0x348UL
    uint32_t : 32;                 // offset 0x34cUL
    uint32_t : 32;                 // offset 0x350UL
    uint32_t : 32;                 // offset 0x354UL
    uint32_t : 32;                 // offset 0x358UL
    uint32_t : 32;                 // offset 0x35cUL
    uint32_t : 32;                 // offset 0x360UL
    uint32_t : 32;                 // offset 0x364UL
    uint32_t : 32;                 // offset 0x368UL
    uint32_t : 32;                 // offset 0x36cUL
    uint32_t : 32;                 // offset 0x370UL
    uint32_t : 32;                 // offset 0x374UL
    uint32_t : 32;                 // offset 0x378UL
    uint32_t : 32;                 // offset 0x37cUL
    uint32_t : 32;                 // offset 0x380UL
    uint32_t : 32;                 // offset 0x384UL
    uint32_t : 32;                 // offset 0x388UL
    uint32_t : 32;                 // offset 0x38cUL
    uint32_t : 32;                 // offset 0x390UL
    uint32_t : 32;                 // offset 0x394UL
    uint32_t : 32;                 // offset 0x398UL
    uint32_t : 32;                 // offset 0x39cUL
    uint32_t : 32;                 // offset 0x3a0UL
    uint32_t : 32;                 // offset 0x3a4UL
    uint32_t : 32;                 // offset 0x3a8UL
    uint32_t : 32;                 // offset 0x3acUL
    uint32_t : 32;                 // offset 0x3b0UL
    uint32_t : 32;                 // offset 0x3b4UL
    uint32_t : 32;                 // offset 0x3b8UL
    uint32_t : 32;                 // offset 0x3bcUL
    uint32_t : 32;                 // offset 0x3c0UL
    uint32_t : 32;                 // offset 0x3c4UL
    uint32_t : 32;                 // offset 0x3c8UL
    uint32_t : 32;                 // offset 0x3ccUL
    uint32_t : 32;                 // offset 0x3d0UL
    uint32_t : 32;                 // offset 0x3d4UL
    uint32_t : 32;                 // offset 0x3d8UL
    uint32_t : 32;                 // offset 0x3dcUL
    uint32_t : 32;                 // offset 0x3e0UL
    uint32_t : 32;                 // offset 0x3e4UL
    uint32_t : 32;                 // offset 0x3e8UL
    uint32_t : 32;                 // offset 0x3ecUL
    uint32_t : 32;                 // offset 0x3f0UL
    uint32_t : 32;                 // offset 0x3f4UL
    uint32_t : 32;                 // offset 0x3f8UL
    uint32_t : 32;                 // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<InterIntegratedCircuit>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(InterIntegratedCircuit, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, our_address1) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, our_address2) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, timing) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, timeout) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, interrupt_status) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, interrupt_clear) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, packet_error_check) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, receive_data) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(InterIntegratedCircuit, transmit_data) == 0x28UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(InterIntegratedCircuit) == 0x400UL, "Must be this exact size");

}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_INTERINTEGRATEDCIRCUIT__HPP_
