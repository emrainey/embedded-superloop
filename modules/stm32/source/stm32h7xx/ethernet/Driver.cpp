#include "stm32/h7xx/ethernet/Driver.hpp"
#include "stm32/peripherals.hpp"

namespace {    // anonymous namespace for private helper functions and definitions

bool OwnBitCorrect() {
    stm32::ethernet::dma::Descriptor d0;
    d0.transmit_read.own = 1;
    bool read = (d0.des[3] & (1U << 31)) != 0;
    stm32::ethernet::dma::Descriptor d1;
    d1.receive_read.own = 1;
    bool write = (d1.des[3] & (1U << 31)) != 0;
    stm32::ethernet::dma::Descriptor d2;
    d2.transmit_write_back.own = 1;
    bool write_back = (d2.des[3] & (1U << 31)) != 0;
    stm32::ethernet::dma::Descriptor d3;
    d3.transmit_context.own = 1;
    bool context = (d3.des[3] & (1U << 31)) != 0;
    return read && write && write_back && context;
}

}    // anonymous namespace

namespace stm32 {
namespace ethernet {

Driver::Driver(core::Allocator& allocator)
    : jarnax::net::ethernet::Driver()
    , jarnax::net::ethernet::Phy()
    , allocator_{allocator} {}

core::Status Driver::Initialize(void) {
    if (not OwnBitCorrect()) {
        return core::Status{core::Result::Failure, core::Cause::Configuration};
    }

    // @TODO Perform the peripheral initialization here, assume the clocks are enabled the device has been reset.

    return core::Status{};
}

bool Driver::Execute(void) {
    return true;
}

core::Status Driver::Configure(Addresses const& addresses) {
    (void)addresses;    // suppress unused parameter warning

    // @TODO do what needs to be done to configure the MAC Addresses with the provided addresses

    return core::Status{};
}

jarnax::net::eui48::Address Driver::GetMacAddress(size_t index) const {
    (void)index;    // suppress unused parameter warning

    // @TODO return the MAC Address of the controller at the specified index. The index should be between 0 and the maximum number of addresses
    // supported by the hardware (as defined by the MaxMACAddressCount constant in the configuration.hpp file).

    return jarnax::net::eui48::Address{};
}

core::Status Driver::Transmit(jarnax::net::ethernet::Frame const*) {
    return core::Status{};
}

core::Status Driver::Receive(jarnax::net::ethernet::Driver::Listener&) {
    return core::Status{};
}

core::Status Driver::Schedule(jarnax::net::ethernet::mdio::Transaction*) {
    return core::Status{};
}

jarnax::net::ethernet::Frame* Driver::Acquire(void) {
    return nullptr;
}

void Driver::Release(jarnax::net::ethernet::Frame* frame) {
    (void)frame;    // suppress unused parameter warning
}

}    // namespace ethernet
}    // namespace stm32
