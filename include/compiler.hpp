#ifndef COMPILER_HPP_
#define COMPILER_HPP_

/// @file
/// Contains compiler specific attributes and macros. These should be the only MACROS in the system due to how the attributes are different on
/// different compilers.

#define ATTRIBUTE(x) __attribute__(x)
#if defined(UNITTEST)
#define LINKER_SECTION(x)
#define NAKED
#define USED __attribute__((used))
#define ALWAYS_INLINE
#define ISR
#elif (defined(__GNUC__) or defined(__clang__)) and defined(__arm__)
#define LINKER_SECTION(x) ATTRIBUTE((used, section(x)))
#define NAKED ATTRIBUTE((used, naked))
#define USED ATTRIBUTE((used))
#define ALWAYS_INLINE ATTRIBUTE((always_inline))
#define ISR ATTRIBUTE((used, naked, nothrow, noreturn, weak, alias("dummy_isr")))
#else
#error "Unsupported compiler, please define the attributes for your compiler."
#endif

#include <cinttypes>
#include <compare>
#include <concepts>
#include <cstddef>
#include <cstdint>
#include <limits>
#include <new>
#include <type_traits>

#if not defined(PRIz)
#define PRIz "zu"
#endif

// clang-format off
inline size_t operator""_Z( unsigned long long int value) {
    return size_t(value);
}
// clang-format on

/// On 32 bit system the precision type that is passed around on the stack is a float, on 64 bit systems it is a double.
#if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8
using precision = double;
#else
using precision = float;
#endif

/// A concept that requires the type to implement all the comparison operators
template <typename TYPE>
concept Comparible = requires(std::remove_reference_t<TYPE> const& t, std::remove_reference_t<TYPE> const& u) {
    { t < u } -> std::convertible_to<bool>;
    { t <= u } -> std::convertible_to<bool>;
    { t > u } -> std::convertible_to<bool>;
    { t >= u } -> std::convertible_to<bool>;
    { t == u } -> std::convertible_to<bool>;
    { t != u } -> std::convertible_to<bool>;
    { t <=> u } -> std::convertible_to<std::strong_ordering>;
};

/// A concept to require a type to not be copyable or moveable
template <typename TYPE>
concept NonCopyableMovable = (not std::is_copy_constructible_v<TYPE>) and (not std::is_move_constructible_v<TYPE>) and
                             (not std::is_copy_assignable_v<TYPE>) and (not std::is_move_assignable_v<TYPE>);

/// @brief A class that is not copyable or moveable
/// This class can be used to create objects that cannot be copied or moved.
class UnCopyMoveable {
public:
    UnCopyMoveable() = default;
    virtual ~UnCopyMoveable() = default;

    UnCopyMoveable(UnCopyMoveable&&) = delete;
    UnCopyMoveable(const UnCopyMoveable&) = delete;
    UnCopyMoveable& operator=(UnCopyMoveable&&) = delete;
    UnCopyMoveable& operator=(const UnCopyMoveable&) = delete;
};

