#pragma once

/// @file
/// The BitMapHeap Interface

#include <cstdint>
#include <cstddef>
#include <limits>

#include <core/Array.hpp>
#include <core/Allocator.hpp>
#include <core/Buffer.hpp>

namespace core {

/// @brief A simple bitmap heap allocator.
/// This allocator uses a bitmap to track the allocation of blocks in a static memory area.
/// @tparam BlockSize
/// @tparam BlockCount
/// @tparam MaxAlignment
template <std::size_t BlockSize, std::size_t BlockCount, std::size_t MaxAlignment = alignof(std::max_align_t)>
class BitMapHeap : public Allocator {
public:
    /// @brief The type of the bitfield used to track the allocation of blocks.
    using BitMapUnit = std::uint32_t;
    /// @brief The number of bits in the bitfueld unit
    static constexpr std::size_t kBitMapDepth = sizeof(BitMapUnit) * 8U;

    static_assert(BlockCount % kBitMapDepth == 0U, "BlockCount must be a multiple of the BitMapUnit type bit depth");

    /// @brief The parameterized constructor
    /// @param buffer The pointer to base of the buffer to use for the heap
    /// @param size  The size of the buffer in bytes
    /// @param upstream The (optional) upstream Allocator to use if the heap is exhausted
    BitMapHeap(void* buffer, std::size_t size, Allocator* upstream = nullptr)
        : buffer_(buffer)
        , size_(size)
        , bitmap_{}
        , stats_{}
        , upstream_(upstream) {
        if (size_ < (BlockSize * BlockCount)) {
            buffer_ = nullptr;
            size_ = 0U;
        }
        uintptr_t base = reinterpret_cast<uintptr_t>(buffer);
        if (base & (MaxAlignment - 1)) {
            buffer_ = nullptr;
            size_ = 0U;
        }
        stats_.size = BlockSize * BlockCount;
        stats_.free = stats_.size;
    }

#if defined(UNITTEST)
    void debug() { printBitmap(); }
#endif

    /// Used to indicate if the Heap itself is valid.
    bool IsValid() { return (buffer_ != nullptr) and (size_ > 0U); }

    /// @brief The Statistics of the Heap
    struct Statistics {
        std::size_t size{0U};     ///< The total size of the Heap
        std::size_t used{0U};     ///< The number of used blocks
        std::size_t free{0U};     ///< The number of free blocks
        std::size_t waste{0U};    ///< The number of wasted bytes (overage from alignment or block size mismatches)
        std::size_t count{0U};    ///< The number of allocations
    };

    /// @brief The Statistics of the Heap
    /// @return The read only reference to the Statistics of the Heap
    Statistics const& GetStatistics() { return stats_; }

    void* allocate(std::size_t bytes, std::size_t alignment) override {
        if (buffer_ == nullptr or size_ == 0) {
            if (upstream_) {
                return upstream_->allocate(bytes, alignment);
            } else {
                return nullptr;
            }
        }
        std::size_t blocks = bytes_to_blocks(bytes, alignment);
        std::size_t startBlock = findFreeBlocks(blocks);
        if (startBlock == BlockCount) {    // no available memory
            if (upstream_) {
                return upstream_->allocate(bytes, alignment);
            } else {
                return nullptr;
            }
        }
        markBlocksAsAllocated(startBlock, blocks);
        stats_.waste += (blocks * BlockSize) - bytes;
        std::size_t offset = startBlock * BlockSize;
        std::size_t alignedOffset = (offset + alignment - 1) & ~(alignment - 1);
        return static_cast<char*>(buffer_) + alignedOffset;
    }

