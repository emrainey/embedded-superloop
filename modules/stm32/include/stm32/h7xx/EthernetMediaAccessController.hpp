
#ifndef STM32_H7XX_ETHERNETMEDIAACCESSCONTROLLER__HPP_
#define STM32_H7XX_ETHERNETMEDIAACCESSCONTROLLER__HPP_

/// @file
/// Auto Generated Structure Definitions for EthernetMediaAccessController from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// Ethernet: media access control (MAC) (Ethernet_MAC)
struct EthernetMediaAccessController final {
    /// Operating mode configuration register (MACCR)
    struct OperatingModeConfiguration final {
        /// Default Constructor
        OperatingModeConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OperatingModeConfiguration(OperatingModeConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OperatingModeConfiguration(OperatingModeConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OperatingModeConfiguration(OperatingModeConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OperatingModeConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OperatingModeConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OperatingModeConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Receiver Enable (RE)
            uint32_t receiver_enable                                              : 1;    // bit 0
            /// TE (TE)
            uint32_t transmitter_enable                                           : 1;    // bit 1
            /// PRELEN (PRELEN)
            uint32_t preamble_length                                              : 2;    // bits 2:3
            /// DC (DC)
            uint32_t deferral_check                                               : 1;    // bit 4
            /// BL (BL)
            uint32_t backoff_limit                                                : 2;    // bits 5:6
            /// (reserved)
            uint32_t                                                              : 1;    // bit 7
            /// DR (DR)
            uint32_t data                                                         : 1;    // bit 8
            /// DCRS (DCRS)
            uint32_t disable_carrier_sense_during_transmission                    : 1;    // bit 9
            /// DO (DO)
            uint32_t disable_receive_own                                          : 1;    // bit 10
            /// ECRSFD (ECRSFD)
            uint32_t enable_carrier_sense_before_transmission_in_full_duplex_mode : 1;    // bit 11
            /// LM (LM)
            uint32_t loopback_mode                                                : 1;    // bit 12
            /// DM (DM)
            uint32_t duplex_mode                                                  : 1;    // bit 13
            /// FES (FES)
            uint32_t fast_ethernet_speed                                          : 1;    // bit 14
            /// (reserved)
            uint32_t                                                              : 1;    // bit 15
            /// JE (JE)
            uint32_t jumbo_packets                                                : 1;    // bit 16
            /// JD (JD)
            uint32_t jabber_disable                                               : 1;    // bit 17
            /// (reserved)
            uint32_t                                                              : 1;    // bit 18
            /// WD (WD)
            uint32_t watchdog                                                     : 1;    // bit 19
            /// ACS (ACS)
            uint32_t automatic_crc_stripping                                      : 1;    // bit 20
            /// CST (CST)
            uint32_t crc_stripping_for_type_packets                               : 1;    // bit 21
            /// S2KP (S2KP)
            uint32_t support_2k_packets                                           : 1;    // bit 22
            /// GPSLCE (GPSLCE)
            uint32_t giant_packet_size_limit_control_enable                       : 1;    // bit 23
            /// IPG (IPG)
            uint32_t inter_packet_gap                                             : 3;    // bits 24:26
            /// IPC (IPC)
            uint32_t ip_checksum_offload                                          : 1;    // bit 27
            /// SARC (SARC)
            uint32_t source_address_insertion_control                             : 3;    // bits 28:30
            /// ARPEN (ARPEN)
            uint32_t arp_enable                                                   : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OperatingModeConfiguration& operator=(OperatingModeConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OperatingModeConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OperatingModeConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OperatingModeConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OperatingModeConfiguration) == 4UL, "Must be this exact size");
    /// Extended operating mode configuration register (MACECR)
    struct ExtendedOperatingModeConfiguration final {
        /// Default Constructor
        ExtendedOperatingModeConfiguration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ExtendedOperatingModeConfiguration(ExtendedOperatingModeConfiguration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ExtendedOperatingModeConfiguration(ExtendedOperatingModeConfiguration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ExtendedOperatingModeConfiguration(ExtendedOperatingModeConfiguration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ExtendedOperatingModeConfiguration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ExtendedOperatingModeConfiguration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ExtendedOperatingModeConfiguration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// GPSL (GPSL)
            uint32_t giant_packet_size_limit                   : 14;    // bits 0:13
            /// (reserved)
            uint32_t                                           : 2;    // bits 14:15
            /// DCRCC (DCRCC)
            uint32_t disable_crc_checking_for_received_packets : 1;    // bit 16
            /// SPEN (SPEN)
            uint32_t slow_protocol_detection_enable            : 1;    // bit 17
            /// USP (USP)
            uint32_t unicast_slow_protocol_packet_detect       : 1;    // bit 18
            /// (reserved)
            uint32_t                                           : 5;    // bits 19:23
            /// EIPGEN (EIPGEN)
            uint32_t extended_inter_packet_gap_enable          : 1;    // bit 24
            /// EIPG (EIPG)
            uint32_t extended_inter_packet_gap_bit_times       : 5;    // bits 25:29
            /// (reserved)
            uint32_t                                           : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ExtendedOperatingModeConfiguration& operator=(ExtendedOperatingModeConfiguration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ExtendedOperatingModeConfiguration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ExtendedOperatingModeConfiguration const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ExtendedOperatingModeConfiguration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ExtendedOperatingModeConfiguration) == 4UL, "Must be this exact size");
    /// Packet filtering control register (MACPFR)
    struct PacketFilterControl final {
        /// Default Constructor
        PacketFilterControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PacketFilterControl(PacketFilterControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PacketFilterControl(PacketFilterControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PacketFilterControl(PacketFilterControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PacketFilterControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PacketFilterControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PacketFilterControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PR (PR)
            uint32_t pending                               : 1;    // bit 0
            /// HUC (HUC)
            uint32_t hash_unicast                          : 1;    // bit 1
            /// HMC (HMC)
            uint32_t hash_multicast                        : 1;    // bit 2
            /// DAIF (DAIF)
            uint32_t destination_address_inverse_filtering : 1;    // bit 3
            /// PM (PM)
            uint32_t promiscuous_mode                      : 1;    // bit 4
            /// DBF (DBF)
            uint32_t disable_broadcast_filter              : 1;    // bit 5
            /// PCF (PCF)
            uint32_t pass_control_frames                   : 2;    // bits 6:7
            /// SAIF (SAIF)
            uint32_t source_address_inverse_filter         : 1;    // bit 8
            /// SAF (SAF)
            uint32_t source_address_filter                 : 1;    // bit 9
            /// HPF (HPF)
            uint32_t hash_or_perfect_filter                : 1;    // bit 10
            /// (reserved)
            uint32_t                                       : 5;    // bits 11:15
            /// VTFE (VTFE)
            uint32_t vlan_tag_filter_enable                : 1;    // bit 16
            /// (reserved)
            uint32_t                                       : 3;    // bits 17:19
            /// IPFE (IPFE)
            uint32_t inverse_pass_filter_enable            : 1;    // bit 20
            /// DNTU (DNTU)
            uint32_t drop_non_ip_packets                   : 1;    // bit 21
            /// (reserved)
            uint32_t                                       : 9;    // bits 22:30
            /// RA (RA)
            uint32_t receive_all                           : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PacketFilterControl& operator=(PacketFilterControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PacketFilterControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PacketFilterControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PacketFilterControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PacketFilterControl) == 4UL, "Must be this exact size");
    /// Watchdog timeout register (MACWTR)
    struct WatchdogTimeout final {
        /// Default Constructor
        WatchdogTimeout()
            : whole{0u} {}
        /// Copy Constructor from volatile
        WatchdogTimeout(WatchdogTimeout volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        WatchdogTimeout(WatchdogTimeout const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        WatchdogTimeout(WatchdogTimeout&&) = delete;
        /// Parameterized Constructor for constant references
        explicit WatchdogTimeout(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit WatchdogTimeout(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~WatchdogTimeout() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// WTO (WTO)
            uint32_t watchdog_timeout             : 4;    // bits 0:3
            /// (reserved)
            uint32_t                              : 4;    // bits 4:7
            /// PWE (PWE)
            uint32_t programmable_watchdog_enable : 1;    // bit 8
            /// (reserved)
            uint32_t                              : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        WatchdogTimeout& operator=(WatchdogTimeout&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(WatchdogTimeout volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(WatchdogTimeout const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<WatchdogTimeout>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(WatchdogTimeout) == 4UL, "Must be this exact size");
    /// Hash Table 0 register (MACHT0R)
    struct HashTable0 final {
        /// Default Constructor
        HashTable0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HashTable0(HashTable0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HashTable0(HashTable0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HashTable0(HashTable0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HashTable0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HashTable0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HashTable0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// HT31T0 (HT31T0)
            uint32_t hash_table_btm : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HashTable0& operator=(HashTable0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HashTable0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HashTable0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HashTable0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HashTable0) == 4UL, "Must be this exact size");
    /// Hash Table 1 register (MACHT1R)
    struct HashTable1 final {
        /// Default Constructor
        HashTable1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HashTable1(HashTable1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HashTable1(HashTable1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HashTable1(HashTable1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HashTable1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HashTable1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HashTable1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// HT63T32 (HT63T32)
            uint32_t hash_table_top : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HashTable1& operator=(HashTable1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HashTable1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HashTable1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HashTable1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HashTable1) == 4UL, "Must be this exact size");
    /// VLAN tag register (MACVTR)
    struct VlanTag final {
        /// Default Constructor
        VlanTag()
            : whole{0u} {}
        /// Copy Constructor from volatile
        VlanTag(VlanTag volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        VlanTag(VlanTag const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        VlanTag(VlanTag&&) = delete;
        /// Parameterized Constructor for constant references
        explicit VlanTag(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit VlanTag(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~VlanTag() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// VL (VL)
            uint32_t vlan_tag_identifier                     : 16;    // bits 0:15
            /// ETV (ETV)
            uint32_t enable_12bit_vlan_tag_comparison        : 1;    // bit 16
            /// VTIM (VTIM)
            uint32_t vlan_tag_inverse_match                  : 1;    // bit 17
            /// ESVL (ESVL)
            uint32_t enable_svlan                            : 1;    // bit 18
            /// ERSVLM (ERSVLM)
            uint32_t enable_receive_svlan_match              : 1;    // bit 19
            /// DOVLTC (DOVLTC)
            uint32_t disable_vlan_type_check                 : 1;    // bit 20
            /// EVLS (EVLS)
            uint32_t enable_vlan_stripping_on_receive        : 2;    // bits 21:22
            /// (reserved)
            uint32_t                                         : 1;    // bit 23
            /// EVLRXS (EVLRXS)
            uint32_t enable_vlan_tag_in_receive_status       : 1;    // bit 24
            /// VTHM (VTHM)
            uint32_t vlan_tag_hash_match                     : 1;    // bit 25
            /// EDVLP (EDVLP)
            uint32_t enable_double_vlan_processing           : 1;    // bit 26
            /// ERIVLT (ERIVLT)
            uint32_t enable_inner_vlan_tag                   : 1;    // bit 27
            /// EIVLS (EIVLS)
            uint32_t enable_inner_vlan_stripping_on_receive  : 2;    // bits 28:29
            /// (reserved)
            uint32_t                                         : 1;    // bit 30
            /// EIVLRXS (EIVLRXS)
            uint32_t enable_inner_vlan_tag_in_receive_status : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        VlanTag& operator=(VlanTag&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(VlanTag volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(VlanTag const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<VlanTag>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(VlanTag) == 4UL, "Must be this exact size");
    /// VLAN Hash table register (MACVHTR)
    struct VlanHashTable final {
        /// Default Constructor
        VlanHashTable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        VlanHashTable(VlanHashTable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        VlanHashTable(VlanHashTable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        VlanHashTable(VlanHashTable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit VlanHashTable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit VlanHashTable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~VlanHashTable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// VLHT (VLHT)
            uint32_t vlan_hash_table : 16;    // bits 0:15
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
        VlanHashTable& operator=(VlanHashTable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(VlanHashTable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(VlanHashTable const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<VlanHashTable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(VlanHashTable) == 4UL, "Must be this exact size");
    /// VLAN inclusion register (MACVIR)
    struct VlanInclusion final {
        /// Default Constructor
        VlanInclusion()
            : whole{0u} {}
        /// Copy Constructor from volatile
        VlanInclusion(VlanInclusion volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        VlanInclusion(VlanInclusion const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        VlanInclusion(VlanInclusion&&) = delete;
        /// Parameterized Constructor for constant references
        explicit VlanInclusion(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit VlanInclusion(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~VlanInclusion() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// VLT (VLT)
            uint32_t vlan_tag            : 16;    // bits 0:15
            /// VLC (VLC)
            uint32_t vlan_tag_comparison : 2;    // bits 16:17
            /// VLP (VLP)
            uint32_t vlan_priority       : 1;    // bit 18
            /// CSVL (CSVL)
            uint32_t c_or_s_vlan         : 1;    // bit 19
            /// VLTI (VLTI)
            uint32_t vlan_tag_input      : 1;    // bit 20
            /// (reserved)
            uint32_t                     : 11;    // bits 21:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        VlanInclusion& operator=(VlanInclusion&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(VlanInclusion volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(VlanInclusion const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<VlanInclusion>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(VlanInclusion) == 4UL, "Must be this exact size");
    /// Inner VLAN inclusion register (MACIVIR)
    struct InnerVlanInclusion final {
        /// Default Constructor
        InnerVlanInclusion()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InnerVlanInclusion(InnerVlanInclusion volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InnerVlanInclusion(InnerVlanInclusion const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InnerVlanInclusion(InnerVlanInclusion&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InnerVlanInclusion(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InnerVlanInclusion(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InnerVlanInclusion() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// VLT (VLT)
            uint32_t vlan_tag            : 16;    // bits 0:15
            /// VLC (VLC)
            uint32_t vlan_tag_comparison : 2;    // bits 16:17
            /// VLP (VLP)
            uint32_t vlan_priority       : 1;    // bit 18
            /// CSVL (CSVL)
            uint32_t c_or_s_vlan         : 1;    // bit 19
            /// VLTI (VLTI)
            uint32_t vlan_tag_input      : 1;    // bit 20
            /// (reserved)
            uint32_t                     : 11;    // bits 21:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InnerVlanInclusion& operator=(InnerVlanInclusion&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InnerVlanInclusion volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InnerVlanInclusion const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InnerVlanInclusion>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InnerVlanInclusion) == 4UL, "Must be this exact size");
    /// Tx Queue flow control register (MACQTxFCR)
    struct QueueTransmitFlowControl final {
        /// Default Constructor
        QueueTransmitFlowControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        QueueTransmitFlowControl(QueueTransmitFlowControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        QueueTransmitFlowControl(QueueTransmitFlowControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        QueueTransmitFlowControl(QueueTransmitFlowControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit QueueTransmitFlowControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit QueueTransmitFlowControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~QueueTransmitFlowControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// FCB_BPA (FCB_BPA)
            uint32_t flow_control_busy_or_backpressure_activate : 1;    // bit 0
            /// TFE (TFE)
            uint32_t transmit_flow_control_enable               : 1;    // bit 1
            /// (reserved)
            uint32_t                                            : 2;    // bits 2:3
            /// PLT (PLT)
            uint32_t pause_low_threshold                        : 3;    // bits 4:6
            /// DZPQ (DZPQ)
            uint32_t disable_zero_quanta_pause                  : 1;    // bit 7
            /// (reserved)
            uint32_t                                            : 8;    // bits 8:15
            /// PT (PT)
            uint32_t pause_time                                 : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        QueueTransmitFlowControl& operator=(QueueTransmitFlowControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(QueueTransmitFlowControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(QueueTransmitFlowControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<QueueTransmitFlowControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(QueueTransmitFlowControl) == 4UL, "Must be this exact size");
    /// Rx flow control register (MACRxFCR)
    struct ReceiveFlowControl final {
        /// Default Constructor
        ReceiveFlowControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveFlowControl(ReceiveFlowControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveFlowControl(ReceiveFlowControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveFlowControl(ReceiveFlowControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveFlowControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveFlowControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveFlowControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RFE (RFE)
            uint32_t receive_flow_control_enable : 1;    // bit 0
            /// UP (UP)
            uint32_t unicast_pause_packet_detect : 1;    // bit 1
            /// (reserved)
            uint32_t                             : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveFlowControl& operator=(ReceiveFlowControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveFlowControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveFlowControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveFlowControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveFlowControl) == 4UL, "Must be this exact size");
    /// Interrupt status register (MACISR)
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
            /// (reserved)
            uint32_t                                                     : 3;    // bits 0:2
            /// PHYIS (PHYIS)
            uint32_t physical_layer_interrupt_status                     : 1;    // bit 3
            /// PMTIS (PMTIS)
            uint32_t power_management_interrupt_status                   : 1;    // bit 4
            /// LPIIS (LPIIS)
            uint32_t low_power_idle_interrupt_status                     : 1;    // bit 5
            /// (reserved)
            uint32_t                                                     : 2;    // bits 6:7
            /// MMCIS (MMCIS)
            uint32_t media_management_counters_interrupt_status          : 1;    // bit 8
            /// MMCRXIS (MMCRXIS)
            uint32_t media_management_counters_receive_interrupt_status  : 1;    // bit 9
            /// MMCTXIS (MMCTXIS)
            uint32_t media_management_counters_transmit_interrupt_status : 1;    // bit 10
            /// (reserved)
            uint32_t                                                     : 1;    // bit 11
            /// TSIS (TSIS)
            uint32_t timestamp_interrupt_status                          : 1;    // bit 12
            /// TXSTSIS (TXSTSIS)
            uint32_t transmit_status_interrupt_status                    : 1;    // bit 13
            /// RXSTSIS (RXSTSIS)
            uint32_t receive_status_interrupt_status                     : 1;    // bit 14
            /// (reserved)
            uint32_t                                                     : 17;    // bits 15:31
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
    /// Interrupt enable register (MACIER)
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
            /// (reserved)
            uint32_t                                   : 3;    // bits 0:2
            /// PHYIE (PHYIE)
            uint32_t physical_layer_interrupt_enable   : 1;    // bit 3
            /// PMTIE (PMTIE)
            uint32_t power_management_interrupt_enable : 1;    // bit 4
            /// LPIIE (LPIIE)
            uint32_t low_power_idle_interrupt_enable   : 1;    // bit 5
            /// (reserved)
            uint32_t                                   : 6;    // bits 6:11
            /// TSIE (TSIE)
            uint32_t timestamp_interrupt_enable        : 1;    // bit 12
            /// TXSTSIE (TXSTSIE)
            uint32_t transmit_status_interrupt_enable  : 1;    // bit 13
            /// RXSTSIE (RXSTSIE)
            uint32_t receive_status_interrupt_enable   : 1;    // bit 14
            /// (reserved)
            uint32_t                                   : 17;    // bits 15:31
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
    /// Rx Tx status register (MACRxTxSR)
    struct ReceiveTransmitStatus final {
        /// Default Constructor
        ReceiveTransmitStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveTransmitStatus(ReceiveTransmitStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveTransmitStatus(ReceiveTransmitStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveTransmitStatus(ReceiveTransmitStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveTransmitStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveTransmitStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveTransmitStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TJT (TJT)
            uint32_t transmit_jabber_timeout         : 1;    // bit 0
            /// NCARR (NCARR)
            uint32_t no_carrier                      : 1;    // bit 1
            /// LCARR (LCARR)
            uint32_t loss_of_carrier                 : 1;    // bit 2
            /// EXDEF (EXDEF)
            uint32_t excessive_deferral              : 1;    // bit 3
            /// LCOL (LCOL)
            uint32_t late_collisions                 : 1;    // bit 4
            /// LCOL (EXCOL)
            uint32_t excessive_collisions            : 1;    // bit 5
            /// (reserved)
            uint32_t                                 : 2;    // bits 6:7
            /// RWT (RWT)
            uint32_t receive_watchdog_timeout_status : 1;    // bit 8
            /// (reserved)
            uint32_t                                 : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveTransmitStatus& operator=(ReceiveTransmitStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveTransmitStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveTransmitStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveTransmitStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveTransmitStatus) == 4UL, "Must be this exact size");
    /// PMT control status register (MACPCSR)
    struct PowerManagementControlStatus final {
        /// Default Constructor
        PowerManagementControlStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PowerManagementControlStatus(PowerManagementControlStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PowerManagementControlStatus(PowerManagementControlStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PowerManagementControlStatus(PowerManagementControlStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PowerManagementControlStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PowerManagementControlStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PowerManagementControlStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PWRDWN (PWRDWN)
            uint32_t power_down                             : 1;    // bit 0
            /// MGKPKTEN (MGKPKTEN)
            uint32_t magic_packet_enable                    : 1;    // bit 1
            /// RWKPKTEN (RWKPKTEN)
            uint32_t remote_wakeup_packet_enable            : 1;    // bit 2
            /// (reserved)
            uint32_t                                        : 2;    // bits 3:4
            /// MGKPRCVD (MGKPRCVD)
            uint32_t magic_packet_received                  : 1;    // bit 5
            /// RWKPRCVD (RWKPRCVD)
            uint32_t remote_wakeup_packet_received          : 1;    // bit 6
            /// (reserved)
            uint32_t                                        : 2;    // bits 7:8
            /// GLBLUCAST (GLBLUCAST)
            uint32_t global_unicast                         : 1;    // bit 9
            /// RWKPFE (RWKPFE)
            uint32_t remote_wakeup_packet_forwarding_enable : 1;    // bit 10
            /// (reserved)
            uint32_t                                        : 13;    // bits 11:23
            /// RWKPTR (RWKPTR)
            uint32_t remote_wakeup_fifo_pointer             : 5;    // bits 24:28
            /// (reserved)
            uint32_t                                        : 2;    // bits 29:30
            /// RWKFILTRST (RWKFILTRST)
            uint32_t remote_wakeup_packet_filter_reset      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PowerManagementControlStatus& operator=(PowerManagementControlStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PowerManagementControlStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PowerManagementControlStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PowerManagementControlStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PowerManagementControlStatus) == 4UL, "Must be this exact size");
    /// Remove wakeup packet filter register (MACRWKPFR)
    struct RemoteWakeupPacketFilter final {
        /// Default Constructor
        RemoteWakeupPacketFilter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        RemoteWakeupPacketFilter(RemoteWakeupPacketFilter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        RemoteWakeupPacketFilter(RemoteWakeupPacketFilter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        RemoteWakeupPacketFilter(RemoteWakeupPacketFilter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit RemoteWakeupPacketFilter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit RemoteWakeupPacketFilter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~RemoteWakeupPacketFilter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// MACRWKPFR (MACRWKPFR)
            uint32_t remote_wakeup_packet_filter : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        RemoteWakeupPacketFilter& operator=(RemoteWakeupPacketFilter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(RemoteWakeupPacketFilter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(RemoteWakeupPacketFilter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<RemoteWakeupPacketFilter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(RemoteWakeupPacketFilter) == 4UL, "Must be this exact size");
    /// LPI control status register (MACLCSR)
    struct LowPowerIdleControlStatus final {
        /// Default Constructor
        LowPowerIdleControlStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowPowerIdleControlStatus(LowPowerIdleControlStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowPowerIdleControlStatus(LowPowerIdleControlStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowPowerIdleControlStatus(LowPowerIdleControlStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowPowerIdleControlStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowPowerIdleControlStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowPowerIdleControlStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TLPIEN (TLPIEN)
            uint32_t transmit_low_power_idle_enable   : 1;    // bit 0
            /// TLPIEX (TLPIEX)
            uint32_t transmit_low_power_idle_exit     : 1;    // bit 1
            /// RLPIEN (RLPIEN)
            uint32_t receive_low_power_idle_enable    : 1;    // bit 2
            /// RLPIEX (RLPIEX)
            uint32_t receive_low_power_idle_exit      : 1;    // bit 3
            /// (reserved)
            uint32_t                                  : 4;    // bits 4:7
            /// TLPIST (TLPIST)
            uint32_t transmit_low_power_idle_status   : 1;    // bit 8
            /// RLPIST (RLPIST)
            uint32_t receive_low_power_idle_status    : 1;    // bit 9
            /// (reserved)
            uint32_t                                  : 6;    // bits 10:15
            /// LPIEN (LPIEN)
            uint32_t low_power_idle_enable            : 1;    // bit 16
            /// PLS (PLS)
            uint32_t pvd_level_select                 : 1;    // bit 17
            /// PLSEN (PLSEN)
            uint32_t physical_layer_status_enable     : 1;    // bit 18
            /// LPITXA (LPITXA)
            uint32_t low_power_idle_transmit_automate : 1;    // bit 19
            /// LPITE (LPITE)
            uint32_t low_power_idle_timer_enable      : 1;    // bit 20
            /// (reserved)
            uint32_t                                  : 11;    // bits 21:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowPowerIdleControlStatus& operator=(LowPowerIdleControlStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleControlStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleControlStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LowPowerIdleControlStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowPowerIdleControlStatus) == 4UL, "Must be this exact size");
    /// LPI timers control register (MACLTCR)
    struct LowPowerIdleTimersControl final {
        /// Default Constructor
        LowPowerIdleTimersControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowPowerIdleTimersControl(LowPowerIdleTimersControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowPowerIdleTimersControl(LowPowerIdleTimersControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowPowerIdleTimersControl(LowPowerIdleTimersControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowPowerIdleTimersControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowPowerIdleTimersControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowPowerIdleTimersControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TWT (TWT)
            uint32_t low_power_idle_transmit_wait_timer : 16;    // bits 0:15
            /// LST (LST)
            uint32_t low_power_idle_lsi_timer           : 10;    // bits 16:25
            /// (reserved)
            uint32_t                                    : 6;    // bits 26:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowPowerIdleTimersControl& operator=(LowPowerIdleTimersControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleTimersControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleTimersControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LowPowerIdleTimersControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowPowerIdleTimersControl) == 4UL, "Must be this exact size");
    /// LPI entry timer register (MACLETR)
    struct LowPowerIdleEntryTimer final {
        /// Default Constructor
        LowPowerIdleEntryTimer()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowPowerIdleEntryTimer(LowPowerIdleEntryTimer volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowPowerIdleEntryTimer(LowPowerIdleEntryTimer const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowPowerIdleEntryTimer(LowPowerIdleEntryTimer&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowPowerIdleEntryTimer(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowPowerIdleEntryTimer(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowPowerIdleEntryTimer() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LPIET (LPIET)
            uint32_t low_power_idle_entry_timer : 17;    // bits 0:16
            /// (reserved)
            uint32_t                            : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowPowerIdleEntryTimer& operator=(LowPowerIdleEntryTimer&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleEntryTimer volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowPowerIdleEntryTimer const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LowPowerIdleEntryTimer>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowPowerIdleEntryTimer) == 4UL, "Must be this exact size");
    /// 1-microsecond-tick counter register (MAC1USTCR)
    struct OneMicrosecondTickCounter final {
        /// Default Constructor
        OneMicrosecondTickCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OneMicrosecondTickCounter(OneMicrosecondTickCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OneMicrosecondTickCounter(OneMicrosecondTickCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OneMicrosecondTickCounter(OneMicrosecondTickCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OneMicrosecondTickCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OneMicrosecondTickCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OneMicrosecondTickCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TIC_1US_CNTR (TIC_1US_CNTR)
            uint32_t tic_1us_counter : 12;    // bits 0:11
            /// (reserved)
            uint32_t                 : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OneMicrosecondTickCounter& operator=(OneMicrosecondTickCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OneMicrosecondTickCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OneMicrosecondTickCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OneMicrosecondTickCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OneMicrosecondTickCounter) == 4UL, "Must be this exact size");
    /// Version register (MACVR)
    struct Version final {
        /// Default Constructor
        Version()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Version(Version volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Version(Version const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Version(Version&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Version(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Version(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Version() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SNPSVER (SNPSVER)
            uint32_t synopsys_version : 8;    // bits 0:7
            /// USERVER (USERVER)
            uint32_t user_version     : 8;    // bits 8:15
            /// (reserved)
            uint32_t                  : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Version& operator=(Version&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Version volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Version const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Version>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Version) == 4UL, "Must be this exact size");
    /// Debug register (MACDR)
    struct Debug final {
        /// Default Constructor
        Debug()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Debug(Debug volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Debug(Debug const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Debug(Debug&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Debug(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Debug(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Debug() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RPESTS (RPESTS)
            uint32_t receive_protocol_engine_status  : 1;    // bit 0
            /// RFCFCSTS (RFCFCSTS)
            uint32_t receive_flow_control_status     : 2;    // bits 1:2
            /// (reserved)
            uint32_t                                 : 13;    // bits 3:15
            /// TPESTS (TPESTS)
            uint32_t transmit_protocol_engine_status : 1;    // bit 16
            /// TFCSTS (TFCSTS)
            uint32_t transmit_flow_control_status    : 2;    // bits 17:18
            /// (reserved)
            uint32_t                                 : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Debug& operator=(Debug&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Debug volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Debug const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Debug>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Debug) == 4UL, "Must be this exact size");
    /// HW feature 1 register (MACHWF1R)
    struct HardwareFeature1 final {
        /// Default Constructor
        HardwareFeature1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HardwareFeature1(HardwareFeature1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HardwareFeature1(HardwareFeature1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HardwareFeature1(HardwareFeature1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HardwareFeature1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HardwareFeature1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HardwareFeature1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXFIFOSIZE (RXFIFOSIZE)
            uint32_t receive_fifo_size                      : 5;    // bits 0:4
            /// (reserved)
            uint32_t                                        : 1;    // bit 5
            /// TXFIFOSIZE (TXFIFOSIZE)
            uint32_t transmit_fifo_size                     : 5;    // bits 6:10
            /// OSTEN (OSTEN)
            uint32_t one_step_timestamp_enable              : 1;    // bit 11
            /// PTOEN (PTOEN)
            uint32_t precision_time_protocol_offload_enable : 1;    // bit 12
            /// ADVTHWORD (ADVTHWORD)
            uint32_t iee1588_high_word_enable               : 1;    // bit 13
            /// ADDR64 (ADDR64)
            uint32_t address_width                          : 2;    // bits 14:15
            /// DCBEN (DCBEN)
            uint32_t data_center_bridging_enable            : 1;    // bit 16
            /// SPHEN (SPHEN)
            uint32_t split_header_enable                    : 1;    // bit 17
            /// TSOEN (TSOEN)
            uint32_t tcp_segmentation_offload_enable        : 1;    // bit 18
            /// DBGMEMA (DBGMEMA)
            uint32_t dma_debug_registers_enable             : 1;    // bit 19
            /// AVSEL (AVSEL)
            uint32_t audio_video_bridge_selected            : 1;    // bit 20
            /// (reserved)
            uint32_t                                        : 3;    // bits 21:23
            /// HASHTBLSZ (HASHTBLSZ)
            uint32_t hash_table_size                        : 2;    // bits 24:25
            /// (reserved)
            uint32_t                                        : 1;    // bit 26
            /// L3L4FNUM (L3L4FNUM)
            uint32_t layer3_layer4_filter_number            : 4;    // bits 27:30
            /// (reserved)
            uint32_t                                        : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HardwareFeature1& operator=(HardwareFeature1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HardwareFeature1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HardwareFeature1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HardwareFeature1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HardwareFeature1) == 4UL, "Must be this exact size");
    /// HW feature 2 register (MACHWF2R)
    struct HardwareFeature2 final {
        /// Default Constructor
        HardwareFeature2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HardwareFeature2(HardwareFeature2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HardwareFeature2(HardwareFeature2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HardwareFeature2(HardwareFeature2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HardwareFeature2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HardwareFeature2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HardwareFeature2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXQCNT (RXQCNT)
            uint32_t receive_queue_count            : 4;    // bits 0:3
            /// (reserved)
            uint32_t                                : 2;    // bits 4:5
            /// TXQCNT (TXQCNT)
            uint32_t transmit_queue_count           : 4;    // bits 6:9
            /// (reserved)
            uint32_t                                : 2;    // bits 10:11
            /// RXCHCNT (RXCHCNT)
            uint32_t receive_channel_count          : 4;    // bits 12:15
            /// (reserved)
            uint32_t                                : 2;    // bits 16:17
            /// TXCHCNT (TXCHCNT)
            uint32_t transmit_channel_count         : 4;    // bits 18:21
            /// (reserved)
            uint32_t                                : 2;    // bits 22:23
            /// PPSOUTNUM (PPSOUTNUM)
            uint32_t pulse_per_second_output_number : 3;    // bits 24:26
            /// (reserved)
            uint32_t                                : 1;    // bit 27
            /// AUXSNAPNUM (AUXSNAPNUM)
            uint32_t aux_snapshot_inputs            : 3;    // bits 28:30
            /// (reserved)
            uint32_t                                : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HardwareFeature2& operator=(HardwareFeature2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HardwareFeature2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HardwareFeature2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HardwareFeature2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HardwareFeature2) == 4UL, "Must be this exact size");
    /// MDIO address register (MACMDIOAR)
    struct MdioAddress final {
        /// Default Constructor
        MdioAddress()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MdioAddress(MdioAddress volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MdioAddress(MdioAddress const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MdioAddress(MdioAddress&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MdioAddress(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MdioAddress(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MdioAddress() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// MB (MB)
            uint32_t management_busy             : 1;    // bit 0
            /// C45E (C45E)
            uint32_t clause45_phy_enable         : 1;    // bit 1
            /// GOC (GOC)
            uint32_t mdio_operation_command      : 2;    // bits 2:3
            /// SKAP (SKAP)
            uint32_t skip_address_packet         : 1;    // bit 4
            /// (reserved)
            uint32_t                             : 3;    // bits 5:7
            /// CR (CR)
            uint32_t control                     : 4;    // bits 8:11
            /// NTC (NTC)
            uint32_t number_of_trailing_clocks   : 3;    // bits 12:14
            /// (reserved)
            uint32_t                             : 1;    // bit 15
            /// RDA (RDA)
            uint32_t register_device_address     : 5;    // bits 16:20
            /// PA (PA)
            uint32_t physical_address            : 5;    // bits 21:25
            /// BTB (BTB)
            uint32_t back_to_back                : 1;    // bit 26
            /// PSE (PSE)
            uint32_t preamble_suppression_enable : 1;    // bit 27
            /// (reserved)
            uint32_t                             : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MdioAddress& operator=(MdioAddress&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MdioAddress volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MdioAddress const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MdioAddress>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MdioAddress) == 4UL, "Must be this exact size");
    /// MDIO data register (MACMDIODR)
    struct MdioData final {
        /// Default Constructor
        MdioData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MdioData(MdioData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MdioData(MdioData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MdioData(MdioData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MdioData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MdioData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MdioData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// MD (MD)
            uint32_t mdio_data        : 16;    // bits 0:15
            /// RA (RA)
            uint32_t register_address : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MdioData& operator=(MdioData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MdioData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MdioData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MdioData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MdioData) == 4UL, "Must be this exact size");
    /// ARP address register (MACARPAR)
    struct ArpAddress final {
        /// Default Constructor
        ArpAddress()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ArpAddress(ArpAddress volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ArpAddress(ArpAddress const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ArpAddress(ArpAddress&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ArpAddress(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ArpAddress(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ArpAddress() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ARPPA (ARPPA)
            uint32_t arp_ipv4_addres : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ArpAddress& operator=(ArpAddress&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ArpAddress volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ArpAddress const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ArpAddress>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ArpAddress) == 4UL, "Must be this exact size");
    /// Address 0 high register (MACA0HR)
    struct Address0High final {
        /// Default Constructor
        Address0High()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address0High(Address0High volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address0High(Address0High const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address0High(Address0High&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address0High(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address0High(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address0High() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRHI (ADDRHI)
            uint32_t address_high   : 16;    // bits 0:15
            /// (reserved)
            uint32_t                : 15;    // bits 16:30
            /// AE (AE)
            uint32_t address_enable : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address0High& operator=(Address0High&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address0High volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address0High const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address0High>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address0High) == 4UL, "Must be this exact size");
    /// Address 0 low register (MACA0LR)
    struct Address0Low final {
        /// Default Constructor
        Address0Low()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address0Low(Address0Low volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address0Low(Address0Low const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address0Low(Address0Low&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address0Low(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address0Low(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address0Low() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRLO (ADDRLO)
            uint32_t address_low : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address0Low& operator=(Address0Low&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address0Low volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address0Low const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address0Low>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address0Low) == 4UL, "Must be this exact size");
    /// Address 1 low register (MACA1LR)
    struct Address1Low final {
        /// Default Constructor
        Address1Low()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address1Low(Address1Low volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address1Low(Address1Low const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address1Low(Address1Low&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address1Low(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address1Low(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address1Low() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRLO (ADDRLO)
            uint32_t address_low : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address1Low& operator=(Address1Low&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address1Low volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address1Low const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address1Low>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address1Low) == 4UL, "Must be this exact size");
    /// Address 2 low register (MACA2LR)
    struct Address2Low final {
        /// Default Constructor
        Address2Low()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address2Low(Address2Low volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address2Low(Address2Low const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address2Low(Address2Low&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address2Low(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address2Low(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address2Low() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRLO (ADDRLO)
            uint32_t address_low : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address2Low& operator=(Address2Low&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address2Low volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address2Low const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address2Low>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address2Low) == 4UL, "Must be this exact size");
    /// Address 1 high register (MACA1HR)
    struct Address1High final {
        /// Default Constructor
        Address1High()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address1High(Address1High volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address1High(Address1High const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address1High(Address1High&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address1High(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address1High(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address1High() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRHI (ADDRHI)
            uint32_t address_high      : 16;    // bits 0:15
            /// (reserved)
            uint32_t                   : 8;    // bits 16:23
            /// MBC (MBC)
            uint32_t mask_byte_control : 6;    // bits 24:29
            /// SA (SA)
            uint32_t source_address    : 1;    // bit 30
            /// AE (AE)
            uint32_t address_enable    : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address1High& operator=(Address1High&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address1High volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address1High const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address1High>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address1High) == 4UL, "Must be this exact size");
    /// Address 2 high register (MACA2HR)
    struct Address2High final {
        /// Default Constructor
        Address2High()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address2High(Address2High volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address2High(Address2High const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address2High(Address2High&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address2High(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address2High(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address2High() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRHI (ADDRHI)
            uint32_t address_high      : 16;    // bits 0:15
            /// (reserved)
            uint32_t                   : 8;    // bits 16:23
            /// MBC (MBC)
            uint32_t mask_byte_control : 6;    // bits 24:29
            /// SA (SA)
            uint32_t source_address    : 1;    // bit 30
            /// AE (AE)
            uint32_t address_enable    : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address2High& operator=(Address2High&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address2High volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address2High const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address2High>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address2High) == 4UL, "Must be this exact size");
    /// Address 3 high register (MACA3HR)
    struct Address3High final {
        /// Default Constructor
        Address3High()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address3High(Address3High volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address3High(Address3High const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address3High(Address3High&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address3High(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address3High(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address3High() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRHI (ADDRHI)
            uint32_t address_high      : 16;    // bits 0:15
            /// (reserved)
            uint32_t                   : 8;    // bits 16:23
            /// MBC (MBC)
            uint32_t mask_byte_control : 6;    // bits 24:29
            /// SA (SA)
            uint32_t source_address    : 1;    // bit 30
            /// AE (AE)
            uint32_t address_enable    : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address3High& operator=(Address3High&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address3High volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address3High const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address3High>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address3High) == 4UL, "Must be this exact size");
    /// Address 3 low register (MACA3LR)
    struct Address3Low final {
        /// Default Constructor
        Address3Low()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Address3Low(Address3Low volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Address3Low(Address3Low const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Address3Low(Address3Low&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Address3Low(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Address3Low(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Address3Low() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ADDRLO (ADDRLO)
            uint32_t address_low : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Address3Low& operator=(Address3Low&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Address3Low volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Address3Low const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Address3Low>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Address3Low) == 4UL, "Must be this exact size");
    /// MMC control register (MMC_CONTROL)
    struct MMCControl final {
        /// Default Constructor
        MMCControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MMCControl(MMCControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MMCControl(MMCControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MMCControl(MMCControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MMCControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MMCControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MMCControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CNTRST (CNTRST)
            uint32_t counters_reset                         : 1;    // bit 0
            /// CNTSTOPRO (CNTSTOPRO)
            uint32_t counter_stop_rollover                  : 1;    // bit 1
            /// RSTONRD (RSTONRD)
            uint32_t reset_on_read                          : 1;    // bit 2
            /// CNTFREEZ (CNTFREEZ)
            uint32_t counter_freeze                         : 1;    // bit 3
            /// CNTPRST (CNTPRST)
            uint32_t counter_preset                         : 1;    // bit 4
            /// CNTPRSTLVL (CNTPRSTLVL)
            uint32_t counter_preset_level                   : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 2;    // bits 6:7
            /// UCDBC (UCDBC)
            uint32_t update_counters_for_dropped_broadcasts : 1;    // bit 8
            /// (reserved)
            uint32_t                                        : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MMCControl& operator=(MMCControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MMCControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MMCControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MMCControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MMCControl) == 4UL, "Must be this exact size");
    /// MMC Rx interrupt register (MMC_RX_INTERRUPT)
    struct MMCReceiveInterrupt final {
        /// Default Constructor
        MMCReceiveInterrupt()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MMCReceiveInterrupt(MMCReceiveInterrupt volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MMCReceiveInterrupt(MMCReceiveInterrupt const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MMCReceiveInterrupt(MMCReceiveInterrupt&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MMCReceiveInterrupt(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MMCReceiveInterrupt(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MMCReceiveInterrupt() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                                             : 5;    // bits 0:4
            /// RXCRCERPIS (RXCRCERPIS)
            uint32_t receive_crc_error_packets_interrupt_status                  : 1;    // bit 5
            /// RXALGNERPIS (RXALGNERPIS)
            uint32_t receive_align_error_packets_interrupt_status                : 1;    // bit 6
            /// (reserved)
            uint32_t                                                             : 10;    // bits 7:16
            /// RXUCGPIS (RXUCGPIS)
            uint32_t receive_unicast_packets_good_counter_interrupts_status      : 1;    // bit 17
            /// (reserved)
            uint32_t                                                             : 8;    // bits 18:25
            /// RXLPIUSCIS (RXLPIUSCIS)
            uint32_t receive_low_power_idle_microsecond_counter_interrupt_status : 1;    // bit 26
            /// RXLPITRCIS (RXLPITRCIS)
            uint32_t receive_low_power_idle_transition_counter_interrupt_status  : 1;    // bit 27
            /// (reserved)
            uint32_t                                                             : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MMCReceiveInterrupt& operator=(MMCReceiveInterrupt&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MMCReceiveInterrupt volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MMCReceiveInterrupt const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MMCReceiveInterrupt>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MMCReceiveInterrupt) == 4UL, "Must be this exact size");
    /// MMC Tx interrupt register (MMC_TX_INTERRUPT)
    struct MMCTransmitInterrupt final {
        /// Default Constructor
        MMCTransmitInterrupt()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MMCTransmitInterrupt(MMCTransmitInterrupt volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MMCTransmitInterrupt(MMCTransmitInterrupt const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MMCTransmitInterrupt(MMCTransmitInterrupt&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MMCTransmitInterrupt(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MMCTransmitInterrupt(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MMCTransmitInterrupt() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                                                  : 14;    // bits 0:13
            /// TXSCOLGPIS (TXSCOLGPIS)
            uint32_t transmit_single_collision_good_packet_counter_interrupt_status   : 1;    // bit 14
            /// TXMCOLGPIS (TXMCOLGPIS)
            uint32_t transmit_multiple_collision_good_packet_counter_interrupt_status : 1;    // bit 15
            /// (reserved)
            uint32_t                                                                  : 5;    // bits 16:20
            /// TXGPKTIS (TXGPKTIS)
            uint32_t transmit_good_packet_counter_interrupt_status                    : 1;    // bit 21
            /// (reserved)
            uint32_t                                                                  : 4;    // bits 22:25
            /// TXLPIUSCIS (TXLPIUSCIS)
            uint32_t transmit_low_power_idle_counter_interrupt_status                 : 1;    // bit 26
            /// TXLPITRCIS (TXLPITRCIS)
            uint32_t transmit_low_power_idle_interrupt_status                         : 1;    // bit 27
            /// (reserved)
            uint32_t                                                                  : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MMCTransmitInterrupt& operator=(MMCTransmitInterrupt&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MMCTransmitInterrupt volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MMCTransmitInterrupt const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MMCTransmitInterrupt>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MMCTransmitInterrupt) == 4UL, "Must be this exact size");
    /// MMC Rx interrupt mask register (MMC_RX_INTERRUPT_MASK)
    struct MMCReceiveInterruptMask final {
        /// Default Constructor
        MMCReceiveInterruptMask()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MMCReceiveInterruptMask(MMCReceiveInterruptMask volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MMCReceiveInterruptMask(MMCReceiveInterruptMask const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MMCReceiveInterruptMask(MMCReceiveInterruptMask&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MMCReceiveInterruptMask(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MMCReceiveInterruptMask(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MMCReceiveInterruptMask() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                                           : 5;    // bits 0:4
            /// RXCRCERPIM (RXCRCERPIM)
            uint32_t receive_crc_error_packets_interrupt_mask                  : 1;    // bit 5
            /// RXALGNERPIM (RXALGNERPIM)
            uint32_t receive_align_error_packets_interrupt_mask                : 1;    // bit 6
            /// (reserved)
            uint32_t                                                           : 10;    // bits 7:16
            /// RXUCGPIM (RXUCGPIM)
            uint32_t receive_unicast_packets_good_interrupt_mask               : 1;    // bit 17
            /// (reserved)
            uint32_t                                                           : 8;    // bits 18:25
            /// RXLPIUSCIM (RXLPIUSCIM)
            uint32_t receive_low_power_idle_microsecond_counter_interrupt_mask : 1;    // bit 26
            /// RXLPITRCIM (RXLPITRCIM)
            uint32_t receive_low_power_idle_transition_counter_interrupt_mask  : 1;    // bit 27
            /// (reserved)
            uint32_t                                                           : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MMCReceiveInterruptMask& operator=(MMCReceiveInterruptMask&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MMCReceiveInterruptMask volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MMCReceiveInterruptMask const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MMCReceiveInterruptMask>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MMCReceiveInterruptMask) == 4UL, "Must be this exact size");
    /// MMC Tx interrupt mask register (MMC_TX_INTERRUPT_MASK)
    struct MMCTransmitInterruptMask final {
        /// Default Constructor
        MMCTransmitInterruptMask()
            : whole{0u} {}
        /// Copy Constructor from volatile
        MMCTransmitInterruptMask(MMCTransmitInterruptMask volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        MMCTransmitInterruptMask(MMCTransmitInterruptMask const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        MMCTransmitInterruptMask(MMCTransmitInterruptMask&&) = delete;
        /// Parameterized Constructor for constant references
        explicit MMCTransmitInterruptMask(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit MMCTransmitInterruptMask(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~MMCTransmitInterruptMask() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                                                : 14;    // bits 0:13
            /// TXSCOLGPIM (TXSCOLGPIM)
            uint32_t transmit_single_collision_good_packet_counter_interrupt_mask   : 1;    // bit 14
            /// TXMCOLGPIM (TXMCOLGPIM)
            uint32_t transmit_multiple_collision_good_packet_counter_interrupt_mask : 1;    // bit 15
            /// (reserved)
            uint32_t                                                                : 5;    // bits 16:20
            /// TXGPKTIM (TXGPKTIM)
            uint32_t transmit_good_packet_counter_interrupt_mask                    : 1;    // bit 21
            /// (reserved)
            uint32_t                                                                : 4;    // bits 22:25
            /// TXLPIUSCIM (TXLPIUSCIM)
            uint32_t transmit_low_power_idle_counter_interrupt_mask                 : 1;    // bit 26
            /// TXLPITRCIM (TXLPITRCIM)
            uint32_t transmit_low_power_idle_interrupt_mask                         : 1;    // bit 27
            /// (reserved)
            uint32_t                                                                : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        MMCTransmitInterruptMask& operator=(MMCTransmitInterruptMask&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(MMCTransmitInterruptMask volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(MMCTransmitInterruptMask const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<MMCTransmitInterruptMask>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(MMCTransmitInterruptMask) == 4UL, "Must be this exact size");
    /// Tx single collision good packets register (TX_SINGLE_COLLISION_GOOD_PACKETS)
    struct TransmitSingleCollisionGoodPackets final {
        /// Default Constructor
        TransmitSingleCollisionGoodPackets()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitSingleCollisionGoodPackets(TransmitSingleCollisionGoodPackets volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitSingleCollisionGoodPackets(TransmitSingleCollisionGoodPackets const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitSingleCollisionGoodPackets(TransmitSingleCollisionGoodPackets&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitSingleCollisionGoodPackets(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitSingleCollisionGoodPackets(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitSingleCollisionGoodPackets() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXSNGLCOLG (TXSNGLCOLG)
            uint32_t transmit_single_collision_good_packets : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitSingleCollisionGoodPackets& operator=(TransmitSingleCollisionGoodPackets&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitSingleCollisionGoodPackets volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitSingleCollisionGoodPackets const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitSingleCollisionGoodPackets>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitSingleCollisionGoodPackets) == 4UL, "Must be this exact size");
    /// Tx multiple collision good packets register (TX_MULTIPLE_COLLISION_GOOD_PACKETS)
    struct TransmitMultipleCollisionGoodPackets final {
        /// Default Constructor
        TransmitMultipleCollisionGoodPackets()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitMultipleCollisionGoodPackets(TransmitMultipleCollisionGoodPackets volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitMultipleCollisionGoodPackets(TransmitMultipleCollisionGoodPackets const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitMultipleCollisionGoodPackets(TransmitMultipleCollisionGoodPackets&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitMultipleCollisionGoodPackets(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitMultipleCollisionGoodPackets(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitMultipleCollisionGoodPackets() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXMULTCOLG (TXMULTCOLG)
            uint32_t transmit_multiple_collision_good_packets : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitMultipleCollisionGoodPackets& operator=(TransmitMultipleCollisionGoodPackets&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitMultipleCollisionGoodPackets volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitMultipleCollisionGoodPackets const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitMultipleCollisionGoodPackets>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitMultipleCollisionGoodPackets) == 4UL, "Must be this exact size");
    /// Tx packet count good register (TX_PACKET_COUNT_GOOD)
    struct TransmitPacketCountGood final {
        /// Default Constructor
        TransmitPacketCountGood()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitPacketCountGood(TransmitPacketCountGood volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitPacketCountGood(TransmitPacketCountGood const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitPacketCountGood(TransmitPacketCountGood&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitPacketCountGood(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitPacketCountGood(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitPacketCountGood() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXPKTG (TXPKTG)
            uint32_t transmit_packet_good_count : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitPacketCountGood& operator=(TransmitPacketCountGood&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitPacketCountGood volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitPacketCountGood const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitPacketCountGood>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitPacketCountGood) == 4UL, "Must be this exact size");
    /// Rx CRC error packets register (RX_CRC_ERROR_PACKETS)
    struct ReceiveCRCErrorPackets final {
        /// Default Constructor
        ReceiveCRCErrorPackets()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveCRCErrorPackets(ReceiveCRCErrorPackets volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveCRCErrorPackets(ReceiveCRCErrorPackets const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveCRCErrorPackets(ReceiveCRCErrorPackets&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveCRCErrorPackets(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveCRCErrorPackets(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveCRCErrorPackets() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXCRCERR (RXCRCERR)
            uint32_t receive_crc_error_packets : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveCRCErrorPackets& operator=(ReceiveCRCErrorPackets&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveCRCErrorPackets volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveCRCErrorPackets const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveCRCErrorPackets>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveCRCErrorPackets) == 4UL, "Must be this exact size");
    /// Rx alignment error packets register (RX_ALIGNMENT_ERROR_PACKETS)
    struct ReceiveAlignmentErrorPackets final {
        /// Default Constructor
        ReceiveAlignmentErrorPackets()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveAlignmentErrorPackets(ReceiveAlignmentErrorPackets volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveAlignmentErrorPackets(ReceiveAlignmentErrorPackets const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveAlignmentErrorPackets(ReceiveAlignmentErrorPackets&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveAlignmentErrorPackets(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveAlignmentErrorPackets(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveAlignmentErrorPackets() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXALGNERR (RXALGNERR)
            uint32_t receive_align_error_packets : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveAlignmentErrorPackets& operator=(ReceiveAlignmentErrorPackets&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveAlignmentErrorPackets volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveAlignmentErrorPackets const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveAlignmentErrorPackets>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveAlignmentErrorPackets) == 4UL, "Must be this exact size");
    /// Rx unicast packets good register (RX_UNICAST_PACKETS_GOOD)
    struct ReceiveUnicastPacketsGood final {
        /// Default Constructor
        ReceiveUnicastPacketsGood()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveUnicastPacketsGood(ReceiveUnicastPacketsGood volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveUnicastPacketsGood(ReceiveUnicastPacketsGood const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveUnicastPacketsGood(ReceiveUnicastPacketsGood&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveUnicastPacketsGood(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveUnicastPacketsGood(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveUnicastPacketsGood() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXUCASTG (RXUCASTG)
            uint32_t receive_unicast_packets_good : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveUnicastPacketsGood& operator=(ReceiveUnicastPacketsGood&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveUnicastPacketsGood volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveUnicastPacketsGood const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveUnicastPacketsGood>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveUnicastPacketsGood) == 4UL, "Must be this exact size");
    /// Tx LPI microsecond timer register (TX_LPI_USEC_CNTR)
    struct TransmitLPIUsecCounter final {
        /// Default Constructor
        TransmitLPIUsecCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitLPIUsecCounter(TransmitLPIUsecCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitLPIUsecCounter(TransmitLPIUsecCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitLPIUsecCounter(TransmitLPIUsecCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitLPIUsecCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitLPIUsecCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitLPIUsecCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXLPIUSC (TXLPIUSC)
            uint32_t transmit_low_power_idle_microseconds_counter : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitLPIUsecCounter& operator=(TransmitLPIUsecCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitLPIUsecCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitLPIUsecCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitLPIUsecCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitLPIUsecCounter) == 4UL, "Must be this exact size");
    /// Tx LPI transition counter register (TX_LPI_TRAN_CNTR)
    struct TransmitLPITranCounter final {
        /// Default Constructor
        TransmitLPITranCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitLPITranCounter(TransmitLPITranCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitLPITranCounter(TransmitLPITranCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitLPITranCounter(TransmitLPITranCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitLPITranCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitLPITranCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitLPITranCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXLPITRC (TXLPITRC)
            uint32_t transmit_low_power_idle : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitLPITranCounter& operator=(TransmitLPITranCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitLPITranCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitLPITranCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitLPITranCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitLPITranCounter) == 4UL, "Must be this exact size");
    /// Rx LPI microsecond counter register (RX_LPI_USEC_CNTR)
    struct ReceiveLPIUsecCounter final {
        /// Default Constructor
        ReceiveLPIUsecCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveLPIUsecCounter(ReceiveLPIUsecCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveLPIUsecCounter(ReceiveLPIUsecCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveLPIUsecCounter(ReceiveLPIUsecCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveLPIUsecCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveLPIUsecCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveLPIUsecCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXLPIUSC (RXLPIUSC)
            uint32_t receive_low_power_idle_microsecond_counter : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveLPIUsecCounter& operator=(ReceiveLPIUsecCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveLPIUsecCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveLPIUsecCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveLPIUsecCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveLPIUsecCounter) == 4UL, "Must be this exact size");
    /// Rx LPI transition counter register (RX_LPI_TRAN_CNTR)
    struct ReceiveLPITranCounter final {
        /// Default Constructor
        ReceiveLPITranCounter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        ReceiveLPITranCounter(ReceiveLPITranCounter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        ReceiveLPITranCounter(ReceiveLPITranCounter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        ReceiveLPITranCounter(ReceiveLPITranCounter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit ReceiveLPITranCounter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit ReceiveLPITranCounter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~ReceiveLPITranCounter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// RXLPITRC (RXLPITRC)
            uint32_t receive_low_power_idle_transition_counter : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        ReceiveLPITranCounter& operator=(ReceiveLPITranCounter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(ReceiveLPITranCounter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(ReceiveLPITranCounter const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<ReceiveLPITranCounter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(ReceiveLPITranCounter) == 4UL, "Must be this exact size");
    /// L3 and L4 control 0 register (MACL3L4C0R)
    struct Layer3AndLayer4Control0 final {
        /// Default Constructor
        Layer3AndLayer4Control0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3AndLayer4Control0(Layer3AndLayer4Control0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3AndLayer4Control0(Layer3AndLayer4Control0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3AndLayer4Control0(Layer3AndLayer4Control0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3AndLayer4Control0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3AndLayer4Control0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3AndLayer4Control0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3PEN0 (L3PEN0)
            uint32_t layer3_protocol_enable                             : 1;    // bit 0
            /// (reserved)
            uint32_t                                                    : 1;    // bit 1
            /// L3SAM0 (L3SAM0)
            uint32_t layer3_ip_source_address_match_enable              : 1;    // bit 2
            /// L3SAIM0 (L3SAIM0)
            uint32_t layer3_ip_source_address_inverse_match_enable      : 1;    // bit 3
            /// L3DAM0 (L3DAM0)
            uint32_t layer3_ip_destination_address_match_enable         : 1;    // bit 4
            /// L3DAIM0 (L3DAIM0)
            uint32_t layer3_ip_destination_address_inverse_match_enable : 1;    // bit 5
            /// L3HSBM0 (L3HSBM0)
            uint32_t layer3_ip_source_address_higher_bits_match         : 5;    // bits 6:10
            /// L3HDBM0 (L3HDBM0)
            uint32_t layer3_ip_destination_address_higher_bits_match    : 5;    // bits 11:15
            /// L4PEN0 (L4PEN0)
            uint32_t layer4_protocol_enable                             : 1;    // bit 16
            /// (reserved)
            uint32_t                                                    : 1;    // bit 17
            /// L4SPM0 (L4SPM0)
            uint32_t layer4_source_port_match_enable                    : 1;    // bit 18
            /// L4SPIM0 (L4SPIM0)
            uint32_t layer4_source_port_inverse_match_enable            : 1;    // bit 19
            /// L4DPM0 (L4DPM0)
            uint32_t layer4_destination_port_match_enable               : 1;    // bit 20
            /// L4DPIM0 (L4DPIM0)
            uint32_t layer4_destination_port_inverse_match_enable       : 1;    // bit 21
            /// (reserved)
            uint32_t                                                    : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3AndLayer4Control0& operator=(Layer3AndLayer4Control0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3AndLayer4Control0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3AndLayer4Control0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3AndLayer4Control0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3AndLayer4Control0) == 4UL, "Must be this exact size");
    /// Layer4 address filter 0 register (MACL4A0R)
    struct Layer4AddressFilter0 final {
        /// Default Constructor
        Layer4AddressFilter0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer4AddressFilter0(Layer4AddressFilter0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer4AddressFilter0(Layer4AddressFilter0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer4AddressFilter0(Layer4AddressFilter0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer4AddressFilter0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer4AddressFilter0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer4AddressFilter0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L4SP0 (L4SP0)
            uint32_t layer4_source_port_number      : 16;    // bits 0:15
            /// L4DP0 (L4DP0)
            uint32_t layer4_destination_port_number : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer4AddressFilter0& operator=(Layer4AddressFilter0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer4AddressFilter0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer4AddressFilter0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer4AddressFilter0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer4AddressFilter0) == 4UL, "Must be this exact size");
    /// MACL3A00R (MACL3A00R)
    struct Layer3Address0Filter0 final {
        /// Default Constructor
        Layer3Address0Filter0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address0Filter0(Layer3Address0Filter0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address0Filter0(Layer3Address0Filter0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address0Filter0(Layer3Address0Filter0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address0Filter0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address0Filter0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address0Filter0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A00 (L3A00)
            uint32_t layer3_address_0_filter_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address0Filter0& operator=(Layer3Address0Filter0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address0Filter0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address0Filter0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address0Filter0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address0Filter0) == 4UL, "Must be this exact size");
    /// Layer3 address 1 filter 0 register (MACL3A10R)
    struct Layer3Address1Filter0 final {
        /// Default Constructor
        Layer3Address1Filter0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address1Filter0(Layer3Address1Filter0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address1Filter0(Layer3Address1Filter0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address1Filter0(Layer3Address1Filter0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address1Filter0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address1Filter0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address1Filter0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A10 (L3A10)
            uint32_t layer3_address_1_filter_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address1Filter0& operator=(Layer3Address1Filter0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address1Filter0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address1Filter0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address1Filter0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address1Filter0) == 4UL, "Must be this exact size");
    /// Layer3 Address 2 filter 0 register (MACL3A20)
    struct Layer3Address2Filter0 final {
        /// Default Constructor
        Layer3Address2Filter0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address2Filter0(Layer3Address2Filter0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address2Filter0(Layer3Address2Filter0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address2Filter0(Layer3Address2Filter0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address2Filter0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address2Filter0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address2Filter0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A20 (L3A20)
            uint32_t layer3_address_2_filter_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address2Filter0& operator=(Layer3Address2Filter0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address2Filter0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address2Filter0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address2Filter0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address2Filter0) == 4UL, "Must be this exact size");
    /// Layer3 Address 3 filter 0 register (MACL3A30)
    struct Layer3Address3Filter0 final {
        /// Default Constructor
        Layer3Address3Filter0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address3Filter0(Layer3Address3Filter0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address3Filter0(Layer3Address3Filter0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address3Filter0(Layer3Address3Filter0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address3Filter0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address3Filter0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address3Filter0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A30 (L3A30)
            uint32_t layer3_address_3_filter_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address3Filter0& operator=(Layer3Address3Filter0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address3Filter0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address3Filter0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address3Filter0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address3Filter0) == 4UL, "Must be this exact size");
    /// L3 and L4 control 1 register (MACL3L4C1R)
    struct Layer3AndLayer4Control1 final {
        /// Default Constructor
        Layer3AndLayer4Control1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3AndLayer4Control1(Layer3AndLayer4Control1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3AndLayer4Control1(Layer3AndLayer4Control1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3AndLayer4Control1(Layer3AndLayer4Control1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3AndLayer4Control1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3AndLayer4Control1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3AndLayer4Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3PEN1 (L3PEN1)
            uint32_t layer3_protocol_enable                             : 1;    // bit 0
            /// (reserved)
            uint32_t                                                    : 1;    // bit 1
            /// L3SAM1 (L3SAM1)
            uint32_t layer3_ip_source_address_match_enable              : 1;    // bit 2
            /// L3SAIM1 (L3SAIM1)
            uint32_t layer3_ip_source_address_inverse_match_enable      : 1;    // bit 3
            /// L3DAM1 (L3DAM1)
            uint32_t layer3_ip_destination_address_match_enable         : 1;    // bit 4
            /// L3DAIM1 (L3DAIM1)
            uint32_t layer3_ip_destination_address_inverse_match_enable : 1;    // bit 5
            /// L3HSBM1 (L3HSBM1)
            uint32_t layer3_ip_source_address_higher_bits_match         : 5;    // bits 6:10
            /// L3HDBM1 (L3HDBM1)
            uint32_t layer3_ip_destination_address_higher_bits_match    : 5;    // bits 11:15
            /// L4PEN1 (L4PEN1)
            uint32_t layer4_protocol_enable                             : 1;    // bit 16
            /// (reserved)
            uint32_t                                                    : 1;    // bit 17
            /// L4SPM1 (L4SPM1)
            uint32_t layer4_source_port_match_enable                    : 1;    // bit 18
            /// L4SPIM1 (L4SPIM1)
            uint32_t layer4_source_port_inverse_match_enable            : 1;    // bit 19
            /// L4DPM1 (L4DPM1)
            uint32_t layer4_destination_port_match_enable               : 1;    // bit 20
            /// L4DPIM1 (L4DPIM1)
            uint32_t layer4_destination_port_inverse_match_enable       : 1;    // bit 21
            /// (reserved)
            uint32_t                                                    : 10;    // bits 22:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3AndLayer4Control1& operator=(Layer3AndLayer4Control1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3AndLayer4Control1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3AndLayer4Control1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3AndLayer4Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3AndLayer4Control1) == 4UL, "Must be this exact size");
    /// Layer 4 address filter 1 register (MACL4A1R)
    struct Layer4AddressFilter1 final {
        /// Default Constructor
        Layer4AddressFilter1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer4AddressFilter1(Layer4AddressFilter1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer4AddressFilter1(Layer4AddressFilter1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer4AddressFilter1(Layer4AddressFilter1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer4AddressFilter1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer4AddressFilter1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer4AddressFilter1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L4SP1 (L4SP1)
            uint32_t layer4_source_port_number      : 16;    // bits 0:15
            /// L4DP1 (L4DP1)
            uint32_t layer4_destination_port_number : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer4AddressFilter1& operator=(Layer4AddressFilter1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer4AddressFilter1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer4AddressFilter1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer4AddressFilter1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer4AddressFilter1) == 4UL, "Must be this exact size");
    /// Layer3 address 0 filter 1 Register (MACL3A01R)
    struct Layer3Address0Filter1 final {
        /// Default Constructor
        Layer3Address0Filter1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address0Filter1(Layer3Address0Filter1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address0Filter1(Layer3Address0Filter1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address0Filter1(Layer3Address0Filter1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address0Filter1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address0Filter1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address0Filter1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A01 (L3A01)
            uint32_t layer3_address_0_filter_1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address0Filter1& operator=(Layer3Address0Filter1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address0Filter1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address0Filter1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address0Filter1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address0Filter1) == 4UL, "Must be this exact size");
    /// Layer3 address 1 filter 1 register (MACL3A11R)
    struct Layer3Address1Filter1 final {
        /// Default Constructor
        Layer3Address1Filter1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address1Filter1(Layer3Address1Filter1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address1Filter1(Layer3Address1Filter1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address1Filter1(Layer3Address1Filter1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address1Filter1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address1Filter1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address1Filter1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A11 (L3A11)
            uint32_t layer3_address_1_filter_1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address1Filter1& operator=(Layer3Address1Filter1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address1Filter1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address1Filter1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address1Filter1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address1Filter1) == 4UL, "Must be this exact size");
    /// Layer3 address 2 filter 1 Register (MACL3A21R)
    struct Layer3Address2Filter1 final {
        /// Default Constructor
        Layer3Address2Filter1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address2Filter1(Layer3Address2Filter1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address2Filter1(Layer3Address2Filter1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address2Filter1(Layer3Address2Filter1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address2Filter1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address2Filter1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address2Filter1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A21 (L3A21)
            uint32_t layer3_address_2_filter_1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address2Filter1& operator=(Layer3Address2Filter1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address2Filter1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address2Filter1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address2Filter1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address2Filter1) == 4UL, "Must be this exact size");
    /// Layer3 address 3 filter 1 register (MACL3A31R)
    struct Layer3Address3Filter1 final {
        /// Default Constructor
        Layer3Address3Filter1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Layer3Address3Filter1(Layer3Address3Filter1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Layer3Address3Filter1(Layer3Address3Filter1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Layer3Address3Filter1(Layer3Address3Filter1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Layer3Address3Filter1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Layer3Address3Filter1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Layer3Address3Filter1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// L3A31 (L3A31)
            uint32_t layer3_address_3_filter_1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Layer3Address3Filter1& operator=(Layer3Address3Filter1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Layer3Address3Filter1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Layer3Address3Filter1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Layer3Address3Filter1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Layer3Address3Filter1) == 4UL, "Must be this exact size");
    /// Timestamp control Register (MACTSCR)
    struct TimestampControl final {
        /// Default Constructor
        TimestampControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampControl(TimestampControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampControl(TimestampControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampControl(TimestampControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSENA (TSENA)
            uint32_t timestamp_enable                       : 1;    // bit 0
            /// TSCFUPDT (TSCFUPDT)
            uint32_t timestamp_coarse_or_fine_update        : 1;    // bit 1
            /// TSINIT (TSINIT)
            uint32_t timestamp_initialize                   : 1;    // bit 2
            /// TSUPDT (TSUPDT)
            uint32_t timestamp_update                       : 1;    // bit 3
            /// (reserved)
            uint32_t                                        : 1;    // bit 4
            /// TSADDREG (TSADDREG)
            uint32_t timestamp_addend_register_update       : 1;    // bit 5
            /// (reserved)
            uint32_t                                        : 2;    // bits 6:7
            /// TSENALL (TSENALL)
            uint32_t timestamp_for_all_packets_enable       : 1;    // bit 8
            /// TSCTRLSSR (TSCTRLSSR)
            uint32_t timestamp_rollover_control             : 1;    // bit 9
            /// TSVER2ENA (TSVER2ENA)
            uint32_t timestamp_version_2_enable             : 1;    // bit 10
            /// TSIPENA (TSIPENA)
            uint32_t timestamp_for_ptp_over_ip_enable       : 1;    // bit 11
            /// TSIPV6ENA (TSIPV6ENA)
            uint32_t timestamp_for_ipv6_enable              : 1;    // bit 12
            /// TSIPV4ENA (TSIPV4ENA)
            uint32_t timestamp_for_ipv4_enable              : 1;    // bit 13
            /// TSEVNTENA (TSEVNTENA)
            uint32_t timestamp_event_enable                 : 1;    // bit 14
            /// TSMSTRENA (TSMSTRENA)
            uint32_t snapshot_timestamp_leader_enable       : 1;    // bit 15
            /// SNAPTYPSEL (SNAPTYPSEL)
            uint32_t snapshot_type_select                   : 2;    // bits 16:17
            /// TSENMACADDR (TSENMACADDR)
            uint32_t timestamp_for_ptp_over_ethernet_enable : 1;    // bit 18
            /// CSC (CSC)
            uint32_t calibration_state_changed              : 1;    // bit 19
            /// (reserved)
            uint32_t                                        : 4;    // bits 20:23
            /// TXTSSTSM (TXTSSTSM)
            uint32_t transmit_timestamp_status_mode         : 1;    // bit 24
            /// (reserved)
            uint32_t                                        : 7;    // bits 25:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampControl& operator=(TimestampControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampControl) == 4UL, "Must be this exact size");
    /// Sub-second increment register (MACSSIR)
    struct SubsecondIncrement final {
        /// Default Constructor
        SubsecondIncrement()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SubsecondIncrement(SubsecondIncrement volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SubsecondIncrement(SubsecondIncrement const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SubsecondIncrement(SubsecondIncrement&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SubsecondIncrement(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SubsecondIncrement(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SubsecondIncrement() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                          : 8;    // bits 0:7
            /// SNSINC (SNSINC)
            uint32_t sub_nanosecond_increment : 8;    // bits 8:15
            /// SSINC (SSINC)
            uint32_t sub_second_increment     : 8;    // bits 16:23
            /// (reserved)
            uint32_t                          : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SubsecondIncrement& operator=(SubsecondIncrement&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SubsecondIncrement volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SubsecondIncrement const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SubsecondIncrement>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SubsecondIncrement) == 4UL, "Must be this exact size");
    /// System time seconds register (MACSTSR)
    struct SystemTimeSeconds final {
        /// Default Constructor
        SystemTimeSeconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SystemTimeSeconds(SystemTimeSeconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SystemTimeSeconds(SystemTimeSeconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SystemTimeSeconds(SystemTimeSeconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SystemTimeSeconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SystemTimeSeconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SystemTimeSeconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSS (TSS)
            uint32_t timestamp_second : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SystemTimeSeconds& operator=(SystemTimeSeconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SystemTimeSeconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SystemTimeSeconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SystemTimeSeconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SystemTimeSeconds) == 4UL, "Must be this exact size");
    /// System time nanoseconds register (MACSTNR)
    struct SystemTimeNanoseconds final {
        /// Default Constructor
        SystemTimeNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SystemTimeNanoseconds(SystemTimeNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SystemTimeNanoseconds(SystemTimeNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SystemTimeNanoseconds(SystemTimeNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SystemTimeNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SystemTimeNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SystemTimeNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSSS (TSSS)
            uint32_t timestamp_sub_second : 31;    // bits 0:30
            /// (reserved)
            uint32_t                      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SystemTimeNanoseconds& operator=(SystemTimeNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SystemTimeNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SystemTimeNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SystemTimeNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SystemTimeNanoseconds) == 4UL, "Must be this exact size");
    /// System time seconds update register (MACSTSUR)
    struct SystemTimeSecondsUpdate final {
        /// Default Constructor
        SystemTimeSecondsUpdate()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SystemTimeSecondsUpdate(SystemTimeSecondsUpdate volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SystemTimeSecondsUpdate(SystemTimeSecondsUpdate const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SystemTimeSecondsUpdate(SystemTimeSecondsUpdate&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SystemTimeSecondsUpdate(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SystemTimeSecondsUpdate(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SystemTimeSecondsUpdate() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSS (TSS)
            uint32_t timestamp_second : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SystemTimeSecondsUpdate& operator=(SystemTimeSecondsUpdate&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SystemTimeSecondsUpdate volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SystemTimeSecondsUpdate const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SystemTimeSecondsUpdate>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SystemTimeSecondsUpdate) == 4UL, "Must be this exact size");
    /// System time nanoseconds update register (MACSTNUR)
    struct SystemTimeNanosecondsUpdate final {
        /// Default Constructor
        SystemTimeNanosecondsUpdate()
            : whole{0u} {}
        /// Copy Constructor from volatile
        SystemTimeNanosecondsUpdate(SystemTimeNanosecondsUpdate volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        SystemTimeNanosecondsUpdate(SystemTimeNanosecondsUpdate const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        SystemTimeNanosecondsUpdate(SystemTimeNanosecondsUpdate&&) = delete;
        /// Parameterized Constructor for constant references
        explicit SystemTimeNanosecondsUpdate(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit SystemTimeNanosecondsUpdate(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~SystemTimeNanosecondsUpdate() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSSS (TSSS)
            uint32_t timestamp_sub_second : 31;    // bits 0:30
            /// ADDSUB (ADDSUB)
            uint32_t add_or_sub_time      : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        SystemTimeNanosecondsUpdate& operator=(SystemTimeNanosecondsUpdate&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(SystemTimeNanosecondsUpdate volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(SystemTimeNanosecondsUpdate const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<SystemTimeNanosecondsUpdate>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(SystemTimeNanosecondsUpdate) == 4UL, "Must be this exact size");
    /// Timestamp addend register (MACTSAR)
    struct TimestampAddend final {
        /// Default Constructor
        TimestampAddend()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampAddend(TimestampAddend volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampAddend(TimestampAddend const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampAddend(TimestampAddend&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampAddend(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampAddend(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampAddend() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSAR (TSAR)
            uint32_t timestamp_addend_register_value : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampAddend& operator=(TimestampAddend&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampAddend volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampAddend const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampAddend>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampAddend) == 4UL, "Must be this exact size");
    /// Timestamp status register (MACTSSR)
    struct TimestampStatus final {
        /// Default Constructor
        TimestampStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampStatus(TimestampStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampStatus(TimestampStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampStatus(TimestampStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSSOVF (TSSOVF)
            uint32_t timestamp_seconds_overflow                 : 1;    // bit 0
            /// TSTARGT0 (TSTARGT0)
            uint32_t timestamp_target_0_reached                 : 1;    // bit 1
            /// AUXTSTRIG (AUXTSTRIG)
            uint32_t aux_timestamp_trigger_snapshot             : 1;    // bit 2
            /// TSTRGTERR0 (TSTRGTERR0)
            uint32_t timestamp_target_0_error                   : 1;    // bit 3
            /// (reserved)
            uint32_t                                            : 11;    // bits 4:14
            /// TXTSSIS (TXTSSIS)
            uint32_t transmit_timestamp_status_interrupt_status : 1;    // bit 15
            /// ATSSTN (ATSSTN)
            uint32_t aux_timestamp_snapshot_trigger_id          : 4;    // bits 16:19
            /// (reserved)
            uint32_t                                            : 4;    // bits 20:23
            /// ATSSTM (ATSSTM)
            uint32_t aux_timestamp_snapshot_trigger_missed      : 1;    // bit 24
            /// ATSNS (ATSNS)
            uint32_t aux_timestamp_snapshots                    : 5;    // bits 25:29
            /// (reserved)
            uint32_t                                            : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampStatus& operator=(TimestampStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampStatus) == 4UL, "Must be this exact size");
    /// Tx timestamp status nanoseconds register (MACTxTSSNR)
    struct TransmitTimestampStatusNanoseconds final {
        /// Default Constructor
        TransmitTimestampStatusNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitTimestampStatusNanoseconds(TransmitTimestampStatusNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitTimestampStatusNanoseconds(TransmitTimestampStatusNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitTimestampStatusNanoseconds(TransmitTimestampStatusNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitTimestampStatusNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitTimestampStatusNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitTimestampStatusNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXTSSLO (TXTSSLO)
            uint32_t transmit_timestamp_status_low    : 31;    // bits 0:30
            /// TXTSSMIS (TXTSSMIS)
            uint32_t transmit_timestamp_status_missed : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitTimestampStatusNanoseconds& operator=(TransmitTimestampStatusNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitTimestampStatusNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitTimestampStatusNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitTimestampStatusNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitTimestampStatusNanoseconds) == 4UL, "Must be this exact size");
    /// Tx timestamp status seconds register (MACTxTSSSR)
    struct TransmitTimestampStatusSeconds final {
        /// Default Constructor
        TransmitTimestampStatusSeconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TransmitTimestampStatusSeconds(TransmitTimestampStatusSeconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TransmitTimestampStatusSeconds(TransmitTimestampStatusSeconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TransmitTimestampStatusSeconds(TransmitTimestampStatusSeconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TransmitTimestampStatusSeconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TransmitTimestampStatusSeconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TransmitTimestampStatusSeconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TXTSSHI (TXTSSHI)
            uint32_t transmit_timestamp_status_high : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TransmitTimestampStatusSeconds& operator=(TransmitTimestampStatusSeconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TransmitTimestampStatusSeconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TransmitTimestampStatusSeconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TransmitTimestampStatusSeconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TransmitTimestampStatusSeconds) == 4UL, "Must be this exact size");
    /// Auxiliary control register (MACACR)
    struct AuxiliaryControl final {
        /// Default Constructor
        AuxiliaryControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AuxiliaryControl(AuxiliaryControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AuxiliaryControl(AuxiliaryControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AuxiliaryControl(AuxiliaryControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AuxiliaryControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AuxiliaryControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AuxiliaryControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// ATSFC (ATSFC)
            uint32_t aux_snapshot_fifo_clear : 1;    // bit 0
            /// (reserved)
            uint32_t                         : 3;    // bits 1:3
            /// ATSEN0 (ATSEN0)
            uint32_t aux_snapshot_enable0    : 1;    // bit 4
            /// ATSEN1 (ATSEN1)
            uint32_t aux_snapshot_enable1    : 1;    // bit 5
            /// ATSEN2 (ATSEN2)
            uint32_t aux_snapshot_enable2    : 1;    // bit 6
            /// ATSEN3 (ATSEN3)
            uint32_t aux_snapshot_enable3    : 1;    // bit 7
            /// (reserved)
            uint32_t                         : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AuxiliaryControl& operator=(AuxiliaryControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AuxiliaryControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AuxiliaryControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AuxiliaryControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AuxiliaryControl) == 4UL, "Must be this exact size");
    /// Auxiliary timestamp nanoseconds register (MACATSNR)
    struct AuxiliaryTimestampNanoseconds final {
        /// Default Constructor
        AuxiliaryTimestampNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AuxiliaryTimestampNanoseconds(AuxiliaryTimestampNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AuxiliaryTimestampNanoseconds(AuxiliaryTimestampNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AuxiliaryTimestampNanoseconds(AuxiliaryTimestampNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AuxiliaryTimestampNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AuxiliaryTimestampNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AuxiliaryTimestampNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// AUXTSLO (AUXTSLO)
            uint32_t aux_timestamp_ns : 31;    // bits 0:30
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
        AuxiliaryTimestampNanoseconds& operator=(AuxiliaryTimestampNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AuxiliaryTimestampNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AuxiliaryTimestampNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AuxiliaryTimestampNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AuxiliaryTimestampNanoseconds) == 4UL, "Must be this exact size");
    /// Auxiliary timestamp seconds register (MACATSSR)
    struct AuxiliaryTimestampSeconds final {
        /// Default Constructor
        AuxiliaryTimestampSeconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AuxiliaryTimestampSeconds(AuxiliaryTimestampSeconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AuxiliaryTimestampSeconds(AuxiliaryTimestampSeconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AuxiliaryTimestampSeconds(AuxiliaryTimestampSeconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AuxiliaryTimestampSeconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AuxiliaryTimestampSeconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AuxiliaryTimestampSeconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// AUXTSHI (AUXTSHI)
            uint32_t aux_timestamp_secs : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AuxiliaryTimestampSeconds& operator=(AuxiliaryTimestampSeconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AuxiliaryTimestampSeconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AuxiliaryTimestampSeconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AuxiliaryTimestampSeconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AuxiliaryTimestampSeconds) == 4UL, "Must be this exact size");
    /// Timestamp Ingress asymmetric correction register (MACTSIACR)
    struct TimestampIngressAsymmetricCorrection final {
        /// Default Constructor
        TimestampIngressAsymmetricCorrection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampIngressAsymmetricCorrection(TimestampIngressAsymmetricCorrection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampIngressAsymmetricCorrection(TimestampIngressAsymmetricCorrection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampIngressAsymmetricCorrection(TimestampIngressAsymmetricCorrection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampIngressAsymmetricCorrection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampIngressAsymmetricCorrection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampIngressAsymmetricCorrection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// OSTIAC (OSTIAC)
            uint32_t one_step_timestamp_ingress_asymmetric_correction : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampIngressAsymmetricCorrection& operator=(TimestampIngressAsymmetricCorrection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampIngressAsymmetricCorrection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampIngressAsymmetricCorrection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampIngressAsymmetricCorrection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampIngressAsymmetricCorrection) == 4UL, "Must be this exact size");
    /// Timestamp Egress asymmetric correction register (MACTSEACR)
    struct TimestampEgressAsymmetricCorrection final {
        /// Default Constructor
        TimestampEgressAsymmetricCorrection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampEgressAsymmetricCorrection(TimestampEgressAsymmetricCorrection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampEgressAsymmetricCorrection(TimestampEgressAsymmetricCorrection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampEgressAsymmetricCorrection(TimestampEgressAsymmetricCorrection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampEgressAsymmetricCorrection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampEgressAsymmetricCorrection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampEgressAsymmetricCorrection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// OSTEAC (OSTEAC)
            uint32_t one_step_timestamp_egress_asymmetric_correction : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampEgressAsymmetricCorrection& operator=(TimestampEgressAsymmetricCorrection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampEgressAsymmetricCorrection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampEgressAsymmetricCorrection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampEgressAsymmetricCorrection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampEgressAsymmetricCorrection) == 4UL, "Must be this exact size");
    /// Timestamp Ingress correction nanosecond register (MACTSICNR)
    struct TimestampIngressCorrectionNanoseconds final {
        /// Default Constructor
        TimestampIngressCorrectionNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampIngressCorrectionNanoseconds(TimestampIngressCorrectionNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampIngressCorrectionNanoseconds(TimestampIngressCorrectionNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampIngressCorrectionNanoseconds(TimestampIngressCorrectionNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampIngressCorrectionNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampIngressCorrectionNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampIngressCorrectionNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSIC (TSIC)
            uint32_t timestamp_ingress_correction : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampIngressCorrectionNanoseconds& operator=(TimestampIngressCorrectionNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampIngressCorrectionNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampIngressCorrectionNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampIngressCorrectionNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampIngressCorrectionNanoseconds) == 4UL, "Must be this exact size");
    /// Timestamp Egress correction nanosecond register (MACTSECNR)
    struct TimestampEgressCorrectionNanoseconds final {
        /// Default Constructor
        TimestampEgressCorrectionNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        TimestampEgressCorrectionNanoseconds(TimestampEgressCorrectionNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        TimestampEgressCorrectionNanoseconds(TimestampEgressCorrectionNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        TimestampEgressCorrectionNanoseconds(TimestampEgressCorrectionNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit TimestampEgressCorrectionNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit TimestampEgressCorrectionNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~TimestampEgressCorrectionNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSEC (TSEC)
            uint32_t timestamp_egress_correction : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        TimestampEgressCorrectionNanoseconds& operator=(TimestampEgressCorrectionNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(TimestampEgressCorrectionNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(TimestampEgressCorrectionNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<TimestampEgressCorrectionNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(TimestampEgressCorrectionNanoseconds) == 4UL, "Must be this exact size");
    /// PPS control register (MACPPSCR)
    struct PulsePerSecondControl final {
        /// Default Constructor
        PulsePerSecondControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PulsePerSecondControl(PulsePerSecondControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PulsePerSecondControl(PulsePerSecondControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PulsePerSecondControl(PulsePerSecondControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PulsePerSecondControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PulsePerSecondControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PulsePerSecondControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PPSCTRL (PPSCTRL)
            uint32_t pulse_per_second_control         : 4;    // bits 0:3
            /// PPSEN0 (PPSEN0)
            uint32_t pulse_per_second_output_0_enable : 1;    // bit 4
            /// TRGTMODSEL0 (TRGTMODSEL0)
            uint32_t target_mode_select_0             : 2;    // bits 5:6
            /// (reserved)
            uint32_t                                  : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PulsePerSecondControl& operator=(PulsePerSecondControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PulsePerSecondControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PulsePerSecondControl) == 4UL, "Must be this exact size");
    /// PPS target time seconds register (MACPPSTTSR)
    struct PulsePerSecondTargetTimeSeconds final {
        /// Default Constructor
        PulsePerSecondTargetTimeSeconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PulsePerSecondTargetTimeSeconds(PulsePerSecondTargetTimeSeconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PulsePerSecondTargetTimeSeconds(PulsePerSecondTargetTimeSeconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PulsePerSecondTargetTimeSeconds(PulsePerSecondTargetTimeSeconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PulsePerSecondTargetTimeSeconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PulsePerSecondTargetTimeSeconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PulsePerSecondTargetTimeSeconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TSTRH0 (TSTRH0)
            uint32_t target_time_seconds_high_0 : 31;    // bits 0:30
            /// (reserved)
            uint32_t                            : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PulsePerSecondTargetTimeSeconds& operator=(PulsePerSecondTargetTimeSeconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondTargetTimeSeconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondTargetTimeSeconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PulsePerSecondTargetTimeSeconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PulsePerSecondTargetTimeSeconds) == 4UL, "Must be this exact size");
    /// PPS target time nanoseconds register (MACPPSTTNR)
    struct PulsePerSecondTargetTimeNanoseconds final {
        /// Default Constructor
        PulsePerSecondTargetTimeNanoseconds()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PulsePerSecondTargetTimeNanoseconds(PulsePerSecondTargetTimeNanoseconds volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PulsePerSecondTargetTimeNanoseconds(PulsePerSecondTargetTimeNanoseconds const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PulsePerSecondTargetTimeNanoseconds(PulsePerSecondTargetTimeNanoseconds&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PulsePerSecondTargetTimeNanoseconds(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PulsePerSecondTargetTimeNanoseconds(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PulsePerSecondTargetTimeNanoseconds() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// TTSL0 (TTSL0)
            uint32_t target_time_seconds_low_0 : 31;    // bits 0:30
            /// TRGTBUSY0 (TRGTBUSY0)
            uint32_t target_time_busy_0        : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PulsePerSecondTargetTimeNanoseconds& operator=(PulsePerSecondTargetTimeNanoseconds&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondTargetTimeNanoseconds volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondTargetTimeNanoseconds const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PulsePerSecondTargetTimeNanoseconds>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PulsePerSecondTargetTimeNanoseconds) == 4UL, "Must be this exact size");
    /// PPS interval register (MACPPSIR)
    struct PulsePerSecondInterval final {
        /// Default Constructor
        PulsePerSecondInterval()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PulsePerSecondInterval(PulsePerSecondInterval volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PulsePerSecondInterval(PulsePerSecondInterval const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PulsePerSecondInterval(PulsePerSecondInterval&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PulsePerSecondInterval(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PulsePerSecondInterval(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PulsePerSecondInterval() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PPSINT0 (PPSINT0)
            uint32_t pulse_per_second_interval_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PulsePerSecondInterval& operator=(PulsePerSecondInterval&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondInterval volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondInterval const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PulsePerSecondInterval>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PulsePerSecondInterval) == 4UL, "Must be this exact size");
    /// PPS width register (MACPPSWR)
    struct PulsePerSecondWidth final {
        /// Default Constructor
        PulsePerSecondWidth()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PulsePerSecondWidth(PulsePerSecondWidth volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PulsePerSecondWidth(PulsePerSecondWidth const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PulsePerSecondWidth(PulsePerSecondWidth&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PulsePerSecondWidth(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PulsePerSecondWidth(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PulsePerSecondWidth() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PPSWIDTH0 (PPSWIDTH0)
            uint32_t pulse_per_second_width_0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PulsePerSecondWidth& operator=(PulsePerSecondWidth&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondWidth volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PulsePerSecondWidth const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PulsePerSecondWidth>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PulsePerSecondWidth) == 4UL, "Must be this exact size");
    /// PTP Offload control register (MACPOCR)
    struct PrecisionTimeProtocolOffloadControl final {
        /// Default Constructor
        PrecisionTimeProtocolOffloadControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PrecisionTimeProtocolOffloadControl(PrecisionTimeProtocolOffloadControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PrecisionTimeProtocolOffloadControl(PrecisionTimeProtocolOffloadControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PrecisionTimeProtocolOffloadControl(PrecisionTimeProtocolOffloadControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PrecisionTimeProtocolOffloadControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PrecisionTimeProtocolOffloadControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PrecisionTimeProtocolOffloadControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// PTOEN (PTOEN)
            uint32_t precision_time_protocol_offload_enable : 1;    // bit 0
            /// ASYNCEN (ASYNCEN)
            uint32_t automatic_ptp_sync_enable              : 1;    // bit 1
            /// APDREQEN (APDREQEN)
            uint32_t automatic_ptp_delay_message_enable     : 1;    // bit 2
            /// (reserved)
            uint32_t                                        : 1;    // bit 3
            /// ASYNCTRIG (ASYNCTRIG)
            uint32_t automatic_ptp_sync_trigger             : 1;    // bit 4
            /// APDREQTRIG (APDREQTRIG)
            uint32_t automatic_ptp_delay_message_trigger    : 1;    // bit 5
            /// DRRDIS (DRRDIS)
            uint32_t disable_pto_delay_response_generation  : 1;    // bit 6
            /// (reserved)
            uint32_t                                        : 1;    // bit 7
            /// DN (DN)
            uint32_t domain_number                          : 8;    // bits 8:15
            /// (reserved)
            uint32_t                                        : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PrecisionTimeProtocolOffloadControl& operator=(PrecisionTimeProtocolOffloadControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolOffloadControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolOffloadControl const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PrecisionTimeProtocolOffloadControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PrecisionTimeProtocolOffloadControl) == 4UL, "Must be this exact size");
    /// PTP Source Port Identity 0 Register (MACSPI0R)
    struct PrecisionTimeProtocolSourcePortIdentity0 final {
        /// Default Constructor
        PrecisionTimeProtocolSourcePortIdentity0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PrecisionTimeProtocolSourcePortIdentity0(PrecisionTimeProtocolSourcePortIdentity0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PrecisionTimeProtocolSourcePortIdentity0(PrecisionTimeProtocolSourcePortIdentity0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PrecisionTimeProtocolSourcePortIdentity0(PrecisionTimeProtocolSourcePortIdentity0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PrecisionTimeProtocolSourcePortIdentity0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PrecisionTimeProtocolSourcePortIdentity0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PrecisionTimeProtocolSourcePortIdentity0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SPI0 (SPI0)
            uint32_t source_port_identity0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PrecisionTimeProtocolSourcePortIdentity0& operator=(PrecisionTimeProtocolSourcePortIdentity0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PrecisionTimeProtocolSourcePortIdentity0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PrecisionTimeProtocolSourcePortIdentity0) == 4UL, "Must be this exact size");
    /// PTP Source port identity 1 register (MACSPI1R)
    struct PrecisionTimeProtocolSourcePortIdentity1 final {
        /// Default Constructor
        PrecisionTimeProtocolSourcePortIdentity1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PrecisionTimeProtocolSourcePortIdentity1(PrecisionTimeProtocolSourcePortIdentity1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PrecisionTimeProtocolSourcePortIdentity1(PrecisionTimeProtocolSourcePortIdentity1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PrecisionTimeProtocolSourcePortIdentity1(PrecisionTimeProtocolSourcePortIdentity1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PrecisionTimeProtocolSourcePortIdentity1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PrecisionTimeProtocolSourcePortIdentity1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PrecisionTimeProtocolSourcePortIdentity1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SPI1 (SPI1)
            uint32_t serial_peripheral_interface1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PrecisionTimeProtocolSourcePortIdentity1& operator=(PrecisionTimeProtocolSourcePortIdentity1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PrecisionTimeProtocolSourcePortIdentity1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PrecisionTimeProtocolSourcePortIdentity1) == 4UL, "Must be this exact size");
    /// PTP Source port identity 2 register (MACSPI2R)
    struct PrecisionTimeProtocolSourcePortIdentity2 final {
        /// Default Constructor
        PrecisionTimeProtocolSourcePortIdentity2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PrecisionTimeProtocolSourcePortIdentity2(PrecisionTimeProtocolSourcePortIdentity2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PrecisionTimeProtocolSourcePortIdentity2(PrecisionTimeProtocolSourcePortIdentity2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PrecisionTimeProtocolSourcePortIdentity2(PrecisionTimeProtocolSourcePortIdentity2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PrecisionTimeProtocolSourcePortIdentity2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PrecisionTimeProtocolSourcePortIdentity2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PrecisionTimeProtocolSourcePortIdentity2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// SPI2 (SPI2)
            uint32_t serial_peripheral_interface2 : 16;    // bits 0:15
            /// (reserved)
            uint32_t                              : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PrecisionTimeProtocolSourcePortIdentity2& operator=(PrecisionTimeProtocolSourcePortIdentity2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PrecisionTimeProtocolSourcePortIdentity2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PrecisionTimeProtocolSourcePortIdentity2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PrecisionTimeProtocolSourcePortIdentity2) == 4UL, "Must be this exact size");
    /// Log message interval register (MACLMIR)
    struct LogMessageInterval final {
        /// Default Constructor
        LogMessageInterval()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LogMessageInterval(LogMessageInterval volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LogMessageInterval(LogMessageInterval const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LogMessageInterval(LogMessageInterval&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LogMessageInterval(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LogMessageInterval(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LogMessageInterval() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// LSI (LSI)
            uint32_t log_sync_interval                : 8;    // bits 0:7
            /// DRSYNCR (DRSYNCR)
            uint32_t delay_request_to_sync_ratio      : 3;    // bits 8:10
            /// (reserved)
            uint32_t                                  : 13;    // bits 11:23
            /// LMPDRI (LMPDRI)
            uint32_t log_min_p_delay_request_interval : 8;    // bits 24:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LogMessageInterval& operator=(LogMessageInterval&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LogMessageInterval volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LogMessageInterval const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LogMessageInterval>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LogMessageInterval) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Operating mode configuration register (MACCR)
    OperatingModeConfiguration operating_mode_configuration;    // offset 0x0UL
    /// Extended operating mode configuration register (MACECR)
    ExtendedOperatingModeConfiguration extended_operating_mode_configuration;    // offset 0x4UL
    /// Packet filtering control register (MACPFR)
    PacketFilterControl packet_filter_control;    // offset 0x8UL
    /// Watchdog timeout register (MACWTR)
    WatchdogTimeout watchdog_timeout;    // offset 0xcUL
    /// Hash Table 0 register (MACHT0R)
    HashTable0 hash_table_0;    // offset 0x10UL
    /// Hash Table 1 register (MACHT1R)
    HashTable1 hash_table_1;    // offset 0x14UL
    uint32_t : 32;              // offset 0x18UL
    uint32_t : 32;              // offset 0x1cUL
    uint32_t : 32;              // offset 0x20UL
    uint32_t : 32;              // offset 0x24UL
    uint32_t : 32;              // offset 0x28UL
    uint32_t : 32;              // offset 0x2cUL
    uint32_t : 32;              // offset 0x30UL
    uint32_t : 32;              // offset 0x34UL
    uint32_t : 32;              // offset 0x38UL
    uint32_t : 32;              // offset 0x3cUL
    uint32_t : 32;              // offset 0x40UL
    uint32_t : 32;              // offset 0x44UL
    uint32_t : 32;              // offset 0x48UL
    uint32_t : 32;              // offset 0x4cUL
    /// VLAN tag register (MACVTR)
    VlanTag vlan_tag;    // offset 0x50UL
    uint32_t : 32;       // offset 0x54UL
    /// VLAN Hash table register (MACVHTR)
    VlanHashTable vlan_hash_table;    // offset 0x58UL
    uint32_t : 32;                    // offset 0x5cUL
    /// VLAN inclusion register (MACVIR)
    VlanInclusion vlan_inclusion;    // offset 0x60UL
    /// Inner VLAN inclusion register (MACIVIR)
    InnerVlanInclusion inner_vlan_inclusion;    // offset 0x64UL
    uint32_t : 32;                              // offset 0x68UL
    uint32_t : 32;                              // offset 0x6cUL
    /// Tx Queue flow control register (MACQTxFCR)
    QueueTransmitFlowControl queue_transmit_flow_control;    // offset 0x70UL
    uint32_t : 32;                                           // offset 0x74UL
    uint32_t : 32;                                           // offset 0x78UL
    uint32_t : 32;                                           // offset 0x7cUL
    uint32_t : 32;                                           // offset 0x80UL
    uint32_t : 32;                                           // offset 0x84UL
    uint32_t : 32;                                           // offset 0x88UL
    uint32_t : 32;                                           // offset 0x8cUL
    /// Rx flow control register (MACRxFCR)
    ReceiveFlowControl receive_flow_control;    // offset 0x90UL
    uint32_t : 32;                              // offset 0x94UL
    uint32_t : 32;                              // offset 0x98UL
    uint32_t : 32;                              // offset 0x9cUL
    uint32_t : 32;                              // offset 0xa0UL
    uint32_t : 32;                              // offset 0xa4UL
    uint32_t : 32;                              // offset 0xa8UL
    uint32_t : 32;                              // offset 0xacUL
    /// Interrupt status register (MACISR)
    InterruptStatus interrupt_status;    // offset 0xb0UL
    /// Interrupt enable register (MACIER)
    InterruptEnable interrupt_enable;    // offset 0xb4UL
    /// Rx Tx status register (MACRxTxSR)
    ReceiveTransmitStatus receive_transmit_status;    // offset 0xb8UL
    uint32_t : 32;                                    // offset 0xbcUL
    /// PMT control status register (MACPCSR)
    PowerManagementControlStatus power_management_control_status;    // offset 0xc0UL
    /// Remove wakeup packet filter register (MACRWKPFR)
    RemoteWakeupPacketFilter remote_wakeup_packet_filter;    // offset 0xc4UL
    uint32_t : 32;                                           // offset 0xc8UL
    uint32_t : 32;                                           // offset 0xccUL
    /// LPI control status register (MACLCSR)
    LowPowerIdleControlStatus low_power_idle_control_status;    // offset 0xd0UL
    /// LPI timers control register (MACLTCR)
    LowPowerIdleTimersControl low_power_idle_timers_control;    // offset 0xd4UL
    /// LPI entry timer register (MACLETR)
    LowPowerIdleEntryTimer low_power_idle_entry_timer;    // offset 0xd8UL
    /// 1-microsecond-tick counter register (MAC1USTCR)
    OneMicrosecondTickCounter one_microsecond_tick_counter;    // offset 0xdcUL
    uint32_t : 32;                                             // offset 0xe0UL
    uint32_t : 32;                                             // offset 0xe4UL
    uint32_t : 32;                                             // offset 0xe8UL
    uint32_t : 32;                                             // offset 0xecUL
    uint32_t : 32;                                             // offset 0xf0UL
    uint32_t : 32;                                             // offset 0xf4UL
    uint32_t : 32;                                             // offset 0xf8UL
    uint32_t : 32;                                             // offset 0xfcUL
    uint32_t : 32;                                             // offset 0x100UL
    uint32_t : 32;                                             // offset 0x104UL
    uint32_t : 32;                                             // offset 0x108UL
    uint32_t : 32;                                             // offset 0x10cUL
    /// Version register (MACVR)
    Version version;    // offset 0x110UL
    /// Debug register (MACDR)
    Debug debug;      // offset 0x114UL
    uint32_t : 32;    // offset 0x118UL
    uint32_t : 32;    // offset 0x11cUL
    /// HW feature 1 register (MACHWF1R)
    HardwareFeature1 hardware_feature_1;    // offset 0x120UL
    /// HW feature 2 register (MACHWF2R)
    HardwareFeature2 hardware_feature_2;    // offset 0x124UL
    uint32_t : 32;                          // offset 0x128UL
    uint32_t : 32;                          // offset 0x12cUL
    uint32_t : 32;                          // offset 0x130UL
    uint32_t : 32;                          // offset 0x134UL
    uint32_t : 32;                          // offset 0x138UL
    uint32_t : 32;                          // offset 0x13cUL
    uint32_t : 32;                          // offset 0x140UL
    uint32_t : 32;                          // offset 0x144UL
    uint32_t : 32;                          // offset 0x148UL
    uint32_t : 32;                          // offset 0x14cUL
    uint32_t : 32;                          // offset 0x150UL
    uint32_t : 32;                          // offset 0x154UL
    uint32_t : 32;                          // offset 0x158UL
    uint32_t : 32;                          // offset 0x15cUL
    uint32_t : 32;                          // offset 0x160UL
    uint32_t : 32;                          // offset 0x164UL
    uint32_t : 32;                          // offset 0x168UL
    uint32_t : 32;                          // offset 0x16cUL
    uint32_t : 32;                          // offset 0x170UL
    uint32_t : 32;                          // offset 0x174UL
    uint32_t : 32;                          // offset 0x178UL
    uint32_t : 32;                          // offset 0x17cUL
    uint32_t : 32;                          // offset 0x180UL
    uint32_t : 32;                          // offset 0x184UL
    uint32_t : 32;                          // offset 0x188UL
    uint32_t : 32;                          // offset 0x18cUL
    uint32_t : 32;                          // offset 0x190UL
    uint32_t : 32;                          // offset 0x194UL
    uint32_t : 32;                          // offset 0x198UL
    uint32_t : 32;                          // offset 0x19cUL
    uint32_t : 32;                          // offset 0x1a0UL
    uint32_t : 32;                          // offset 0x1a4UL
    uint32_t : 32;                          // offset 0x1a8UL
    uint32_t : 32;                          // offset 0x1acUL
    uint32_t : 32;                          // offset 0x1b0UL
    uint32_t : 32;                          // offset 0x1b4UL
    uint32_t : 32;                          // offset 0x1b8UL
    uint32_t : 32;                          // offset 0x1bcUL
    uint32_t : 32;                          // offset 0x1c0UL
    uint32_t : 32;                          // offset 0x1c4UL
    uint32_t : 32;                          // offset 0x1c8UL
    uint32_t : 32;                          // offset 0x1ccUL
    uint32_t : 32;                          // offset 0x1d0UL
    uint32_t : 32;                          // offset 0x1d4UL
    uint32_t : 32;                          // offset 0x1d8UL
    uint32_t : 32;                          // offset 0x1dcUL
    uint32_t : 32;                          // offset 0x1e0UL
    uint32_t : 32;                          // offset 0x1e4UL
    uint32_t : 32;                          // offset 0x1e8UL
    uint32_t : 32;                          // offset 0x1ecUL
    uint32_t : 32;                          // offset 0x1f0UL
    uint32_t : 32;                          // offset 0x1f4UL
    uint32_t : 32;                          // offset 0x1f8UL
    uint32_t : 32;                          // offset 0x1fcUL
    /// MDIO address register (MACMDIOAR)
    MdioAddress mdio_address;    // offset 0x200UL
    /// MDIO data register (MACMDIODR)
    MdioData mdio_data;    // offset 0x204UL
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
    /// Address 0 high register (MACA0HR)
    Address0High address_0_high;    // offset 0x300UL
    /// Address 0 low register (MACA0LR)
    Address0Low address_0_low;    // offset 0x304UL
    /// Address 1 high register (MACA1HR)
    Address1High address_1_high;    // offset 0x308UL
    /// Address 1 low register (MACA1LR)
    Address1Low address_1_low;    // offset 0x30cUL
    /// Address 2 high register (MACA2HR)
    Address2High address_2_high;    // offset 0x310UL
    /// Address 2 low register (MACA2LR)
    Address2Low address_2_low;    // offset 0x314UL
    /// Address 3 high register (MACA3HR)
    Address3High address_3_high;    // offset 0x318UL
    /// Address 3 low register (MACA3LR)
    Address3Low address_3_low;    // offset 0x31cUL
    uint32_t : 32;                // offset 0x320UL
    uint32_t : 32;                // offset 0x324UL
    uint32_t : 32;                // offset 0x328UL
    uint32_t : 32;                // offset 0x32cUL
    uint32_t : 32;                // offset 0x330UL
    uint32_t : 32;                // offset 0x334UL
    uint32_t : 32;                // offset 0x338UL
    uint32_t : 32;                // offset 0x33cUL
    uint32_t : 32;                // offset 0x340UL
    uint32_t : 32;                // offset 0x344UL
    uint32_t : 32;                // offset 0x348UL
    uint32_t : 32;                // offset 0x34cUL
    uint32_t : 32;                // offset 0x350UL
    uint32_t : 32;                // offset 0x354UL
    uint32_t : 32;                // offset 0x358UL
    uint32_t : 32;                // offset 0x35cUL
    uint32_t : 32;                // offset 0x360UL
    uint32_t : 32;                // offset 0x364UL
    uint32_t : 32;                // offset 0x368UL
    uint32_t : 32;                // offset 0x36cUL
    uint32_t : 32;                // offset 0x370UL
    uint32_t : 32;                // offset 0x374UL
    uint32_t : 32;                // offset 0x378UL
    uint32_t : 32;                // offset 0x37cUL
    uint32_t : 32;                // offset 0x380UL
    uint32_t : 32;                // offset 0x384UL
    uint32_t : 32;                // offset 0x388UL
    uint32_t : 32;                // offset 0x38cUL
    uint32_t : 32;                // offset 0x390UL
    uint32_t : 32;                // offset 0x394UL
    uint32_t : 32;                // offset 0x398UL
    uint32_t : 32;                // offset 0x39cUL
    uint32_t : 32;                // offset 0x3a0UL
    uint32_t : 32;                // offset 0x3a4UL
    uint32_t : 32;                // offset 0x3a8UL
    uint32_t : 32;                // offset 0x3acUL
    uint32_t : 32;                // offset 0x3b0UL
    uint32_t : 32;                // offset 0x3b4UL
    uint32_t : 32;                // offset 0x3b8UL
    uint32_t : 32;                // offset 0x3bcUL
    uint32_t : 32;                // offset 0x3c0UL
    uint32_t : 32;                // offset 0x3c4UL
    uint32_t : 32;                // offset 0x3c8UL
    uint32_t : 32;                // offset 0x3ccUL
    uint32_t : 32;                // offset 0x3d0UL
    uint32_t : 32;                // offset 0x3d4UL
    uint32_t : 32;                // offset 0x3d8UL
    uint32_t : 32;                // offset 0x3dcUL
    uint32_t : 32;                // offset 0x3e0UL
    uint32_t : 32;                // offset 0x3e4UL
    uint32_t : 32;                // offset 0x3e8UL
    uint32_t : 32;                // offset 0x3ecUL
    uint32_t : 32;                // offset 0x3f0UL
    uint32_t : 32;                // offset 0x3f4UL
    uint32_t : 32;                // offset 0x3f8UL
    uint32_t : 32;                // offset 0x3fcUL
    uint32_t : 32;                // offset 0x400UL
    uint32_t : 32;                // offset 0x404UL
    uint32_t : 32;                // offset 0x408UL
    uint32_t : 32;                // offset 0x40cUL
    uint32_t : 32;                // offset 0x410UL
    uint32_t : 32;                // offset 0x414UL
    uint32_t : 32;                // offset 0x418UL
    uint32_t : 32;                // offset 0x41cUL
    uint32_t : 32;                // offset 0x420UL
    uint32_t : 32;                // offset 0x424UL
    uint32_t : 32;                // offset 0x428UL
    uint32_t : 32;                // offset 0x42cUL
    uint32_t : 32;                // offset 0x430UL
    uint32_t : 32;                // offset 0x434UL
    uint32_t : 32;                // offset 0x438UL
    uint32_t : 32;                // offset 0x43cUL
    uint32_t : 32;                // offset 0x440UL
    uint32_t : 32;                // offset 0x444UL
    uint32_t : 32;                // offset 0x448UL
    uint32_t : 32;                // offset 0x44cUL
    uint32_t : 32;                // offset 0x450UL
    uint32_t : 32;                // offset 0x454UL
    uint32_t : 32;                // offset 0x458UL
    uint32_t : 32;                // offset 0x45cUL
    uint32_t : 32;                // offset 0x460UL
    uint32_t : 32;                // offset 0x464UL
    uint32_t : 32;                // offset 0x468UL
    uint32_t : 32;                // offset 0x46cUL
    uint32_t : 32;                // offset 0x470UL
    uint32_t : 32;                // offset 0x474UL
    uint32_t : 32;                // offset 0x478UL
    uint32_t : 32;                // offset 0x47cUL
    uint32_t : 32;                // offset 0x480UL
    uint32_t : 32;                // offset 0x484UL
    uint32_t : 32;                // offset 0x488UL
    uint32_t : 32;                // offset 0x48cUL
    uint32_t : 32;                // offset 0x490UL
    uint32_t : 32;                // offset 0x494UL
    uint32_t : 32;                // offset 0x498UL
    uint32_t : 32;                // offset 0x49cUL
    uint32_t : 32;                // offset 0x4a0UL
    uint32_t : 32;                // offset 0x4a4UL
    uint32_t : 32;                // offset 0x4a8UL
    uint32_t : 32;                // offset 0x4acUL
    uint32_t : 32;                // offset 0x4b0UL
    uint32_t : 32;                // offset 0x4b4UL
    uint32_t : 32;                // offset 0x4b8UL
    uint32_t : 32;                // offset 0x4bcUL
    uint32_t : 32;                // offset 0x4c0UL
    uint32_t : 32;                // offset 0x4c4UL
    uint32_t : 32;                // offset 0x4c8UL
    uint32_t : 32;                // offset 0x4ccUL
    uint32_t : 32;                // offset 0x4d0UL
    uint32_t : 32;                // offset 0x4d4UL
    uint32_t : 32;                // offset 0x4d8UL
    uint32_t : 32;                // offset 0x4dcUL
    uint32_t : 32;                // offset 0x4e0UL
    uint32_t : 32;                // offset 0x4e4UL
    uint32_t : 32;                // offset 0x4e8UL
    uint32_t : 32;                // offset 0x4ecUL
    uint32_t : 32;                // offset 0x4f0UL
    uint32_t : 32;                // offset 0x4f4UL
    uint32_t : 32;                // offset 0x4f8UL
    uint32_t : 32;                // offset 0x4fcUL
    uint32_t : 32;                // offset 0x500UL
    uint32_t : 32;                // offset 0x504UL
    uint32_t : 32;                // offset 0x508UL
    uint32_t : 32;                // offset 0x50cUL
    uint32_t : 32;                // offset 0x510UL
    uint32_t : 32;                // offset 0x514UL
    uint32_t : 32;                // offset 0x518UL
    uint32_t : 32;                // offset 0x51cUL
    uint32_t : 32;                // offset 0x520UL
    uint32_t : 32;                // offset 0x524UL
    uint32_t : 32;                // offset 0x528UL
    uint32_t : 32;                // offset 0x52cUL
    uint32_t : 32;                // offset 0x530UL
    uint32_t : 32;                // offset 0x534UL
    uint32_t : 32;                // offset 0x538UL
    uint32_t : 32;                // offset 0x53cUL
    uint32_t : 32;                // offset 0x540UL
    uint32_t : 32;                // offset 0x544UL
    uint32_t : 32;                // offset 0x548UL
    uint32_t : 32;                // offset 0x54cUL
    uint32_t : 32;                // offset 0x550UL
    uint32_t : 32;                // offset 0x554UL
    uint32_t : 32;                // offset 0x558UL
    uint32_t : 32;                // offset 0x55cUL
    uint32_t : 32;                // offset 0x560UL
    uint32_t : 32;                // offset 0x564UL
    uint32_t : 32;                // offset 0x568UL
    uint32_t : 32;                // offset 0x56cUL
    uint32_t : 32;                // offset 0x570UL
    uint32_t : 32;                // offset 0x574UL
    uint32_t : 32;                // offset 0x578UL
    uint32_t : 32;                // offset 0x57cUL
    uint32_t : 32;                // offset 0x580UL
    uint32_t : 32;                // offset 0x584UL
    uint32_t : 32;                // offset 0x588UL
    uint32_t : 32;                // offset 0x58cUL
    uint32_t : 32;                // offset 0x590UL
    uint32_t : 32;                // offset 0x594UL
    uint32_t : 32;                // offset 0x598UL
    uint32_t : 32;                // offset 0x59cUL
    uint32_t : 32;                // offset 0x5a0UL
    uint32_t : 32;                // offset 0x5a4UL
    uint32_t : 32;                // offset 0x5a8UL
    uint32_t : 32;                // offset 0x5acUL
    uint32_t : 32;                // offset 0x5b0UL
    uint32_t : 32;                // offset 0x5b4UL
    uint32_t : 32;                // offset 0x5b8UL
    uint32_t : 32;                // offset 0x5bcUL
    uint32_t : 32;                // offset 0x5c0UL
    uint32_t : 32;                // offset 0x5c4UL
    uint32_t : 32;                // offset 0x5c8UL
    uint32_t : 32;                // offset 0x5ccUL
    uint32_t : 32;                // offset 0x5d0UL
    uint32_t : 32;                // offset 0x5d4UL
    uint32_t : 32;                // offset 0x5d8UL
    uint32_t : 32;                // offset 0x5dcUL
    uint32_t : 32;                // offset 0x5e0UL
    uint32_t : 32;                // offset 0x5e4UL
    uint32_t : 32;                // offset 0x5e8UL
    uint32_t : 32;                // offset 0x5ecUL
    uint32_t : 32;                // offset 0x5f0UL
    uint32_t : 32;                // offset 0x5f4UL
    uint32_t : 32;                // offset 0x5f8UL
    uint32_t : 32;                // offset 0x5fcUL
    uint32_t : 32;                // offset 0x600UL
    uint32_t : 32;                // offset 0x604UL
    uint32_t : 32;                // offset 0x608UL
    uint32_t : 32;                // offset 0x60cUL
    uint32_t : 32;                // offset 0x610UL
    uint32_t : 32;                // offset 0x614UL
    uint32_t : 32;                // offset 0x618UL
    uint32_t : 32;                // offset 0x61cUL
    uint32_t : 32;                // offset 0x620UL
    uint32_t : 32;                // offset 0x624UL
    uint32_t : 32;                // offset 0x628UL
    uint32_t : 32;                // offset 0x62cUL
    uint32_t : 32;                // offset 0x630UL
    uint32_t : 32;                // offset 0x634UL
    uint32_t : 32;                // offset 0x638UL
    uint32_t : 32;                // offset 0x63cUL
    uint32_t : 32;                // offset 0x640UL
    uint32_t : 32;                // offset 0x644UL
    uint32_t : 32;                // offset 0x648UL
    uint32_t : 32;                // offset 0x64cUL
    uint32_t : 32;                // offset 0x650UL
    uint32_t : 32;                // offset 0x654UL
    uint32_t : 32;                // offset 0x658UL
    uint32_t : 32;                // offset 0x65cUL
    uint32_t : 32;                // offset 0x660UL
    uint32_t : 32;                // offset 0x664UL
    uint32_t : 32;                // offset 0x668UL
    uint32_t : 32;                // offset 0x66cUL
    uint32_t : 32;                // offset 0x670UL
    uint32_t : 32;                // offset 0x674UL
    uint32_t : 32;                // offset 0x678UL
    uint32_t : 32;                // offset 0x67cUL
    uint32_t : 32;                // offset 0x680UL
    uint32_t : 32;                // offset 0x684UL
    uint32_t : 32;                // offset 0x688UL
    uint32_t : 32;                // offset 0x68cUL
    uint32_t : 32;                // offset 0x690UL
    uint32_t : 32;                // offset 0x694UL
    uint32_t : 32;                // offset 0x698UL
    uint32_t : 32;                // offset 0x69cUL
    uint32_t : 32;                // offset 0x6a0UL
    uint32_t : 32;                // offset 0x6a4UL
    uint32_t : 32;                // offset 0x6a8UL
    uint32_t : 32;                // offset 0x6acUL
    uint32_t : 32;                // offset 0x6b0UL
    uint32_t : 32;                // offset 0x6b4UL
    uint32_t : 32;                // offset 0x6b8UL
    uint32_t : 32;                // offset 0x6bcUL
    uint32_t : 32;                // offset 0x6c0UL
    uint32_t : 32;                // offset 0x6c4UL
    uint32_t : 32;                // offset 0x6c8UL
    uint32_t : 32;                // offset 0x6ccUL
    uint32_t : 32;                // offset 0x6d0UL
    uint32_t : 32;                // offset 0x6d4UL
    uint32_t : 32;                // offset 0x6d8UL
    uint32_t : 32;                // offset 0x6dcUL
    uint32_t : 32;                // offset 0x6e0UL
    uint32_t : 32;                // offset 0x6e4UL
    uint32_t : 32;                // offset 0x6e8UL
    uint32_t : 32;                // offset 0x6ecUL
    uint32_t : 32;                // offset 0x6f0UL
    uint32_t : 32;                // offset 0x6f4UL
    uint32_t : 32;                // offset 0x6f8UL
    uint32_t : 32;                // offset 0x6fcUL
    /// MMC control register (MMC_CONTROL)
    MMCControl mmc_control;    // offset 0x700UL
    /// MMC Rx interrupt register (MMC_RX_INTERRUPT)
    MMCReceiveInterrupt mmc_receive_interrupt;    // offset 0x704UL
    /// MMC Tx interrupt register (MMC_TX_INTERRUPT)
    MMCTransmitInterrupt mmc_transmit_interrupt;    // offset 0x708UL
    /// MMC Rx interrupt mask register (MMC_RX_INTERRUPT_MASK)
    MMCReceiveInterruptMask mmc_receive_interrupt_mask;    // offset 0x70cUL
    /// MMC Tx interrupt mask register (MMC_TX_INTERRUPT_MASK)
    MMCTransmitInterruptMask mmc_transmit_interrupt_mask;    // offset 0x710UL
    uint32_t : 32;                                           // offset 0x714UL
    uint32_t : 32;                                           // offset 0x718UL
    uint32_t : 32;                                           // offset 0x71cUL
    uint32_t : 32;                                           // offset 0x720UL
    uint32_t : 32;                                           // offset 0x724UL
    uint32_t : 32;                                           // offset 0x728UL
    uint32_t : 32;                                           // offset 0x72cUL
    uint32_t : 32;                                           // offset 0x730UL
    uint32_t : 32;                                           // offset 0x734UL
    uint32_t : 32;                                           // offset 0x738UL
    uint32_t : 32;                                           // offset 0x73cUL
    uint32_t : 32;                                           // offset 0x740UL
    uint32_t : 32;                                           // offset 0x744UL
    uint32_t : 32;                                           // offset 0x748UL
    /// Tx single collision good packets register (TX_SINGLE_COLLISION_GOOD_PACKETS)
    TransmitSingleCollisionGoodPackets transmit_single_collision_good_packets;    // offset 0x74cUL
    /// Tx multiple collision good packets register (TX_MULTIPLE_COLLISION_GOOD_PACKETS)
    TransmitMultipleCollisionGoodPackets transmit_multiple_collision_good_packets;    // offset 0x750UL
    uint32_t : 32;                                                                    // offset 0x754UL
    uint32_t : 32;                                                                    // offset 0x758UL
    uint32_t : 32;                                                                    // offset 0x75cUL
    uint32_t : 32;                                                                    // offset 0x760UL
    uint32_t : 32;                                                                    // offset 0x764UL
    /// Tx packet count good register (TX_PACKET_COUNT_GOOD)
    TransmitPacketCountGood transmit_packet_count_good;    // offset 0x768UL
    uint32_t : 32;                                         // offset 0x76cUL
    uint32_t : 32;                                         // offset 0x770UL
    uint32_t : 32;                                         // offset 0x774UL
    uint32_t : 32;                                         // offset 0x778UL
    uint32_t : 32;                                         // offset 0x77cUL
    uint32_t : 32;                                         // offset 0x780UL
    uint32_t : 32;                                         // offset 0x784UL
    uint32_t : 32;                                         // offset 0x788UL
    uint32_t : 32;                                         // offset 0x78cUL
    uint32_t : 32;                                         // offset 0x790UL
    /// Rx CRC error packets register (RX_CRC_ERROR_PACKETS)
    ReceiveCRCErrorPackets receive_crc_error_packets;    // offset 0x794UL
    /// Rx alignment error packets register (RX_ALIGNMENT_ERROR_PACKETS)
    ReceiveAlignmentErrorPackets receive_alignment_error_packets;    // offset 0x798UL
    uint32_t : 32;                                                   // offset 0x79cUL
    uint32_t : 32;                                                   // offset 0x7a0UL
    uint32_t : 32;                                                   // offset 0x7a4UL
    uint32_t : 32;                                                   // offset 0x7a8UL
    uint32_t : 32;                                                   // offset 0x7acUL
    uint32_t : 32;                                                   // offset 0x7b0UL
    uint32_t : 32;                                                   // offset 0x7b4UL
    uint32_t : 32;                                                   // offset 0x7b8UL
    uint32_t : 32;                                                   // offset 0x7bcUL
    uint32_t : 32;                                                   // offset 0x7c0UL
    /// Rx unicast packets good register (RX_UNICAST_PACKETS_GOOD)
    ReceiveUnicastPacketsGood receive_unicast_packets_good;    // offset 0x7c4UL
    uint32_t : 32;                                             // offset 0x7c8UL
    uint32_t : 32;                                             // offset 0x7ccUL
    uint32_t : 32;                                             // offset 0x7d0UL
    uint32_t : 32;                                             // offset 0x7d4UL
    uint32_t : 32;                                             // offset 0x7d8UL
    uint32_t : 32;                                             // offset 0x7dcUL
    uint32_t : 32;                                             // offset 0x7e0UL
    uint32_t : 32;                                             // offset 0x7e4UL
    uint32_t : 32;                                             // offset 0x7e8UL
    /// Tx LPI microsecond timer register (TX_LPI_USEC_CNTR)
    TransmitLPIUsecCounter transmit_lpi_usec_counter;    // offset 0x7ecUL
    /// Tx LPI transition counter register (TX_LPI_TRAN_CNTR)
    TransmitLPITranCounter transmit_lpi_tran_counter;    // offset 0x7f0UL
    /// Rx LPI microsecond counter register (RX_LPI_USEC_CNTR)
    ReceiveLPIUsecCounter receive_lpi_usec_counter;    // offset 0x7f4UL
    /// Rx LPI transition counter register (RX_LPI_TRAN_CNTR)
    ReceiveLPITranCounter receive_lpi_tran_counter;    // offset 0x7f8UL
    uint32_t : 32;                                     // offset 0x7fcUL
    uint32_t : 32;                                     // offset 0x800UL
    uint32_t : 32;                                     // offset 0x804UL
    uint32_t : 32;                                     // offset 0x808UL
    uint32_t : 32;                                     // offset 0x80cUL
    uint32_t : 32;                                     // offset 0x810UL
    uint32_t : 32;                                     // offset 0x814UL
    uint32_t : 32;                                     // offset 0x818UL
    uint32_t : 32;                                     // offset 0x81cUL
    uint32_t : 32;                                     // offset 0x820UL
    uint32_t : 32;                                     // offset 0x824UL
    uint32_t : 32;                                     // offset 0x828UL
    uint32_t : 32;                                     // offset 0x82cUL
    uint32_t : 32;                                     // offset 0x830UL
    uint32_t : 32;                                     // offset 0x834UL
    uint32_t : 32;                                     // offset 0x838UL
    uint32_t : 32;                                     // offset 0x83cUL
    uint32_t : 32;                                     // offset 0x840UL
    uint32_t : 32;                                     // offset 0x844UL
    uint32_t : 32;                                     // offset 0x848UL
    uint32_t : 32;                                     // offset 0x84cUL
    uint32_t : 32;                                     // offset 0x850UL
    uint32_t : 32;                                     // offset 0x854UL
    uint32_t : 32;                                     // offset 0x858UL
    uint32_t : 32;                                     // offset 0x85cUL
    uint32_t : 32;                                     // offset 0x860UL
    uint32_t : 32;                                     // offset 0x864UL
    uint32_t : 32;                                     // offset 0x868UL
    uint32_t : 32;                                     // offset 0x86cUL
    uint32_t : 32;                                     // offset 0x870UL
    uint32_t : 32;                                     // offset 0x874UL
    uint32_t : 32;                                     // offset 0x878UL
    uint32_t : 32;                                     // offset 0x87cUL
    uint32_t : 32;                                     // offset 0x880UL
    uint32_t : 32;                                     // offset 0x884UL
    uint32_t : 32;                                     // offset 0x888UL
    uint32_t : 32;                                     // offset 0x88cUL
    uint32_t : 32;                                     // offset 0x890UL
    uint32_t : 32;                                     // offset 0x894UL
    uint32_t : 32;                                     // offset 0x898UL
    uint32_t : 32;                                     // offset 0x89cUL
    uint32_t : 32;                                     // offset 0x8a0UL
    uint32_t : 32;                                     // offset 0x8a4UL
    uint32_t : 32;                                     // offset 0x8a8UL
    uint32_t : 32;                                     // offset 0x8acUL
    uint32_t : 32;                                     // offset 0x8b0UL
    uint32_t : 32;                                     // offset 0x8b4UL
    uint32_t : 32;                                     // offset 0x8b8UL
    uint32_t : 32;                                     // offset 0x8bcUL
    uint32_t : 32;                                     // offset 0x8c0UL
    uint32_t : 32;                                     // offset 0x8c4UL
    uint32_t : 32;                                     // offset 0x8c8UL
    uint32_t : 32;                                     // offset 0x8ccUL
    uint32_t : 32;                                     // offset 0x8d0UL
    uint32_t : 32;                                     // offset 0x8d4UL
    uint32_t : 32;                                     // offset 0x8d8UL
    uint32_t : 32;                                     // offset 0x8dcUL
    uint32_t : 32;                                     // offset 0x8e0UL
    uint32_t : 32;                                     // offset 0x8e4UL
    uint32_t : 32;                                     // offset 0x8e8UL
    uint32_t : 32;                                     // offset 0x8ecUL
    uint32_t : 32;                                     // offset 0x8f0UL
    uint32_t : 32;                                     // offset 0x8f4UL
    uint32_t : 32;                                     // offset 0x8f8UL
    uint32_t : 32;                                     // offset 0x8fcUL
    /// L3 and L4 control 0 register (MACL3L4C0R)
    Layer3AndLayer4Control0 layer3_and_layer4_control_0;    // offset 0x900UL
    /// Layer4 address filter 0 register (MACL4A0R)
    Layer4AddressFilter0 layer4_address_filter_0;    // offset 0x904UL
    uint32_t : 32;                                   // offset 0x908UL
    uint32_t : 32;                                   // offset 0x90cUL
    /// MACL3A00R (MACL3A00R)
    Layer3Address0Filter0 layer3_address_0_filter_0;    // offset 0x910UL
    /// Layer3 address 1 filter 0 register (MACL3A10R)
    Layer3Address1Filter0 layer3_address_1_filter_0;    // offset 0x914UL
    /// Layer3 Address 2 filter 0 register (MACL3A20)
    Layer3Address2Filter0 layer3_address_2_filter_0;    // offset 0x918UL
    /// Layer3 Address 3 filter 0 register (MACL3A30)
    Layer3Address3Filter0 layer3_address_3_filter_0;    // offset 0x91cUL
    uint32_t : 32;                                      // offset 0x920UL
    uint32_t : 32;                                      // offset 0x924UL
    uint32_t : 32;                                      // offset 0x928UL
    uint32_t : 32;                                      // offset 0x92cUL
    /// L3 and L4 control 1 register (MACL3L4C1R)
    Layer3AndLayer4Control1 layer3_and_layer4_control_1;    // offset 0x930UL
    /// Layer 4 address filter 1 register (MACL4A1R)
    Layer4AddressFilter1 layer4_address_filter_1;    // offset 0x934UL
    uint32_t : 32;                                   // offset 0x938UL
    uint32_t : 32;                                   // offset 0x93cUL
    /// Layer3 address 0 filter 1 Register (MACL3A01R)
    Layer3Address0Filter1 layer3_address_0_filter_1;    // offset 0x940UL
    /// Layer3 address 1 filter 1 register (MACL3A11R)
    Layer3Address1Filter1 layer3_address_1_filter_1;    // offset 0x944UL
    /// Layer3 address 2 filter 1 Register (MACL3A21R)
    Layer3Address2Filter1 layer3_address_2_filter_1;    // offset 0x948UL
    /// Layer3 address 3 filter 1 register (MACL3A31R)
    Layer3Address3Filter1 layer3_address_3_filter_1;    // offset 0x94cUL
    uint32_t : 32;                                      // offset 0x950UL
    uint32_t : 32;                                      // offset 0x954UL
    uint32_t : 32;                                      // offset 0x958UL
    uint32_t : 32;                                      // offset 0x95cUL
    uint32_t : 32;                                      // offset 0x960UL
    uint32_t : 32;                                      // offset 0x964UL
    uint32_t : 32;                                      // offset 0x968UL
    uint32_t : 32;                                      // offset 0x96cUL
    uint32_t : 32;                                      // offset 0x970UL
    uint32_t : 32;                                      // offset 0x974UL
    uint32_t : 32;                                      // offset 0x978UL
    uint32_t : 32;                                      // offset 0x97cUL
    uint32_t : 32;                                      // offset 0x980UL
    uint32_t : 32;                                      // offset 0x984UL
    uint32_t : 32;                                      // offset 0x988UL
    uint32_t : 32;                                      // offset 0x98cUL
    uint32_t : 32;                                      // offset 0x990UL
    uint32_t : 32;                                      // offset 0x994UL
    uint32_t : 32;                                      // offset 0x998UL
    uint32_t : 32;                                      // offset 0x99cUL
    uint32_t : 32;                                      // offset 0x9a0UL
    uint32_t : 32;                                      // offset 0x9a4UL
    uint32_t : 32;                                      // offset 0x9a8UL
    uint32_t : 32;                                      // offset 0x9acUL
    uint32_t : 32;                                      // offset 0x9b0UL
    uint32_t : 32;                                      // offset 0x9b4UL
    uint32_t : 32;                                      // offset 0x9b8UL
    uint32_t : 32;                                      // offset 0x9bcUL
    uint32_t : 32;                                      // offset 0x9c0UL
    uint32_t : 32;                                      // offset 0x9c4UL
    uint32_t : 32;                                      // offset 0x9c8UL
    uint32_t : 32;                                      // offset 0x9ccUL
    uint32_t : 32;                                      // offset 0x9d0UL
    uint32_t : 32;                                      // offset 0x9d4UL
    uint32_t : 32;                                      // offset 0x9d8UL
    uint32_t : 32;                                      // offset 0x9dcUL
    uint32_t : 32;                                      // offset 0x9e0UL
    uint32_t : 32;                                      // offset 0x9e4UL
    uint32_t : 32;                                      // offset 0x9e8UL
    uint32_t : 32;                                      // offset 0x9ecUL
    uint32_t : 32;                                      // offset 0x9f0UL
    uint32_t : 32;                                      // offset 0x9f4UL
    uint32_t : 32;                                      // offset 0x9f8UL
    uint32_t : 32;                                      // offset 0x9fcUL
    uint32_t : 32;                                      // offset 0xa00UL
    uint32_t : 32;                                      // offset 0xa04UL
    uint32_t : 32;                                      // offset 0xa08UL
    uint32_t : 32;                                      // offset 0xa0cUL
    uint32_t : 32;                                      // offset 0xa10UL
    uint32_t : 32;                                      // offset 0xa14UL
    uint32_t : 32;                                      // offset 0xa18UL
    uint32_t : 32;                                      // offset 0xa1cUL
    uint32_t : 32;                                      // offset 0xa20UL
    uint32_t : 32;                                      // offset 0xa24UL
    uint32_t : 32;                                      // offset 0xa28UL
    uint32_t : 32;                                      // offset 0xa2cUL
    uint32_t : 32;                                      // offset 0xa30UL
    uint32_t : 32;                                      // offset 0xa34UL
    uint32_t : 32;                                      // offset 0xa38UL
    uint32_t : 32;                                      // offset 0xa3cUL
    uint32_t : 32;                                      // offset 0xa40UL
    uint32_t : 32;                                      // offset 0xa44UL
    uint32_t : 32;                                      // offset 0xa48UL
    uint32_t : 32;                                      // offset 0xa4cUL
    uint32_t : 32;                                      // offset 0xa50UL
    uint32_t : 32;                                      // offset 0xa54UL
    uint32_t : 32;                                      // offset 0xa58UL
    uint32_t : 32;                                      // offset 0xa5cUL
    uint32_t : 32;                                      // offset 0xa60UL
    uint32_t : 32;                                      // offset 0xa64UL
    uint32_t : 32;                                      // offset 0xa68UL
    uint32_t : 32;                                      // offset 0xa6cUL
    uint32_t : 32;                                      // offset 0xa70UL
    uint32_t : 32;                                      // offset 0xa74UL
    uint32_t : 32;                                      // offset 0xa78UL
    uint32_t : 32;                                      // offset 0xa7cUL
    uint32_t : 32;                                      // offset 0xa80UL
    uint32_t : 32;                                      // offset 0xa84UL
    uint32_t : 32;                                      // offset 0xa88UL
    uint32_t : 32;                                      // offset 0xa8cUL
    uint32_t : 32;                                      // offset 0xa90UL
    uint32_t : 32;                                      // offset 0xa94UL
    uint32_t : 32;                                      // offset 0xa98UL
    uint32_t : 32;                                      // offset 0xa9cUL
    uint32_t : 32;                                      // offset 0xaa0UL
    uint32_t : 32;                                      // offset 0xaa4UL
    uint32_t : 32;                                      // offset 0xaa8UL
    uint32_t : 32;                                      // offset 0xaacUL
    uint32_t : 32;                                      // offset 0xab0UL
    uint32_t : 32;                                      // offset 0xab4UL
    uint32_t : 32;                                      // offset 0xab8UL
    uint32_t : 32;                                      // offset 0xabcUL
    uint32_t : 32;                                      // offset 0xac0UL
    uint32_t : 32;                                      // offset 0xac4UL
    uint32_t : 32;                                      // offset 0xac8UL
    uint32_t : 32;                                      // offset 0xaccUL
    uint32_t : 32;                                      // offset 0xad0UL
    uint32_t : 32;                                      // offset 0xad4UL
    uint32_t : 32;                                      // offset 0xad8UL
    uint32_t : 32;                                      // offset 0xadcUL
    /// ARP address register (MACARPAR)
    ArpAddress arp_address;    // offset 0xae0UL
    uint32_t : 32;             // offset 0xae4UL
    uint32_t : 32;             // offset 0xae8UL
    uint32_t : 32;             // offset 0xaecUL
    uint32_t : 32;             // offset 0xaf0UL
    uint32_t : 32;             // offset 0xaf4UL
    uint32_t : 32;             // offset 0xaf8UL
    uint32_t : 32;             // offset 0xafcUL
    /// Timestamp control Register (MACTSCR)
    TimestampControl timestamp_control;    // offset 0xb00UL
    /// Sub-second increment register (MACSSIR)
    SubsecondIncrement subsecond_increment;    // offset 0xb04UL
    /// System time seconds register (MACSTSR)
    SystemTimeSeconds system_time_seconds;    // offset 0xb08UL
    /// System time nanoseconds register (MACSTNR)
    SystemTimeNanoseconds system_time_nanoseconds;    // offset 0xb0cUL
    /// System time seconds update register (MACSTSUR)
    SystemTimeSecondsUpdate system_time_seconds_update;    // offset 0xb10UL
    /// System time nanoseconds update register (MACSTNUR)
    SystemTimeNanosecondsUpdate system_time_nanoseconds_update;    // offset 0xb14UL
    /// Timestamp addend register (MACTSAR)
    TimestampAddend timestamp_addend;    // offset 0xb18UL
    uint32_t : 32;                       // offset 0xb1cUL
    /// Timestamp status register (MACTSSR)
    TimestampStatus timestamp_status;    // offset 0xb20UL
    uint32_t : 32;                       // offset 0xb24UL
    uint32_t : 32;                       // offset 0xb28UL
    uint32_t : 32;                       // offset 0xb2cUL
    /// Tx timestamp status nanoseconds register (MACTxTSSNR)
    TransmitTimestampStatusNanoseconds transmit_timestamp_status_nanoseconds;    // offset 0xb30UL
    /// Tx timestamp status seconds register (MACTxTSSSR)
    TransmitTimestampStatusSeconds transmit_timestamp_status_seconds;    // offset 0xb34UL
    uint32_t : 32;                                                       // offset 0xb38UL
    uint32_t : 32;                                                       // offset 0xb3cUL
    /// Auxiliary control register (MACACR)
    AuxiliaryControl auxiliary_control;    // offset 0xb40UL
    uint32_t : 32;                         // offset 0xb44UL
    /// Auxiliary timestamp nanoseconds register (MACATSNR)
    AuxiliaryTimestampNanoseconds auxiliary_timestamp_nanoseconds;    // offset 0xb48UL
    /// Auxiliary timestamp seconds register (MACATSSR)
    AuxiliaryTimestampSeconds auxiliary_timestamp_seconds;    // offset 0xb4cUL
    /// Timestamp Ingress asymmetric correction register (MACTSIACR)
    TimestampIngressAsymmetricCorrection timestamp_ingress_asymmetric_correction;    // offset 0xb50UL
    /// Timestamp Egress asymmetric correction register (MACTSEACR)
    TimestampEgressAsymmetricCorrection timestamp_egress_asymmetric_correction;    // offset 0xb54UL
    /// Timestamp Ingress correction nanosecond register (MACTSICNR)
    TimestampIngressCorrectionNanoseconds timestamp_ingress_correction_nanoseconds;    // offset 0xb58UL
    /// Timestamp Egress correction nanosecond register (MACTSECNR)
    TimestampEgressCorrectionNanoseconds timestamp_egress_correction_nanoseconds;    // offset 0xb5cUL
    uint32_t : 32;                                                                   // offset 0xb60UL
    uint32_t : 32;                                                                   // offset 0xb64UL
    uint32_t : 32;                                                                   // offset 0xb68UL
    uint32_t : 32;                                                                   // offset 0xb6cUL
    /// PPS control register (MACPPSCR)
    PulsePerSecondControl pulse_per_second_control;    // offset 0xb70UL
    uint32_t : 32;                                     // offset 0xb74UL
    uint32_t : 32;                                     // offset 0xb78UL
    uint32_t : 32;                                     // offset 0xb7cUL
    /// PPS target time seconds register (MACPPSTTSR)
    PulsePerSecondTargetTimeSeconds pulse_per_second_target_time_seconds;    // offset 0xb80UL
    /// PPS target time nanoseconds register (MACPPSTTNR)
    PulsePerSecondTargetTimeNanoseconds pulse_per_second_target_time_nanoseconds;    // offset 0xb84UL
    /// PPS interval register (MACPPSIR)
    PulsePerSecondInterval pulse_per_second_interval;    // offset 0xb88UL
    /// PPS width register (MACPPSWR)
    PulsePerSecondWidth pulse_per_second_width;    // offset 0xb8cUL
    uint32_t : 32;                                 // offset 0xb90UL
    uint32_t : 32;                                 // offset 0xb94UL
    uint32_t : 32;                                 // offset 0xb98UL
    uint32_t : 32;                                 // offset 0xb9cUL
    uint32_t : 32;                                 // offset 0xba0UL
    uint32_t : 32;                                 // offset 0xba4UL
    uint32_t : 32;                                 // offset 0xba8UL
    uint32_t : 32;                                 // offset 0xbacUL
    uint32_t : 32;                                 // offset 0xbb0UL
    uint32_t : 32;                                 // offset 0xbb4UL
    uint32_t : 32;                                 // offset 0xbb8UL
    uint32_t : 32;                                 // offset 0xbbcUL
    /// PTP Offload control register (MACPOCR)
    PrecisionTimeProtocolOffloadControl precision_time_protocol_offload_control;    // offset 0xbc0UL
    /// PTP Source Port Identity 0 Register (MACSPI0R)
    PrecisionTimeProtocolSourcePortIdentity0 precision_time_protocol_source_port_identity_0;    // offset 0xbc4UL
    /// PTP Source port identity 1 register (MACSPI1R)
    PrecisionTimeProtocolSourcePortIdentity1 precision_time_protocol_source_port_identity_1;    // offset 0xbc8UL
    /// PTP Source port identity 2 register (MACSPI2R)
    PrecisionTimeProtocolSourcePortIdentity2 precision_time_protocol_source_port_identity_2;    // offset 0xbccUL
    /// Log message interval register (MACLMIR)
    LogMessageInterval log_message_interval;    // offset 0xbd0UL
    uint32_t : 32;                              // offset 0xbd4UL
    uint32_t : 32;                              // offset 0xbd8UL
    uint32_t : 32;                              // offset 0xbdcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<EthernetMediaAccessController>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(EthernetMediaAccessController, operating_mode_configuration) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, extended_operating_mode_configuration) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, packet_filter_control) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, watchdog_timeout) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, hash_table_0) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, hash_table_1) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, vlan_tag) == 0x50UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, vlan_hash_table) == 0x58UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, vlan_inclusion) == 0x60UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, inner_vlan_inclusion) == 0x64UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, queue_transmit_flow_control) == 0x70UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_flow_control) == 0x90UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, interrupt_status) == 0xb0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, interrupt_enable) == 0xb4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_transmit_status) == 0xb8UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, power_management_control_status) == 0xc0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, remote_wakeup_packet_filter) == 0xc4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, low_power_idle_control_status) == 0xd0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, low_power_idle_timers_control) == 0xd4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, low_power_idle_entry_timer) == 0xd8UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, one_microsecond_tick_counter) == 0xdcUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, version) == 0x110UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, debug) == 0x114UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, hardware_feature_1) == 0x120UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, hardware_feature_2) == 0x124UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mdio_address) == 0x200UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mdio_data) == 0x204UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_0_high) == 0x300UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_0_low) == 0x304UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_1_high) == 0x308UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_1_low) == 0x30cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_2_high) == 0x310UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_2_low) == 0x314UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_3_high) == 0x318UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, address_3_low) == 0x31cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mmc_control) == 0x700UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mmc_receive_interrupt) == 0x704UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mmc_transmit_interrupt) == 0x708UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mmc_receive_interrupt_mask) == 0x70cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, mmc_transmit_interrupt_mask) == 0x710UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_single_collision_good_packets) == 0x74cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_multiple_collision_good_packets) == 0x750UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_packet_count_good) == 0x768UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_crc_error_packets) == 0x794UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_alignment_error_packets) == 0x798UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_unicast_packets_good) == 0x7c4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_lpi_usec_counter) == 0x7ecUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_lpi_tran_counter) == 0x7f0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_lpi_usec_counter) == 0x7f4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, receive_lpi_tran_counter) == 0x7f8UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_and_layer4_control_0) == 0x900UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer4_address_filter_0) == 0x904UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_0_filter_0) == 0x910UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_1_filter_0) == 0x914UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_2_filter_0) == 0x918UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_3_filter_0) == 0x91cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_and_layer4_control_1) == 0x930UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer4_address_filter_1) == 0x934UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_0_filter_1) == 0x940UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_1_filter_1) == 0x944UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_2_filter_1) == 0x948UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, layer3_address_3_filter_1) == 0x94cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, arp_address) == 0xae0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_control) == 0xb00UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, subsecond_increment) == 0xb04UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, system_time_seconds) == 0xb08UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, system_time_nanoseconds) == 0xb0cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, system_time_seconds_update) == 0xb10UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, system_time_nanoseconds_update) == 0xb14UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_addend) == 0xb18UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_status) == 0xb20UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_timestamp_status_nanoseconds) == 0xb30UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, transmit_timestamp_status_seconds) == 0xb34UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, auxiliary_control) == 0xb40UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, auxiliary_timestamp_nanoseconds) == 0xb48UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, auxiliary_timestamp_seconds) == 0xb4cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_ingress_asymmetric_correction) == 0xb50UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_egress_asymmetric_correction) == 0xb54UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_ingress_correction_nanoseconds) == 0xb58UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, timestamp_egress_correction_nanoseconds) == 0xb5cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, pulse_per_second_control) == 0xb70UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, pulse_per_second_target_time_seconds) == 0xb80UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, pulse_per_second_target_time_nanoseconds) == 0xb84UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, pulse_per_second_interval) == 0xb88UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, pulse_per_second_width) == 0xb8cUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, precision_time_protocol_offload_control) == 0xbc0UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, precision_time_protocol_source_port_identity_0) == 0xbc4UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, precision_time_protocol_source_port_identity_1) == 0xbc8UL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, precision_time_protocol_source_port_identity_2) == 0xbccUL, "Must be located at this offset");
static_assert(offsetof(EthernetMediaAccessController, log_message_interval) == 0xbd0UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(EthernetMediaAccessController) == 0xbe0UL, "Must be this exact size");

/// The external volatile ethernet_media_access_controller which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern EthernetMediaAccessController volatile ethernet_media_access_controller;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_ETHERNETMEDIAACCESSCONTROLLER__HPP_
