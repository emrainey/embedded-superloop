// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "core/Units.hpp"

#include <iostream>

namespace core {
namespace units {
/// @brief The number of Ticks in a second for this board
constexpr static std::uint32_t ticks_per_second{128U};
/// @brief Defines the system tick period value used to represent the passage of time in floats
constexpr static float tick_period{1.0F / static_cast<float>(ticks_per_second)};
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_microsecond = 12U;
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_millisecond = 12'000U;
/// @brief The number of iota per second (based on the ClockTree)
constexpr static std::uint32_t iota_per_second = 12'000'000U;
}    // namespace units
}    // namespace core
#define BOARD_HPP_    // this is to emulate the board.hpp include
// This depends on the board specific stated conversions above
#include "core/Conversions.hpp"

constexpr double epsilon{0.0625};    // 1/16th of a unit, used for floating point comparisons

TEST_CASE("Units - Equations") {
    core::units::Volts v{1.0f};
    core::units::Amperes i{2.0f};
    core::units::Ohms r{4.0f};

    SECTION("Ohm's Law") {
        auto v2 = i * r;
        REQUIRE_THAT(static_cast<double>(v2.value()), Catch::Matchers::WithinAbs(8.0, epsilon));
        v2 = r * i;
        REQUIRE_THAT(static_cast<double>(v2.value()), Catch::Matchers::WithinAbs(8.0, epsilon));

        auto i2 = v / r;
        REQUIRE_THAT(static_cast<double>(i2.value()), Catch::Matchers::WithinAbs(0.25, epsilon));

        auto r2 = v / i;
        REQUIRE_THAT(static_cast<double>(r2.value()), Catch::Matchers::WithinAbs(0.5, epsilon));
    }
    SECTION("Power") {
        auto p = v * i;
        REQUIRE_THAT(static_cast<double>(p.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
        p = i * v;
        REQUIRE_THAT(static_cast<double>(p.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
    }
    SECTION("Literals") {
        using namespace core::units;
        auto v2 = 1.0_V;
        auto i2 = 1.0_A;
        auto r2 = 1.0_Ohm;
        auto p = v2 / i2;
        REQUIRE_THAT(static_cast<double>(p.value()), Catch::Matchers::WithinAbs(static_cast<double>(r2.value()), epsilon));

        auto v3 = 1.0_mV;
        auto i3 = 1.0_mA;
        auto r3 = v3 / i3;
        REQUIRE_THAT(static_cast<double>(r3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));

        auto r4 = 1.0_kOhm;
        REQUIRE_THAT(static_cast<double>(r4.value()), Catch::Matchers::WithinAbs(1000.0, epsilon));

        auto t0 = 42_ticks;
        REQUIRE(t0.value() == 42U);

        auto s0 = 1.0_sec;
        REQUIRE_THAT(static_cast<double>(s0.value()), Catch::Matchers::WithinAbs(1.0, epsilon));

        auto s1 = 1.0_msec;
        REQUIRE_THAT(static_cast<double>(s1.value()), Catch::Matchers::WithinAbs(0.001, epsilon));

        auto s2 = 1.0_usec;
        REQUIRE_THAT(static_cast<double>(s2.value()), Catch::Matchers::WithinAbs(0.000001, 0.0000001));

        auto m3 = 147_usec;
        REQUIRE(m3.value() == 147U);

        auto h0 = 1_Hz;
        REQUIRE(h0.value() == 1U);

        auto h1 = 1_KHz;
        REQUIRE(h1.value() == 1000U);

        auto h2 = 1_MHz;
        REQUIRE(h2.value() == 1000000U);

        auto c = 299'792'458.0_mps;
        REQUIRE_THAT(static_cast<double>(c.value()), Catch::Matchers::WithinAbs(299792458.0, epsilon));

        auto kph = 631.0_kph;
        REQUIRE(kph == 175.27777778_mps);
        REQUIRE_THAT(static_cast<double>(kph.value()), Catch::Matchers::WithinAbs(175.27777778, epsilon));

        auto c_kph = 1'079'252'848.8_kph;    // c in kph
        REQUIRE(c_kph == 1.0_c);
        REQUIRE_THAT(static_cast<double>(c_kph.value()), Catch::Matchers::WithinAbs(299792458.0, epsilon));
        auto d = c_kph * 0.5f;
        REQUIRE(d == 0.5_c);
    }
}

TEST_CASE("Units - Conversions") {
    using namespace core::units;
    SECTION("Time to Ticks") {
        core::units::Ticks t = core::units::ConvertToTicks(1.0_sec);
        REQUIRE(t == core::units::Ticks{core::units::ticks_per_second});
    }

    SECTION("Time to Ticks Half") {
        core::units::Ticks t = core::units::ConvertToTicks(0.5_sec);
        REQUIRE(t == core::units::Ticks{core::units::ticks_per_second / 2});
    }

    SECTION("Ticks to Time") {
        core::units::Seconds s0 = core::units::ConvertToSeconds(42_ticks);
        REQUIRE_THAT(static_cast<double>(s0.value()), Catch::Matchers::WithinAbs(0.328125, epsilon));
        REQUIRE_THAT(static_cast<double>(s0.value()), Catch::Matchers::WithinAbs(42.0 * static_cast<double>(core::units::tick_period), epsilon));
    }
}

TEST_CASE("Units - Ratios") {
    using namespace core::units;
    using core::units::operator""_g;
    auto one = 1.0_g;
    auto two = 2.0_g;
    Acceleration g = one;
    SECTION("Equality") {
        REQUIRE(one == one);
        REQUIRE_THAT(static_cast<double>(g.Numerator().Numerator().value()), Catch::Matchers::WithinAbs(9.80665, epsilon));
        REQUIRE_THAT(static_cast<double>(g.Numerator().Denominator().value()), Catch::Matchers::WithinAbs(1.0, epsilon));
        REQUIRE_THAT(static_cast<double>(g.Denominator().value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Operations") {
        auto three = one + two;
        REQUIRE(three == 3.0_g);
        REQUIRE(two == (three - one));
    }

    SECTION("Comparison") {
        REQUIRE(one < two);
        REQUIRE(two > one);
        REQUIRE(one <= one);
        REQUIRE(one <= two);
        REQUIRE(two >= two);
        REQUIRE(two >= one);
    }

    SECTION("Scalar Multiplication") {
        REQUIRE(2.0_g == (1.0_g * 2.0));
        REQUIRE((2.0 * 1.0_g) == 2.0_g);
    }

    SECTION("Scalar Division") {
        REQUIRE((1.0_g / 2.0) == 0.5_g);
    }
}
