#include "core/Printer.hpp"
#include "compiler.hpp"

namespace core {

namespace {
/// @brief A no-operation Printer used as the weak default.
/// Any translation unit that provides its own core::GetPrinter() definition
/// will override this weak symbol at link time.
class NullPrinter final : public Printer {
public:
    void operator()(const char* const /*format*/, ...) const override {}
    void operator()(char const* const /*source*/, Status /*status*/) const override {}
};
}    // anonymous namespace

ATTRIBUTE((weak)) Printer& GetPrinter() {
    static NullPrinter null_printer;
    return null_printer;
}

}    // namespace core
