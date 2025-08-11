// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "core/Units.hpp"

#include <iostream>

// AUTO GENERATED, DO NOT MODIFY!
constexpr static double epsilon{0.0625};    // 1/16th of a unit, used for floating point comparisons

TEST_CASE("Units - Degrees") {
    using namespace core::units;
    Degrees v1{1.0f};
    Degrees v2{2.0f};

    SECTION("Unit Value") {
        REQUIRE_THAT(static_cast<double>(v1.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
        REQUIRE_THAT(static_cast<double>(v2.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
        REQUIRE_THAT(static_cast<double>(float(v1)), Catch::Matchers::WithinAbs(1.0, epsilon));
        REQUIRE_THAT(static_cast<double>(float(v2)), Catch::Matchers::WithinAbs(2.0, epsilon));
    }

    SECTION("Default Construct") {
        Degrees v3;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(0.0, epsilon));
    }

    SECTION("Copy Construct") {
        auto v3{v1};
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Const Construct") {
        Degrees const v3{7.0f};
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(7.0, epsilon));
    }

    SECTION("Copy Assign") {
        Degrees v3;
        v3 = v1;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Copy Assign to Volatile") {
        Degrees volatile v3;
        v3 = v1;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Copy Assign From Volatile") {
        Degrees volatile v3{7.0f};
        Degrees v4;
        v4 = v3;
        REQUIRE_THAT(static_cast<double>(v4.value()), Catch::Matchers::WithinAbs(7.0, epsilon));
    }

    SECTION("Addition") {
        auto v3 = v1 + v2;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(3.0, epsilon));
    }

    SECTION("Subtraction") {
        auto v3 = v2 - v1;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Multiplication") {
        auto v3 = v1 * 2.0;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
        v3 = 2.0f * v1;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(2.0, epsilon));
    }

    SECTION("Division") {
        auto v3 = v2 / 2.0f;
        REQUIRE_THAT(static_cast<double>(v3.value()), Catch::Matchers::WithinAbs(1.0, epsilon));
    }

    SECTION("Equality") {
        REQUIRE_THAT(static_cast<double>(v1.value()), Catch::Matchers::WithinAbs(static_cast<double>(v1.value()), epsilon));
        REQUIRE_THAT(static_cast<double>(v1.value()), not Catch::Matchers::WithinAbs(static_cast<double>(v2.value()), epsilon));
    }

    SECTION("Less Than") {
        REQUIRE(v1 < v2);
        REQUIRE_FALSE(v2 < v1);
    }

    SECTION("Less Than or Equal") {
        REQUIRE(v1 <= v1);
        REQUIRE(v1 <= v2);
        REQUIRE_FALSE(v2 <= v1);
    }

    SECTION("Greater Than") {
        REQUIRE(v2 > v1);
        REQUIRE_FALSE(v1 > v2);
    }

    SECTION("Greater Than or Equal") {
        REQUIRE(v1 >= v1);
        REQUIRE(v2 >= v1);
        REQUIRE_FALSE(v1 >= v2);
    }

    SECTION("OStream") {
        using namespace core::units;
        std::cout << v1 << " and " << v2 << std::endl;
    }
}
