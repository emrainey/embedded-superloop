#include <catch2/catch_test_macros.hpp>
#include "core/EnumType.hpp"

enum class Test : std::uint32_t {
    None = 0U,
    Foo = 1U,
    Bar = 2U,
    Baz = 3U,
};

TEST_CASE("Enums - Accessing Elements") {
    SECTION("Default Constructor") {
        core::EnumType<Test> test;
        REQUIRE(test.get() == Test::None);
        REQUIRE(test.value() == 0U);
    }
    SECTION("Parameter Constructor") {
        core::EnumType<Test> test(Test::Foo);
        REQUIRE(test.get() == Test::Foo);
        REQUIRE(test.value() == 1U);
    }
    SECTION("Equality of EnumType") {
        core::EnumType<Test> test1(Test::Foo);
        core::EnumType<Test> test2(Test::Foo);
        core::EnumType<Test> test3(Test::Bar);
        REQUIRE(test1 == test2);
        REQUIRE(test1 != test3);
    }
    SECTION("Equality of EnumType to Enum") {
        core::EnumType<Test> test(Test::Foo);
        REQUIRE(test == Test::Foo);
        REQUIRE(test != Test::Bar);
    }
}
