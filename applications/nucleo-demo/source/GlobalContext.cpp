#include "BoardContext.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Monitor.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/console/Service.hpp"
#include "jarnax/net/Interface.hpp"

#include "Demo.hpp"
#include "jarnax/net/ip/v4/Address.hpp"

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
        , ip_address_{192U, 168U, 3U, 3U}
        , subnet_mask_{jarnax::net::ip::v4::C::mask}
        , network_interface_{board_context_.GetEthernet(), board_context_.GetDefinedMacAddress(), ip_address_, subnet_mask_}
        , demo_{jarnax::GetTicker(), board_context_, network_interface_} {}

    /// Default Destructor
    virtual ~GlobalContext() = default;

    Status Initialize(void) override {
        bool result = true;
        result &= superloop_.Enlist(monitor_);
        result &= superloop_.Enlist(board_context_.GetI2cA());
        result &= superloop_.Enlist(board_context_.GetI2cB());
        result &= superloop_.Enlist(board_context_.GetSpiA());
        result &= superloop_.Enlist(board_context_.GetUsartB());
        result &= superloop_.Enlist(board_context_.GetEthernet());    // Pumps the PHY ONLY
        result &= superloop_.Enlist(board_context_.GetLan8742aDriver());
        result &= superloop_.Enlist(board_context_.GetConsole());
        result &= superloop_.Enlist(network_interface_);    // Pumps the network interface & Frames
        result &= superloop_.Enlist(demo_);
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    jarnax::BoardContext& board_context_;    ///< Convenience reference to the board context
    jarnax::SuperLoop superloop_;            ///< The super loop instance for this application
    jarnax::Monitor monitor_;                ///< A monitor service
    jarnax::net::ip::v4::Address ip_address_;
    jarnax::net::ip::v4::Address subnet_mask_;
    jarnax::net::Interface network_interface_;    ///< The Network Interface
    Demo demo_;                                   ///< The demonstration instance
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
