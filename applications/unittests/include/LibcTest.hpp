#ifndef LIBC_UNITTEST_HPP_
#define LIBC_UNITTEST_HPP_

#include "jarnax.hpp"
#include "jarnax/UnitTest.hpp"    // the template

using jarnax::Executable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class LibcTests : std::uint32_t {
    kCompare = 1U,
    kFill,
    kCopyCompare,
    kFillCopyCompare,

    // bookkeeping
    kMinimum = kCompare,
    kStep = 1U,
    kMaximum = kFillCopyCompare
};

/// A unit test of some number of collected ticks to ensure they are monotonic
class LibcTest final : public jarnax::UnitTest<LibcTests, 8> {
public:
    // using State = typename jarnax::UnitTest<LibcTests, 8>::State;
    LibcTest();
    State Test(EnumType test_enum) override;

protected:
    constexpr static size_t kLength{20U};    ///< The length of the test arrays
    constexpr static uint8_t fill_value{0xA5U};
    constexpr static uint8_t anti_fill_value{0x5AU};
    uint8_t src[kLength];
    uint8_t tmp[kLength];
    uint8_t dst[kLength];
};

#endif    // LIBC_UNITTEST_HPP_
