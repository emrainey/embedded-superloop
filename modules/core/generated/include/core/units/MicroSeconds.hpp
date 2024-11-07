#pragma once

// clang-format off

/// @file
/// AUTO GENERATED FILE, DO NOT MODIFY!
/// Header for the MicroSeconds unit of measurement

#include <type_traits>
#include <cstdint>

#if defined(UNITTEST)
#include <iostream>
#endif

#include "core/units/Unit.hpp"

namespace core {
namespace units {
class MicroSeconds : public Unit<uint64_t, 1> {
public:
    using StorageType = uint64_t;
    constexpr MicroSeconds()
        : Unit<uint64_t, 1>{} {
    }
    constexpr explicit MicroSeconds(uint64_t v)
        : Unit<uint64_t, 1>{v} {
    }
    // constexpr MicroSeconds(MicroSeconds& other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    constexpr MicroSeconds(MicroSeconds const& other)
        : Unit<uint64_t, 1>{other.value()} {
    }
    // constexpr MicroSeconds(MicroSeconds volatile & other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    // constexpr MicroSeconds(MicroSeconds const volatile & other)
    //     : Unit<uint64_t, 1>{other.value()} {
    // }
    constexpr MicroSeconds& operator=(MicroSeconds& other) {
        value_ = other.value();
       return *this;
    }
    constexpr MicroSeconds& operator=(MicroSeconds const& other) {
        value_ = other.value();
        return *this;
    }
    inline MicroSeconds& operator=(MicroSeconds volatile& other) {
        value_ = other.value();
        return *this;
    }
    // constexpr MicroSeconds& operator=(MicroSeconds const volatile& other) {
    //     value_ = other.value();
    //     return *this;
    // }
    inline MicroSeconds volatile& operator=(MicroSeconds& other) volatile {
        value_ = other.value();
        return *this;
    }
    // constexpr MicroSeconds volatile& operator=(MicroSeconds const& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr MicroSeconds volatile& operator=(MicroSeconds volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    // constexpr MicroSeconds volatile& operator=(MicroSeconds const volatile& other) volatile {
    //     value_ = other.value();
    //     return *this;
    // }
    friend constexpr inline MicroSeconds operator+(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs.value() + rhs.value()};
    }
    friend constexpr inline MicroSeconds operator-(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs.value() - rhs.value()};
    }
    friend constexpr inline MicroSeconds operator*(MicroSeconds const& lhs, uint64_t rhs) {
        return MicroSeconds{lhs.value() * rhs};
    }
    friend constexpr inline MicroSeconds operator/(MicroSeconds const& lhs, uint64_t rhs) {
        return MicroSeconds{lhs.value() / rhs};
    }
    friend constexpr inline MicroSeconds operator*(uint64_t lhs, MicroSeconds const& rhs) {
        return MicroSeconds{lhs * rhs.value()};
    }
    friend constexpr inline bool operator==(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() == rhs.value();
    }
    friend constexpr inline bool operator!=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() != rhs.value();
    }
    friend constexpr inline bool operator<(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() < rhs.value();
    }
    friend constexpr inline bool operator<=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() <= rhs.value();
    }
    friend constexpr inline bool operator>(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() > rhs.value();
    }
    friend constexpr inline bool operator>=(MicroSeconds const& lhs, MicroSeconds const& rhs) {
        return lhs.value() >= rhs.value();
    }
};

#if defined(UNITTEST)
constexpr std::ostream& operator<<(std::ostream& os, MicroSeconds const& v) {
        os << "MicroSeconds" << " " << v.value();
        return os;
    }
#endif

}    // namespace units
}    // namespace core

// clang-format on
