#ifndef SEGGER_RTT_HPP_
#define SEGGER_RTT_HPP_

/// @file
/// A re-implementation of the SEGGER RTT interface for use with the RTT Viewer in C++.

#ifdef UNITTEST
#include <new>
#endif

#include <cstdint>
#include <cstddef>
#include <utility>
#include <core/core.hpp>

/// @brief The namespace for the SEGGER RTT implementation.
namespace rtt {

/// @brief Contains the information about the Buffer (but not the buffer itself).
class BufferInfo {
public:
    /// @brief Default Constructor
    BufferInfo() = default;

    /// @brief Parameterized Constructor
    /// @param n The name
    /// @param s The size of the data buffer
    /// @param d The pointer to the data buffer
    BufferInfo(char const* n, size_t s, uint8_t d[]);

    /// @brief Writes the string to the ring buffer
    /// @param size The number of chars
    /// @param string The array of chars to write
    /// @retval The number of chars written
    size_t Write(size_t const size, char const string[]);

    /// @brief Reads the string from the ring buffer
    /// @param[inout] size On Input, the capacity of the string buffer, on output the number of chars read
    /// @param string The location to store the array of chars read
    /// @retval The number of chars read
    size_t Read(size_t const size, char string[]);

    /// @brief Returns the name of the buffer
    char const* GetName(void) const volatile;

    /// @brief Determines if the buffer is empty
    bool IsEmpty(void) const volatile;

    /// @brief Returns the number of bytes available to read in the buffer
    size_t GetCountAvailableData(void) const volatile;

    /// @brief Returns the number of free bytes available to write in the buffer
    size_t GetCountAvailableSpace(void) const volatile;

protected:
#if not defined(__arm__)
    using SizeType = size_t;
#else
    using SizeType = uint32_t;
#endif

    char const* name_{nullptr};
    uint8_t* data_{nullptr};
    SizeType size_{0U};
    SizeType volatile write_offset_{0u};
    SizeType volatile read_offset_{0u};
    struct Flags {
        enum class Mode : uint32_t {
            NoBlockSkip = 0U,
            NoBlockTrim = 1U,
            BlockIfFifoFull = 2U,
            Mask = 3U,
        };
        /// Constructor
        Flags();
        /// The mode of the buffer
        Mode mode_      : 2;
        uint32_t        : 22;
        /// Used to check the bits?
        uint32_t check_ : 8;
    };
    Flags flags_;
    static_assert(sizeof(Flags) == sizeof(uint32_t), "Must match");
};
#if defined(__arm__)
static_assert(sizeof(BufferInfo) == 24U, "Must be exactly this size on 32 bit");
#endif

static constexpr size_t kIndexBits{4u};

struct Index {
    Index(uint32_t i)
        : index{i & 0xF} {}
    uint32_t index : kIndexBits;
    uint32_t : 32U - kIndexBits;
};

/// The holder of the up and down buffers as well as the magic number sequence used to detect the structure.
class ControlBlock {
public:
    constexpr static size_t kMaxUpBufferCount{(1 << kIndexBits)};
    constexpr static size_t kMaxDownBufferCount{(1 << kIndexBits)};

    template <class... Args>
    bool emplace_up(Args&&... args) {
        if (up_buffer_count_ < kMaxUpBufferCount) {
            (void)new (&up_[up_buffer_count_]) BufferInfo(std::forward<Args>(args)...);
            up_buffer_count_++;
            return true;
        }
        return false;
    }

    template <class... Args>
    bool emplace_down(Args&&... args) {
        if (down_buffer_count_ < kMaxDownBufferCount) {
            (void)new (&down_[down_buffer_count_]) BufferInfo(std::forward<Args>(args)...);
            down_buffer_count_++;
            return true;
        }
        return false;
    }

    BufferInfo& GetUp(Index i) { return up_[i.index]; }

    BufferInfo& GetDown(Index i) { return down_[i.index]; }

public:
    /// Magic Value for the tool to ID the Control Block in Memory.
    char const id[16] = {'S', 'E', 'G', 'G', 'E', 'R', ' ', 'R', 'T', 'T', 0, 0, 0, 0, 0, 0};

protected:
    // char id[16];
    uint32_t const maximum_up_buffers_count_{kMaxUpBufferCount};
    uint32_t const maximum_down_buffers_count_{kMaxDownBufferCount};
    BufferInfo up_[kMaxUpBufferCount];
    BufferInfo down_[kMaxDownBufferCount];
    // management items past SEGGER's definitions
    uint32_t up_buffer_count_;
    uint32_t down_buffer_count_;
};

/// The global instance of the Control Block
extern ControlBlock control_block;

/// @brief Called bu clients to initialize the RTT to sensible defaults.
void initialize(void);

}    // namespace rtt

#endif    // SEGGER_RTT_HPP_