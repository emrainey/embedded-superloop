#include <jarnax/print.hpp>
#include <jarnax/console/UsartConsole.hpp>

namespace jarnax {
namespace console {

UsartConsole::UsartConsole(jarnax::usart::Driver& driver)
    : driver_{driver} {
}

void UsartConsole::Print(Level level, char const format[], ...) {
    if (to_underlying(level_) >= to_underlying(level)) {
        va_list args;
        va_start(args, format);
        unsigned long count = vsnprint(buffer_, sizeof(buffer_), format, args);
        va_end(args);

        if (count <= output_.Spaces()) {
            for (size_t i = 0; i < count; i++) {
                output_.Push(buffer_[i]);
            }
        }
    }
}

bool UsartConsole::Execute(void) {
    // if there's space in the driver, write to it from the Ring
    if (not output_.IsEmpty()) {
        // pull data out and write to driver.
        size_t largest = output_.MaxContiguousElements();
        if (largest > 0U) {
            usart::Driver::DataUnit const* tmp = reinterpret_cast<usart::Driver::DataUnit const*>(&output_[0U]);
            core::Span<usart::Driver::DataUnit const> span{tmp, largest};
            core::Status status = driver_.Enqueue(span);
            if (status.IsSuccess()) {
                // remove the data from the Ring
                output_.Drop(span.count());
            }
        }
    }
    return true;
}

}    // namespace console
}    // namespace jarnax
