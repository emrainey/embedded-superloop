#include <gtest/gtest.h>
#include <core/Event.hpp>

using namespace core;

TEST(Events, SingleEventsDefault) {
    events::Single<int> trigger;    // default constructor
    ASSERT_FALSE((trigger));
}

TEST(Events, SingleEventsParameterized) {
    events::Single<int> trigger{4};
    ASSERT_TRUE((trigger));
}

TEST(Events, SingleEventsSetAndGet) {
    events::Single<int> trigger;
    ASSERT_FALSE((trigger));
    trigger = 6;
    ASSERT_TRUE((trigger));
    auto tmp = int(trigger);
    ASSERT_FALSE((trigger));
    ASSERT_EQ(6, tmp);
}

TEST(Events, Flags) {    // As an enumeration
    events::Single<events::Flag> trigger{events::Flag::Lowered};
    ASSERT_TRUE(trigger);
    events::Flag tmp = events::Flag(trigger);
    ASSERT_FALSE(trigger);
    ASSERT_EQ(events::Flag::Lowered, tmp);
    // set
    trigger = events::Flag::Raised;
    ASSERT_TRUE(trigger);
    // get
    tmp = events::Flag(trigger);
    ASSERT_EQ(events::Flag::Raised, tmp);
    ASSERT_FALSE(trigger);
}

TEST(Events, Multiples) {
    // mulitples
    events::Single<events::Flag> a{events::Flag::Lowered};
    events::Single<events::Flag> b{events::Flag::Lowered};
    events::Single<events::Flag> c{events::Flag::Lowered};
    events::Multiplier<events::Flag, 3> m = {&a, &b, &c};
    events::Flag tmp = events::Flag(m);
    ASSERT_FALSE(m);
    ASSERT_FALSE(a);
    ASSERT_FALSE(b);
    ASSERT_FALSE(c);
    ASSERT_EQ(events::Flag::Lowered, tmp);
    m = events::Flag::Raised;
    ASSERT_TRUE(m);
    ASSERT_TRUE(a);
    ASSERT_TRUE(b);
    ASSERT_TRUE(c);
    tmp = events::Flag(a);
    ASSERT_EQ(events::Flag::Raised, tmp);
    ASSERT_FALSE(a);
    tmp = events::Flag(b);
    ASSERT_EQ(events::Flag::Raised, tmp);
    ASSERT_FALSE(b);
    tmp = events::Flag(c);
    ASSERT_EQ(events::Flag::Raised, tmp);
    ASSERT_FALSE(c);
}