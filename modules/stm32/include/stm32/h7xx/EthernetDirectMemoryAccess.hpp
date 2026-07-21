
#ifndef STM32_H7XX_ETHERNETDIRECTMEMORYACCESS__HPP_
#define STM32_H7XX_ETHERNETDIRECTMEMORYACCESS__HPP_

/// @file
/// Auto Generated Structure Definitions for EthernetDirectMemoryAccess from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Ethernet: DMA mode register (DMA) (Ethernet_DMA)
struct EthernetDirectMemoryAccess final {
    /// DMA mode register (DMAMR)
    struct Mode final {
        /// Default Constructor
        Mode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Mode(Mode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Mode(Mode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Mode(Mode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Mode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Mode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Mode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Software Reset (SWR)
            uint32_t software_reset                          : 1;    // bit 0
            /// DMA Tx or Rx Arbitration Scheme (DA)
            uint32_t dma_transmit_receive_arbitration_scheme : 1;    // bit 1
            /// (reserved)
            uint32_t                                         : 9;    // bits 2:10
            /// Transmit priority (TXPR)
            uint32_t transmit_priority                       : 1;    // bit 11
            /// Priority ratio (PR)
            uint32_t pending                                 : 3;    // bits 12:14
            /// (reserved)
            uint32_t                                         : 1;    // bit 15
            /// Interrupt Mode (INTM)
            uint32_t interrupt_mode                          : 1;    // bit 16
            /// (reserved)
            uint32_t                                         : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Mode& operator=(Mode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Mode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Mode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Mode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Mode) == 4UL, "Must be this exact size");
    /// System bus mode register (DMASBMR)
    struct SystemBusMode final {
        /// Default Constructor
        SystemBusMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SystemBusMode(SystemBusMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SystemBusMode(SystemBusMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SystemBusMode(SystemBusMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SystemBusMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SystemBusMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SystemBusMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Fixed Burst Length (FB)
            uint32_t fixed_burst_length    : 1;    // bit 0
            /// (reserved)
            uint32_t                       : 11;    // bits 1:11
            /// Address-Aligned Beats (AAL)
            uint32_t address_aligned_beats : 1;    // bit 12
            /// (reserved)
            uint32_t                       : 1;    // bit 13
            /// Mixed Burst (MB)
            uint32_t mixed_burst           : 1;    // bit 14
            /// Rebuild INCRx Burst (RB)
            uint32_t rebuild_incrx_burst   : 1;    // bit 15
            /// (reserved)
            uint32_t                       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SystemBusMode& operator=(SystemBusMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SystemBusMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SystemBusMode const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SystemBusMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SystemBusMode) == 4UL, "Must be this exact size");
    /// Interrupt status register (DMAISR)
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
            /// DMA Channel Interrupt Status (DC0IS)
            uint32_t dma_channel_interrupt_status             : 1;    // bit 0
            /// (reserved)
            uint32_t                                          : 15;    // bits 1:15
            /// MTL Interrupt Status (MTLIS)
            uint32_t media_transaction_layer_interrupt_status : 1;    // bit 16
            /// MAC Interrupt Status (MACIS)
            uint32_t media_access_controller_interrupt_status : 1;    // bit 17
            /// (reserved)
            uint32_t                                          : 14;    // bits 18:31
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
    /// Debug status register (DMADSR)
    struct DebugStatus final {
        /// Default Constructor
        DebugStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        DebugStatus(DebugStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        DebugStatus(DebugStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        DebugStatus(DebugStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit DebugStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit DebugStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~DebugStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// AHB Master Write Channel (AXWHSTS)
            uint32_t ahb_master_write_channel           : 1;    // bit 0
            /// (reserved)
            uint32_t                                    : 7;    // bits 1:7
            /// DMA Channel Receive Process State (RPS0)
            uint32_t dma_channel_receive_process_state  : 4;    // bits 8:11
            /// DMA Channel Transmit Process State (TPS0)
            uint32_t dma_channel_transmit_process_state : 4;    // bits 12:15
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
        DebugStatus& operator=(DebugStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(DebugStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(DebugStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<DebugStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(DebugStatus) == 4UL, "Must be this exact size");
    /// Channel control register (DMACCR)
    struct ChannelControl final {
        /// Default Constructor
        ChannelControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelControl(ChannelControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelControl(ChannelControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelControl(ChannelControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Maximum Segment Size (MSS)
            uint32_t maximum_segment_size                 : 14;    // bits 0:13
            /// (reserved)
            uint32_t                                      : 2;    // bits 14:15
            /// 8xPBL mode (PBLX8)
            uint32_t programmable_burst_length_scale_by_8 : 1;    // bit 16
            /// (reserved)
            uint32_t                                      : 1;    // bit 17
            /// Descriptor Skip Length (DSL)
            uint32_t descriptor_skip_length               : 3;    // bits 18:20
            /// (reserved)
            uint32_t                                      : 11;    // bits 21:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelControl& operator=(ChannelControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelControl) == 4UL, "Must be this exact size");
    /// Channel transmit control register (DMACTxCR)
    struct ChannelTransmitControl final {
        /// Default Constructor
        ChannelTransmitControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelTransmitControl(ChannelTransmitControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelTransmitControl(ChannelTransmitControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelTransmitControl(ChannelTransmitControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelTransmitControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelTransmitControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelTransmitControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Start or Stop Transmission Command (ST)
            uint32_t start                              : 1;    // bit 0
            /// (reserved)
            uint32_t                                    : 3;    // bits 1:3
            /// Operate on Second Packet (OSF)
            uint32_t operate_second_packet              : 1;    // bit 4
            /// (reserved)
            uint32_t                                    : 7;    // bits 5:11
            /// TCP Segmentation Enabled (TSE)
            uint32_t tcp_segmentation_enabled           : 1;    // bit 12
            /// (reserved)
            uint32_t                                    : 3;    // bits 13:15
            /// Transmit Programmable Burst Length (TXPBL)
            uint32_t transmit_programmable_burst_length : 6;    // bits 16:21
            /// (reserved)
            uint32_t                                    : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelTransmitControl& operator=(ChannelTransmitControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelTransmitControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelTransmitControl) == 4UL, "Must be this exact size");
    /// Channel receive control register (DMACRxCR)
    struct ChannelReceiveControl final {
        /// Default Constructor
        ChannelReceiveControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelReceiveControl(ChannelReceiveControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelReceiveControl(ChannelReceiveControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelReceiveControl(ChannelReceiveControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelReceiveControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelReceiveControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelReceiveControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Start or Stop Receive Command (SR)
            uint32_t status                            : 1;    // bit 0
            /// Receive Buffer size (RBSZ)
            uint32_t receive_buffer_size               : 14;    // bits 1:14
            /// (reserved)
            uint32_t                                   : 1;    // bit 15
            /// RXPBL (RXPBL)
            uint32_t receive_programmable_burst_length : 6;    // bits 16:21
            /// (reserved)
            uint32_t                                   : 9;    // bits 22:30
            /// DMA Rx Channel Packet Flush (RPF)
            uint32_t dma_receive_channel_packet_flush  : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelReceiveControl& operator=(ChannelReceiveControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelReceiveControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelReceiveControl) == 4UL, "Must be this exact size");
    /// Channel Tx descriptor list address register (DMACTxDLAR)
    struct ChannelTransmitDescriptorListAddress final {
        /// Default Constructor
        ChannelTransmitDescriptorListAddress()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelTransmitDescriptorListAddress(ChannelTransmitDescriptorListAddress volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelTransmitDescriptorListAddress(ChannelTransmitDescriptorListAddress const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelTransmitDescriptorListAddress(ChannelTransmitDescriptorListAddress&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelTransmitDescriptorListAddress(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelTransmitDescriptorListAddress(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelTransmitDescriptorListAddress() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                     : 2;    // bits 0:1
            /// Start of Transmit List (TDESLA)
            uint32_t start_transmit_list : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelTransmitDescriptorListAddress& operator=(ChannelTransmitDescriptorListAddress&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorListAddress volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorListAddress const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelTransmitDescriptorListAddress>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelTransmitDescriptorListAddress) == 4UL, "Must be this exact size");
    /// Channel Rx descriptor list address register (DMACRxDLAR)
    struct ChannelReceiveDescriptorListAddress final {
        /// Default Constructor
        ChannelReceiveDescriptorListAddress()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelReceiveDescriptorListAddress(ChannelReceiveDescriptorListAddress volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelReceiveDescriptorListAddress(ChannelReceiveDescriptorListAddress const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelReceiveDescriptorListAddress(ChannelReceiveDescriptorListAddress&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelReceiveDescriptorListAddress(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelReceiveDescriptorListAddress(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelReceiveDescriptorListAddress() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                    : 2;    // bits 0:1
            /// Start of Receive List (RDESLA)
            uint32_t start_receive_list : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelReceiveDescriptorListAddress& operator=(ChannelReceiveDescriptorListAddress&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorListAddress volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorListAddress const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelReceiveDescriptorListAddress>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelReceiveDescriptorListAddress) == 4UL, "Must be this exact size");
    /// Channel Tx descriptor tail pointer register (DMACTxDTPR)
    struct ChannelTransmitDescriptorTailPointer final {
        /// Default Constructor
        ChannelTransmitDescriptorTailPointer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelTransmitDescriptorTailPointer(ChannelTransmitDescriptorTailPointer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelTransmitDescriptorTailPointer(ChannelTransmitDescriptorTailPointer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelTransmitDescriptorTailPointer(ChannelTransmitDescriptorTailPointer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelTransmitDescriptorTailPointer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelTransmitDescriptorTailPointer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelTransmitDescriptorTailPointer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                  : 2;    // bits 0:1
            /// Transmit Descriptor Tail Pointer (TDT)
            uint32_t transmit_descriptor_tail_pointer : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelTransmitDescriptorTailPointer& operator=(ChannelTransmitDescriptorTailPointer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorTailPointer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorTailPointer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelTransmitDescriptorTailPointer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelTransmitDescriptorTailPointer) == 4UL, "Must be this exact size");
    /// Channel Rx descriptor tail pointer register (DMACRxDTPR)
    struct ChannelReceiveDescriptorTailPointer final {
        /// Default Constructor
        ChannelReceiveDescriptorTailPointer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelReceiveDescriptorTailPointer(ChannelReceiveDescriptorTailPointer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelReceiveDescriptorTailPointer(ChannelReceiveDescriptorTailPointer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelReceiveDescriptorTailPointer(ChannelReceiveDescriptorTailPointer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelReceiveDescriptorTailPointer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelReceiveDescriptorTailPointer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelReceiveDescriptorTailPointer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                 : 2;    // bits 0:1
            /// Receive Descriptor Tail Pointer (RDT)
            uint32_t receive_descriptor_tail_pointer : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelReceiveDescriptorTailPointer& operator=(ChannelReceiveDescriptorTailPointer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorTailPointer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorTailPointer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelReceiveDescriptorTailPointer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelReceiveDescriptorTailPointer) == 4UL, "Must be this exact size");
    /// Channel Tx descriptor ring length register (DMACTxRLR)
    struct ChannelTransmitDescriptorRingLength final {
        /// Default Constructor
        ChannelTransmitDescriptorRingLength()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelTransmitDescriptorRingLength(ChannelTransmitDescriptorRingLength volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelTransmitDescriptorRingLength(ChannelTransmitDescriptorRingLength const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelTransmitDescriptorRingLength(ChannelTransmitDescriptorRingLength&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelTransmitDescriptorRingLength(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelTransmitDescriptorRingLength(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelTransmitDescriptorRingLength() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Transmit Descriptor Ring Length (TDRL)
            uint32_t transmit_descriptor_ring_length : 10;    // bits 0:9
            /// (reserved)
            uint32_t                                 : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelTransmitDescriptorRingLength& operator=(ChannelTransmitDescriptorRingLength&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorRingLength volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelTransmitDescriptorRingLength const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value & 0x3FFU; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ChannelTransmitDescriptorRingLength>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelTransmitDescriptorRingLength) == 4UL, "Must be this exact size");
    /// Channel Rx descriptor ring length register (DMACRxRLR)
    struct ChannelReceiveDescriptorRingLength final {
        /// Default Constructor
        ChannelReceiveDescriptorRingLength()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelReceiveDescriptorRingLength(ChannelReceiveDescriptorRingLength volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelReceiveDescriptorRingLength(ChannelReceiveDescriptorRingLength const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelReceiveDescriptorRingLength(ChannelReceiveDescriptorRingLength&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelReceiveDescriptorRingLength(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelReceiveDescriptorRingLength(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelReceiveDescriptorRingLength() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Receive Descriptor Ring Length (RDRL)
            uint32_t receive_descriptor_ring_length : 10;    // bits 0:9
            /// (reserved)
            uint32_t                                : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelReceiveDescriptorRingLength& operator=(ChannelReceiveDescriptorRingLength&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorRingLength volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveDescriptorRingLength const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value & 0x3FFU; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<ChannelReceiveDescriptorRingLength>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelReceiveDescriptorRingLength) == 4UL, "Must be this exact size");
    /// Channel interrupt enable register (DMACIER)
    struct ChannelInterruptEnable final {
        /// Default Constructor
        ChannelInterruptEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelInterruptEnable(ChannelInterruptEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelInterruptEnable(ChannelInterruptEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelInterruptEnable(ChannelInterruptEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelInterruptEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelInterruptEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelInterruptEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Transmit Interrupt Enable (TIE)
            uint32_t trigger_interrupt_enable           : 1;    // bit 0
            /// Transmit Stopped Enable (TXSE)
            uint32_t transmit_stopped_enable            : 1;    // bit 1
            /// Transmit Buffer Unavailable Enable (TBUE)
            uint32_t transmit_buffer_unavailable_enable : 1;    // bit 2
            /// (reserved)
            uint32_t                                    : 3;    // bits 3:5
            /// Receive Interrupt Enable (RIE)
            uint32_t receive_interrupt_enable           : 1;    // bit 6
            /// Receive Buffer Unavailable Enable (RBUE)
            uint32_t receive_buffer_unavailable_enable  : 1;    // bit 7
            /// Receive Stopped Enable (RSE)
            uint32_t receive_stopped_enable             : 1;    // bit 8
            /// Receive Watchdog Timeout Enable (RWTE)
            uint32_t receive_watchdog_timeout_enable    : 1;    // bit 9
            /// Early Transmit Interrupt Enable (ETIE)
            uint32_t early_transmit_interrupt_enable    : 1;    // bit 10
            /// Early Receive Interrupt Enable (ERIE)
            uint32_t early_receive_interrupt_enable     : 1;    // bit 11
            /// Fatal Bus Error Enable (FBEE)
            uint32_t fatal_bus_error_enable             : 1;    // bit 12
            /// Context Descriptor Error Enable (CDEE)
            uint32_t context_descriptor_error_enable    : 1;    // bit 13
            /// Abnormal Interrupt Summary Enable (AIE)
            uint32_t abnormal_interrupt_summary_enable  : 1;    // bit 14
            /// Normal Interrupt Summary Enable (NIE)
            uint32_t normal_interrupt_summary_enable    : 1;    // bit 15
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
        ChannelInterruptEnable& operator=(ChannelInterruptEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelInterruptEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelInterruptEnable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelInterruptEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelInterruptEnable) == 4UL, "Must be this exact size");
    /// Channel Rx interrupt watchdog timer register (DMACRxIWTR)
    struct ChannelReceiveInterruptWatchdogTimer final {
        /// Default Constructor
        ChannelReceiveInterruptWatchdogTimer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelReceiveInterruptWatchdogTimer(ChannelReceiveInterruptWatchdogTimer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelReceiveInterruptWatchdogTimer(ChannelReceiveInterruptWatchdogTimer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelReceiveInterruptWatchdogTimer(ChannelReceiveInterruptWatchdogTimer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelReceiveInterruptWatchdogTimer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelReceiveInterruptWatchdogTimer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelReceiveInterruptWatchdogTimer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Receive Interrupt Watchdog Timer Count (RWT)
            uint32_t receive_interrupt_watchdog_timer_count : 8;    // bits 0:7
            /// (reserved)
            uint32_t                                        : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelReceiveInterruptWatchdogTimer& operator=(ChannelReceiveInterruptWatchdogTimer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveInterruptWatchdogTimer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelReceiveInterruptWatchdogTimer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelReceiveInterruptWatchdogTimer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelReceiveInterruptWatchdogTimer) == 4UL, "Must be this exact size");
    /// Channel current application transmit descriptor register (DMACCATxDR)
    struct ChannelCurrentApplicationTransmitDescriptor final {
        /// Default Constructor
        ChannelCurrentApplicationTransmitDescriptor()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelCurrentApplicationTransmitDescriptor(ChannelCurrentApplicationTransmitDescriptor volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelCurrentApplicationTransmitDescriptor(ChannelCurrentApplicationTransmitDescriptor const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelCurrentApplicationTransmitDescriptor(ChannelCurrentApplicationTransmitDescriptor&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelCurrentApplicationTransmitDescriptor(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelCurrentApplicationTransmitDescriptor(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelCurrentApplicationTransmitDescriptor() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Application Transmit Descriptor Address Pointer (CURTDESAPTR)
            uint32_t application_transmit_descriptor_address_pointer : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelCurrentApplicationTransmitDescriptor& operator=(ChannelCurrentApplicationTransmitDescriptor&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationTransmitDescriptor volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationTransmitDescriptor const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelCurrentApplicationTransmitDescriptor>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelCurrentApplicationTransmitDescriptor) == 4UL, "Must be this exact size");
    /// Channel current application receive descriptor register (DMACCARxDR)
    struct ChannelCurrentApplicationReceiveDescriptor final {
        /// Default Constructor
        ChannelCurrentApplicationReceiveDescriptor()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelCurrentApplicationReceiveDescriptor(ChannelCurrentApplicationReceiveDescriptor volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelCurrentApplicationReceiveDescriptor(ChannelCurrentApplicationReceiveDescriptor const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelCurrentApplicationReceiveDescriptor(ChannelCurrentApplicationReceiveDescriptor&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelCurrentApplicationReceiveDescriptor(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelCurrentApplicationReceiveDescriptor(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelCurrentApplicationReceiveDescriptor() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Application Receive Descriptor Address Pointer (CURRDESAPTR)
            uint32_t application_receive_descriptor_address_pointer : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelCurrentApplicationReceiveDescriptor& operator=(ChannelCurrentApplicationReceiveDescriptor&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationReceiveDescriptor volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationReceiveDescriptor const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelCurrentApplicationReceiveDescriptor>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelCurrentApplicationReceiveDescriptor) == 4UL, "Must be this exact size");
    /// Channel current application transmit buffer register (DMACCATxBR)
    struct ChannelCurrentApplicationTransmitBuffer final {
        /// Default Constructor
        ChannelCurrentApplicationTransmitBuffer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelCurrentApplicationTransmitBuffer(ChannelCurrentApplicationTransmitBuffer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelCurrentApplicationTransmitBuffer(ChannelCurrentApplicationTransmitBuffer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelCurrentApplicationTransmitBuffer(ChannelCurrentApplicationTransmitBuffer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelCurrentApplicationTransmitBuffer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelCurrentApplicationTransmitBuffer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelCurrentApplicationTransmitBuffer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Application Transmit Buffer Address Pointer (CURTBUFAPTR)
            uint32_t application_transmit_buffer_address_pointer : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelCurrentApplicationTransmitBuffer& operator=(ChannelCurrentApplicationTransmitBuffer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationTransmitBuffer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationTransmitBuffer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelCurrentApplicationTransmitBuffer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelCurrentApplicationTransmitBuffer) == 4UL, "Must be this exact size");
    /// Channel current application receive buffer register (DMACCARxBR)
    struct ChannelCurrentApplicationReceiveBuffer final {
        /// Default Constructor
        ChannelCurrentApplicationReceiveBuffer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelCurrentApplicationReceiveBuffer(ChannelCurrentApplicationReceiveBuffer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelCurrentApplicationReceiveBuffer(ChannelCurrentApplicationReceiveBuffer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelCurrentApplicationReceiveBuffer(ChannelCurrentApplicationReceiveBuffer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelCurrentApplicationReceiveBuffer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelCurrentApplicationReceiveBuffer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelCurrentApplicationReceiveBuffer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Application Receive Buffer Address Pointer (CURRBUFAPTR)
            uint32_t application_receive_buffer_address_pointer : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelCurrentApplicationReceiveBuffer& operator=(ChannelCurrentApplicationReceiveBuffer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationReceiveBuffer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelCurrentApplicationReceiveBuffer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelCurrentApplicationReceiveBuffer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelCurrentApplicationReceiveBuffer) == 4UL, "Must be this exact size");
    /// Channel status register (DMACSR)
    struct ChannelStatus final {
        /// Default Constructor
        ChannelStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelStatus(ChannelStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelStatus(ChannelStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelStatus(ChannelStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Transmit Interrupt (TI)
            uint32_t transmit_interrupt          : 1;    // bit 0
            /// Transmit Process Stopped (TPS)
            uint32_t transmit_process_stopped    : 1;    // bit 1
            /// Transmit Buffer Unavailable (TBU)
            uint32_t transmit_buffer_unavailable : 1;    // bit 2
            /// (reserved)
            uint32_t                             : 3;    // bits 3:5
            /// Receive Interrupt (RI)
            uint32_t receive_interrupt           : 1;    // bit 6
            /// Receive Buffer Unavailable (RBU)
            uint32_t receive_buffer_unavailable  : 1;    // bit 7
            /// Receive Process Stopped (RPS)
            uint32_t receive_process_stopped     : 1;    // bit 8
            /// Receive Watchdog Timeout (RWT)
            uint32_t receive_watchdog_timeout    : 1;    // bit 9
            /// Early Transmit Interrupt (ET)
            uint32_t early_transmit_interrupt    : 1;    // bit 10
            /// Early Receive Interrupt (ER)
            uint32_t early_receive_interrupt     : 1;    // bit 11
            /// Fatal Bus Error (FBE)
            uint32_t fatal_bus_error             : 1;    // bit 12
            /// Context Descriptor Error (CDE)
            uint32_t context_descriptor_error    : 1;    // bit 13
            /// Abnormal Interrupt Summary (AIS)
            uint32_t abnormal_interrupt_summary  : 1;    // bit 14
            /// Normal Interrupt Summary (NIS)
            uint32_t normal_interrupt_summary    : 1;    // bit 15
            /// Tx DMA Error Bits (TEB)
            uint32_t transmit_dma_error_bits     : 3;    // bits 16:18
            /// Rx DMA Error Bits (REB)
            uint32_t receive_dma_error_bits      : 3;    // bits 19:21
            /// (reserved)
            uint32_t                             : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ChannelStatus& operator=(ChannelStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelStatus) == 4UL, "Must be this exact size");
    /// Channel missed frame count register (DMACMFCR)
    struct ChannelMissedFrameCount final {
        /// Default Constructor
        ChannelMissedFrameCount()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ChannelMissedFrameCount(ChannelMissedFrameCount volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ChannelMissedFrameCount(ChannelMissedFrameCount const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ChannelMissedFrameCount(ChannelMissedFrameCount&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ChannelMissedFrameCount(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ChannelMissedFrameCount(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ChannelMissedFrameCount() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Dropped Packet Counters (MFC)
            uint32_t dropped_packet_counters     : 11;    // bits 0:10
            /// (reserved)
            uint32_t                             : 4;    // bits 11:14
            /// Overflow status of the MFC Counter (MFCO)
            uint32_t overflow_status_mfc_counter : 1;    // bit 15
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
        ChannelMissedFrameCount& operator=(ChannelMissedFrameCount&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ChannelMissedFrameCount volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ChannelMissedFrameCount const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ChannelMissedFrameCount>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ChannelMissedFrameCount) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// DMA mode register (DMAMR)
    Mode mode;    // offset 0x0UL
    /// System bus mode register (DMASBMR)
    SystemBusMode system_bus_mode;    // offset 0x4UL
    /// Interrupt status register (DMAISR)
    InterruptStatus interrupt_status;    // offset 0x8UL
    /// Debug status register (DMADSR)
    DebugStatus debug_status;    // offset 0xcUL
    uint32_t : 32;               // offset 0x10UL
    uint32_t : 32;               // offset 0x14UL
    uint32_t : 32;               // offset 0x18UL
    uint32_t : 32;               // offset 0x1cUL
    uint32_t : 32;               // offset 0x20UL
    uint32_t : 32;               // offset 0x24UL
    uint32_t : 32;               // offset 0x28UL
    uint32_t : 32;               // offset 0x2cUL
    uint32_t : 32;               // offset 0x30UL
    uint32_t : 32;               // offset 0x34UL
    uint32_t : 32;               // offset 0x38UL
    uint32_t : 32;               // offset 0x3cUL
    uint32_t : 32;               // offset 0x40UL
    uint32_t : 32;               // offset 0x44UL
    uint32_t : 32;               // offset 0x48UL
    uint32_t : 32;               // offset 0x4cUL
    uint32_t : 32;               // offset 0x50UL
    uint32_t : 32;               // offset 0x54UL
    uint32_t : 32;               // offset 0x58UL
    uint32_t : 32;               // offset 0x5cUL
    uint32_t : 32;               // offset 0x60UL
    uint32_t : 32;               // offset 0x64UL
    uint32_t : 32;               // offset 0x68UL
    uint32_t : 32;               // offset 0x6cUL
    uint32_t : 32;               // offset 0x70UL
    uint32_t : 32;               // offset 0x74UL
    uint32_t : 32;               // offset 0x78UL
    uint32_t : 32;               // offset 0x7cUL
    uint32_t : 32;               // offset 0x80UL
    uint32_t : 32;               // offset 0x84UL
    uint32_t : 32;               // offset 0x88UL
    uint32_t : 32;               // offset 0x8cUL
    uint32_t : 32;               // offset 0x90UL
    uint32_t : 32;               // offset 0x94UL
    uint32_t : 32;               // offset 0x98UL
    uint32_t : 32;               // offset 0x9cUL
    uint32_t : 32;               // offset 0xa0UL
    uint32_t : 32;               // offset 0xa4UL
    uint32_t : 32;               // offset 0xa8UL
    uint32_t : 32;               // offset 0xacUL
    uint32_t : 32;               // offset 0xb0UL
    uint32_t : 32;               // offset 0xb4UL
    uint32_t : 32;               // offset 0xb8UL
    uint32_t : 32;               // offset 0xbcUL
    uint32_t : 32;               // offset 0xc0UL
    uint32_t : 32;               // offset 0xc4UL
    uint32_t : 32;               // offset 0xc8UL
    uint32_t : 32;               // offset 0xccUL
    uint32_t : 32;               // offset 0xd0UL
    uint32_t : 32;               // offset 0xd4UL
    uint32_t : 32;               // offset 0xd8UL
    uint32_t : 32;               // offset 0xdcUL
    uint32_t : 32;               // offset 0xe0UL
    uint32_t : 32;               // offset 0xe4UL
    uint32_t : 32;               // offset 0xe8UL
    uint32_t : 32;               // offset 0xecUL
    uint32_t : 32;               // offset 0xf0UL
    uint32_t : 32;               // offset 0xf4UL
    uint32_t : 32;               // offset 0xf8UL
    uint32_t : 32;               // offset 0xfcUL
    /// Channel control register (DMACCR)
    ChannelControl channel_control;    // offset 0x100UL
    /// Channel transmit control register (DMACTxCR)
    ChannelTransmitControl channel_transmit_control;    // offset 0x104UL
    /// Channel receive control register (DMACRxCR)
    ChannelReceiveControl channel_receive_control;    // offset 0x108UL
    uint32_t : 32;                                    // offset 0x10cUL
    uint32_t : 32;                                    // offset 0x110UL
    /// Channel Tx descriptor list address register (DMACTxDLAR)
    ChannelTransmitDescriptorListAddress channel_transmit_descriptor_list_address;    // offset 0x114UL
    uint32_t : 32;                                                                    // offset 0x118UL
    /// Channel Rx descriptor list address register (DMACRxDLAR)
    ChannelReceiveDescriptorListAddress channel_receive_descriptor_list_address;    // offset 0x11cUL
    /// Channel Tx descriptor tail pointer register (DMACTxDTPR)
    ChannelTransmitDescriptorTailPointer channel_transmit_descriptor_tail_pointer;    // offset 0x120UL
    uint32_t : 32;                                                                    // offset 0x124UL
    /// Channel Rx descriptor tail pointer register (DMACRxDTPR)
    ChannelReceiveDescriptorTailPointer channel_receive_descriptor_tail_pointer;    // offset 0x128UL
    /// Channel Tx descriptor ring length register (DMACTxRLR)
    ChannelTransmitDescriptorRingLength channel_transmit_descriptor_ring_length;    // offset 0x12cUL
    /// Channel Rx descriptor ring length register (DMACRxRLR)
    ChannelReceiveDescriptorRingLength channel_receive_descriptor_ring_length;    // offset 0x130UL
    /// Channel interrupt enable register (DMACIER)
    ChannelInterruptEnable channel_interrupt_enable;    // offset 0x134UL
    /// Channel Rx interrupt watchdog timer register (DMACRxIWTR)
    ChannelReceiveInterruptWatchdogTimer channel_receive_interrupt_watchdog_timer;    // offset 0x138UL
    uint32_t : 32;                                                                    // offset 0x13cUL
    uint32_t : 32;                                                                    // offset 0x140UL
    /// Channel current application transmit descriptor register (DMACCATxDR)
    ChannelCurrentApplicationTransmitDescriptor channel_current_application_transmit_descriptor;    // offset 0x144UL
    uint32_t : 32;                                                                                  // offset 0x148UL
    /// Channel current application receive descriptor register (DMACCARxDR)
    ChannelCurrentApplicationReceiveDescriptor channel_current_application_receive_descriptor;    // offset 0x14cUL
    uint32_t : 32;                                                                                // offset 0x150UL
    /// Channel current application transmit buffer register (DMACCATxBR)
    ChannelCurrentApplicationTransmitBuffer channel_current_application_transmit_buffer;    // offset 0x154UL
    uint32_t : 32;                                                                          // offset 0x158UL
    /// Channel current application receive buffer register (DMACCARxBR)
    ChannelCurrentApplicationReceiveBuffer channel_current_application_receive_buffer;    // offset 0x15cUL
    /// Channel status register (DMACSR)
    ChannelStatus channel_status;    // offset 0x160UL
    uint32_t : 32;                   // offset 0x164UL
    uint32_t : 32;                   // offset 0x168UL
    /// Channel missed frame count register (DMACMFCR)
    ChannelMissedFrameCount channel_missed_frame_count;    // offset 0x16cUL
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
static_assert(std::is_standard_layout<EthernetDirectMemoryAccess>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(EthernetDirectMemoryAccess, mode) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, system_bus_mode) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, interrupt_status) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, debug_status) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_control) == 0x100UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_transmit_control) == 0x104UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_receive_control) == 0x108UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_transmit_descriptor_list_address) == 0x114UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_receive_descriptor_list_address) == 0x11cUL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_transmit_descriptor_tail_pointer) == 0x120UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_receive_descriptor_tail_pointer) == 0x128UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_transmit_descriptor_ring_length) == 0x12cUL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_receive_descriptor_ring_length) == 0x130UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_interrupt_enable) == 0x134UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_receive_interrupt_watchdog_timer) == 0x138UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_current_application_transmit_descriptor) == 0x144UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_current_application_receive_descriptor) == 0x14cUL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_current_application_transmit_buffer) == 0x154UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_current_application_receive_buffer) == 0x15cUL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_status) == 0x160UL, "Must be located at this offset");
static_assert(offsetof(EthernetDirectMemoryAccess, channel_missed_frame_count) == 0x16cUL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(EthernetDirectMemoryAccess) == 0x400UL, "Must be this exact size");

/// The external volatile ethernet_direct_memory_access which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern EthernetDirectMemoryAccess volatile ethernet_direct_memory_access;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_ETHERNETDIRECTMEMORYACCESS__HPP_
