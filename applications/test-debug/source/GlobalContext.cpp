#include "BoardContext.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Monitor.hpp"

#include "DebugTest.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : test_{}
        , monitor_{jarnax::GetBoardContext().GetTimer(), jarnax::GetBoardContext().GetStatusIndicator(), jarnax::GetBoardContext().GetErrorIndicator()}
        , superloop_{jarnax::GetTicker()} {}

    /// Default Destructor
    virtual ~GlobalContext() = default;

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(monitor_);
        result &= GetSuperLoop().Enlist(test_);
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    DebugTest test_;
    jarnax::Monitor monitor_;
    jarnax::SuperLoop superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext global_context;
    return global_context;
}
}    // namespace jarnax
