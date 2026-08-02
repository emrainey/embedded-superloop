#ifndef STM32_TESTS_MOCKS_CORE_MOCK_ALLOCATOR_HPP
#define STM32_TESTS_MOCKS_CORE_MOCK_ALLOCATOR_HPP

/// @file
/// GoogleMock Allocator for the core::Allocator interface. Host unit tests can use this mock to verify the allocation and deallocation patterns of
/// objects that depend on a core::Allocator without touching the real heap.

#include <cstddef>

#include <core/Allocator.hpp>

#include <gmock/gmock.h>

namespace core {

/// The GoogleMock implementation of the core::Allocator interface.
class MockAllocator : public core::Allocator {
public:
    MOCK_METHOD(void*, allocate, (std::size_t bytes, std::size_t alignment), (override));
    MOCK_METHOD(void, deallocate, (void* p, std::size_t bytes, std::size_t alignment), (override));

    virtual ~MockAllocator() = default;
};

}    // namespace core

#endif    // STM32_TESTS_MOCKS_CORE_MOCK_ALLOCATOR_HPP
