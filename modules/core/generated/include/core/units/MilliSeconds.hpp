#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the MilliSeconds unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class MilliSeconds : public Unit<uint32_t, 1> {
public:
    using StorageType = uint32_t;
    constexpr MilliSeconds()
        : Unit<uint32_t, 1>{} {
    }
    constexpr explicit MilliSeconds(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }
    // constexpr MilliSeconds(MilliSeconds& other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr MilliSeconds(MilliSeconds const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }
    // constexpr MilliSeconds(MilliSeconds volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    // constexpr MilliSeconds(MilliSeconds const volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr MilliSeconds& operator=(MilliSeconds& other) {
        value_ = other.value();
       return *this;
    }
    constexpr MilliSeconds& operator=(MilliSeconds const& other) {
        value_ = other.value();
        return *this;
    }
    inline MilliSeconds& operator=(MilliSeconds volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr MilliSeconds& operator=(MilliSeconds const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline MilliSeconds volatile& operator=(MilliSeconds& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr MilliSeconds volatile& operator=(MilliSeconds const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr MilliSeconds volatile& operator=(MilliSeconds volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr MilliSeconds volatile& operator=(MilliSeconds const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline MilliSeconds operator+(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs.value() + rhs.value()};
    }
    friend constexpr inline MilliSeconds operator-(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs.value() - rhs.value()};
    }
    friend constexpr inline MilliSeconds operator*(MilliSeconds const& lhs, uint32_t rhs) {
        return MilliSeconds{lhs.value() * rhs};
    }
    friend constexpr inline MilliSeconds operator/(MilliSeconds const& lhs, uint32_t rhs) {
        return MilliSeconds{lhs.value() / rhs};
    }
    friend constexpr inline MilliSeconds operator*(uint32_t lhs, MilliSeconds const& rhs) {
        return MilliSeconds{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(MilliSeconds const& lhs, MilliSeconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, MilliSeconds const& v) {
        os << "MilliSeconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
