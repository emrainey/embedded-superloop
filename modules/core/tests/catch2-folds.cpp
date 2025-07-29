#include <catch2/catch_test_macros.hpp>
#include "core/Folds.hpp"

TEST_CASE("Folds - Simple") {
    SECTION("Sum") {
        int E = core::sum(1, 1, 2, 3, 5, 8, 13, 21);
        REQUIRE(E == 54);
    }
    SECTION("Product") {
        int P = core::product(4, 5, 6);
        REQUIRE(P == 120);
    }
    SECTION("All - True") {
        bool A = core::all(true, true, true, true);
        REQUIRE(A == true);
    }
    SECTION("All - One False") {
        bool A = core::all(true, true, false, true);
        REQUIRE(A == false);
    }
    SECTION("Any - True") {
        bool A = core::any(false, false, false, true);
        REQUIRE(A == true);
    }
    SECTION("Any - False") {
        bool A = core::any(false, false, false, false);
        REQUIRE(A == false);
    }
    SECTION("Is Decreasing - True") {
        bool D = core::is_strictly_decreasing(5, 4, 3, 2, 1);
        REQUIRE(D == true);
    }
    SECTION("Is Decreasing - False") {
        bool D = core::is_strictly_decreasing(1, 2, 3, 4, 5);
        REQUIRE(D == false);
        bool D2 = core::is_strictly_decreasing(5, 4, 4, 4, 4);
        REQUIRE(D2 == false);
    }
    SECTION("Is Increasing - True") {
        bool I = core::is_strictly_increasing(1, 2, 3, 4, 5);
        REQUIRE(I == true);
    }
    SECTION("Is Increasing - False") {
        bool I = core::is_strictly_increasing(5, 4, 3, 2, 1);
        REQUIRE(I == false);
        bool I2 = core::is_strictly_increasing(1, 2, 2, 2, 2);
        REQUIRE(I2 == false);
    }
    SECTION("Maximum") {
        auto M = core::max(1, 2, 3, 4, 5);
        REQUIRE(M == 5);
        auto M2 = core::max(5, 4, 3, 2, 1);
        REQUIRE(M2 == 5);
        auto M3 = core::max(1, 2, 3, 4, 5, 4, 3, 2, 1);
        REQUIRE(M3 == 5);
    }
    SECTION("Minimum") {
        auto M = core::min(1, 2, 3, 4, 5);
        REQUIRE(M == 1);
        auto M2 = core::min(5, 4, 3, 2, 1);
        REQUIRE(M2 == 1);
        auto M3 = core::min(5, 4, 3, 2, 1, 2, 3, 4, 5);
        REQUIRE(M3 == 1);
    }
}