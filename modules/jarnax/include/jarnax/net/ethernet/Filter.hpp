#ifndef JARNAX_NET_ETHERNET_FILTER_HPP
#define JARNAX_NET_ETHERNET_FILTER_HPP

/// @file
/// The Filter class for managing MAC address filters in the Ethernet layer.

#include <cstdint>
#include <jarnax/net/configuration.hpp>
#include <jarnax/net/eui/Address.hpp>
#include <jarnax/net/types.hpp>

namespace jarnax {
namespace net {
namespace ethernet {

/// @brief  The Filter Entry for managing ethernet MAC address filters
class FilterEntry {
public:
    /// @brief Default constructor for FilterEntry
    constexpr FilterEntry() = default;

    /// @brief The parameterized constructor for FilterEntry
    /// @param address The address to match
    FilterEntry(eui48::Address address);

    /// @brief Checks if this filter entry is valid
    /// @return True if the filter entry is valid, false otherwise
    bool IsValid() const;

    /// @brief Checks if this filter entry matches the given address and is valid
    /// @param addr The address to match against
    /// @return True if the filter entry is valid and matches the address, false otherwise
    bool Matches(const eui48::Address& addr) const;

    /// @brief Clears the filter entry, marking it as invalid and resetting the address
    void Clear();

protected:
    bool valid_{false};           //!< Is this a valid filter entry?
    eui48::Address address_{};    //!< The address to match
};

/// @brief The Filter class for managing a set of MAC filter entries
class Filter {
public:
    /// @brief Default constructor
    constexpr Filter() = default;

    /// @brief Adds an address to the filter
    /// @param address The address to add
    /// @return True if the address was added, false if the filter is full
    bool Add(eui48::Address const& address);

    /// @brief Removes an address from the filter
    /// @param address The address to remove
    /// @return True if the address was removed, false if it was not found
    bool Remove(eui48::Address const& address);

    /// @brief Checks if the filter matches a given address
    /// @param addr The address to check
    /// @return True if the filter matches the address, false otherwise
    bool Matches(eui48::Address const& addr) const;

protected:
    FilterEntry entries_[net::ethernet::MaximumFilterEntries];    //!< The filter entries
};

}    // namespace ethernet
}    // namespace net
}    // namespace jarnax

#endif    // JARNAX_NET_ETHERNET_FILTER_HPP
