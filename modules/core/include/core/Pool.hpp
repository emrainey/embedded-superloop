#ifndef CORE_POOL_HPP
#define CORE_POOL_HPP

/// @file
/// The Pool Template class

#include "core/Array.hpp"
#include "core/Container.hpp"

namespace core {
/// @brief A Pool is a fixed size array of Containers which can be used to store objects.
template <typename TYPE, std::size_t CAPACITY>
class Pool {
public:
    /// The value type of the Stack
    using ValueType = TYPE;
    /// The pointer type to a ValueType
    using Pointer = TYPE*;
    /// The pointer to a constant ValueType
    using PointerConst = TYPE const*;
    /// The reference to a ValueType
    using Reference = TYPE&;
    /// The reference to the constant ValueType
    using ReferenceConst = TYPE const&;
    /// The index type of the array, zero based
    using IndexType = std::size_t;
    /// The size type of the array, expresses a number of bytes
    using SizeType = IndexType;
    /// The count type of the array, expresses a count of ValueTypes
    using CountType = SizeType;
    /// The iterator type
    using Iterator = Pointer;
    /// The Iterator of Constant Type
    using IteratorConst = PointerConst;

    /// Emplaces the TYPE into the storage at the first unused location.
    /// @tparam ...ARGS
    /// @param ...args the arguments to the constructor of the object
    /// @return The index to the constructed TYPE or the max value if no locations were free.
    template <typename... ARGS>
    IndexType emplace(ARGS&&... args) {
        size_t index{0U};
        for (auto& item : storage_) {
            if (item) {
                index++;
                continue;    // already used
            } else {
                item.emplace(std::forward<ARGS>(args)...);
                used_++;
                free_--;
                return index;
            }
        }
        return std::numeric_limits<IndexType>::max();
    }

    /// Destructs the TYPE at the given index.
    /// @param index The index to destruct
    void dismiss(IndexType index) {
        if (index < CAPACITY) {
            used_--;
            free_++;
            storage_[index].dismiss();
        }
    }

    /// Returns a mutable reference to the Container at the index
    /// @param index The index to the Container
    /// @return A mutable reference to the Container
    Container<TYPE>& operator[](IndexType index) { return storage_[index]; }

    /// Returns a constant reference to the Container at the index
    /// @param index The index to the Container
    /// @return A constant reference to the Container
    Container<TYPE> const& operator[](IndexType index) const { return storage_[index]; }

    /// @return The count of free elements in the Pool
    CountType available() const { return free_; }

    /// @return The count of used elements in the Pool
    CountType count() const { return used_; }

    /// @return The number of elements in the Pool
    constexpr CountType capacity() const { return CAPACITY; }

    /// @param index The index to check
    /// @return True of the Container at the index is present (constructed)
    bool is_present(IndexType index) const { return bool(storage_[index % CAPACITY]); }

protected:
    Array<Container<TYPE>, CAPACITY> storage_;    ///< The storage of all containers
    CountType used_{0U};                          ///< The number of used containers
    CountType free_{CAPACITY};                    ///< The number of free containers.
};
}    // namespace core
#endif    // CORE_POOL_HPP