#include <catch2/catch_test_macros.hpp>

#include <cinttypes>

#include "core/Conversions.hpp"
#include "core/Status.hpp"

#include "jarnax/JumpTimer.hpp"
#include "jarnax/Monitor.hpp"

using namespace core::units;

namespace {

/// @brief Mock Indicator that tracks its state for testing
class TestIndicator : public jarnax::Indicator {
public:
    TestIndicator()
        : active_count_{0}
        , inactive_count_{0}
        , toggle_count_{0}
        , is_active_{false} {}

    virtual ~TestIndicator() = default;

    void Active() override {
        active_count_++;
        is_active_ = true;
    }

    void Inactive() override {
        inactive_count_++;
        is_active_ = false;
    }

    void Toggle() override {
        toggle_count_++;
        is_active_ = !is_active_;
    }

    std::size_t GetActiveCount() const { return active_count_; }
    std::size_t GetInactiveCount() const { return inactive_count_; }
    std::size_t GetToggleCount() const { return toggle_count_; }
    bool IsActive() const { return is_active_; }

    void Reset() {
        active_count_ = 0;
        inactive_count_ = 0;
        toggle_count_ = 0;
        is_active_ = false;
    }

private:
    std::size_t active_count_;
    std::size_t inactive_count_;
    std::size_t toggle_count_;
    bool is_active_;
};

}    // namespace

TEST_CASE("Monitor Construction", "[Monitor]") {
    jarnax::JumpTimer timer;
    TestIndicator status_indicator;
    TestIndicator error_indicator;
    ConfigureIotas(1'000'000);    // 1 iota = 1 microsecond for testing

    jarnax::Monitor monitor(timer, status_indicator, error_indicator);

    SECTION("Initial State") {
        // Indicators should not be touched until Execute is called
        REQUIRE(status_indicator.GetToggleCount() == 0);
        REQUIRE(error_indicator.GetActiveCount() == 0);
        REQUIRE(error_indicator.GetInactiveCount() == 0);
    }
}

TEST_CASE("Monitor Status Blink", "[Monitor]") {
    ConfigureIotas(1'000'000);    // 1 iota = 1 microsecond for testing
    const Iota half_period_iotas{core::units::ConvertToIota(jarnax::Monitor::HalfPeriodStatusBlink)};

    jarnax::JumpTimer timer;
    TestIndicator status_indicator;
    TestIndicator error_indicator;

    jarnax::Monitor monitor(timer, status_indicator, error_indicator);

    SECTION("Initial State") {
        // Indicators should not be touched until Execute is called
        REQUIRE(status_indicator.GetToggleCount() == 0);
        REQUIRE(error_indicator.GetActiveCount() == 0);
        REQUIRE(error_indicator.GetInactiveCount() == 0);
    }

    SECTION("Simple Timing Test") {
        // Timer starts at 0, Monitor sets countdown limit to 500'000
        REQUIRE(timer.GetIotas() == 0_iota);
        monitor.Execute();
        monitor.Execute();
        monitor.Execute();
        monitor.Execute();
        REQUIRE(timer.GetIotas() == 0_iota);
        REQUIRE(status_indicator.GetToggleCount() == 0);

        // Jump to 1 before expiration
        timer.Jump(half_period_iotas - 1_iota);
        REQUIRE(timer.GetIotas() == (half_period_iotas - 1_iota));

        // Execute - should NOT toggle yet?
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 0);

        // Jump past expiration
        timer.Jump(1_iota);
        REQUIRE(timer.GetIotas() == half_period_iotas);

        // Execute - should toggle now
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 1);
    }

    SECTION("Status Toggles After HalfPeriod") {
        // Jump to just before expiration
        timer.Jump(half_period_iotas - 1_iota);
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 0);

        // Jump past expiration
        timer.Jump(2_iota);
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 1);

        // Wait for next period
        timer.Jump(half_period_iotas);
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 2);
    }

    SECTION("Multiple Status Toggles") {
        // Simulate multiple blink cycles
        for (std::size_t i = 1; i <= 5; ++i) {
            timer.Jump(half_period_iotas);
            monitor.Execute();
            REQUIRE(status_indicator.GetToggleCount() == i);
        }
    }
}

