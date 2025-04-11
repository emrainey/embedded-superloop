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

/// @brief The core namespace which holds the generic but embedded focused template types
namespace core {
/// @brief Used to indicate of a feature is enabled or disabled
class Feature {
public:
    /// A feature flag
    enum class Flag : std::uint32_t {
        Disabled = 0U,
        Enabled = 1U,
    };

    /// @brief The default constructor
    /// @param value The value to assign
    consteval Feature(Flag value)
        : value_{value} {}

    /// Used to indicate if the feature is enabled.
    /// @return True if enabled, false otherwise
    consteval explicit operator bool() const { return value_ == Flag::Enabled; }

protected:
    Flag value_;    ///< The value of the feature flag
};
}    // namespace core
namespace {    // anonymous
static constexpr core::Feature kFeatureTest{core::Feature::Flag::Enabled};
static_assert((kFeatureTest), "Feature Test Failed");
static_assert(bool(kFeatureTest), "Feature Test Failed");
static_assert((not core::Feature{core::Feature::Flag::Disabled}), "Feature Test Failed");
}    // namespace

#endif    // CORE_HPP_
