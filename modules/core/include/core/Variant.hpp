#ifndef CORE_VARIANT_HPP
#define CORE_VARIANT_HPP

/// @file
/// Type-Safe Union (Variant) Implementation

#include <cstddef>
#include <cstdint>
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

/// SFINAE helper for conditional compilation
/// @tparam B Boolean condition
/// @tparam T Type to enable if condition is true
template <bool B, typename T = void>
struct enable_if {};

/// Specialization when condition is true
/// @tparam T Type to enable
template <typename T>
struct enable_if<true, T> {
    using type = T;
};

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

/// Helper to check if a type is in the variant's type list
/// @tparam T The type to check
/// @tparam ...TYPES The variant's type list
template <typename T, typename... TYPES>
struct is_variant_alternative : false_type {};

/// Specialization when the type is found in the variant's type list
/// @tparam T The type to check
/// @tparam ...TYPES The variant's type list
template <typename T, typename... TYPES>
struct is_variant_alternative<T, type_list<TYPES...>> {
    static constexpr bool value = any(same_type<T, TYPES>::value...);
};

/// A type safe "union" type that can hold any of the types specified in the template parameter pack.
/// @tparam ...TYPES
template <typename... TYPES>
class Variant {
    static constexpr size_t count_ = sizeof...(TYPES);    ///< The number of types in the variant
    static_assert(count_ > 0, "variant must have at least one alternative");
    static constexpr size_t max_size_ = core::max(sizeof(TYPES)...);
    static constexpr size_t max_align_ = core::max(alignof(TYPES)...);

    alignas(max_align_) std::uint8_t data_[max_size_];    ///< Holds the storage for the variant
    size_t type_index_;                                   ///< The index of the type in the variant

    /// Helper to destroy the active type
    template <size_t INDEX = 0>
    void destroy_active() {
        if constexpr (INDEX < count_) {
            if (type_index_ == INDEX) {
                using CurrentType = typename nth_type<INDEX, TYPES...>::type;
                reinterpret_cast<CurrentType*>(data_)->~CurrentType();
            } else {
                destroy_active<INDEX + 1>();
            }
        }
    }

    /// Helper to get the nth type from parameter pack
    template <size_t N, typename First, typename... Rest>
    struct nth_type {
        using type = typename nth_type<N - 1, Rest...>::type;
    };

    template <typename First, typename... Rest>
    struct nth_type<0, First, Rest...> {
        using type = First;
    };

public:
    /// No default construction allowed
    Variant() = delete;

    /// Constructs a variant with the specified type from the parameter pack
    /// Only enabled if TYPE is one of TYPES...
    /// @tparam TYPE The type to construct (must be in TYPES...)
    /// @param value The value to initialize with
    template <typename TYPE, typename = typename core::enable_if<is_variant_alternative<TYPE, type_list<TYPES...>>::value>::type>
    explicit Variant(TYPE const& value)
        : type_index_{type_index_mapper<TYPE, type_list<TYPES...>>::value} {
        static_assert(is_variant_alternative<TYPE, type_list<TYPES...>>::value, "TYPE must be one of the variant alternatives");
        new (data_) TYPE(value);
    }

    /// Move constructor
    /// @tparam TYPE The type to construct (must be in TYPES...)
    /// @param value The value to move from
    template <typename TYPE, typename = typename core::enable_if<is_variant_alternative<TYPE, type_list<TYPES...>>::value>::type>
    explicit Variant(TYPE&& value)
        : type_index_{type_index_mapper<TYPE, type_list<TYPES...>>::value} {
        static_assert(is_variant_alternative<TYPE, type_list<TYPES...>>::value, "TYPE must be one of the variant alternatives");
        new (data_) TYPE(static_cast<TYPE&&>(value));
    }

    /// Destructor - destroys the active type
    ~Variant() { destroy_active(); }

    /// Copy constructor - deleted for safety (can be enabled with explicit implementation)
    Variant(Variant const&) = delete;

    /// Move constructor - deleted for safety (can be enabled with explicit implementation)
    Variant(Variant&&) = delete;

    /// Copy assignment - deleted for safety (can be enabled with explicit implementation)
    Variant& operator=(Variant const&) = delete;

    /// Move assignment - deleted for safety (can be enabled with explicit implementation)
    Variant& operator=(Variant&&) = delete;

    /// Returns the number of types in the variant
    constexpr auto count() const { return count_; }

    /// Returns the size of the variant storage (does not count the tag)
    constexpr auto storage_size() const { return max_size_; }

    /// Returns the alignment of the variant storage
    constexpr auto storage_alignment() const { return max_align_; }

    /// Returns the current type index
    constexpr size_t index() const { return type_index_; }

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

    /// Gets a reference to the value if it holds TYPE, otherwise undefined behavior
    /// @tparam TYPE The type to get (must be in TYPES...)
    /// @return Reference to the stored value
    /// @warning Only call this after verifying with isa<TYPE>()
    template <typename TYPE>
    TYPE& get() {
        static_assert(is_variant_alternative<TYPE, type_list<TYPES...>>::value, "TYPE must be one of the variant alternatives");
        // For safety-critical code, you might want to add a runtime check here
        // if (!isa<TYPE>()) { /* handle error */ }
        return *reinterpret_cast<TYPE*>(data_);
    }

    /// Gets a const reference to the value if it holds TYPE, otherwise undefined behavior
    /// @tparam TYPE The type to get (must be in TYPES...)
    /// @return Const reference to the stored value
    /// @warning Only call this after verifying with isa<TYPE>()
    template <typename TYPE>
    TYPE const& get() const {
        static_assert(is_variant_alternative<TYPE, type_list<TYPES...>>::value, "TYPE must be one of the variant alternatives");
        // For safety-critical code, you might want to add a runtime check here
        // if (!isa<TYPE>()) { /* handle error */ }
        return *reinterpret_cast<TYPE const*>(data_);
    }
};

}    // namespace core

#endif    // CORE_VARIANT_HPP
