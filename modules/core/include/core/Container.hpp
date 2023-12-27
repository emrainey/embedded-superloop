#ifndef CORE_CONTAINER_HPP_
#define CORE_CONTAINER_HPP_

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace core {

/// A container holds a constructible object which can be constructed at a later time.
/// @note Containers are not copyable or movable. Once placed a contained object is meant to stay in the container.
template <typename TYPE>
class Container {
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

    // static_assert(std::is_constructible<TYPE>(), "The type must be constructible");
    Container()
        : storage_{}
        , that_(nullptr) {}

    ~Container() { dismiss(); }

    /// Constructs a new object in place
    /// @tparam ...ARGS The set of arguments for the constructor of the object
    /// @param ...args The pack of arguments to pass to the constructor
    /// @note This will dismiss the current object if it exists
    template <typename... ARGS>
    void emplace(ARGS&&... args) {
        static_assert(std::is_constructible<ValueType, ARGS...>::value, "Object type must be constructible with provided arguments");
        dismiss();
        /// Placement new the object in the storage
        that_ = new (&storage_[0]) TYPE(std::forward<ARGS>(args)...);
    }

    void dismiss() {
        if (that_) {
            that_->~TYPE();
            that_ = nullptr;
        }
    }

    Container(Container const&) = delete;
    Container(Container&&) = delete;
    Container& operator=(Container const&) = delete;
    Container& operator=(Container&&) = delete;

    /// Allows testing the container to know if the object was emplaced
    explicit operator bool() const { return that_ != nullptr; }

    /// Used to get a reference to an atomic in the Container
    /// @return the reference to the object
    TYPE& operator*() {
        if (that_) {
            return *that_;
        } else {
            /// this is potentially uninitialized storage!
            return *reinterpret_cast<TYPE*>(&storage_[0]);
        }
    }

    /// Allows access to the internal object
    /// @return the pointer to the object or nullptr if not emplaced
    TYPE const* operator->() const { return that_; }

    /// Allows access to the internal object
    /// @return the pointer to the object or nullptr if not emplaced
    TYPE* operator->() { return that_; }

    constexpr std::size_t storage_size() const { return sizeof(storage_); }
    constexpr std::size_t storage_alignment() const { return alignof(TYPE); }

protected:
    alignas(alignof(TYPE)) std::uint8_t storage_[sizeof(TYPE)];
    TYPE* that_;
};

}    // namespace core

#endif    // CORE_CONTAINER_HPP_
