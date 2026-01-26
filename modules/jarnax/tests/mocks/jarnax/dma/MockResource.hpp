#ifndef JARNAX_MOCK_RESOURCE_HPP_
#define JARNAX_MOCK_RESOURCE_HPP_

/// @file
/// GoogleMock DMA Resource

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <jarnax/dma/Resource.hpp>

namespace jarnax {
namespace dma {

/// This class is a mock for the Resource class, which is used to represent a DMA Resource.
/// It uses Google Mock to create a mock interface for testing purposes.
/// The methods are defined as MOCK_METHOD to allow for expectations and verifications in tests.
class MockResource : public jarnax::dma::Resource {
public:
    MOCK_METHOD(void, Initialize, (Peripheral const& peripheral), (override));
    MOCK_METHOD(
        core::Status, ConfigureCopyToPeripheral, (std::uintptr_t source, size_t count, size_t unit_size, std::uintptr_t destination), (override)
    );
    MOCK_METHOD(
        core::Status, ConfigureCopyFromPeripheral, (std::uintptr_t source, std::uintptr_t destination, size_t count, size_t unit_size), (override)
    );
    MOCK_METHOD(core::Status, Enable, (), (override));
    MOCK_METHOD(core::Status, Disable, (), (override));
    MOCK_METHOD(core::Status, GetStatus, (), (const, override));
    MOCK_METHOD(size_t, GetIdentifier, (), (const, override));
    virtual ~MockResource() = default;
};

}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_MOCK_RESOURCE_HPP_
