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

TEST_CASE("Container - Basic") {
    core::Container<Dummy> container;
    SECTION("Basics") {
        REQUIRE(container.storage_size() == sizeof(Dummy));
        REQUIRE(container.storage_alignment() == alignof(Dummy));
        REQUIRE_FALSE(container);
        // REQUIRE(&(*container) != nullptr);
    }
    SECTION("Emplace") {
        container.emplace(7);
        REQUIRE(container);
        REQUIRE(container->value() == 7);
    }
}

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
        REQUIRE(pool.capacity() == 3U);
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
    SECTION("Construct All and Past") {
        REQUIRE(pool.available() == 3U);
        auto index = pool.emplace(7);
        REQUIRE(index == 0);
        index = pool.emplace(8);
        REQUIRE(index == 1);
        index = pool.emplace(9);
        REQUIRE(index == 2);
        index = pool.emplace(10);
        REQUIRE(index == std::numeric_limits<std::size_t>::max());
        REQUIRE(*pool[0] == 7);
        REQUIRE(*pool[1] == 8);
        REQUIRE(*pool[2] == 9);
        REQUIRE(pool.available() == 0U);
        REQUIRE(pool.count() == 3U);
    }
}