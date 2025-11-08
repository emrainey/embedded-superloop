#pragma once

/// @file
/// A fake configuration header

namespace core {
namespace units {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{128U};
}    // namespace units
}    // namespace core

namespace cortex {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{core::units::ticks_per_second};
}    // namespace cortex
