
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
        : m_self_test_{}
        , m_libc_test_{}
        , m_tick_test_{}
        , m_stack_test_{}
        , m_superloop_{jarnax::GetTicker()} {}

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(m_self_test_);
        result &= GetSuperLoop().Enlist(m_libc_test_);
        result &= GetSuperLoop().Enlist(m_tick_test_);
        result &= GetSuperLoop().Enlist(m_stack_test_);
        if (result) {
            return core::Status{};
        } else {
            return Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return m_superloop_; }

protected:
    // declare all the unit tests here
    SelfTest m_self_test_;
    LibcTest m_libc_test_;
    TickTest m_tick_test_;
    StackTest m_stack_test_;
    jarnax::SuperLoop m_superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext my_context;
    return my_context;
}
}    // namespace jarnax