#include "StackTest.hpp"

static StackTest::TestName tests[] = {
    DEFINE_TEST_NAME(StackTests::kFirst),
    DEFINE_TEST_NAME(StackTests::kSingleWrite),
    DEFINE_TEST_NAME(StackTests::kSecondWrite),
    DEFINE_TEST_NAME(StackTests::kThirdWrite),
    DEFINE_TEST_NAME(StackTests::kFourthWrite),
    DEFINE_TEST_NAME(StackTests::kFirstRead),
    DEFINE_TEST_NAME(StackTests::kSecondRead),
    DEFINE_TEST_NAME(StackTests::kThirdRead),
    DEFINE_TEST_NAME(StackTests::kFourthRead),
    DEFINE_TEST_NAME(StackTests::kLast),
};

StackTest::StackTest()
    : UnitTest("StackTest", tests) {
}

StackTest::State StackTest::Test(EnumType test_enum) {
    if (test_enum == StackTests::kFirst) {
        // basics
        CompareEqual(stack_.count(), 0_Z);
        CompareEqual(stack_.capacity(), kLimit);
    } else if (test_enum == StackTests::kSingleWrite) {
        // add some values, check indexes and counts
        Assert(stack_.Push(99_Z));
        CompareEqual(stack_.count(), 1_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 99_Z);
    } else if (test_enum == StackTests::kSecondWrite) {
        Assert(stack_.Push(66_Z));
        CompareEqual(stack_.count(), 2_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 66_Z);
        CompareEqual(stack_[1U], 99_Z);
    } else if (test_enum == StackTests::kThirdWrite) {
        Assert(stack_.Push(33_Z));
        CompareEqual(stack_.count(), 3_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 33_Z);
        CompareEqual(stack_[1U], 66_Z);
        CompareEqual(stack_[2U], 99_Z);
    } else if (test_enum == StackTests::kFourthWrite) {
        Assert(stack_.Push(11_Z));
        CompareEqual(stack_.count(), kLimit);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 11_Z);
        CompareEqual(stack_[1U], 33_Z);
        CompareEqual(stack_[2U], 66_Z);
        CompareEqual(stack_[3U], 99_Z);
    } else if (test_enum == StackTests::kFirstRead) {
        // add some values, check indexes and counts
        Assert(stack_.Pop(value_) and value_ == 11U);
        CompareEqual(stack_.count(), 3_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 33_Z);
        CompareEqual(stack_[1U], 66_Z);
        CompareEqual(stack_[2U], 99_Z);
    } else if (test_enum == StackTests::kSecondRead) {
        Assert(stack_.Pop(value_) and value_ == 33U);
        CompareEqual(stack_.count(), 2_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 66_Z);
        CompareEqual(stack_[1U], 99_Z);
    } else if (test_enum == StackTests::kThirdRead) {
        Assert(stack_.Pop(value_) and value_ == 66_Z);
        CompareEqual(stack_.count(), 1_Z);
        CompareEqual(stack_.capacity(), kLimit);
        CompareEqual(stack_[0U], 99_Z);
    } else if (test_enum == StackTests::kFourthRead) {
        Assert(stack_.Pop(value_) and value_ == 99U);
        CompareEqual(stack_.count(), 0_Z);
        CompareEqual(stack_.capacity(), kLimit);
    } else if (test_enum == StackTests::kLast) {
        Assert(stack_.Pop(value_) and value_ == 99U);
        CompareEqual(stack_.count(), 0_Z);
        CompareEqual(stack_.capacity(), kLimit);
    } else {
        return State::Skipped;
    }
    return State::Completed;
}
