#include "BoardContext.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Monitor.hpp"
#include "jarnax/Ticker.hpp"

#include "CyphalApp.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : board_context_{jarnax::GetBoardContext()}
        , superloop_{jarnax::GetTicker()}
        , monitor_{board_context_.GetTimer(), board_context_.GetStatusIndicator(), board_context_.GetErrorIndicator()}
        , cyphal_app_{jarnax::GetTicker(), board_context_} {}

    virtual ~GlobalContext() = default;

    Status Initialize(void) override {
        bool result = true;
        result &= superloop_.Enlist(monitor_);
        result &= superloop_.Enlist(board_context_.GetEthernet());
        result &= superloop_.Enlist(board_context_.GetLan8742aDriver());
        result &= superloop_.Enlist(board_context_.GetConsole());
        result &= superloop_.Enlist(cyphal_app_);
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    jarnax::BoardContext& board_context_;
    jarnax::SuperLoop superloop_;
    jarnax::Monitor monitor_;
    nucleo::cyphal::CyphalApp cyphal_app_;
};

namespace jarnax {

core::Container<GlobalContext> global_context;

Context& GetContext(void) {
    if (not global_context) {
        global_context.emplace();
    }
    return *global_context;
}
}    // namespace jarnax
