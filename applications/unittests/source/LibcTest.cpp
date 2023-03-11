#include "LibcTest.hpp"

using jarnax::Executable;

LibcTest::TestName tests[] = {
    DEFINE_TEST_NAME(LibcTests::kCompare),
    DEFINE_TEST_NAME(LibcTests::kFill),
    DEFINE_TEST_NAME(LibcTests::kCopyCompare),
    DEFINE_TEST_NAME(LibcTests::kFillCopyCompare),
};

LibcTest::LibcTest()
    : UnitTest{"LibcTest", tests}
    , src{}
    , tmp{}
    , dst{} {
}

LibcTest::State LibcTest::Test(EnumType test_enum) {
    if (test_enum == LibcTests::kCompare) {
        // compares
        uint8_t volatile a = 1U;
        uint8_t volatile b = 2U;
        uint8_t volatile c = 1U;
        Assert(-1 == memory::compare(&a, &b, 1U), "Must be this return");
        Assert(0 == memory::compare(&a, &c, 1U), "Must be this return");
        Assert(+1 == memory::compare(&b, &a, 1U), "Must be this return");
    } else if (test_enum == LibcTests::kFill) {
        memory::fill(src, fill_value);
        memory::fill(tmp, anti_fill_value, kLength);
        Assert(0 != memory::compare(src, tmp, kLength), "Must be not equal");
    } else if (test_enum == LibcTests::kCopyCompare) {
        memory::copy(dst, tmp);
        Assert(0 == memory::compare(tmp, dst, kLength), "Must be the same");
        Assert(0 != memory::compare(src, dst, kLength), "Must not be the same");
    } else if (test_enum == LibcTests::kFillCopyCompare) {
        memory::copy(dst, src, kLength);    // allows over runs?
        Assert(0 == memory::compare(src, dst, kLength), "Must be the same");
    } else {
        return State::Skipped;
    }
    return State::Completed;
}