/// @brief A class that is not allocatable on the heap
/// This class can be used to create objects that cannot be allocated on the heap in any fashion.
/// Placement New / Delete Are Not to be Deleted! They are the only way to "allocate" these objects
/// In a known location in order to control Construction and Destruction time.
class UnAllocatable {
public:
    UnAllocatable() = default;
    virtual ~UnAllocatable() = default;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // New Methods as Defined from the Reference @see https://en.cppreference.com/w/cpp/memory/new/operator_new
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    void* operator new(std::size_t count) = delete;
    void* operator new[](std::size_t count) = delete;
    void* operator new(std::size_t count, std::align_val_t al) = delete;
    void* operator new[](std::size_t count, std::align_val_t al) = delete;
    void* operator new(std::size_t, const std::nothrow_t&) noexcept = delete;
    void* operator new[](std::size_t, const std::nothrow_t&) noexcept = delete;
    void* operator new(std::size_t count, std::align_val_t al, const std::nothrow_t& tag) noexcept = delete;
    void* operator new[](std::size_t count, std::align_val_t al, const std::nothrow_t& tag) noexcept = delete;
    // void* operator new(std::size_t count, void* ptr) noexcept;
    // void* operator new[](std::size_t, void* ptr) noexcept;
    // void* operator new  ( std::size_t count, /* args... */ );
    // void* operator new[]( std::size_t count, /* args... */ );
    // void* operator new  ( std::size_t count, std::align_val_t al, /* args... */ );
    // void* operator new[]( std::size_t count, std::align_val_t al, /* args... */ );

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // If the local versions are deleted, then the Class versions can't be defined
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    // static void* operator new(std::size_t count) = delete;
    // static void* operator new[](std::size_t count) = delete;
    // static void* operator new(std::size_t count, std::align_val_t al) = delete;
    // static void* operator new[](std::size_t count, std::align_val_t al) = delete;
    // static void* operator new(std::size_t count, void* ptr) noexcept;
    // static void* operator new[](std::size_t, void* ptr) noexcept;
    // static void* operator new(std::size_t count, std::align_val_t al);
    // static void* operator new[](std::size_t count, std::align_val_t al);
    // static void* operator new  ( std::size_t count, /* args... */ );
    // static void* operator new[]( std::size_t count, /* args... */ );
    // static void* operator new  ( std::size_t count, std::align_val_t al, /* args... */ );
    // static void* operator new[]( std::size_t count, std::align_val_t al, /* args... */ );

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // Delete Methods as defined from the Reference @see https://en.cppreference.com/w/cpp/memory/new/operator_delete
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    inline void operator delete(void*) noexcept {}    // without a definition, objects can't be destructed
    void operator delete[](void*) = delete;
    void operator delete(void*, std::align_val_t) noexcept = delete;
    void operator delete[](void*, std::align_val_t) noexcept = delete;
    void operator delete(void*, std::size_t) noexcept = delete;
    void operator delete[](void*, std::size_t) noexcept = delete;
    void operator delete(void* ptr, std::size_t sz, std::align_val_t al) noexcept = delete;
    void operator delete[](void* ptr, std::size_t sz, std::align_val_t al) noexcept = delete;
    // void operator delete  ( void* ptr, const std::nothrow_t& tag ) noexcept;
    // void operator delete[]( void* ptr, const std::nothrow_t& tag ) noexcept;
    // void operator delete  ( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;
    // void operator delete[]( void* ptr, std::align_val_t al, const std::nothrow_t& tag ) noexcept;
    // void operator delete  ( void* ptr, void* place ) noexcept;
    // void operator delete[]( void* ptr, void* place ) noexcept;
    // void operator delete  ( void* ptr, args... );
    // void operator delete[]( void* ptr, args... );

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=
    // If the local versions are deleted, then the Class versions can't be defined
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=

    // static void operator delete(void* ptr) = delete;
    // static void operator delete[](void* ptr) = delete;
    // static void operator delete(void* ptr, std::align_val_t al) = delete;
    // static void operator delete[](void* ptr, std::align_val_t al) = delete;
    // static void operator delete(void* ptr, std::size_t sz) = delete;
    // static void operator delete[](void* ptr, std::size_t sz) = delete;
    // static void operator delete(void* ptr, std::size_t sz, std::align_val_t al) = delete;
    // static void operator delete[](void* ptr, std::size_t sz, std::align_val_t al) = delete;
    // static void operator delete(void* ptr, ... /* args */);
    // static void operator delete[](void* ptr, ... /* args */);

    // inline static void operator delete(UnAllocatable*, std::destroying_delete_t) {}    // without a definition, objects can't be destructed
    // static void operator delete(UnAllocatable* ptr, std::destroying_delete_t, std::align_val_t al) = delete;
    // static void operator delete(UnAllocatable* ptr, std::destroying_delete_t, std::size_t sz) = delete;
    // static void operator delete(UnAllocatable* ptr, std::destroying_delete_t, std::size_t sz, std::align_val_t al) = delete;
};

#endif    // COMPILER_HPP_
