#include "memory.hpp"
#include "strings.hpp"

#include <catch2/catch_test_macros.hpp>

using namespace strings;

TEST_CASE("length of empty string is zero", "[strings]") {
    REQUIRE(length("") == 0);
}

TEST_CASE("length of a string", "[strings]") {
    REQUIRE(length("hello") == 5);
    REQUIRE(length("a") == 1);
}

TEST_CASE("last_character not found returns nullptr", "[strings]") {
    REQUIRE(last_character("hello", 'z') == nullptr);
    REQUIRE(last_character("", 'a') == nullptr);
}

TEST_CASE("last_character returns the last occurrence", "[strings]") {
    char const* const text = "a/b/c/d";
    char const* const found = last_character(text, '/');
    REQUIRE(found != nullptr);
    REQUIRE(*found == '/');
    REQUIRE(found == text + 5);
}

TEST_CASE("last_character single occurrence", "[strings]") {
    char const* const text = "dir/file";
    char const* const found = last_character(text, '/');
    REQUIRE(found == text + 3);
}

TEST_CASE("last_character returns the whole string when it is the separator", "[strings]") {
    char const* const text = "/";
    char const* const found = last_character(text, '/');
    REQUIRE(found == text);
}

TEST_CASE("last_character at the end of the string", "[strings]") {
    char const* const text = "abc/";
    char const* const found = last_character(text, '/');
    REQUIRE(found == text + 3);
}

TEST_CASE("memory move copies forward when ranges do not overlap", "[memory][move]") {
    std::uint8_t buffer[] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U};
    std::uint8_t src[] = {0x0AU, 0x0BU, 0x0CU};
    memory::move(buffer, src, 3U);
    REQUIRE(buffer[0] == 0x0AU);
    REQUIRE(buffer[1] == 0x0BU);
    REQUIRE(buffer[2] == 0x0CU);
    REQUIRE(buffer[3] == 0x04U);    // untouched tail
    REQUIRE(buffer[4] == 0x05U);
}

TEST_CASE("memory move handles overlapping ranges (forward shift)", "[memory][move]") {
    std::uint8_t buffer[] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U};
    // Shift the first three bytes one position to the right (overlap, dest > src).
    memory::move(buffer + 1, buffer, 3U);
    REQUIRE(buffer[0] == 0x01U);
    REQUIRE(buffer[1] == 0x01U);
    REQUIRE(buffer[2] == 0x02U);
    REQUIRE(buffer[3] == 0x03U);
    REQUIRE(buffer[4] == 0x05U);
}

TEST_CASE("memory move handles overlapping ranges (backward shift)", "[memory][move]") {
    std::uint8_t buffer[] = {0x01U, 0x02U, 0x03U, 0x04U, 0x05U};
    // Shift the last three bytes one position to the left (overlap, dest < src).
    memory::move(buffer + 1, buffer + 2, 3U);
    REQUIRE(buffer[0] == 0x01U);
    REQUIRE(buffer[1] == 0x03U);
    REQUIRE(buffer[2] == 0x04U);
    REQUIRE(buffer[3] == 0x05U);
    REQUIRE(buffer[4] == 0x05U);    // untouched tail
}

TEST_CASE("memory move of zero bytes does nothing", "[memory][move]") {
    std::uint8_t buffer[] = {0x01U, 0x02U, 0x03U};
    memory::move(buffer, buffer, 0U);
    REQUIRE(buffer[0] == 0x01U);
    REQUIRE(buffer[1] == 0x02U);
    REQUIRE(buffer[2] == 0x03U);
}

TEST_CASE("memory copy copies bytes from const source", "[memory][copy]") {
    char const* const src = "\x0A\x0B\x0C\x0D";
    std::uint8_t dst[4]{};
    memory::copy(dst, src, 4U);
    REQUIRE(dst[0] == 0x0AU);
    REQUIRE(dst[1] == 0x0BU);
    REQUIRE(dst[2] == 0x0CU);
    REQUIRE(dst[3] == 0x0DU);
}

TEST_CASE("memory copy of zero bytes does nothing", "[memory][copy]") {
    char const src = 0x0A;
    std::uint8_t dst = 0x55U;
    memory::copy(&dst, &src, 0U);
    REQUIRE(dst == 0x55U);
}
