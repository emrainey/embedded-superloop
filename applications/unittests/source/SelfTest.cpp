#include "SelfTest.hpp"

struct Dummy {
    uint32_t counter{0U};
    bool value{false};
};

bool operator==(Dummy const& a, Dummy const& b) {
    return (a.counter == b.counter);
}

bool operator!=(Dummy const& a, Dummy const& b) {
    return not operator==(a, b);
}

static SelfTest::TestName tests[] = {
    DEFINE_TEST_NAME(SelfTests::kAutoFailed),
    DEFINE_TEST_NAME(SelfTests::kAutoPassed),
    DEFINE_TEST_NAME(SelfTests::kCompareValueEqualPass),
    DEFINE_TEST_NAME(SelfTests::kCompareValueEqualFail),
    DEFINE_TEST_NAME(SelfTests::kCompareFloatEqualPass),
    DEFINE_TEST_NAME(SelfTests::kCompareFloatEqualFail),
    DEFINE_TEST_NAME(SelfTests::kCompareRefValueEqualPass),
    DEFINE_TEST_NAME(SelfTests::kCompareRefValueEqualFail),
    DEFINE_TEST_NAME(SelfTests::kCompareStructEqualPass),
    DEFINE_TEST_NAME(SelfTests::kCompareStructEqualFail),
};

SelfTest::SelfTest()
    : UnitTest{"SelfTest", tests} {
}

SelfTest::State SelfTest::Test(EnumType test_enum) {
    if (test_enum == SelfTests::kAutoFailed) {
        Assert(false, "Should be false");
    } else if (test_enum == SelfTests::kAutoPassed) {
        Assert(true, "Should be true");
    } else if (test_enum == SelfTests::kCompareValueEqualPass) {
        CompareEqual(10U, 10U);
    } else if (test_enum == SelfTests::kCompareValueEqualFail) {
        CompareNotEqual(1028U, 11U);
    } else if (test_enum == SelfTests::kCompareFloatEqualPass) {
        if (jarnax::enable_access_to_fpu) {
            float volatile a = 5.75F;
            float volatile b = 6.75F - 1.0F;
            CompareFloatEqual(a, b);
        }
    } else if (test_enum == SelfTests::kCompareFloatEqualFail) {
        if (jarnax::enable_access_to_fpu) {
            float volatile a = 5.75F + (2.0F * std::numeric_limits<float>::epsilon());
            float volatile b = 6.75F - 1.0F;
            CompareFloatNotEqual(a, b);
        }
    } else if (test_enum == SelfTests::kCompareRefValueEqualPass) {
        volatile int a = 99;
        volatile int b = 99;
        CompareRefEqual(a, b);
    } else if (test_enum == SelfTests::kCompareRefValueEqualFail) {
        volatile int c = 99;
        volatile int d = 11;
        CompareRefNotEqual(c, d);
    } else if (test_enum == SelfTests::kCompareStructEqualPass) {
        Dummy a = {20, true};
        Dummy b = {20, false};
        CompareRefEqual(a, b);
    } else if (test_enum == SelfTests::kCompareStructEqualFail) {
        Dummy a = {20, true};
        Dummy b = {21, true};
        CompareRefNotEqual(a, b);
    } else {
        return State::Skipped;
    }
    return State::Completed;
}