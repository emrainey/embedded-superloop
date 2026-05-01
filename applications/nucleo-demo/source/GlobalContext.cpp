#include "BoardContext.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Monitor.hpp"
#include "jarnax/console/Service.hpp"
#include "jarnax/drivers/ssd1306/Driver.hpp"

#include "Demo.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : demo_{}
        , monitor_{jarnax::GetBoardContext().GetTimer(), jarnax::GetBoardContext().GetStatusIndicator(), jarnax::GetBoardContext().GetErrorIndicator()}
        , console_{jarnax::GetBoardContext().GetConsole()}
        , superloop_{jarnax::GetTicker()} {}

    /// Default Destructor
    virtual ~GlobalContext() = default;

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(monitor_);
        result &= GetSuperLoop().Enlist(demo_);
        result &= GetSuperLoop().Enlist(jarnax::GetBoardContext().GetI2cA());
        result &= GetSuperLoop().Enlist(jarnax::GetBoardContext().GetI2cB());
        result &= GetSuperLoop().Enlist(jarnax::GetBoardContext().GetSpiA());
        result &= GetSuperLoop().Enlist(jarnax::GetBoardContext().GetUsartB());
        result &= GetSuperLoop().Enlist(console_);
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    Demo demo_;
    jarnax::Monitor monitor_;
    jarnax::console::Service& console_;    // a reference to the board console service
                                           // since this is not in the board context, it has to be in the GlobalContext
    jarnax::SuperLoop superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext global_context;
    return global_context;
}
}    // namespace jarnax
