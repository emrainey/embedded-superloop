#ifndef CORE_PRINTER_HPP
#define CORE_PRINTER_HPP

#include "compiler.hpp"
#include "core/Status.hpp"

/// @file
/// @brief The Printer Interface
/// @details This interface is used to print information to the console or other debugging mechanisms.

namespace core {

/// @brief A class which is able to print to come debugging mechanism.
/// This interface does not specify how the printing is done, but it is expected that the derived class will implement the print function.
class Printer {
public:
    /// @brief The print function
    virtual void operator()(const char* const format, ...) const ATTRIBUTE((format(printf, 2, 3))) = 0;

    /// @brief The print function for Status objects
    virtual void operator()(char const* const source, Status status) const = 0;

protected:
    ~Printer() = default;    ///< Inaccessible Destructor
};

/// @brief The function to get the default printer object.
Printer& GetPrinter();

}    // namespace core

#endif    // CORE_PRINTER_HPP
