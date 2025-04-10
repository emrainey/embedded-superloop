#pragma once

/// @file
/// The Allocator Interface

#include <cstdint>
#include <cstddef>

namespace core {

/// @brief The interface to use to allocate memory. This may be static or dynamic memory.
class Allocator {
public:
    /// @brief Allocates memory within the Allocator
    /// @param bytes The number of bytes needed.
    /// @param alignment The alignment of the memory. Defaults to the maximum alignment.
    /// @return A void pointer to the allocated memory. This must be cast to whatever type is needed.
    virtual void* allocate(std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) = 0;

    /// @brief Deallocates memory within the Allocator
    /// @param p The pointer previously allocated by this Allocator.
    /// @param bytes The number of bytes to deallocate.
    /// @param alignment The alignment of the memory. Defaults to the maximum alignment.
    virtual void deallocate(void* p, std::size_t bytes, std::size_t alignment = alignof(std::max_align_t)) = 0;

protected:
    /// Do not allow destruction through the interface
    ~Allocator() = default;
};

/// @brief Retrieves the default allocator for the system.
/// @return The default allocator for the system.
extern Allocator& GetDefaultAllocator() noexcept;

}    // namespace core
