#ifndef CORE_EVENT_HPP_
#define CORE_EVENT_HPP_

#include <cstdint>
#include <utility>

/// @file
/// The Events Namespace and Event Interface

namespace core {

/// @brief Holds a valued object that can be used to signal based on assignment or reading.
template <typename StorageType>
class Event {
public:
    Event()
        : raised_{false}
        , value_{StorageType()} {}
    /// Constructs an event with a value and marks it as raised
    /// @param v The initial value for the event
    Event(StorageType v)
        : raised_{true}
        , value_{v} {}

    /// Move Constructor will clear the original event
    Event(Event&& other) noexcept
        : raised_{other.raised_}
        , value_{std::move(other.value_)} {
        other.raised_ = false;
    }

    // Can't copy an Event
    Event(Event const&) = delete;

    // Can't copy assign an Event.
    Event& operator=(Event const&) = delete;

    /// Move assignment operator will clear the original event if raised
    Event& operator=(Event&& other) {
        if (this != &other) {
            raised_ = other.raised_;
            value_ = std::move(other.value_);
            other.raised_ = false;
        }
        return *this;
    }

    /// Destructor
    ~Event() = default;

    /// Raises the event with a copy of a value
    void Raise(StorageType value) {
        raised_ = true;
        value_ = value;
    }

    /// Raises the event with a copy assign from a const reference
    void Raise(StorageType const& value) {
        raised_ = true;
        value_ = value;
    }

    /// Raises the event with a move assignment of the value.
    void Raise(StorageType&& value) {
        raised_ = true;
        value_ = std::move(value);
    }

    /// Copy by Const Reference Assignment operator will raise the event
    Event& operator=(StorageType const& value) {
        raised_ = true;
        value_ = value;
        return *this;
    }

    /// Move Assignment operator will raise the event
    Event& operator=(StorageType&& value) {
        raised_ = true;
        value_ = std::move(value);
        return *this;
    }

    /// Explicit conversion to the StorageType which will clear the raised flag and
    /// will return a copy of the value.
    explicit operator StorageType() const {
        raised_ = false;
        return value_;
    }

    /// Check if the event is raised
    bool IsRaised(void) const { return raised_; }

    /// Peeks at the value of the event but does not clear the raised flag
    StorageType const& Peek(void) const { return value_; }

    /// Returns a read only reference the value of the event and clears the raised flag
    StorageType const& Get(void) const {
        raised_ = false;
        return value_;
    }

    /// Clears the event without altering the value.
    void Clear(void) { raised_ = false; }

private:
    mutable bool raised_;    ///< Indicates if the event has been raised
    StorageType value_;      ///< The value of the Event.
};

}    // namespace core

#endif    // CORE_EVENT_HPP_
