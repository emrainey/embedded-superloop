#include <gtest/gtest.h>
#include <jarnax/net/ethernet/Filter.hpp>
#include "jarnax/TestContext.hpp"

using namespace jarnax::net::ethernet;
using jarnax::net::ethernet::Filter;
using jarnax::net::ethernet::FilterEntry;
using jarnax::net::eui48::Address;

TEST(FilterEntryTest, DefaultConstructor) {
    FilterEntry entry;
    EXPECT_FALSE(entry.IsValid());
}

TEST(FilterEntryTest, ParameterizedConstructor) {
    Address mac{0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    FilterEntry entry{mac};
    EXPECT_TRUE(entry.IsValid());
    EXPECT_TRUE(entry.Matches(mac));
    EXPECT_FALSE(entry.Matches(Address{0x66, 0x77, 0x88, 0x99, 0xAA, 0xBB}));
}

TEST(FilterEntryTest, MatchAndClearing) {
    Address mac{0x00, 0x11, 0x22, 0x33, 0x44, 0x55};
    FilterEntry entry{mac};
    EXPECT_TRUE(entry.Matches(mac));
    entry.Clear();
    EXPECT_FALSE(entry.Matches(mac));
}

TEST(FilterTest, AddAndMatchesEntry) {
    Filter filter;
    Address mac{0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    filter.Add(mac);
    EXPECT_TRUE(filter.Matches(mac));
}

TEST(FilterTest, RemoveEntry) {
    Filter filter;
    Address mac{0x01, 0x02, 0x03, 0x04, 0x05, 0x06};
    EXPECT_TRUE(filter.Add(mac));
    EXPECT_TRUE(filter.Remove(mac));
}

// --- New Tests for FilterEntry ---

TEST(FilterEntryTest, CopyAssignment) {
    FilterEntry entry1{Address{0x11, 0x22, 0x33, 0x44, 0x55, 0x66}};
    FilterEntry entry2 = entry1;
    EXPECT_EQ(entry1.IsValid(), entry2.IsValid());
    EXPECT_TRUE(entry1.Matches(Address{0x11, 0x22, 0x33, 0x44, 0x55, 0x66}));
}

// --- New Tests for Filter ---

TEST(FilterTest, AddWhenFull) {
    Filter filter;
    // Fill the filter (assuming MaximumFilterEntries is small, e.g., 100, we add a dummy address)
    Address dummy_mac{0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
    for (size_t i = 0; i < jarnax::net::ethernet::MaximumFilterEntries; ++i) {
        filter.Add(Address{0xAAAA, i, 0x00, 0x00, 0x00, 0x00});
    }
    // Attempt to add one more entry
    EXPECT_FALSE(filter.Add(dummy_mac)) << "Filter should return false when full";
}

TEST(FilterTest, RemoveNonExistentEntry) {
    Filter filter;
    Address existing_mac{0xAA, 0xBB, 0xCC, 0xDD, 0xEE, 0xFF};
    Address non_existing_mac{0x11, 0x22, 0x33, 0x44, 0x55, 0x66};

    filter.Add(existing_mac);

    // Attempt to remove an entry that is not present
    EXPECT_FALSE(filter.Remove(non_existing_mac)) << "Remove should return false if address is not found";
}
