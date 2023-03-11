#ifndef SYSTEM_EXECUTABLE_HPP_
#define SYSTEM_EXECUTABLE_HPP_

/// @file
/// jarnax::Executable Interface

#include "jarnax/LoopInfo.hpp"

namespace jarnax {

/// @brief Object which are executable inherit this interface and implement the Execute method
/// which informs them of the current superloop
class Executable {
public:
    /// Clients implement this function to be called by the Super Loop.
    virtual bool Execute(LoopInfo const &metadata) = 0;

protected:
    ~Executable() = default;
};

}    // namespace jarnax

#endif    // SYSTEM_EXECUTABLE_HPP_