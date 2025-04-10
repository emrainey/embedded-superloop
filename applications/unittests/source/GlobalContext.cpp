
#include "jarnax/Context.hpp"
#include "unittests.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::DriverContext;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : self_test_{}
        , libc_test_{}
        , tick_test_{}
        , stack_test_{}
        , superloop_{jarnax::GetTicker()} {}

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(self_test_);
        result &= GetSuperLoop().Enlist(libc_test_);
        result &= GetSuperLoop().Enlist(tick_test_);
        result &= GetSuperLoop().Enlist(stack_test_);
        if (result) {
            return core::Status{};
        } else {
            return Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    // declare all the unit tests here
    SelfTest self_test_;
    LibcTest libc_test_;
    TickTest tick_test_;
    StackTest stack_test_;
    jarnax::SuperLoop superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext my_context;
    return my_context;
}
}    // namespace jarnax