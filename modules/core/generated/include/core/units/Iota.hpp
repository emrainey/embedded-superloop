#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the Iota unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class Iota : public Unit<uint64_t, 1> {
public:
    using StorageType = uint64_t;
    constexpr Iota()
        : Unit<uint64_t, 1>{} {
    }
    constexpr explicit Iota(uint64_t v)
        : Unit<uint64_t, 1>{v} {
    }
    // constexpr Iota(Iota& other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    constexpr Iota(Iota const& other)
        : Unit<uint64_t, 1>{other.value()} {
    }
    // constexpr Iota(Iota volatile & other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    // constexpr Iota(Iota const volatile & other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    constexpr Iota& operator=(Iota& other) {
        value_ = other.value();
       return *this;
    }
    constexpr Iota& operator=(Iota const& other) {
        value_ = other.value();
        return *this;
    }
    inline Iota& operator=(Iota volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr Iota& operator=(Iota const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline Iota volatile& operator=(Iota& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr Iota volatile& operator=(Iota const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Iota volatile& operator=(Iota volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr Iota volatile& operator=(Iota const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline Iota operator+(Iota const& lhs, Iota const& rhs) {
        return Iota{lhs.value() + rhs.value()};
    }
    friend constexpr inline Iota operator-(Iota const& lhs, Iota const& rhs) {
        return Iota{lhs.value() - rhs.value()};
    }
    friend constexpr inline Iota operator*(Iota const& lhs, uint64_t rhs) {
        return Iota{lhs.value() * rhs};
    }
    friend constexpr inline Iota operator/(Iota const& lhs, uint64_t rhs) {
        return Iota{lhs.value() / rhs};
    }
    friend constexpr inline Iota operator*(uint64_t lhs, Iota const& rhs) {
        return Iota{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(Iota const& lhs, Iota const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(Iota const& lhs, Iota const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(Iota const& lhs, Iota const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(Iota const& lhs, Iota const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(Iota const& lhs, Iota const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(Iota const& lhs, Iota const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, Iota const& v) {
        os << "Iota" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
