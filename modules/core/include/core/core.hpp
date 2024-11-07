#ifndef CORE_HPP_
#define CORE_HPP_

/// @file
/// Core Library

#include <cstdint>
#include <cstddef>

#include "core/std.hpp"
#include "core/Span.hpp"
#include "core/Array.hpp"
#include "core/Split.hpp"
#include "core/Ring.hpp"
#include "core/Status.hpp"
#include "core/Stack.hpp"
#include "core/Variant.hpp"
// #include "core/Optional.hpp"
#include "core/EnumType.hpp"
#include "core/Intervals.hpp"

// /// A feature flag
// enum class Feature : std::uint32_t {
//     Disabled = 0U,
//     Enabled = 1U,
// };

// /// @brief The global operator for testing a feature flag
// /// @param feature The flag to test
// inline explicit operator bool(Feature feature) const {
//     return feature == Feature::Enabled;
// }

// /// An inverted feature flag
// enum class InvertedFeature : std::uint32_t {
//     Disabled = 1U,
//     Enabled = 0U,
// };

// /// @brief The global operator for testing a feature flag
// /// @param feature The flag to test
// inline explicit operator bool(InvertedFeature feature) const {
//     return feature == InvertedFeature::Enabled;
// }

#endif    // CORE_HPP_
