#ifndef JARNAX_NET_ARP_TABLE_HPP
#define JARNAX_NET_ARP_TABLE_HPP

/// @file
/// The ARP Table Declaration

#include "core/Pool.hpp"
#include "core/avl/Node.hpp"

#include "jarnax/net/arp/Entry.hpp"
#include "jarnax/net/configuration.hpp"

#include <compare>
#include <cstdint>
#include <limits>

namespace jarnax {
namespace net {
namespace arp {

/// @brief Fixed-size ARP table indexed by IPv4 address.
/// @tparam CAPACITY Maximum number of entries in the table.
template <std::size_t CAPACITY = MaxEntries>
class Table {
public:
    using EntryType = Entry;
    using IndexType = std::size_t;
    using CountType = std::size_t;

    /// @brief Constructs and inserts an ARP entry.
    /// @return True when inserted or updated, false when no capacity was available.
    bool Insert(ip::v4::Address const& ipv4, eui48::Address const& mac, std::uint32_t ttl) { return Insert(EntryType{ipv4, mac, ttl}); }

    /// @brief Inserts an ARP entry, replacing the existing value for the same IPv4 key.
    /// @return True when inserted or updated, false when no capacity was available.
    bool Insert(EntryType const& entry) {
        if (not entry.IsValid()) {
            return false;
        }

        NodeType* existing = FindNode(entry.ipv4);
        if (existing != nullptr) {
            *(entries_[existing->Value().entry_index]) = entry;
            return true;
        }

        IndexType entry_index = entries_.emplace(entry);
        if (entry_index == InvalidIndex) {
            return false;
        }

        IndexType node_index = nodes_.emplace(Key{entry.ipv4, entry_index, InvalidIndex});
        if (node_index == InvalidIndex) {
            entries_.dismiss(entry_index);
            return false;
        }

        nodes_[node_index]->Value().node_index = node_index;
        NodeType* inserted = &(*nodes_[node_index]);

        if (root_ == nullptr) {
            root_ = inserted;
        } else {
            root_->Insert(inserted);
            root_ = root_->FindRoot();
        }

        return true;
    }

    /// @brief Removes an ARP entry by IPv4 key.
    /// @return True when removed, false when not found.
    bool Remove(ip::v4::Address const& ipv4) {
        if (FindNode(ipv4) == nullptr) {
            return false;
        }

        core::Array<EntryType, CAPACITY> retained{};
        CountType retained_count{0U};

        for (IndexType index = 0U; index < CAPACITY; ++index) {
            if (not entries_.is_present(index)) {
                continue;
            }

            EntryType const& candidate = *(entries_[index]);
            if (candidate == ipv4) {
                continue;
            }
            retained[retained_count++] = candidate;
        }

        Clear();

        for (IndexType index = 0U; index < retained_count; ++index) {
            Insert(retained[index]);
        }

        return true;
    }

    /// @brief Looks up an ARP entry by IPv4 key.
    EntryType* Find(ip::v4::Address const& ipv4) {
        NodeType* node = FindNode(ipv4);
        if (node == nullptr) {
            return nullptr;
        }
        return entries_[node->Value().entry_index].operator->();
    }

    /// @brief Looks up an ARP entry by IPv4 key.
    EntryType const* Find(ip::v4::Address const& ipv4) const {
        NodeType const* node = FindNode(ipv4);
        if (node == nullptr) {
            return nullptr;
        }
        return entries_[node->Value().entry_index].operator->();
    }

    /// @brief Decrements TTL on all entries and removes expired entries.
    void Tick() {
        core::Array<ip::v4::Address, CAPACITY> expired{};
        CountType expired_count{0U};

        for (IndexType index = 0U; index < CAPACITY; ++index) {
            if (not entries_.is_present(index)) {
                continue;
            }

            entries_[index]->DecrementTTL();
            if (not entries_[index]->IsValid()) {
                expired[expired_count++] = entries_[index]->ipv4;
            }
        }

        for (IndexType i = 0U; i < expired_count; ++i) {
            Remove(expired[i]);
        }
    }

    /// @brief Removes all entries from the table.
    void Clear() {
        for (IndexType index = 0U; index < CAPACITY; ++index) {
            if (entries_.is_present(index)) {
                entries_.dismiss(index);
            }
            if (nodes_.is_present(index)) {
                nodes_.dismiss(index);
            }
        }
        root_ = nullptr;
    }

