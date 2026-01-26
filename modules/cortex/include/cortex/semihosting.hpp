#ifndef CORTEX_M_SEMIHOSTING_HPP
#define CORTEX_M_SEMIHOSTING_HPP

/// @file
/// ARM Cortex-M Semihosting Interface

#include <core/Span.hpp>
#include <core/Units.hpp>

#include <cstdint>
#include "cortex/thumb.hpp"

namespace cortex {

/// @brief The Semihosting API
/// @see https://developer.arm.com/documentation/dui0205/f/semihosting/semihosting-swis
namespace semihosting {

/// File handle type for semihosting operations
using Handle = std::int32_t;

/// Invalid file handle constant
constexpr static Handle InvalidHandle{-1};

/// Result codes for semihosting operations
enum class Result : std::int32_t {
    Success = 0,
    Failure = -1,
};

/// The modes of file access via the Open API.
enum class Mode : std::uint32_t {
    Read = 0,
    ReadBinary = 1,
    ReadWrite = 2,
    ReadWriteBinary = 3,
    WriteTruncate = 4,
    WriteTruncateBinary = 5,
    WriteReadTruncate = 6,
    WriteReadTruncateBinary = 7,
    Append = 8,
    AppendBinary = 9,
    AppendPlus = 10,
    AppendPlusBinary = 11,
};

/// Checks if the debugger is connected.
bool IsConnected(void);

/// Opens a file and returns a handle.
/// @param name The span of the name of the file to open.
/// @param mode The mode to open the file in.
Handle Open(core::Span<char const> name, Mode mode);

/// Closes a file.
/// @param handle The handle of the file to close.
/// @return 0 on success, -1 on error.
Result Close(Handle handle);

/// Writes data to a file.
/// @param handle The handle of the file to write to.
/// @param buffer The data to write.
/// @param len The length of the data to write.
/// @return The number of bytes written, or -1 on error.
Result Write(Handle handle, core::Span<char const> buffer);

/// Writes a single character to a file
/// @param c The character to write.
void Write(char c);

/// Writes a string to a file.
/// @param string The string to write.
void Write(const char string[]);

/// Reads data from a file.
/// @param handle The handle of the file to read from.
/// @param buffer The buffer to read the data into.
/// @param len The length of the data to read.
/// @return The number of bytes read, or -1 on error.
Result Read(Handle handle, core::Span<char> buffer);

/// Reads a character from a file.
char Read(void);

/// Checks if a value is an error.
/// @return True if the value is an error, false otherwise.
bool IsError(int32_t value);

/// Checks if a file handle is a TTY.
/// @param handle The handle of the file to check.
/// @return True if the file is a TTY, false otherwise.
bool IsTTY(int handle);

/// Seeks to a position in a file.
/// @param handle The handle of the file to seek in.
/// @param position The position to seek to.
/// @return The new position on success, or -1 on error.
Result Seek(Handle handle, uint32_t position);

/// Gets the length of a file.
/// @param handle The handle of the file to get the length of.
/// @return The length of the file, or -1 on error.
int32_t Length(Handle handle);

/// Gets A temporary name for a file.
/// @param name[out] The location to store the name of the file
/// @param id The ID of the temporary file.
Result TempName(core::Span<char const> name, uint32_t id);

/// Removes a file from the Host File System
/// @param name The span of the name of the file to remove
Result Remove(core::Span<char const> name);

/// Renames a file on the Host File System
/// @param old_file The span of the current file name
/// @param new_file The span of the new file name
/// @return 0 on success, -1 on error
Result Rename(core::Span<char const> old_file, core::Span<char const> new_file);

/// @return The number of Seconds since the start of Execution
core::units::Seconds Clock();

/// @return The current time in seconds since the epoch.
core::units::Seconds Time();

/// Executes a command on the host system
/// @param command The command to execute on the host
/// @return 0 on success, -1 on error
Result System(core::Span<char const> command);

/// @return The host system errno value.
int32_t Errno();

/// @return The command line given to the Debugger to hand off to the program
uint32_t GetCommandLine(core::Span<char> buffer);

/// @brief Information about the heap and stack blocks
struct BlockInfo {
    uint32_t heap_base;
    uint32_t heap_limit;
    uint32_t stack_base;
    uint32_t stack_limit;
};

/// @param[out] info The block information to fill in
void HeapInfo(BlockInfo*& info);

/// @param[out] ticks the elapsed ticks since the system started.
/// @return 0 on success , -1 on failure.
Result ElapsedTicks(uint64_t& ticks);

/// @return the host tick frequency.
/// @retval 0xFF'FF'FF'FF indicates an error.
uint32_t TickFrequency(void);

/// Exception codes for semihosting exception reporting
enum class Exception : int32_t {
    // Hardware Exceptions
    BranchToZero = 0x2'00'00U,            ///< The PC was branched to address 0
    UndefinedInstruction = 0x2'00'01U,    ///< The instruction is not defined
    SoftwareInterrupt = 0x2'00'02U,       ///< A software interrupt was generated
    PrefetchAbort = 0x2'00'03U,           ///< A prefetch abort occurred
    DataAbort = 0x2'00'04U,               ///< A data abort occurred
    Address = 0x2'00'05U,                 ///< An address error occurred
    Interrupt = 0x2'00'06U,               ///< An interrupt was triggered
    FastInterrupt = 0x2'00'07U,           ///< A fast interrupt was triggered
    // Software Exceptions
    Breakpoint = 0x2'00'20U,          ///< A breakpoint was triggered
    Watchpoint = 0x2'00'21U,          ///< A watchpoint was triggered
    StepComplete = 0x2'00'22U,        ///< A step complete event occurred
    RuntimeError = 0x2'00'23U,        ///< A runtime error occurred
    InternalError = 0x2'00'24U,       ///< An internal error occurred
    UserInterruption = 0x2'00'25U,    ///< A user interruption occurred
    ApplicationExit = 0x2'00'26U,     ///< The application has exited
    StackOverflow = 0x2'00'27U,       ///< A stack overflow occurred
    DivisionByZero = 0x2'00'28U,      ///< A division by zero occurred
    OsSpecific = 0x2'00'29U,          ///< OS-specific error occurred
};

/// Reports an Exception over Semihosting
/// @param exception The exception to report.
void Report(Exception exception);

/// Not a direct Semihosting call, but will emit the output over Semihosting
void Print(char const format[], ...);

/// Not a direct Semihosting call, but will emit the output over Semihosting
Result Print(Handle handle, char const format[], ...);

}    // namespace semihosting
}    // namespace cortex

#endif    // CORTEX_M_SEMIHOSTING_HPP
