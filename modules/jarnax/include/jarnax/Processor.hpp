#ifndef JARNAX_PROCESSOR_HPP_
#define JARNAX_PROCESSOR_HPP_

#include <core/Units.hpp>
#include <cortex/partnumber.hpp>
#include "cortex/tick.hpp"
#include "cortex/types.hpp"

namespace jarnax {

/// @brief The interface to the Processor
class Processor {
public:
    /// @brief Disable Interrupts
    virtual void DisableInterrupts() = 0;
    /// @brief Enables Interrupts
    virtual void EnableInterrupts() = 0;
    /// @brief Gets the current system tick count
    virtual cortex::Ticks GetTicks() const = 0;
    /// @brief Gets the Cortex Part Number
    virtual cortex::PartNumber GetPartNumber() const = 0;
    /// @brief Gets the Cortex Revision Number
    virtual cortex::Revision GetRevision() const = 0;
    /// @brief Gets the Frequency of the Core.
    virtual cortex::Hertz GetCoreFrequency() const = 0;
    /// @brief Gets the Frequency of the clock which feeds the System Tick
    virtual cortex::Hertz GetSystemTickClockFrequency() const = 0;
    /// @brief Gets the Priviledged Mode
    /// @warning Likely to be deprecated after testing.
    virtual cortex::modes::Privileged GetMode() const = 0;
    /// @brief Resets the Processor
    /// @warning This method will not return!
    virtual void SoftwareReset() = 0;

protected:
    ~Processor() = default;
};
}    // namespace jarnax

#endif    // JARNAX_PROCESSOR_HPP_
