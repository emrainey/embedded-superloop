#include <cstddef>
#include <cstdint>

#include <gtest/gtest.h>

#include <core/Array.hpp>
#include <core/MockAllocator.hpp>

#include <jarnax/TestContext.hpp>
#include <jarnax/net/ethernet/Frame.hpp>

#include <stm32/h7xx/ethernet/Driver.hpp>

using namespace ::testing;

namespace stm32 {
namespace ethernet {
namespace dma {

using Frame = jarnax::net::ethernet::Frame;

/// @brief The shared fixture for the DescriptorRing tests. Each test gets its own descriptor array and ring so the ring index and frame accounting
/// can be verified in isolation.
class DescriptorRingTest : public ::testing::Test {
public:
    constexpr static std::size_t RingCount{4U};

    DescriptorRingTest()
        : descriptors_{}
        , ring_{descriptors_} {}

    void SetUp() override {
        // By default the mock hands real memory to/from the default allocator. Individual tests override this to simulate failures and to verify the
        // exact allocation/deallocation call patterns.
        ON_CALL(allocator_, allocate(_, _)).WillByDefault([](std::size_t bytes, std::size_t alignment) {
            return core::GetDefaultAllocator().allocate(bytes, alignment);
        });
        ON_CALL(allocator_, deallocate(_, _, _)).WillByDefault([](void* p, std::size_t bytes, std::size_t alignment) {
            core::GetDefaultAllocator().deallocate(p, bytes, alignment);
        });
    }

protected:
    /// Asserts every descriptor in the ring is completely zeroed.
    void ExpectDescriptorsZeroed() const {
        for (std::size_t i = 0U; i < RingCount; ++i) {
            EXPECT_EQ(0U, ring_.GetDescriptor(i)->des[0]);
            EXPECT_EQ(0U, ring_.GetDescriptor(i)->des[1]);
            EXPECT_EQ(0U, ring_.GetDescriptor(i)->des[2]);
            EXPECT_EQ(0U, ring_.GetDescriptor(i)->des[3]);
        }
    }

    /// Asserts every frame pointer in the ring is null.
    void ExpectFramesNull() const {
        for (std::size_t i = 0U; i < RingCount; ++i) {
            EXPECT_EQ(nullptr, ring_.GetFrame(i));
        }
    }

