/// @file
/// Print Functions. Heavily inspired by ChatGPT which likely got these from the Arduino project.

#include <cstdint>
#include <cstdlib>
#include <cstddef>
#include <cstdarg>
#include <limits>

#include "board.hpp"
#include "strings.hpp"
#include "jarnax/system.hpp"
#include "segger/rtt.hpp"
#include "cortex/mcu.hpp"
namespace jarnax {

static constexpr unsigned int base2{2u};
static constexpr unsigned int base8{8u};
static constexpr unsigned int base10{10u};
static constexpr unsigned int base16{16u};
static constexpr unsigned int base64{64u};
static constexpr unsigned int digit_places_limit{32u};
static constexpr unsigned int float_fractional_limit{6u};

// store these in RAM externally to the function.
static constexpr size_t PrintfBufferSize{4096U};
static char printf_buffer[PrintfBufferSize];

template <typename T, typename U>
static U clamp_to_range(T value, U min, U max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return static_cast<U>(value);
    }
}

/// @brief Parses the number and prints it in the specified base in the buffer
/// @tparam T The type of number to parse
/// @param start The index to start at
/// @param buffer The buffer to write to
/// @param num The number to parse
/// @param base The base to parse the number in
/// @return The index at the exclusive end of the number
template <typename T>
static unsigned long print_number(unsigned long start, char buffer[], T num, unsigned int base) {
    // the digits cover base 2, base 8 (don't use) base 10, base 12, base 16 and base 64
    static constexpr char const *const digits =
        "0123456789abcdef"
        "ghijklmnopqrstuv"
        "wxyzABCDEFGHIJKL"
        "MNOPQRSTUVWXYZ+/";

    unsigned long offset = 0;
    char backwards_digits[digit_places_limit];    // hold the value temporarily

    if (base == base2) {
        if (num < 0b10) {
            buffer[start] = digits[num];
            return start + 1;
        } else {
            while (num != 0) {
                backwards_digits[offset] = digits[num & 1];
                offset++;
                num >>= 1;
            }
        }
    }
    if (base == base8) {
        if (num < 8) {
            buffer[start] = digits[num];
            return start + 1;
        } else {
            while (num != 0) {
                backwards_digits[offset] = digits[num & 7];
                offset++;
                num >>= 3;
            }
        }
    }
    if (base == base10) {
        if (num < 10) {
            buffer[start] = digits[num];
            return start + 1;
        } else {
            while (num != 0) {
                backwards_digits[offset] = digits[num % 10];
                offset++;
                num /= 10;
            }
        }
    }
    if (base == base16) {
        if (num < 0x10) {
            buffer[start] = digits[num];
            return start + 1;
        } else {
            while (num != 0) {
                backwards_digits[offset] = digits[num & 0xF];
                offset++;
                num >>= 4;
            }
        }
    }
    if (base == base64) {
        if (num < 0x40) {
            buffer[start] = digits[num];
            return start + 1;
        } else {
            while (num != 0) {
                backwards_digits[offset] = digits[num & 0x3F];
                offset++;
                num >>= 6;
            }
        }
    }
    if (offset > 0) {
        for (unsigned int i = 0; i < offset; i++) {
            buffer[start + i] = backwards_digits[offset - i - 1];
        }
    }
    return start + offset;
}

/// @brief Parses the number and prints it in the specified base in the buffer
/// @tparam T The type of number to parse
/// @param start The index to start at
/// @param buffer The buffer to write to
/// @param num The number to parse
/// @param base The base to parse the number in
/// @return The index at the exclusive end of the number
template <typename T>
static unsigned long print_signed_number(unsigned long start, char buffer[], T num, unsigned int base) {
    if (num < 0) {
        buffer[start] = '-';
        return print_number(start + 1, buffer, -num, base);
    } else {
        return print_number(start, buffer, num, base);
    }
}

constexpr bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

