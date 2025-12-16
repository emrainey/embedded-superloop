#include <catch2/catch_test_macros.hpp>
#include "core/Split.hpp"

TEST_CASE("Split - Basic Properties with uint8_t") {
    SECTION("Split 8 bits at position 3") {
        using SplitType = core::Split<std::uint8_t, 3>;
        REQUIRE(SplitType::StorageNumberOfBits == 8U);
        REQUIRE(SplitType::SplitNumberOfBits == 3U);
        REQUIRE(sizeof(SplitType) == sizeof(std::uint8_t));
    }

    SECTION("Split 8 bits at position 4") {
        using SplitType = core::Split<std::uint8_t, 4>;
        REQUIRE(SplitType::StorageNumberOfBits == 8U);
        REQUIRE(SplitType::SplitNumberOfBits == 4U);
        REQUIRE(sizeof(SplitType) == sizeof(std::uint8_t));
    }

    SECTION("Split 8 bits at position 1") {
        using SplitType = core::Split<std::uint8_t, 1>;
        REQUIRE(SplitType::StorageNumberOfBits == 8U);
        REQUIRE(SplitType::SplitNumberOfBits == 1U);
        REQUIRE(sizeof(SplitType) == sizeof(std::uint8_t));
    }

    SECTION("Split 8 bits at position 7") {
        using SplitType = core::Split<std::uint8_t, 7>;
        REQUIRE(SplitType::StorageNumberOfBits == 8U);
        REQUIRE(SplitType::SplitNumberOfBits == 7U);
        REQUIRE(sizeof(SplitType) == sizeof(std::uint8_t));
    }
}

TEST_CASE("Split - Whole Value Access") {
    SECTION("Split at 3 bits - set whole value") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0xA5;    // 10100101
        REQUIRE(split.whole == 0xA5);
    }

    SECTION("Split at 4 bits - set whole value") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xFF;    // 11111111
        REQUIRE(split.whole == 0xFF);
    }

    SECTION("Split at 1 bit - set whole value") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0x00;
        REQUIRE(split.whole == 0x00);
    }
}

TEST_CASE("Split - Lower Bits Access") {
    SECTION("Split at 3 bits - lower 3 bits") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0xA5;    // 10100101
        // Lower 3 bits: 101 = 5
        REQUIRE(split.parts.lower == 0x05);
    }

    SECTION("Split at 4 bits - lower 4 bits") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xA5;    // 10100101
        // Lower 4 bits: 0101 = 5
        REQUIRE(split.parts.lower == 0x05);
    }

    SECTION("Split at 1 bit - lower 1 bit") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0xA5;    // 10100101
        // Lower 1 bit: 1 = 1
        REQUIRE(split.parts.lower == 0x01);
    }

    SECTION("Split at 7 bits - lower 7 bits") {
        core::Split<std::uint8_t, 7> split;
        split.whole = 0xA5;    // 10100101
        // Lower 7 bits: 0100101 = 0x25
        REQUIRE(split.parts.lower == 0x25);
    }
}

TEST_CASE("Split - Upper Bits Access") {
    SECTION("Split at 3 bits - upper 5 bits") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0xA5;    // 10100101
        // Upper 5 bits: 10100 = 20
        REQUIRE(split.parts.upper == 0x14);
    }

    SECTION("Split at 4 bits - upper 4 bits") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xA5;    // 10100101
        // Upper 4 bits: 1010 = 10
        REQUIRE(split.parts.upper == 0x0A);
    }

    SECTION("Split at 1 bit - upper 7 bits") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0xA5;    // 10100101
        // Upper 7 bits: 1010010 = 0x52
        REQUIRE(split.parts.upper == 0x52);
    }

    SECTION("Split at 7 bits - upper 1 bit") {
        core::Split<std::uint8_t, 7> split;
        split.whole = 0xA5;    // 10100101
        // Upper 1 bit: 1 = 1
        REQUIRE(split.parts.upper == 0x01);
    }
}

TEST_CASE("Split - Setting Lower Bits") {
    SECTION("Split at 3 bits - set lower bits") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0x00;
        split.parts.lower = 0x07;    // 111
        // Lower 3 bits should be 111, upper should remain 0
        REQUIRE(split.parts.lower == 0x07);
        REQUIRE(split.parts.upper == 0x00);
        REQUIRE(split.whole == 0x07);
    }

    SECTION("Split at 4 bits - set lower bits") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0x00;
        split.parts.lower = 0x0F;    // 1111
        REQUIRE(split.parts.lower == 0x0F);
        REQUIRE(split.parts.upper == 0x00);
        REQUIRE(split.whole == 0x0F);
    }
}

TEST_CASE("Split - Setting Upper Bits") {
    SECTION("Split at 3 bits - set upper bits") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0x00;
        split.parts.upper = 0x1F;    // 11111 (5 bits)
        // Upper 5 bits should be 11111
        REQUIRE(split.parts.upper == 0x1F);
        REQUIRE(split.parts.lower == 0x00);
        REQUIRE(split.whole == 0xF8);    // 11111000
    }

    SECTION("Split at 4 bits - set upper bits") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0x00;
        split.parts.upper = 0x0F;    // 1111 (4 bits)
        REQUIRE(split.parts.upper == 0x0F);
        REQUIRE(split.parts.lower == 0x00);
        REQUIRE(split.whole == 0xF0);    // 11110000
    }

    SECTION("Split at 1 bit - set upper bits") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0x00;
        split.parts.upper = 0x7F;    // 1111111 (7 bits)
        REQUIRE(split.parts.upper == 0x7F);
        REQUIRE(split.parts.lower == 0x00);
        REQUIRE(split.whole == 0xFE);    // 11111110
    }
}

