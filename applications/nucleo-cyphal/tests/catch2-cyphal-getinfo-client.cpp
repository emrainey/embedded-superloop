#define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>

#include "GetInfoScanner.hpp"

using nucleo::cyphal::GetInfoScanner;

namespace {

GetInfoScanner MakeDefaultScanner() {
    return GetInfoScanner{2U, 10U};
}

}    // namespace

TEST_CASE("GetInfoScanner Empty case: fresh scanner has no pending query", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner = MakeDefaultScanner();
    REQUIRE_FALSE(scanner.HasPending());
    REQUIRE(scanner.PendingNode() == 0U);
    REQUIRE(scanner.PeekNext() == 2U);
    REQUIRE(scanner.TidCount() == 0U);
}

TEST_CASE("GetInfoScanner TakeNext walks the window and wraps around", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{4U, 6U};
    REQUIRE(scanner.TakeNext() == 4U);
    REQUIRE(scanner.TakeNext() == 5U);
    REQUIRE(scanner.TakeNext() == 6U);
    REQUIRE(scanner.TakeNext() == 4U);    // wraps back to first
    REQUIRE(scanner.TakeNext() == 5U);
}

TEST_CASE("GetInfoScanner single-node window always yields that node", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{7U, 7U};
    REQUIRE(scanner.TakeNext() == 7U);
    REQUIRE(scanner.TakeNext() == 7U);
    REQUIRE(scanner.PeekNext() == 7U);
}

TEST_CASE("GetInfoScanner IsInRange respects inclusive bounds", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{2U, 10U};
    REQUIRE(scanner.IsInRange(2U));
    REQUIRE(scanner.IsInRange(10U));
    REQUIRE(scanner.IsInRange(7U));
    REQUIRE_FALSE(scanner.IsInRange(1U));
    REQUIRE_FALSE(scanner.IsInRange(11U));
    REQUIRE_FALSE(scanner.IsInRange(100U));
}

TEST_CASE("GetInfoScanner Reset re-arms cursor and clears pending", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{2U, 5U};
    (void)scanner.TakeNext();
    (void)scanner.TakeNext();
    scanner.SetPending(3U);
    REQUIRE(scanner.HasPending());
    scanner.Reset();
    REQUIRE_FALSE(scanner.HasPending());
    REQUIRE(scanner.PeekNext() == 2U);
}

TEST_CASE("GetInfoScanner SetPending only accepts an in-range node", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{2U, 10U};
    scanner.SetPending(3U);
    REQUIRE(scanner.HasPending());
    REQUIRE(scanner.PendingNode() == 3U);
    scanner.ClearPending();
    REQUIRE_FALSE(scanner.HasPending());

    scanner.SetPending(42U);    // outside window
    REQUIRE_FALSE(scanner.HasPending());

    scanner.SetPending(2U);
    scanner.SetPending(9U);    // already pending
    REQUIRE(scanner.PendingNode() == 2U);
}

TEST_CASE("GetInfoScanner NextTransferId tracks an independent counter per server node", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{2U, 10U};
    REQUIRE(scanner.NextTransferId(2U) == 0U);
    REQUIRE(scanner.NextTransferId(2U) == 1U);
    REQUIRE(scanner.NextTransferId(3U) == 0U);    // different node, fresh counter
    REQUIRE(scanner.NextTransferId(2U) == 2U);    // node 2 counter independent of node 3
    REQUIRE(scanner.NextTransferId(8U) == 0U);
    REQUIRE(scanner.TidCount() == 3U);
}

TEST_CASE("GetInfoScanner NextTransferId ignores out-of-window nodes", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{2U, 10U};
    REQUIRE(scanner.NextTransferId(1U) == 0U);
    REQUIRE(scanner.NextTransferId(200U) == 0U);
    REQUIRE(scanner.TidCount() == 0U);
}

TEST_CASE("GetInfoScanner full window never exceeds the tracking table", "[cyphal][getinfo][scanner]") {
    GetInfoScanner scanner{1U, 254U};    // exceeds MaxWindowSize
    std::uint64_t last_tid = 0U;
    for (unsigned int i = 0U; i < GetInfoScanner::MaxWindowSize; ++i) {
        last_tid = scanner.NextTransferId(static_cast<std::uint16_t>(1U + i));
    }
    REQUIRE(scanner.TidCount() == GetInfoScanner::MaxWindowSize);
    // The next distinct node cannot be tracked anymore.
    REQUIRE(scanner.NextTransferId(GetInfoScanner::MaxWindowSize + 1U) == 0U);
    REQUIRE(last_tid == 0U);
}