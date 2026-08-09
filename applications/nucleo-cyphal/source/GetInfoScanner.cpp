#include "GetInfoScanner.hpp"

#include <cstring>

namespace nucleo {
namespace cyphal {

GetInfoScanner::GetInfoScanner(std::uint16_t first_node, std::uint16_t last_node)
    : first_{first_node}
    , last_{last_node}
    , next_{first_node}
    , pending_{0U}
    , has_pending_{false}
    , tid_count_{0U}
    , tids_{} {
    // (first_node, last_node) are guarded by the application configuration.
    std::memset(tids_, 0, sizeof(tids_));
}

void GetInfoScanner::Reset() {
    next_ = first_;
    pending_ = 0U;
    has_pending_ = false;
}

bool GetInfoScanner::IsInRange(std::uint16_t node) const {
    return (node >= first_) && (node <= last_);
}

std::uint16_t GetInfoScanner::PeekNext() const {
    return next_;
}

std::uint16_t GetInfoScanner::TakeNext() {
    std::uint16_t const node = next_;
    next_ = (node == last_) ? first_ : static_cast<std::uint16_t>(node + 1U);
    return node;
}

bool GetInfoScanner::HasPending() const {
    return has_pending_;
}

std::uint16_t GetInfoScanner::PendingNode() const {
    return pending_;
}

void GetInfoScanner::SetPending(std::uint16_t node) {
    if (IsInRange(node) && !has_pending_) {
        pending_ = node;
        has_pending_ = true;
    }
}

void GetInfoScanner::ClearPending() {
    pending_ = 0U;
    has_pending_ = false;
}

std::uint64_t GetInfoScanner::NextTransferId(std::uint16_t node) {
    if (!IsInRange(node)) {
        return 0U;
    }
    TidEntry* entry = FindTid(node);
    if (entry == nullptr) {
        if (tid_count_ >= MaxWindowSize) {
            return 0U;
        }
        entry = &tids_[tid_count_++];
        entry->node_id = node;
        entry->transfer_id = 0U;
    }
    return entry->transfer_id++;
}

std::size_t GetInfoScanner::TidCount() const {
    return tid_count_;
}

GetInfoScanner::TidEntry* GetInfoScanner::FindTid(std::uint16_t node) {
    for (std::size_t i = 0U; i < tid_count_; ++i) {
        if (tids_[i].node_id == node) {
            return &tids_[i];
        }
    }
    return nullptr;
}

GetInfoScanner::TidEntry const* GetInfoScanner::FindTid(std::uint16_t node) const {
    for (std::size_t i = 0U; i < tid_count_; ++i) {
        if (tids_[i].node_id == node) {
            return &tids_[i];
        }
    }
    return nullptr;
}

}    // namespace cyphal
}    // namespace nucleo