#ifndef JARNAX_USART_CONSOLE_HPP
#define JARNAX_USART_CONSOLE_HPP

#include <jarnax/console/Service.hpp>
#include <jarnax/usart/Driver.hpp>

namespace jarnax {
namespace console {

class UsartConsole : public jarnax::console::Service {
public:
    UsartConsole(jarnax::usart::Driver& driver);

    void Print(Level level, char const fmt[], ...) override;
    bool Execute(void) override;

protected:
    jarnax::usart::Driver& driver_;
    char buffer_[OutputLength];
};

}    // namespace console
}    // namespace jarnax

#endif    //
