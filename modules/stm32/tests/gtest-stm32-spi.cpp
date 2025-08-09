#include <gtest/gtest.h>
#include <core/Buffer.hpp>
#include <gtest/Status.hpp>
#include <jarnax/GlacialTimer.hpp>
#include <jarnax/TestContext.hpp>
#include <jarnax/dma/MockManager.hpp>
#include <memory.hpp>
#include <stm32/spi/Driver.hpp>
#include <stm32/vectors.hpp>
#include "board.hpp"

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
        // txn_.Inform(jarnax::spi::Transaction::Event::None);
        EXPECT_CALL(mock_dma_manager_, Assign(SPI1_TX)).WillOnce(Return(&mock_tx_resource_));
        EXPECT_CALL(mock_dma_manager_, Assign(SPI1_RX)).WillOnce(Return(&mock_rx_resource_));
        EXPECT_CALL(mock_tx_resource_, Initialize(SPI1_TX)).Times(1);
        EXPECT_CALL(mock_rx_resource_, Initialize(SPI1_RX)).Times(1);
        core::Status status = spi_driver_.Initialize(42_MHz, 6_MHz);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
        // assert some things about the SPI1 peripheral device
        stm32::registers::SerialPeripheralInterface::Control1 control1;
        stm32::registers::SerialPeripheralInterface::Control2 control2;
        control1 = stm32::registers::spi1.control1;
        control2 = stm32::registers::spi1.control2;
        ASSERT_EQ(0x314U, control1.whole);
        // ASSERT_EQ(1U, control1.bits.leader);
        // ASSERT_EQ(3U, control1.bits.baud_rate);
        ASSERT_EQ(4U, control2.whole);
    }

    void TearDown() override {
        // Code to clean up after tests, if needed
    }

protected:
    void Initialize(size_t count, uint8_t injected_tx[]) {
        ASSERT_TRUE(txn_.IsUninitialized());
        auto tx_span = buffer_.as_span().subspan(0U, BufferSize / 2U);
        auto rx_span = buffer_.as_span().subspan(BufferSize / 2U, BufferSize / 2U);
        ASSERT_FALSE(tx_span.IsEmpty());
        ASSERT_FALSE(rx_span.IsEmpty());
        memory::fill(tx_span.data(), 0xFF, tx_span.count());
        memory::fill(rx_span.data(), 0x00, rx_span.count());
        txn_.use_data_as_bytes = true;
        for (size_t i = 0; i < count; ++i) {
            tx_span[i] = injected_tx[i];
        }
        txn_.sent_size = 0U;
        txn_.send_size = count;
        txn_.receive_offset = BufferSize / 2U;
        txn_.received_size = 0U;
        txn_.receive_size = count;
        // Move the buffer into the transaction, we'll lose it until after the transaction is complete
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

    void SimulateDataTransfer(size_t count, uint8_t expected_tx[], uint8_t injected_rx[]) {
        if constexpr (not use_dma_for_spi) {
            for (size_t i = 0; i < count; ++i) {
                size_t old_interrupts = spi_driver_.GetStatistics().interrupts;
                // set the bits to indicate that there was a TXE and RXNE interrupt
                stm32::registers::SerialPeripheralInterface::Status status;
                stm32::registers::SerialPeripheralInterface::Data data;
                status = stm32::registers::spi1.status;
                status.bits.transmit_buffer_empty = 1;     // TXE
                stm32::registers::spi1.status = status;    // write
                stm32::spi1_isr();                         // call the ISR to handle the TXE
                ASSERT_EQ(old_interrupts + 1, spi_driver_.GetStatistics().interrupts);
                ASSERT_EQ((i + 1), spi_driver_.GetStatistics().transmit_buffer_empty);
                data = stm32::registers::spi1.data;    // read the data register
                ASSERT_EQ(expected_tx[i], static_cast<uint8_t>(data.bits.data)) << "i=" << i;
                data.whole = injected_rx[i];
                stm32::registers::spi1.data = data;          // write the injected RX
                status.bits.transmit_buffer_empty = 0;       // TXE is handled
                status.bits.receive_buffer_not_empty = 1;    // RXNE
                stm32::registers::spi1.status = status;      // write
                stm32::spi1_isr();                           // call the ISR to handle the RXNE
                ASSERT_EQ(old_interrupts + 2, spi_driver_.GetStatistics().interrupts);
                ASSERT_EQ((i + 1), spi_driver_.GetStatistics().receive_buffer_not_empty);
                status.bits.receive_buffer_not_empty = 0;    // RXNE is handled
                stm32::registers::spi1.status = status;      // write
            }
        } else {
            // the TX DMA stream should have been triggered
            ASSERT_TRUE(false) << "DMA simulation not implemented yet";
        }
    }

    void VerifyData(size_t count, uint8_t expected_rx[]) {
        ASSERT_TRUE(txn_.IsComplete());
        buffer_ = txn_.Relinquish();
        ASSERT_EQ(count, txn_.sent_size);
        ASSERT_EQ(count, txn_.received_size);
        auto rx_span = buffer_.as_span().subspan(txn_.receive_offset, txn_.received_size);
        ASSERT_EQ(count, rx_span.count());
        for (size_t i = 0; i < count; ++i) {
            ASSERT_EQ(expected_rx[i], rx_span[i]);
        }
    }

    jarnax::GlacialTimer timer_;
    jarnax::dma::MockManager mock_dma_manager_;
    jarnax::dma::MockResource mock_tx_resource_;
    jarnax::dma::MockResource mock_rx_resource_;
    stm32::spi::Driver spi_driver_;
    jarnax::spi::Transaction txn_;
    core::Buffer<uint8_t> buffer_;
};

TEST_F(SPIDriverTest, Empty) {}

TEST_F(SPIDriverTest, Simple) {
    size_t count = 2U;
    uint8_t expected_tx[] = {0x0F, 0x34};
    uint8_t injected_rx[] = {0xAB, 0xCD};
    Initialize(count, expected_tx);
    Schedule();
    ASSERT_TRUE(spi_driver_.Execute());
    ASSERT_FALSE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Busy, core::Cause::State);

    SimulateDataTransfer(count, expected_tx, injected_rx);

    ASSERT_TRUE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Success, core::Cause::State);
    VerifyData(count, injected_rx);
}

}    // namespace spi
}    // namespace stm32
