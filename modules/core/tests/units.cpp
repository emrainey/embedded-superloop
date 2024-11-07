// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Units.hpp"

#include <iostream>

TEST_CASE("Units - Equations") {
    core::units::Volts v{1.0f};
    core::units::Amperes i{2.0f};
    core::units::Ohms r{4.0f};

    SECTION("Ohm's Law") {
        auto v2 = i * r;
        REQUIRE(v2.value() == 8.0f);
        v2 = r * i;
        REQUIRE(v2.value() == 8.0f);

        auto i2 = v / r;
        REQUIRE(i2.value() == 0.25f);

        auto r2 = v / i;
        REQUIRE(r2.value() == 0.5f);
    }
    SECTION("Power") {
        auto p = v * i;
        REQUIRE(p.value() == 2.0f);
        p = i * v;
        REQUIRE(p.value() == 2.0f);
    }
    SECTION("Literals") {
        using namespace core::units;
        auto v2 = 1.0_V;
        auto i2 = 1.0_A;
        auto r2 = 1.0_Ohm;
        auto p = v2 / i2;
        REQUIRE(p.value() == r2.value());

        auto v3 = 1.0_mV;
        auto i3 = 1.0_mA;
        auto r3 = v3 / i3;
        REQUIRE(r3.value() == 1.0f);

        auto r4 = 1.0_kOhm;
        REQUIRE(r4.value() == 1000.0f);

        auto t0 = 42_ticks;
        REQUIRE(t0.value() == 42U);

        auto s0 = 1.0_sec;
        REQUIRE(s0.value() == 1.0f);

        auto s1 = 1.0_msec;
        REQUIRE(s1.value() == 0.001f);

        auto s2 = 1.0_usec;
        REQUIRE(s2.value() == 0.000001f);

        auto m3 = 147_usec;
        REQUIRE(m3.value() == 147U);

        auto h0 = 1_Hz;
        REQUIRE(h0.value() == 1U);

        auto h1 = 1_kHz;
        REQUIRE(h1.value() == 1000U);

        auto h2 = 1_MHz;
        REQUIRE(h2.value() == 1000000U);
    }
}

TEST_CASE("Units - Conversions") {
    using namespace core::units;
    SECTION("Time to Ticks") {
        core::units::Ticks t = core::units::ConvertToTicks(1.0_sec);
        REQUIRE(t == core::units::ticks_per_second);
    }

    SECTION("Time to Ticks Half") {
        core::units::Ticks t = core::units::ConvertToTicks(0.5_sec);
        REQUIRE(t == core::units::ticks_per_second / 2);
    }

    SECTION("Ticks to Time") {
        core::units::Seconds s0 = core::units::ConvertToSeconds(42_ticks);
        REQUIRE(s0.value() == 0.328125F);
    }
}