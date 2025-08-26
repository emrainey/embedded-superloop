// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include <catch2/matchers/catch_matchers_floating_point.hpp>
#include "core/Tokenizer.hpp"

#include <iostream>

void Print(core::hayes::Token token, const char *expected) {
    printf("Actual Token=[%zu]\"%.*s\" Expected: \"%s\"\r\n", token.size(), static_cast<int>(token.size()), token.data(), expected);
}

class TokenizerTest {
public:
    TokenizerTest() {
        // Constructor implementation
    }

    void PrepareAsDisjointed() {
        REQUIRE(tokenizer.Push("\r\nO"));
        REQUIRE(tokenizer.Push("K\r\n"));
        REQUIRE(tokenizer.Push("\r\nER"));
        REQUIRE(tokenizer.Push("ROR\r\n"));
        REQUIRE(tokenizer.Push("\x10\x04\r\nN"));
        REQUIRE(tokenizer.Push("O CARRIER\r\n"));
        REQUIRE(tokenizer.Push("\r"));
        REQUIRE(tokenizer.Push("\nAT+BOB: "));
        REQUIRE(tokenizer.Push("-19, 40\r\n"));

        REQUIRE(50 == tokenizer.GetStatistics().pushed);
    }

    void PrepareAsNormal() {
        REQUIRE(tokenizer.Push("\r\nOK\r\n"));
        REQUIRE(tokenizer.Push("\r\nERROR\r\n"));
        REQUIRE(tokenizer.Push("\x10\x04\r\nNO CARRIER\r\n"));
        REQUIRE(tokenizer.Push("\r\nAT+BOB: -19, 40\r\n"));
        REQUIRE(not tokenizer.IsEmpty());

        REQUIRE(50 == tokenizer.GetStatistics().pushed);
    }

    void ExpectToken(const char *expected, size_t expected_tokens, size_t expected_counted) {
        auto token = tokenizer.Get();
        Print(token, expected);
        REQUIRE(expected_tokens == tokenizer.GetStatistics().tokens);
        REQUIRE(expected_counted == tokenizer.GetStatistics().counted);
        REQUIRE(not token.IsEmpty());
        REQUIRE(memory::compare(token.data(), expected, strings::length(expected)) == 0);
        tokenizer.Consume(token);
    }

    void ExpectTokens() {
        ExpectToken("\r\n", 1, 2);
        ExpectToken("OK\r\n", 2, 6);
        ExpectToken("\r\n", 3, 8);
        ExpectToken("ERROR\r\n", 4, 15);
        ExpectToken("\x10\x04\r\n", 5, 19);
        ExpectToken("NO CARRIER\r\n", 6, 31);
        ExpectToken("\r\n", 7, 33);
        ExpectToken("AT+BOB: -19, 40\r\n", 8, 50);
    }

    core::hayes::Tokenizer_<64U> tokenizer{"\r\n"};
};

TEST_CASE("Tokenizer") {
    TokenizerTest test;

    SECTION("Full Sequence Stream") {
        test.PrepareAsNormal();
        test.ExpectTokens();
    }

    SECTION("Partial Stream") {
        test.PrepareAsDisjointed();
        test.ExpectTokens();
    }
}
