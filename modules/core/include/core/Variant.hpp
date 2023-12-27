#pragma once

#include <cstdint>
#include <cstddef>
// #include <variant>

#include "core/Folds.hpp"

namespace core {

struct false_type {
    static constexpr bool value = false;
    bool operator()() const { return value; }
    explicit operator bool() const { return value; }
};

struct true_type {
    static constexpr bool value = true;
    bool operator()() const { return value; }
    explicit operator bool() const { return value; }
};

template <typename T, typename U>
struct same_type : false_type {};

template <typename T>
struct same_type<T, T> : true_type {};

template <typename... TYPES>
struct type_list {};

template <typename T, typename LIST>
struct type_index_mapper {
    // static_assert(sizeof...(TYPES), "Type not found!");
};

template <typename T, typename... TYPES>
struct type_index_mapper<T, type_list<T, TYPES...>> {
    static constexpr size_t value = 0;
};

template <typename T, typename U, typename... TYPES>
struct type_index_mapper<T, type_list<U, TYPES...>> {
    static constexpr size_t value = 1 + type_index_mapper<T, type_list<TYPES...>>::value;
};

/// A type safe union type that can hold any of the types specified in the template parameter pack.
/// @tparam ...TYPES
template <typename... TYPES>
class Variant {
    static constexpr size_t count_ = sizeof...(TYPES);    ///< The number of types in the variant
    static_assert(count_ > 0, "variant must have at least one alternative");
    static constexpr size_t max_size_ = core::max(sizeof(TYPES)...);
    static constexpr size_t max_align_ = core::max(alignof(TYPES)...);

    alignas(max_align_) std::uint8_t data[max_size_];
    size_t type_index_;

public:
    /// No defalt construction allowed
    Variant() = delete;

    /// Constructs a variant with the specificed type in the parameter pack
    /// @tparam TYPE
    template <typename TYPE>
    Variant(TYPE value)
        : type_index_{type_index_mapper<TYPE, type_list<TYPES...>>::value} {
        new (data) TYPE(value);
    }

    /// Returns the number of types in the variant
    constexpr auto count() const { return count_; }
    /// Returns the size of the variant storage (does not count the tag)
    constexpr auto storage_size() const { return max_size_; }
    /// Returns the alignment of the variant storage
    constexpr auto storage_alignment() const { return max_align_; }
    /// Returns true if the type was defined as one part of the initial variant
    template <typename TYPE>
    constexpr bool could() const {
        return any(same_type<TYPE, TYPES>::value...);
    }

    template <typename TYPE>
    constexpr bool isa() const {
        return could<TYPE>() and (type_index_ == type_index_mapper<TYPE, type_list<TYPES...>>::value);
    }

    ///
};

}    // namespace core