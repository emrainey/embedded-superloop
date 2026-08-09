#ifndef APP_CYPHAL_GET_INFO_SCANNER_HPP
#define APP_CYPHAL_GET_INFO_SCANNER_HPP

#include <cstddef>
#include <cstdint>

namespace nucleo {
namespace cyphal {

/// Sequential scanner over a window of server node-IDs for uavcan.node.GetInfo client queries.
///
/// The scanner owns:
///   - the scan window [first, last] (inclusive);
///   - a cursor advancing around the window so each Execute() scan tick queries the next node;
///   - a per-server-node transfer-ID counter (Cyphal requires a separate transfer-ID per
///     (service-ID, server node-ID) pair);
///   - the identity of the node with a query currently in flight.
///
/// It has no dependency on the target, libudpard, or hypha, so it is fully host-testable.
class GetInfoScanner {
public:
    static constexpr std::size_t MaxWindowSize = 32U;

    /// Constructs a scanner over [first_node, last_node] inclusive.
    /// Both bounds must be in range and first_node <= last_node.
    GetInfoScanner(std::uint16_t first_node, std::uint16_t last_node);

    /// Re-arms the scanner to query first_node next, with no pending query.
    void Reset();

    /// True when node lies within the scan window.
    bool IsInRange(std::uint16_t node) const;

    /// The next node-ID to query without advancing the cursor.
    std::uint16_t PeekNext() const;

    /// Returns the next node-ID to query and advances the cursor (wrapping at last).
    std::uint16_t TakeNext();

    /// True while a query is awaiting a response.
    bool HasPending() const;

    /// The node-ID with a query in flight.
    std::uint16_t PendingNode() const;

    /// Records that a request was just sent to node.
    /// Precondition: IsInRange(node) and not HasPending().
    void SetPending(std::uint16_t node);

    /// Clears the in-flight query (response received or timed out).
    void ClearPending();

    /// Returns the current transfer-ID for node and increments it.
    /// A fresh counter is created on first use for a node in the window.
    std::uint64_t NextTransferId(std::uint16_t node);

    /// Number of distinct server node-IDs currently tracked for transfer-IDs.
    std::size_t TidCount() const;

private:
    struct TidEntry {
        std::uint16_t node_id;
        std::uint64_t transfer_id;
    };

    TidEntry* FindTid(std::uint16_t node);
    TidEntry const* FindTid(std::uint16_t node) const;

    std::uint16_t first_{0U};
    std::uint16_t last_{0U};
    std::uint16_t next_{0U};
    std::uint16_t pending_{0U};
    bool has_pending_{false};
    std::size_t tid_count_{0U};
    TidEntry tids_[MaxWindowSize];
};

}    // namespace cyphal
}    // namespace nucleo

#endif    // APP_CYPHAL_GET_INFO_SCANNER_HPP