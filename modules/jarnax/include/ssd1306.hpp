#ifndef SDD1306_HPP
#define SDD1306_HPP

#include <cstdint>
#include <cstddef>
#include <limits>
#include "memory.hpp"

namespace ssd1306 {

using symbol = uint8_t[8];
static_assert(sizeof(symbol) == 8u, "Must be 8 bytes in size");

/**
    Symbols are constructed as a set of 8 bytes with each byte having 8 bits

   0 1 2 3 4 5 6 7 (bytes)
  +-+-+-+-+-+-+-+-+
0 | | | | | | | | | (0x1)
  +-+-+-+-+-+-+-+-+
1 | | |X|X|X|X| | | (0x2)
  +-+-+-+-+-+-+-+-+
2 | |X| | | | |X| | (0x4)
  +-+-+-+-+-+-+-+-+
3 | | | | | |X| | | (0x8)
  +-+-+-+-+-+-+-+-+
4 | | | |X|X| | | | (0x10)
  +-+-+-+-+-+-+-+-+
5 | | |X| | | | | | (0x20)
  +-+-+-+-+-+-+-+-+
6 | |X|X|X|X|X|X| | (0x40)
  +-+-+-+-+-+-+-+-+
7 | | | | | | | | | (0x80)
  +-+-+-+-+-+-+-+-+
  This is the 2
*/
namespace symbols {
symbol block = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
symbol space = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
symbol box = {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x7E, 0x00};
symbol hash = {0x00, 0x24, 0x7E, 0x24, 0x24, 0x7E, 0x24, 0x00};

symbol alphabet[26] = {
    {0x00, 0x78, 0x14, 0x12, 0x12, 0x14, 0x78, 0x00},    // A
    {0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00},    // B
    {0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x24, 0x00},    // C
    {0x00, 0x7E, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00},    // D
    {0x00, 0x7E, 0x4A, 0x4A, 0x4A, 0x4A, 0x4A, 0x00},    // E
    {0x00, 0x7E, 0x0A, 0x0A, 0x0A, 0x0A, 0x0A, 0x00},    // F
    {0x00, 0x3C, 0x42, 0x42, 0x42, 0x52, 0x34, 0x00},    // G
    {0x00, 0x7E, 0x08, 0x08, 0x08, 0x08, 0x7E, 0x00},    // H
    {0x00, 0x42, 0x42, 0x42, 0x7E, 0x42, 0x42, 0x00},    // I
    {0x00, 0x22, 0x42, 0x42, 0x42, 0x42, 0x3E, 0x00},    // J
    {0x00, 0x7E, 0x08, 0x08, 0x08, 0x34, 0x42, 0x00},    // K
    {0x00, 0x7E, 0x40, 0x40, 0x40, 0x40, 0x40, 0x00},    // L
    {0x00, 0x7E, 0x04, 0x08, 0x08, 0x04, 0x7E, 0x00},    // M
    {0x00, 0x7E, 0x04, 0x08, 0x10, 0x20, 0x7E, 0x00},    // N
    {0x00, 0x3C, 0x42, 0x42, 0x42, 0x42, 0x3C, 0x00},    // O
    {0x00, 0x7E, 0x0A, 0x0A, 0x0A, 0x0A, 0x04, 0x00},    // P
    {0x00, 0x3C, 0x42, 0x42, 0xE2, 0x42, 0x3C, 0x00},    // Q
    {0x00, 0x7E, 0x0A, 0x0A, 0x0A, 0x0A, 0x74, 0x00},    // R
    {0x00, 0x24, 0x42, 0x4A, 0x52, 0x42, 0x24, 0x00},    // S
    {0x00, 0x02, 0x02, 0x02, 0x7E, 0x02, 0x02, 0x00},    // T
    {0x00, 0x3E, 0x40, 0x40, 0x40, 0x40, 0x3E, 0x00},    // U
    {0x00, 0x06, 0x38, 0x40, 0x40, 0x38, 0x06, 0x00},    // V
    {0x00, 0x3E, 0x40, 0x20, 0x20, 0x40, 0x3E, 0x00},    // W
    {0x00, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x00},    // X
    {0x00, 0x02, 0x04, 0x78, 0x78, 0x04, 0x02, 0x00},    // Y
    {0x00, 0x42, 0x62, 0x52, 0x4A, 0x46, 0x42, 0x00},    // Z
};

symbol numerals[10] = {
    {0x00, 0x3C, 0x62, 0x52, 0x4A, 0x46, 0x3C, 0x00},    // 0
    {0x00, 0x40, 0x48, 0x44, 0x7E, 0x40, 0x40, 0x00},    // 1
    {0x00, 0x44, 0x62, 0x52, 0x52, 0x4A, 0x44, 0x00},    // 2
    {0x00, 0x22, 0x42, 0x4A, 0x4A, 0x4E, 0x32, 0x00},    // 3
    {0x00, 0x10, 0x18, 0x14, 0x12, 0x7E, 0x10, 0x00},    // 4
    {0x00, 0x5E, 0x52, 0x52, 0x52, 0x52, 0x32, 0x00},    // 5
    {0x00, 0x3C, 0x52, 0x52, 0x52, 0x52, 0x24, 0x00},    // 6
    {0x00, 0x42, 0x22, 0x12, 0x0A, 0x06, 0x02, 0x00},    // 7
    {0x00, 0x34, 0x4A, 0x4A, 0x4A, 0x4A, 0x34, 0x00},    // 8
    {0x00, 0x24, 0x4A, 0x4A, 0x4A, 0x4A, 0x3C, 0x00},    // 9
};
}    // namespace symbols

struct Control {
    Control()
        : value{0} {}    ///< Default constructor initializes the control byte to 0
    Control(uint8_t Co, uint8_t DC)
        : value{0U} {
        bits.zero = 0;                               ///< Must be 0
        bits.next_is_data_not_command = DC & 0b1;    ///< 0 for command, 1 for data
        bits.continuation = Co & 0b1;                ///< Following bytes are all data (0) or not (1)
    }
    union {
        struct {
            uint8_t zero                     : 6;    ///< Must be 0
            uint8_t next_is_data_not_command : 1;    ///< 0 for command, 1 for data
            uint8_t continuation             : 1;    ///< Following bytes are all data (0) or not (1)
        } bits;
        uint8_t value;    ///< The raw value of the control byte
    };
};

enum class Command : std::uint8_t {
    // Lower Column Addresses = 0x00 to 0x0F
    // Higher Column Addresses = 0x10 to 0x1F
    MemoryAddressingMode = 0x20,
    SetColumnAddress = 0x21,
    SetPageAddress = 0x22,
    DeactivateScroll = 0x2E,
    ActivateScroll = 0x2F,
    // Set Display Start Line = 0x40 to 0x7F
    DisplayStartLine = 0x40,
    SetStartLine = 0x40,
    ContrastControl = 0x81,
    Resume = 0xA4,         ///< Resumes displaying whatever is in the display memory
    AllPixelsOn = 0xA5,    ///< Sets all pixels to ON, regardless of the display memory
    InverseDisplay = 0xA7,
    DisplayOn = 0xAF,
    DisplayOff = 0xAE,
    NoOp = 0xE3,
};

static constexpr std::uint8_t DefaultAddress{0x3C};      ///< Default I2C address for the SSD1306 display
static constexpr std::uint8_t SecondaryAddress{0x3D};    ///< Secondary I2C address for the SSD1306 display

template <size_t W, size_t H>
class Image {
public:
    constexpr static std::size_t width{W};     // in pixels
    constexpr static std::size_t height{H};    // in pixels
    constexpr static std::size_t height_per_byte{8u};
    constexpr static std::size_t pages{height / height_per_byte};

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

#if defined(UNIT_TEST)
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

protected:
    uint8_t data[height / height_per_byte][width];

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

    bool write(symbol sym, uint8_t x, uint8_t y) {
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

#if defined(UNIT_TEST)
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
                    uint8_t col = (sizeof(symbol) * x) + s;
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
