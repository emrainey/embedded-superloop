#ifndef W25Q16BV_HPP
#define W25Q16BV_HPP

#include <cstdint>
#include <cstddef>

namespace w25q16bv {

static constexpr uint8_t ManufacturerID = 0xEFU;    ///< Manufacturer ID (for Winbond)
static constexpr uint8_t DeviceID = 0x14U;          ///< Device ID (for W25Q16BV)
static constexpr uint16_t JEDEC_ID = 0x4015U;       ///< Device ID via JEDEC (for W25Q16BV)

/// @brief The Winbond Flash Driver over SPI Instructions
enum class Instruction : std::uint8_t {
    None = 0x00U,    ///< No instruction
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    WriteEnable = 0x06U,              ///< Write Enable
    VolatileSRWriteEnable = 0x50U,    ///< Volatile Status Register Write Enable
    WriteDisable = 0x04U,             ///< Write Disable
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    ReleasePowerDown = 0xABU,    ///< Release Power Down
    Manufacturer = 0x90U,        ///< Manufacturer ID
    GetJedecId = 0x9FU,          ///< JEDEC ID
    ReadUniqueId = 0x4BU,        ///< Read Unique ID
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    ReadData = 0x03U,        ///< Read Data
    FastReadData = 0x0BU,    ///< Fast Read Data
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    PageProgram = 0x02U,    ///< Page Program
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    SectorErase = 0x20U,      ///< Sector Erase
    BlockErase32k = 0x52U,    ///< Block Erase 32k
    BlockErase64k = 0xD8U,    ///< Block Erase 64k
    ChipErase = 0xC7U,        ///< Chip Erase
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    ReadStatusRegister1 = 0x05U,     ///< Read Status Register 1
    ReadStatusRegister2 = 0x35U,     ///< Read Status Register 2
    ReadStatusRegister3 = 0x15U,     ///< Read Status Register 3
    WriteStatusRegister1 = 0x01U,    ///< Write Status Register 1
    WriteStatusRegister2 = 0x31U,    ///< Write Status Register 2
    WriteStatusRegister3 = 0x11U,    ///< Write Status Register 3
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    ReadSerialFlashDiscoverableParameterRegister = 0x5AU,    ///< Read Serial Flash Discoverable Parameter Register
    EraseSecurityRegister = 0x44U,                           ///< Erase Security Register
    ProgramSecurityRegister = 0x42U,                         ///< Program Security Register
    ReadSecurityRegister = 0x48U,                            ///< Read Security Register
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    GlobalBlockLock = 0x7EU,          ///< Global Block Lock
    GlobalBlockUnlock = 0x98U,        ///< Global Block Unlock
    ReadBlockLock = 0x3BU,            ///< Read Block Lock
    IndividualBlockLock = 0x36U,      ///< Individual Block Lock
    IndividualBlockUnlock = 0x39U,    ///< Individual Block Unlock
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    EraseProgramSuspend = 0x75U,    ///< Erase/Program Suspend
    EraseProgramResume = 0x7AU,     ///< Erase/Program Resume
    PowerDown = 0xB9U,              ///< Power Down
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    EnableReset = 0x66U,    ///< Enable Reset
    ResetDevice = 0x99U,    ///< Reset Device
};

/// @brief Address is 3 bytes, MSB order
/// @details The address is used to identify the location in the memory
struct Address {
    using Type = uint32_t;    ///< Type is a 24-bit unsigned integer but stored in a 32-bit unsigned integer
    uint8_t address[3U];      ///< Address is 3 bytes, MSB order

    /// @brief Parameter constructor
    /// @param addr The address to be assigned
    /// @code Address addr{0x123456U}; @endcode
    constexpr explicit Address(Type addr)
        : address{
              static_cast<uint8_t>((addr >> 16U) & 0xFFU), static_cast<uint8_t>((addr >> 8U) & 0xFFU), static_cast<uint8_t>((addr >> 0U) & 0xFFU)
          } {}

    /// @brief Used when assigning the address struct to a Type type
    /// @code Type addr = Address{0x12, 0x34, 0x56}; @endcode
    constexpr explicit operator Type() const {
        return (static_cast<Type>(address[0U]) << 16U) | (static_cast<Type>(address[1U]) << 8U) | address[2U];
    }

    /// @brief Used when assigning a Type value to the address struct
    /// @code Address addr = 0x123456U; @endcode
    constexpr Address& operator=(Type const addr) {
        address[0U] = static_cast<uint8_t>((addr >> 16U) & 0xFFU);
        address[1U] = static_cast<uint8_t>((addr >> 8U) & 0xFFU);
        address[2U] = static_cast<uint8_t>((addr >> 0U) & 0xFFU);
        return *this;
    }
};

struct Empty {};

template <size_t N>
struct Data : Address {
    uint8_t data[N];
};

template <size_t N>
struct Dummy {
    uint8_t dummy[N];
};

template <size_t N>
struct ID : Dummy<N> {
    uint8_t id;
};

struct Format {
    Instruction instruction;
    union {
        Empty empty;
        ID<3U> id;
        Address address_only;    ///< Used with Reading Data or Erasing
        Data<1U> one_data;
        Data<2U> two_data;
        uint8_t raw[6U];
    } fields;
};
static_assert(sizeof(Format) == 7U, "Format is not 7 bytes");

struct Status {
    union {
        struct {
            uint16_t busy                 : 1;    ///< Busy bit
            uint16_t write_enable_latch   : 1;    ///< Write Enable Latch bit
            uint16_t block_protect        : 3;    ///< Block Protect bits
            uint16_t top_bottom           : 1;    ///< Status Register 2 bit
            uint16_t sector_protect       : 1;    ///< Sector Protect bit
            uint16_t status_protect       : 2;    ///< Status Register Protect bit
            uint16_t quad_enable          : 1;    ///< Reserved
            uint16_t                      : 5;    ///< Reserved
            uint16_t erase_suspend_status : 1;    ///< Reserved
        } bits;
        uint8_t u08[2];     ///< Raw bytes
        uint16_t u16[1];    ///< Raw word
    } fields;
};
static_assert(sizeof(Status) == 2U, "Status is 16 bit");

}    // namespace w25q16bv

#endif    // W25Q16BV_HPP