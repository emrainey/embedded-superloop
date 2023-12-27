#include <catch2/catch_test_macros.hpp>
#include "core/Pool.hpp"

class Dummy {
public:
    Dummy(int value)
        : value_{value} {}

    int const& value() const { return value_; }

protected:
    int value_;
};

TEST_CASE("Pool w/ Class") {
    core::Pool<Dummy, 3> pool;
    SECTION("Basics") {
        REQUIRE(pool.count() == 0U);
        REQUIRE(pool.available() == 3U);
    }
    SECTION("Construct and Dismiss") {
        REQUIRE(pool.available() == 3U);
        auto index = pool.emplace(7);
        REQUIRE(index == 0);
        REQUIRE(pool.count() == 1U);
        REQUIRE(pool.available() == 2U);
        REQUIRE(pool.is_present(index));
        REQUIRE(pool[index]->value() == 7);
        pool.dismiss(index);
        REQUIRE(pool.available() == 3U);
        REQUIRE(pool.count() == 0U);
        REQUIRE(pool.is_present(index) == false);
    }
}

TEST_CASE("Pool w/ Array") {
    core::Pool<core::Array<uint8_t, 10>, 3> pool;
    SECTION("Basics") {
        REQUIRE(pool.count() == 0U);
        REQUIRE(pool.available() == 3U);
    }
    SECTION("Construct and Dismiss") {
    }
}

TEST_CASE("Pool w/ Ints") {
    core::Pool<int, 3> pool;
    SECTION("Basics") {
        REQUIRE(pool.count() == 0U);
        REQUIRE(pool.available() == 3U);
    }
    SECTION("Construct and Dismiss") {
        REQUIRE(pool.is_present(0) == false);
        REQUIRE(pool.available() == 3U);
        auto index = pool.emplace(7);
        REQUIRE(index == 0);
        REQUIRE(pool.count() == 1U);
        REQUIRE(pool.available() == 2U);
        REQUIRE(pool.is_present(index));
    }
}