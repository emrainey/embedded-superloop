#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the SquareMeters unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class SquareMeters : public Unit<float, 2> {
public:
    constexpr SquareMeters()
        : Unit<float, 2>{} {
    }
    constexpr explicit SquareMeters(float v)
        : Unit<float, 2>{v} {
    }
    // constexpr SquareMeters(SquareMeters& other)
    //     : Unit<float, 2>{other.value()} {
    // }
    constexpr SquareMeters(SquareMeters const& other)
        : Unit<float, 2>{other.value()} {
    }
    // constexpr SquareMeters(SquareMeters volatile & other)
    //     : Unit<float, 2>{other.value()} {
    // }
    // constexpr SquareMeters(SquareMeters const volatile & other)
    //     : Unit<float, 2>{other.value()} {
    // }
    constexpr SquareMeters& operator=(SquareMeters& other) {
        value_ = other.value();
       return *this;
    }
    constexpr SquareMeters& operator=(SquareMeters const& other) {
        value_ = other.value();
        return *this;
    }
    inline SquareMeters& operator=(SquareMeters volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr SquareMeters& operator=(SquareMeters const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline SquareMeters volatile& operator=(SquareMeters& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr SquareMeters volatile& operator=(SquareMeters const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr SquareMeters volatile& operator=(SquareMeters volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr SquareMeters volatile& operator=(SquareMeters const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline SquareMeters operator+(SquareMeters const& lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs.value() + rhs.value()};
    }
    friend constexpr inline SquareMeters operator-(SquareMeters const& lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs.value() - rhs.value()};
    }
    friend constexpr inline SquareMeters operator*(SquareMeters const& lhs, float rhs) {
        return SquareMeters{lhs.value() * rhs};
    }
    friend constexpr inline SquareMeters operator/(SquareMeters const& lhs, float rhs) {
        return SquareMeters{lhs.value() / rhs};
    }
    friend constexpr inline SquareMeters operator*(float lhs, SquareMeters const& rhs) {
        return SquareMeters{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(SquareMeters const& lhs, SquareMeters const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, SquareMeters const& v) {
        os << "SquareMeters" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
