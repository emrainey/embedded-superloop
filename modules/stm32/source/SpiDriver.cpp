#include "stm32/SpiDriver.hpp"

namespace stm32 {

SpiDriver::SpiDriver(stm32::registers::SerialPeripheralInterface volatile& spi)
    : jarnax::spi::Driver{static_cast<jarnax::spi::Transactor&>(*this)}
    , spi_{spi} {
}

core::Status SpiDriver::Initialize(Hertz peripheral_frequency, Hertz desired_spi_clock_frequency) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Verify(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Start(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Check(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

core::Status SpiDriver::Cancel(jarnax::spi::Transaction& transaction) {
    // do nothing
    return core::Status{core::Result::Success, core::Cause::State};
}

}  // namespace stm32