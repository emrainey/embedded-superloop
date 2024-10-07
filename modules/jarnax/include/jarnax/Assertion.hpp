#ifndef ASSERTION_HPP_
#define ASSERTION_HPP_

#include "jarnax/system.hpp"

namespace jarnax {

#define assertion(condition) \
    { Assertion _assertion{condition, __FILE__, __LINE__}; }

class Assertion {
public:
    Assertion(bool condition, char const* const filename, std::uint32_t line_number)
        : filename_{filename}
        , line_number_{line_number}
        , condition_{condition} {}

    ~Assertion() {
        if (not condition_) {
            jarnax::print("Assertion in ");
            jarnax::print(filename_);
            jarnax::print("\r\n");
            cortex::spinhalt();
        }
    }

protected:
    char const* const filename_;
    std::uint32_t const line_number_;
    bool condition_;
};

}    // namespace jarnax

#endif    // ASSERTION_HPP_