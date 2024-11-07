#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Ticks unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Ticks : public Unit<uint32_t, 1> {
public:
    using StorageType = uint32_t;
    constexpr Ticks()
        : Unit<uint32_t, 1>{} {
    }
    constexpr explicit Ticks(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }
    // constexpr Ticks(Ticks& other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr Ticks(Ticks const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }
    // constexpr Ticks(Ticks volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    // constexpr Ticks(Ticks const volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr Ticks& operator=(Ticks& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Ticks& operator=(Ticks const& other) {
        value_ = other.value();
        return *this;
    }
    inline Ticks& operator=(Ticks volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Ticks& operator=(Ticks const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Ticks volatile& operator=(Ticks& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Ticks volatile& operator=(Ticks const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Ticks volatile& operator=(Ticks volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Ticks volatile& operator=(Ticks const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Ticks operator+(Ticks const& lhs, Ticks const& rhs) {
        return Ticks{lhs.value() + rhs.value()};
    }
    friend constexpr inline Ticks operator-(Ticks const& lhs, Ticks const& rhs) {
        return Ticks{lhs.value() - rhs.value()};
    }
    friend constexpr inline Ticks operator*(Ticks const& lhs, uint32_t rhs) {
        return Ticks{lhs.value() * rhs};
    }
    friend constexpr inline Ticks operator/(Ticks const& lhs, uint32_t rhs) {
        return Ticks{lhs.value() / rhs};
    }
    friend constexpr inline Ticks operator*(uint32_t lhs, Ticks const& rhs) {
        return Ticks{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Ticks const& lhs, Ticks const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Ticks const& v) {
        os << "Ticks" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
