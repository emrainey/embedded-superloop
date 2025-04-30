#ifndef WINBOND_HPP
#define WINBOND_HPP

#include <cstdint>
#include <cstddef>

namespace winbond {

enum class Instruction : std::uint8_t {
    ManufacturerID = 0xEFU,    ///< Read Manufacturer and Device ID
    DeviceID1 = 0xABU,         ///< Read Device ID 1
    DeviceID2 = 0x90U,         ///< Read Device ID 2
    DeviceID3 = 0x92U,         ///< Read Device ID 3
    DeviceID4 = 0x94U,         ///< Read Device ID 4
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    WriteEnable = 0x06U,              ///< Write Enable
    VolatileSRWriteEnable = 0x50U,    ///< Volatile Status Register Write Enable
    WriteDisable = 0x04U,             ///< Write Disable
    // --==--==--==--==--==--==--==--==--==--==--==--==--
    ReleasePowerDown = 0xABU,    ///< Release Power Down
    Manufacturer = 0x90U,        ///< Manufacturer ID
    JEDED_ID = 0x9FU,            ///< JEDEC ID
    ReadUniqueID = 0x4BU,        ///< Read Unique ID
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

enum class MetadataByte : char {
    Zero = '0',
    NotUsed = 'n',
    Dummy = 'y',
    Address = 'a',
    Data = 'd',
    Lock = 'l',
    Status = 's',
};

struct Address {
    uint8_t address[3U];

    inline uint32_t GetAddress() const {
        return (static_cast<uint32_t>(address[0U]) << 16U) | (static_cast<uint32_t>(address[1U]) << 8U) | address[2U];
    }
    inline void SetAddress(uint32_t addr) {
        address[0U] = static_cast<uint8_t>((addr >> 16U) & 0xFFU);
        address[1U] = static_cast<uint8_t>((addr >> 8U) & 0xFFU);
        address[2U] = static_cast<uint8_t>(addr & 0xFFU);
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
        Address address_only;
        Data<1U> one_data;
        Data<2U> two_data;
        uint8_t raw[6U];
    } fields;
};
static_assert(sizeof(Format) == 7U, "Format is not 7 bytes");

}    // namespace winbond

#endif    // WINBOND_HPP