#ifndef SDD1306_HPP
#define SDD1306_HPP

#include <cstdint>
#include <cstddef>
#include <limits>
#include "memory.hpp"
#if defined(UNITTEST)
#include <cstdio>
#endif

namespace ssd1306 {

using symbol = uint8_t[8];
static_assert(sizeof(symbol) == 8u, "Must be 8 bytes in size");

namespace symbols {
extern symbol const block;
extern symbol const space;
extern symbol const box;
extern symbol const hash;
extern symbol const alphabet[26];
extern symbol const numerals[10];
}    // namespace symbols

struct Control {
    /// @brief Value to use for Commands Following this Byte
    /// Co = 1, D/C = 0
    static constexpr std::uint8_t CommandMode{0x80U};
    /// @brief Value to use for Data Following this Byte
    /// Co = 1, D/C = 1
    static constexpr std::uint8_t DataMode{0x40U};
    /// @brief Control byte for Data Only
    /// Co = 0, D/C = 1
    static constexpr std::uint8_t DataOnly{0x00U};
};

struct Command {
    // Lower Column Addresses = 0x00 to 0x0F
    // Higher Column Addresses = 0x10 to 0x1F
    static constexpr uint8_t MemoryAddressingMode = 0x20U;
    static constexpr uint8_t SetColumnAddress = 0x21U;
    static constexpr uint8_t SetPageAddress = 0x22U;
    static constexpr uint8_t DeactivateScroll = 0x2EU;
    static constexpr uint8_t ActivateScroll = 0x2FU;
    // Set Display Start Line = 0x40 to 0x7F
    static constexpr uint8_t DisplayStartLine = 0x40U;
    static constexpr uint8_t SetStartLine = 0x40U;
    static constexpr uint8_t ContrastControl = 0x81U;
    static constexpr uint8_t ChargePump = 0x8DU;          ///< Sets the charge pump for the display
    static constexpr uint8_t SetSegmentRemap0 = 0xA0U;    ///< Sets the segment remap for the display (Col0 = Seg0)
    static constexpr uint8_t SetSegmentRemap1 = 0xA0U;    ///< Sets the segment remap for the display (Col0 = Seg127)
    static constexpr uint8_t Resume = 0xA4U;              ///< Resumes displaying whatever is in the display memory
    static constexpr uint8_t AllPixelsOn = 0xA5U;         ///< Sets all pixels to ON, regardless of the display memory
    static constexpr uint8_t NormalDisplay = 0xA6U;       ///< Off Pixels are OFF, On Pixels are ON
    static constexpr uint8_t InverseDisplay = 0xA7U;      ///< Off Pixels are ON, On Pixels are OFF
    static constexpr uint8_t SetMuxRatio = 0xA8U;         ///< Sets the multiplex ratio, i.e. the number of rows in the display
    static constexpr uint8_t DisplayOn = 0xAFU;
    static constexpr uint8_t DisplayOff = 0xAEU;
    static constexpr uint8_t SetCOMScanUp = 0xC0U;          ///< Sets the lower nibble of the column address
    static constexpr uint8_t SetCOMScanDown = 0xC8U;        ///< Sets the higher nibble of the column address
    static constexpr uint8_t SetDisplayOffset = 0xD3U;      ///< Sets the display offset, i.e. the number of rows to skip at the top of the display
    static constexpr uint8_t SetDisplayClock = 0xD5U;       ///< Sets the display clock divide ratio and oscillator frequency
    static constexpr uint8_t SetPreChargePeriod = 0xD9U;    ///< Sets the pre-charge period for the display
    static constexpr uint8_t SetCOMHwConfig = 0xDAU;        ///< Sets the COM hardware configuration, i.e. the number of COM lines and their order
    static constexpr uint8_t SetVCOMH = 0xDBU;              ///< Sets the VCOMH deselect level, i.e. the voltage level for the VCOM pin
    static constexpr uint8_t NoOp = 0xE3U;
};

static constexpr std::uint8_t DefaultAddress{0x3C};      ///< Default I2C address for the SSD1306 display
static constexpr std::uint8_t SecondaryAddress{0x3D};    ///< Secondary I2C address for the SSD1306 display

/// @brief The SSD1306 Image class represents a monochrome bitmap image.
/// @tparam W The width of the image in pixels.
/// @tparam H The height of the image in pixels.
template <size_t W, size_t H>
class Image {
public:
    constexpr static std::size_t width{W};     // in pixels
    constexpr static std::size_t height{H};    // in pixels
    constexpr static std::size_t height_per_byte{8u};
    constexpr static std::size_t pages{height / height_per_byte};

    /// @brief Sets a pixel in the image.
    /// @param col The column data to set the pixel to (0-255).
    /// @param x The x-coordinate of the pixel.
    /// @param page The page in which the pixel is located (0 to pages-1).
    /// @return True if the pixel was set successfully, false otherwise.
    bool set(uint8_t col, uint8_t x, uint8_t page) {
        if (x < width and page < pages) {
            data[page][x] = col;
            return true;
        } else {
            return false;
        }
    }

