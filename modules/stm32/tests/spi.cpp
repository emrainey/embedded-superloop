#include <gtest/gtest.h>
#include <gtest/Status.hpp>
#include "board.hpp"
#include <memory.hpp>
#include <jarnax/dma/MockManager.hpp>
#include <jarnax/TestContext.hpp>
#include <jarnax/JumpTimer.hpp>
#include <stm32/spi/Driver.hpp>
#include <core/Buffer.hpp>

using namespace ::testing;
// using WillOnce;
// using ::testing::Return;

namespace stm32 {
namespace spi {
class SPIDriverTest : public ::testing::Test {
public:
    constexpr static size_t BufferSize{256U};
    SPIDriverTest()
        : timer_{}
        , mock_dma_manager_{}
        , spi_driver_{stm32::registers::spi1, mock_dma_manager_, SPI1_TX, SPI1_RX}
        , txn_{timer_}
        , buffer_{BufferSize, core::GetDefaultAllocator()} {
        // Constructor code, if needed
    }

    ~SPIDriverTest() override = default;

    void SetUp() override {
        // Code to set up the test environment, if needed
        ASSERT_EQ(256U, buffer_.capacity());
        timer_.Jump(10_iota);
        // txn_.Inform(jarnax::spi::Transaction::Event::None);
        EXPECT_CALL(mock_dma_manager_, Assign(SPI1_TX)).WillOnce(Return(&mock_tx_resource_));
        EXPECT_CALL(mock_dma_manager_, Assign(SPI1_RX)).WillOnce(Return(&mock_rx_resource_));
        EXPECT_CALL(mock_tx_resource_, Initialize(SPI1_TX)).Times(1);
        EXPECT_CALL(mock_rx_resource_, Initialize(SPI1_RX)).Times(1);
        core::Status status = spi_driver_.Initialize(42_MHz, 6_MHz);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
    }

    void TearDown() override {
        // Code to clean up after tests, if needed
    }

protected:
    void Initialize() {
        ASSERT_TRUE(txn_.IsUninitialized());
        auto tx_span = buffer_.as_span().subspan(0U, BufferSize/2U);
        auto rx_span = buffer_.as_span().subspan(BufferSize/2U, BufferSize/2U);
        ASSERT_FALSE(tx_span.IsEmpty());
        ASSERT_FALSE(rx_span.IsEmpty());
        memory::fill(tx_span.data(), 0xFF, tx_span.count());
        memory::fill(rx_span.data(), 0x00, rx_span.count());
        tx_span[0] = 0x0F;
        tx_span[1] = 0x34;
        txn_.send_size = 2U;
        txn_.receive_offset = BufferSize/2U;
        txn_.receive_size = 2U;
        txn_.buffer = std::move(buffer_);
        txn_.Inform(jarnax::spi::Transaction::Event::Initialized);
    }

    void Schedule() {
        ASSERT_TRUE(txn_.IsInitialized());
        core::Status status = spi_driver_.Schedule(&txn_);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
        ASSERT_TRUE(txn_.IsQueued());
        ASSERT_EQ(1U, spi_driver_.GetCoordinatorStatistics().accepted);
    }

    jarnax::JumpTimer timer_;
    jarnax::dma::MockManager mock_dma_manager_;
    jarnax::dma::MockResource mock_tx_resource_;
    jarnax::dma::MockResource mock_rx_resource_;
    stm32::spi::Driver spi_driver_;
    jarnax::spi::Transaction txn_;
    core::Buffer<uint8_t> buffer_;
};

TEST_F(SPIDriverTest, Empty) {}

TEST_F(SPIDriverTest, Simple) {
    Initialize();
    Schedule();
    ASSERT_TRUE(spi_driver_.Execute());
    ASSERT_FALSE(txn_.IsComplete());
}

}    // namespace spi
}    // namespace stm32


