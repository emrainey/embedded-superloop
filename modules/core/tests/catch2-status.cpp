// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "core/Status.hpp"

TEST_CASE("Status") {
    SECTION("Default Constructor") {
        core::Status status;
        REQUIRE(bool(status));
        REQUIRE(status.IsSuccess());
        REQUIRE_FALSE(status.IsBusy());
        REQUIRE(status == core::Status{core::Result::Success, core::Cause::Unknown});
    }
    SECTION("Parameter Constructor") {
        core::Status status{core::Result::Busy, core::Cause::State};
        REQUIRE_FALSE(bool(status));
        REQUIRE_FALSE(status.IsSuccess());
        REQUIRE(status.IsBusy());
        REQUIRE(status == core::Status{core::Result::Busy, core::Cause::State});
    }
    SECTION("Comparison") {
        core::Status status{core::Result::Success, core::Cause::Unknown};
        REQUIRE(status == core::Status{core::Result::Success, core::Cause::Unknown});
        REQUIRE(status != core::Status{core::Result::Failure, core::Cause::Unknown});
        REQUIRE_FALSE(status == core::Status{core::Result::Failure, core::Cause::Unknown});
        REQUIRE(status != core::Status{core::Result::Success, core::Cause::Parameter});
        REQUIRE_FALSE(status == core::Status{core::Result::Success, core::Cause::Parameter});
        REQUIRE(status != core::Status{core::Result::Failure, core::Cause::Parameter});
        REQUIRE_FALSE(status == core::Status{core::Result::Failure, core::Cause::Parameter});
    }
    SECTION("Location") {
        core::Status status{core::Result::Success, core::Cause::Unknown};
        REQUIRE(status.GetLocation() != 0);
    }
    SECTION("Statistics") {
        core::Status status1{core::Result::Success, core::Cause::Unknown};
        core::Status status2{core::Result::Busy, core::Cause::State};
        core::Status status3{core::Result::Failure, core::Cause::Parameter};
        core::Status status4{core::Result::Timeout, core::Cause::Hardware};
        core::Status status5{core::Result::NotReady, core::Cause::Configuration};

        core::Status::Statistics const& stats = core::Status::GetStatistics();
        REQUIRE(stats.total >= 5U);
        REQUIRE(stats.result_counts.fields.success >= 1U);
        REQUIRE(stats.result_counts.fields.busy >= 1U);
        REQUIRE(stats.result_counts.fields.failure >= 1U);
        REQUIRE(stats.result_counts.fields.timeout >= 1U);
        REQUIRE(stats.result_counts.fields.not_ready >= 1U);
        REQUIRE(stats.cause_counts.fields.unknown >= 1U);
        REQUIRE(stats.cause_counts.fields.state >= 1U);
        REQUIRE(stats.cause_counts.fields.parameter >= 1U);
        REQUIRE(stats.cause_counts.fields.hardware >= 1U);
        REQUIRE(stats.cause_counts.fields.configuration >= 1U);
    }
    SECTION("Log") {
        core::Status status1{core::Result::Failure, core::Cause::Parameter};
        core::Status status2{core::Result::Timeout, core::Cause::Hardware};
        core::Status status3{core::Result::NotReady, core::Cause::Configuration};

        auto& log = core::Status::GetLog();
        REQUIRE(log.Count() >= 3U);

        bool found_status1 = false;
        bool found_status2 = false;
        bool found_status3 = false;

        while (log.Count() > 0) {
            auto& entry = log.Peek();
            if (entry == status1) {
                found_status1 = true;
            } else if (entry == status2) {
                found_status2 = true;
            } else if (entry == status3) {
                found_status3 = true;
            }
            printf(
                "Log Entry: Result=%d, Cause=%d Location=%p\r\n",
                static_cast<int>(entry.GetResult()),
                static_cast<int>(entry.GetCause()),
                reinterpret_cast<void*>(entry.GetLocation())
            );
            log.Drop(1);    // remove 1 entry
        }

        REQUIRE(found_status1);
        REQUIRE(found_status2);
        REQUIRE(found_status3);
    }
}
