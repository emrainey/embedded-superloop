#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <cstddef>
#include <type_traits>

/// Contains features used to debug the system at compile time
namespace debug {

/// Used to compare two sizes at compile time.
template <std::size_t A, std::size_t B>
class ConstexprValueCompare final {
public:
    static_assert(A == B, "Values must match!");
};

template <std::size_t A, std::size_t B>
class ConstexprValueDivisible final {
public:
    static_assert((A % B) == 0, "Second value must even divide first value!");
};

using StorageType = std::uint64_t;

enum class MaskType : StorageType {
    None = 0U,
    //===BYTE 0===
    fatal = (1ULL << 0),
    error = (1ULL << 1),
    warning = (1ULL << 2),
    info = (1ULL << 3),
    verbose = (1ULL << 4),
    // reserved          = 1ULL << 5,
    // reserved          = 1ULL << 6,
    // reserved          = 1ULL << 7,
    //===BYTE 1===
    boot = (1ULL << 8),
    isr = 1ULL << 9,
    svc = 1ULL << 10,
    fault = 1ULL << 11,
    states = 1ULL << 12,
    initialization = 1ULL << 13,
    // reserved          = 1ULL << 14,
    // reserved          = 1ULL << 15,
    //===BYTE 2===
    dma = 1ULL << 16,
    i2c = 1ULL << 17,
    spi = 1ULL << 18,
    can = 1ULL << 19,
    adc = 1ULL << 20,
    dac = 1ULL << 21,
    pwm = 1ULL << 22,
    uart = 1ULL << 23,
    //===BYTE 3===
    usart = 1ULL << 24,
    ethernet = 1ULL << 25,
    screen = 1ULL << 26,
    usb = 1ULL << 27,
    // reserved          = 1ULL << 28,
    // reserved          = 1ULL << 29,
    // reserved          = 1ULL << 30,
    // reserved          = 1ULL << 31,
    //===BYTE 4=== (System Objects)
    superloop = 1ULL << 32,
    monitor = 1ULL << 33,
    transactor = 1ULL << 34,
    coordinator = 1ULL << 35,
    timers = 1ULL << 36,
    ticks = 1ULL << 37,
    // reserved          = 1ULL << 38,
    // reserved          = 1ULL << 39,
    //===BYTE 5=== (Services)
    temperature = 1ULL << 40,
    network = 1ULL << 41,
    storage = 1ULL << 42,
    display = 1ULL << 43,
    audio = 1ULL << 44,
    // reserved          = 1ULL << 45,
    // reserved          = 1ULL << 46,
    // reserved          = 1ULL << 47,
    //===BYTE 6===
    // reserved          = 1ULL << 48,
    // reserved          = 1ULL << 49,
    // reserved          = 1ULL << 50,
    // reserved          = 1ULL << 51,
    // reserved          = 1ULL << 52,
    // reserved          = 1ULL << 53,
    // reserved          = 1ULL << 54,
    // reserved          = 1ULL << 55,
    //===BYTE 7===
    // reserved          = 1ULL << 56,
    // reserved          = 1ULL << 57,
    // reserved          = 1ULL << 58,
    // reserved          = 1ULL << 59,
    // reserved          = 1ULL << 60,
    // reserved          = 1ULL << 61,
    // reserved          = 1ULL << 62,
    // reserved          = 1ULL << 63,
    All = ~0U,
};

constexpr bool operator&(StorageType lhs, MaskType rhs) {
    return (lhs & static_cast<StorageType>(rhs)) != 0;
}
constexpr bool operator&(MaskType lhs, StorageType rhs) {
    return (static_cast<StorageType>(lhs) & rhs) != 0;
}
constexpr MaskType operator|(MaskType lhs, MaskType rhs) {
    return static_cast<MaskType>(static_cast<StorageType>(lhs) | static_cast<StorageType>(rhs));
}

#if not defined(DEBUG_MASK)
#define DEBUG_MASK static_cast<StorageType>(0x7ULL)
#endif

constexpr static bool fatal{DEBUG_MASK & MaskType::fatal};
constexpr static bool error{DEBUG_MASK & MaskType::error};
constexpr static bool warning{DEBUG_MASK & MaskType::warning};
constexpr static bool info{DEBUG_MASK & MaskType::info};
constexpr static bool verbose{DEBUG_MASK & MaskType::verbose};

constexpr static bool boot{DEBUG_MASK & MaskType::boot};
constexpr static bool isr{DEBUG_MASK & MaskType::isr};
constexpr static bool svc{DEBUG_MASK & MaskType::svc};
constexpr static bool fault{DEBUG_MASK & MaskType::fault};
constexpr static bool states{DEBUG_MASK & MaskType::states};

constexpr static bool i2c{DEBUG_MASK & MaskType::i2c};
constexpr static bool i2c_isr{DEBUG_MASK & MaskType::i2c and DEBUG_MASK & MaskType::isr};    // this seems to effect timing, be careful!
constexpr static bool spi{DEBUG_MASK & MaskType::spi};
constexpr static bool spi_isr{DEBUG_MASK & MaskType::spi and DEBUG_MASK & MaskType::isr};    // this seems to effect timing, be careful!
constexpr static bool uart{DEBUG_MASK & MaskType::uart};
constexpr static bool uart_isr{DEBUG_MASK & MaskType::uart and DEBUG_MASK & MaskType::isr};
constexpr static bool usart{DEBUG_MASK & MaskType::usart};
constexpr static bool usart_isr{DEBUG_MASK & MaskType::usart and DEBUG_MASK & MaskType::isr};
constexpr static bool dma{DEBUG_MASK & MaskType::dma};
constexpr static bool dma_isr{DEBUG_MASK & MaskType::dma and DEBUG_MASK & MaskType::isr};

constexpr static bool superloop{DEBUG_MASK & MaskType::superloop};
constexpr static bool monitor{DEBUG_MASK & MaskType::monitor};
constexpr static bool transactor{DEBUG_MASK & MaskType::transactor};
constexpr static bool coordinator{DEBUG_MASK & MaskType::coordinator};
constexpr static bool temperature{DEBUG_MASK & MaskType::temperature};

constexpr static bool inform{DEBUG_MASK & MaskType::info and DEBUG_MASK & MaskType::states};
constexpr static bool duration{DEBUG_MASK & MaskType::timers and DEBUG_MASK & MaskType::info};

}    // namespace debug

#endif    // DEBUG_HPP_
