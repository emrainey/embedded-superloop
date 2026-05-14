#ifndef CORE_SPLIT_HPP_
#define CORE_SPLIT_HPP_

/// @file
/// Integer Bit Field Splitter

#include "iso.hpp"

namespace core {

/// The Split Template
template <typename STORAGE_TYPE, size_t NUM_BITS>
struct Split final {
    /// @brief The number of bits in the sotrage
    constexpr static size_t StorageNumberOfBits = sizeof(STORAGE_TYPE) * 8U;
    /// @brief The number of bits in the split
    constexpr static size_t SplitNumberOfBits = NUM_BITS;

    static_assert(SplitNumberOfBits > 0, "Must be larger than zero");
    static_assert(StorageNumberOfBits > SplitNumberOfBits, "Must be less than storage type number of bits");

    /// The Storage type of the Split
    using StorageType = STORAGE_TYPE;

    Split() = default;
    Split(StorageType w)
        : whole{w} {}
    Split(StorageType lower, StorageType upper)
        : parts{lower, upper} {}
    Split(Split const&) = default;
    Split(Split&&) = default;
    Split& operator=(Split const& other) {
        whole = other.whole;
        return *this;
    }
    Split& operator=(Split&& other) {
        whole = other.whole;
        return *this;
    }

    /// The structure holding the lower and upper parts
    struct Fields final {
        StorageType lower : SplitNumberOfBits;                          ///< The lower bits below the split
        StorageType upper : StorageNumberOfBits - SplitNumberOfBits;    ///< The upper bits above the split
    };

    /// The union of the whole and parts
    union {
        Fields parts;         ///< The parts of the split
        StorageType whole;    ///< Used to operate on the whole storage
    };
    static_assert(sizeof(Fields) == sizeof(StorageType), "Must be the same");
};

}    // namespace core

#endif    // CORE_SPLIT_HPP_
