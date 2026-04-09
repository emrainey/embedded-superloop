#include <gtest/gtest.h>
#include <core/Buffer.hpp>
#include <gtest/Status.hpp>
#include <jarnax/GlacialTimer.hpp>
#include <jarnax/TestContext.hpp>
#include <jarnax/dma/MockManager.hpp>
#include <memory.hpp>
#include <stm32/configure.hpp>
#include <stm32/i2c/Driver.hpp>
#include <stm32/vectors.hpp>
#include "board.hpp"

using namespace ::testing;
// using WillOnce;
// using ::testing::Return;

namespace stm32 {
namespace i2c {
class I2CDriverTest : public ::testing::Test {
public:
    constexpr static size_t BufferSize{256U};
    I2CDriverTest()
        : timer_{}
        , mock_dma_manager_{}
        , i2c_driver_{stm32::peripherals::i2c1, mock_dma_manager_, I2C1_TX, I2C1_RX}
        , txn_{timer_}
        , buffer_{BufferSize, core::GetDefaultAllocator()} {
        // Constructor code, if needed
    }
    ~I2CDriverTest() override = default;

    void SetUp() override {
        // Code to set up the test environment, if needed
        ASSERT_EQ(256U, buffer_.capacity());
        // txn_.Inform(jarnax::spi::Transaction::Event::None);
        EXPECT_CALL(mock_dma_manager_, Assign(I2C1_TX)).WillOnce(Return(&mock_tx_resource_));
        EXPECT_CALL(mock_dma_manager_, Assign(I2C1_RX)).WillOnce(Return(&mock_rx_resource_));
        EXPECT_CALL(mock_tx_resource_, Initialize(I2C1_TX)).Times(1);
        EXPECT_CALL(mock_rx_resource_, Initialize(I2C1_RX)).Times(1);
        core::Status status = i2c_driver_.Initialize(42_MHz, 400_KHz);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
        // assert some things about the I2C1 peripheral device
        stm32::peripherals::InterIntegratedCircuit::Control1 control1;
        control1 = stm32::peripherals::i2c1.control1;
        ASSERT_EQ(0x0001U, control1.whole);
        stm32::peripherals::InterIntegratedCircuit::Control2 control2;
        control2 = stm32::peripherals::i2c1.control2;
        if constexpr (stm32::configure::use_i2c_as == stm32::configure::Mode::Dma) {
            ASSERT_EQ(1U, control2.bits.error_interrupt_enable);
            ASSERT_EQ(1U, control2.bits.event_interrupt_enable);
            ASSERT_EQ(1U, control2.bits.buffer_interrupt_enable);
        }
    }
    void TearDown() override {
        // Code to clean up after tests, if needed
    }

protected:
    void Initialize(jarnax::i2c::Address address, core::Span<std::uint8_t> injected) {
        ASSERT_TRUE(txn_.IsUninitialized());
        auto span = buffer_.as_span();
        ASSERT_FALSE(span.IsEmpty());
        if (address.small.read) {
            // clear it out with nonsense
            memory::fill(span.data(), 0xA5, span.count());
        } else {
            for (size_t i = 0; i < injected.count(); ++i) {
                span[i] = injected[i];
            }
        }
        txn_.address = address;
        txn_.actual_count = 0U;
        txn_.desired_count = injected.count();
        // Move the buffer into the transaction, we'll lose it until after the transaction is complete
        txn_.buffer = std::move(buffer_);
        txn_.Inform(jarnax::i2c::Transaction::Event::Initialized);
    }

    void Schedule() {
        ASSERT_TRUE(txn_.IsInitialized());
        core::Status status = i2c_driver_.Schedule(&txn_);
        ASSERT_STATUS_EQ(status, core::Result::Success, core::Cause::State);
        ASSERT_TRUE(txn_.IsQueued());
        ASSERT_EQ(1U, i2c_driver_.GetCoordinatorStatistics().accepted);
    }

