#include <gmock/gmock.h>
#include <gtest/gtest.h>

#include <cortex/Peripheral.hpp>
#include <jarnax/JumpTimer.hpp>
#include <jarnax/MockCache.hpp>
#include <jarnax/MockTransactor.hpp>
#include <jarnax/dma/MockManager.hpp>

namespace jarnax {

static constexpr std::size_t Attempts = 3u;
class DummyTransaction : public Transactable<DummyTransaction, Attempts> {
public:
    DummyTransaction(Timer& timer)
        : Transactable{timer} {}
    void Clear() { id_ = 0; }

    void Initialize(std::size_t id) {
        id_ = id;
        Inform(Event::Initialized);
    }

    bool IsFinal() const { return Transactable<DummyTransaction, Attempts>::IsFinal(); }

protected:
    std::size_t id_;
};

}    // namespace jarnax

TEST(Mocks, Transactor) {
    jarnax::MockTransactor<jarnax::DummyTransaction> mock_transactor;
    jarnax::JumpTimer timer{};
    jarnax::DummyTransaction transaction{timer};
    transaction.Initialize(42);
    EXPECT_CALL(mock_transactor, Verify(testing::Ref(transaction)))
        .WillOnce(testing::Return(core::Status{core::Result::Success, core::Cause::Unknown}));
    mock_transactor.Verify(transaction);
}

TEST(Mocks, DMA) {
    jarnax::dma::MockManager mock_manager;
    jarnax::dma::MockResource mock_resource;
    cortex::Peripheral peripheral{cortex::Peripheral::Type::DMA, 0, cortex::Peripheral::Sub::TX};

    EXPECT_CALL(mock_manager, Assign(peripheral)).WillOnce(testing::Return(&mock_resource));
    EXPECT_CALL(mock_resource, Initialize(peripheral)).Times(1);
    jarnax::dma::Resource* resource = mock_manager.Assign(peripheral);
    ASSERT_NE(resource, nullptr);
    resource->Initialize(peripheral);
}

TEST(Mocks, Cache) {
    jarnax::MockDataCache mock_data_cache;
    jarnax::MockInstructionCache mock_instruction_cache;

    EXPECT_CALL(mock_data_cache, Enable()).Times(1);
    EXPECT_CALL(mock_data_cache, Invalidate(std::uintptr_t{0x20000000}, size_t{64})).Times(1);
    EXPECT_CALL(mock_instruction_cache, Enable()).Times(1);
    EXPECT_CALL(mock_instruction_cache, Invalidate()).Times(1);

    mock_data_cache.Enable();
    mock_data_cache.Invalidate(0x20000000, 64);
    mock_instruction_cache.Enable();
    mock_instruction_cache.Invalidate();
}
