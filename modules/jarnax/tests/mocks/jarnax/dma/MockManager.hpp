#ifndef JARNAX_DMA_MOCK_MANAGER_HPP
#define JARNAX_DMA_MOCK_MANAGER_HPP

#include <jarnax/dma/Manager.hpp>
#include <jarnax/dma/Resource.hpp>
#include <jarnax/Peripheral.hpp>

#include <gtest/gtest.h>
#include <gmock/gmock.h>

#include <jarnax/dma/MockResource.hpp>

namespace jarnax {
namespace dma {

class MockManager : public jarnax::dma::Manager_<jarnax::dma::MockResource> {
public:
    MOCK_METHOD(jarnax::dma::Resource_<jarnax::dma::MockResource>*, Assign, (Peripheral const& peripheral), (override));
    MOCK_METHOD(jarnax::dma::Resource_<jarnax::dma::MockResource>*, Acquire, (size_t index, Peripheral const& peripheral), (override));
    MOCK_METHOD(core::Status, Release, (jarnax::dma::Resource_<jarnax::dma::MockResource> * &resource), (override));
};

using Manager = jarnax::dma::Manager_<jarnax::dma::MockResource>;

}    // namespace dma
}    // namespace jarnax

#endif    // JARNAX_DMA_MOCK_MANAGER_HPP
