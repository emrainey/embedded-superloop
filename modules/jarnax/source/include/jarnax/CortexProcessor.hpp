#ifndef JARNAX_INTERNAL_PROCESSOR_HPP_
#define JARNAX_INTERNAL_PROCESSOR_HPP_

#include "jarnax/Processor.hpp"

namespace jarnax {
class CortexProcessor : public Processor {
public:
    virtual ~CortexProcessor() = default;

    //=============================
    // jarnax::Processor Interface
    //=============================
    void DisableInterrupts() override;
    void EnableInterrupts() override;
    cortex::Ticks GetTicks() const override;
    cortex::PartNumber GetPartNumber() const override;
    cortex::Revision GetRevision() const override;
    cortex::Hertz GetCoreFrequency() const override;
    cortex::Hertz GetSystemTickClockFrequency() const override;
    cortex::modes::Privileged GetMode() const override;
    void SoftwareReset() override;
};    // namespace classCortexProcessor:public Processor

}    // namespace jarnax

#endif    // JARNAX_INTERNAL_PROCESSOR_HPP_