    /// The RAM-backed descriptor storage for the ring under test.
    core::Array<Descriptor volatile, RingCount> descriptors_{};
    /// The ring under test.
    DescriptorRing<RingCount> ring_;
    /// The mock allocator used to verify the frame allocation/deallocation patterns.
    core::MockAllocator allocator_;
};

TEST_F(DescriptorRingTest, Empty) {}

TEST_F(DescriptorRingTest, InitialState) {
    EXPECT_EQ(RingCount, ring_.Count());
    EXPECT_EQ(descriptors_.data(), ring_.GetStart());
    EXPECT_EQ(descriptors_.data() + RingCount, ring_.GetLimit());
    ExpectFramesNull();
    ExpectDescriptorsZeroed();
}

TEST_F(DescriptorRingTest, GetStartAndLimitAreAdjacent) {
    EXPECT_EQ(static_cast<std::ptrdiff_t>(RingCount), ring_.GetLimit() - ring_.GetStart());
    std::uintptr_t const start = reinterpret_cast<std::uintptr_t>(ring_.GetStart());
    std::uintptr_t const limit = reinterpret_cast<std::uintptr_t>(ring_.GetLimit());
    EXPECT_EQ(RingCount * sizeof(Descriptor), limit - start);
}

TEST_F(DescriptorRingTest, GetIndexForEveryDescriptor) {
    for (std::size_t i = 0U; i < RingCount; ++i) {
        EXPECT_EQ(static_cast<std::ptrdiff_t>(i), ring_.GetIndex(ring_.GetDescriptor(i)));
    }
    EXPECT_EQ(-1, ring_.GetIndex(ring_.GetLimit()));
}

TEST_F(DescriptorRingTest, GetDescriptorBounds) {
    for (std::size_t i = 0U; i < RingCount; ++i) {
        EXPECT_EQ(descriptors_.data() + i, ring_.GetDescriptor(i));
    }
    EXPECT_EQ(nullptr, ring_.GetDescriptor(RingCount));
    EXPECT_EQ(nullptr, ring_.GetDescriptor(RingCount + 1U));
    EXPECT_EQ(nullptr, ring_.GetDescriptor(RingCount * 4U));
}

TEST_F(DescriptorRingTest, GetFrameBounds) {
    for (std::size_t i = 0U; i < RingCount; ++i) {
        EXPECT_EQ(nullptr, ring_.GetFrame(i));
    }
    EXPECT_EQ(nullptr, ring_.GetFrame(RingCount));
    EXPECT_EQ(nullptr, ring_.GetFrame(RingCount + 1U));
    EXPECT_EQ(nullptr, ring_.GetFrame(RingCount * 4U));
}

TEST_F(DescriptorRingTest, ConstructAllocatesOneFramePerDescriptor) {
    EXPECT_CALL(allocator_, allocate(sizeof(Frame), alignof(Frame))).Times(RingCount);
    ASSERT_TRUE(ring_.Construct(allocator_));
    for (std::size_t i = 0U; i < RingCount; ++i) {
        EXPECT_NE(nullptr, ring_.GetFrame(i));
    }
    // Every frame must be a distinct allocation so the DMA never points two descriptors at the same buffer.
    for (std::size_t i = 0U; i < RingCount; ++i) {
        for (std::size_t j = i + 1U; j < RingCount; ++j) {
            EXPECT_NE(ring_.GetFrame(i), ring_.GetFrame(j));
        }
    }
}

TEST_F(DescriptorRingTest, ConstructLeavesDescriptorsZeroed) {
    ASSERT_TRUE(ring_.Construct(allocator_));
    ExpectDescriptorsZeroed();
}

TEST_F(DescriptorRingTest, DestructReleasesFramesAndClearsDescriptors) {
    ASSERT_TRUE(ring_.Construct(allocator_));
    EXPECT_CALL(allocator_, deallocate(_, sizeof(Frame), alignof(Frame))).Times(RingCount);
    ring_.Destruct(allocator_);
    ExpectFramesNull();
    ExpectDescriptorsZeroed();
}

TEST_F(DescriptorRingTest, ConstructAgainAfterDestructAllocatesFreshFrames) {
    ASSERT_TRUE(ring_.Construct(allocator_));
    EXPECT_NE(nullptr, ring_.GetFrame(0U));
    ring_.Destruct(allocator_);
    ASSERT_TRUE(ring_.Construct(allocator_));
    EXPECT_NE(nullptr, ring_.GetFrame(0U));
}

TEST_F(DescriptorRingTest, ConstructAfterFailureSucceeds) {
    // Simulate a first allocation failure, then verify the ring can be constructed successfully afterwards.
    {
        InSequence sequence;
        EXPECT_CALL(allocator_, allocate(_, _)).WillOnce(Return(nullptr));
        EXPECT_CALL(allocator_, allocate(_, _)).Times(static_cast<int>(RingCount)).WillRepeatedly([](std::size_t bytes, std::size_t alignment) {
            return core::GetDefaultAllocator().allocate(bytes, alignment);
        });
    }
    ASSERT_FALSE(ring_.Construct(allocator_));
    ExpectFramesNull();
    ExpectDescriptorsZeroed();

    ASSERT_TRUE(ring_.Construct(allocator_));
    EXPECT_CALL(allocator_, deallocate(_, _, _)).Times(static_cast<int>(RingCount));
    ring_.Destruct(allocator_);
}

TEST_F(DescriptorRingTest, DescriptorClearZeroesAllWords) {
    Descriptor descriptor;
    descriptor.des[0] = 0xDEADBEEFU;
    descriptor.des[1] = 0xCAFEBABEU;
    descriptor.des[2] = 0x12345678U;
    descriptor.des[3] = 0x87654321U;
    descriptor.Clear();
    EXPECT_EQ(0U, descriptor.des[0]);
    EXPECT_EQ(0U, descriptor.des[1]);
    EXPECT_EQ(0U, descriptor.des[2]);
    EXPECT_EQ(0U, descriptor.des[3]);
}

/// @brief Parameterized test which forces the allocator to fail on a specific descriptor's frame allocation (0-based). This verifies that the ring
/// deallocates the frames it already allocated and leaves the ring in a clean, reusable state.
class DescriptorRingConstructFailureTest : public DescriptorRingTest, public WithParamInterface<std::size_t> {};

TEST_P(DescriptorRingConstructFailureTest, FailsCleanlyAtEveryAllocationPoint) {
    std::size_t const fail_index = GetParam();
    std::size_t call = 0U;

    // The failure happens on the (fail_index + 1)th allocation, so the allocator is hit exactly fail_index + 1 times before the ring gives up.
    EXPECT_CALL(allocator_, allocate(_, _)).Times(static_cast<int>(fail_index + 1U)).WillRepeatedly([&call, fail_index](std::size_t bytes, std::size_t alignment) {
        if (call++ == fail_index) {
            return static_cast<void*>(nullptr);
        }
        return core::GetDefaultAllocator().allocate(bytes, alignment);
    });

    // The frames allocated before the failure are released by the internal Destruct.
    EXPECT_CALL(allocator_, deallocate(_, sizeof(Frame), alignof(Frame))).Times(static_cast<int>(fail_index));

    ASSERT_FALSE(ring_.Construct(allocator_));
    ExpectFramesNull();
    ExpectDescriptorsZeroed();
}

INSTANTIATE_TEST_SUITE_P(ConstructFailure, DescriptorRingConstructFailureTest, Range<std::size_t>(0U, DescriptorRingTest::RingCount, std::size_t{1U}));

}    // namespace dma
}    // namespace ethernet
}    // namespace stm32
