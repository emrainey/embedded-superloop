#ifndef JARNAX_NET_ETHERNET_LAN8742A_HPP
#define JARNAX_NET_ETHERNET_LAN8742A_HPP

#include <cstdint>
#include "core/StateMachine.hpp"
#include "core/Status.hpp"
#include "core/Units.hpp"
#include "jarnax/CountDown.hpp"
#include "jarnax/Driver.hpp"
#include "jarnax/net/ethernet/Phy.hpp"

namespace jarnax {
namespace net {
namespace ethernet {
namespace lan8742a {

/// @brief The default polling interval for checking PHY status (500 ms)
constexpr static core::units::MilliSeconds DefaultPollingInterval{500U};

/// @brief The states of the LAN8742A PHY state machine
enum class State : std::uint8_t {
    Undefined = 0,               ///< Undefined state, required by the state machine
    Idling,                      ///< Device is idle, waiting to be initialized
    Resetting,                   ///< Device is issuing a software reset
    AwaitingReset,               ///< Device is waiting for the software reset to complete
    ConfiguringAutoNegotiation,  ///< Device is enabling/restarting auto-negotiation
    AwaitingLink,                ///< Device is waiting for the physical link to be established
    PollingLinkStatus,           ///< Device is reading link status register
    ReadingLinkStatus,           ///< Device is reading speed/duplex status
    ConfiguringMac,              ///< Device is configuring the MAC operating mode
    LinkUp,                      ///< Device link is active and configured
    Error                        ///< Device is in error state
};

/// @brief The events that can occur in the LAN8742A state machine
enum class Event : std::uint8_t {
    None = 0,      ///< No event, used to cycle the state machine
    Initialize,    ///< Initialize the state machine / start state machine
    Reset          ///< Reset the state machine / PHY
};

/// @brief Callback interface for the LAN8742A state machine to read/write registers and handle events
class Callback {
public:
    /// Start a read transaction from a PHY register
    virtual core::Status StartRead(uint8_t reg) = 0;
    /// Start a write transaction to a PHY register
    virtual core::Status StartWrite(uint8_t reg, uint16_t value) = 0;
    /// Get the value of a completed read transaction
    virtual core::Status GetValue(uint16_t& value) = 0;
    /// Callback when link is resolved and up
    virtual void OnLinkUp(bool speed_100m, bool full_duplex) = 0;
    /// Callback when link is lost
    virtual void OnLinkDown() = 0;
    /// Callback when a transaction or driver error occurs
    virtual void OnError(core::Status status) = 0;

protected:
    ~Callback() = default;
};

/// @brief State machine for the LAN8742A PHY
class StateMachine : public core::StateMachine<State>, protected core::StateMachine<State>::Callback {
public:
    StateMachine(jarnax::Timer const& timer, core::units::Iota polling_interval, lan8742a::Callback& callback);
    virtual ~StateMachine() = default;

    /// Process an event in the state machine
    void Process(Event event);
    /// Check if the state machine is idling
    bool IsIdling() const;
    /// Check if the state machine has a resolved link
    bool IsLinkUp() const;

protected:
    void OnEnter() override;
    void OnExit() override;
    void OnEntry(State state) override;
    State OnCycle(State state) override;
    void OnExit(State state) override;
    void OnTransition(State from, State to) override;

private:
    lan8742a::Callback& callback_;
    Event event_;
    core::Status status_;
    jarnax::CountDown polling_timer_;
    bool speed_100m_{false};
    bool full_duplex_{false};
};

/// @brief Driver class wrapping the LAN8742A StateMachine and MDIO transactions
class Driver final : public jarnax::Driver,
                     protected Callback,
                     protected jarnax::net::ethernet::mdio::Transaction::CompletionListener {
public:
    Driver(jarnax::Timer const& timer, core::units::Iota polling_interval, jarnax::net::ethernet::Phy& phy, uint8_t phy_address = 0U);
    virtual ~Driver() = default;

    // jarnax::Driver Interface
    core::Status Initialize() override;
    bool Execute() override;

    /// Returns true if the link is resolved and active
    bool IsLinkUp() const;

protected:
    // Callback implementation
    core::Status StartRead(uint8_t reg) override;
    core::Status StartWrite(uint8_t reg, uint16_t value) override;
    core::Status GetValue(uint16_t& value) override;
    void OnLinkUp(bool speed_100m, bool full_duplex) override;
    void OnLinkDown() override;
    void OnError(core::Status status) override;

    // mdio::Transaction::CompletionListener implementation
    void OnTransactionCompleted(jarnax::net::ethernet::mdio::Transaction& transaction) override;

private:
    jarnax::net::ethernet::Phy& phy_;
    uint8_t const phy_address_;
    jarnax::net::ethernet::mdio::Transaction transaction_;
    bool completion_handed_off_{false};
    StateMachine state_machine_;
    Event event_{Event::None};
};

}  // namespace lan8742a
}  // namespace ethernet
}  // namespace net
}  // namespace jarnax

#endif  // JARNAX_NET_ETHERNET_LAN8742A_HPP
