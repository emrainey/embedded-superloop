#include "cortex/semihosting.hpp"
#include <core/vsnprint.hpp>
#include <cstdarg>
#include <strings.hpp>    // my lib
#include "cortex/types.hpp"
#include "polyfill.hpp"

namespace cortex {
namespace semihosting {

enum class Operation : uint32_t {
    Connected = 0x0,    ///< Segger specific code to check if the debugger is connected
    Open = 0x01,
    Close = 0x02,
    WriteCharacter = 0x03,
    WriteString = 0x04,
    Write = 0x05,
    Read = 0x06,
    ReadCharacter = 0x07,
    IsError = 0x08,
    IsTTY = 0x09,
    Seek = 0x0A,
    // no 0xB
    FileLength = 0x0C,
    TempName = 0x0D,
    Remove = 0x0E,
    Rename = 0x0F,
    Clock = 0x10,
    Time = 0x11,
    System = 0x12,
    Errno = 0x13,
    // No 0x14
    GetCommandLine = 0x15,
    HeapInfo = 0x16,
    EnterSupervisorMode = 0x17,
    ReportException = 0x18,
    // No 0x19 through 0x1F
    Startup = 0x20,
    // No 0x21 through 0xFF
    Elapsed = 0x30,
    TickFrequency = 0x31,
};

bool IsConnected(void) {
    uint32_t ret = static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::Connected), nullptr));
    return (ret == 1U);
}

Handle Open(core::Span<char const> name, Mode mode) {
    struct Args {
        const char* name;
        Mode mode;
        uint32_t len;
    } args{name.data(), mode, static_cast<uint32_t>(name.size())};
    // Use the Thumb instruction to call the semihosting Open API
    Handle handle = static_cast<Handle>(thumb::semihosting(polyfill::to_underlying(Operation::Open), &args));
    return handle;
}

Result Close(Handle handle) {
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Close), &handle));
}

Result Write(Handle handle, core::Span<char const> buffer) {
    struct Args {
        Handle handle;
        void const* buffer;
        uint32_t len;
    } args{handle, buffer.data(), static_cast<uint32_t>(buffer.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Write), &args));
}

Result Read(Handle handle, core::Span<char> buffer) {
    struct Args {
        Handle handle;
        void* buffer;
        uint32_t len;
    } args{handle, buffer.data(), static_cast<uint32_t>(buffer.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Read), &args));
}

void Write(char c) {
    thumb::semihosting(polyfill::to_underlying(Operation::WriteCharacter), &c);
}

void Write(char const string[]) {
    thumb::semihosting(polyfill::to_underlying(Operation::WriteString), string);
}

char Read(void) {
    return static_cast<char>(thumb::semihosting(polyfill::to_underlying(Operation::ReadCharacter), nullptr));
}

Result Seek(Handle handle, uint32_t position) {
    struct Args {
        Handle handle;
        uint32_t position;
    } args{handle, position};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Seek), &args));
}

int32_t Length(Handle handle) {
    return static_cast<int32_t>(thumb::semihosting(polyfill::to_underlying(Operation::FileLength), &handle));
}

Result TempName(core::Span<char const> name, uint8_t id) {
    struct Args {
        char const* name;
        uint32_t id;
        uint32_t length;
    } args{name.data(), id, static_cast<uint32_t>(name.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::TempName), &args));
}

Result Remove(core::Span<char const> name) {
    struct Args {
        char const* name;
        uint32_t length;
    } args{name.data(), static_cast<uint32_t>(name.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Remove), &args));
}

Result Rename(core::Span<char const> old_name, core::Span<char const> new_name) {
    struct Args {
        char const* old_name;
        uint32_t old_length;
        char const* new_name;
        uint32_t new_length;
    } args{old_name.data(), static_cast<uint32_t>(old_name.size()), new_name.data(), static_cast<uint32_t>(new_name.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Rename), &args));
}

int32_t Errno(void) {
    return static_cast<int32_t>(thumb::semihosting(polyfill::to_underlying(Operation::Errno), nullptr));
}

bool IsError(int32_t value) {
    uint32_t ret = static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::IsError), &value));
    return ret != 0;
}

bool IsTTY(int handle) {
    uint32_t ret = static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::IsTTY), &handle));
    return ret != 0;
}

core::units::Seconds Clock(void) {
    uint32_t secs_since_boot = static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::Clock), nullptr));
    return core::units::Seconds{static_cast<float>(secs_since_boot)};
}

core::units::Seconds Time(void) {
    uint32_t centiseconds = static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::Time), nullptr));
    return core::units::Seconds{static_cast<float>(centiseconds) / 100.0f};
}

Result Elapsed(uint64_t& ticks) {
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::Elapsed), &ticks));
}

uint32_t TickFrequency(void) {
    return static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::TickFrequency), nullptr));
}

Result System(core::Span<char const> command) {
    struct Args {
        char const* command;
        uint32_t length;
    } args{command.data(), static_cast<uint32_t>(command.size())};
    return static_cast<Result>(thumb::semihosting(polyfill::to_underlying(Operation::System), &args));
}

uint32_t GetCommandLine(core::Span<char> buffer) {
    struct Args {
        char* buffer;
        uint32_t length;
    } args{buffer.data(), static_cast<uint32_t>(buffer.size())};
    return static_cast<uint32_t>(thumb::semihosting(polyfill::to_underlying(Operation::GetCommandLine), &args));
}

void HeapInfo(BlockInfo*& info) {
    // r1 will have the pointer to the BlockInfo structure?
    static_cast<void>(thumb::semihosting(polyfill::to_underlying(Operation::HeapInfo), &info));
}

void Report(Exception exception) {
    cortex::word r1;
    r1.as_s32[0] = polyfill::to_underlying(exception);
    return static_cast<void>(thumb::semihosting(polyfill::to_underlying(Operation::ReportException), r1.as_pointer));
}

constexpr static size_t semihosting_buffer_size = 256;

void Print(char const format[], ...) {
    static char semihosting_buffer[semihosting_buffer_size];
    va_list args;
    va_start(args, format);
    core::vsnprint(semihosting_buffer, sizeof(semihosting_buffer), format, args);
    va_end(args);
    cortex::semihosting::Write(semihosting_buffer);
}

Result Print(Handle handle, char const format[], ...) {
    static char semihosting_buffer[semihosting_buffer_size];
    va_list args;
    va_start(args, format);
    core::vsnprint(semihosting_buffer, sizeof(semihosting_buffer), format, args);    // Format the string
    core::Span<char const> semihosting_span{semihosting_buffer, strings::length(semihosting_buffer)};
    Result result = cortex::semihosting::Write(handle, semihosting_span);
    va_end(args);
    return result;
}

}    // namespace semihosting
}    // namespace cortex
