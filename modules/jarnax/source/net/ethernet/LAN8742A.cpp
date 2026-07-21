#include "jarnax/net/ethernet/LAN8742A.hpp"
#include "jarnax/print.hpp"

namespace jarnax {
namespace net {
namespace ethernet {
namespace lan8742a {

// Register addresses (avoiding kCamelCase constants per AGENTS.md rules)
constexpr uint8_t register_bmcr = 0U;
constexpr uint8_t register_bmsr = 1U;
constexpr uint8_t register_phy_special_control_status = 31U;

// Register bit definitions
constexpr uint16_t bmcr_reset = 0x8000U;
constexpr uint16_t bmcr_auto_negotiation_enable = 0x1000U;
constexpr uint16_t bmcr_restart_auto_negotiation = 0x0200U;

constexpr uint16_t bmsr_auto_negotiation_complete = 0x0020U;
constexpr uint16_t bmsr_link_status = 0x0004U;

constexpr uint16_t special_duplex_mask = 0x0010U;  // Bit 4 of Register 31 (1 = Full, 0 = Half)
constexpr uint16_t special_speed_mask = 0x0008U;   // Bit 3 of Register 31 (1 = 100M, 0 = 10M)

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// StateMachine Implementation
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

StateMachine::StateMachine(jarnax::Timer const& timer, core::units::Iota polling_interval, lan8742a::Callback& callback)
    : core::StateMachine<State>{*this, State::Idling}
    , core::StateMachine<State>::Callback{}
    , callback_{callback}
    , event_{Event::None}
    , status_{}
    , polling_timer_{timer, polling_interval} {}

void StateMachine::Process(Event event) {
    if (not IsFinal()) {
        event_ = event;
        RunOnce();
        event_ = Event::None;
    }
}

bool StateMachine::IsIdling() const {
    return Is(State::Idling);
}

bool StateMachine::IsLinkUp() const {
    return Is(State::LinkUp);
}

void StateMachine::OnEnter() {}

void StateMachine::OnExit() {}

void StateMachine::OnEntry(State state) {
    if (state == State::Resetting) {
        status_ = callback_.StartWrite(register_bmcr, bmcr_reset);
    } else if (state == State::AwaitingReset) {
        status_ = callback_.StartRead(register_bmcr);
    } else if (state == State::ConfiguringAutoNegotiation) {
        status_ = callback_.StartWrite(register_bmcr, bmcr_auto_negotiation_enable | bmcr_restart_auto_negotiation);
    } else if (state == State::AwaitingLink) {
        polling_timer_.Reset();
    } else if (state == State::PollingLinkStatus) {
        status_ = callback_.StartRead(register_bmsr);
    } else if (state == State::ReadingLinkStatus) {
        status_ = callback_.StartRead(register_phy_special_control_status);
    } else if (state == State::ConfiguringMac) {
        callback_.OnLinkUp(speed_100m_, full_duplex_);
    } else if (state == State::LinkUp) {
        polling_timer_.Reset();
    } else if (state == State::Error) {
        callback_.OnError(status_);
    }
}

State StateMachine::OnCycle(State state) {
    if (state == State::Idling) {
        if (event_ == Event::Initialize or event_ == Event::Reset) {
            state = State::Resetting;
        }
    } else if (state == State::Resetting) {
        if (status_.IsSuccess()) {
            uint16_t dummy = 0U;
            status_ = callback_.GetValue(dummy);
            if (status_.IsSuccess()) {
                state = State::AwaitingReset;
            } else if (status_ == core::Result::NotReady) {
                status_ = core::Status{};  // Keep waiting
            } else {
                state = State::Error;
            }
        } else {
            state = State::Error;
        }
    } else if (state == State::AwaitingReset) {
        if (status_.IsSuccess()) {
            uint16_t bmcr_val = 0U;
            status_ = callback_.GetValue(bmcr_val);
            if (status_.IsSuccess()) {
                if ((bmcr_val & bmcr_reset) != 0U) {
                    // Reset is still in progress, request another read
                    status_ = callback_.StartRead(register_bmcr);
                } else {
                    state = State::ConfiguringAutoNegotiation;
                }
            } else if (status_ == core::Result::NotReady) {
                status_ = core::Status{};  // Keep waiting
            } else {
                state = State::Error;
            }
        } else {
            state = State::Error;
        }
    } else if (state == State::ConfiguringAutoNegotiation) {
        if (status_.IsSuccess()) {
            uint16_t dummy = 0U;
            status_ = callback_.GetValue(dummy);
            if (status_.IsSuccess()) {
                state = State::AwaitingLink;
            } else if (status_ == core::Result::NotReady) {
                status_ = core::Status{};  // Keep waiting
            } else {
                state = State::Error;
            }
        } else {
            state = State::Error;
        }
    } else if (state == State::AwaitingLink) {
        if (event_ == Event::Reset) {
            state = State::Resetting;
        } else if (polling_timer_.IsExpired()) {
            state = State::PollingLinkStatus;
        }
    } else if (state == State::PollingLinkStatus) {
        if (status_.IsSuccess()) {
            uint16_t bmsr_val = 0U;
            status_ = callback_.GetValue(bmsr_val);
            if (status_.IsSuccess()) {
                bool const link_up = (bmsr_val & bmsr_link_status) != 0U;
                bool const auto_neg_complete = (bmsr_val & bmsr_auto_negotiation_complete) != 0U;

                if (link_up) {
                    if (Was(State::AwaitingLink)) {
                        if (auto_neg_complete) {
                            state = State::ReadingLinkStatus;
                        } else {
                            // Link is up but AN not complete, continue polling
                            state = State::AwaitingLink;
                        }
                    } else if (Was(State::LinkUp)) {
                        // Link is still up and healthy
                        state = State::LinkUp;
                    } else {
                        state = State::AwaitingLink;
                    }
                } else {
                    if (Was(State::LinkUp)) {
                        callback_.OnLinkDown();
                    }
                    state = State::AwaitingLink;
                }
            } else if (status_ == core::Result::NotReady) {
                status_ = core::Status{};  // Keep waiting
            } else {
                state = State::Error;
            }
        } else {
            state = State::Error;
        }
    } else if (state == State::ReadingLinkStatus) {
        if (status_.IsSuccess()) {
            uint16_t special_val = 0U;
            status_ = callback_.GetValue(special_val);
            if (status_.IsSuccess()) {
                speed_100m_ = (special_val & special_speed_mask) != 0U;
                full_duplex_ = (special_val & special_duplex_mask) != 0U;
                state = State::ConfiguringMac;
            } else if (status_ == core::Result::NotReady) {
                status_ = core::Status{};  // Keep waiting
            } else {
                state = State::Error;
            }
        } else {
            state = State::Error;
        }
    } else if (state == State::ConfiguringMac) {
        state = State::LinkUp;
    } else if (state == State::LinkUp) {
        if (event_ == Event::Reset) {
            state = State::Resetting;
        } else if (polling_timer_.IsExpired()) {
            state = State::PollingLinkStatus;
        }
    } else if (state == State::Error) {
        if (event_ == Event::Reset or event_ == Event::Initialize) {
            state = State::Resetting;
        }
    }
    return state;
}

void StateMachine::OnExit(State state) {
    static_cast<void>(state);
}

void StateMachine::OnTransition(State from, State to) {
    static_cast<void>(from);
    static_cast<void>(to);
}

//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
// Driver Implementation
//-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

Driver::Driver(jarnax::Timer const& timer, core::units::Iota polling_interval, jarnax::net::ethernet::Phy& phy, uint8_t phy_address)
    : jarnax::Driver{}
    , Callback{}
    , jarnax::net::ethernet::mdio::Transaction::CompletionListener{}
    , phy_{phy}
    , phy_address_{phy_address}
    , transaction_{timer}
    , completion_handed_off_{false}
    , state_machine_{timer, polling_interval, *this}
    , event_{Event::None} {}

core::Status Driver::Initialize() {
    state_machine_.Enter();
    event_ = Event::Initialize;
    return core::Status{};
}

bool Driver::Execute() {
    if (state_machine_.IsFinal()) {
        state_machine_.Enter();
    }
    state_machine_.Process(event_);
    event_ = Event::None;
    return true;
}

bool Driver::IsLinkUp() const {
    return state_machine_.IsLinkUp();
}

core::Status Driver::StartRead(uint8_t reg) {
    if (transaction_.IsResetable()) {
        transaction_.Reset();
    }
    if (not transaction_.IsUninitialized()) {
        return core::Status{core::Result::NotReady, core::Cause::State};
    }
    transaction_.clause = jarnax::net::ethernet::mdio::Clause::_22;
    transaction_.operation = jarnax::net::ethernet::mdio::Operation::Read;
    transaction_.phy_address = static_cast<uint16_t>(phy_address_ & 0x1FU);
    transaction_.register_address = static_cast<uint16_t>(reg & 0x1FU);
    transaction_.data = 0U;

    transaction_.SetCompletionListener(this);
    transaction_.Inform(jarnax::net::ethernet::mdio::Transaction::Event::Initialized);

    return phy_.Schedule(&transaction_);
}

core::Status Driver::StartWrite(uint8_t reg, uint16_t value) {
    if (transaction_.IsResetable()) {
        transaction_.Reset();
    }
    if (not transaction_.IsUninitialized()) {
        return core::Status{core::Result::NotReady, core::Cause::State};
    }
    transaction_.clause = jarnax::net::ethernet::mdio::Clause::_22;
    transaction_.operation = jarnax::net::ethernet::mdio::Operation::Write;
    transaction_.phy_address = static_cast<uint16_t>(phy_address_ & 0x1FU);
    transaction_.register_address = static_cast<uint16_t>(reg & 0x1FU);
    transaction_.data = value;

    transaction_.SetCompletionListener(this);
    transaction_.Inform(jarnax::net::ethernet::mdio::Transaction::Event::Initialized);

    return phy_.Schedule(&transaction_);
}

core::Status Driver::GetValue(uint16_t& value) {
    if (transaction_.IsComplete()) {
        if (not completion_handed_off_) {
            return core::Status{core::Result::NotReady, core::Cause::State};
        }
        value = transaction_.data;
        transaction_.Inform(jarnax::net::ethernet::mdio::Transaction::Event::Recycle);
        completion_handed_off_ = false;
        return core::Status{};
    }
    return core::Status{core::Result::NotReady, core::Cause::State};
}

void Driver::OnLinkUp(bool speed_100m, bool full_duplex) {
    jarnax::print("LAN8742A: Link is UP - Speed: %s, Duplex: %s\r\n",
                  speed_100m ? "100Mbps" : "10Mbps",
                  full_duplex ? "Full" : "Half");
    phy_.ConfigureMacLink(speed_100m, full_duplex);
}

void Driver::OnLinkDown() {
    jarnax::print("LAN8742A: Link is DOWN\r\n");
}

void Driver::OnError(core::Status status) {
    jarnax::print("LAN8742A: Error occurred, status code: %u\r\n", static_cast<unsigned>(status.GetResult()));
}

void Driver::OnTransactionCompleted(jarnax::net::ethernet::mdio::Transaction& transaction) {
    if (&transaction == &transaction_) {
        completion_handed_off_ = true;
    }
}

}  // namespace lan8742a
}  // namespace ethernet
}  // namespace net
}  // namespace jarnax
