#ifndef CORE_EVENTS_HPP_
#define CORE_EVENTS_HPP_

/// @file
/// The Events Namespace and Event Interface

namespace core {
/// @brief The events Namespace contains objects which are used to transmit events.
namespace events {

/// @brief An enum which wraps a boolean to provide a more abstracted notion of a flag.
enum class Flag : bool {
    Lowered = false,
    Raised = true,
};

/// @brief Used provided an interface for capturing the setting and getting of values some object.
/// @tparam STORAGE The storage type of the event. Can not be a boolean.
template <typename STORAGE>
class Event {
    static_assert(not std::is_same<bool, STORAGE>::value, "Must not be a boolean, use a Flag instead.");

public:
    /// @brief The Storage Type of the Event
    using StorageType = STORAGE;

    /// @brief Used to determine if the Event has been set.
    /// @retval true The value has been set.
    /// @retval false The values has not been set.
    /// @post explicit operator StorageType()
    virtual explicit operator bool(void) const = 0;

    /// @brief Used to read or get the value out of the Event.
    /// This will internally clear the indicator.
    virtual explicit operator StorageType(void) = 0;

    /// @brief Used to write or set the value into the Event.
    /// This will internally set the indicator.
    virtual void operator=(StorageType const &other) = 0;

protected:
    /// Do not allow destruction through the interface
    ~Event() = default;
};

}    // namespace events
}    // namespace core

#endif    // CORE_EVENTS_HPP_
