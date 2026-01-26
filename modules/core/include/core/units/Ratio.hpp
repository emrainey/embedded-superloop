#ifndef CORE_RATIO_HPP
#define CORE_RATIO_HPP

/// @file
/// Unit Ratio Types and Operations

#include <core/units/Unit.hpp>

namespace core {
namespace units {

/// @brief A type to represent a ratio of two units.
/// @tparam NumeratorType The type of the numerator unit
/// @tparam DenominatorType The type of the denominator unit
template <typename NumeratorType, typename DenominatorType>
class Ratio : public units::Unit<typename NumeratorType::Type> {
public:
    using Type = typename NumeratorType::Type;    ///< The type of the ratio

    static_assert(not std::is_same<NumeratorType, DenominatorType>::value, "Must be different types!");
    static_assert(std::is_same<typename NumeratorType::Type, typename DenominatorType::Type>::value, "Underlying unit types must be the same!");

    /// In this constructor the denominator is assumed to be one
    constexpr Ratio(Type numerator)
        : units::Unit<Type>{numerator} {}

    /// Constructs a ratio from numerator and denominator values
    /// @param numerator The numerator value
    /// @param denominator The denominator value
    constexpr Ratio(NumeratorType const& numerator, DenominatorType const& denominator)
        : units::Unit<Type>{numerator.value() / denominator.value()} {}

    /// Constructs a ratio from rvalue numerator and denominator
    /// @param numerator The numerator value (rvalue)
    /// @param denominator The denominator value (rvalue)
    constexpr Ratio(NumeratorType&& numerator, DenominatorType&& denominator)
        : units::Unit<Type>{numerator.value() / denominator.value()} {}

    /// Copy constructor
    /// @param other The ratio to copy from
    constexpr Ratio(Ratio const& other)
        : units::Unit<Type>{other.value()} {}

    /// Move constructor
    /// @param other The ratio to move from
    constexpr Ratio(Ratio&& other) noexcept
        : units::Unit<Type>{std::move(other.value())} {}

    /// Copy assignment operator
    /// @param other The ratio to copy from
    /// @return Reference to this ratio
    constexpr Ratio& operator=(Ratio const& other) {
        units::Unit<Type>::value_ = other.value();
        return *this;
    }

    /// Move assignment operator
    /// @param other The ratio to move from
    /// @return Reference to this ratio
    constexpr Ratio& operator=(Ratio&& other) noexcept {
        units::Unit<Type>::value_ = std::move(other.value_);
        return *this;
    }

    /// Gets the numerator of the ratio
    /// @return The numerator value
    constexpr NumeratorType Numerator() const { return NumeratorType{units::Unit<typename NumeratorType::Type>::value()}; }

    /// Gets the denominator of the ratio (always 1 after simplification)
    /// @return The denominator value
    constexpr DenominatorType Denominator() const {
        return DenominatorType{1};    // The denominator is always 1 in a ratio
    }

    /// Unary Negative operator
    constexpr Ratio operator-() const { return Ratio{-Numerator(), Denominator()}; }

    // Comparison Overloads

    /// Equality comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if ratios are equal
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

    /// Inequality comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if ratios are not equal
    friend constexpr bool operator!=(Ratio const& lhs, Ratio const& rhs) { return not(lhs == rhs); }

    /// Less-than comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if lhs is less than rhs
    friend constexpr bool operator<(Ratio const& lhs, Ratio const& rhs) { return lhs.value() < rhs.value(); }

    /// Less-than-or-equal comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if lhs is less than or equal to rhs
    friend constexpr bool operator<=(Ratio const& lhs, Ratio const& rhs) { return lhs.value() <= rhs.value(); }

    /// Greater-than comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if lhs is greater than rhs
    friend constexpr bool operator>(Ratio const& lhs, Ratio const& rhs) { return lhs.value() > rhs.value(); }

    /// Greater-than-or-equal comparison operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return True if lhs is greater than or equal to rhs
    friend constexpr bool operator>=(Ratio const& lhs, Ratio const& rhs) { return lhs.value() >= rhs.value(); }

    // Arithmetic Overloads

    /// Addition operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return Sum of the two ratios
    friend constexpr Ratio operator+(Ratio const& lhs, Ratio const& rhs) { return Ratio{lhs.value() + rhs.value()}; }

    /// Subtraction operator
    /// @param lhs Left-hand side ratio
    /// @param rhs Right-hand side ratio
    /// @return Difference of the two ratios
    friend constexpr Ratio operator-(Ratio const& lhs, Ratio const& rhs) { return Ratio{lhs.value() - rhs.value()}; }

    // Scalars
    /// Multiplication by scalar operator
    /// @param lhs The ratio
    /// @param scalar The scalar value to multiply by
    /// @return Product of ratio and scalar
    friend constexpr Ratio operator*(Ratio const& lhs, Type scalar) { return Ratio{lhs.value() * scalar}; }

    /// Multiplication by scalar operator (reversed)
    /// @param scalar The scalar value to multiply by
    /// @param rhs The ratio
    /// @return Product of scalar and ratio
    friend constexpr Ratio operator*(Type scalar, Ratio const& rhs) { return Ratio{scalar * rhs.value()}; }

    /// Division by scalar operator
    /// @param lhs The ratio
    /// @param scalar The scalar value to divide by
    /// @return Quotient of ratio and scalar
    friend constexpr Ratio operator/(Ratio const& lhs, Type scalar) { return Ratio{lhs.value() / scalar}; }
};
}    // namespace units
}    // namespace core

#endif    // CORE_RATIO_HPP
