#include <cstdio>
#include <cstdarg>
#include "polyfill.hpp"
#include "core/Status.hpp"
#include "core/Printer.hpp"

namespace core {

class StdioPrinter : public Printer {
public:
    StdioPrinter() = default;
    ~StdioPrinter() = default;
    void operator()(const char* const source, core::Status status) const override {
        operator()(
            "%s => Status{Result=%d, Cause=%u Location=%x}\n",
            source,
            to_underlying(status.GetResult()),
            to_underlying(status.GetCause()),
            status.GetLocation()
        );
    }
    void operator()(const char* const format, ...) const override {
        va_list args;
        va_start(args, format);
        vprintf(format, args);
        va_end(args);
    }
};

Printer& GetPrinter() {
    static StdioPrinter printer;
    return printer;
}
}    // namespace core
