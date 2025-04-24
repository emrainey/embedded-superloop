#ifndef JARNAX_PRINT_HPP_
#define JARNAX_PRINT_HPP_

/// @file
/// The Print Interface

#include "compiler.hpp"
#include <cinttypes>
#include "core/Status.hpp"

#ifndef PRIz
/// The format specifier for size_t
/// @note This is a workaround for the fact that size_t is not defined in the C++ standard library
#define PRIz "zu"
#endif

/// The namespace of the system level functions
namespace jarnax {

/// @brief Prints the information of a status object
/// @param source Some literal string to identify the source of the status
/// @param status The status object to print
void print(char const* const source, core::Status status);

/// @brief Primitive Printing Facility.
/// Supports %s, %d, %i, %u, %x, %p, %b (binary), %f for float ONLY (no doubles!)
/// @param format The format string.
/// @param ... The variadic arguments.
void print(const char* format, ...) ATTRIBUTE((format(printf, 1, 2)));

/// @brief A class which is able to print to come debugging mechanism.
/// This interface does not specify how the printing is done, but it is expected that the derived class will implement the print function.
class Printer {
public:
    /// @brief The print function
    virtual void operator()(const char* format, ...) const ATTRIBUTE((format(printf, 2, 3))) = 0;

    /// @brief The print function for Status objects
    virtual void operator()(char const* const source, core::Status status) const = 0;

protected:
    ~Printer() = default;    ///< Inaccessible Destructor
};

/// @brief The function to get the default printer object.
Printer& GetPrinter();

}    // namespace jarnax

#endif    // JARNAX_PRINT_HPP_
