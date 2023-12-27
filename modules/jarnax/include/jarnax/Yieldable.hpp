#ifndef JARNAX_YIELDABLE_HPP_
#define JARNAX_YIELDABLE_HPP_

/// @file
/// jarnax::Yieldable Interface

#include "jarnax/Executable.hpp"
#include "core/Event.hpp"

namespace jarnax {
/// @brief Yieldable objects inherit this interface and implement the Execute method
template <typename EVENT_TYPE, size_t STACK_SIZE, size_t COUNT>
class Yieldable : public Executable {
public:
    Yieldable()
        : m_watermark{kWaterMark}
        , m_stack_pointer{&m_stack[STACK_SIZE]}
        , m_event{}
        , m_index{SIZE_MAX} {
        // clear the stack
        memset(m_stack, 0, sizeof(m_stack));
        // initialize the statics
        if (s_initialized == false) {
            // initialize the list of Yieldables
            memset(s_yieldable_list, 0, sizeof(s_yieldable_list));
            s_initialized = true;
        }
        // for each instance of the Yieldable, remember the address of the object
        if (s_yieldable_count < COUNT) {
            m_index = s_yieldable_count;
            s_yieldable_list[s_yieldable_count] = this;
            s_yieldable_count++;
            s_too_many_instances = false;
        } else {
            // Yieldable past this count won't be remembered
            s_too_many_instances = true;
        }
    }

    /// @brief Indicates if the Yieldable is within the range of valid Yieldables
    /// @return If false, there's been a build error!
    bool IsValid(void) const { return (m_index == SIZE_MAX) ? false : true; }

    /// @brief Used by external objects to signal the Yieldable
    /// @param event_value When signalled the Yieldable will be executed on the next cycle
    void Signal(EVENT_TYPE event_value) { m_event = event_value; }

    [[noreturn]] void Start(void) {
        // set the stack pointer to the address of one past the end of the stack
        //
    }

protected:
    static void static_yield(void) {
        do {
            size_t next = s_current->m_index + 1;
            if (next >= s_yieldable_count) {
                next = 0;
            }
            // go to the next yieldable
            s_current = &s_yieldable_list[next];
            // check the events
            auto &event = s_current->GetEvent();
            if (event) {    // if the event is signalled
                // go to this yieldable
                break;
            } else {
                // go to the next yieldable
            }
        } while (true);
    }

    /// @brief Yields the current executable to the system. Only the Yieldable itself can invoke this.
    void Yield(void) {
        // save the stack
        // save the stack pointer

        static_yield();

        // restore the stack pointer
        // restore the stack (and pc)
    }

    /// @brief Retrieves the Event for the Yieldable
    /// @param
    /// @return
    core::events::Event<EVENT_TYPE> &GetEvent(void) { return m_event; }

    /// Prevent construction of Yieldable objects
    ~Yieldable() = default;

    constexpr static uint32_t kWaterMark{0x55AAAA55};
    uint32_t const m_watermark;                  ///< Watermark to check for stack overflow
    alignas(8u) uint8_t m_stack[STACK_SIZE];     ///< Stack for the executable
    void *m_stack_pointer;                       ///< Stack pointer for the executable (when it's not being used)
    core::events::Single<EVENT_TYPE> m_event;    ///< Event for the Yieldable
    size_t m_index{SIZE_MAX};                    ///< Index of the Yieldable in the private list
private:
    static bool s_initialized;                    ///< Whether the Yieldable statics have been initialized
    static Yieldable *s_yieldable_list[COUNT];    ///< List of all Yieldables
    static size_t s_yieldable_count;              ///< Number of Yieldables
    static bool s_too_many_instances;             ///< Whether there are too many instances of Yieldable
    static Yieldable *s_current;                  ///< The currently executing Yieldable
};

template <typename EVENT_TYPE, size_t STACK_SIZE, size_t COUNT>
bool Yieldable<EVENT_TYPE, STACK_SIZE, COUNT>::s_initialized{false};

template <typename EVENT_TYPE, size_t STACK_SIZE, size_t COUNT>
Yieldable<EVENT_TYPE, STACK_SIZE, COUNT> *Yieldable<EVENT_TYPE, STACK_SIZE, COUNT>::s_yieldable_list[COUNT];

template <typename EVENT_TYPE, size_t STACK_SIZE, size_t COUNT>
size_t Yieldable<EVENT_TYPE, STACK_SIZE, COUNT>::s_yieldable_count{0};

template <typename EVENT_TYPE, size_t STACK_SIZE, size_t COUNT>
bool Yieldable<EVENT_TYPE, STACK_SIZE, COUNT>::s_too_many_instances{false};

}    // namespace jarnax

#endif    // JARNAX_YIELDABLE_HPP_