#include "core/Conversions.hpp"
#include "core/Units.hpp"

namespace core {
namespace units {

// Holds the global values for the Conversion to and From Iotas
extern std::uint32_t time_source_iotas_per_second;
extern std::uint32_t time_source_iotas_per_millisecond;
extern std::uint32_t time_source_iotas_per_microsecond;

MicroSeconds ConvertToMicroSeconds(Iota const& value) {
    MicroSeconds::StorageType v =
        static_cast<MicroSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(time_source_iotas_per_microsecond));
    return MicroSeconds{v};
}

Iota ConvertToIota(MicroSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MicroSeconds::StorageType>(time_source_iotas_per_microsecond));
    return Iota{v};
}

MilliSeconds ConvertToMilliSeconds(Iota const& value) {
    MilliSeconds::StorageType v =
        static_cast<MilliSeconds::StorageType>(value.value() / static_cast<Iota::StorageType>(time_source_iotas_per_millisecond));
    return MilliSeconds{v};
}

Iota ConvertToIota(MilliSeconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<MilliSeconds::StorageType>(time_source_iotas_per_millisecond));
    return Iota{v};
}

Seconds ConvertToSeconds(Iota const& value) {
    Seconds::StorageType v = static_cast<Seconds::StorageType>(value.value()) / static_cast<Seconds::StorageType>(time_source_iotas_per_second);
    return Seconds{v};
}

Iota ConvertToIota(Seconds const& value) {
    Iota::StorageType v = static_cast<Iota::StorageType>(value.value() * static_cast<Seconds::StorageType>(time_source_iotas_per_second));
    return Iota{v};
}

}    // namespace units
}    // namespace core