    /// @return The number of active ARP entries.
    CountType Count() const { return entries_.count(); }

    /// @return Remaining capacity in the ARP table.
    CountType Available() const { return entries_.available(); }

    /// @return Maximum capacity in the ARP table.
    constexpr CountType Capacity() const { return CAPACITY; }

private:
    static constexpr IndexType InvalidIndex = std::numeric_limits<IndexType>::max();

    /// @brief AVL key for ARP table lookup.
    /// @details The IPv4 address is the logical lookup key. The index fields track the paired
    /// pooled entry and node so the table can keep the two storage pools in sync.
    struct Key {
        /// @brief IPv4 address used for ordering and lookup.
        ip::v4::Address ipv4{};
        /// @brief Index of the stored ARP entry in the entry pool.
        IndexType entry_index{InvalidIndex};
        /// @brief Index of the backing AVL node in the node pool.
        IndexType node_index{InvalidIndex};

        /// @brief Converts the key to its IPv4 value for ordering comparisons.
        constexpr explicit operator std::uint32_t() const { return static_cast<std::uint32_t>(ipv4); }

        /// @brief Compares keys by IPv4 address.
        bool operator==(Key const& other) const { return static_cast<std::uint32_t>(*this) == static_cast<std::uint32_t>(other); }
        /// @brief Compares keys by IPv4 address.
        bool operator!=(Key const& other) const { return not(*this == other); }
        /// @brief Compares keys by IPv4 address.
        bool operator<(Key const& other) const { return static_cast<std::uint32_t>(*this) < static_cast<std::uint32_t>(other); }
        /// @brief Compares keys by IPv4 address.
        bool operator<=(Key const& other) const { return static_cast<std::uint32_t>(*this) <= static_cast<std::uint32_t>(other); }
        /// @brief Compares keys by IPv4 address.
        bool operator>(Key const& other) const { return static_cast<std::uint32_t>(*this) > static_cast<std::uint32_t>(other); }
        /// @brief Compares keys by IPv4 address.
        bool operator>=(Key const& other) const { return static_cast<std::uint32_t>(*this) >= static_cast<std::uint32_t>(other); }

        /// @brief Provides three-way ordering by IPv4 address.
        std::strong_ordering operator<=>(Key const& other) const { return static_cast<std::uint32_t>(*this) <=> static_cast<std::uint32_t>(other); }
    };

    /// The AVL tree node is a Key wrapped in a Node for indexing the ARP entries by IPv4 address. The node pool is used to manage the memory of the
    /// AVL nodes, and the entry pool is used to manage the memory of the ARP entries.
    using NodeType = core::avl::Node<Key>;

    /// @brief Finds the AVL node for a given IPv4 address.
    NodeType* FindNode(ip::v4::Address const& ipv4) {
        if (root_ == nullptr) {
            return nullptr;
        }
        return root_->Find(Key{ipv4, InvalidIndex, InvalidIndex});
    }

    /// @brief Finds the AVL node for a given IPv4 address.
    NodeType const* FindNode(ip::v4::Address const& ipv4) const {
        if (root_ == nullptr) {
            return nullptr;
        }
        return root_->Find(Key{ipv4, InvalidIndex, InvalidIndex});
    }

    /// @brief Recomputes the root of the AVL tree.
    void RecomputeRoot() {
        root_ = nullptr;
        for (IndexType index = 0U; index < CAPACITY; ++index) {
            if (not nodes_.is_present(index)) {
                continue;
            }

            NodeType* node = &(*nodes_[index]);
            if (node->IsRoot()) {
                root_ = node;
                return;
            }
        }
    }

    /// @brief AVL tree of ARP entries indexed by IPv4 address, with a separate pool for the ARP entries themselves.
    core::Pool<EntryType, CAPACITY> entries_{};
    /// @brief AVL tree of ARP entries indexed by IPv4 address, with a separate pool for the ARP entries themselves.
    core::Pool<NodeType, CAPACITY> nodes_{};
    /// @brief Root of the AVL tree of ARP entries indexed by IPv4 address, with a separate pool for the ARP entries themselves.
    NodeType* root_{nullptr};
};

}    // namespace arp
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ARP_TABLE_HPP
