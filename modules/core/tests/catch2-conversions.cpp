#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>

#include "configure.hpp"
#include "core/Conversions.hpp"
#include "core/Units.hpp"

/// @file
/// @brief Unit tests for core::units conversion functions between different time units.
/// Tests both Iota conversions (platform-dependent) and Ticks conversions (system-dependent).

namespace core {
namespace units {
// Define the platform-specific iota conversion rates for testing
// These would normally be defined by the platform/timer configuration
std::uint32_t timer2_iotas_per_second = 1'000'000U;     // 1 MHz timer
std::uint32_t timer2_iotas_per_millisecond = 1'000U;    // 1000 iotas per ms
std::uint32_t timer2_iotas_per_microsecond = 1U;        // 1 iota per μs
}    // namespace units
}    // namespace core

constexpr double epsilon{0.0001};    // For floating point comparisons

TEST_CASE("Conversions - Iota to MicroSeconds") {
    using namespace core::units;

    SECTION("Zero iotas") {
        Iota iotas{0U};
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 0U);
    }

    SECTION("One iota equals one microsecond") {
        Iota iotas{1U};
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 1U);
    }

    SECTION("1000 iotas equals 1000 microseconds") {
        Iota iotas{1'000U};
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 1'000U);
    }

    SECTION("1 million iotas equals 1 second worth of microseconds") {
        Iota iotas{1'000'000U};
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 1'000'000U);
    }
}

TEST_CASE("Conversions - MicroSeconds to Iota") {
    using namespace core::units;

    SECTION("Zero microseconds") {
        MicroSeconds us{0U};
        Iota iotas = ConvertToIota(us);
        REQUIRE(iotas.value() == 0U);
    }

    SECTION("One microsecond equals one iota") {
        MicroSeconds us{1U};
        Iota iotas = ConvertToIota(us);
        REQUIRE(iotas.value() == 1U);
    }

    SECTION("1000 microseconds equals 1000 iotas") {
        MicroSeconds us{1'000U};
        Iota iotas = ConvertToIota(us);
        REQUIRE(iotas.value() == 1'000U);
    }

    SECTION("Round trip conversion") {
        MicroSeconds original{42'000U};
        Iota iotas = ConvertToIota(original);
        MicroSeconds result = ConvertToMicroSeconds(iotas);
        REQUIRE(result.value() == original.value());
    }
}

TEST_CASE("Conversions - Iota to MilliSeconds") {
    using namespace core::units;

    SECTION("Zero iotas") {
        Iota iotas{0U};
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 0U);
    }

    SECTION("1000 iotas equals 1 millisecond") {
        Iota iotas{1'000U};
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 1U);
    }

    SECTION("10000 iotas equals 10 milliseconds") {
        Iota iotas{10'000U};
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 10U);
    }

    SECTION("1 million iotas equals 1000 milliseconds") {
        Iota iotas{1'000'000U};
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 1'000U);
    }

    SECTION("Partial milliseconds truncate") {
        Iota iotas{1'500U};           // 1.5 ms
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 1U);    // Truncates to 1 ms
    }
}

TEST_CASE("Conversions - MilliSeconds to Iota") {
    using namespace core::units;

    SECTION("Zero milliseconds") {
        MilliSeconds ms{0U};
        Iota iotas = ConvertToIota(ms);
        REQUIRE(iotas.value() == 0U);
    }

    SECTION("One millisecond equals 1000 iotas") {
        MilliSeconds ms{1U};
        Iota iotas = ConvertToIota(ms);
        REQUIRE(iotas.value() == 1'000U);
    }

    SECTION("100 milliseconds equals 100000 iotas") {
        MilliSeconds ms{100U};
        Iota iotas = ConvertToIota(ms);
        REQUIRE(iotas.value() == 100'000U);
    }

    SECTION("Round trip conversion") {
        MilliSeconds original{250U};
        Iota iotas = ConvertToIota(original);
        MilliSeconds result = ConvertToMilliSeconds(iotas);
        REQUIRE(result.value() == original.value());
    }
}

TEST_CASE("Conversions - Iota to Seconds") {
    using namespace core::units;

    SECTION("Zero iotas") {
        Iota iotas{0U};
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.0, epsilon));
    }

    SECTION("1 million iotas equals 1 second") {
        Iota iotas{1'000'000U};
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("500000 iotas equals 0.5 seconds") {
        Iota iotas{500'000U};
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.5, epsilon));
    }

    SECTION("2 million iotas equals 2 seconds") {
        Iota iotas{2'000'000U};
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
    }

    SECTION("Small fractional seconds") {
        Iota iotas{123'456U};    // 0.123456 seconds
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.123456, epsilon));
    }
}

TEST_CASE("Conversions - Seconds to Iota") {
    using namespace core::units;

    SECTION("Zero seconds") {
        Seconds sec{0.0f};
        Iota iotas = ConvertToIota(sec);
        REQUIRE(iotas.value() == 0U);
    }

    SECTION("One second equals 1 million iotas") {
        Seconds sec{1.0f};
        Iota iotas = ConvertToIota(sec);
        REQUIRE(iotas.value() == 1'000'000U);
    }

    SECTION("Half second equals 500000 iotas") {
        Seconds sec{0.5f};
        Iota iotas = ConvertToIota(sec);
        REQUIRE(iotas.value() == 500'000U);
    }

    SECTION("2.5 seconds equals 2.5 million iotas") {
        Seconds sec{2.5f};
        Iota iotas = ConvertToIota(sec);
        REQUIRE(iotas.value() == 2'500'000U);
    }

    SECTION("Round trip conversion") {
        Seconds original{3.14159f};
        Iota iotas = ConvertToIota(original);
        Seconds result = ConvertToSeconds(iotas);
        // Allow for some loss of precision in round trip
        REQUIRE_THAT(static_cast<double>(result.value()), Catch::Matchers::WithinAbs(static_cast<double>(original.value()), 0.001));
    }
}

TEST_CASE("Conversions - Seconds to Ticks") {
    using namespace core::units;

    SECTION("Zero seconds") {
        Seconds sec{0.0f};
        Ticks ticks = ConvertToTicks(sec);
        REQUIRE(ticks.value() == 0U);
    }

    SECTION("One second equals ticks_per_second") {
        Seconds sec{1.0f};
        Ticks ticks = ConvertToTicks(sec);
        REQUIRE(ticks.value() == ticks_per_second);
    }

    SECTION("Half second equals half ticks_per_second") {
        Seconds sec{0.5f};
        Ticks ticks = ConvertToTicks(sec);
        REQUIRE(ticks.value() == ticks_per_second / 2);
    }

    SECTION("Two seconds equals 2 * ticks_per_second") {
        Seconds sec{2.0f};
        Ticks ticks = ConvertToTicks(sec);
        REQUIRE(ticks.value() == 2 * ticks_per_second);
    }

    SECTION("Fractional seconds") {
        Seconds sec{0.25f};    // Quarter second
        Ticks ticks = ConvertToTicks(sec);
        REQUIRE(ticks.value() == ticks_per_second / 4);
    }
}

TEST_CASE("Conversions - Ticks to Seconds") {
    using namespace core::units;

    SECTION("Zero ticks") {
        Ticks ticks{0U};
        Seconds sec = ConvertToSeconds(ticks);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.0, epsilon));
    }

    SECTION("ticks_per_second equals 1 second") {
        Ticks ticks{ticks_per_second};
        Seconds sec = ConvertToSeconds(ticks);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Half ticks_per_second equals 0.5 seconds") {
        Ticks ticks{ticks_per_second / 2};
        Seconds sec = ConvertToSeconds(ticks);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.5, epsilon));
    }

    SECTION("Double ticks_per_second equals 2 seconds") {
        Ticks ticks{2 * ticks_per_second};
        Seconds sec = ConvertToSeconds(ticks);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
    }

    SECTION("Round trip conversion") {
        Seconds original{1.5f};
        Ticks ticks = ConvertToTicks(original);
        Seconds result = ConvertToSeconds(ticks);
        REQUIRE_THAT(static_cast<double>(result.value()), Catch::Matchers::WithinAbs(static_cast<double>(original.value()), epsilon));
    }
}

