#ifndef ASSERTION_HPP_
#define ASSERTION_HPP_

#include "jarnax/system.hpp"

namespace jarnax {

#define assertion(condition)                                 \
    {                                                        \
        Assertion _assertion{condition, __FILE__, __LINE__}; \
    }

/// @brief A class to hold the assertion result as well as the filename/line number.
class Assertion {
public:
    /// @brief Parameter Constructor
    /// @param condition The boolean value of the condition
    /// @param filename The literal string of the filename (usually __FILE__)
    /// @param line_number The literal integer of the file line number (usually __LINE__)
    Assertion(bool condition, char const* const filename, std::uint32_t line_number)
        : filename_{filename}
        , line_number_{line_number}
        , condition_{condition} {}

    /// @brief Destructor which triggers the prints and halt if the condition is false
    ~Assertion() {
        if (not condition_) {
            jarnax::print("Assertion in ");
            jarnax::print(filename_);
            jarnax::print("\r\n");
            cortex::spinhalt();
        }
    }

protected:
    char const* const filename_;         ///< The file in which the assertion happened
    std::uint32_t const line_number_;    ///< The line number in which the assertion happened
    bool condition_;                     ///< The condition value
};

}    // namespace jarnax

#endif    // ASSERTION_HPP_