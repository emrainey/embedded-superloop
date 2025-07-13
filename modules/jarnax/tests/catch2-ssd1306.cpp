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
        image.pattern(::ssd1306::Image128x32::Pattern::Checkerboard);
        image.render();
    }
    SECTION("SSD1306 Image Pattern") {
        REQUIRE(image.GetData()[0] == 0x00);
        image.pattern(::ssd1306::Image128x32::Pattern::VerticalStripes);
        image.render();
    }
    SECTION("SSD1306 Image Pattern") {
        REQUIRE(image.GetData()[0] == 0x00);
        image.pattern(::ssd1306::Image128x32::Pattern::HorizontalStripes);
        image.render();
    }
    SECTION("SSD1306 Image Pattern") {
        REQUIRE(image.GetData()[0] == 0x00);
        image.pattern(::ssd1306::Image128x32::Pattern::AA55);
        image.render();
    }
    SECTION("SSD1306 Image Pattern") {
        REQUIRE(image.GetData()[0] == 0x00);
        image.pattern(::ssd1306::Image128x32::Pattern::FlippingCounters);
        image.render();
    }
    SECTION("Single Pixel on Screen") {
        REQUIRE(image.GetData()[0] == 0x00);
        screen.clear();
        screen.write(0, 0, ssd1306::symbols::alphabet[0]);    // Write 'A' to the screen
        screen.render();
    }
    SECTION("Checkerboard Pattern") {
        screen.checkerboard();
        screen.render();
        REQUIRE(image.GetData()[0] == 0x00);
        REQUIRE(image.GetData()[8] == 0xFF);
    }
    SECTION("Write String to Screen") {
        screen.clear();
        screen.write(0, 0, "Hello World");
        screen.render();
    }
}