#ifndef TICK_UNITTEST_HPP_
#define TICK_UNITTEST_HPP_

#include "jarnax.hpp"
#include "jarnax/UnitTest.hpp"    // the template

using jarnax::Executable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class TickTests : uint32_t {
    kCollect = 1U,
    kCompute,
    // bookkeeping
    kMinimum = kCollect,
    kStep = 1U,
    kMaximum = kCompute,
};

/// A unit test of some number of collected ticks to ensure they are monotonic
class TickTest final : public jarnax::UnitTest<TickTests, 100> {
public:
    // using State = typename jarnax::UnitTest<TickTests, 100>::State;
    TickTest();
    State Test(EnumType test_enum) override;

protected:
    constexpr static size_t kLength{20U};      ///< The length of the test arrays
    size_t m_tick_index_{0U};                  ///< The
    core::Array<Ticks, kLength> m_ticks_{};    ///< An array
};

#endif    // TICK_UNITTEST_HPP_
