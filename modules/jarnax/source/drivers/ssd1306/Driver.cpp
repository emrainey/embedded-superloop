/// @file
/// The SSD1306 Driver implementation

#include "memory.hpp"
#include "jarnax/drivers/ssd1306/Driver.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

Driver::Driver(jarnax::Timer& timer, jarnax::i2c::Driver& i2c_driver, core::Allocator& allocator)
    : timer_{timer}
    , i2c_driver_{i2c_driver}
    , i2c_buffer_{sizeof(::ssd1306::Image128x32), allocator}
    , i2c_transaction_{timer}
    , address_{}    // Default I2C address for SSD1306
    , allocator_{allocator}
    , image_{}
    , screen_{image_}
    , state_machine_{*this}
    , next_event_{Event::None}
    , powered_{false}
    , updated_{false} {
}

core::Status Driver::Initialize(jarnax::i2c::Address address) {
    address_ = address;
    return core::Status{core::Result::Success, core::Cause::State};    // Initialization successful
}

::ssd1306::Image128x32& Driver::GetImage(void) {
    return image_;
}

::ssd1306::Screen128x32& Driver::GetScreen(void) {
    return screen_;
}

void Driver::Update(void) {
    updated_ = false;               // Reset the updated state
    next_event_ = Event::Update;    // Set the next event to Update
}

bool Driver::IsUpdated(void) const {
    return updated_;    // Return the updated state
}

bool Driver::Execute() {
    state_machine_.Process(next_event_);    // Process the state machine with no events
    next_event_ = Event::None;              // Reset the next event after processing
    return true;                            // Always return true to indicate the loop should continue
}

bool Driver::IsPresent(void) const {
    // assume for now there is always an SSD1306 present
    return true;
}

core::Status Driver::Prepare(CommandSequence sequence) {
    // Prepare the command sequence for the SSD1306
    if (i2c_transaction_.IsUninitialized()) {
        i2c_transaction_.address.whole = address_.whole;      // Set the I2C address
        i2c_transaction_.desired_count = sequence.count();    // Set the desired count to the size of the command sequence
        i2c_transaction_.actual_count = 0U;                   // Reset the actual count
        {                                                     // limit the scope of the span to avoid dangling pointers
            auto span = i2c_buffer_.as_span().subspan(0, i2c_transaction_.desired_count);
            memory::copy(span.data(), sequence.data(), sequence.count());    // Copy the command sequence into the I2C buffer
        }
        i2c_transaction_.buffer = std::move(i2c_buffer_);                         // Set the buffer for the transaction
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Initialized);    // Mark the transaction as initialized
        return core::Status{core::Result::Success, core::Cause::State};           // Return success status
    }
    return core::Status{core::Result::NotReady, core::Cause::State};    // If already initialized, return not ready
}

core::Status Driver::Issue(void) {
    // Issue the prepared command sequence to the SSD1306
    return i2c_driver_.Schedule(&i2c_transaction_);
}

core::Status Driver::AreCommandsComplete(void) const {
    // Check if the commands issued to the SSD1306 are complete
    return i2c_transaction_.IsComplete() ? core::Status{core::Result::Success, core::Cause::State}
                                         : core::Status{core::Result::Busy, core::Cause::State};
}

void Driver::OnEvent(Event event, core::Status status) {
    // Handle events from the state machine
    if (event == Event::PowerOn) {
        powered_ = true;
    } else if (event == Event::PowerOff) {
        powered_ = false;
    } else if (event == Event::Update) {
        updated_ = true;    // Mark that an update has occurred
    } else if (event == Event::ErrorOccurred) {
        // Handle error state
        jarnax::print("SSD1306 Error:", status);
    }
    // Log the event and status if needed
}

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax
