#ifndef CORE_ENUMTYPE_HPP_
#define CORE_ENUMTYPE_HPP_

#include "iso.hpp"

namespace core {
/// A wraps an enumerated type and provides some syntactic sugar to make using said types easier as Error Codes.
/// Requires a default value of `None` to be set to 0. This allows for default constructing enums with known values.
/// @tparam ENUM_TYPE
template <typename ENUM_TYPE>
class EnumType {
public:
    static_assert(std::is_enum<ENUM_TYPE>::value, "ENUM_TYPE must be an enumerated type");
    static_assert(static_cast<std::underlying_type_t<ENUM_TYPE>>(ENUM_TYPE::None) == 0U, "ENUM_TYPE must have a None member which has a value of 0");

    /// Default Constructor
    EnumType()
        : value_(ENUM_TYPE::None) {}
    /// Parameter Constructor
    /// @param value The value to set
    EnumType(ENUM_TYPE value)
        : value_{value} {}

    /// Copy Constructor
    /// @param other The other EnumType to copy
    EnumType(const EnumType &other)
        : value_{other.value_} {}
    /// Copy Assignment Operator
    /// @param other The other EnumType to copy
    EnumType &operator=(const EnumType &other) {
        value_ = other.value_;
        return *this;
    }
    /// Move Constructor
    /// @param other The other EnumType to move
    EnumType(EnumType &&other)
        : value_{std::move(other.value_)} {}
    /// Move Assignment Operator
    /// @param other The other EnumType to move
    EnumType &operator=(EnumType &&other) {
        value_ = std::move(other.value_);
        other.value_ = ENUM_TYPE::None;
        return *this;
    }
    /// Destructor
    ~EnumType() = default;
    /// Equality Operator
    /// @param other The other EnumType to compare
    bool operator==(const EnumType &other) const { return value_ == other.value_; }
    /// Inequality Operator
    /// @param other The other EnumType to compare
    bool operator!=(const EnumType &other) const { return not operator==(other); }
    /// Equality to the value type
    /// @param value The value to compare
    bool operator==(ENUM_TYPE value) const { return value_ == value; }
    /// Inequality to the value type
    /// @param value The value to compare
    bool operator!=(ENUM_TYPE value) const { return not operator==(value); }
    /// Returns the value of the enum
    ENUM_TYPE get() const { return value_; }
    /// Returns the value of the enum via the underlying type
    /// @return The value of the enum
    constexpr typename std::underlying_type<ENUM_TYPE>::type value() const {
        return static_cast<typename std::underlying_type<ENUM_TYPE>::type>(value_);
    }

protected:
    ENUM_TYPE value_;
};

}    // namespace core

#endif    // CORE_ENUMTYPE_HPP_