#ifndef CORE_POOL_HPP
#define CORE_POOL_HPP

#include "core/Array.hpp"
#include "core/Container.hpp"

namespace core {
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

    void dismiss(IndexType index) {
        if (index < CAPACITY) {
            used_--;
            free_++;
            storage_[index].dismiss();
        }
    }

    Container<TYPE>& operator[](IndexType index) { return storage_[index]; }
    Container<TYPE> const& operator[](IndexType index) const { return storage_[index]; }
    CountType available() const { return free_; }
    CountType count() const { return used_; }
    constexpr CountType capacity() const { return CAPACITY; }
    bool is_present(IndexType index) const { return bool(storage_[index % CAPACITY]); }

protected:
    Array<Container<TYPE>, CAPACITY> storage_;
    CountType used_{0U};
    CountType free_{CAPACITY};
};
}    // namespace core
#endif    // CORE_POOL_HPP