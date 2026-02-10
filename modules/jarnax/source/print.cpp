/// @file
/// Print Functions. Heavily inspired by ChatGPT which likely got these from the Arduino project.

#include <cstdarg>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <limits>

#include "core/vsnprint.hpp"
#include "cortex/swo.hpp"
#include "jarnax/system.hpp"
#include "segger/rtt.hpp"
#include "strings.hpp"
namespace jarnax {
// store these in RAM externally to the function.
static constexpr size_t PrintfBufferSize{4096U};
static char printf_buffer[PrintfBufferSize];

static __attribute__((used)) void vprint(const char *format, va_list args) {
    unsigned long count = core::vsnprint(printf_buffer, PrintfBufferSize, format, args);

    if constexpr (use_rtt_for_printf) {
        rtt::control_block.GetUp(rtt::Index{0}).Write(count, printf_buffer);
    }
    if constexpr (use_swo_for_printf) {
        cortex::swo::emit(cortex::swo::Port::System, printf_buffer);
    }
    if constexpr (use_uart_for_printf) {
        // @TODO add uart::write(buffer, count);
    }
    if constexpr (use_logger_for_printf) {
        // @TODO add complex network logging
    }
}

void print(const char *format, ...) {
    va_list args;
    va_start(args, format);
    if constexpr (use_system_printf) {
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
        std::vprintf(format, args);
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#pragma GCC diagnostic pop
    } else {
        vprint(format, args);
    }
    va_end(args);
}

void print(char const *const source, core::Status status) {
    print(
        "%s => Status{Result=%d, Cause=%u Location=%" PRIxPTR "}\n",
        source,
        polyfill::to_underlying(status.GetResult()),
        polyfill::to_underlying(status.GetCause()),
        status.GetLocation()
    );
}

class SimplePrinter : public core::Printer {
public:
    SimplePrinter()
        : buffer_{} {
        operator()("SimplePrinter Initialized\r\n");
    }

    /// Default Destructor
    virtual ~SimplePrinter() = default;

    void operator()(const char *const format, ...) const override {
        if constexpr (use_system_printf) {
            va_list args;
            va_start(args, format);
#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat-nonliteral"
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wformat-nonliteral"
#endif
            std::vprintf(format, args);
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
#pragma GCC diagnostic pop
            va_end(args);
        } else {
            va_list args;
            va_start(args, format);
            unsigned long count = core::vsnprint(buffer_, PrintfBufferSize, format, args);
            va_end(args);
            if constexpr (use_rtt_for_printf) {
                rtt::control_block.GetUp(rtt::Index{0}).Write(count, buffer_);
            }
            if constexpr (use_swo_for_printf) {
                cortex::swo::emit(cortex::swo::Port::System, buffer_);
            }
            if constexpr (use_uart_for_printf) {
                // @TODO add uart::write(buffer, count);
            }
            if constexpr (use_logger_for_printf) {
                // @TODO add complex network logging
            }
        }
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
