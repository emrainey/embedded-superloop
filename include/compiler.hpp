#ifndef COMPILER_HPP_
#define COMPILER_HPP_

/// @file
/// @brief Contains compiler specific attributes and macros. These should be the only MACROS in the system due to how the attributes are different on
/// different compilers.

#if defined(__GNUC__) or defined(__clang__)
/// @brief Defines a compiler-specific attribute
#define ATTRIBUTE(x) __attribute__(x)
#endif

/// @def LINKER_SECTION
/// @brief Places a variable or function in a specific linker section

/// @def NAKED
/// @brief Marks a function as naked, meaning it has no prologue/epilogue

/// @def USED
/// @brief Marks a variable or function as used, preventing the compiler from optimizing it away

/// @def ALWAYS_INLINE
/// @brief Marks a function as always inline, preventing the compiler from generating a separate function call

/// @def ISR
/// @brief Marks a function as an interrupt service routine. This applies several attributes to ensure the functions are used and do not have a
/// prologue/epilogue.

#if defined(UNITTEST)

// Unit Testing on GCC/Clang typically will not need or want the on-target attributes defined as
// they interfere with the normal operation of the unit tests.

#define LINKER_SECTION(x)
#define NAKED
#define ALWAYS_INLINE
#define ISR
// ELse if using GCC/Clang for ARM, define the attributes for the target
#elif (defined(__GNUC__) or defined(__clang__)) and defined(__arm__)

// On GCC/Clang for ARM, define the attributes for the target

#define LINKER_SECTION(x) ATTRIBUTE((used, section(x)))
#define NAKED ATTRIBUTE((used, naked))
#define ALWAYS_INLINE ATTRIBUTE((always_inline))
#define ISR ATTRIBUTE((used, naked, nothrow, noreturn))
#else
#error "Unsupported compiler, please define the attributes for your compiler."
#endif

#if defined(__has_attribute)
#if __has_attribute(used)
#define USED ATTRIBUTE((used))
#else
#define USED
#endif
// The alias attribute is not supported on Darwin, even though it defines __has_attribute(alias) as true
#if __has_attribute(alias) and not(defined(__APPLE__) or defined(__MACH__))
#define ALIAS(x) ATTRIBUTE((weak, alias(#x)))
#else
#define ALIAS(x) ATTRIBUTE((weak))
#endif
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

/// @brief User-defined literal for size_t
inline size_t operator""_Z(unsigned long long int value) {
    return static_cast<size_t>(value);
}

#if defined(__SIZEOF_POINTER__) && __SIZEOF_POINTER__ == 8
/// On 64 bit system the precision type that is passed around on the stack is a double.
using precision = double;
#else    // 32 bit systems
/// On 32 bit system the precision type that is passed around on the stack is a float.
using precision = float;
#endif

/// A concept that requires the type to implement all the comparison operators
template <typename TYPE>
concept Comparable = requires(std::remove_reference_t<TYPE> const& t, std::remove_reference_t<TYPE> const& u) {
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
