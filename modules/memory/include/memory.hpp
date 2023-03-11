#ifndef MEMORY_HPP_
#define MEMORY_HPP_

/// @file
/// The Memory Operations

#include <cstdint>
#include <cstddef>

/// @brief Standard C compatibility API for memory sets.
/// @param dst The pointer to the location to write the value.
/// @param value The value to write (truncated to a byte).
/// @param bytes The number of bytes to write.
/// @return Returns dst.
extern "C" void *memset(void *dst, int value, std::size_t bytes);

/// @brief Standard C compatibility API for memory copy.
/// @param dst The pointer to write the data to.
/// @param src The pointer to read the data from.
/// @param bytes The number of bytes to copy.
/// @return Returns dst.
extern "C" void *memcpy(void *dst, void const *src, std::size_t bytes);

/// The memory namespace
namespace memory {

/// Fills an array with a specific value.
/// @tparam UNIT_TYPE The unit type of the element.
/// @param array The array of the elements.
/// @param value The value to assign to each element.
/// @param count The count of the number of elements.
template <typename UNIT_TYPE>
void fill(UNIT_TYPE array[], UNIT_TYPE value, std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        array[i] = value;
    }
}

/// Copies a source array to destination array of elements.
/// @tparam UNIT_TYPE The unit type of the element.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
/// @param count The count of the number of elements.
template <typename UNIT_TYPE>
void copy(UNIT_TYPE dst[], UNIT_TYPE const src[], std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        dst[i] = src[i];
    }
}

/// Compares two array of the same type for specific count
/// @tparam UNIT_TYPE The unit type of the element.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
/// @param count The count of the number of elements.
/// @return 0 if equal, -1 is left arg is lower, 1 otherwise.
template <typename UNIT_TYPE>
int compare(UNIT_TYPE const lhs[], UNIT_TYPE const rhs[], std::size_t count) {
    for (std::size_t i = 0; i < count; ++i) {
        if (lhs[i] < rhs[i]) {
            return -1;
        } else if (lhs[i] > rhs[i]) {
            return 1;
        }
    }
    return 0;
}

/// Fills an array with a specific value.
/// @tparam UNIT_TYPE The unit type of the element.
/// @tparam COUNT The number of elements in the array.
/// @param array The array of the elements.
/// @param value The value to assign to each element.
template <typename UNIT_TYPE, std::size_t COUNT>
void fill(UNIT_TYPE (&array)[COUNT], UNIT_TYPE value) {
    for (std::size_t i = 0; i < COUNT; ++i) {
        array[i] = value;
    }
}

/// Copies a source array to destination array of elements.
/// @tparam UNIT_TYPE The unit type of the element.
/// @tparam COUNT The number of elements in the array.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
template <typename UNIT_TYPE, std::size_t COUNT>
void copy(UNIT_TYPE (&dst)[COUNT], UNIT_TYPE const (&src)[COUNT]) {
    for (std::size_t i = 0; i < COUNT; ++i) {
        dst[i] = src[i];
    }
}

/// Compares two array of the same type for specific count
/// @tparam UNIT_TYPE The unit type of the element.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
/// @param count The count of the number of elements.
/// @return 0 if equal, -1 is left arg is lower, 1 otherwise.
template <typename UNIT_TYPE, size_t COUNT>
int compare(UNIT_TYPE (&lhs)[COUNT], UNIT_TYPE (&rhs)[COUNT]) {
    for (std::size_t i = 0; i < COUNT; ++i) {
        if (lhs[i] < rhs[i]) {
            return -1;
        } else if (lhs[i] > rhs[i]) {
            return 1;
        }
    }
    return 0;
}

/// Copies a source array to destination array of unknown types.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
/// @param bytes The number of bytes to copy.
void copy(void *dst, void *const src, std::size_t bytes);

/// Fills an array of an unknown type with a specific value.
/// @param dst The destination array of the elements.
/// @param value The byte value to assign to the destination.
/// @param bytes The number of bytes to copy.
void fill(void *dst, std::uint8_t value, std::size_t bytes);

/// Compares two array of the same type for specific count
/// @tparam UNIT_TYPE The unit type of the element.
/// @param dst The destination array of the elements.
/// @param src The source array of the elements.
/// @param count The count of the number of elements.
/// @return 0 if equal, -1 is left arg is lower, 1 otherwise.
int compare(void const *lhs, void const *rhs, std::size_t bytes);

}    // namespace memory

#endif    // MEMORY_HPP_