    bool set(bool value, uint8_t x, uint8_t y) {
        if (x < width and y < height) {
            _set(value, x, y);
            return true;
        } else {
            return false;
        }
    }

    bool get(uint8_t x, uint8_t y) const {
        if (x < width and y < height) {
            uint8_t row = y >> 3;
            uint8_t bit = y & 0x7;
            return ((data[row][x] & (1 << bit)) == (1 << bit));
        } else {
            return false;
        }
    }

    bool clear(uint8_t x, uint8_t y, uint8_t dx, uint8_t dy) {
        if (((y + dy) < y) or ((x + dx) < x)) {
            return false;
        }
        for (uint8_t j = y; j < (y + dy); j++) {
            for (uint8_t i = x; i < (x + dx); i++) {
                _set(false, i, j);
            }
        }
        return true;
    }

    void clear(void) { memory::fill(&data[0][0], 0, sizeof(data)); }

    void pattern(void) {
        for (uint8_t p = 0; p < pages; p++) {
            for (uint8_t x = 0; x < width; x++) {
                data[p][x] = x + p;
            }
        }
    }

#if defined(UNITTEST)
    /// @brief Dumps the image data to stdout for debugging purposes.
    /// @details This function prints the raw data of the image in hexadecimal format, one page per line.
    ///          Each byte represents a column of pixels in the corresponding page.
    void dump(void) {
        for (uint8_t p = 0; p < pages; p++) {
            for (uint8_t x = 0; x < width; x++) {
                printf("%02x", data[p][x]);
            }
            printf("\n");
        }
        fflush(stdout);
    }

    void render(void) {
        for (uint8_t y = 0; y < height; y++) {
            for (uint8_t x = 0; x < width; x++) {
                printf("%c", get(x, y) ? 'X' : ' ');
            }
            printf("\n\r");
        }
        printf("---128x32--- (set terminal to 128x34)\r\n");
    }
#endif
    constexpr uint8_t const* GetData(void) const { return &data[0][0]; }
    constexpr std::size_t GetSize(void) const { return sizeof(data); }

protected:
    /// @brief The data buffer for the image.
    uint8_t data[height / height_per_byte][width];

    /// @brief Sets a pixel in the image at the specified coordinates.
    /// @param value The value to set the pixel to (true for ON, false for OFF).
    /// @param x The x-coordinate of the pixel.
    /// @param y The y-coordinate of the pixel.
    /// @note The y-coordinate is divided by 8 to determine the page, and the
    ///       bit within the page is determined by the remainder of y divided by 8.
    /// @details This function modifies the data buffer directly to set or clear the pixel.
    inline void _set(bool value, uint8_t x, uint8_t y) {
        uint8_t row = y >> 3;
        uint8_t bit = y & 0x7;
        if (value) {
            data[row][x] |= (1 << bit);
        } else {
            data[row][x] &= ~(1 << bit);
        }
    }
};

using Image128x32 = Image<128, 32>;

template <size_t W, size_t H>
class Screen {
public:
    constexpr static uint8_t width{W / sizeof(symbol)};
    constexpr static uint8_t height{H};

    Screen(Image<W, H>& im)
        : image{im} {}

    bool write(symbol const sym, uint8_t x, uint8_t y) {
        if (x < width and y < height) {
            // memcpy(symbols[x][y], sym, sizeof(symbol));
            for (uint8_t s = 0; s < sizeof(symbol); s++) {
                symbols[y][x][s] = sym[s];
            }
            return true;
        } else {
            return false;
        }
    }

    void clear(void) {
        memory::fill(&symbols[0][0][0], 0, sizeof(symbols));
        image.clear();
    }

    void checkerboard(void) {
        for (uint8_t v = 0; v < height; v++) {
            for (uint8_t u = 0; u < width; u++) {
                if ((u + v) & 1) {
                    write(ssd1306::symbols::block, u, v);
                } else {
                    write(ssd1306::symbols::space, u, v);
                }
            }
        }
    }

    void pattern(void) {
        for (uint8_t y = 0; y < height; y++) {
            for (uint8_t x = 0; x < width; x++) {
                for (uint8_t s = 0; s < sizeof(symbol); s++) {
                    symbols[y][x][s] = x + y + s;
                }
            }
        }
    }

#if defined(UNITTEST)
    void dump(void) {
        for (uint8_t y = 0; y < height; y++) {
            for (uint8_t x = 0; x < width; x++) {
                for (uint8_t s = 0; s < sizeof(symbol); s++) {
                    printf("%02x", symbols[y][x][s]);
                }
                printf(" ");
            }
            printf("\n");
        }
        fflush(stdout);
    }
#endif

    void render(void) {
        for (uint8_t y = 0; y < height; y++) {
            for (uint8_t x = 0; x < width; x++) {
                for (uint8_t s = 0; s < sizeof(symbol); s++) {
                    // screen y == page
                    uint8_t col = uint8_t(sizeof(symbol) * x) + s;
                    (void)image.set(symbols[y][x][s], col, y);
                }
            }
        }
    }

protected:
    Image<W, H>& image;
    symbol symbols[height][width];
};

using Screen128x32 = Screen<128, 32>;

}    // namespace ssd1306

#endif    // SDD1306_HPP
