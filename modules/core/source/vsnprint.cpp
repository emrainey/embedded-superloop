/// @file
/// Print Functions. Heavily inspired by ChatGPT which likely got these from the Arduino project.

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>

#include "strings.hpp"

namespace core {

static constexpr unsigned int base2{2u};
static constexpr unsigned int base8{8u};
static constexpr unsigned int base10{10u};
static constexpr unsigned int base16{16u};
static constexpr unsigned int base64{64u};
static constexpr unsigned int digit_places_limit{32u};
static constexpr unsigned int float_fractional_limit{6u};

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
static unsigned long print_number(unsigned long start, char buffer[], T num, unsigned int base, unsigned int width = 0, bool leading_zero = false, bool uppercase = false, bool is_negative = false) {
    // the digits cover base 2, base 8 (don't use) base 10, base 12, base 16 and base 64
    static constexpr char const *const digits =
        "0123456789abcdef"
        "ghijklmnopqrstuv"
        "wxyzABCDEFGHIJKL"
        "MNOPQRSTUVWXYZ+/";

    unsigned long offset = 0;
    char backwards_digits[digit_places_limit];    // hold the value temporarily

    if (num == 0) {
        backwards_digits[offset++] = '0';
    } else {
        if (base == base2) {
            while (num != 0) {
                backwards_digits[offset++] = digits[num & 1];
                num >>= 1;
            }
        } else if (base == base8) {
            while (num != 0) {
                backwards_digits[offset++] = digits[num & 7];
                num >>= 3;
            }
        } else if (base == base10) {
            while (num != 0) {
                backwards_digits[offset++] = digits[num % 10];
                num /= 10;
            }
        } else if (base == base16) {
            while (num != 0) {
                char d = digits[num & 0xF];
                if (uppercase && d >= 'a' && d <= 'z') {
                    d = d - 'a' + 'A';
                }
                backwards_digits[offset++] = d;
                num >>= 4;
            }
        } else if (base == base64) {
            while (num != 0) {
                backwards_digits[offset++] = digits[num & 0x3F];
                num >>= 6;
            }
        }
    }

    // Determine how many characters we will print before padding
    unsigned int total_chars = static_cast<unsigned int>(offset) + (is_negative ? 1U : 0U);
    unsigned long current = start;

    // Space padding (leading_zero = false) goes before the sign
    if (!leading_zero && width > total_chars) {
        unsigned int padding = width - total_chars;
        for (unsigned int i = 0; i < padding; i++) {
            buffer[current++] = ' ';
        }
    }

    // Print the sign if negative
    if (is_negative) {
        buffer[current++] = '-';
    }

    // Zero padding (leading_zero = true) goes after the sign
    if (leading_zero && width > total_chars) {
        unsigned int padding = width - total_chars;
        for (unsigned int i = 0; i < padding; i++) {
            buffer[current++] = '0';
        }
    }

    // Print the digits in correct order (reverse of backwards_digits)
    for (unsigned int i = 0; i < offset; i++) {
        buffer[current++] = backwards_digits[offset - i - 1];
    }

    return current;
}

/// @brief Parses the number and prints it in the specified base in the buffer
/// @tparam T The type of number to parse
/// @param start The index to start at
/// @param buffer The buffer to write to
/// @param num The number to parse
/// @param base The base to parse the number in
/// @return The index at the exclusive end of the number
template <typename T>
static unsigned long print_signed_number(unsigned long start, char buffer[], T num, unsigned int base, unsigned int width = 0, bool leading_zero = false) {
    if (num < 0) {
        // Safe absolute value conversion using uint64_t to avoid signed integer overflow on INT_MIN
        uint64_t abs_val = static_cast<uint64_t>(-static_cast<int64_t>(num));
        return print_number(start, buffer, abs_val, base, width, leading_zero, false, true);
    } else {
        return print_number(start, buffer, static_cast<uint64_t>(num), base, width, leading_zero, false, false);
    }
}

constexpr bool is_digit(char c) {
    return (c >= '0' && c <= '9');
}

unsigned long vsnprint(char buffer[], size_t buffer_size, const char *format, va_list args) {
    unsigned long index = 0U;    // always start back at zero

    while (*format) {
        if (*format == '%') {
            format++;

            // Handle leading zero modifier
            bool leading_zero = false;
            if (*format == '0') {
                leading_zero = true;
                format++;
            }

            // Handle width modifier
            unsigned int width = 0;
            if (is_digit(*format)) {
                while (is_digit(*format)) {
                    width = width * 10U + static_cast<unsigned int>(*format - '0');
                    format++;
                }
                if (width > digit_places_limit) {
                    width = digit_places_limit;
                }
            }

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
                        index = print_signed_number(index, buffer, num, base10, width, leading_zero);
                    } else if (long_modifier) {
                        int32_t num = va_arg(args, int32_t);
                        num = clamp_to_range(num, std::numeric_limits<int32_t>::min(), std::numeric_limits<int32_t>::max());
                        index = print_signed_number(index, buffer, num, base10, width, leading_zero);
                    } else if (half_modifier) {
                        int value = static_cast<int16_t>(va_arg(args, int));
                        int16_t num = clamp_to_range(value, std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max());
                        index = print_signed_number(index, buffer, num, base10, width, leading_zero);
                    } else if (halfhalf_modifier) {
                        int value = va_arg(args, int);
                        int8_t num = clamp_to_range(value, std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());
                        index = print_signed_number(index, buffer, num, base10, width, leading_zero);
                    } else {
                        auto num = va_arg(args, int);
                        index = print_signed_number(index, buffer, num, base10, width, leading_zero);
                    }
                    break;
                }
                case 'u': {
                    if (longlong_modifier) {
                        uint64_t num = va_arg(args, uint64_t);
                        num = clamp_to_range(num, std::numeric_limits<uint64_t>::min(), std::numeric_limits<uint64_t>::max());
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    } else if (long_modifier) {
                        uint32_t num = va_arg(args, uint32_t);
                        num = clamp_to_range(num, std::numeric_limits<uint32_t>::min(), std::numeric_limits<uint32_t>::max());
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    } else if (half_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint16_t num = clamp_to_range(value, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    } else if (halfhalf_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint8_t num = clamp_to_range(value, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    } else if (size_modifier) {
                        size_t num = va_arg(args, size_t);
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    } else {
                        unsigned int num = va_arg(args, unsigned int);
                        index = print_number(index, buffer, num, base10, width, leading_zero);
                    }
                    break;
                }
                case 'x': {
                    buffer[index++] = '0';
                    buffer[index++] = 'x';
                    unsigned int sub_width = (width > 2) ? (width - 2) : 0;
                    if (longlong_modifier) {
                        uint64_t num = va_arg(args, uint64_t);
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    } else if (long_modifier) {
                        uint32_t num = va_arg(args, uint32_t);
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    } else if (half_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint16_t num = clamp_to_range(value, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    } else if (halfhalf_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint8_t num = clamp_to_range(value, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    } else if (size_modifier) {
                        size_t num = va_arg(args, size_t);
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    } else {
                        uint32_t num = va_arg(args, unsigned int);
                        index = print_number(index, buffer, num, base16, sub_width, leading_zero, false);
                    }
                    break;
                }
                case 'X': {
                    if (longlong_modifier) {
                        uint64_t num = va_arg(args, uint64_t);
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
                    } else if (long_modifier) {
                        uint32_t num = va_arg(args, uint32_t);
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
                    } else if (half_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint16_t num = clamp_to_range(value, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
                    } else if (halfhalf_modifier) {
                        unsigned int value = va_arg(args, unsigned int);
                        uint8_t num = clamp_to_range(value, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
                    } else if (size_modifier) {
                        size_t num = va_arg(args, size_t);
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
                    } else {
                        uint32_t num = va_arg(args, unsigned int);
                        index = print_number(index, buffer, num, base16, width, leading_zero, true);
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
                    unsigned int sub_width = (width > 2) ? (width - 2) : 0;
                    index = print_number(index, buffer, num, base2, sub_width, leading_zero, false);
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

    // null terminate the string
    if (index >= buffer_size) {
        index = buffer_size - 1;
    }
    buffer[index] = '\0';
    return index;
}

}    // namespace core
