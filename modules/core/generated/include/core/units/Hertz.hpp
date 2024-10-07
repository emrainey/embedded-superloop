#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Hertz unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Hertz : public Unit<uint32_t, 1> {
public:
    constexpr Hertz()
        : Unit<uint32_t, 1>{} {
    }
    constexpr explicit Hertz(uint32_t v)
        : Unit<uint32_t, 1>{v} {
    }
    // constexpr Hertz(Hertz& other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr Hertz(Hertz const& other)
        : Unit<uint32_t, 1>{other.value()} {
    }
    // constexpr Hertz(Hertz volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    // constexpr Hertz(Hertz const volatile & other)
    //     : Unit<uint32_t, 1>{other.value()} {
    // }
    constexpr Hertz& operator=(Hertz& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Hertz& operator=(Hertz const& other) {
        value_ = other.value();
        return *this;
    }
    inline Hertz& operator=(Hertz volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Hertz& operator=(Hertz const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Hertz volatile& operator=(Hertz& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Hertz volatile& operator=(Hertz const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Hertz volatile& operator=(Hertz volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Hertz volatile& operator=(Hertz const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Hertz operator+(Hertz const& lhs, Hertz const& rhs) {
        return Hertz{lhs.value() + rhs.value()};
    }
    friend constexpr inline Hertz operator-(Hertz const& lhs, Hertz const& rhs) {
        return Hertz{lhs.value() - rhs.value()};
    }
    friend constexpr inline Hertz operator*(Hertz const& lhs, uint32_t rhs) {
        return Hertz{lhs.value() * rhs};
    }
    friend constexpr inline Hertz operator/(Hertz const& lhs, uint32_t rhs) {
        return Hertz{lhs.value() / rhs};
    }
    friend constexpr inline Hertz operator*(uint32_t lhs, Hertz const& rhs) {
        return Hertz{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Hertz const& lhs, Hertz const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Hertz const& v) {
        os << "Hertz" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
