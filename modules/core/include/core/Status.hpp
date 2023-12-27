
#include <cstdint>
#include <core/EnumType.hpp>

namespace core {

///
using CodeType = std::uint8_t;

enum class Argument : CodeType {
    None = 0U,
    InvalidValue = 1U,      ///< Used when a specific value is required but not provided
    InvalidSize = 2U,       ///< Used when a size field is incorrect
    InvalidPointer = 3U,    ///< Used when a pointer is invalid
};

using ArgumentType = EnumType<Argument>;

enum class Memory : CodeType {
    None = 0U,
    InvalidAlignment = 1U,    ///< Used when an alignment is invalid
    InvalidOffset = 2U,       ///< Used when an offset is invalid
    InvalidPointer = 4U,      ///< Used when a pointer is invalid
};

using MemoryType = EnumType<Memory>;

using EnumTypeVariant = Variant<ArgumentType, MemoryType>;

// class Status : public EnumType<Argument> {}    // namespace core

}    // namespace core
