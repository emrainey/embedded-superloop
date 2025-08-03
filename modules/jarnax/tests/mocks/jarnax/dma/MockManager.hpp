#ifndef JARNAX_DMA_MOCK_MANAGER_HPP
#define JARNAX_DMA_MOCK_MANAGER_HPP

#include <jarnax/Peripheral.hpp>
#include <jarnax/dma/Manager.hpp>
#include <jarnax/dma/Resource.hpp>

#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <jarnax/dma/MockResource.hpp>

namespace jarnax {
namespace dma {

class MockManager : public jarnax::dma::Manager {
public:
    MOCK_METHOD(jarnax::dma::Resource*, Assign, (Peripheral const& peripheral), (override));
    MOCK_METHOD(jarnax::dma::Resource*, Acquire, (size_t index, Peripheral const& peripheral), (override));
    MOCK_METHOD(core::Status, Release, (jarnax::dma::Resource * &resource), (override));
    virtual ~MockManager() = default;
};

}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_MOCK_MANAGER_HPP
