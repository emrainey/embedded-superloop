#include <catch2/catch_test_macros.hpp>
#include "core/Container.hpp"

class Foo {
public:
    Foo(uint64_t v)
        : foo{v} {}

    uint64_t get() const { return foo; }

protected:
    uint64_t foo;
};

class Bar {
public:
    Bar(Foo& f)
        : foo{f} {}

    uint64_t get() const { return foo.get(); }

protected:
    Foo& foo;
};

TEST_CASE("Containers") {
    SECTION("Atomic") {
        core::Container<int> test;
        REQUIRE(test.storage_size() == sizeof(int));
        REQUIRE(test.storage_alignment() == alignof(int));
        REQUIRE(!test);
        test.emplace(42);
        REQUIRE(test);
        REQUIRE(*test == 42);
        test.dismiss();
        REQUIRE(!test);
    }
    SECTION("Foo - Simple") {
        core::Container<Foo> test;
        REQUIRE(test.storage_size() == sizeof(Foo));
        REQUIRE(test.storage_alignment() == alignof(Foo));
        REQUIRE(!test);
        test.emplace(42UL);
        REQUIRE(test);
        REQUIRE(test->get() == 42UL);
        REQUIRE((*test).get() == 42UL);
        test.dismiss();
        REQUIRE(!test);
    }
    SECTION("Bar - Complex") {
        Foo foo{42UL};
        core::Container<Bar> bar;
        REQUIRE(bar.storage_size() == sizeof(Bar));
        REQUIRE(bar.storage_alignment() == alignof(Bar));
        REQUIRE(!bar);
        bar.emplace(foo);
        REQUIRE(bar);
        REQUIRE(bar->get() == 42UL);
        REQUIRE((*bar).get() == 42UL);
        bar.dismiss();
        REQUIRE(!bar);
    }
}
