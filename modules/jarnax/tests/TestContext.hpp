#ifndef TEST_CONTEXT_HPP_
#define TEST_CONTEXT_HPP_

#include "jarnax/Context.hpp"

namespace jarnax {

class GlobalContext : public Context {
public:
    GlobalContext()
        : loop_{jarnax::GetTicker()} {}
    core::Status Initialize() override { return core::Status{}; }
    SuperLoop &GetSuperLoop(void) override { return loop_; }

protected:
    SuperLoop loop_;
};

Context &GetContext() {
    static GlobalContext my_context;
    return my_context;
}

}    // namespace jarnax

#endif // TEST_CONTEXT_HPP_