#ifndef CORE_VARIANT_HPP
#define CORE_VARIANT_HPP

#include <cstdint>
#include <cstddef>
// #include <variant>

#include "core/Folds.hpp"

namespace core {

/// @brief A type to embody false-ness
struct false_type {
    /// @brief The value of a false type
    static constexpr bool value = false;
    /// @brief Returns the value of the type
    bool operator()() const { return value; }
    /// @brief Returns the value of the type
    explicit operator bool() const { return value; }
};

/// @brief A type to embody truth-i-ness
struct true_type {
    /// @brief The value of a true type
    static constexpr bool value = true;
    /// @brief Returns the value of the type
    bool operator()() const { return value; }
    /// @brief Returns the value of the type
    explicit operator bool() const { return value; }
};

/// When selected, shows the compiler has decided the types are not the same.
/// @tparam T First type
/// @tparam U Second type
template <typename T, typename U>
struct same_type : false_type {};

/// When selected, shows the compiler has decided the types are the same.
/// @tparam T The type
template <typename T>
struct same_type<T, T> : true_type {};

/// When selected, shows that the type information is empty
/// @tparam ...TYPES
template <typename... TYPES>
struct type_list {};

template <typename T, typename LIST>
struct type_index_mapper {
    // static_assert(sizeof...(TYPES), "Type not found!");
};

/// Base definition for mapping a number to a type
/// @tparam T The type to map
/// @tparam ...TYPES
template <typename T, typename... TYPES>
struct type_index_mapper<T, type_list<T, TYPES...>> {
    /// @brief The zero value
    static constexpr size_t value = 0;
};

/// Extended definition to define how to map a value to a type.
/// @tparam T The type to map
/// @tparam U The next type
/// @tparam ...TYPES The set of all types
template <typename T, typename U, typename... TYPES>
struct type_index_mapper<T, type_list<U, TYPES...>> {
    /// @brief The value of the type index
    static constexpr size_t value = 1 + type_index_mapper<T, type_list<TYPES...>>::value;
};

/// A type safe "union" type that can hold any of the types specified in the template parameter pack.
/// @tparam ...TYPES
template <typename... TYPES>
class Variant {
    static constexpr size_t count_ = sizeof...(TYPES);    ///< The number of types in the variant
    static_assert(count_ > 0, "variant must have at least one alternative");
    static constexpr size_t max_size_ = core::max(sizeof(TYPES)...);
    static constexpr size_t max_align_ = core::max(alignof(TYPES)...);

    alignas(max_align_) std::uint8_t data[max_size_];    ///< Holds the storage for the variant
    size_t type_index_;                                  ///< The index of the type in the variant

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
    /// Returns true if the type could be TYPE and the type index is the same as the type index of the variant, false otherwise.
    /// @tparam TYPE The type to check against
    /// @return Return true or false (no exceptions)
    template <typename TYPE>
    constexpr bool isa() const {
        return could<TYPE>() and (type_index_ == type_index_mapper<TYPE, type_list<TYPES...>>::value);
    }
};

}    // namespace core

#endif    // CORE_VARIANT_HPP