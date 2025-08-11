#ifndef CORE_RATIO_HPP
#define CORE_RATIO_HPP

#include <core/units/Unit.hpp>

namespace core {
namespace units {
template <typename NumeratorType, typename DenominatorType>
class Ratio : public units::Unit<typename NumeratorType::Type> {
public:
    using Type = typename NumeratorType::Type;    ///< The type of the ratio

    static_assert(not std::is_same<NumeratorType, DenominatorType>::value, "Must be different types!");
    static_assert(std::is_same<typename NumeratorType::Type, typename DenominatorType::Type>::value, "Underlying unit types must be the same!");

    /// In this constructor the denominator is assumed to be one
    constexpr Ratio(Type numerator)
        : units::Unit<Type>{numerator} {}

    constexpr Ratio(NumeratorType const& numerator, DenominatorType const& denominator)
        : units::Unit<Type>{numerator.value() / denominator.value()} {}

    constexpr Ratio(NumeratorType&& numerator, DenominatorType&& denominator)
        : units::Unit<Type>{numerator.value() / denominator.value()} {}

    constexpr Ratio(Ratio const& other)
        : units::Unit<Type>{other.value()} {}

    constexpr Ratio(Ratio&& other) noexcept
        : units::Unit<Type>{std::move(other.value())} {}

    constexpr Ratio& operator=(Ratio const& other) {
        units::Unit<Type>::value_ = other.value();
        return *this;
    }

    constexpr Ratio& operator=(Ratio&& other) noexcept {
        units::Unit<Type>::value_ = std::move(other.value_);
        return *this;
    }

    constexpr NumeratorType Numerator() const { return NumeratorType{units::Unit<typename NumeratorType::Type>::value()}; }

    constexpr DenominatorType Denominator() const {
        return DenominatorType{1};    // The denominator is always 1 in a ratio
    }

    /// Unary Negative operator
    constexpr Ratio operator-() const { return Ratio{-Numerator(), Denominator()}; }

    // Comparison Overloads

    friend constexpr bool operator==(Ratio const& lhs, Ratio const& rhs) {
        if constexpr (std::is_floating_point_v<typename Ratio::Type>) {
            return std::fabs(lhs.value() - rhs.value()) < std::numeric_limits<typename Ratio::Type>::epsilon();
        } else {
#if defined(__clang__)
#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wfloat-equal"
#endif
            return lhs.value() == rhs.value();
#if defined(__clang__)
#pragma clang diagnostic pop
#endif
        }
    }

    friend constexpr bool operator!=(Ratio const& lhs, Ratio const& rhs) { return not(lhs == rhs); }

    friend constexpr bool operator<(Ratio const& lhs, Ratio const& rhs) { return lhs.value() < rhs.value(); }

    friend constexpr bool operator<=(Ratio const& lhs, Ratio const& rhs) { return lhs.value() <= rhs.value(); }

    friend constexpr bool operator>(Ratio const& lhs, Ratio const& rhs) { return lhs.value() > rhs.value(); }

    friend constexpr bool operator>=(Ratio const& lhs, Ratio const& rhs) { return lhs.value() >= rhs.value(); }

    // Arithmetic Overloads

    friend constexpr Ratio operator+(Ratio const& lhs, Ratio const& rhs) { return Ratio{lhs.value() + rhs.value()}; }

    friend constexpr Ratio operator-(Ratio const& lhs, Ratio const& rhs) { return Ratio{lhs.value() - rhs.value()}; }

    // Scalars
    friend constexpr Ratio operator*(Ratio const& lhs, Type scalar) { return Ratio{lhs.value() * scalar}; }

    friend constexpr Ratio operator*(Type scalar, Ratio const& rhs) { return Ratio{scalar * rhs.value()}; }

    friend constexpr Ratio operator/(Ratio const& lhs, Type scalar) { return Ratio{lhs.value() / scalar}; }
};
}    // namespace units
}    // namespace core

#endif    // CORE_RATIO_HPP