    void deallocate(void* p, std::size_t bytes, std::size_t alignment) noexcept override {
        if (buffer_ == nullptr or size_ == 0) {
            if (upstream_) {
                upstream_->deallocate(p, bytes, alignment);
            }
            return;
        }
        bool contained = is_contained(p, bytes);
        if (contained) {
            std::size_t offset = reinterpret_cast<uintptr_t>(p) - reinterpret_cast<uintptr_t>(buffer_);
            std::size_t startBlock = offset / BlockSize;
            std::size_t blocks = (bytes + alignment - 1 + BlockSize - 1) / BlockSize;
            stats_.waste -= (blocks * BlockSize) - bytes;
            markBlocksAsFree(startBlock, blocks);
        } else {
            if (upstream_) {
                upstream_->deallocate(p, bytes, alignment);
            }
        }
    }

protected:
    inline std::size_t bytes_to_blocks(std::size_t bytes, std::size_t alignment) { return (bytes + alignment - 1 + BlockSize - 1) / BlockSize; }

    inline bool is_contained(void* p, std::size_t bytes) {
        uintptr_t base = reinterpret_cast<uintptr_t>(buffer_);
        uintptr_t offset = reinterpret_cast<uintptr_t>(p) - base;
        return offset < size_ and offset + bytes <= size_;
    }

private:
    std::size_t findFreeBlocks(std::size_t blocks) {
        std::size_t startBlock = 0;
        std::size_t freeBlocks = 0;
        for (std::size_t i = 0; i < bitmap_.size(); ++i) {
            if (bitmap_[i] != std::numeric_limits<BitMapUnit>::max()) {
                for (std::size_t j = 0; j < kBitMapDepth; ++j) {
                    if ((bitmap_[i] & (1u << j)) == 0) {
                        ++freeBlocks;
                        if (freeBlocks == blocks) {
                            // printf("Found %lu contiguous blocks at %lu\r\n", blocks, startBlock);
                            return startBlock;
                        }
                    } else {
                        startBlock = i * kBitMapDepth + j + 1;
                        freeBlocks = 0;
                    }
                }
            } else {
                startBlock = (i + 1) * kBitMapDepth;
                freeBlocks = 0;
            }
        }
        // this indicates that there are not enough free blocks
        return BlockCount;
    }

    void markBlocksAsAllocated(std::size_t startBlock, std::size_t blocks) {
        for (std::size_t i = startBlock; i < startBlock + blocks; ++i) {
            std::size_t bitmapIndex = i / kBitMapDepth;
            std::size_t bitIndex = i % kBitMapDepth;
            bitmap_[bitmapIndex] |= (1u << bitIndex);
        }
        stats_.count++;
        stats_.used += (BlockSize * blocks);
        stats_.free -= (BlockSize * blocks);
    }

    void markBlocksAsFree(std::size_t startBlock, std::size_t blocks) {
        for (std::size_t i = startBlock; i < startBlock + blocks; ++i) {
            std::size_t bitmapIndex = i / kBitMapDepth;
            std::size_t bitIndex = i % kBitMapDepth;
            bitmap_[bitmapIndex] &= ~(1u << bitIndex);
        }
        stats_.count--;
        stats_.used -= (BlockSize * blocks);
        stats_.free += (BlockSize * blocks);
    }

#if defined(UNITTEST)
    void printBitmap() {
        printf(
            "Heap Total: %zu Allocated: %lu Free: %lu Waste:%lu Count: %lu Valid? %s\r\n",
            stats_.size,
            stats_.used,
            stats_.free,
            stats_.waste,
            stats_.count,
            IsValid() ? "yes" : "no"
        );
        for (std::size_t i = 0U; i < bitmap_.size(); ++i) {
            for (std::size_t j = 0; j < kBitMapDepth; ++j) {
                char const c = (bitmap_[i] & (1u << j)) ? 'X' : '_';
                printf("%c", c);
            }
            printf("\r\n");
        }
    }
#endif

    /// The pointer to the static memory area
    void* buffer_;
    /// The size of the static memory area
    std::size_t size_;
    /// The array of bitmaps
    Array<uint32_t, (BlockCount + (kBitMapDepth - 1)) / kBitMapDepth> bitmap_;
    /// The statistics of the heap
    Statistics stats_;
    /// The upstream allocator
    Allocator* upstream_;
};

}    // namespace core