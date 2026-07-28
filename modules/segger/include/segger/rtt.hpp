#ifndef SEGGER_RTT_HPP_
#define SEGGER_RTT_HPP_

/// @file
/// A re-implementation of the SEGGER RTT interface for use with the RTT Viewer in C++.

#ifdef UNITTEST
#include <new>
#endif

#include <core/core.hpp>
#include <cstddef>
#include <cstdint>
#include <utility>

/// @brief The namespace for the SEGGER RTT implementation.
namespace rtt {

using iso::operator""_KiB;
/// The size of the buffer to send to the RTT Host
constexpr static size_t kUpwardBufferSize{4_KiB};
/// The size of the buffer to receive from the RTT Host
constexpr static size_t kDownwardBufferSize{16u};

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

    /// @brief Clears the buffer by resetting the read and write offsets to zero.
    void Clear(void) volatile { write_offset_ = 0U; read_offset_ = 0U; }

protected:
#if defined(__arm__)
    /// The size type used for buffer offsets on 32 bit ARM
    using SizeType = uint32_t;
#else
    /// The size type used for buffer offsets on other platforms
    using SizeType = size_t;
#endif

    char const* name_{nullptr};             ///< The name of the buffer
    uint8_t* data_{nullptr};                ///< The pointer to the data buffer
    SizeType size_{0U};                     ///< The size of the data buffer
    SizeType volatile write_offset_{0u};    ///< The write offset into the buffer
    SizeType volatile read_offset_{0u};     ///< The read offset into the buffer

    /// @brief RTT buffer operation mode flags
    /// @details Controls buffer behavior when full or when read/write operations are attempted
    struct Flags {
        /// @brief The mode of operation for the RTT buffer
        enum class Mode : uint32_t {
            NoBlockSkip = 0U,        ///< Non-blocking mode that skips data when the buffer is full
            NoBlockTrim = 1U,        ///< Non-blocking mode that trims data to fit when the buffer is full
            BlockIfFifoFull = 2U,    ///< Blocking mode that waits when the buffer is full
            Mask = 3U,               ///< Mask for the mode bits
        };
        /// Constructor
        Flags();
        /// The mode of the buffer
        Mode mode_      : 2;
        uint32_t        : 22;
        /// Used to check the bits?
        uint32_t check_ : 8;
    };

    Flags flags_;    ///< The flags controlling buffer behavior
    static_assert(sizeof(Flags) == sizeof(uint32_t), "Must match");
};
#if defined(__arm__)
static_assert(sizeof(BufferInfo) == 24U, "Must be exactly this size on 32 bit");
#endif

/// The number of bits used for the buffer index
static constexpr size_t kIndexBits{4u};

/// @brief Index into RTT buffer arrays
/// @details Provides a compact index representation for accessing RTT up/down buffers
struct Index {
    /// @brief Constructor from uint32_t
    Index(uint32_t i)
        : index{i & 0xF} {}
    uint32_t index : kIndexBits;    ///< Buffer index (0-15)
    uint32_t       : 32U - kIndexBits;
};

/// The holder of the up and down buffers as well as the magic number sequence used to detect the structure.
class ControlBlock {
public:
    /// @brief The maximum number of up buffers supported
    constexpr static size_t kMaxUpBufferCount{(1 << kIndexBits)};
    /// @brief The maximum number of down buffers supported
    constexpr static size_t kMaxDownBufferCount{(1 << kIndexBits)};

    /// @brief Constructs a Up Control Block with the given parameters
    template <class... Args>
    bool emplace_up(Args&&... args) {
        if (up_buffer_count_ < kMaxUpBufferCount) {
            (void)new (&up_[up_buffer_count_]) BufferInfo(std::forward<Args>(args)...);
            up_buffer_count_++;
            return true;
        }
        return false;
    }

    /// @brief Constructs a Down Control Block with the given parameters
    template <class... Args>
    bool emplace_down(Args&&... args) {
        if (down_buffer_count_ < kMaxDownBufferCount) {
            (void)new (&down_[down_buffer_count_]) BufferInfo(std::forward<Args>(args)...);
            down_buffer_count_++;
            return true;
        }
        return false;
    }

    /// @brief Retrieves the Up BufferInfo at the given index
    /// @param i The index of the Up buffer
    /// @return The BufferInfo reference
    BufferInfo& GetUp(Index i) { return up_[i.index]; }

    /// @brief Retrieves the Down BufferInfo at the given index
    /// @param i The index of the Down buffer
    /// @return The BufferInfo reference
    BufferInfo& GetDown(Index i) { return down_[i.index]; }

public:
    /// Magic Value for the tool to ID the Control Block in Memory.
    char const id[16] = {'S', 'E', 'G', 'G', 'E', 'R', ' ', 'R', 'T', 'T', 0, 0, 0, 0, 0, 0};

protected:
    /// The maximum number of up/down buffers supported by SEGGER's RTT Viewer
    uint32_t const maximum_up_buffers_count_{kMaxUpBufferCount};
    /// The maximum number of down buffers supported by SEGGER's RTT Viewer
    uint32_t const maximum_down_buffers_count_{kMaxDownBufferCount};
    /// The actual up buffers
    BufferInfo up_[kMaxUpBufferCount];
    /// The actual down buffers
    BufferInfo down_[kMaxDownBufferCount];

    // === management items past SEGGER's definitions

    /// The actual count of up buffers instantiated
    uint32_t up_buffer_count_;
    /// The actual count of down buffers instantiated
    uint32_t down_buffer_count_;
};

/// The global instance of the Control Block
extern ControlBlock control_block;

/// @brief Called bu clients to initialize the RTT to sensible defaults.
void initialize(void);

}    // namespace rtt

#endif    // SEGGER_RTT_HPP_
