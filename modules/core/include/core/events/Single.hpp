#ifndef CORE_EVENTS_SINGLE_HPP_
#define CORE_EVENTS_SINGLE_HPP_

#include <core/events/Event.hpp>

/// @file
/// The Events Namespace and Event Interface

namespace core {
/// @brief The events Namespace contains objects which are used to transmit events.
namespace events {

/// @brief Provides a concrete implementation of a single event wrapper.
/// @tparam STORAGE
template <typename STORAGE>
class Single : public Event<STORAGE> {
public:
    static_assert(std::is_integral<STORAGE>::value or std::is_enum<STORAGE>::value, "Must be an integer type or enumeration");
    /// @brief The storage type of the Single Event, which reuses the Event's Type
    using StorageType = typename Event<STORAGE>::StorageType;

    /// @brief Default Constructor begins as not fired and set to the zero value of the StorageType
    Single()
        : fired_{false}
        , value_{StorageType(0)} {}

    /// @brief Single Event do initialize as fired by the parameterized constructor
    /// @param initial The initial value of the Event
    Single(StorageType initial)
        : fired_{true}
        , value_{initial} {}

    /// @brief Single Event do not initialize as fired by the default constructor
    virtual ~Single() = default;

    /// @brief Explicit bool test
    explicit operator bool(void) const override { return fired_; }

    /// @brief Explcit Type cast to the StorageType
    /// @warning Clears the fired state
    explicit operator StorageType(void) override {
        fired_ = false;
        return value_;
    }

    /// @brief Assignment operator
    /// @warning Sets the fired state
    /// @param other The other Event to copy from
    void operator=(StorageType const &other) override {
        fired_ = true;
        value_ = other;
    }

protected:
    /// @brief The flag which indicates the Event fired
    mutable bool fired_{false};
    /// @brief The storage fo the value
    StorageType value_{StorageType(0)};
};

}    // namespace events
}    // namespace core

#endif    // CORE_EVENTS_SINGLE_HPP_
