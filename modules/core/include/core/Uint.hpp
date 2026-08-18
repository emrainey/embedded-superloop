#ifndef CORE_UINT_HPP
#define CORE_UINT_HPP

#include <cstdint>
#include <type_traits>

namespace core {

template <typename STORAGE_TYPE, size_t NUM_BITS>
struct Uint_ {
    static_assert(NUM_BITS > 0, "Must be larger than zero");
    static_assert(sizeof(STORAGE_TYPE) * 8U >= NUM_BITS, "Must be less than or equal to storage type number of bits");
    static_assert(std::is_unsigned_v<STORAGE_TYPE>, "Storage type must be unsigned");

    using StorageType = STORAGE_TYPE;

    constexpr Uint_()
        : value{0U} {}
    constexpr Uint_(StorageType l)
        : value{static_cast<StorageType>(l & ((static_cast<StorageType>(1U) << NUM_BITS) - 1U))} {}
    constexpr Uint_(Uint_ const&) = default;
    constexpr Uint_(Uint_&&) = default;
    constexpr Uint_& operator=(Uint_ const& other) {
        value = other.value;
        return *this;
    }
    constexpr Uint_& operator=(Uint_&& other) {
        value = other.value;
        return *this;
    }
    explicit constexpr operator StorageType() const { return value; }
    constexpr Uint_& operator=(StorageType other) {
        value = other & ((static_cast<StorageType>(1U) << NUM_BITS) - 1U);    // Mask the value to fit in the number of bits
        return *this;
    }
    StorageType value : NUM_BITS;                         ///< The value bits
    StorageType : sizeof(StorageType) * 8U - NUM_BITS;    ///< The upper bits are unnamed and unused
};

template <size_t NUM_BITS>
using uint8_ = Uint_<std::uint8_t, NUM_BITS>;

template <size_t NUM_BITS>
using uint16_ = Uint_<std::uint16_t, NUM_BITS>;

template <size_t NUM_BITS>
using uint32_ = Uint_<std::uint32_t, NUM_BITS>;

template <size_t NUM_BITS>
using uint64_ = Uint_<std::uint64_t, NUM_BITS>;

// === Arithmetic Operators ===

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr Uint_<STORAGE_TYPE, NUM_BITS> operator+(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return Uint_<STORAGE_TYPE, NUM_BITS>{static_cast<STORAGE_TYPE>(lhs) + static_cast<STORAGE_TYPE>(rhs)};
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr Uint_<STORAGE_TYPE, NUM_BITS> operator-(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return Uint_<STORAGE_TYPE, NUM_BITS>{static_cast<STORAGE_TYPE>(lhs) - static_cast<STORAGE_TYPE>(rhs)};
}

// === Comparison Operators ===

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value < rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value < rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs < rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value <= rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value <= rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator<=(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs <= rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value > rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value > rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs > rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value >= rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value >= rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator>=(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs >= rhs.value;
}

// === Equality Operators ===

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator==(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value == rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator==(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value == rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator==(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs == rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator!=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs.value != rhs.value;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator!=(Uint_<STORAGE_TYPE, NUM_BITS> const& lhs, STORAGE_TYPE const& rhs) {
    return lhs.value != rhs;
}

template <typename STORAGE_TYPE, size_t NUM_BITS>
constexpr bool operator!=(STORAGE_TYPE const& lhs, Uint_<STORAGE_TYPE, NUM_BITS> const& rhs) {
    return lhs != rhs.value;
}

}    // namespace core

#endif
