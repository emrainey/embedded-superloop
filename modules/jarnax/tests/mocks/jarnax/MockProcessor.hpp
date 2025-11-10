#ifndef JARNAX_MOCK_PROCESSOR_HPP_
#define JARNAX_MOCK_PROCESSOR_HPP_

/// @file
/// A Mock Processor Interface for Jarnax unit tests
#include <jarnax/Processor.hpp>

namespace jarnax {

class MockProcessor : public Processor {
public:
    MOCK_METHOD(void, DisableInterrupts, (), (override));
    MOCK_METHOD(void, EnableInterrupts, (), (override));
    MOCK_METHOD(cortex::Ticks, GetTicks, (), (const, override));
    MOCK_METHOD(cortex::PartNumber, GetPartNumber, (), (const, override));
    MOCK_METHOD(cortex::Revision, GetRevision, (), (const, override));
    MOCK_METHOD(cortex::Hertz, GetCoreFrequency, (), (const, override));
    MOCK_METHOD(cortex::Hertz, GetSystemTickClockFrequency, (), (const, override));
    MOCK_METHOD(cortex::modes::Privileged, GetMode, (), (const, override));
    MOCK_METHOD(void, SoftwareReset, (), (override));
    virtual ~MockProcessor() = default;
};
}    // namespace jarnax

#endif
