#ifndef STACK_UNITTEST_HPP_
#define STACK_UNITTEST_HPP_

#include "jarnax.hpp"
#include "jarnax/UnitTest.hpp"    // the template
#include "core/Stack.hpp"

using jarnax::Executable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class StackTests : std::uint32_t {
    kFirst = 1U,
    kSingleWrite,
    kSecondWrite,
    kThirdWrite,
    kFourthWrite,
    kFirstRead,
    kSecondRead,
    kThirdRead,
    kFourthRead,
    kLast,
    // bookkeeping enums
    kMinimum = kFirst,
    kStep = 1U,
    kMaximum = kLast,
};

/// A unit test of the Stack test.
class StackTest final : public jarnax::UnitTest<StackTests, 50> {
public:
    using Parent = typename jarnax::UnitTest<StackTests, 50>;
    using State = typename jarnax::UnitTest<StackTests, 50>::State;
    StackTest();
    State Test(EnumType test_enum) override;

protected:
    constexpr static size_t kLimit = 4U;
    core::Stack<size_t, kLimit> stack_;
    std::size_t value_{0U};
};

#endif    // STACK_UNITTEST_HPP_
