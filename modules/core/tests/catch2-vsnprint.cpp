#include <catch2/catch_test_macros.hpp>
#include "core/vsnprint.hpp"
#include <cstdarg>
#include <string>

static unsigned long test_vsnprint(char buffer[], size_t buffer_size, const char* format, ...) {
    va_list args;
    va_start(args, format);
    unsigned long result = core::vsnprint(buffer, buffer_size, format, args);
    va_end(args);
    return result;
}

TEST_CASE("vsnprint formatting checks") {
    char buffer[128];

    SECTION("Normal string without formatting") {
        unsigned long len = test_vsnprint(buffer, sizeof(buffer), "Hello World");
        REQUIRE(std::string(buffer) == "Hello World");
        REQUIRE(len == 11);
    }

    SECTION("Uppercase hex with modifiers and padding (%X)") {
        unsigned long len = test_vsnprint(buffer, sizeof(buffer), "%02X", 0x0A);
        REQUIRE(std::string(buffer) == "0A");
        REQUIRE(len == 2);

        len = test_vsnprint(buffer, sizeof(buffer), "%02X", 0x5);
        REQUIRE(std::string(buffer) == "05");
        REQUIRE(len == 2);

        len = test_vsnprint(buffer, sizeof(buffer), "%X", 0xABC);
        REQUIRE(std::string(buffer) == "ABC");
        REQUIRE(len == 3);

        len = test_vsnprint(buffer, sizeof(buffer), "%08X", 0x12AB);
        REQUIRE(std::string(buffer) == "000012AB");
        REQUIRE(len == 8);
    }

    SECTION("Lowercase hex with prepended 0x (%x)") {
        unsigned long len = test_vsnprint(buffer, sizeof(buffer), "%x", 0x12AB);
        REQUIRE(std::string(buffer) == "0x12ab");
        REQUIRE(len == 6);

        len = test_vsnprint(buffer, sizeof(buffer), "%08x", 0x12AB);
        REQUIRE(std::string(buffer) == "0x0012ab"); // 0x + 6 padded hex digits = 8 chars
        REQUIRE(len == 8);
    }

    SECTION("Decimal signed/unsigned formatting with width and padding") {
        unsigned long len = test_vsnprint(buffer, sizeof(buffer), "%d", -123);
        REQUIRE(std::string(buffer) == "-123");
        REQUIRE(len == 4);

        len = test_vsnprint(buffer, sizeof(buffer), "%04d", -5);
        REQUIRE(std::string(buffer) == "-005");
        REQUIRE(len == 4);

        len = test_vsnprint(buffer, sizeof(buffer), "%4d", -5);
        REQUIRE(std::string(buffer) == "  -5");
        REQUIRE(len == 4);

        len = test_vsnprint(buffer, sizeof(buffer), "%04u", 7);
        REQUIRE(std::string(buffer) == "0007");
        REQUIRE(len == 4);
    }

    SECTION("Binary formatting with prepended 0b (%b)") {
        unsigned long len = test_vsnprint(buffer, sizeof(buffer), "%b", 5);
        REQUIRE(std::string(buffer) == "0b101");
        REQUIRE(len == 5);

        len = test_vsnprint(buffer, sizeof(buffer), "%08b", 5);
        REQUIRE(std::string(buffer) == "0b000101"); // 0b + 6 padded binary digits = 8 chars
        REQUIRE(len == 8);
    }
}
