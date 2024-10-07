
#include "jarnax/Context.hpp"

#include "Task.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : m_task_{}
        , m_superloop_{jarnax::GetTicker()} {}

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(m_task_);
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return m_superloop_; }

protected:
    Task m_task_;
    jarnax::SuperLoop m_superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext my_context;
    return my_context;
}
}    // namespace jarnax