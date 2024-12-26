#ifndef STM32_REGISTERS_DIRECTMEMORYACCESS_HPP_
#define STM32_REGISTERS_DIRECTMEMORYACCESS_HPP_

/// @file
/// Auto Generated Structure Definitions for DirectMemoryAccess from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// DMA controller (DMA1)
struct DirectMemoryAccess final {
    /// low interrupt status register (LISR)
    struct LowInterruptStatus final {
        /// Default Constructor
        LowInterruptStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowInterruptStatus(LowInterruptStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowInterruptStatus(LowInterruptStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowInterruptStatus(LowInterruptStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowInterruptStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowInterruptStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowInterruptStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Stream x FIFO error interrupt flag (x=3..0) (FEIF0)
            uint32_t fifo_error_interrupt0        : 1;    // bit 0
            /// (reserved)
            uint32_t                              : 1;    // bit 1
            /// Stream x direct mode error interrupt flag (x=3..0) (DMEIF0)
            uint32_t direct_mode_error_interrupt0 : 1;    // bit 2
            /// Stream x transfer error interrupt flag (x=3..0) (TEIF0)
            uint32_t transfer_error_interrupt0    : 1;    // bit 3
            /// Stream x half transfer interrupt flag (x=3..0) (HTIF0)
            uint32_t half_transfer_interrupt0     : 1;    // bit 4
            /// Stream x transfer complete interrupt flag (x = 3..0) (TCIF0)
            uint32_t transfer_complete_interrupt0 : 1;    // bit 5
            /// Stream x FIFO error interrupt flag (x=3..0) (FEIF1)
            uint32_t fifo_error_interrupt1        : 1;    // bit 6
            /// (reserved)
            uint32_t                              : 1;    // bit 7
            /// Stream x direct mode error interrupt flag (x=3..0) (DMEIF1)
            uint32_t direct_mode_error_interrupt1 : 1;    // bit 8
            /// Stream x transfer error interrupt flag (x=3..0) (TEIF1)
            uint32_t transfer_error_interrupt1    : 1;    // bit 9
            /// Stream x half transfer interrupt flag (x=3..0) (HTIF1)
            uint32_t half_transfer_interrupt1     : 1;    // bit 10
            /// Stream x transfer complete interrupt flag (x = 3..0) (TCIF1)
            uint32_t transfer_complete_interrupt1 : 1;    // bit 11
            /// (reserved)
            uint32_t                              : 4;    // bits 12:15
            /// Stream x FIFO error interrupt flag (x=3..0) (FEIF2)
            uint32_t fifo_error_interrupt2        : 1;    // bit 16
            /// (reserved)
            uint32_t                              : 1;    // bit 17
            /// Stream x direct mode error interrupt flag (x=3..0) (DMEIF2)
            uint32_t direct_mode_error_interrupt2 : 1;    // bit 18
            /// Stream x transfer error interrupt flag (x=3..0) (TEIF2)
            uint32_t transfer_error_interrupt2    : 1;    // bit 19
            /// Stream x half transfer interrupt flag (x=3..0) (HTIF2)
            uint32_t half_transfer_interrupt2     : 1;    // bit 20
            /// Stream x transfer complete interrupt flag (x = 3..0) (TCIF2)
            uint32_t transfer_complete_interrupt2 : 1;    // bit 21
            /// Stream x FIFO error interrupt flag (x=3..0) (FEIF3)
            uint32_t fifo_error_interrupt3        : 1;    // bit 22
            /// (reserved)
            uint32_t                              : 1;    // bit 23
            /// Stream x direct mode error interrupt flag (x=3..0) (DMEIF3)
            uint32_t direct_mode_error_interrupt3 : 1;    // bit 24
            /// Stream x transfer error interrupt flag (x=3..0) (TEIF3)
            uint32_t transfer_error_interrupt3    : 1;    // bit 25
            /// Stream x half transfer interrupt flag (x=3..0) (HTIF3)
            uint32_t half_transfer_interrupt3     : 1;    // bit 26
            /// Stream x transfer complete interrupt flag (x = 3..0) (TCIF3)
            uint32_t transfer_complete_interrupt3 : 1;    // bit 27
            /// (reserved)
            uint32_t                              : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowInterruptStatus& operator=(LowInterruptStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowInterruptStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowInterruptStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LowInterruptStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowInterruptStatus) == 4UL, "Must be this exact size");
    /// high interrupt status register (HISR)
    struct HighInterruptStatus final {
        /// Default Constructor
        HighInterruptStatus()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HighInterruptStatus(HighInterruptStatus volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HighInterruptStatus(HighInterruptStatus const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HighInterruptStatus(HighInterruptStatus&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HighInterruptStatus(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HighInterruptStatus(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HighInterruptStatus() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Stream x FIFO error interrupt flag (x=7..4) (FEIF4)
            uint32_t fifo_error_interrupt4        : 1;    // bit 0
            /// (reserved)
            uint32_t                              : 1;    // bit 1
            /// Stream x direct mode error interrupt flag (x=7..4) (DMEIF4)
            uint32_t direct_mode_error_interrupt4 : 1;    // bit 2
            /// Stream x transfer error interrupt flag (x=7..4) (TEIF4)
            uint32_t transfer_error_interrupt4    : 1;    // bit 3
            /// Stream x half transfer interrupt flag (x=7..4) (HTIF4)
            uint32_t half_transfer_interrupt4     : 1;    // bit 4
            /// Stream x transfer complete interrupt flag (x=7..4) (TCIF4)
            uint32_t transfer_complete_interrupt4 : 1;    // bit 5
            /// Stream x FIFO error interrupt flag (x=7..4) (FEIF5)
            uint32_t fifo_error_interrupt5        : 1;    // bit 6
            /// (reserved)
            uint32_t                              : 1;    // bit 7
            /// Stream x direct mode error interrupt flag (x=7..4) (DMEIF5)
            uint32_t direct_mode_error_interrupt5 : 1;    // bit 8
            /// Stream x transfer error interrupt flag (x=7..4) (TEIF5)
            uint32_t transfer_error_interrupt5    : 1;    // bit 9
            /// Stream x half transfer interrupt flag (x=7..4) (HTIF5)
            uint32_t half_transfer_interrupt5     : 1;    // bit 10
            /// Stream x transfer complete interrupt flag (x=7..4) (TCIF5)
            uint32_t transfer_complete_interrupt5 : 1;    // bit 11
            /// (reserved)
            uint32_t                              : 4;    // bits 12:15
            /// Stream x FIFO error interrupt flag (x=7..4) (FEIF6)
            uint32_t fifo_error_interrupt6        : 1;    // bit 16
            /// (reserved)
            uint32_t                              : 1;    // bit 17
            /// Stream x direct mode error interrupt flag (x=7..4) (DMEIF6)
            uint32_t direct_mode_error_interrupt6 : 1;    // bit 18
            /// Stream x transfer error interrupt flag (x=7..4) (TEIF6)
            uint32_t transfer_error_interrupt6    : 1;    // bit 19
            /// Stream x half transfer interrupt flag (x=7..4) (HTIF6)
            uint32_t half_transfer_interrupt6     : 1;    // bit 20
            /// Stream x transfer complete interrupt flag (x=7..4) (TCIF6)
            uint32_t transfer_complete_interrupt6 : 1;    // bit 21
            /// Stream x FIFO error interrupt flag (x=7..4) (FEIF7)
            uint32_t fifo_error_interrupt7        : 1;    // bit 22
            /// (reserved)
            uint32_t                              : 1;    // bit 23
            /// Stream x direct mode error interrupt flag (x=7..4) (DMEIF7)
            uint32_t direct_mode_error_interrupt7 : 1;    // bit 24
            /// Stream x transfer error interrupt flag (x=7..4) (TEIF7)
            uint32_t transfer_error_interrupt7    : 1;    // bit 25
            /// Stream x half transfer interrupt flag (x=7..4) (HTIF7)
            uint32_t half_transfer_interrupt7     : 1;    // bit 26
            /// Stream x transfer complete interrupt flag (x=7..4) (TCIF7)
            uint32_t transfer_complete_interrupt7 : 1;    // bit 27
            /// (reserved)
            uint32_t                              : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HighInterruptStatus& operator=(HighInterruptStatus&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HighInterruptStatus volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HighInterruptStatus const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HighInterruptStatus>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HighInterruptStatus) == 4UL, "Must be this exact size");
    /// low interrupt flag clear register (LIFCR)
    struct LowInterruptFlagClear final {
        /// Default Constructor
        LowInterruptFlagClear()
            : whole{0u} {}
        /// Copy Constructor from volatile
        LowInterruptFlagClear(LowInterruptFlagClear volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        LowInterruptFlagClear(LowInterruptFlagClear const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        LowInterruptFlagClear(LowInterruptFlagClear&&) = delete;
        /// Parameterized Constructor for constant references
        explicit LowInterruptFlagClear(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit LowInterruptFlagClear(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~LowInterruptFlagClear() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Stream x clear FIFO error interrupt flag (x = 3..0) (CFEIF0)
            uint32_t clear_fifo_error_interrupt0        : 1;    // bit 0
            /// (reserved)
            uint32_t                                    : 1;    // bit 1
            /// Stream x clear direct mode error interrupt flag (x = 3..0) (CDMEIF0)
            uint32_t clear_direct_mode_error_interrupt0 : 1;    // bit 2
            /// Stream x clear transfer error interrupt flag (x = 3..0) (CTEIF0)
            uint32_t clear_transfer_error_interrupt0    : 1;    // bit 3
            /// Stream x clear half transfer interrupt flag (x = 3..0) (CHTIF0)
            uint32_t clear_half_transfer_interrupt0     : 1;    // bit 4
            /// Stream x clear transfer complete interrupt flag (x = 3..0) (CTCIF0)
            uint32_t clear_transfer_complete_interrupt0 : 1;    // bit 5
            /// Stream x clear FIFO error interrupt flag (x = 3..0) (CFEIF1)
            uint32_t clear_fifo_error_interrupt1        : 1;    // bit 6
            /// (reserved)
            uint32_t                                    : 1;    // bit 7
            /// Stream x clear direct mode error interrupt flag (x = 3..0) (CDMEIF1)
            uint32_t clear_direct_mode_error_interrupt1 : 1;    // bit 8
            /// Stream x clear transfer error interrupt flag (x = 3..0) (CTEIF1)
            uint32_t clear_transfer_error_interrupt1    : 1;    // bit 9
            /// Stream x clear half transfer interrupt flag (x = 3..0) (CHTIF1)
            uint32_t clear_half_transfer_interrupt1     : 1;    // bit 10
            /// Stream x clear transfer complete interrupt flag (x = 3..0) (CTCIF1)
            uint32_t clear_transfer_complete_interrupt1 : 1;    // bit 11
            /// (reserved)
            uint32_t                                    : 4;    // bits 12:15
            /// Stream x clear FIFO error interrupt flag (x = 3..0) (CFEIF2)
            uint32_t clear_fifo_error_interrupt2        : 1;    // bit 16
            /// (reserved)
            uint32_t                                    : 1;    // bit 17
            /// Stream x clear direct mode error interrupt flag (x = 3..0) (CDMEIF2)
            uint32_t clear_direct_mode_error_interrupt2 : 1;    // bit 18
            /// Stream x clear transfer error interrupt flag (x = 3..0) (CTEIF2)
            uint32_t clear_transfer_error_interrupt2    : 1;    // bit 19
            /// Stream x clear half transfer interrupt flag (x = 3..0) (CHTIF2)
            uint32_t clear_half_transfer_interrupt2     : 1;    // bit 20
            /// Stream x clear transfer complete interrupt flag (x = 3..0) (CTCIF2)
            uint32_t clear_transfer_complete_interrupt2 : 1;    // bit 21
            /// Stream x clear FIFO error interrupt flag (x = 3..0) (CFEIF3)
            uint32_t clear_fifo_error_interrupt3        : 1;    // bit 22
            /// (reserved)
            uint32_t                                    : 1;    // bit 23
            /// Stream x clear direct mode error interrupt flag (x = 3..0) (CDMEIF3)
            uint32_t clear_direct_mode_error_interrupt3 : 1;    // bit 24
            /// Stream x clear transfer error interrupt flag (x = 3..0) (CTEIF3)
            uint32_t clear_transfer_error_interrupt3    : 1;    // bit 25
            /// Stream x clear half transfer interrupt flag (x = 3..0) (CHTIF3)
            uint32_t clear_half_transfer_interrupt3     : 1;    // bit 26
            /// Stream x clear transfer complete interrupt flag (x = 3..0) (CTCIF3)
            uint32_t clear_transfer_complete_interrupt3 : 1;    // bit 27
            /// (reserved)
            uint32_t                                    : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        LowInterruptFlagClear& operator=(LowInterruptFlagClear&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(LowInterruptFlagClear volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(LowInterruptFlagClear const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<LowInterruptFlagClear>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(LowInterruptFlagClear) == 4UL, "Must be this exact size");
    /// high interrupt flag clear register (HIFCR)
    struct HighInterruptFlagClear final {
        /// Default Constructor
        HighInterruptFlagClear()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HighInterruptFlagClear(HighInterruptFlagClear volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HighInterruptFlagClear(HighInterruptFlagClear const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HighInterruptFlagClear(HighInterruptFlagClear&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HighInterruptFlagClear(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HighInterruptFlagClear(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HighInterruptFlagClear() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Stream x clear FIFO error interrupt flag (x = 7..4) (CFEIF4)
            uint32_t clear_fifo_error_interrupt4        : 1;    // bit 0
            /// (reserved)
            uint32_t                                    : 1;    // bit 1
            /// Stream x clear direct mode error interrupt flag (x = 7..4) (CDMEIF4)
            uint32_t clear_direct_mode_error_interrupt4 : 1;    // bit 2
            /// Stream x clear transfer error interrupt flag (x = 7..4) (CTEIF4)
            uint32_t clear_transfer_error_interrupt4    : 1;    // bit 3
            /// Stream x clear half transfer interrupt flag (x = 7..4) (CHTIF4)
            uint32_t clear_half_transfer_interrupt4     : 1;    // bit 4
            /// Stream x clear transfer complete interrupt flag (x = 7..4) (CTCIF4)
            uint32_t clear_transfer_complete_interrupt4 : 1;    // bit 5
            /// Stream x clear FIFO error interrupt flag (x = 7..4) (CFEIF5)
            uint32_t clear_fifo_error_interrupt5        : 1;    // bit 6
            /// (reserved)
            uint32_t                                    : 1;    // bit 7
            /// Stream x clear direct mode error interrupt flag (x = 7..4) (CDMEIF5)
            uint32_t clear_direct_mode_error_interrupt5 : 1;    // bit 8
            /// Stream x clear transfer error interrupt flag (x = 7..4) (CTEIF5)
            uint32_t clear_transfer_error_interrupt5    : 1;    // bit 9
            /// Stream x clear half transfer interrupt flag (x = 7..4) (CHTIF5)
            uint32_t clear_half_transfer_interrupt5     : 1;    // bit 10
            /// Stream x clear transfer complete interrupt flag (x = 7..4) (CTCIF5)
            uint32_t clear_transfer_complete_interrupt5 : 1;    // bit 11
            /// (reserved)
            uint32_t                                    : 4;    // bits 12:15
            /// Stream x clear FIFO error interrupt flag (x = 7..4) (CFEIF6)
            uint32_t clear_fifo_error_interrupt6        : 1;    // bit 16
            /// (reserved)
            uint32_t                                    : 1;    // bit 17
            /// Stream x clear direct mode error interrupt flag (x = 7..4) (CDMEIF6)
            uint32_t clear_direct_mode_error_interrupt6 : 1;    // bit 18
            /// Stream x clear transfer error interrupt flag (x = 7..4) (CTEIF6)
            uint32_t clear_transfer_error_interrupt6    : 1;    // bit 19
            /// Stream x clear half transfer interrupt flag (x = 7..4) (CHTIF6)
            uint32_t clear_half_transfer_interrupt6     : 1;    // bit 20
            /// Stream x clear transfer complete interrupt flag (x = 7..4) (CTCIF6)
            uint32_t clear_transfer_complete_interrupt6 : 1;    // bit 21
            /// Stream x clear FIFO error interrupt flag (x = 7..4) (CFEIF7)
            uint32_t clear_fifo_error_interrupt7        : 1;    // bit 22
            /// (reserved)
            uint32_t                                    : 1;    // bit 23
            /// Stream x clear direct mode error interrupt flag (x = 7..4) (CDMEIF7)
            uint32_t clear_direct_mode_error_interrupt7 : 1;    // bit 24
            /// Stream x clear transfer error interrupt flag (x = 7..4) (CTEIF7)
            uint32_t clear_transfer_error_interrupt7    : 1;    // bit 25
            /// Stream x clear half transfer interrupt flag (x = 7..4) (CHTIF7)
            uint32_t clear_half_transfer_interrupt7     : 1;    // bit 26
            /// Stream x clear transfer complete interrupt flag (x = 7..4) (CTCIF7)
            uint32_t clear_transfer_complete_interrupt7 : 1;    // bit 27
            /// (reserved)
            uint32_t                                    : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HighInterruptFlagClear& operator=(HighInterruptFlagClear&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HighInterruptFlagClear volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HighInterruptFlagClear const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HighInterruptFlagClear>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HighInterruptFlagClear) == 4UL, "Must be this exact size");
    /// @brief The Stream subcomponent
    struct Stream final {
        /// stream x configuration register (S0CR)
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

            enum class DataTransferDirection : uint32_t {
                PeripheralToMemory = 0b00,
                MemoryToPeripheral = 0b01,
                MemoryToMemory = 0b10
            };

            enum class DataSize : uint32_t {
                Bits8 = 0b00,
                Bits16 = 0b01,
                Bits32 = 0b10
            };

            enum class Priority : uint32_t {
                Low = 0b00,
                Medium = 0b01,
                High = 0b10,
                VeryHigh = 0b11
            };

            enum class Burst : uint32_t {
                Single = 0b00,
                Increment4 = 0b01,
                Increment8 = 0b10,
                Increment16 = 0b11
            };

            /// The internal bitfield for the register
            struct Fields final {
                /// Stream enable / flag stream ready when read low (EN)
                uint32_t stream_enable                        : 1;    // bit 0
                /// Direct mode error interrupt enable (DMEIE)
                uint32_t direct_mode_error_interrupt_enable   : 1;    // bit 1
                /// Transfer error interrupt enable (TEIE)
                uint32_t transfer_error_interrupt_enable      : 1;    // bit 2
                /// Half transfer interrupt enable (HTIE)
                uint32_t half_transfer_interrupt_enable       : 1;    // bit 3
                /// Transfer complete interrupt enable (TCIE)
                uint32_t transfer_complete_interrupt_enable   : 1;    // bit 4
                /// Peripheral flow controller (PFCTRL)
                uint32_t peripheral_flow_control              : 1;    // bit 5
                /// Data transfer direction (DIR)
                DataTransferDirection data_transfer_direction : 2;    // bits 6:7
                /// Circular mode (CIRC)
                uint32_t circular_mode                        : 1;    // bit 8
                /// Peripheral increment mode (PINC)
                uint32_t peripheral_increment_mode            : 1;    // bit 9
                /// Memory increment mode (MINC)
                uint32_t memory_increment_mode                : 1;    // bit 10
                /// Peripheral data size (PSIZE)
                DataSize peripheral_data_size                 : 2;    // bits 11:12
                /// Memory data size (MSIZE)
                DataSize memory_size                          : 2;    // bits 13:14
                /// Peripheral increment offset size (PINCOS)
                uint32_t peripheral_increment_offset_size     : 1;    // bit 15
                /// Priority level (PL)
                Priority priority_level                       : 2;    // bits 16:17
                /// Double buffer mode (DBM)
                uint32_t double_buffer_mode                   : 1;    // bit 18
                /// Current target (only in double buffer mode) (CT)
                uint32_t current_target                       : 1;    // bit 19
                /// (reserved)
                uint32_t                                      : 1;    // bit 20
                /// Peripheral burst transfer configuration (PBURST)
                Burst peripheral_burst                        : 2;    // bits 21:22
                /// Memory burst transfer configuration (MBURST)
                Burst memory_burst                            : 2;    // bits 23:24
                /// Channel selection (CHSEL)
                uint32_t channel_selection                    : 3;    // bits 25:27
                /// (reserved)
                uint32_t                                      : 4;    // bits 28:31
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
        /// stream x number of data register (S0NDTR)
        struct NumberOfDatum final {
            /// Default Constructor
            NumberOfDatum()
                : whole{0u} {}
            /// Copy Constructor from volatile
            NumberOfDatum(NumberOfDatum volatile const& other)
                : whole{other.whole} {}
            /// Copy Construction from nonvolatile
            NumberOfDatum(NumberOfDatum const& other)
                : whole{other.whole} {}
            /// Move Constructor is deleted
            NumberOfDatum(NumberOfDatum&&) = delete;
            /// Parameterized Constructor for constant references
            explicit NumberOfDatum(uint32_t const& value)
                : whole{value} {}
            /// Parameterized Constructor for volatile references
            explicit NumberOfDatum(uint32_t volatile& value)
                : whole{value} {}
            /// Destructor is empty
            ~NumberOfDatum() = default;

            /// The internal bitfield for the register
            struct Fields final {
                /// Number of data items to transfer (NDT)
                uint32_t number_of_datum : 16;    // bits 0:15
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
            NumberOfDatum& operator=(NumberOfDatum&&) = delete;
            /// Assignment from a volatile to a non volatile copy of the register.
            /// @note Does not return a reference
            inline void operator=(NumberOfDatum volatile& other) { whole = other.whole; }
            /// Assignment from a non volatile to a volatile register
            /// @note Does not return a reference
            inline void operator=(NumberOfDatum const& other) volatile { whole = other.whole; }
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
        static_assert(std::is_standard_layout<NumberOfDatum>::value, "Must be standard layout");
        // Ensure the sizeof the entire register is correct.
        static_assert(sizeof(NumberOfDatum) == 4UL, "Must be this exact size");

        /// stream x FIFO control register (S0FCR)
        struct FifoControl final {
            /// Default Constructor
            FifoControl()
                : whole{0u} {}
            /// Copy Constructor from volatile
            FifoControl(FifoControl volatile const& other)
                : whole{other.whole} {}
            /// Copy Construction from nonvolatile
            FifoControl(FifoControl const& other)
                : whole{other.whole} {}
            /// Move Constructor is deleted
            FifoControl(FifoControl&&) = delete;
            /// Parameterized Constructor for constant references
            explicit FifoControl(uint32_t const& value)
                : whole{value} {}
            /// Parameterized Constructor for volatile references
            explicit FifoControl(uint32_t volatile& value)
                : whole{value} {}
            /// Destructor is empty
            ~FifoControl() = default;

            enum class FifoThreshold : uint32_t {
                Empty = 0b00,
                Quarter = 0b01,
                Half = 0b10,
                Full = 0b11
            };

            enum class FifoStatus : uint32_t {
                ZeroToUnderQuarter = 0b000,
                QuarterToUnderHalf = 0b001,
                HalfToUnderThreeQuarters = 0b010,
                ThreeQuartersToUnderFull = 0b011,
                Empty = 0b100,
                Full = 0b101,
            };

            /// The internal bitfield for the register
            struct Fields final {
                /// FIFO threshold selection (FTH)
                FifoThreshold fifo_threshold         : 2;    // bits 0:1
                /// Direct mode disable (DMDIS)
                uint32_t direct_mode_disable         : 1;    // bit 2
                /// FIFO status (FS)
                FifoStatus fifo_status               : 3;    // bits 3:5
                /// (reserved)
                uint32_t                             : 1;    // bit 6
                /// FIFO error interrupt enable (FEIE)
                uint32_t fifo_error_interrupt_enable : 1;    // bit 7
                /// (reserved)
                uint32_t                             : 24;    // bits 8:31
            };
            //+=MEMORY======================================+
            union {
                Fields bits;
                uint32_t whole;
            };
            //+=MEMORY======================================+
            /// Move Assignment is deleted
            FifoControl& operator=(FifoControl&&) = delete;
            /// Assignment from a volatile to a non volatile copy of the register.
            /// @note Does not return a reference
            inline void operator=(FifoControl volatile& other) { whole = other.whole; }
            /// Assignment from a non volatile to a volatile register
            /// @note Does not return a reference
            inline void operator=(FifoControl const& other) volatile { whole = other.whole; }
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
        /// stream x configuration register (S0CR)
        Configuration configuration;    // offset 0x10UL
        /// stream x number of data register (S0NDTR)
        NumberOfDatum number_of_datum;    // offset 0x14UL
        /// stream x peripheral address register (S0PAR.PA)
        uintptr_t peripheral_address;    // offset 0x18UL
        /// stream x memory 0 address register (S0M0AR.M0A)
        uintptr_t memory0_address;    // offset 0x1cUL
        /// stream x memory 1 address register (S0M1AR.M1A)
        uintptr_t memory1_address;    // offset 0x20UL
        /// stream x FIFO control register (S0FCR)
        FifoControl fifo_control;    // offset 0x24UL
    };
#if defined(__arm__)
    static_assert(sizeof(Stream) == 0x18UL, "Stream is not the correct size");
#endif
    //+=MEMORY======================================+
    /// low interrupt status register (LISR)
    LowInterruptStatus low_interrupt_status;    // offset 0x0UL
    /// high interrupt status register (HISR)
    HighInterruptStatus high_interrupt_status;    // offset 0x4UL
    /// low interrupt flag clear register (LIFCR)
    LowInterruptFlagClear low_interrupt_flag_clear;    // offset 0x8UL
    /// high interrupt flag clear register (HIFCR)
    HighInterruptFlagClear high_interrupt_flag_clear;    // offset 0xcUL
    /// Stream Set
    Stream streams[8];    /// offset 0x10UL, size 0x18UL

    uint32_t : 32;    // offset 0xd0UL
    uint32_t : 32;    // offset 0xd4UL
    uint32_t : 32;    // offset 0xd8UL
    uint32_t : 32;    // offset 0xdcUL
    uint32_t : 32;    // offset 0xe0UL
    uint32_t : 32;    // offset 0xe4UL
    uint32_t : 32;    // offset 0xe8UL
    uint32_t : 32;    // offset 0xecUL
    uint32_t : 32;    // offset 0xf0UL
    uint32_t : 32;    // offset 0xf4UL
    uint32_t : 32;    // offset 0xf8UL
    uint32_t : 32;    // offset 0xfcUL
    uint32_t : 32;    // offset 0x100UL
    uint32_t : 32;    // offset 0x104UL
    uint32_t : 32;    // offset 0x108UL
    uint32_t : 32;    // offset 0x10cUL
    uint32_t : 32;    // offset 0x110UL
    uint32_t : 32;    // offset 0x114UL
    uint32_t : 32;    // offset 0x118UL
    uint32_t : 32;    // offset 0x11cUL
    uint32_t : 32;    // offset 0x120UL
    uint32_t : 32;    // offset 0x124UL
    uint32_t : 32;    // offset 0x128UL
    uint32_t : 32;    // offset 0x12cUL
    uint32_t : 32;    // offset 0x130UL
    uint32_t : 32;    // offset 0x134UL
    uint32_t : 32;    // offset 0x138UL
    uint32_t : 32;    // offset 0x13cUL
    uint32_t : 32;    // offset 0x140UL
    uint32_t : 32;    // offset 0x144UL
    uint32_t : 32;    // offset 0x148UL
    uint32_t : 32;    // offset 0x14cUL
    uint32_t : 32;    // offset 0x150UL
    uint32_t : 32;    // offset 0x154UL
    uint32_t : 32;    // offset 0x158UL
    uint32_t : 32;    // offset 0x15cUL
    uint32_t : 32;    // offset 0x160UL
    uint32_t : 32;    // offset 0x164UL
    uint32_t : 32;    // offset 0x168UL
    uint32_t : 32;    // offset 0x16cUL
    uint32_t : 32;    // offset 0x170UL
    uint32_t : 32;    // offset 0x174UL
    uint32_t : 32;    // offset 0x178UL
    uint32_t : 32;    // offset 0x17cUL
    uint32_t : 32;    // offset 0x180UL
    uint32_t : 32;    // offset 0x184UL
    uint32_t : 32;    // offset 0x188UL
    uint32_t : 32;    // offset 0x18cUL
    uint32_t : 32;    // offset 0x190UL
    uint32_t : 32;    // offset 0x194UL
    uint32_t : 32;    // offset 0x198UL
    uint32_t : 32;    // offset 0x19cUL
    uint32_t : 32;    // offset 0x1a0UL
    uint32_t : 32;    // offset 0x1a4UL
    uint32_t : 32;    // offset 0x1a8UL
    uint32_t : 32;    // offset 0x1acUL
    uint32_t : 32;    // offset 0x1b0UL
    uint32_t : 32;    // offset 0x1b4UL
    uint32_t : 32;    // offset 0x1b8UL
    uint32_t : 32;    // offset 0x1bcUL
    uint32_t : 32;    // offset 0x1c0UL
    uint32_t : 32;    // offset 0x1c4UL
    uint32_t : 32;    // offset 0x1c8UL
    uint32_t : 32;    // offset 0x1ccUL
    uint32_t : 32;    // offset 0x1d0UL
    uint32_t : 32;    // offset 0x1d4UL
    uint32_t : 32;    // offset 0x1d8UL
    uint32_t : 32;    // offset 0x1dcUL
    uint32_t : 32;    // offset 0x1e0UL
    uint32_t : 32;    // offset 0x1e4UL
    uint32_t : 32;    // offset 0x1e8UL
    uint32_t : 32;    // offset 0x1ecUL
    uint32_t : 32;    // offset 0x1f0UL
    uint32_t : 32;    // offset 0x1f4UL
    uint32_t : 32;    // offset 0x1f8UL
    uint32_t : 32;    // offset 0x1fcUL
    uint32_t : 32;    // offset 0x200UL
    uint32_t : 32;    // offset 0x204UL
    uint32_t : 32;    // offset 0x208UL
    uint32_t : 32;    // offset 0x20cUL
    uint32_t : 32;    // offset 0x210UL
    uint32_t : 32;    // offset 0x214UL
    uint32_t : 32;    // offset 0x218UL
    uint32_t : 32;    // offset 0x21cUL
    uint32_t : 32;    // offset 0x220UL
    uint32_t : 32;    // offset 0x224UL
    uint32_t : 32;    // offset 0x228UL
    uint32_t : 32;    // offset 0x22cUL
    uint32_t : 32;    // offset 0x230UL
    uint32_t : 32;    // offset 0x234UL
    uint32_t : 32;    // offset 0x238UL
    uint32_t : 32;    // offset 0x23cUL
    uint32_t : 32;    // offset 0x240UL
    uint32_t : 32;    // offset 0x244UL
    uint32_t : 32;    // offset 0x248UL
    uint32_t : 32;    // offset 0x24cUL
    uint32_t : 32;    // offset 0x250UL
    uint32_t : 32;    // offset 0x254UL
    uint32_t : 32;    // offset 0x258UL
    uint32_t : 32;    // offset 0x25cUL
    uint32_t : 32;    // offset 0x260UL
    uint32_t : 32;    // offset 0x264UL
    uint32_t : 32;    // offset 0x268UL
    uint32_t : 32;    // offset 0x26cUL
    uint32_t : 32;    // offset 0x270UL
    uint32_t : 32;    // offset 0x274UL
    uint32_t : 32;    // offset 0x278UL
    uint32_t : 32;    // offset 0x27cUL
    uint32_t : 32;    // offset 0x280UL
    uint32_t : 32;    // offset 0x284UL
    uint32_t : 32;    // offset 0x288UL
    uint32_t : 32;    // offset 0x28cUL
    uint32_t : 32;    // offset 0x290UL
    uint32_t : 32;    // offset 0x294UL
    uint32_t : 32;    // offset 0x298UL
    uint32_t : 32;    // offset 0x29cUL
    uint32_t : 32;    // offset 0x2a0UL
    uint32_t : 32;    // offset 0x2a4UL
    uint32_t : 32;    // offset 0x2a8UL
    uint32_t : 32;    // offset 0x2acUL
    uint32_t : 32;    // offset 0x2b0UL
    uint32_t : 32;    // offset 0x2b4UL
    uint32_t : 32;    // offset 0x2b8UL
    uint32_t : 32;    // offset 0x2bcUL
    uint32_t : 32;    // offset 0x2c0UL
    uint32_t : 32;    // offset 0x2c4UL
    uint32_t : 32;    // offset 0x2c8UL
    uint32_t : 32;    // offset 0x2ccUL
    uint32_t : 32;    // offset 0x2d0UL
    uint32_t : 32;    // offset 0x2d4UL
    uint32_t : 32;    // offset 0x2d8UL
    uint32_t : 32;    // offset 0x2dcUL
    uint32_t : 32;    // offset 0x2e0UL
    uint32_t : 32;    // offset 0x2e4UL
    uint32_t : 32;    // offset 0x2e8UL
    uint32_t : 32;    // offset 0x2ecUL
    uint32_t : 32;    // offset 0x2f0UL
    uint32_t : 32;    // offset 0x2f4UL
    uint32_t : 32;    // offset 0x2f8UL
    uint32_t : 32;    // offset 0x2fcUL
    uint32_t : 32;    // offset 0x300UL
    uint32_t : 32;    // offset 0x304UL
    uint32_t : 32;    // offset 0x308UL
    uint32_t : 32;    // offset 0x30cUL
    uint32_t : 32;    // offset 0x310UL
    uint32_t : 32;    // offset 0x314UL
    uint32_t : 32;    // offset 0x318UL
    uint32_t : 32;    // offset 0x31cUL
    uint32_t : 32;    // offset 0x320UL
    uint32_t : 32;    // offset 0x324UL
    uint32_t : 32;    // offset 0x328UL
    uint32_t : 32;    // offset 0x32cUL
    uint32_t : 32;    // offset 0x330UL
    uint32_t : 32;    // offset 0x334UL
    uint32_t : 32;    // offset 0x338UL
    uint32_t : 32;    // offset 0x33cUL
    uint32_t : 32;    // offset 0x340UL
    uint32_t : 32;    // offset 0x344UL
    uint32_t : 32;    // offset 0x348UL
    uint32_t : 32;    // offset 0x34cUL
    uint32_t : 32;    // offset 0x350UL
    uint32_t : 32;    // offset 0x354UL
    uint32_t : 32;    // offset 0x358UL
    uint32_t : 32;    // offset 0x35cUL
    uint32_t : 32;    // offset 0x360UL
    uint32_t : 32;    // offset 0x364UL
    uint32_t : 32;    // offset 0x368UL
    uint32_t : 32;    // offset 0x36cUL
    uint32_t : 32;    // offset 0x370UL
    uint32_t : 32;    // offset 0x374UL
    uint32_t : 32;    // offset 0x378UL
    uint32_t : 32;    // offset 0x37cUL
    uint32_t : 32;    // offset 0x380UL
    uint32_t : 32;    // offset 0x384UL
    uint32_t : 32;    // offset 0x388UL
    uint32_t : 32;    // offset 0x38cUL
    uint32_t : 32;    // offset 0x390UL
    uint32_t : 32;    // offset 0x394UL
    uint32_t : 32;    // offset 0x398UL
    uint32_t : 32;    // offset 0x39cUL
    uint32_t : 32;    // offset 0x3a0UL
    uint32_t : 32;    // offset 0x3a4UL
    uint32_t : 32;    // offset 0x3a8UL
    uint32_t : 32;    // offset 0x3acUL
    uint32_t : 32;    // offset 0x3b0UL
    uint32_t : 32;    // offset 0x3b4UL
    uint32_t : 32;    // offset 0x3b8UL
    uint32_t : 32;    // offset 0x3bcUL
    uint32_t : 32;    // offset 0x3c0UL
    uint32_t : 32;    // offset 0x3c4UL
    uint32_t : 32;    // offset 0x3c8UL
    uint32_t : 32;    // offset 0x3ccUL
    uint32_t : 32;    // offset 0x3d0UL
    uint32_t : 32;    // offset 0x3d4UL
    uint32_t : 32;    // offset 0x3d8UL
    uint32_t : 32;    // offset 0x3dcUL
    uint32_t : 32;    // offset 0x3e0UL
    uint32_t : 32;    // offset 0x3e4UL
    uint32_t : 32;    // offset 0x3e8UL
    uint32_t : 32;    // offset 0x3ecUL
    uint32_t : 32;    // offset 0x3f0UL
    uint32_t : 32;    // offset 0x3f4UL
    uint32_t : 32;    // offset 0x3f8UL
    uint32_t : 32;    // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<DirectMemoryAccess>::value, "Must be standard layout");
#if defined(__arm__)
// Ensure the offsets are all correct
static_assert(offsetof(DirectMemoryAccess, low_interrupt_status) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, high_interrupt_status) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, low_interrupt_flag_clear) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, high_interrupt_flag_clear) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].configuration) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].number_of_datum) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].peripheral_address) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].memory0_address) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].memory1_address) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(DirectMemoryAccess, streams[0].fifo_control) == 0x24UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(DirectMemoryAccess) == 0x400UL, "Must be this exact size");
#endif

static constexpr size_t NumberOfDmaControllers{2U};
static constexpr size_t NumberOfDmaStreamsPerController{8U};

/// The external volatile direct_memory_access which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern DirectMemoryAccess volatile direct_memory_access[NumberOfDmaControllers];
}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_DIRECTMEMORYACCESS1__HPP_