#ifndef JARNAX_EXECUTABLE_HPP
#define JARNAX_EXECUTABLE_HPP

/// @file
/// jarnax::Executable Interface

namespace jarnax {

/// @brief Object which are executable inherit this interface and implement the Execute method
/// which informs them of the current superloop
class Executable {
public:
    /// Clients implement this function to be called by the Super Loop.
    /// @retval True if the object is still active and should be called again.
    /// @retval false if the object is complete and should not be called again.
    virtual bool Execute() = 0;

protected:
    ~Executable() = default;
};

}    // namespace jarnax

#endif    // JARNAX_EXECUTABLE_HPP