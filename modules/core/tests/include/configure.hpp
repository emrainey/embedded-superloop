#pragma once

/// @file
/// A fake configuration header

namespace core {
namespace units {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{128U};
/// @brief Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{1.0F / static_cast<float>(ticks_per_second)};
}    // namespace units
}    // namespace core

namespace cortex {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{core::units::ticks_per_second};
/// @brief Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{core::units::tick_period};
}    // namespace cortex
