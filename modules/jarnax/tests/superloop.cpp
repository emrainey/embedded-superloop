// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/Context.hpp"
#include "jarnax/SuperLoop.hpp"

#include <cstdio>

using namespace core::units;

namespace jarnax {
class Dummy : public Executable {
public:
    Dummy(const char *name)
        : name_{name}
        , count_{0u} {}
    bool Execute(LoopInfo const &) override {
        count_++;
        return true;
    }

    std::size_t Count() const { return count_; }
    void Print() const { printf("%s: %lu\r\n", name_, count_); }

protected:
    char const *name_;
    std::size_t count_;
};

class GlobalContext : public Context {
public:
    GlobalContext()
        : loop_{jarnax::GetTicker()} {}
    core::Status Initialize() override { return core::Status{}; }
    SuperLoop &GetSuperLoop(void) override { return loop_; }

protected:
    SuperLoop loop_;
};

Context &GetContext() {
    static GlobalContext my_context;
    return my_context;
}

class FakeTicker : public Ticker {
public:
    FakeTicker(Ticks starting)
        : current_{0u}
        , bias_{starting} {}
    Ticks GetTicksSinceBoot(void) const override {
        Ticks tmp;
        tmp = current_;
        current_ = current_ + 1_ticks;
        return tmp;
    }
    Hertz GetTicksPerSecond(void) const override { return Hertz{core::units::ticks_per_second.value()}; }
    Time GetTimeSinceBoot(void) const override { return core::units::ConvertToSeconds(GetTicksSinceBoot()); }
    Ticks GetTicks(void) const override { return GetTicksSinceBoot() + bias_; }
    Time GetTime(void) const override { return core::units::ConvertToSeconds(GetTicksSinceBoot() + bias_); }
    void AdjustTicks(Ticks bias) override { bias_ = bias; }
    bool IsEnabled(void) const override { return true; }

protected:
    mutable Ticks current_{0u};
    Ticks bias_{0u};
};

Ticker &GetTicker() {
    static FakeTicker ticker{0_ticks};
    return ticker;
}

TEST_CASE("SuperLoop - Cadence Test") {
    FakeTicker ticker{10_ticks};
    SuperLoop loop{ticker};
    Dummy dummy0{"Dummy0"};
    Dummy dummy1{"Dummy1"};
    Dummy dummy2{"Dummy2"};
    Dummy dummy3{"Dummy3"};
    // right now these have to be read as RIGHT to LEFT <--
    loop.Enlist(dummy0, 0b1010'1010'1010'1010'1010'1010'1010'1010u);
    loop.Enlist(dummy1, 0b0101'0101'0101'0101'0101'0101'0101'0101u);
    loop.Enlist(dummy2, 0b1111'1111'1111'1111'1111'1111'1111'1111u);
    loop.Enlist(dummy3, 0b1111'0000'1111'0000'1111'0000'1111'0000u);

    SECTION("Single Count") {
        loop.RunAllOnce();
        dummy0.Print();
        REQUIRE(dummy0.Count() == 0U);
        dummy1.Print();
        REQUIRE(dummy1.Count() == 1U);
        dummy2.Print();
        REQUIRE(dummy2.Count() == 1U);
        dummy3.Print();
        REQUIRE(dummy3.Count() == 0U);
    }
    SECTION("All Count") {
        for (size_t i = 0; i < 32U; i++) {
            loop.RunAllOnce();
        }
        dummy0.Print();
        REQUIRE(dummy0.Count() == 16U);
        dummy1.Print();
        REQUIRE(dummy1.Count() == 16U);
        dummy2.Print();
        REQUIRE(dummy2.Count() == 32U);
        dummy3.Print();
        REQUIRE(dummy3.Count() == 16U);
    }
}

}    // namespace jarnax