#ifndef DEBUG_HPP_
#define DEBUG_HPP_

/// @file
/// @brief Contains features used to debug the system at compile time.

#include <cstddef>
#include <type_traits>

/// Contains features used to debug the system at compile time
namespace debug {

/// @brief Used to compare two sizes at compile time.
/// Typically this will force a compiler to evaluate the expression at compile time. Used in place of the availability of consteval.
/// @tparam A The first value to compare
/// @tparam B The second value to compare
/// @code
/// using Check = ConstexprValueCompare<sizeof(MyType), 4>;
/// @endcode
template <std::size_t A, std::size_t B>
class ConstexprValueCompare final {
public:
    static_assert(A == B, "Values must match!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Used to compare two values at compile time to see if A is evenly divisible by B.
/// Use in a manner to force a compiler to evaluate the expression at compile time.
/// @tparam A The first value to compare
/// @tparam B The second value to compare
template <std::size_t A, std::size_t B>
class ConstexprValueDivisible final {
public:
    static_assert((A % B) == 0, "Second value must evenly divide first value!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Used to compare two values at compile time to see if A is less than B.
/// Use in a manner to force a compiler to evaluate the expression at compile time.
/// @tparam A The first value to compare
/// @tparam B The second value to compare
template <std::size_t A, std::size_t B>
class ConstexprValueLessThan final {
public:
    static_assert(A < B, "First value must be less than second value!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Used to compare two values at compile time to see if A is less than or equal to B.
/// Use in a manner to force a compiler to evaluate the expression at compile time.
/// @tparam A The first value to compare
/// @tparam B The second value to compare
template <std::size_t A, std::size_t B>
class ConstexprValueLessEqual final {
public:
    static_assert(A <= B, "First value must be less than or equal to second value!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Used to determine if a value is a power of two at compile time.
/// Use in a manner to force a compiler to evaluate the expression at compile time.
/// @tparam N The value to check if it is a power of two
template <std::size_t N>
class ConstexprIsPowerOfTwo final {
public:
    static_assert(N > 0 && (N & (N - 1)) == 0, "Value must be a power of two!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Used to determine if a value is within a specified range at compile time.
/// Use in a manner to force a compiler to evaluate the expression at compile time.
/// @tparam Value The value to check if it is within the range
/// @tparam Min The minimum value of the range (inclusive)
/// @tparam Max The maximum value of the range (inclusive)
template <std::size_t Value, std::size_t Min, std::size_t Max>
class ConstexprValueInRange final {
public:
    static_assert(Value >= Min && Value <= Max, "Value must be within specified range!");
    static constexpr bool value = true;    // for SFINAE purposes
};

/// @brief Force a compile error showing the type T
/// @tparam T The type to show in the compile error
/// Usage: TypeDebugger<decltype(my_var)> show_type;
template <typename T>
class TypeDebugger;    // Intentionally no definition - will cause compile error showing T

/// @brief Show size of a type at compile time (will fail, but show size in error)
/// @tparam T The type to show the size of
/// Usage: TypeSizeDebugger<my_type> show_size;
template <typename T, std::size_t Size = sizeof(T)>
class TypeSizeDebugger;    // Intentionally no definition

/// @brief Verify type sizes match expectations
/// @tparam T The type to check the size of
/// @tparam ExpectedSize The expected size of the type in bytes
template <typename T, std::size_t ExpectedSize>
class TypeSizeValidator final {
public:
    static_assert(sizeof(T) == ExpectedSize, "Type size does not match expected size!");
    static constexpr std::size_t value = sizeof(T);
};

/// @brief Verify type alignment matches expectations
/// @tparam T The type to check the alignment of
/// @tparam ExpectedAlignment The expected alignment of the type in bytes
template <typename T, std::size_t ExpectedAlignment>
class TypeAlignmentValidator final {
public:
    static_assert(alignof(T) == ExpectedAlignment, "Type alignment does not match expected alignment!");
    static constexpr std::size_t value = alignof(T);
};

/// The type used to store debug masks.
using StorageType = std::uint64_t;

/// The enumeration of all Mask Bits in the StorageType
enum class MaskType : StorageType {
    None = 0U,    ///< Indicates no mask.
    //===BYTE 0===
    Fatal = (1ULL << 0),      ///< Indicates a fatal error.
    Error = (1ULL << 1),      ///< Indicates a non-fatal error.
    Warning = (1ULL << 2),    ///< Indicates a warning.
    Info = (1ULL << 3),       ///< Indicates informational messages.
    Verbose = (1ULL << 4),    ///< Indicates verbose messages.
    Debug = (1ULL << 5),      ///< Indicates debug messages.
    // reserved          = 1ULL << 6,
    // reserved          = 1ULL << 7,
    //===BYTE 1===
    Boot = (1ULL << 8),               ///< Indicates that the message has to do with the boot process.
    Isr = (1ULL << 9),                ///< Indicates that the message has to do with an interrupt service routine.
    Svc = (1ULL << 10),               ///< Indicates that the message has to do with a supervisor call.
    Fault = (1ULL << 11),             ///< Indicates that the message has to do with a fault.
    States = (1ULL << 12),            ///< Indicates that the message has to do with system states.
    Initialization = (1ULL << 13),    ///< Indicates that the message has to do with system initialization.
    // reserved          = (1ULL << 14),
    // reserved          = (1ULL << 15),
    //===BYTE 2===
    Dma = (1ULL << 16),     ///< Indicates that the message has to do with a DMA operation.
    I2c = (1ULL << 17),     ///< Indicates that the message has to do with an I2C operation.
    Spi = (1ULL << 18),     ///< Indicates that the message has to do with an SPI operation.
    Can = (1ULL << 19),     ///< Indicates that the message has to do with a CAN operation.
    Adc = (1ULL << 20),     ///< Indicates that the message has to do with an ADC operation.
    Dac = (1ULL << 21),     ///< Indicates that the message has to do with a DAC operation.
    Pwm = (1ULL << 22),     ///< Indicates that the message has to do with a PWM operation.
    Uart = (1ULL << 23),    ///< Indicates that the message has to do with a UART operation.
    //===BYTE 3===
    Usart = (1ULL << 24),       ///< Indicates that the message has to do with a USART operation.
    Ethernet = (1ULL << 25),    ///< Indicates that the message has to do with an Ethernet operation.
    Screen = (1ULL << 26),      ///< Indicates that the message has to do with a Screen operation.
    Usb = (1ULL << 27),         ///< Indicates that the message has to do with a USB operation.
    // reserved          = (1ULL << 28),
    // reserved          = (1ULL << 29),
    // reserved          = (1ULL << 30),
    // reserved          = (1ULL << 31),
    //===BYTE 4=== (System Objects)
    Superloop = (1ULL << 32),      ///< Indicates that the message has to do with the superloop.
    Monitor = (1ULL << 33),        ///< Indicates that the message has to do with the monitor.
    Transactor = (1ULL << 34),     ///< Indicates that the message has to do with the transactor.
    Coordinator = (1ULL << 35),    ///< Indicates that the message has to do with the coordinator.
    Timers = (1ULL << 36),         ///< Indicates that the message has to do with timers.
    Ticks = (1ULL << 37),          ///< Indicates that the message has to do with ticks.
    Events = (1ULL << 38),         ///< Indicates that the message has to do with events.
    // reserved          = (1ULL << 39),
    //===BYTE 5=== (Services)
    Temperature = (1ULL << 40),    ///< Indicates that the message has to do with temperature.
    Network = (1ULL << 41),        ///< Indicates that the message has to do with network operations.
    Storage = (1ULL << 42),        ///< Indicates that the message has to do with storage operations.
    Display = (1ULL << 43),        ///< Indicates that the message has to do with display operations.
    Audio = (1ULL << 44),          ///< Indicates that the message has to do with audio operations.
    // reserved          = (1ULL << 45),
    // reserved          = (1ULL << 46),
    // reserved          = (1ULL << 47),
    //===BYTE 6===
    // reserved          = (1ULL << 48),
    // reserved          = (1ULL << 49),
    // reserved          = (1ULL << 50),
    // reserved          = (1ULL << 51),
    // reserved          = (1ULL << 52),
    // reserved          = (1ULL << 53),
    // reserved          = (1ULL << 54),
    // reserved          = (1ULL << 55),
    //===BYTE 7===
    // reserved          = (1ULL << 56),
    // reserved          = (1ULL << 57),
    // reserved          = (1ULL << 58),
    // reserved          = (1ULL << 59),
    // reserved          = (1ULL << 60),
    // reserved          = (1ULL << 61),
    // reserved          = (1ULL << 62),
    // reserved          = (1ULL << 63),
    All = ~0U,    ///< Used to indicate that the message will be grouped with All operations.
};

/// @brief Bitwise operators for MaskType to allow for easy combination and checking of masks.
/// @param lhs The left-hand side of the bitwise operation, which is a StorageType value.
/// @param rhs The right-hand side of the bitwise operation, which is a MaskType
/// @return A boolean value indicating whether the bitwise AND of the StorageType and MaskType is non-zero.
constexpr bool operator&(StorageType lhs, MaskType rhs) {
    return (lhs & static_cast<StorageType>(rhs)) != 0;
}

/// @brief Bitwise operators for MaskType to allow for easy combination and checking of masks.
/// @param lhs The left-hand side of the bitwise operation, which is a MaskType value.
/// @param rhs The right-hand side of the bitwise operation, which is a StorageType value.
/// @return A boolean value indicating whether the bitwise AND of the MaskType and StorageType is non-zero.
constexpr bool operator&(MaskType lhs, StorageType rhs) {
    return (static_cast<StorageType>(lhs) & rhs) != 0;
}

/// @brief Bitwise operators for MaskType to allow for easy combination of MaskType values.
/// @param lhs The left-hand side of the bitwise operation, which is a MaskType value.
/// @param rhs The right-hand side of the bitwise operation, which is a MaskType value.
/// @return A MaskType value that is the result of the bitwise OR of the two MaskType values. This "value" WILL NO LONGER be a valid MaskType, but can
/// be used to nest further bitwise operations to combine multiple MaskType values together.
constexpr MaskType operator|(MaskType lhs, MaskType rhs) {
    return static_cast<MaskType>(static_cast<StorageType>(lhs) | static_cast<StorageType>(rhs));
}

#if not defined(DEBUG_MASK)
/// @brief The mask used to determine which debug messages are enabled. This should be defined by the user before including this header.
/// The default value does not enable all messages.
#define DEBUG_MASK static_cast<StorageType>(0x0000'0000'0000'0007ULL)
#endif

constexpr static bool Fatal{DEBUG_MASK & MaskType::Fatal};
constexpr static bool Error{DEBUG_MASK & MaskType::Error};
constexpr static bool Warning{DEBUG_MASK & MaskType::Warning};
constexpr static bool Info{DEBUG_MASK & MaskType::Info};
constexpr static bool Verbose{DEBUG_MASK & MaskType::Verbose};

constexpr static bool Boot{DEBUG_MASK & MaskType::Boot};
constexpr static bool Isr{DEBUG_MASK & MaskType::Isr};
constexpr static bool Svc{DEBUG_MASK & MaskType::Svc};
constexpr static bool Fault{DEBUG_MASK & MaskType::Fault};
constexpr static bool States{DEBUG_MASK & MaskType::States};

constexpr static bool I2c{DEBUG_MASK & MaskType::I2c};
constexpr static bool I2cIsr{DEBUG_MASK & MaskType::I2c and DEBUG_MASK & MaskType::Isr};    // this seems to effect timing, be careful!
constexpr static bool Spi{DEBUG_MASK & MaskType::Spi};
constexpr static bool SpiIsr{DEBUG_MASK & MaskType::Spi and DEBUG_MASK & MaskType::Isr};    // this seems to effect timing, be careful!
constexpr static bool Uart{DEBUG_MASK & MaskType::Uart};
constexpr static bool UartIsr{DEBUG_MASK & MaskType::Uart and DEBUG_MASK & MaskType::Isr};
constexpr static bool Usart{DEBUG_MASK & MaskType::Usart};
constexpr static bool UsartIsr{DEBUG_MASK & MaskType::Usart and DEBUG_MASK & MaskType::Isr};
constexpr static bool Dma{DEBUG_MASK & MaskType::Dma};
constexpr static bool DmaIsr{DEBUG_MASK & MaskType::Dma and DEBUG_MASK & MaskType::Isr};

constexpr static bool Superloop{DEBUG_MASK & MaskType::Superloop};
constexpr static bool Monitor{DEBUG_MASK & MaskType::Monitor};
constexpr static bool Transactor{DEBUG_MASK & MaskType::Transactor};
constexpr static bool Coordinator{DEBUG_MASK & MaskType::Coordinator};
constexpr static bool Temperature{DEBUG_MASK & MaskType::Temperature};
constexpr static bool Display{DEBUG_MASK & MaskType::Display};

constexpr static bool Inform{DEBUG_MASK & MaskType::Info and DEBUG_MASK & MaskType::States};
constexpr static bool Duration{DEBUG_MASK & MaskType::Timers and DEBUG_MASK & MaskType::Info};

}    // namespace debug

#endif    // DEBUG_HPP_