static unsigned long vsnprint(char buffer[], size_t buffer_size, const char *format, va_list args) {
    unsigned long index = 0U;    // always start back at zero

    while (*format) {
        if (*format == '%') {
            format++;

            // Handle %l modifiers
            bool longlong_modifier = false;
            bool long_modifier = false;
            if (*format == 'l') {
                long_modifier = true;
                format++;
                // Handle %ll modifier
                if (*format == 'l') {
                    longlong_modifier = true;
                    format++;
                }
            }

            // Handle %h modifiers
            bool halfhalf_modifier = false;
            bool half_modifier = false;
            if (*format == 'h') {
                half_modifier = true;
                format++;
                if (*format == 'h') {
                    halfhalf_modifier = true;
                    format++;
                }
            }

            // Handle %z modifier
            bool size_modifier = false;
            if (*format == 'z') {
                size_modifier = true;
                format++;
            }

            // Handle leading zero modifier
            // bool leading_zero = false;
            // if (*format == '0') {
            //     leading_zero = true;
            //     format++;
            // }
            // bool specific_digits = false;
            // if (is_digit(*format)) {
            //     specific_digits = true;
            //     unsigned int digits = 0;
            //     while (is_digit(*format)) {
            //         digits = digits * 10 + (*format - '0');
            //         format++;
            //     }
            //     if (digits > digit_places_limit) {
            //         digits = digit_places_limit;
            //     }
            // }
            // (void)leading_zero;       // @TODO unused
            // (void)specific_digits;    // @TODO unused

            switch (*format) {
                case 's': {
                    const char *str = va_arg(args, const char *);
                    while (((*str) != '\0') && index < (buffer_size - 1)) {
                        buffer[index++] = *str;
                        ++str;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    if (longlong_modifier) {
                        int64_t num = va_arg(args, int64_t);
                        num = clamp_to_range(num, std::numeric_limits<int64_t>::min(), std::numeric_limits<int64_t>::max());
                        index = print_signed_number(index, buffer, num, base10);
                    } else if (long_modifier) {
                        int32_t num = va_arg(args, int32_t);
                        num = clamp_to_range(num, std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
                        index = print_signed_number(index, buffer, num, base10);
                    } else if (half_modifier) {
                        int value = static_cast<int16_t>(va_arg(args, int));
                        int16_t num = clamp_to_range(value, std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max());
                        index = print_signed_number(index, buffer, num, base10);
                    } else if (halfhalf_modifier) {
                        int value = va_arg(args, int);
                        int8_t num = clamp_to_range(value, std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());
                        index = print_signed_number(index, buffer, num, base10);
                        // } else if (size_modifier) {
                        //     ssize_t value = va_arg(args, ssize_t);
                        //     num = clamp_to_range(value, std::numeric_limits<ssize_t>::min(), std::numeric_limits<ssize_t>::max());
                        //     index = print_signed_number(index, buffer, num, base10);
                    } else {
                        auto num = va_arg(args, int);
                        index = print_signed_number(index, buffer, num, base10);
                    }
                    break;
                }
                case 'u': {
                    if (longlong_modifier) {
                        uint64_t num = va_arg(args, uint64_t);
                        num = clamp_to_range(num, std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
                        index = print_number(index, buffer, num, base10);
                    } else if (long_modifier) {
                        uint32_t num = va_arg(args, uint32_t);
                        num = clamp_to_range(num, std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
                        index = print_number(index, buffer, num, base10);
                    } else if (half_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint16_t num = clamp_to_range(value, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                        index = print_number(index, buffer, num, base10);
                    } else if (halfhalf_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint8_t num = clamp_to_range(value, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                        index = print_number(index, buffer, num, base10);
                    } else if (size_modifier) {
                        size_t num = va_arg(args, size_t);
                        index = print_number(index, buffer, num, base10);
                    } else {
                        unsigned int num = va_arg(args, unsigned int);
                        index = print_number(index, buffer, num, base10);
                    }
                    break;
                }
                case 'x': {
                    buffer[index++] = '0';
                    buffer[index++] = 'x';
                    if (longlong_modifier) {
                        uint64_t num = va_arg(args, uint64_t);
                        index = print_number(index, buffer, num, base16);
                    } else if (long_modifier) {
                        uint32_t num = va_arg(args, unsigned long);    // 32 bits
                        index = print_number(index, buffer, num, base16);
                    } else if (half_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint16_t num = clamp_to_range(value, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                        index = print_number(index, buffer, num, base16);
                    } else if (halfhalf_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint8_t num = clamp_to_range(value, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                        index = print_number(index, buffer, num, base16);
                    } else if (size_modifier) {
                        size_t num = va_arg(args, size_t);
                        index = print_number(index, buffer, num, base16);
                    } else {
                        uint32_t num = va_arg(args, unsigned int);
                        index = print_number(index, buffer, num, base16);
                    }
                    break;
                }
                case 'p': {
                    uintptr_t ptr = va_arg(args, uintptr_t);
                    buffer[index++] = '0';
                    buffer[index++] = 'x';
                    index = print_number(index, buffer, ptr, base16);
                    break;
                }
                case 'f': {
                    using precision = float;
                    precision num = static_cast<precision>(va_arg(args, double));
                    long integer_part = static_cast<long>(num);
                    index = print_signed_number(index, buffer, integer_part, base10);
                    buffer[index++] = '.';
                    precision fractional_part = num - static_cast<precision>(integer_part);
                    // we only use 6 decimal places
                    for (unsigned int i = 0; i < float_fractional_limit; i++) {
                        // bring one place up from the fractional part
                        fractional_part *= base10;
                        // get the integer part again of the digit
                        long digit = static_cast<long>(fractional_part);
                        buffer[index++] = '0' + static_cast<char>(digit);
                        fractional_part -= static_cast<precision>(digit);
                    }
                    break;
                }
                case 'b': {
                    unsigned long num;
                    if (long_modifier) {
                        num = va_arg(args, unsigned long);
                    } else {
                        num = va_arg(args, unsigned int);
                    }
                    buffer[index++] = '0';
                    buffer[index++] = 'b';
                    index = print_number(index, buffer, num, base2);
                    break;
                }
                default:
                    buffer[index++] = '?';    // unknown format modifier
                    break;
            }
        } else {
            if (index < (buffer_size - 1)) {
                buffer[index++] = *format;
            }
        }
        format++;
    }

    // FIXME determine if we've run over.

    // null terminate the string
    if (index >= buffer_size) {
        index = buffer_size - 1;
    }
    buffer[index] = '\0';
    return index;
}

static void vprint(const char *format, va_list args) {
    unsigned long count = vsnprint(printf_buffer, PrintfBufferSize, format, args);

    if (use_rtt_for_printf) {
        rtt::control_block.GetUp(rtt::Index{0}).Write(count, printf_buffer);
    }
    if (use_swo_for_printf) {
        cortex::swo::emit(cortex::swo::Port::System, printf_buffer);
    }
    if (use_uart_for_printf) {
        // @TODO add uart::write(buffer, count);
    }
    if (use_logger_for_printf) {
        // @TODO add complex network logging
    }
#if defined(UNIT_TESTS)
    if (use_system_printf) {
        // UNIT TESTS
        vsnprintf(printf_buffer, PrintfBufferSize, format, args);
    }
#endif
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    vprint(format, args);
    va_end(args);
}

void print(char const *const source, core::Status status) {
    print(
        "%s => Status{Result=%d, Cause=%u Location=%x}\n",
        source,
        to_underlying(status.GetResult()),
        to_underlying(status.GetCause()),
        status.GetLocation()
    );
}

class SimplePrinter : public core::Printer {
public:
    SimplePrinter()
        : buffer_{} {
        operator()("SimplePrinter Initialized\r\n");
    }

    void operator()(const char *const format, ...) const override {
        va_list args;
        va_start(args, format);
        unsigned long count = vsnprint(buffer_, PrintfBufferSize, format, args);
        va_end(args);

        if (use_rtt_for_printf) {
            rtt::control_block.GetUp(rtt::Index{0}).Write(count, buffer_);
        }
        if (use_swo_for_printf) {
            cortex::swo::emit(cortex::swo::Port::System, buffer_);
        }
        if (use_uart_for_printf) {
            // @TODO add uart::write(buffer, count);
        }
        if (use_logger_for_printf) {
            // @TODO add complex network logging
        }
#if defined(UNIT_TESTS)
        if (use_system_printf) {
            // UNIT TESTS
            vsnprintf(buffer_, PrintfBufferSize, format, args);
        }
#endif
    }

    void operator()(char const *const source, core::Status status) const override { print(source, status); }

private:
    mutable char buffer_[PrintfBufferSize];    ///< The buffer to write to
};

}    // namespace jarnax

namespace core {

Printer &GetPrinter() {
    static jarnax::SimplePrinter simple;
    return simple;
}

}    // namespace core
