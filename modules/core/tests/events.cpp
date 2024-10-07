#include <catch2/catch_test_macros.hpp>
#include <core/Event.hpp>

using namespace core;

TEST_CASE("SingleEventsDefault") {
    events::Single<int> trigger;    // default constructor
    REQUIRE(not(trigger));
}

TEST_CASE("SingleEventsParameterized") {
    events::Single<int> trigger{4};
    REQUIRE((trigger));
}

TEST_CASE("SingleEventsSetAndGet") {
    events::Single<int> trigger;
    REQUIRE(not(trigger));
    trigger = 6;
    REQUIRE((trigger));
    auto tmp = int(trigger);
    REQUIRE(not(trigger));
    REQUIRE(6 == tmp);
    trigger = 7;
    REQUIRE((trigger));
    auto const tmp2 = int(trigger);
    REQUIRE(tmp2 == 7);
    REQUIRE(not(trigger));
}

TEST_CASE("Flags") {    // As an enumeration
    events::Single<events::Flag> trigger{events::Flag::Lowered};
    REQUIRE(trigger);
    events::Flag tmp = events::Flag(trigger);
    REQUIRE(not trigger);
    REQUIRE(events::Flag::Lowered == tmp);
    // set
    trigger = events::Flag::Raised;
    REQUIRE(trigger);
    // get
    tmp = events::Flag(trigger);
    REQUIRE(events::Flag::Raised == tmp);
    REQUIRE(not trigger);
}

TEST_CASE("Multiples") {
    events::Single<events::Flag> a{events::Flag::Lowered};
    events::Single<events::Flag> b{events::Flag::Lowered};
    events::Single<events::Flag> c{events::Flag::Lowered};
    events::Multiplier<events::Flag, 3> m = {&a, &b, &c};
    events::Flag tmp = events::Flag(m);
    SECTION("Assumptions") {
        REQUIRE(not m);
        REQUIRE(not a);
        REQUIRE(not b);
        REQUIRE(not c);
        REQUIRE(events::Flag::Lowered == tmp);
    }
    SECTION("Set and Individually Get") {
        m = events::Flag::Raised;
        REQUIRE(m);
        REQUIRE(a);
        REQUIRE(b);
        REQUIRE(c);
        tmp = events::Flag(a);
        REQUIRE(events::Flag::Raised == tmp);
        REQUIRE(not a);
        tmp = events::Flag(b);
        REQUIRE(events::Flag::Raised == tmp);
        REQUIRE(not b);
        tmp = events::Flag(c);
        REQUIRE(events::Flag::Raised == tmp);
        REQUIRE(not c);
    }
}