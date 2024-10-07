#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the CubicMeters unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class CubicMeters : public Unit<float, 3> {
public:
    constexpr CubicMeters()
        : Unit<float, 3>{} {
    }
    constexpr explicit CubicMeters(float v)
        : Unit<float, 3>{v} {
    }
    // constexpr CubicMeters(CubicMeters& other)
    //     : Unit<float, 3>{other.value()} {
    // }
    constexpr CubicMeters(CubicMeters const& other)
        : Unit<float, 3>{other.value()} {
    }
    // constexpr CubicMeters(CubicMeters volatile & other)
    //     : Unit<float, 3>{other.value()} {
    // }
    // constexpr CubicMeters(CubicMeters const volatile & other)
    //     : Unit<float, 3>{other.value()} {
    // }
    constexpr CubicMeters& operator=(CubicMeters& other) {
        value_ = other.value();
       return *this;
    }
    constexpr CubicMeters& operator=(CubicMeters const& other) {
        value_ = other.value();
        return *this;
    }
    inline CubicMeters& operator=(CubicMeters volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr CubicMeters& operator=(CubicMeters const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline CubicMeters volatile& operator=(CubicMeters& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr CubicMeters volatile& operator=(CubicMeters const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr CubicMeters volatile& operator=(CubicMeters volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr CubicMeters volatile& operator=(CubicMeters const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline CubicMeters operator+(CubicMeters const& lhs, CubicMeters const& rhs) {
        return CubicMeters{lhs.value() + rhs.value()};
    }
    friend constexpr inline CubicMeters operator-(CubicMeters const& lhs, CubicMeters const& rhs) {
        return CubicMeters{lhs.value() - rhs.value()};
    }
    friend constexpr inline CubicMeters operator*(CubicMeters const& lhs, float rhs) {
        return CubicMeters{lhs.value() * rhs};
    }
    friend constexpr inline CubicMeters operator/(CubicMeters const& lhs, float rhs) {
        return CubicMeters{lhs.value() / rhs};
    }
    friend constexpr inline CubicMeters operator*(float lhs, CubicMeters const& rhs) {
        return CubicMeters{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(CubicMeters const& lhs, CubicMeters const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, CubicMeters const& v) {
        os << "CubicMeters" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
