#ifndef TEST_SPI_HPP
#define TEST_SPI_HPP

#include <memory.hpp>
#include "BoardContext.hpp"
#include "core/Allocator.hpp"
#include "jarnax/Copier.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Indicator.hpp"
#include "jarnax/Loopable.hpp"
#include "jarnax/Ticker.hpp"
#include "jarnax/Timer.hpp"
#include "jarnax/i2c/Driver.hpp"
#include "ssd1306.hpp"

using jarnax::Loopable;
using jarnax::LoopInfo;
using jarnax::Ticks;

enum class AppState : std::uint8_t {
    Undefined = 0U,
    Identify,
    Waiting,
    Error,
};

class SPITest final : public jarnax::Loopable, protected core::StateMachine<AppState>::Callback {
public:
    SPITest();
    bool Execute() override;

    struct Statistics {
        std::size_t uninitialized{0U};    ///< The number of times the transaction was uninitialized
        std::size_t initialized{0U};      ///< The number of times the transaction was initialized
        std::size_t scheduled{0U};        ///< The number of times the transaction was scheduled
        std::size_t rebuffed{0U};         ///< The number of times the transaction was failed to be scheduled.
        std::size_t complete{0U};         ///< The number of times the transaction was complete
        std::size_t succeeded{0U};        ///< The number of times the transaction was successfully completed
        std::size_t failed{0U};           ///< The number of times the transaction was discarded
    };

protected:
    void InitializeTransaction(void);

    void OnEnter() override;
    void OnEntry(AppState state) override;
    AppState OnCycle(AppState state) override;
    void OnExit(AppState state) override;
    void OnTransition(AppState from, AppState to) override;
    void OnExit() override;

    core::Status TransactionCycle(std::uint8_t command, size_t count);

    jarnax::Ticker& ticker_;
    jarnax::Timer const& timer_;
    jarnax::spi::Driver& spi_driver_;
    jarnax::spi::Transaction spi_transaction_;
    core::Buffer<jarnax::spi::DataUnit> spi_buffer_;
    jarnax::CountDown spi_countdown_;
    core::StateMachine<AppState> state_machine_;
    Statistics stats_;
};

extern SPITest::Statistics* app_statistics;

#endif    // TEST_SPI_HPP
