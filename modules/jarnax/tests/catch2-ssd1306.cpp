// #define CATCH_CONFIG_MAIN
#include <catch2/catch_test_macros.hpp>
#include "ssd1306.hpp"

TEST_CASE("SSD1306") {
    ::ssd1306::Image128x32 image;
    ::ssd1306::Screen128x32 screen(image);

    // Test the SSD1306 symbols
    REQUIRE(ssd1306::symbols::block[0] == 0xFF);
    REQUIRE(ssd1306::symbols::space[0] == 0x00);

    REQUIRE(image.width == 128);
    REQUIRE(image.height == 32);
    image.clear();

    SECTION("SSD1306 Image Pattern") {
        REQUIRE(image.GetData()[0] == 0x00);
        image.pattern();
        image.render();
        REQUIRE(image.GetData()[1] == 0x01);
    }
    SECTION("Single Pixel on Screen") {
        screen.write(ssd1306::symbols::block, 0, 0);
        screen.render();
        REQUIRE(image.GetData()[0] == 0xFF);
        image.clear();
        REQUIRE(image.GetData()[0] == 0x00);
    }
    SECTION("Checkerboard Pattern") {
        screen.checkerboard();
        screen.render();
        image.render();
        REQUIRE(image.GetData()[0] == 0xAA);    // Checkerboard pattern should have alternating bits
    }
}