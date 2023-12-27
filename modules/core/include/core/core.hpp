#ifndef CORE_HPP_
#define CORE_HPP_

/// @file
/// Core Library

#include <cstdint>
#include <cstddef>

#include "core/Span.hpp"
#include "core/Array.hpp"
#include "core/Split.hpp"
#include "core/Ring.hpp"
#include "core/Stack.hpp"
#include "core/Variant.hpp"
// #include "core/Optional.hpp"
#include "core/EnumType.hpp"

// C++ Requires some global symbols defined in order to compile.
extern "C" void __cxa_pure_virtual(void);

/// Placement new operator given pointer
/// @note Required for C++ Compatibility
void *operator new(std::size_t bytes, void *pointer);

/// Placement new operator given address
/// @note _NOT_ Required for C++ Compatibility (customized for device-as-object)
void *operator new(std::size_t bytes, uintptr_t address);

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
