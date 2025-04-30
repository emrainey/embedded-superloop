#ifndef CORE_FRACTION_HPP
#define CORE_FRACTION_HPP

#include <cstdint>
#include <iostream>
#include <type_traits>

namespace core {

template <typename NumeratorType, typename DenominatorType>
class Fraction_ {
    static_assert(std::is_integral<NumeratorType>::value, "Must be integral numerator_");
    static_assert(std::is_integral<DenominatorType>::value, "Must be integral denominator_");
    // static_assert(std::is_unsigned<DenominatorType>::value, "Must be unsigned denominator_");

protected:
    NumeratorType numerator_;
    DenominatorType denominator_;

    static DenominatorType gcd(NumeratorType a, DenominatorType b) {
        DenominatorType c = static_cast<DenominatorType>(std::abs(a));    // ensure positive
        DenominatorType gcd = std::min(c, b);
        while (gcd > 0) {
            if ((c % gcd) == 0 && (b % gcd) == 0)
                return gcd;
            gcd -= 1;
        }
        return 0;
    }

    static DenominatorType lcm(DenominatorType a, DenominatorType b) { return (a * b) / gcd(a, b); }

    void reduce() {
        auto g = gcd(numerator_, denominator_);
        if (g > 1) {
            if (g > std::numeric_limits<NumeratorType>::max()) {
                // this is a special case where the numerator_ is larger than the max value
                // so we set it to the max value and the denominator_ to 1
                numerator_ = std::numeric_limits<NumeratorType>::max();
                denominator_ = 1;
            } else {
                numerator_ /= static_cast<NumeratorType>(g);
                denominator_ /= g;
            }
        }
    }

public:
    /// @brief  Default constructor
    Fraction_()
        : numerator_{0}
        , denominator_{1} {}

    /// @brief  Constructor with numerator only (denominator is set to 1)
    /// @param n The numerator
    explicit Fraction_(NumeratorType n)
        : numerator_{n}
        , denominator_{1} {}

    /// @brief The constructor with numerator and denominator
    /// @param n The numerator
    /// @param d The denominator
    /// @note The denominator should be non-zero
    explicit Fraction_(NumeratorType n, DenominatorType d)
        : numerator_{n}
        , denominator_{d} {
        reduce();
    }

    /// @brief This is a special case where the denominator_ is zero.
    /// @return True if the value is infinite, false otherwise
    /// @note This is somewhat of an abuse of a colloquial understanding of division as repeated subtraction and not a pure mathematical definition
    /// (which would be undefined).
    bool IsInfinite() const { return (denominator_ == 0); }

    /// @brief This is a special case where the numerator_ is zero.
    /// @return True if the value is zero, false otherwise
    bool IsZero() const { return (numerator_ == 0); }

    /// @brief Equality operator
    /// @param other The other fraction to compare to
    /// @return True if the two fractions are equal, false otherwise
    /// @note This assumes that the fractions are reduced but does not reduce them itself.
    bool operator==(Fraction_ const& other) const {
        bool same = (numerator_ == other.numerator_ and denominator_ == other.denominator_);
        // this assumes that the fractions are reduced
        return same;
    }

    /// @brief Inequality operator
    /// @param other The other fraction to compare to
    /// @return True if the two fractions are not equal, false otherwise
    bool operator!=(Fraction_ const& other) const { return not operator==(other); }

    /// @brief Greater than operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is greater than the other, false otherwise
    bool operator>(NumeratorType m) const {
        // convert to Fraction_ and compare
        Fraction_ f{m};
        return (*this > f);
    }

    /// @brief Greater than operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is greater than the other, false otherwise
    bool operator>(Fraction_ const& other) const {
        // cross multiply to avoid floating point issues
        return ((numerator_ * other.denominator_) > (other.numerator_ * denominator_));
    }

    /// @brief Less than operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is less than the other, false otherwise
    bool operator<(NumeratorType m) const {
        // convert to Fraction_ and compare
        Fraction_ f{m};
        return (*this < f);
    }

    /// @brief Less than operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is less than the other, false otherwise
    bool operator<(Fraction_ const& other) const {
        // cross multiply to avoid floating point issues
        return ((numerator_ * other.denominator_) < (other.numerator_ * denominator_));
    }

    /// @brief Greater than or equal to operator
    /// @param m The value to compare to (assumed to be m/1)
    /// @return True if this fraction is greater than or equal to the value, false otherwise
    bool operator>=(NumeratorType m) const {
        // convert to Fraction_ and compare
        Fraction_ f{m};
        return (*this >= f);
    }

    /// @brief Greater than or equal to operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is greater than or equal to the other, false otherwise
    bool operator>=(Fraction_ const& other) const {
        // cross multiply to avoid floating point issues
        return ((numerator_ * other.denominator_) >= (other.numerator_ * denominator_));
    }

