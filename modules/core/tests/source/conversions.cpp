#include "core/Conversions.hpp"
#include "configure.hpp"
#include "core/Units.hpp"

/// @file
/// @brief Test implementation of conversion functions for unit testing.
/// This provides the definitions required by catch2-conversions.cpp tests.

namespace core {
namespace units {

// External declarations for test-specific iota rates
// These are defined in catch2-conversions.cpp
extern std::uint32_t timer2_iotas_per_second;
extern std::uint32_t timer2_iotas_per_millisecond;
extern std::uint32_t timer2_iotas_per_microsecond;

MicroSeconds ConvertToMicroSeconds(Iota const& value) {
    MicroSeconds::StorageType v =
        static_cast<MicroSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(timer2_iotas_per_microsecond));
    return MicroSeconds{v};
}

Iota ConvertToIota(MicroSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MicroSeconds::StorageType>(timer2_iotas_per_microsecond));
    return Iota{v};
}

MilliSeconds ConvertToMilliSeconds(Iota const& value) {
    MilliSeconds::StorageType v =
        static_cast<MilliSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(timer2_iotas_per_millisecond));
    return MilliSeconds{v};
}

Iota ConvertToIota(MilliSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MilliSeconds::StorageType>(timer2_iotas_per_millisecond));
    return Iota{v};
}

Seconds ConvertToSeconds(Iota const& value) {
    Seconds::StorageType v = static_cast<Seconds::StorageType>(value.value()) / static_cast<Seconds::StorageType>(timer2_iotas_per_second);
    return Seconds{v};
}

Iota ConvertToIota(Seconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<Seconds::StorageType>(timer2_iotas_per_second));
    return Iota{v};
}

Ticks ConvertToTicks(Seconds const& time) {
    // e.g. 1/2 seconds = 1/2 * 128 ticks = 64.0 ticks
    float fraction = time.value() * static_cast<float>(cortex::ticks_per_second);
    return Ticks{static_cast<Ticks::StorageType>(fraction)};
}

Seconds ConvertToSeconds(Ticks const& ticks) {
    // e.g. 64 ticks = 64 / 128 seconds = 0.5 seconds
    float fraction = static_cast<Seconds::StorageType>(ticks.value()) / static_cast<Seconds::StorageType>(cortex::ticks_per_second);
    return Seconds{fraction};
}

}    // namespace units
}    // namespace core
