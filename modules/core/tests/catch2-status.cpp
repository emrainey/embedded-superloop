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
}