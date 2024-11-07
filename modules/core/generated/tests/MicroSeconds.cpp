// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Units.hpp"

#include <iostream>

// AUTO GENERATED, DO NOT MODIFY!

TEST_CASE("Units - MicroSeconds") {
    using namespace core::units;
    MicroSeconds v1{1U};
    MicroSeconds v2{2U};

    SECTION("Unit Value") {
        REQUIRE(v1.value() == 1U);
        REQUIRE(v2.value() == 2U);
        REQUIRE(uint64_t(v1) == 1U);
        REQUIRE(uint64_t(v2) == 2U);
    }

    SECTION("Default Construct") {
        MicroSeconds v3;
        REQUIRE(v3.value() == 0U);
    }

    SECTION("Copy Construct") {
        auto v3{v1};
        REQUIRE(v3.value() == 1U);
    }

    SECTION("Const Construct") {
        MicroSeconds const v3{7U};
        REQUIRE(v3.value() == 7U);
    }

    SECTION("Copy Construct from Const") {
        MicroSeconds const v3{7U};
        auto v4{v3};
        REQUIRE(v4.value() == 7U);
    }

    // SECTION("Const Construct from Volatile") {
    //    MicroSeconds volatile v3{7U};
    //    MicroSeconds const v4{v3};
    //    REQUIRE(v4.value() == 7U);
    // }

    // SECTION("Const Construct from Const Volatile") {
    //     MicroSeconds const volatile v3{7U};
    //     MicroSeconds const v4{v3};
    //     REQUIRE(v4.value() == 7U);
    // }

    SECTION("Copy Assign") {
        MicroSeconds v3;
        v3 = v1;
        REQUIRE(v3.value() == 1U);
    }

    SECTION("Copy Assign to Volatile") {
        MicroSeconds volatile v3;
        v3 = v1;
        REQUIRE(v3.value() == 1U);
    }

    SECTION("Copy Assign From Volatile") {
        MicroSeconds volatile v3{7U};
        MicroSeconds v4;
        v4 = v3;
        REQUIRE(v4.value() == 7U);
    }

    SECTION("Addition") {
        auto v3 = v1 + v2;
        REQUIRE(v3.value() == 3U);
    }

    SECTION("Subtraction") {
        auto v3 = v2 - v1;
        REQUIRE(v3.value() == 1U);
    }

    SECTION("Multiplication") {
        auto v3 = v1 * 2U;
        REQUIRE(v3.value() == 2U);
        v3 = 2U * v1;
        REQUIRE(v3.value() == 2U);
    }

    SECTION("Division") {
        auto v3 = v2 / 2U;
        REQUIRE(v3.value() == 1U);
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
