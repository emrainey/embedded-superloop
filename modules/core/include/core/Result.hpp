#ifndef CORE_RESULT_HPP
#define CORE_RESULT_HPP

#include <cstdint>
#include <core/EnumType.hpp>

namespace core {

/// the Code Type is used to represent the type of codes in the Arguments and Memory types
using CodeType = std::uint8_t;

/// @brief The enumeration of argument problems
enum class Argument : CodeType {
    None = 0U,
    InvalidValue = 1U,      ///< Used when a specific value is required but not provided
    InvalidSize = 2U,       ///< Used when a size field is incorrect
    InvalidPointer = 3U,    ///< Used when a pointer is invalid
};

/// @brief The type of the argument as an enumerable type
using ArgumentType = EnumType<Argument>;

/// @brief The enumeration of the memory problems
enum class Memory : CodeType {
    None = 0U,
    InvalidAlignment = 1U,    ///< Used when an alignment is invalid
    InvalidOffset = 2U,       ///< Used when an offset is invalid
    InvalidPointer = 4U,      ///< Used when a pointer is invalid
};

/// @brief The type of the memory enumerable type
using MemoryType = EnumType<Memory>;

/// @brief The simple type of an EnumTypeVariant
using EnumTypeVariant = Variant<ArgumentType, MemoryType>;

// class Result : public EnumType<Argument> {}    // namespace core

}    // namespace core

#endif    // CORE_RESULT_HPP
