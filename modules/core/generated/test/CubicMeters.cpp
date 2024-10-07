// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Units.hpp"

#include <iostream>

// AUTO GENERATED, DO NOT MODIFY!

TEST_CASE("Units - CubicMeters") {
    using namespace core::units;
    CubicMeters v1{1.0f};
    CubicMeters v2{2.0f};

    SECTION("Unit Value") {
        REQUIRE(v1.value() == 1.0f);
        REQUIRE(v2.value() == 2.0f);
        REQUIRE(float(v1) == 1.0f);
        REQUIRE(float(v2) == 2.0f);
    }

    SECTION("Default Construct") {
        CubicMeters v3;
        REQUIRE(v3.value() == 0.0f);
    }

    SECTION("Copy Construct") {
        auto v3{v1};
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Const Construct") {
        CubicMeters const v3{7.0f};
        REQUIRE(v3.value() == 7.0f);
    }

    SECTION("Const Construct from Volatile") {
        CubicMeters volatile v3{7.0f};
        CubicMeters const v4{v3};
        REQUIRE(v4.value() == 7.0f);
    }

    SECTION("Const Construct from Const Volatile") {
        CubicMeters const volatile v3{7.0f};
        CubicMeters const v4{v3};
        REQUIRE(v4.value() == 7.0f);
    }

    SECTION("Copy Assign") {
        auto v3 = v1;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Copy Assign to Volatile") {
        auto volatile v3 = v1;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Copy Assign From Volatile") {
        CubicMeters volatile v3{7.0f};
        auto v4 = v3;
        REQUIRE(v4.value() == 7.0f);
    }

    SECTION("Addition") {
        auto v3 = v1 + v2;
        REQUIRE(v3.value() == 3.0f);
    }

    SECTION("Subtraction") {
        auto v3 = v2 - v1;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Multiplication") {
        auto v3 = v1 * 2.0f;
        REQUIRE(v3.value() == 2.0f);
        v3 = 2.0f * v1;
        REQUIRE(v3.value() == 2.0f);
    }

    SECTION("Division") {
        auto v3 = v2 / 2.0f;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Equality") {
        REQUIRE(v1 == v1);
        REQUIRE(v1 != v2);
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

    SECTION("Literal") {
        using namespace core::units;
        auto v3 = 1.0_V;
        REQUIRE(v3.value() == 1.0f);
        v3 = 1000.0_mV;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("OStream") {
        using namespace core::units;
        std::cout << v1 << " and " << v2 << std::endl;
    }
}
