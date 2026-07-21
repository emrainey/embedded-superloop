
#ifndef STM32_H7XX_ETHERNETMEDIATRANSACTIONLAYER__HPP_
#define STM32_H7XX_ETHERNETMEDIATRANSACTIONLAYER__HPP_

/// @file
/// Auto Generated Structure Definitions for EthernetMediaTransactionLayer from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Ethernet: MTL mode register (MTL) (Ethernet_MTL)
struct EthernetMediaTransactionLayer final {
    /// Operating mode Register (MTLOMR)
    struct OperatingMode final {
        /// Default Constructor
        OperatingMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OperatingMode(OperatingMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OperatingMode(OperatingMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OperatingMode(OperatingMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OperatingMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OperatingMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OperatingMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                       : 1;    // bit 0
            /// DTXSTS (DTXSTS)
            uint32_t debug_transmit_status : 1;    // bit 1
            /// (reserved)
            uint32_t                       : 6;    // bits 2:7
            /// CNTPRST (CNTPRST)
            uint32_t counter_preset        : 1;    // bit 8
            /// CNTCLR (CNTCLR)
            uint32_t counter_clear         : 1;    // bit 9
            /// (reserved)
            uint32_t                       : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OperatingMode& operator=(OperatingMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OperatingMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OperatingMode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OperatingMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OperatingMode) == 4UL, "Must be this exact size");
    /// Interrupt status Register (MTLISR)
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
            /// Queue interrupt status (Q0IS)
            uint32_t queue_0_interrupt_status : 1;    // bit 0
            /// (reserved)
            uint32_t                          : 31;    // bits 1:31
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
    /// Tx queue operating mode Register (MTLTxQOMR)
    struct TransmitQueueOperatingMode final {
        /// Default Constructor
        TransmitQueueOperatingMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitQueueOperatingMode(TransmitQueueOperatingMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitQueueOperatingMode(TransmitQueueOperatingMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitQueueOperatingMode(TransmitQueueOperatingMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitQueueOperatingMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitQueueOperatingMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitQueueOperatingMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Flush Transmit Queue (FTQ)
            uint32_t flush_transmit_queue       : 1;    // bit 0
            /// Transmit Store and Forward (TSF)
            uint32_t transmit_store_and_forward : 1;    // bit 1
            /// Transmit Queue Enable (TXQEN)
            uint32_t transmit_queue_enable      : 2;    // bits 2:3
            /// Transmit Threshold Control (TTC)
            uint32_t transmit_threshold_control : 3;    // bits 4:6
            /// (reserved)
            uint32_t                            : 9;    // bits 7:15
            /// Transmit Queue Size (TQS)
            uint32_t transmit_queue_size        : 3;    // bits 16:18
            /// (reserved)
            uint32_t                            : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitQueueOperatingMode& operator=(TransmitQueueOperatingMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitQueueOperatingMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitQueueOperatingMode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitQueueOperatingMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitQueueOperatingMode) == 4UL, "Must be this exact size");
    /// Tx queue underflow register (MTLTxQUR)
    struct TransmitQueueUnderflow final {
        /// Default Constructor
        TransmitQueueUnderflow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitQueueUnderflow(TransmitQueueUnderflow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitQueueUnderflow(TransmitQueueUnderflow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitQueueUnderflow(TransmitQueueUnderflow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitQueueUnderflow(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitQueueUnderflow(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitQueueUnderflow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Underflow Packet Counter (UFFRMCNT)
            uint32_t underflow_frame_count      : 11;    // bits 0:10
            /// UFCNTOVF (UFCNTOVF)
            uint32_t underflow_counter_overflow : 1;    // bit 11
            /// (reserved)
            uint32_t                            : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitQueueUnderflow& operator=(TransmitQueueUnderflow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitQueueUnderflow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitQueueUnderflow const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitQueueUnderflow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitQueueUnderflow) == 4UL, "Must be this exact size");
    /// Tx queue debug Register (MTLTxQDR)
    struct TransmitQueueDebug final {
        /// Default Constructor
        TransmitQueueDebug()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitQueueDebug(TransmitQueueDebug volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitQueueDebug(TransmitQueueDebug const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitQueueDebug(TransmitQueueDebug&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitQueueDebug(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitQueueDebug(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitQueueDebug() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXQPAUSED (TXQPAUSED)
            uint32_t transmit_queue_paused             : 1;    // bit 0
            /// TRCSTS (TRCSTS)
            uint32_t transmit_read_controller_status   : 2;    // bits 1:2
            /// TWCSTS (TWCSTS)
            uint32_t transmit_write_controller_status  : 1;    // bit 3
            /// TXQSTS (TXQSTS)
            uint32_t transmit_queue_status             : 1;    // bit 4
            /// TXSTSFSTS (TXSTSFSTS)
            uint32_t transmit_store_and_forward_status : 1;    // bit 5
            /// (reserved)
            uint32_t                                   : 10;    // bits 6:15
            /// PTXQ (PTXQ)
            uint32_t packets_in_transmit_queue         : 3;    // bits 16:18
            /// (reserved)
            uint32_t                                   : 1;    // bit 19
            /// STXSTSF (STXSTSF)
            uint32_t store_and_forward_transmit_status : 3;    // bits 20:22
            /// (reserved)
            uint32_t                                   : 9;    // bits 23:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitQueueDebug& operator=(TransmitQueueDebug&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitQueueDebug volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitQueueDebug const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitQueueDebug>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitQueueDebug) == 4UL, "Must be this exact size");
    /// Queue interrupt control status Register (MTLQICSR)
    struct QueueInterruptControlStatus final {
        /// Default Constructor
        QueueInterruptControlStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        QueueInterruptControlStatus(QueueInterruptControlStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        QueueInterruptControlStatus(QueueInterruptControlStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        QueueInterruptControlStatus(QueueInterruptControlStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit QueueInterruptControlStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit QueueInterruptControlStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~QueueInterruptControlStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXUNFIS (TXUNFIS)
            uint32_t transmit_underflow_interrupt_status : 1;    // bit 0
            /// (reserved)
            uint32_t                                     : 7;    // bits 1:7
            /// TXUIE (TXUIE)
            uint32_t transmit_underflow_interrupt_enable : 1;    // bit 8
            /// (reserved)
            uint32_t                                     : 7;    // bits 9:15
            /// RXOVFIS (RXOVFIS)
            uint32_t receive_overflow_interrupt_status   : 1;    // bit 16
            /// (reserved)
            uint32_t                                     : 7;    // bits 17:23
            /// RXOIE (RXOIE)
            uint32_t receive_overflow_interrupt_enable   : 1;    // bit 24
            /// (reserved)
            uint32_t                                     : 7;    // bits 25:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        QueueInterruptControlStatus& operator=(QueueInterruptControlStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(QueueInterruptControlStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(QueueInterruptControlStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<QueueInterruptControlStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(QueueInterruptControlStatus) == 4UL, "Must be this exact size");
    /// Rx queue operating mode register (MTLRxQOMR)
    struct ReceiveQueueOperatingMode final {
        /// Default Constructor
        ReceiveQueueOperatingMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveQueueOperatingMode(ReceiveQueueOperatingMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveQueueOperatingMode(ReceiveQueueOperatingMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveQueueOperatingMode(ReceiveQueueOperatingMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveQueueOperatingMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveQueueOperatingMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveQueueOperatingMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RTC (RTC)
            uint32_t real_time_clock                          : 2;    // bits 0:1
            /// (reserved)
            uint32_t                                          : 1;    // bit 2
            /// FUP (FUP)
            uint32_t forward_undersized_good_packets          : 1;    // bit 3
            /// FEP (FEP)
            uint32_t forward_error_packets                    : 1;    // bit 4
            /// RSF (RSF)
            uint32_t receive_store_and_forward                : 1;    // bit 5
            /// DIS_TCP_EF (DIS_TCP_EF)
            uint32_t disable_dropping_tcpip_on_checksum_error : 1;    // bit 6
            /// EHFC (EHFC)
            uint32_t enable_hardware_flow_control             : 1;    // bit 7
            /// RFA (RFA)
            uint32_t receive_flow_control_activate            : 3;    // bits 8:10
            /// (reserved)
            uint32_t                                          : 3;    // bits 11:13
            /// RFD (RFD)
            uint32_t receive_flow_control_deactivate          : 3;    // bits 14:16
            /// (reserved)
            uint32_t                                          : 3;    // bits 17:19
            /// RQS (RQS)
            uint32_t receive_queue_size                       : 3;    // bits 20:22
            /// (reserved)
            uint32_t                                          : 9;    // bits 23:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveQueueOperatingMode& operator=(ReceiveQueueOperatingMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueOperatingMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueOperatingMode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveQueueOperatingMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveQueueOperatingMode) == 4UL, "Must be this exact size");
    /// Rx queue missed packet and overflow counter register (MTLRxQMPOCR)
    struct ReceiveQueueMissedPacketAndOverflowCounter final {
        /// Default Constructor
        ReceiveQueueMissedPacketAndOverflowCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveQueueMissedPacketAndOverflowCounter(ReceiveQueueMissedPacketAndOverflowCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveQueueMissedPacketAndOverflowCounter(ReceiveQueueMissedPacketAndOverflowCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveQueueMissedPacketAndOverflowCounter(ReceiveQueueMissedPacketAndOverflowCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveQueueMissedPacketAndOverflowCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveQueueMissedPacketAndOverflowCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveQueueMissedPacketAndOverflowCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// OVFPKTCNT (OVFPKTCNT)
            uint32_t overflow_packet_count            : 11;    // bits 0:10
            /// OVFCNTOVF (OVFCNTOVF)
            uint32_t overflow_packet_counter_overflow : 1;    // bit 11
            /// (reserved)
            uint32_t                                  : 4;    // bits 12:15
            /// MISPKTCNT (MISPKTCNT)
            uint32_t missed_packet_count              : 11;    // bits 16:26
            /// MISCNTOVF (MISCNTOVF)
            uint32_t missed_packet_counter_overflow   : 1;    // bit 27
            /// (reserved)
            uint32_t                                  : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveQueueMissedPacketAndOverflowCounter& operator=(ReceiveQueueMissedPacketAndOverflowCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueMissedPacketAndOverflowCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueMissedPacketAndOverflowCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveQueueMissedPacketAndOverflowCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveQueueMissedPacketAndOverflowCounter) == 4UL, "Must be this exact size");
    /// Rx queue debug register (MTLRxQDR)
    struct ReceiveQueueDebug final {
        /// Default Constructor
        ReceiveQueueDebug()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveQueueDebug(ReceiveQueueDebug volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveQueueDebug(ReceiveQueueDebug const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveQueueDebug(ReceiveQueueDebug&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveQueueDebug(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveQueueDebug(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveQueueDebug() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RWCSTS (RWCSTS)
            uint32_t receive_write_controller_status : 1;    // bit 0
            /// RRCSTS (RRCSTS)
            uint32_t receive_read_controller_status  : 2;    // bits 1:2
            /// (reserved)
            uint32_t                                 : 1;    // bit 3
            /// RXQSTS (RXQSTS)
            uint32_t receive_queue_status            : 2;    // bits 4:5
            /// (reserved)
            uint32_t                                 : 10;    // bits 6:15
            /// PRXQ (PRXQ)
            uint32_t packets_in_receive_queue        : 14;    // bits 16:29
            /// (reserved)
            uint32_t                                 : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveQueueDebug& operator=(ReceiveQueueDebug&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueDebug volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveQueueDebug const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveQueueDebug>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveQueueDebug) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Operating mode Register (MTLOMR)
    OperatingMode operating_mode;    // offset 0x0UL
    uint32_t : 32;                   // offset 0x4UL
    uint32_t : 32;                   // offset 0x8UL
    uint32_t : 32;                   // offset 0xcUL
    uint32_t : 32;                   // offset 0x10UL
    uint32_t : 32;                   // offset 0x14UL
    uint32_t : 32;                   // offset 0x18UL
    uint32_t : 32;                   // offset 0x1cUL
    /// Interrupt status Register (MTLISR)
    InterruptStatus interrupt_status;    // offset 0x20UL
    uint32_t : 32;                       // offset 0x24UL
    uint32_t : 32;                       // offset 0x28UL
    uint32_t : 32;                       // offset 0x2cUL
    uint32_t : 32;                       // offset 0x30UL
    uint32_t : 32;                       // offset 0x34UL
    uint32_t : 32;                       // offset 0x38UL
    uint32_t : 32;                       // offset 0x3cUL
    uint32_t : 32;                       // offset 0x40UL
    uint32_t : 32;                       // offset 0x44UL
    uint32_t : 32;                       // offset 0x48UL
    uint32_t : 32;                       // offset 0x4cUL
    uint32_t : 32;                       // offset 0x50UL
    uint32_t : 32;                       // offset 0x54UL
    uint32_t : 32;                       // offset 0x58UL
    uint32_t : 32;                       // offset 0x5cUL
    uint32_t : 32;                       // offset 0x60UL
    uint32_t : 32;                       // offset 0x64UL
    uint32_t : 32;                       // offset 0x68UL
    uint32_t : 32;                       // offset 0x6cUL
    uint32_t : 32;                       // offset 0x70UL
    uint32_t : 32;                       // offset 0x74UL
    uint32_t : 32;                       // offset 0x78UL
    uint32_t : 32;                       // offset 0x7cUL
    uint32_t : 32;                       // offset 0x80UL
    uint32_t : 32;                       // offset 0x84UL
    uint32_t : 32;                       // offset 0x88UL
    uint32_t : 32;                       // offset 0x8cUL
    uint32_t : 32;                       // offset 0x90UL
    uint32_t : 32;                       // offset 0x94UL
    uint32_t : 32;                       // offset 0x98UL
    uint32_t : 32;                       // offset 0x9cUL
    uint32_t : 32;                       // offset 0xa0UL
    uint32_t : 32;                       // offset 0xa4UL
    uint32_t : 32;                       // offset 0xa8UL
    uint32_t : 32;                       // offset 0xacUL
    uint32_t : 32;                       // offset 0xb0UL
    uint32_t : 32;                       // offset 0xb4UL
    uint32_t : 32;                       // offset 0xb8UL
    uint32_t : 32;                       // offset 0xbcUL
    uint32_t : 32;                       // offset 0xc0UL
    uint32_t : 32;                       // offset 0xc4UL
    uint32_t : 32;                       // offset 0xc8UL
    uint32_t : 32;                       // offset 0xccUL
    uint32_t : 32;                       // offset 0xd0UL
    uint32_t : 32;                       // offset 0xd4UL
    uint32_t : 32;                       // offset 0xd8UL
    uint32_t : 32;                       // offset 0xdcUL
    uint32_t : 32;                       // offset 0xe0UL
    uint32_t : 32;                       // offset 0xe4UL
    uint32_t : 32;                       // offset 0xe8UL
    uint32_t : 32;                       // offset 0xecUL
    uint32_t : 32;                       // offset 0xf0UL
    uint32_t : 32;                       // offset 0xf4UL
    uint32_t : 32;                       // offset 0xf8UL
    uint32_t : 32;                       // offset 0xfcUL
    /// Tx queue operating mode Register (MTLTxQOMR)
    TransmitQueueOperatingMode transmit_queue_operating_mode;    // offset 0x100UL
    /// Tx queue underflow register (MTLTxQUR)
    TransmitQueueUnderflow transmit_queue_underflow;    // offset 0x104UL
    /// Tx queue debug Register (MTLTxQDR)
    TransmitQueueDebug transmit_queue_debug;    // offset 0x108UL
    uint32_t : 32;                              // offset 0x10cUL
    uint32_t : 32;                              // offset 0x110UL
    uint32_t : 32;                              // offset 0x114UL
    uint32_t : 32;                              // offset 0x118UL
    uint32_t : 32;                              // offset 0x11cUL
    uint32_t : 32;                              // offset 0x120UL
    uint32_t : 32;                              // offset 0x124UL
    uint32_t : 32;                              // offset 0x128UL
    /// Queue interrupt control status Register (MTLQICSR)
    QueueInterruptControlStatus queue_interrupt_control_status;    // offset 0x12cUL
    /// Rx queue operating mode register (MTLRxQOMR)
    ReceiveQueueOperatingMode receive_queue_operating_mode;    // offset 0x130UL
    /// Rx queue missed packet and overflow counter register (MTLRxQMPOCR)
    ReceiveQueueMissedPacketAndOverflowCounter receive_queue_missed_packet_and_overflow_counter;    // offset 0x134UL
    /// Rx queue debug register (MTLRxQDR)
    ReceiveQueueDebug receive_queue_debug;    // offset 0x138UL
    uint32_t : 32;                            // offset 0x13cUL
    uint32_t : 32;                            // offset 0x140UL
    uint32_t : 32;                            // offset 0x144UL
    uint32_t : 32;                            // offset 0x148UL
    uint32_t : 32;                            // offset 0x14cUL
    uint32_t : 32;                            // offset 0x150UL
    uint32_t : 32;                            // offset 0x154UL
    uint32_t : 32;                            // offset 0x158UL
    uint32_t : 32;                            // offset 0x15cUL
    uint32_t : 32;                            // offset 0x160UL
    uint32_t : 32;                            // offset 0x164UL
    uint32_t : 32;                            // offset 0x168UL
    uint32_t : 32;                            // offset 0x16cUL
    uint32_t : 32;                            // offset 0x170UL
    uint32_t : 32;                            // offset 0x174UL
    uint32_t : 32;                            // offset 0x178UL
    uint32_t : 32;                            // offset 0x17cUL
    uint32_t : 32;                            // offset 0x180UL
    uint32_t : 32;                            // offset 0x184UL
    uint32_t : 32;                            // offset 0x188UL
    uint32_t : 32;                            // offset 0x18cUL
    uint32_t : 32;                            // offset 0x190UL
    uint32_t : 32;                            // offset 0x194UL
    uint32_t : 32;                            // offset 0x198UL
    uint32_t : 32;                            // offset 0x19cUL
    uint32_t : 32;                            // offset 0x1a0UL
    uint32_t : 32;                            // offset 0x1a4UL
    uint32_t : 32;                            // offset 0x1a8UL
    uint32_t : 32;                            // offset 0x1acUL
    uint32_t : 32;                            // offset 0x1b0UL
    uint32_t : 32;                            // offset 0x1b4UL
    uint32_t : 32;                            // offset 0x1b8UL
    uint32_t : 32;                            // offset 0x1bcUL
    uint32_t : 32;                            // offset 0x1c0UL
    uint32_t : 32;                            // offset 0x1c4UL
    uint32_t : 32;                            // offset 0x1c8UL
    uint32_t : 32;                            // offset 0x1ccUL
    uint32_t : 32;                            // offset 0x1d0UL
    uint32_t : 32;                            // offset 0x1d4UL
    uint32_t : 32;                            // offset 0x1d8UL
    uint32_t : 32;                            // offset 0x1dcUL
    uint32_t : 32;                            // offset 0x1e0UL
    uint32_t : 32;                            // offset 0x1e4UL
    uint32_t : 32;                            // offset 0x1e8UL
    uint32_t : 32;                            // offset 0x1ecUL
    uint32_t : 32;                            // offset 0x1f0UL
    uint32_t : 32;                            // offset 0x1f4UL
    uint32_t : 32;                            // offset 0x1f8UL
    uint32_t : 32;                            // offset 0x1fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<EthernetMediaTransactionLayer>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(EthernetMediaTransactionLayer, operating_mode) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, interrupt_status) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, transmit_queue_operating_mode) == 0x100UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, transmit_queue_underflow) == 0x104UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, transmit_queue_debug) == 0x108UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, queue_interrupt_control_status) == 0x12cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, receive_queue_operating_mode) == 0x130UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, receive_queue_missed_packet_and_overflow_counter) == 0x134UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaTransactionLayer, receive_queue_debug) == 0x138UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(EthernetMediaTransactionLayer) == 0x200UL, "Must be this exact size");

/// The external volatile ethernet_media_transaction_layer which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern EthernetMediaTransactionLayer volatile ethernet_media_transaction_layer;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_ETHERNETMEDIATRANSACTIONLAYER__HPP_
