#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "core/Variant.hpp"

constexpr double epsilon{0.0001};    // For floating point comparisons

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

TEST_CASE("PartNumber - Basics") {
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

TEST_CASE("Variant - Type-Safe Construction") {
    SECTION("Construct with Foo") {
        Foo f{42U};
        core::Variant<Foo, Bar, Baz> test(f);
        REQUIRE(test.isa<Foo>() == true);
        REQUIRE(test.index() == 0);
    }
    SECTION("Construct with Bar") {
        Bar b{123456ULL};
        core::Variant<Foo, Bar, Baz> test(b);
        REQUIRE(test.isa<Bar>() == true);
        REQUIRE(test.index() == 1);
    }
    SECTION("Construct with Baz") {
        Baz bz{3.14f};
        core::Variant<Foo, Bar, Baz> test(bz);
        REQUIRE(test.isa<Baz>() == true);
        REQUIRE(test.index() == 2);
    }
    SECTION("Construct with inline value") {
        core::Variant<Foo, Bar, Baz> test(Foo{999U});
        REQUIRE(test.isa<Foo>() == true);
        REQUIRE(test.get<Foo>().foo == 999U);
    }
}

TEST_CASE("Variant - Get Method") {
    SECTION("Get Foo value") {
        Foo f{42U};
        core::Variant<Foo, Bar, Baz> test(f);
        REQUIRE(test.isa<Foo>() == true);
        REQUIRE(test.get<Foo>().foo == 42U);
    }
    SECTION("Get Bar value") {
        Bar b{123456ULL};
        core::Variant<Foo, Bar, Baz> test(b);
        REQUIRE(test.isa<Bar>() == true);
        REQUIRE(test.get<Bar>().bar == 123456ULL);
    }
    SECTION("Get Baz value") {
        Baz bz{3.14f};
        core::Variant<Foo, Bar, Baz> test(bz);
        REQUIRE(test.isa<Baz>() == true);
        REQUIRE_THAT(static_cast<double>(test.get<Baz>().baz), Catch::Matchers::WithinAbs(3.14, epsilon));
    }
    SECTION("Const get") {
        Foo f{42U};
        core::Variant<Foo, Bar, Baz> const test(f);
        REQUIRE(test.get<Foo>().foo == 42U);
    }
    SECTION("Modify through get") {
        Foo f{42U};
        core::Variant<Foo, Bar, Baz> test(f);
        test.get<Foo>().foo = 100U;
        REQUIRE(test.get<Foo>().foo == 100U);
    }
}

TEST_CASE("Variant - Proper Destruction") {
    struct DestructorCounter {
        int* counter;
        explicit DestructorCounter(int* c)
            : counter(c) {}
        DestructorCounter(DestructorCounter const& other)
            : counter(other.counter) {}
        ~DestructorCounter() {
            if (counter) (*counter)++;
        }
    };

    SECTION("Destructor called on scope exit") {
        int count = 0;
        {
            DestructorCounter dc(&count);
            {
                core::Variant<DestructorCounter, int, float> test(dc);
                REQUIRE(count == 0);    // dc is still alive, variant copy made
            }
            REQUIRE(count == 1);        // Variant destroyed
        }
        REQUIRE(count == 2);            // dc destroyed
    }
}

TEST_CASE("Variant - Different Type Combinations") {
    SECTION("Integer types") {
        core::Variant<int, uint32_t, int64_t> test(int{-42});
        REQUIRE(test.isa<int>() == true);
        REQUIRE(test.get<int>() == -42);
    }
    SECTION("Float types") {
        core::Variant<float, double> test(3.14159);
        REQUIRE(test.isa<double>() == true);
        REQUIRE_THAT(test.get<double>(), Catch::Matchers::WithinAbs(3.14159, epsilon));
    }
    SECTION("Mixed primitive and struct") {
        core::Variant<int, Foo, double> test(Foo{777U});
        REQUIRE(test.isa<Foo>() == true);
        REQUIRE(test.get<Foo>().foo == 777U);
    }
}

TEST_CASE("Variant - Index Method") {
    SECTION("First type has index 0") {
        core::Variant<Foo, Bar, Baz> test(Foo{});
        REQUIRE(test.index() == 0);
    }
    SECTION("Second type has index 1") {
        core::Variant<Foo, Bar, Baz> test(Bar{});
        REQUIRE(test.index() == 1);
    }
    SECTION("Third type has index 2") {
        core::Variant<Foo, Bar, Baz> test(Baz{});
        REQUIRE(test.index() == 2);
    }
}

TEST_CASE("Variant - Move Construction") {
    struct MoveOnly {
        int value;
        MoveOnly(int v)
            : value(v) {}
        MoveOnly(MoveOnly const&) = delete;
        MoveOnly(MoveOnly&& other)
            : value(other.value) {
            other.value = 0;
        }
        MoveOnly& operator=(MoveOnly const&) = delete;
        MoveOnly& operator=(MoveOnly&&) = delete;
    };

    SECTION("Move into variant") {
        MoveOnly mo(42);
        core::Variant<MoveOnly, int> test(static_cast<MoveOnly&&>(mo));
        REQUIRE(test.isa<MoveOnly>() == true);
        REQUIRE(test.get<MoveOnly>().value == 42);
        REQUIRE(mo.value == 0);    // Moved from
    }
}
