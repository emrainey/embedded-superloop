#include <catch2/catch_test_macros.hpp>
#include "core/Variant.hpp"

struct Foo {
    uint32_t foo;
};

struct Bar {
    uint64_t bar;
};

struct Baz {
    float baz;
};

struct Gog {
    double gog;
};

TEST_CASE("Sameness") {
    SECTION("Template Structures") {
        REQUIRE(core::same_type<int, int>::value == true);
        REQUIRE(core::same_type<int, float>::value == false);
    }
    // SECTION("Template Variables") {
    //     REQUIRE(core::are_same_type<int, int>() == true);
    //     REQUIRE(core::are_same_type<int, float>() == false);
    // }
}

TEST_CASE("Variants - Basics") {
    SECTION("Default Constructor") {
        core::Variant<Foo, Bar, Baz> test{Foo{}};
        REQUIRE(test.count() == 3U);
        REQUIRE(test.storage_size() == sizeof(Bar));
        REQUIRE(test.storage_alignment() == alignof(Bar));
    }
    SECTION("Could Be") {
        core::Variant<Foo, Bar, Baz> test(Foo{});
        REQUIRE(test.could<Foo>() == true);
        REQUIRE(test.could<Bar>() == true);
        REQUIRE(test.could<Baz>() == true);
        REQUIRE(test.could<Gog>() == false);
    }
    SECTION("Is a Foo") {
        core::Variant<Foo, Bar, Baz> test(Foo{});
        REQUIRE(test.isa<Foo>() == true);
        REQUIRE(test.isa<Bar>() == false);
        REQUIRE(test.isa<Baz>() == false);
        // REQUIRE(test.isa<Gog>() == false); // Gog is not in the variant, thus it can not compile!
    }
    SECTION("Is a Bar") {
        core::Variant<Foo, Bar, Baz> test(Bar{});
        REQUIRE(test.isa<Foo>() == false);
        REQUIRE(test.isa<Bar>() == true);
        REQUIRE(test.isa<Baz>() == false);
        // REQUIRE(test.isa<Gog>() == false); // Gog is not in the variant, thus it can not compile!
    }
    SECTION("Is a Baz") {
        core::Variant<Foo, Bar, Baz> test(Baz{});
        REQUIRE(test.isa<Foo>() == false);
        REQUIRE(test.isa<Bar>() == false);
        REQUIRE(test.isa<Baz>() == true);
        // REQUIRE(test.isa<Gog>() == false); // Gog is not in the variant, thus it can not compile!
    }
}
