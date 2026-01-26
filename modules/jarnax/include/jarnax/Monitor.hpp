#ifndef JARNAX_MONITOR_HPP
#define JARNAX_MONITOR_HPP

#include "core/Status.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Timer.hpp"

namespace jarnax {

/// @brief A Service which monitors the system status via Status and reports.
class Monitor : public jarnax::Loopable {
public:
    constexpr static core::units::MicroSeconds HalfPeriodStatusBlink{500'000u};    ///< The default interval to indicate the status

    /// @brief The parameterized constructor
    /// @param timer The timer to use for the monitor
    /// @param status_indicator The indicator to use for the status
    /// @param error_indicator The indicator to use for the error
    Monitor(jarnax::Timer const& timer, jarnax::Indicator& status_indicator, jarnax::Indicator& error_indicator);

    /// @brief The execute method
    bool Execute() override;

    /// Informs the monitor that a particular Status has occurred.
    /// @param status The status to report
    void Report(core::Status status);

protected:
    jarnax::Timer const& timer_;             ///< The timer reference to use for timing
    jarnax::Indicator& status_indicator_;    ///< The indicator to use for the status
    jarnax::Indicator& error_indicator_;     ///< The indicator to use for the error
    jarnax::CountDown countdown_;            ///< Used to track when to indicate the status
    core::Status reported_status_;           ///< The last reported status
};

}    // namespace jarnax

#endif    // JARNAX_MONITOR_HPP
