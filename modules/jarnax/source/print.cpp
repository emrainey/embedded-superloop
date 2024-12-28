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
static constexpr unsigned int base10{10u};
static constexpr unsigned int base16{16u};
static constexpr unsigned int digit_places_limit{32u};
static constexpr unsigned int float_fractional_limit{6u};

static unsigned long clamp_to_range(unsigned long value, unsigned long min, unsigned long max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

static long clamp_to_range(long value, long min, long max) {
    if (value < min) {
        return min;
    } else if (value > max) {
        return max;
    } else {
        return value;
    }
}

static unsigned long print_number(unsigned long start, char buffer[], unsigned long num, unsigned int base) {
    const char *digits = "0123456789abcdef";
    unsigned int offset = 0;
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
    if (offset > 0) {
        for (unsigned int i = 0; i < offset; i++) {
            buffer[start + i] = backwards_digits[offset - i - 1];
        }
    }
    return start + offset;
}

static unsigned long print_signed_number(unsigned long start, char buffer[], long num, unsigned int base) {
    if (num < 0) {
        buffer[start] = '-';
        return print_number(start + 1, buffer, static_cast<unsigned long>(-num), base);
    } else {
        return print_number(start, buffer, static_cast<unsigned long>(num), base);
    }
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);

    // store these in RAM externally to the function.
    static constexpr size_t PRINTF_BUFFER_SIZE{4096U};
    static char buffer[PRINTF_BUFFER_SIZE];
    static unsigned long index;

    // always start back at zero
    index = 0;

    while (*format) {
        if (*format == '%') {
            format++;

            // Handle %l modifiers
            bool longlong_modifier = false;
            bool long_modifier = false;
            if (*format == 'l') {
                long_modifier = true;
                format++;
                if (*format == 'l') {
                    longlong_modifier = true;
                    format++;
                }
            }
            static_cast<void>(longlong_modifier);    // can't use for now

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
                    while (((*str) != '\0') && index < (PRINTF_BUFFER_SIZE - 1)) {
                        buffer[index++] = *str;
                        ++str;
                    }
                    break;
                }
                case 'd':
                case 'i': {
                    long num;
                    if (long_modifier) {
                        num = va_arg(args, long);
                    } else if (half_modifier) {
                        num = va_arg(args, int);
                        num = clamp_to_range(num, std::numeric_limits<int16_t>::min(), std::numeric_limits<int16_t>::max());
                    } else if (halfhalf_modifier) {
                        num = va_arg(args, int);
                        num = clamp_to_range(num, std::numeric_limits<int8_t>::min(), std::numeric_limits<int8_t>::max());
                        // } else if (size_modifier) {
                        //     num = va_arg(args, ssize_t);
                    } else {
                        num = va_arg(args, int);
                    }
                    index = print_signed_number(index, buffer, num, base10);
                    break;
                }
                case 'u': {
                    unsigned long num;
                    if (long_modifier) {
                        num = va_arg(args, unsigned long);
                        // } else if (longlong_modifier) {
                        //     num = va_arg(args, unsigned long long);
                    } else if (half_modifier) {
                        num = va_arg(args, unsigned int);
                        num = clamp_to_range(num, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                    } else if (halfhalf_modifier) {
                        num = va_arg(args, unsigned int);
                        num = clamp_to_range(num, std::numeric_limits<uint8_t>::min(), std::numeric_limits<uint8_t>::max());
                    } else if (size_modifier) {
                        num = va_arg(args, size_t);
                    } else {
                        num = va_arg(args, unsigned int);
                    }
                    index = print_number(index, buffer, num, base10);
                    break;
                }
                case 'x': {
                    unsigned long num;
                    buffer[index++] = '0';
                    buffer[index++] = 'x';
                    if (long_modifier) {
                        num = va_arg(args, unsigned long);
                    } else if (half_modifier) {
                        num = va_arg(args, unsigned int);
                        num = clamp_to_range(num, std::numeric_limits<uint16_t>::min(), std::numeric_limits<uint16_t>::max());
                    } else {
                        num = va_arg(args, unsigned int);
                    }
                    index = print_number(index, buffer, num, base16);
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
            if (index < (PRINTF_BUFFER_SIZE - 1)) {
                buffer[index++] = *format;
            }
        }
        format++;
    }

    va_end(args);

    // FIXME determine if we've run over.

    // null terminate the string
    buffer[index] = '\0';
    if (use_rtt_for_printf) {
        rtt::control_block.GetUp(rtt::Index{0}).Write(index, buffer);
    }
    if (use_swo_for_printf) {
        cortex::swo::emit(cortex::swo::Port::System, buffer);
    }
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

}    // namespace jarnax