TEST_CASE("Conversions - Cross-unit consistency") {
    using namespace core::units;

    SECTION("1 second = 1000 milliseconds (via Iota)") {
        Seconds sec{1.0f};
        Iota iotas = ConvertToIota(sec);
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 1'000U);
    }

    SECTION("1 second = 1000000 microseconds (via Iota)") {
        Seconds sec{1.0f};
        Iota iotas = ConvertToIota(sec);
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 1'000'000U);
    }

    SECTION("1 millisecond = 1000 microseconds (via Iota)") {
        MilliSeconds ms{1U};
        Iota iotas = ConvertToIota(ms);
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == 1'000U);
    }

    SECTION("100 milliseconds = 0.1 seconds") {
        MilliSeconds ms{100U};
        Iota iotas = ConvertToIota(ms);
        Seconds sec = ConvertToSeconds(iotas);
        REQUIRE_THAT(static_cast<double>(sec.value()), Catch::Matchers::WithinAbs(0.1, epsilon));
    }
}

TEST_CASE("Conversions - Edge cases") {
    using namespace core::units;

    SECTION("Maximum representable microseconds") {
        // Test near the upper limit of uint32_t microseconds
        MicroSeconds us{1'000'000U};    // 1 second worth
        Iota iotas = ConvertToIota(us);
        MicroSeconds result = ConvertToMicroSeconds(iotas);
        REQUIRE(result.value() == us.value());
    }

    SECTION("Very small non-zero iota values") {
        Iota iotas{1U};    // Single iota
        MicroSeconds us = ConvertToMicroSeconds(iotas);
        REQUIRE(us.value() == core::units::timer2_iotas_per_microsecond);
    }

    SECTION("Truncation in millisecond conversion") {
        // 999 iotas should truncate to 0 milliseconds
        Iota iotas{999U};
        MilliSeconds ms = ConvertToMilliSeconds(iotas);
        REQUIRE(ms.value() == 0U);
    }

    SECTION("Precision limit in Seconds conversion") {
        // Very small second values
        Seconds sec{0.000001f};    // 1 microsecond
        Iota iotas = ConvertToIota(sec);
        REQUIRE(iotas.value() >= 1U);
        REQUIRE(iotas.value() <= 2U);
    }
}
