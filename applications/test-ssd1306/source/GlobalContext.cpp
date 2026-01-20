#include "BoardContext.hpp"
#include "jarnax/Context.hpp"
#include "jarnax/Monitor.hpp"

#include "DisplayTest.hpp"

using core::Cause;
using core::Result;
using core::Status;
using jarnax::Context;
using jarnax::SuperLoop;

class GlobalContext : public Context {
public:
    GlobalContext()
        : display_driver_{jarnax::GetBoardContext().GetTimer(), jarnax::GetBoardContext().GetI2cDriver(), jarnax::GetBoardContext().GetDmaAllocator()}
        , test_{display_driver_}
        , monitor_{jarnax::GetBoardContext().GetTimer(), jarnax::GetBoardContext().GetStatusIndicator(), jarnax::GetBoardContext().GetErrorIndicator()}
        , superloop_{jarnax::GetTicker()} {}

    /// Default Destructor
    virtual ~GlobalContext() = default;

    Status Initialize(void) override {
        bool result = true;
        result &= GetSuperLoop().Enlist(monitor_);
        result &= GetSuperLoop().Enlist(test_);
        result &= GetSuperLoop().Enlist(display_driver_);
        result &= GetSuperLoop().Enlist(jarnax::GetBoardContext().GetI2cDriver());
        // initialize the display driver with the default I2C address
        jarnax::i2c::Address address{::ssd1306::DefaultAddress};
        result &= display_driver_.Initialize(address).IsSuccess();
        if (result) {
            return core::Status{};
        } else {
            return core::Status{Result::Failure, Cause::Configuration};
        }
    }

    SuperLoop& GetSuperLoop(void) override { return superloop_; }

protected:
    // since this is not in the board context, it has to be in the GlobalContext
    jarnax::drivers::ssd1306::Driver display_driver_;
    DisplayTest test_;
    jarnax::Monitor monitor_;
    jarnax::SuperLoop superloop_;
};

namespace jarnax {
Context& GetContext(void) {
    static GlobalContext global_context;
    return global_context;
}
}    // namespace jarnax
