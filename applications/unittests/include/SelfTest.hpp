#ifndef SELF_UNITTEST_HPP_
#define SELF_UNITTEST_HPP_

#include "jarnax.hpp"
#include "jarnax/UnitTest.hpp"

using jarnax::Executable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class SelfTests : std::size_t {
    kAutoFailed = 1U,
    kAutoPassed,
    kCompareValueEqualPass,
    kCompareValueEqualFail,
    kCompareFloatEqualPass,
    kCompareFloatEqualFail,
    kCompareRefValueEqualPass,
    kCompareRefValueEqualFail,
    kCompareStructEqualPass,
    kCompareStructEqualFail,

    // bookkeeping
    kMinimum = kAutoFailed,
    kStep = 1U,
    kMaximum = kCompareStructEqualFail
};

/// A unit test of the unit test.
class SelfTest final : public jarnax::UnitTest<SelfTests, 11> {
public:
    // using State = typename jarnax::UnitTest<SelfTests, 11>::State;
    SelfTest();
    State Test(EnumType test_enum) override;
};

#endif    // SELF_UNITTEST_HPP_
