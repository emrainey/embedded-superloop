/// @file
/// The SSD1306 Driver implementation

#include "jarnax/drivers/ssd1306/Driver.hpp"
#include "memory.hpp"

namespace jarnax {
namespace drivers {
namespace ssd1306 {

Driver::Driver(jarnax::Timer const& timer, jarnax::i2c::Driver& i2c_driver, core::Allocator& allocator)
    : Loopable{}
    , timer_{timer}
    , i2c_driver_{i2c_driver}
    , i2c_buffer_{sizeof(::ssd1306::Image128x32) + 17U, allocator}
    , i2c_transaction_{timer}
    , address_{}
    , allocator_{allocator}
    , image_{}
    , screen_{image_}
    , state_machine_{*this}
    , next_event_{Event::None}
    , powered_{false}
    , updated_{false}
    , statistics_{} {}

core::Status Driver::Initialize(jarnax::i2c::Address address) {
    address_ = address;                                                // Set the I2C address for the SSD1306 display
    next_event_ = Event::PowerOn;                                      // Set the next event to PowerOn
    state_machine_.Enter();                                            // Initialize the state machine to start the powering on process
    return core::Status{core::Result::Success, core::Cause::State};    // Initialization successful
}

core::Status Driver::GetStatus(void) const {
    // Check the status of the SSD1306 display
    if (not powered_) {
        return core::Status{core::Result::NotReady, core::Cause::State};    // Not ready if the display is not powered
    }
    core::Status status = i2c_transaction_.GetStatus();                     // Get the status from the I2C driver
    if (status.IsBusy()) {
        return status;                                                      // If the I2C transaction is busy, return that status
    }
    return core::Status{core::Result::Success, core::Cause::State};         // Otherwise, return success
}

jarnax::ssd1306::Image128x32& Driver::GetImage(void) {
    return image_;
}

jarnax::ssd1306::Screen128x32& Driver::GetScreen(void) {
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

core::Status Driver::Prepare(Sequence sequence) {
    // Prepare the command sequence for the SSD1306
    if (i2c_transaction_.IsUninitialized()) {
        auto now = timer_.GetMicroseconds();                                           // Get the current time
        i2c_transaction_.SetDeadline(now + core::units::MicroSeconds{10'000U});        // Set a deadline for the transaction
        i2c_transaction_.address.whole = address_.whole;                               // Set the I2C address
        i2c_transaction_.desired_count = sequence.count();                             // Set the desired count to the size of the command sequence
        i2c_transaction_.actual_count = 0U;                                            // Reset the actual count
        if (not i2c_buffer_.IsEmpty()) {                                               // limit the scope of the span to avoid dangling pointers
            auto span = i2c_buffer_.as_span().subspan(0, i2c_transaction_.desired_count);
            memory::copy(span.data(), sequence.data(), sequence.size());               // Copy the command sequence into the I2C buffer
            i2c_transaction_.buffer = std::move(i2c_buffer_);                          // Set the buffer for the transaction
        } else {
            statistics_.buffer_invalid++;                                              // Increment the buffer invalid count if the buffer is empty
            return core::Status{core::Result::NotAvailable, core::Cause::Resource};    // If the buffer is empty, return not available
        }
        statistics_.prepared++;
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Initialized);    // Mark the transaction as initialized
        return core::Status{core::Result::Success, core::Cause::State};           // Return success status
    } else {
        jarnax::print("SSD1306 Driver: Prepare called while not uninitialized\r\n");
    }
    return core::Status{core::Result::NotReady, core::Cause::State};    // If already initialized, return not ready
}

core::Status Driver::PrepareRender(Sequence sequence) {
    if (i2c_transaction_.IsUninitialized()) {
        auto now = timer_.GetMicroseconds();                                                     // Get the current time
        i2c_transaction_.SetDeadline(now + core::units::MicroSeconds{100'000U});                 // Set a deadline for the transaction
        i2c_transaction_.address.whole = address_.whole;                                         // Set the I2C address for the transaction
        i2c_transaction_.desired_count = sequence.size() + image_.GetSize();                     // Set the desired count to the size of the image
        i2c_transaction_.actual_count = 0U;                                                      // Reset the actual count
        if (not i2c_buffer_.IsEmpty()) {                                                         // Check if the I2C buffer is not empty
            auto span = i2c_buffer_.as_span().subspan(0, i2c_transaction_.desired_count);
            memory::copy(span.data(), sequence.data(), sequence.size());                         // Copy the command sequence into the I2C buffer
            memory::copy(&span.data()[sequence.count()], image_.GetData(), image_.GetSize());    // Copy the image data into the I2C buffer
            i2c_transaction_.buffer = std::move(i2c_buffer_);                                    // Set the buffer for the transaction
        } else {
            statistics_.buffer_invalid++;                                              // Increment the buffer invalid count if the buffer is empty
            return core::Status{core::Result::NotAvailable, core::Cause::Resource};    // If the buffer is empty, return not available
        }
        statistics_.prepared++;
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Initialized);    // Mark the transaction as initialized
        return core::Status{core::Result::Success, core::Cause::State};           // Return success status
    } else {
        jarnax::print("SSD1306 Driver: PrepareRender called while not uninitialized", i2c_transaction_.GetStatus());
    }
    return core::Status{core::Result::NotReady, core::Cause::State};    // If already initialized, return not ready
}

core::Status Driver::Issue(void) {
    if (i2c_transaction_.IsInitialized()) {
        statistics_.issued++;
        // Issue the prepared command sequence to the SSD1306
        return i2c_driver_.Schedule(&i2c_transaction_);
    } else {
        // If the transaction is not initialized, return an error status
        return core::Status{core::Result::NotReady, core::Cause::State};
    }
}

bool Driver::AreCommandsComplete(core::Status& status) {
    // Check if the commands issued to the SSD1306 are complete
    if (i2c_transaction_.IsComplete()) {
        statistics_.completed++;
        i2c_buffer_ = i2c_transaction_.Relinquish();    // Get the buffer from the completed transaction
        status = i2c_transaction_.GetStatus();          // Get the status of the transaction
        jarnax::print(
            "Transaction took %" PRIu64 " microseconds\r\n", i2c_transaction_.GetDuration().value()
        );                                                           // Log the elapsed time of the transaction
        if (status.IsFailure()) {
            statistics_.failures++;                                  // Increment the failure count if the transaction failed
            jarnax::print("SSD1306 Transaction Error: ", status);    // Log the error if the transaction failed
        } else {
            if constexpr (debug::inform) {
                jarnax::print("SSD1306 Transaction Success: ", status);    // Log the success if the transaction succeeded
            }
        }
        i2c_transaction_.Inform(jarnax::i2c::Transaction::Event::Recycle);    // Inform the transaction that it has been recycled
        return true;
    }
    return false;
}

void Driver::OnEvent(Event event, core::Status status) {
    // Handle events from the state machine
    jarnax::print("SSD1306 Event: %d\r\n", static_cast<int>(event));
    if (status.IsFailure()) {
        status_ = status;                                    // Update the status if the event failed
        jarnax::print("SSD1306 Event Failure: ", status);    // Log the failure status if the event failed
    }
    if (event == Event::PowerOn) {
        powered_ = true;
    } else if (event == Event::PowerOff) {
        powered_ = false;
    } else if (event == Event::Update) {
        updated_ = true;
        statistics_.updated++;
    }
}

}    // namespace ssd1306
}    // namespace drivers
}    // namespace jarnax
