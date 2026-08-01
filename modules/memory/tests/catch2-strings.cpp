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
