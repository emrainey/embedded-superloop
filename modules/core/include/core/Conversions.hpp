#ifndef CORE_CONVERSIONS_HPP_
#define CORE_CONVERSIONS_HPP_

#if not defined(BOARD_HPP_)
#error "This file should only be included inside board.hpp as it depends on board specific definitions."
#endif

namespace core {
namespace units {
constexpr MicroSeconds ConvertToMicroSeconds(Iota const& value) {
    MicroSeconds::StorageType v =
        static_cast<MicroSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(core::units::iota_per_microsecond));
    return MicroSeconds{v};
}
constexpr Iota ConvertToIota(MicroSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MicroSeconds::StorageType>(core::units::iota_per_microsecond));
    return Iota{v};
}
constexpr MilliSeconds ConvertToMilliSeconds(Iota const& value) {
    MilliSeconds::StorageType v =
        static_cast<MilliSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(core::units::iota_per_millisecond));
    return MilliSeconds{v};
}
constexpr Iota ConvertToIota(MilliSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MilliSeconds::StorageType>(core::units::iota_per_millisecond));
    return Iota{v};
}

/// @brief Converts Iota to Seconds
/// @param value The iota value to convert
/// @return The Seconds value
constexpr Seconds ConvertToSeconds(Iota const& value) {
    Seconds::StorageType v = static_cast<Seconds::StorageType>(value.value()) / static_cast<Seconds::StorageType>(core::units::iota_per_second);
    return Seconds{v};
}

/// @brief Converts Seconds to Iota
/// @param value The Seconds value to convert
/// @return The Iota value
constexpr Iota ConvertToIota(Seconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<Seconds::StorageType>(core::units::iota_per_second));
    return Iota{v};
}

/// @brief Converts Seconds to Ticks
/// @param time The time to convert
/// @return The Ticks value
constexpr Ticks ConvertToTicks(Seconds const& time) {
    // e.g. 1/2 seconds = 1/2 * 128 ticks = 64.0 ticks
    float fraction = time.value() * core::units::ticks_per_second;
    return Ticks{static_cast<Ticks::StorageType>(fraction)};
}

/// @brief Converts Ticks to Seconds
/// @param ticks The ticks to convert
/// @return The Seconds value
constexpr Seconds ConvertToSeconds(Ticks const& ticks) {
    // e.g. 64 ticks = 64 / 128 seconds = 0.5 seconds
    float fraction = static_cast<Seconds::StorageType>(ticks.value()) / static_cast<Seconds::StorageType>(core::units::ticks_per_second);
    return Seconds{fraction};
}

}    // namespace units
}    // namespace core

#endif    // CORE_CONVERSIONS_HPP_
