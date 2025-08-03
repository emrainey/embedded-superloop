#ifndef DEBUG_HPP_
#define DEBUG_HPP_

#include <cstddef>
#include <type_traits>

/// Contains features used to debug the system at compile time
namespace debug {

/// Used to compare two sizes at compile time.
template <std::size_t A, std::size_t B>
class ConstexprValueCompare final {
public:
    static_assert(A == B, "Values must match!");
};

template <std::size_t A, std::size_t B>
class ConstexprValueDivisible final {
public:
    static_assert((A % B) == 0, "Second value must even divide first value!");
};

}    // namespace debug

#endif    // DEBUG_HPP_
