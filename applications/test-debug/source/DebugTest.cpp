#include "DebugTest.hpp"
#include "board.hpp"
#include "cortex/mcu.hpp"
#include "cortex/semihosting.hpp"
#include "jarnax/Assertion.hpp"
#include "memory.h"

using namespace core::units;

DebugTest::DebugTest()
    : countdown_{jarnax::GetBoardContext().GetTimer(), core::units::ConvertToIota(core::units::MilliSeconds(1000))}
    , one_time_{true}
    , handle_{cortex::semihosting::InvalidHandle}
    , readme_{cortex::semihosting::InvalidHandle} {}

bool DebugTest::Execute() {
    if (one_time_) {
        uint32_t frequency = cortex::semihosting::TickFrequency();
        jarnax::print("Host Tick Freq=%lu\r\n", frequency);
        auto clock = cortex::semihosting::Clock();
        jarnax::print("Host Clock=%f\r\n", static_cast<double>(clock.value()));
        auto secs = cortex::semihosting::Time();
        jarnax::print("Host Time=%f\r\n", static_cast<double>(secs.value()));
        one_time_ = false;
        core::Span<char> commandline{commandline_, sizeof(commandline_)};
        cortex::semihosting::GetCommandLine(commandline);
        jarnax::print("Command Line: %s\r\n", commandline_);
    }

    if (handle_ == cortex::semihosting::InvalidHandle) {
        core::Span<char const> filename{"console.txt"};
        core::Span<char const> old_file{"console.old.txt"};
        cortex::semihosting::Remove(old_file);
        cortex::semihosting::Rename(filename, old_file);
        handle_ = cortex::semihosting::Open(filename, cortex::semihosting::Mode::WriteReadTruncate);
    }

    if (readme_ == cortex::semihosting::InvalidHandle) {
        core::Span<char const> README{"README.md"};
        readme_ = cortex::semihosting::Open(README, cortex::semihosting::Mode::Read);
    }

    if (countdown_.IsExpired()) {
        char buffer[256U];
        core::Span<char> span(buffer);
        cortex::swo::emit(cortex::swo::Port::Errors, "[0] This is a test string\r\n");
        cortex::swo::emit(cortex::swo::Port::System, "[1] This is a test string\r\n");
        cortex::semihosting::Print(handle_, "This is a test string with no varargs\r\n");
        cortex::semihosting::Close(handle_);
        handle_ = cortex::semihosting::InvalidHandle;
        cortex::semihosting::Print("This is a test string to the terminal? PI=%f\r\n", static_cast<double>(3.14f));    // to the Terminal in Ozone?
        cortex::semihosting::Read(readme_, span);
        jarnax::print("Read from README:\r\n%s\r\n", buffer);
        countdown_.Reset();
    }
    return true;
}
