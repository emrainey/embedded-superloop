// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "jarnax/Yieldable.hpp"

using namespace jarnax;
using Yielder = Yieldable<int, 1024, 2>;

class Dummy : public Yielder {
public:
    Dummy()
        : Yielder() {}
    bool Execute(LoopInfo const &) override { return true; }
};

Dummy a;
Dummy b;
Dummy c;

TEST_CASE("Yieldable - Construction") {
    SECTION("Valid Yieldables") {
        REQUIRE(a.IsValid() == true);
        REQUIRE(b.IsValid() == true);
    }

    SECTION("Invalid Yieldables") {
        REQUIRE(c.IsValid() == false);
    }
}