TEST_CASE("Monitor Error Reporting", "[Monitor]") {
    ConfigureIotas(1'000'000);    // 1 iota = 1 microsecond for testing
    jarnax::JumpTimer timer;
    TestIndicator status_indicator;
    TestIndicator error_indicator;

    jarnax::Monitor monitor(timer, status_indicator, error_indicator);

    SECTION("Success Status - Error Inactive") {
        monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
        monitor.Execute();

        REQUIRE(error_indicator.GetInactiveCount() == 1);
        REQUIRE(error_indicator.GetActiveCount() == 0);
        REQUIRE_FALSE(error_indicator.IsActive());
    }

    SECTION("Error Status - Error Active") {
        monitor.Report(core::Status{core::Result::InvalidValue, core::Cause::Parameter});
        monitor.Execute();

        REQUIRE(error_indicator.GetActiveCount() == 1);
        REQUIRE(error_indicator.GetInactiveCount() == 0);
        REQUIRE(error_indicator.IsActive());
    }

    SECTION("Multiple Success Reports") {
        for (std::size_t i = 0; i < 3; ++i) {
            monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
            monitor.Execute();
        }

        REQUIRE(error_indicator.GetInactiveCount() == 3);
        REQUIRE(error_indicator.GetActiveCount() == 0);
    }

    SECTION("Multiple Error Reports") {
        monitor.Report(core::Status{core::Result::Timeout, core::Cause::Peripheral});
        monitor.Execute();
        REQUIRE(error_indicator.GetActiveCount() == 1);

        monitor.Report(core::Status{core::Result::Busy, core::Cause::Resource});
        monitor.Execute();
        REQUIRE(error_indicator.GetActiveCount() == 2);

        monitor.Report(core::Status{core::Result::OutOfRange, core::Cause::Parameter});
        monitor.Execute();
        REQUIRE(error_indicator.GetActiveCount() == 3);
    }

    SECTION("Alternating Success and Error") {
        monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
        monitor.Execute();
        REQUIRE(error_indicator.GetInactiveCount() == 1);

        monitor.Report(core::Status{core::Result::InvalidValue, core::Cause::Parameter});
        monitor.Execute();
        REQUIRE(error_indicator.GetActiveCount() == 1);

        monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
        monitor.Execute();
        REQUIRE(error_indicator.GetInactiveCount() == 2);
    }
}

TEST_CASE("Monitor Combined Behavior", "[Monitor]") {
    constexpr auto half_period = jarnax::Monitor::HalfPeriodStatusBlink;
    constexpr Iota half_period_iotas{half_period.value()};
    ConfigureIotas(1'000'000);    // 1 iota = 1 microsecond for testing

    jarnax::JumpTimer timer;
    TestIndicator status_indicator;
    TestIndicator error_indicator;

    jarnax::Monitor monitor(timer, status_indicator, error_indicator);

    SECTION("Status Blink and Error Reporting Together") {
        // Report success and execute
        monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
        monitor.Execute();
        REQUIRE(error_indicator.GetInactiveCount() == 1);
        REQUIRE(status_indicator.GetToggleCount() == 0);

        // Jump to trigger status blink
        timer.Jump(half_period_iotas);
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 1);
        REQUIRE(error_indicator.GetInactiveCount() == 2);    // Called again

        // Report error
        monitor.Report(core::Status{core::Result::Busy, core::Cause::Resource});
        timer.Jump(half_period_iotas);
        monitor.Execute();
        REQUIRE(status_indicator.GetToggleCount() == 2);
        REQUIRE(error_indicator.GetActiveCount() == 1);
    }

    SECTION("Execute Returns True") {
        // Monitor::Execute should always return true
        REQUIRE(monitor.Execute());
        monitor.Report(core::Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(monitor.Execute());
        monitor.Report(core::Status{core::Result::Timeout, core::Cause::Peripheral});
        REQUIRE(monitor.Execute());
    }
}