    /// @brief Less than or equal to operator
    /// @param m The value to compare to (assumed to be m/1)
    /// @return True if this fraction is less than or equal to the value, false otherwise
    bool operator<=(NumeratorType m) const {
        // convert to Fraction_ and compare
        Fraction_ f{m};
        return (*this <= f);
    }

    /// @brief Less than or equal to operator
    /// @param other The other fraction to compare to
    /// @return True if this fraction is less than or equal to the other, false otherwise
    bool operator<=(Fraction_ const& other) const {
        // cross multiply to avoid floating point issues
        return ((numerator_ * other.denominator_) <= (other.numerator_ * denominator_));
    }

    /// @brief Unary plus equals operator
    /// @tparam AdditiveType The type of the additive operator
    /// @param m The value to add to the fraction
    /// @return The fraction itself after being altered
    template <typename AdditiveType>
    Fraction_& operator+=(AdditiveType m) {
        static_assert(std::is_integral<AdditiveType>::value, "AdditiveType must be integral");
        numerator_ += (m * denominator_);
        reduce();
        return (*this);
    }

    /// @brief Unary minus equals operator
    /// @tparam AdditiveType The type of the additive operator
    /// @param m The value to subtract from the fraction
    /// @return The fraction itself after being altered
    template <typename AdditiveType>
    Fraction_& operator-=(AdditiveType m) {
        static_assert(std::is_integral<AdditiveType>::value, "AdditiveType must be integral");
        numerator_ -= (m * denominator_);
        reduce();
        return (*this);
    }

    /// @brief Unary multiplication equals operator
    /// @tparam MultiplicativeType The type of the multiplicative operator
    /// @param m The value to multiply the fraction by
    /// @return The fraction itself after being altered
    template <typename MultiplicativeType>
    Fraction_& operator*=(MultiplicativeType m) {
        static_assert(std::is_integral<MultiplicativeType>::value, "MultiplicativeType must be integral");
        numerator_ = numerator_ * m;
        reduce();
        return (*this);
    }

    /// @brief Unary division equals operator
    /// @tparam MultiplicativeType The type of the multiplicative operator
    /// @param m The value to divide the fraction by
    /// @return The fraction itself after being altered
    template <typename MultiplicativeType>
    Fraction_& operator/=(MultiplicativeType m) {
        static_assert(std::is_integral<MultiplicativeType>::value, "MultiplicativeType must be integral");
        denominator_ = denominator_ * m;
        reduce();
        return (*this);
    }

    /// @brief Unary plus equals operator with another fraction
    /// @param other The other fraction to add to this one
    /// @return The fraction itself after being altered
    Fraction_& operator+=(Fraction_ const& other) {
        auto common_denominator = lcm(denominator_, other.denominator_);
        auto our_denominator = common_denominator / denominator_;
        auto other_denominator = common_denominator / other.denominator_;
        numerator_ = (numerator_ * our_denominator) + (other.numerator_ * other_denominator);
        denominator_ = common_denominator;
        reduce();
        return (*this);
    }

    /// @brief Unary minus equals operator with another fraction
    /// @param other The other fraction to subtract from this one
    /// @return The fraction itself after being altered
    Fraction_& operator-=(Fraction_ const& other) {
        auto common_denominator = lcm(denominator_, other.denominator_);
        auto our_denominator = common_denominator / denominator_;
        auto other_denominator = common_denominator / other.denominator_;
        numerator_ = (numerator_ * our_denominator) - (other.numerator_ * other_denominator);
        denominator_ = common_denominator;
        reduce();
        return (*this);
    }

    /// @brief Unary multiplication equals operator with another fraction
    /// @param other The other fraction to multiply with this one
    /// @return The fraction itself after being altered
    Fraction_& operator*=(Fraction_ const& other) {
        numerator_ *= other.numerator_;
        denominator_ *= other.denominator_;
        reduce();
        return (*this);
    }

    /// @brief Unary division equals operator with another fraction
    /// @param other The other fraction to divide this one by
    /// @return The fraction itself after being altered
    Fraction_& operator/=(Fraction_ const& other) {
        numerator_ *= other.denominator_;
        denominator_ *= other.numerator_;
        reduce();
        return (*this);
    }

    /// @brief Binary plus operator
    /// @param a The first fraction
    /// @param b The second fraction
    /// @return The result of the addition
    friend Fraction_ operator+(Fraction_ const& a, Fraction_ const& b) {
        Fraction_ c;
        auto common_denominator = lcm(a.denominator_, b.denominator_);
        c.numerator_ = (a.numerator_ * (common_denominator / a.denominator_)) + (b.numerator_ * (common_denominator / b.denominator_));
        c.denominator_ = common_denominator;
        c.reduce();
        return c;
    }