    void SimulateDataTransfer(core::Span<std::uint8_t> injected) {
        if constexpr (stm32::configure::use_i2c_as != stm32::configure::Mode::Dma) {
            // simulate the address phase going well
            stm32::peripherals::InterIntegratedCircuit::Control1 control1;
            stm32::peripherals::InterIntegratedCircuit::Control2 control2;
            stm32::peripherals::InterIntegratedCircuit::Status1 status1;
            stm32::peripherals::InterIntegratedCircuit::Status2 status2;
            status1 = stm32::peripherals::i2c1.status1;    // read
            status2 = stm32::peripherals::i2c1.status2;    // read
            status1.bits.address = 1;                      // set address match
            status2.bits.busy = 1;                         // set busy
            stm32::peripherals::i2c1.status1 = status1;    // write
            stm32::peripherals::i2c1.status2 = status2;    // write

            stm32::i2c1_event_isr();                       // call the ISR to handle the data
            // ASSERT_EQ(1U, i2c_driver_.GetStatistics().address_match);
            status1.bits.address = 0;                      // set address match
            stm32::peripherals::i2c1.status1 = status1;    // write

            if (txn_.address.small.read) {
                // Simulate the data transfer by calling the ISR directly
                for (size_t i = 0; i < injected.count(); ++i) {
                    stm32::peripherals::InterIntegratedCircuit::Data data;
                    status1.bits.receive_not_empty = 1;            // set transmit empty
                    stm32::peripherals::i2c1.status1 = status1;    // write
                    data.bits.data = injected[i];                  // write the data out
                    stm32::peripherals::i2c1.data = data;          // write back
                    stm32::i2c1_event_isr();                       // call the ISR to handle the data
                    // ASSERT_EQ(i + 1, i2c_driver_.GetStatistics().bytes_received);
                    status1.bits.receive_not_empty = 0;            // set transmit empty
                    stm32::peripherals::i2c1.status1 = status1;    // write
                }
            } else {                                               // write
                // Simulate the data transfer by calling the ISR directly
                for (size_t i = 0; i < injected.count(); ++i) {
                    stm32::peripherals::InterIntegratedCircuit::Data data;
                    status1.bits.transmit_empty = 1;                // set transmit empty
                    if (i + 1U == injected.count()) {
                        status1.bits.byte_transfer_finished = 1;    // present BTF during the final TXE ISR
                    }
                    stm32::peripherals::i2c1.status1 = status1;     // write
                    stm32::i2c1_event_isr();                        // call the ISR to handle the data
                    // ASSERT_EQ(i + 1, i2c_driver_.GetStatistics().bytes_transmitted);
                    data = stm32::peripherals::i2c1.data;          // read the data register
                    ASSERT_EQ(injected[i], data.bits.data);        // check the data
                    status1.bits.transmit_empty = 0;               // clear transmit empty
                    stm32::peripherals::i2c1.status1 = status1;    // write
                }
                control1 = stm32::peripherals::i2c1.control1;      // read
                ASSERT_EQ(1U, control1.bits.stop);                 // check for stop condition
                control1.bits.stop = 0;                            // clear stop condition
                stm32::peripherals::i2c1.control1 = control1;      // write
                // ASSERT_EQ(i + 1, i2c_driver_.GetStatistics().transmitted);
            }
            if (txn_.address.small.read) {
                // For reads we still model BTF as a later interrupt after the final byte arrives.
                status1 = stm32::peripherals::i2c1.status1;    // read
                status1.bits.byte_transfer_finished = 1;       // modify the status
                stm32::peripherals::i2c1.status1 = status1;    // write
                stm32::i2c1_event_isr();                       // call the ISR to handle the data
                status1.bits.byte_transfer_finished = 0;       // modify the status
                stm32::peripherals::i2c1.status1 = status1;    // write
            }
        } else {
            ASSERT_TRUE(false) << "DMA for I2C not implemented in this test";
        }
    }

    void VerifyData(core::Span<std::uint8_t> expected) {
        ASSERT_TRUE(txn_.IsComplete());
        buffer_ = txn_.Relinquish();
        auto span = buffer_.as_span();
        ASSERT_EQ(expected.count(), txn_.desired_count);
        ASSERT_EQ(expected.count(), txn_.actual_count);
        for (size_t i = 0; i < expected.count(); ++i) {
            ASSERT_EQ(expected[i], span[i]);
        }
    }

    jarnax::GlacialTimer timer_;
    jarnax::dma::MockManager mock_dma_manager_;
    jarnax::dma::MockResource mock_tx_resource_;
    jarnax::dma::MockResource mock_rx_resource_;
    stm32::i2c::Driver i2c_driver_;
    jarnax::i2c::Transaction txn_;
    core::Buffer<uint8_t> buffer_;
};

TEST_F(I2CDriverTest, Empty) {}

TEST_F(I2CDriverTest, SimpleTx) {
    uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};
    core::Span<uint8_t> injected{data};
    jarnax::i2c::Address address{uint8_t(0x50U)};    // example address
    address.small.read = 0;                          // write
    Initialize(address, injected);
    Schedule();
    ASSERT_TRUE(i2c_driver_.Execute());
    ASSERT_FALSE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Busy, core::Cause::State);

    SimulateDataTransfer(injected);

    ASSERT_TRUE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Success, core::Cause::State);
    VerifyData(injected);
}

TEST_F(I2CDriverTest, SimpleRx) {
    uint8_t data[] = {0xAA, 0xBB, 0xCC, 0xDD};       // data to inject into the receive buffer
    core::Span<std::uint8_t> injected{data};
    jarnax::i2c::Address address{uint8_t(0x50U)};    // example address
    address.small.read = 1;                          // read
    Initialize(address, injected);
    Schedule();
    ASSERT_TRUE(i2c_driver_.Execute());
    ASSERT_FALSE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Busy, core::Cause::State);

    SimulateDataTransfer(injected);

    ASSERT_TRUE(txn_.IsComplete());
    ASSERT_STATUS_EQ(txn_.GetStatus(), core::Result::Success, core::Cause::State);
    VerifyData(injected);
}

}    // namespace i2c
}    // namespace stm32
