#ifndef JARNAX_USART_CONSOLE_HPP
#define JARNAX_USART_CONSOLE_HPP

/// @file
/// USART Console Implementation

#include <jarnax/console/Service.hpp>
#include <jarnax/usart/Driver.hpp>

namespace jarnax {
namespace console {

/// @brief A Console Service which uses a USART Driver for output
class UsartConsole : public jarnax::console::Service {
public:
    /// The Parameterized Constructor
    /// @param driver The USART Driver to use for output
    explicit UsartConsole(jarnax::usart::Driver& driver);

    // === Overrides ===
    void Print(Level level, char const fmt[], ...) override;
    bool Execute(void) override;

protected:
    jarnax::usart::Driver& driver_;    ///< The reference to the USART Driver
    char buffer_[OutputLength];        ///< The internal buffer for formatted output
};

}    // namespace console
}    // namespace jarnax

#endif    // JARNAX_USART_CONSOLE_HPP
