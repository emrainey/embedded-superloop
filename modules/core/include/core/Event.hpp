#ifndef CORE_EVENTS_HPP_
#define CORE_EVENTS_HPP_

namespace core {
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
    ~Event() = default;
};

/// @brief Provides a concrete implementation of a single event wrapper.
/// @tparam STORAGE
template <typename STORAGE>
class Single : public Event<STORAGE> {
public:
    static_assert(std::is_integral<STORAGE>::value or std::is_enum<STORAGE>::value, "Must be an integer type or enumeration");
    using StorageType = typename Event<STORAGE>::StorageType;

    /// @brief Single Event do not initialize as fired by the default constructor
    Single() = default;

    /// @brief Single Event do initialize as fired by the parameterized constructor
    /// @param initial
    Single(StorageType initial)
        : fired_{true}
        , value_{initial} {}

    explicit operator bool(void) const override { return fired_; }

    explicit operator StorageType(void) override {
        fired_ = false;
        return value_;
    }

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

/// @brief Allows multiple Single Events to be set simultaneously via the same Event interface.
/// @tparam STORAGE The storage of the Single subordinate Events
/// @tparam COUNT The number of Single subordinate Events.
template <typename STORAGE, size_t COUNT>
class Multiplier : public Event<STORAGE> {
public:
    using StorageType = typename Event<STORAGE>::StorageType;

    /// @brief The default constructor does not set the events.
    Multiplier() = default;

    /// @brief The initializer list will connect all the suborddinate Single Events into this Event, clearing them in
    /// the process.
    /// @param list The list of pointers to Events.
    Multiplier(std::initializer_list<Event<STORAGE> *> list) {
        for (auto item : list) {
            Hook(item);
        }
    }

    explicit operator bool(void) const override { return bool(input_); }

    explicit operator StorageType(void) override { return StorageType(input_); }

    void operator=(StorageType const &other) override {
        input_ = other;
        for (size_t i = 0; i < count_; i++) {
            printf("Test [%zu] = %p\r\n", i, reinterpret_cast<void *>(outputs_[i]));
            if (outputs_[i]) {
                *outputs_[i] = other;
            }
        }
    }

    bool Hook(Event<STORAGE> *other) {
        for (size_t i = count_; i < COUNT; i++) {
            if (outputs_[i] == nullptr) {
                count_++;
                outputs_[i] = other;
                StorageType volatile tmp = StorageType(*outputs_[i]);    // get the event, thus clearing it
                (void)tmp;
                return true;
            }
        }
        return false;
    }

protected:
    Single<STORAGE> input_;
    size_t count_{0u};
    Event<STORAGE> *outputs_[COUNT]{};
};

}    // namespace events
}    // namespace core

#endif    // CORE_EVENTS_HPP_