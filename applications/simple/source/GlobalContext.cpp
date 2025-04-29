
#include "jarnax/Context.hpp"

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
        , superloop_{jarnax::GetTicker()} {}

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(demo_);
        result &= GetSuperLoop().Enlist(jarnax::GetDriverContext().GetSpiDriver());
        result &= GetSuperLoop().Enlist(jarnax::GetDriverContext().GetWinbondDriver());
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    Demo demo_;
    jarnax::SuperLoop superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext my_context;
    return my_context;
}
}    // namespace jarnax