    /// @brief Binary minus operator
    /// @param a The first fraction
    /// @param b The second fraction
    /// @return The result of the subtraction
    friend Fraction_ operator-(Fraction_ const& a, Fraction_ const& b) {
        Fraction_ c;
        auto common_denominator = lcm(a.denominator_, b.denominator_);
        c.numerator_ = (a.numerator_ * (common_denominator / a.denominator_)) - (b.numerator_ * (common_denominator / b.denominator_));
        c.denominator_ = common_denominator;
        c.reduce();
        return c;
    }

    /// @brief Binary multiplication operator
    /// @param a The first fraction
    /// @param b The second fraction
    /// @return The result of the multiplication
    friend Fraction_ operator*(Fraction_ const& a, Fraction_ const& b) {
        Fraction_ c;
        c.numerator_ = a.numerator_ * b.numerator_;
        c.denominator_ = a.denominator_ * b.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary division operator
    /// @param a The first fraction
    /// @param b The second fraction
    /// @return The result of the division
    friend Fraction_ operator/(Fraction_ const& a, Fraction_ const& b) {
        Fraction_ c;
        c.numerator_ = a.numerator_ * b.denominator_;
        c.denominator_ = a.denominator_ * b.numerator_;
        c.reduce();
        return c;
    }

    /// @brief Binary plus operator with a scalar
    /// @param a The first fraction
    /// @param b The scalar to add to the fraction
    /// @return The result of the addition
    template <typename AdditiveType>
    friend Fraction_ operator+(Fraction_ const& a, AdditiveType b) {
        Fraction_ c;
        c.numerator_ = a.numerator_ + (b * a.denominator_);
        c.denominator_ = a.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary addition operator with a scalar
    /// @param a The first fraction
    /// @param b The scalar to add to the fraction
    /// @return The result of the addition
    template <typename AdditiveType>
    friend Fraction_ operator+(AdditiveType b, Fraction_ const& a) {
        Fraction_ c;
        c.numerator_ = (b * a.denominator_) + a.numerator_;
        c.denominator_ = a.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary minus operator with a scalar and a Fraction
    /// @tparam AdditiveType
    /// @param b the scalar to subtract the fraction from
    /// @param a The fraction to subtract from the scalar
    /// @return The result of the subtraction
    template <typename AdditiveType>
    friend Fraction_ operator-(AdditiveType b, Fraction_ const& a) {
        Fraction_ c;
        c.numerator_ = (b * a.denominator_) - a.numerator_;
        c.denominator_ = a.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary minus operator with a scalar
    /// @tparam AdditiveType
    /// @param a The first fraction
    /// @param b The scalar to subtract from the fraction
    /// @return The result of the subtraction
    template <typename AdditiveType>
    friend Fraction_ operator-(Fraction_ const& a, AdditiveType b) {
        Fraction_ c;
        c.numerator_ = a.numerator_ - (b * a.denominator_);
        c.denominator_ = a.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary multiplication operator with a scalar
    /// @tparam MultiplicativeType
    /// @param a The first fraction
    /// @param b The scalar to multiply the fraction by
    /// @return The result of the multiplication
    template <typename MultiplicativeType>
    friend Fraction_ operator*(Fraction_ const& a, MultiplicativeType b) {
        Fraction_ c;
        c.numerator_ = a.numerator_ * b;
        c.denominator_ = a.denominator_;
        c.reduce();
        return c;
    }

    /// @brief Binary division operator with a scalar
    /// @tparam MultiplicativeType
    /// @param a The first fraction
    /// @param b The scalar to divide the fraction by
    /// @return The result of the division
    template <typename MultiplicativeType>
    friend Fraction_ operator/(Fraction_ const& a, MultiplicativeType b) {
        Fraction_ c;
        c.numerator_ = a.numerator_;
        c.denominator_ = a.denominator_ * b;
        c.reduce();
        return c;
    }

#if defined(UNITTEST)
    /// @brief Output operator for the fraction
    /// @param os The output stream
    /// @param f The fraction to output
    friend std::ostream& operator<<(std::ostream& os, Fraction_ const& f) { return os << "fraction=" << f.numerator_ << "/" << f.denominator_; }
#endif

    /// @brief Convert the fraction to another Type
    /// @tparam SomeType The type to convert to
    /// @return The converted value
    template <typename SomeType>
    SomeType as() const {
        return static_cast<SomeType>(numerator_) / static_cast<SomeType>(denominator_);
    }
};

using Fraction = Fraction_<int, int>;

}    // namespace core

#endif    // CORE_FRACTION_HPP