TEST_CASE("Split - Setting Both Parts") {
    SECTION("Split at 3 bits - set both parts") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0x00;
        split.parts.lower = 0x05;    // 101
        split.parts.upper = 0x14;    // 10100
        REQUIRE(split.parts.lower == 0x05);
        REQUIRE(split.parts.upper == 0x14);
        REQUIRE(split.whole == 0xA5);    // 10100101
    }

    SECTION("Split at 4 bits - set both parts") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0x00;
        split.parts.lower = 0x0A;    // 1010
        split.parts.upper = 0x05;    // 0101
        REQUIRE(split.parts.lower == 0x0A);
        REQUIRE(split.parts.upper == 0x05);
        REQUIRE(split.whole == 0x5A);    // 01011010
    }

    SECTION("Split at 1 bit - set both parts") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0x00;
        split.parts.lower = 0x01;    // 1
        split.parts.upper = 0x52;    // 1010010
        REQUIRE(split.parts.lower == 0x01);
        REQUIRE(split.parts.upper == 0x52);
        REQUIRE(split.whole == 0xA5);    // 10100101
    }
}

TEST_CASE("Split - Modifying Parts Independently") {
    SECTION("Split at 4 bits - modify lower without affecting upper") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xA5;    // 10100101
        REQUIRE(split.parts.lower == 0x05);
        REQUIRE(split.parts.upper == 0x0A);

        split.parts.lower = 0x0F;              // Change lower to 1111
        REQUIRE(split.parts.lower == 0x0F);
        REQUIRE(split.parts.upper == 0x0A);    // Upper should remain unchanged
        REQUIRE(split.whole == 0xAF);          // 10101111
    }

    SECTION("Split at 4 bits - modify upper without affecting lower") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xA5;    // 10100101
        REQUIRE(split.parts.lower == 0x05);
        REQUIRE(split.parts.upper == 0x0A);

        split.parts.upper = 0x05;              // Change upper to 0101
        REQUIRE(split.parts.lower == 0x05);    // Lower should remain unchanged
        REQUIRE(split.parts.upper == 0x05);
        REQUIRE(split.whole == 0x55);          // 01010101
    }
}

TEST_CASE("Split - Boundary Values") {
    SECTION("Split at 3 bits - all zeros") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0x00;
        REQUIRE(split.parts.lower == 0x00);
        REQUIRE(split.parts.upper == 0x00);
        REQUIRE(split.whole == 0x00);
    }

    SECTION("Split at 3 bits - all ones") {
        core::Split<std::uint8_t, 3> split;
        split.whole = 0xFF;
        REQUIRE(split.parts.lower == 0x07);    // 111
        REQUIRE(split.parts.upper == 0x1F);    // 11111
        REQUIRE(split.whole == 0xFF);
    }

    SECTION("Split at 4 bits - all zeros") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0x00;
        REQUIRE(split.parts.lower == 0x00);
        REQUIRE(split.parts.upper == 0x00);
        REQUIRE(split.whole == 0x00);
    }

    SECTION("Split at 4 bits - all ones") {
        core::Split<std::uint8_t, 4> split;
        split.whole = 0xFF;
        REQUIRE(split.parts.lower == 0x0F);    // 1111
        REQUIRE(split.parts.upper == 0x0F);    // 1111
        REQUIRE(split.whole == 0xFF);
    }
}

TEST_CASE("Split - Edge Cases") {
    SECTION("Split at 1 bit - minimum split") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0b10101010;
        REQUIRE(split.parts.lower == 0);            // Bit 0
        REQUIRE(split.parts.upper == 0b1010101);    // Bits 7-1
    }

    SECTION("Split at 7 bits - maximum split") {
        core::Split<std::uint8_t, 7> split;
        split.whole = 0b10101010;
        REQUIRE(split.parts.lower == 0b0101010);    // Bits 6-0
        REQUIRE(split.parts.upper == 1);            // Bit 7
    }

    SECTION("Split at 1 bit - alternating pattern") {
        core::Split<std::uint8_t, 1> split;
        split.whole = 0x55;                    // 01010101
        REQUIRE(split.parts.lower == 1);
        REQUIRE(split.parts.upper == 0x2A);    // 0101010
    }

    SECTION("Split at 7 bits - alternating pattern") {
        core::Split<std::uint8_t, 7> split;
        split.whole = 0x55;                    // 01010101
        REQUIRE(split.parts.lower == 0x55);    // 1010101
        REQUIRE(split.parts.upper == 0);
    }
}

TEST_CASE("Split - Practical Use Cases") {
    SECTION("Split at 2 bits - extracting 2-bit field") {
        core::Split<std::uint8_t, 2> split;
        split.whole = 0b11010110;
        REQUIRE(split.parts.lower == 0b10);        // Lower 2 bits
        REQUIRE(split.parts.upper == 0b110101);    // Upper 6 bits
    }

    SECTION("Split at 5 bits - extracting 5-bit field") {
        core::Split<std::uint8_t, 5> split;
        split.whole = 0b11010110;
        REQUIRE(split.parts.lower == 0b10110);    // Lower 5 bits
        REQUIRE(split.parts.upper == 0b110);      // Upper 3 bits
    }

    SECTION("Split at 6 bits - extracting 6-bit field") {
        core::Split<std::uint8_t, 6> split;
        split.whole = 0b11010110;
        REQUIRE(split.parts.lower == 0b010110);    // Lower 6 bits
        REQUIRE(split.parts.upper == 0b11);        // Upper 2 bits
    }
}
