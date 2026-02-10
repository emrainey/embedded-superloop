#include <cstdarg>
#include <cstdio>
#include "core/Printer.hpp"
#include "core/Status.hpp"
#include "polyfill.hpp"

namespace core {

class StdioPrinter : public Printer {
public:
    StdioPrinter() = default;
    virtual ~StdioPrinter() = default;

    void operator()(const char* const source, core::Status status) const override {
        operator()(
            "%s => Status{Result=%d, Cause=%u Location=%x}\n",
            source,
            polyfill::to_underlying(status.GetResult()),
            polyfill::to_underlying(status.GetCause()),
            status.GetLocation()
        );
    }
    void operator()(const char* const format, ...) const override {
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
    }
};

Printer& GetPrinter() {
    static StdioPrinter printer;
    return printer;
}
}    // namespace core
