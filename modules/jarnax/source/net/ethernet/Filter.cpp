#include <jarnax/net/ethernet/Filter.hpp>
#include "jarnax/net/eui/Address.hpp"

namespace jarnax {
namespace net {
namespace ethernet {

FilterEntry::FilterEntry(eui48::Address address)
    : valid_{true}
    , address_{address} {}

bool FilterEntry::IsValid() const {
    return valid_;
}

bool FilterEntry::Matches(const eui48::Address& addr) const {
    return valid_ and (address_ == addr);
}

void FilterEntry::Clear() {
    valid_ = false;                 // Mark the filter entry as invalid
    address_ = eui48::Address{};    // Reset the address to default
}

bool Filter::Add(eui48::Address const& address) {
    for (auto& entry : entries_) {
        if (not entry.IsValid()) {
            entry = FilterEntry{address};
            return true;
        }
    }
    return false;    // Filter is full
}

bool Filter::Remove(eui48::Address const& address) {
    for (auto& entry : entries_) {
        if (entry.IsValid() and entry.Matches(address)) {
            entry.Clear();    // Clear the entry
            return true;      // Successfully removed
        }
    }
    return false;    // Address not found in filter
}

bool Filter::Matches(eui48::Address const& addr) const {
    for (const auto& entry : entries_) {
        if (entry.Matches(addr)) {
            return true;
        }
    }
    return false;
}

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax
