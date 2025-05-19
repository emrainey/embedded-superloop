#ifndef JARNAX_MONITOR_HPP
#define JARNAX_MONITOR_HPP

#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Indicator.hpp"

namespace jarnax {

class Monitor : public jarnax::Loopable {
public:
    /// @brief The parameterized constructor
    /// @param timer The timer to use for the monitor
    /// @param status_indicator The indicator to use for the status
    /// @param error_indicator The indicator to use for the error
    Monitor(jarnax::Timer& timer, jarnax::Indicator& status_indicator, jarnax::Indicator& error_indicator);

    /// @brief The execute method
    bool Execute() override;

protected:
    jarnax::Timer& timer_;
    jarnax::Indicator& status_indicator_;
    jarnax::Indicator& error_indicator_;
    jarnax::CountDown countdown_;    ///< Used to track when to indicate the status
};

}    // namespace jarnax

#endif    // JARNAX_MONITOR_HPP