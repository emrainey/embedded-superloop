#ifndef STM32_REGISTERS_GENERALPURPOSEINPUTOUTPUT_HPP
#define STM32_REGISTERS_GENERALPURPOSEINPUTOUTPUT_HPP

/// @file
/// Auto Generated Structure Definitions for GeneralPurposeInputOutput from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// General-purpose I/Os (GeneralPurposeInputOutput)
struct GeneralPurposeInputOutput final {
    /// GPIO port mode register (Mode)
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
            /// Port x configuration bits (y = 0..15) (Mode0)
            uint32_t moder0  : 2;    // bits 0:1
            /// Port x configuration bits (y = 0..15) (Mode1)
            uint32_t moder1  : 2;    // bits 2:3
            /// Port x configuration bits (y = 0..15) (Mode2)
            uint32_t moder2  : 2;    // bits 4:5
            /// Port x configuration bits (y = 0..15) (Mode3)
            uint32_t moder3  : 2;    // bits 6:7
            /// Port x configuration bits (y = 0..15) (Mode4)
            uint32_t moder4  : 2;    // bits 8:9
            /// Port x configuration bits (y = 0..15) (Mode5)
            uint32_t moder5  : 2;    // bits 10:11
            /// Port x configuration bits (y = 0..15) (Mode6)
            uint32_t moder6  : 2;    // bits 12:13
            /// Port x configuration bits (y = 0..15) (Mode7)
            uint32_t moder7  : 2;    // bits 14:15
            /// Port x configuration bits (y = 0..15) (Mode8)
            uint32_t moder8  : 2;    // bits 16:17
            /// Port x configuration bits (y = 0..15) (Mode9)
            uint32_t moder9  : 2;    // bits 18:19
            /// Port x configuration bits (y = 0..15) (Mode10)
            uint32_t moder10 : 2;    // bits 20:21
            /// Port x configuration bits (y = 0..15) (Mode11)
            uint32_t moder11 : 2;    // bits 22:23
            /// Port x configuration bits (y = 0..15) (Mode12)
            uint32_t moder12 : 2;    // bits 24:25
            /// Port x configuration bits (y = 0..15) (Mode13)
            uint32_t moder13 : 2;    // bits 26:27
            /// Port x configuration bits (y = 0..15) (Mode14)
            uint32_t moder14 : 2;    // bits 28:29
            /// Port x configuration bits (y = 0..15) (Mode15)
            uint32_t moder15 : 2;    // bits 30:31
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
    /// GPIO port output type register (OutputType)
    struct OutputType final {
        /// Default Constructor
        OutputType()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OutputType(OutputType volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OutputType(OutputType const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OutputType(OutputType&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OutputType(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OutputType(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OutputType() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port x configuration bits (y = 0..15) (OT0)
            uint32_t ot0  : 1;    // bit 0
            /// Port x configuration bits (y = 0..15) (OT1)
            uint32_t ot1  : 1;    // bit 1
            /// Port x configuration bits (y = 0..15) (OT2)
            uint32_t ot2  : 1;    // bit 2
            /// Port x configuration bits (y = 0..15) (OT3)
            uint32_t ot3  : 1;    // bit 3
            /// Port x configuration bits (y = 0..15) (OT4)
            uint32_t ot4  : 1;    // bit 4
            /// Port x configuration bits (y = 0..15) (OT5)
            uint32_t ot5  : 1;    // bit 5
            /// Port x configuration bits (y = 0..15) (OT6)
            uint32_t ot6  : 1;    // bit 6
            /// Port x configuration bits (y = 0..15) (OT7)
            uint32_t ot7  : 1;    // bit 7
            /// Port x configuration bits (y = 0..15) (OT8)
            uint32_t ot8  : 1;    // bit 8
            /// Port x configuration bits (y = 0..15) (OT9)
            uint32_t ot9  : 1;    // bit 9
            /// Port x configuration bits (y = 0..15) (OT10)
            uint32_t ot10 : 1;    // bit 10
            /// Port x configuration bits (y = 0..15) (OT11)
            uint32_t ot11 : 1;    // bit 11
            /// Port x configuration bits (y = 0..15) (OT12)
            uint32_t ot12 : 1;    // bit 12
            /// Port x configuration bits (y = 0..15) (OT13)
            uint32_t ot13 : 1;    // bit 13
            /// Port x configuration bits (y = 0..15) (OT14)
            uint32_t ot14 : 1;    // bit 14
            /// Port x configuration bits (y = 0..15) (OT15)
            uint32_t ot15 : 1;    // bit 15
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
        OutputType& operator=(OutputType&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OutputType volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OutputType const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OutputType>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OutputType) == 4UL, "Must be this exact size");
    /// GPIO port output speed register (OutputSpeed)
    struct OutputSpeed final {
        /// Default Constructor
        OutputSpeed()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OutputSpeed(OutputSpeed volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OutputSpeed(OutputSpeed const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OutputSpeed(OutputSpeed&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OutputSpeed(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OutputSpeed(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OutputSpeed() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port x configuration bits (y = 0..15) (OutputSpeed0)
            uint32_t ospeedr0  : 2;    // bits 0:1
            /// Port x configuration bits (y = 0..15) (OutputSpeed1)
            uint32_t ospeedr1  : 2;    // bits 2:3
            /// Port x configuration bits (y = 0..15) (OutputSpeed2)
            uint32_t ospeedr2  : 2;    // bits 4:5
            /// Port x configuration bits (y = 0..15) (OutputSpeed3)
            uint32_t ospeedr3  : 2;    // bits 6:7
            /// Port x configuration bits (y = 0..15) (OutputSpeed4)
            uint32_t ospeedr4  : 2;    // bits 8:9
            /// Port x configuration bits (y = 0..15) (OutputSpeed5)
            uint32_t ospeedr5  : 2;    // bits 10:11
            /// Port x configuration bits (y = 0..15) (OutputSpeed6)
            uint32_t ospeedr6  : 2;    // bits 12:13
            /// Port x configuration bits (y = 0..15) (OutputSpeed7)
            uint32_t ospeedr7  : 2;    // bits 14:15
            /// Port x configuration bits (y = 0..15) (OutputSpeed8)
            uint32_t ospeedr8  : 2;    // bits 16:17
            /// Port x configuration bits (y = 0..15) (OutputSpeed9)
            uint32_t ospeedr9  : 2;    // bits 18:19
            /// Port x configuration bits (y = 0..15) (OutputSpeed10)
            uint32_t ospeedr10 : 2;    // bits 20:21
            /// Port x configuration bits (y = 0..15) (OutputSpeed11)
            uint32_t ospeedr11 : 2;    // bits 22:23
            /// Port x configuration bits (y = 0..15) (OutputSpeed12)
            uint32_t ospeedr12 : 2;    // bits 24:25
            /// Port x configuration bits (y = 0..15) (OutputSpeed13)
            uint32_t ospeedr13 : 2;    // bits 26:27
            /// Port x configuration bits (y = 0..15) (OutputSpeed14)
            uint32_t ospeedr14 : 2;    // bits 28:29
            /// Port x configuration bits (y = 0..15) (OutputSpeed15)
            uint32_t ospeedr15 : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OutputSpeed& operator=(OutputSpeed&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OutputSpeed volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OutputSpeed const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OutputSpeed>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OutputSpeed) == 4UL, "Must be this exact size");
    /// GPIO port pull-up/pull-down register (PullUpPullDown)
    struct PullUpPullDown final {
        /// Default Constructor
        PullUpPullDown()
            : whole{0u} {}
        /// Copy Constructor from volatile
        PullUpPullDown(PullUpPullDown volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        PullUpPullDown(PullUpPullDown const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        PullUpPullDown(PullUpPullDown&&) = delete;
        /// Parameterized Constructor for constant references
        explicit PullUpPullDown(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit PullUpPullDown(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~PullUpPullDown() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port x configuration bits (y = 0..15) (PullUpPullDown0)
            uint32_t pupdr0  : 2;    // bits 0:1
            /// Port x configuration bits (y = 0..15) (PullUpPullDown1)
            uint32_t pupdr1  : 2;    // bits 2:3
            /// Port x configuration bits (y = 0..15) (PullUpPullDown2)
            uint32_t pupdr2  : 2;    // bits 4:5
            /// Port x configuration bits (y = 0..15) (PullUpPullDown3)
            uint32_t pupdr3  : 2;    // bits 6:7
            /// Port x configuration bits (y = 0..15) (PullUpPullDown4)
            uint32_t pupdr4  : 2;    // bits 8:9
            /// Port x configuration bits (y = 0..15) (PullUpPullDown5)
            uint32_t pupdr5  : 2;    // bits 10:11
            /// Port x configuration bits (y = 0..15) (PullUpPullDown6)
            uint32_t pupdr6  : 2;    // bits 12:13
            /// Port x configuration bits (y = 0..15) (PullUpPullDown7)
            uint32_t pupdr7  : 2;    // bits 14:15
            /// Port x configuration bits (y = 0..15) (PullUpPullDown8)
            uint32_t pupdr8  : 2;    // bits 16:17
            /// Port x configuration bits (y = 0..15) (PullUpPullDown9)
            uint32_t pupdr9  : 2;    // bits 18:19
            /// Port x configuration bits (y = 0..15) (PullUpPullDown10)
            uint32_t pupdr10 : 2;    // bits 20:21
            /// Port x configuration bits (y = 0..15) (PullUpPullDown11)
            uint32_t pupdr11 : 2;    // bits 22:23
            /// Port x configuration bits (y = 0..15) (PullUpPullDown12)
            uint32_t pupdr12 : 2;    // bits 24:25
            /// Port x configuration bits (y = 0..15) (PullUpPullDown13)
            uint32_t pupdr13 : 2;    // bits 26:27
            /// Port x configuration bits (y = 0..15) (PullUpPullDown14)
            uint32_t pupdr14 : 2;    // bits 28:29
            /// Port x configuration bits (y = 0..15) (PullUpPullDown15)
            uint32_t pupdr15 : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        PullUpPullDown& operator=(PullUpPullDown&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(PullUpPullDown volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(PullUpPullDown const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<PullUpPullDown>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(PullUpPullDown) == 4UL, "Must be this exact size");
    /// GPIO port input data register (InputData)
    struct InputData final {
        /// Default Constructor
        InputData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InputData(InputData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InputData(InputData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InputData(InputData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InputData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InputData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InputData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port input data (y = 0..15) (InputData0)
            uint32_t idr0  : 1;    // bit 0
            /// Port input data (y = 0..15) (InputData1)
            uint32_t idr1  : 1;    // bit 1
            /// Port input data (y = 0..15) (InputData2)
            uint32_t idr2  : 1;    // bit 2
            /// Port input data (y = 0..15) (InputData3)
            uint32_t idr3  : 1;    // bit 3
            /// Port input data (y = 0..15) (InputData4)
            uint32_t idr4  : 1;    // bit 4
            /// Port input data (y = 0..15) (InputData5)
            uint32_t idr5  : 1;    // bit 5
            /// Port input data (y = 0..15) (InputData6)
            uint32_t idr6  : 1;    // bit 6
            /// Port input data (y = 0..15) (InputData7)
            uint32_t idr7  : 1;    // bit 7
            /// Port input data (y = 0..15) (InputData8)
            uint32_t idr8  : 1;    // bit 8
            /// Port input data (y = 0..15) (InputData9)
            uint32_t idr9  : 1;    // bit 9
            /// Port input data (y = 0..15) (InputData10)
            uint32_t idr10 : 1;    // bit 10
            /// Port input data (y = 0..15) (InputData11)
            uint32_t idr11 : 1;    // bit 11
            /// Port input data (y = 0..15) (InputData12)
            uint32_t idr12 : 1;    // bit 12
            /// Port input data (y = 0..15) (InputData13)
            uint32_t idr13 : 1;    // bit 13
            /// Port input data (y = 0..15) (InputData14)
            uint32_t idr14 : 1;    // bit 14
            /// Port input data (y = 0..15) (InputData15)
            uint32_t idr15 : 1;    // bit 15
            /// (reserved)
            uint32_t       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InputData& operator=(InputData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InputData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InputData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InputData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InputData) == 4UL, "Must be this exact size");
    /// GPIO port output data register (OutputData)
    struct OutputData final {
        /// Default Constructor
        OutputData()
            : whole{0u} {}
        /// Copy Constructor from volatile
        OutputData(OutputData volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        OutputData(OutputData const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        OutputData(OutputData&&) = delete;
        /// Parameterized Constructor for constant references
        explicit OutputData(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit OutputData(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~OutputData() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port output data (y = 0..15) (OutputData0)
            uint32_t odr0  : 1;    // bit 0
            /// Port output data (y = 0..15) (OutputData1)
            uint32_t odr1  : 1;    // bit 1
            /// Port output data (y = 0..15) (OutputData2)
            uint32_t odr2  : 1;    // bit 2
            /// Port output data (y = 0..15) (OutputData3)
            uint32_t odr3  : 1;    // bit 3
            /// Port output data (y = 0..15) (OutputData4)
            uint32_t odr4  : 1;    // bit 4
            /// Port output data (y = 0..15) (OutputData5)
            uint32_t odr5  : 1;    // bit 5
            /// Port output data (y = 0..15) (OutputData6)
            uint32_t odr6  : 1;    // bit 6
            /// Port output data (y = 0..15) (OutputData7)
            uint32_t odr7  : 1;    // bit 7
            /// Port output data (y = 0..15) (OutputData8)
            uint32_t odr8  : 1;    // bit 8
            /// Port output data (y = 0..15) (OutputData9)
            uint32_t odr9  : 1;    // bit 9
            /// Port output data (y = 0..15) (OutputData10)
            uint32_t odr10 : 1;    // bit 10
            /// Port output data (y = 0..15) (OutputData11)
            uint32_t odr11 : 1;    // bit 11
            /// Port output data (y = 0..15) (OutputData12)
            uint32_t odr12 : 1;    // bit 12
            /// Port output data (y = 0..15) (OutputData13)
            uint32_t odr13 : 1;    // bit 13
            /// Port output data (y = 0..15) (OutputData14)
            uint32_t odr14 : 1;    // bit 14
            /// Port output data (y = 0..15) (OutputData15)
            uint32_t odr15 : 1;    // bit 15
            /// (reserved)
            uint32_t       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        OutputData& operator=(OutputData&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(OutputData volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(OutputData const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<OutputData>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(OutputData) == 4UL, "Must be this exact size");
    /// GPIO port bit set/reset register (BitSetReset)
    struct BitSetReset final {
        /// Default Constructor
        BitSetReset()
            : whole{0u} {}
        /// Copy Constructor from volatile
        BitSetReset(BitSetReset volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        BitSetReset(BitSetReset const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        BitSetReset(BitSetReset&&) = delete;
        /// Parameterized Constructor for constant references
        explicit BitSetReset(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit BitSetReset(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~BitSetReset() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port x set bit y (y= 0..15) (BS0)
            uint32_t bs0  : 1;    // bit 0
            /// Port x set bit y (y= 0..15) (BS1)
            uint32_t bs1  : 1;    // bit 1
            /// Port x set bit y (y= 0..15) (BS2)
            uint32_t bs2  : 1;    // bit 2
            /// Port x set bit y (y= 0..15) (BS3)
            uint32_t bs3  : 1;    // bit 3
            /// Port x set bit y (y= 0..15) (BS4)
            uint32_t bs4  : 1;    // bit 4
            /// Port x set bit y (y= 0..15) (BS5)
            uint32_t bs5  : 1;    // bit 5
            /// Port x set bit y (y= 0..15) (BS6)
            uint32_t bs6  : 1;    // bit 6
            /// Port x set bit y (y= 0..15) (BS7)
            uint32_t bs7  : 1;    // bit 7
            /// Port x set bit y (y= 0..15) (BS8)
            uint32_t bs8  : 1;    // bit 8
            /// Port x set bit y (y= 0..15) (BS9)
            uint32_t bs9  : 1;    // bit 9
            /// Port x set bit y (y= 0..15) (BS10)
            uint32_t bs10 : 1;    // bit 10
            /// Port x set bit y (y= 0..15) (BS11)
            uint32_t bs11 : 1;    // bit 11
            /// Port x set bit y (y= 0..15) (BS12)
            uint32_t bs12 : 1;    // bit 12
            /// Port x set bit y (y= 0..15) (BS13)
            uint32_t bs13 : 1;    // bit 13
            /// Port x set bit y (y= 0..15) (BS14)
            uint32_t bs14 : 1;    // bit 14
            /// Port x set bit y (y= 0..15) (BS15)
            uint32_t bs15 : 1;    // bit 15
            /// Port x set bit y (y= 0..15) (BR0)
            uint32_t br0  : 1;    // bit 16
            /// Port x reset bit y (y = 0..15) (BR1)
            uint32_t br1  : 1;    // bit 17
            /// Port x reset bit y (y = 0..15) (BR2)
            uint32_t br2  : 1;    // bit 18
            /// Port x reset bit y (y = 0..15) (BR3)
            uint32_t br3  : 1;    // bit 19
            /// Port x reset bit y (y = 0..15) (BR4)
            uint32_t br4  : 1;    // bit 20
            /// Port x reset bit y (y = 0..15) (BR5)
            uint32_t br5  : 1;    // bit 21
            /// Port x reset bit y (y = 0..15) (BR6)
            uint32_t br6  : 1;    // bit 22
            /// Port x reset bit y (y = 0..15) (BR7)
            uint32_t br7  : 1;    // bit 23
            /// Port x reset bit y (y = 0..15) (BR8)
            uint32_t br8  : 1;    // bit 24
            /// Port x reset bit y (y = 0..15) (BR9)
            uint32_t br9  : 1;    // bit 25
            /// Port x reset bit y (y = 0..15) (BR10)
            uint32_t br10 : 1;    // bit 26
            /// Port x reset bit y (y = 0..15) (BR11)
            uint32_t br11 : 1;    // bit 27
            /// Port x reset bit y (y = 0..15) (BR12)
            uint32_t br12 : 1;    // bit 28
            /// Port x reset bit y (y = 0..15) (BR13)
            uint32_t br13 : 1;    // bit 29
            /// Port x reset bit y (y = 0..15) (BR14)
            uint32_t br14 : 1;    // bit 30
            /// Port x reset bit y (y = 0..15) (BR15)
            uint32_t br15 : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        BitSetReset& operator=(BitSetReset&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(BitSetReset volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(BitSetReset const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<BitSetReset>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(BitSetReset) == 4UL, "Must be this exact size");
    /// GPIO port configuration lock register (Lock)
    struct Lock final {
        /// Default Constructor
        Lock()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Lock(Lock volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Lock(Lock const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Lock(Lock&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Lock(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Lock(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Lock() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Port x lock bit y (y= 0..15) (LCK0)
            uint32_t lck0  : 1;    // bit 0
            /// Port x lock bit y (y= 0..15) (LCK1)
            uint32_t lck1  : 1;    // bit 1
            /// Port x lock bit y (y= 0..15) (LCK2)
            uint32_t lck2  : 1;    // bit 2
            /// Port x lock bit y (y= 0..15) (LCK3)
            uint32_t lck3  : 1;    // bit 3
            /// Port x lock bit y (y= 0..15) (LCK4)
            uint32_t lck4  : 1;    // bit 4
            /// Port x lock bit y (y= 0..15) (LCK5)
            uint32_t lck5  : 1;    // bit 5
            /// Port x lock bit y (y= 0..15) (LCK6)
            uint32_t lck6  : 1;    // bit 6
            /// Port x lock bit y (y= 0..15) (LCK7)
            uint32_t lck7  : 1;    // bit 7
            /// Port x lock bit y (y= 0..15) (LCK8)
            uint32_t lck8  : 1;    // bit 8
            /// Port x lock bit y (y= 0..15) (LCK9)
            uint32_t lck9  : 1;    // bit 9
            /// Port x lock bit y (y= 0..15) (LCK10)
            uint32_t lck10 : 1;    // bit 10
            /// Port x lock bit y (y= 0..15) (LCK11)
            uint32_t lck11 : 1;    // bit 11
            /// Port x lock bit y (y= 0..15) (LCK12)
            uint32_t lck12 : 1;    // bit 12
            /// Port x lock bit y (y= 0..15) (LCK13)
            uint32_t lck13 : 1;    // bit 13
            /// Port x lock bit y (y= 0..15) (LCK14)
            uint32_t lck14 : 1;    // bit 14
            /// Port x lock bit y (y= 0..15) (LCK15)
            uint32_t lck15 : 1;    // bit 15
            /// Port x lock bit y (y= 0..15) (LCKK)
            uint32_t lckk  : 1;    // bit 16
            /// (reserved)
            uint32_t       : 15;    // bits 17:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Lock& operator=(Lock&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Lock volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Lock const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Lock>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Lock) == 4UL, "Must be this exact size");
    /// GPIO alternate function low register (AlternativeFunctionLow)
    struct AlternativeFunctionLow final {
        /// Default Constructor
        AlternativeFunctionLow()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AlternativeFunctionLow(AlternativeFunctionLow volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AlternativeFunctionLow(AlternativeFunctionLow const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AlternativeFunctionLow(AlternativeFunctionLow&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AlternativeFunctionLow(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AlternativeFunctionLow(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AlternativeFunctionLow() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow0)
            uint32_t afrl0 : 4;    // bits 0:3
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow1)
            uint32_t afrl1 : 4;    // bits 4:7
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow2)
            uint32_t afrl2 : 4;    // bits 8:11
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow3)
            uint32_t afrl3 : 4;    // bits 12:15
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow4)
            uint32_t afrl4 : 4;    // bits 16:19
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow5)
            uint32_t afrl5 : 4;    // bits 20:23
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow6)
            uint32_t afrl6 : 4;    // bits 24:27
            /// Alternate function selection for port x bit y (y = 0..7) (AlternativeFunctionLow7)
            uint32_t afrl7 : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AlternativeFunctionLow& operator=(AlternativeFunctionLow&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AlternativeFunctionLow volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AlternativeFunctionLow const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AlternativeFunctionLow>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AlternativeFunctionLow) == 4UL, "Must be this exact size");
    /// GPIO alternate function high register (AlternativeFunctionHigh)
    struct AlternativeFunctionHigh final {
        /// Default Constructor
        AlternativeFunctionHigh()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AlternativeFunctionHigh(AlternativeFunctionHigh volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AlternativeFunctionHigh(AlternativeFunctionHigh const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AlternativeFunctionHigh(AlternativeFunctionHigh&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AlternativeFunctionHigh(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AlternativeFunctionHigh(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AlternativeFunctionHigh() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh8)
            uint32_t afrh8  : 4;    // bits 0:3
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh9)
            uint32_t afrh9  : 4;    // bits 4:7
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh10)
            uint32_t afrh10 : 4;    // bits 8:11
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh11)
            uint32_t afrh11 : 4;    // bits 12:15
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh12)
            uint32_t afrh12 : 4;    // bits 16:19
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh13)
            uint32_t afrh13 : 4;    // bits 20:23
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh14)
            uint32_t afrh14 : 4;    // bits 24:27
            /// Alternate function selection for port x bit y (y = 8..15) (AlternativeFunctionHigh15)
            uint32_t afrh15 : 4;    // bits 28:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AlternativeFunctionHigh& operator=(AlternativeFunctionHigh&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AlternativeFunctionHigh volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AlternativeFunctionHigh const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<AlternativeFunctionHigh>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AlternativeFunctionHigh) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// GPIO port mode register (Mode)
    Mode mode;    // offset 0x0UL
    /// GPIO port output type register (OutputType)
    OutputType output_type;    // offset 0x4UL
    /// GPIO port output speed register (OutputSpeed)
    OutputSpeed output_speed;    // offset 0x8UL
    /// GPIO port pull-up/pull-down register (PullUpPullDown)
    PullUpPullDown pullup_pulldown;    // offset 0xcUL
    /// GPIO port input data register (InputData)
    InputData input_data;    // offset 0x10UL
    /// GPIO port output data register (OutputData)
    OutputData output_data;    // offset 0x14UL
    /// GPIO port bit set/reset register (BitSetReset)
    BitSetReset bit_set_reset;    // offset 0x18UL
    /// GPIO port configuration lock register (Lock)
    Lock lock;    // offset 0x1cUL
    /// GPIO alternate function low register (AlternativeFunctionLow)
    AlternativeFunctionLow alt_func_low;    // offset 0x20UL
    /// GPIO alternate function high register (AlternativeFunctionHigh)
    AlternativeFunctionHigh alt_func_high;    // offset 0x24UL
    uint32_t : 32;                            // offset 0x28UL
    uint32_t : 32;                            // offset 0x2cUL
    uint32_t : 32;                            // offset 0x30UL
    uint32_t : 32;                            // offset 0x34UL
    uint32_t : 32;                            // offset 0x38UL
    uint32_t : 32;                            // offset 0x3cUL
    uint32_t : 32;                            // offset 0x40UL
    uint32_t : 32;                            // offset 0x44UL
    uint32_t : 32;                            // offset 0x48UL
    uint32_t : 32;                            // offset 0x4cUL
    uint32_t : 32;                            // offset 0x50UL
    uint32_t : 32;                            // offset 0x54UL
    uint32_t : 32;                            // offset 0x58UL
    uint32_t : 32;                            // offset 0x5cUL
    uint32_t : 32;                            // offset 0x60UL
    uint32_t : 32;                            // offset 0x64UL
    uint32_t : 32;                            // offset 0x68UL
    uint32_t : 32;                            // offset 0x6cUL
    uint32_t : 32;                            // offset 0x70UL
    uint32_t : 32;                            // offset 0x74UL
    uint32_t : 32;                            // offset 0x78UL
    uint32_t : 32;                            // offset 0x7cUL
    uint32_t : 32;                            // offset 0x80UL
    uint32_t : 32;                            // offset 0x84UL
    uint32_t : 32;                            // offset 0x88UL
    uint32_t : 32;                            // offset 0x8cUL
    uint32_t : 32;                            // offset 0x90UL
    uint32_t : 32;                            // offset 0x94UL
    uint32_t : 32;                            // offset 0x98UL
    uint32_t : 32;                            // offset 0x9cUL
    uint32_t : 32;                            // offset 0xa0UL
    uint32_t : 32;                            // offset 0xa4UL
    uint32_t : 32;                            // offset 0xa8UL
    uint32_t : 32;                            // offset 0xacUL
    uint32_t : 32;                            // offset 0xb0UL
    uint32_t : 32;                            // offset 0xb4UL
    uint32_t : 32;                            // offset 0xb8UL
    uint32_t : 32;                            // offset 0xbcUL
    uint32_t : 32;                            // offset 0xc0UL
    uint32_t : 32;                            // offset 0xc4UL
    uint32_t : 32;                            // offset 0xc8UL
    uint32_t : 32;                            // offset 0xccUL
    uint32_t : 32;                            // offset 0xd0UL
    uint32_t : 32;                            // offset 0xd4UL
    uint32_t : 32;                            // offset 0xd8UL
    uint32_t : 32;                            // offset 0xdcUL
    uint32_t : 32;                            // offset 0xe0UL
    uint32_t : 32;                            // offset 0xe4UL
    uint32_t : 32;                            // offset 0xe8UL
    uint32_t : 32;                            // offset 0xecUL
    uint32_t : 32;                            // offset 0xf0UL
    uint32_t : 32;                            // offset 0xf4UL
    uint32_t : 32;                            // offset 0xf8UL
    uint32_t : 32;                            // offset 0xfcUL
    uint32_t : 32;                            // offset 0x100UL
    uint32_t : 32;                            // offset 0x104UL
    uint32_t : 32;                            // offset 0x108UL
    uint32_t : 32;                            // offset 0x10cUL
    uint32_t : 32;                            // offset 0x110UL
    uint32_t : 32;                            // offset 0x114UL
    uint32_t : 32;                            // offset 0x118UL
    uint32_t : 32;                            // offset 0x11cUL
    uint32_t : 32;                            // offset 0x120UL
    uint32_t : 32;                            // offset 0x124UL
    uint32_t : 32;                            // offset 0x128UL
    uint32_t : 32;                            // offset 0x12cUL
    uint32_t : 32;                            // offset 0x130UL
    uint32_t : 32;                            // offset 0x134UL
    uint32_t : 32;                            // offset 0x138UL
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
    uint32_t : 32;                            // offset 0x200UL
    uint32_t : 32;                            // offset 0x204UL
    uint32_t : 32;                            // offset 0x208UL
    uint32_t : 32;                            // offset 0x20cUL
    uint32_t : 32;                            // offset 0x210UL
    uint32_t : 32;                            // offset 0x214UL
    uint32_t : 32;                            // offset 0x218UL
    uint32_t : 32;                            // offset 0x21cUL
    uint32_t : 32;                            // offset 0x220UL
    uint32_t : 32;                            // offset 0x224UL
    uint32_t : 32;                            // offset 0x228UL
    uint32_t : 32;                            // offset 0x22cUL
    uint32_t : 32;                            // offset 0x230UL
    uint32_t : 32;                            // offset 0x234UL
    uint32_t : 32;                            // offset 0x238UL
    uint32_t : 32;                            // offset 0x23cUL
    uint32_t : 32;                            // offset 0x240UL
    uint32_t : 32;                            // offset 0x244UL
    uint32_t : 32;                            // offset 0x248UL
    uint32_t : 32;                            // offset 0x24cUL
    uint32_t : 32;                            // offset 0x250UL
    uint32_t : 32;                            // offset 0x254UL
    uint32_t : 32;                            // offset 0x258UL
    uint32_t : 32;                            // offset 0x25cUL
    uint32_t : 32;                            // offset 0x260UL
    uint32_t : 32;                            // offset 0x264UL
    uint32_t : 32;                            // offset 0x268UL
    uint32_t : 32;                            // offset 0x26cUL
    uint32_t : 32;                            // offset 0x270UL
    uint32_t : 32;                            // offset 0x274UL
    uint32_t : 32;                            // offset 0x278UL
    uint32_t : 32;                            // offset 0x27cUL
    uint32_t : 32;                            // offset 0x280UL
    uint32_t : 32;                            // offset 0x284UL
    uint32_t : 32;                            // offset 0x288UL
    uint32_t : 32;                            // offset 0x28cUL
    uint32_t : 32;                            // offset 0x290UL
    uint32_t : 32;                            // offset 0x294UL
    uint32_t : 32;                            // offset 0x298UL
    uint32_t : 32;                            // offset 0x29cUL
    uint32_t : 32;                            // offset 0x2a0UL
    uint32_t : 32;                            // offset 0x2a4UL
    uint32_t : 32;                            // offset 0x2a8UL
    uint32_t : 32;                            // offset 0x2acUL
    uint32_t : 32;                            // offset 0x2b0UL
    uint32_t : 32;                            // offset 0x2b4UL
    uint32_t : 32;                            // offset 0x2b8UL
    uint32_t : 32;                            // offset 0x2bcUL
    uint32_t : 32;                            // offset 0x2c0UL
    uint32_t : 32;                            // offset 0x2c4UL
    uint32_t : 32;                            // offset 0x2c8UL
    uint32_t : 32;                            // offset 0x2ccUL
    uint32_t : 32;                            // offset 0x2d0UL
    uint32_t : 32;                            // offset 0x2d4UL
    uint32_t : 32;                            // offset 0x2d8UL
    uint32_t : 32;                            // offset 0x2dcUL
    uint32_t : 32;                            // offset 0x2e0UL
    uint32_t : 32;                            // offset 0x2e4UL
    uint32_t : 32;                            // offset 0x2e8UL
    uint32_t : 32;                            // offset 0x2ecUL
    uint32_t : 32;                            // offset 0x2f0UL
    uint32_t : 32;                            // offset 0x2f4UL
    uint32_t : 32;                            // offset 0x2f8UL
    uint32_t : 32;                            // offset 0x2fcUL
    uint32_t : 32;                            // offset 0x300UL
    uint32_t : 32;                            // offset 0x304UL
    uint32_t : 32;                            // offset 0x308UL
    uint32_t : 32;                            // offset 0x30cUL
    uint32_t : 32;                            // offset 0x310UL
    uint32_t : 32;                            // offset 0x314UL
    uint32_t : 32;                            // offset 0x318UL
    uint32_t : 32;                            // offset 0x31cUL
    uint32_t : 32;                            // offset 0x320UL
    uint32_t : 32;                            // offset 0x324UL
    uint32_t : 32;                            // offset 0x328UL
    uint32_t : 32;                            // offset 0x32cUL
    uint32_t : 32;                            // offset 0x330UL
    uint32_t : 32;                            // offset 0x334UL
    uint32_t : 32;                            // offset 0x338UL
    uint32_t : 32;                            // offset 0x33cUL
    uint32_t : 32;                            // offset 0x340UL
    uint32_t : 32;                            // offset 0x344UL
    uint32_t : 32;                            // offset 0x348UL
    uint32_t : 32;                            // offset 0x34cUL
    uint32_t : 32;                            // offset 0x350UL
    uint32_t : 32;                            // offset 0x354UL
    uint32_t : 32;                            // offset 0x358UL
    uint32_t : 32;                            // offset 0x35cUL
    uint32_t : 32;                            // offset 0x360UL
    uint32_t : 32;                            // offset 0x364UL
    uint32_t : 32;                            // offset 0x368UL
    uint32_t : 32;                            // offset 0x36cUL
    uint32_t : 32;                            // offset 0x370UL
    uint32_t : 32;                            // offset 0x374UL
    uint32_t : 32;                            // offset 0x378UL
    uint32_t : 32;                            // offset 0x37cUL
    uint32_t : 32;                            // offset 0x380UL
    uint32_t : 32;                            // offset 0x384UL
    uint32_t : 32;                            // offset 0x388UL
    uint32_t : 32;                            // offset 0x38cUL
    uint32_t : 32;                            // offset 0x390UL
    uint32_t : 32;                            // offset 0x394UL
    uint32_t : 32;                            // offset 0x398UL
    uint32_t : 32;                            // offset 0x39cUL
    uint32_t : 32;                            // offset 0x3a0UL
    uint32_t : 32;                            // offset 0x3a4UL
    uint32_t : 32;                            // offset 0x3a8UL
    uint32_t : 32;                            // offset 0x3acUL
    uint32_t : 32;                            // offset 0x3b0UL
    uint32_t : 32;                            // offset 0x3b4UL
    uint32_t : 32;                            // offset 0x3b8UL
    uint32_t : 32;                            // offset 0x3bcUL
    uint32_t : 32;                            // offset 0x3c0UL
    uint32_t : 32;                            // offset 0x3c4UL
    uint32_t : 32;                            // offset 0x3c8UL
    uint32_t : 32;                            // offset 0x3ccUL
    uint32_t : 32;                            // offset 0x3d0UL
    uint32_t : 32;                            // offset 0x3d4UL
    uint32_t : 32;                            // offset 0x3d8UL
    uint32_t : 32;                            // offset 0x3dcUL
    uint32_t : 32;                            // offset 0x3e0UL
    uint32_t : 32;                            // offset 0x3e4UL
    uint32_t : 32;                            // offset 0x3e8UL
    uint32_t : 32;                            // offset 0x3ecUL
    uint32_t : 32;                            // offset 0x3f0UL
    uint32_t : 32;                            // offset 0x3f4UL
    uint32_t : 32;                            // offset 0x3f8UL
    uint32_t : 32;                            // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<GeneralPurposeInputOutput>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(GeneralPurposeInputOutput, mode) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, output_type) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, output_speed) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, pullup_pulldown) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, input_data) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, output_data) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, bit_set_reset) == 0x18UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, lock) == 0x1cUL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, alt_func_low) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(GeneralPurposeInputOutput, alt_func_high) == 0x24UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(GeneralPurposeInputOutput) == 0x400UL, "Must be this exact size");

static constexpr std::size_t NumberOfGeneralPurposeInputOutputInstances = 11UL;

/// The external volatile gpio which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern GeneralPurposeInputOutput volatile general_purpose_input_output[NumberOfGeneralPurposeInputOutputInstances];

}    // namespace registers

}    // namespace stm32

#endif    // STM32_REGISTERS_GENERALPURPOSEINPUTOUTPUT_HPP