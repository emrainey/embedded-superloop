// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Units.hpp"

#include <iostream>

// AUTO GENERATED, DO NOT MODIFY!

TEST_CASE("Units - Seconds") {
    using namespace core::units;
    Seconds v1{1.0f};
    Seconds v2{2.0f};

    SECTION("Unit Value") {
        REQUIRE(v1.value() == 1.0f);
        REQUIRE(v2.value() == 2.0f);
        REQUIRE(float(v1) == 1.0f);
        REQUIRE(float(v2) == 2.0f);
    }

    SECTION("Default Construct") {
        Seconds v3;
        REQUIRE(v3.value() == 0.0f);
    }

    SECTION("Copy Construct") {
        auto v3{v1};
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Const Construct") {
        Seconds const v3{7.0f};
        REQUIRE(v3.value() == 7.0f);
    }

    // SECTION("Const Construct from Volatile") {
    //     Seconds volatile v3{7.0f};
    //     Seconds const v4{v3};
    //     REQUIRE(v4.value() == 7.0f);
    // }

    // SECTION("Const Construct from Const Volatile") {
    //     Seconds const volatile v3{7.0f};
    //     Seconds const v4{v3};
    //     REQUIRE(v4.value() == 7.0f);
    // }

    SECTION("Copy Assign") {
        Seconds v3;
        v3 = v1;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Copy Assign to Volatile") {
        Seconds volatile v3;
        v3 = v1;
        REQUIRE(v3.value() == 1.0f);
    }

    SECTION("Copy Assign From Volatile") {
        Seconds volatile v3{7.0f};
        Seconds v4;
        v4 = v3;
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

    SECTION("OStream") {
        using namespace core::units;
        std::cout << v1 << " and " << v2 << std::endl;
    }
}
