#ifndef CORE_SPLIT_HPP_
#define CORE_SPLIT_HPP_

#include "iso.hpp"

namespace core {

/// The Split Template
template <typename STORAGE_TYPE, size_t NUM_BITS>
struct Split final {
    constexpr static size_t StorageNumberOfBits = sizeof(STORAGE_TYPE) * 8U;
    constexpr static size_t SplitNumberOfBits = NUM_BITS;
    static_assert(SplitNumberOfBits > 0, "Must be larger than zero");
    static_assert(StorageNumberOfBits > SplitNumberOfBits, "Must be less than storage type number of bits");

    /// The Storage type of the Split
    using StorageType = STORAGE_TYPE;

    /// The structure holding the lower and upper parts
    struct Fields final {
        StorageType lower : SplitNumberOfBits;
        StorageType upper : StorageNumberOfBits - SplitNumberOfBits;
    };

    /// The union of the whole and parts
    union {
        Fields parts;
        StorageType whole;    //!< Used to operate on the whole storage
    };
    static_assert(sizeof(Fields) == sizeof(StorageType), "Must be the same");
};

}    // namespace core

#endif    // CORE_SPLIT_HPP_
