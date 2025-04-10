#ifndef JARNAX_INITIALIZABLE_HPP_
#define JARNAX_INITIALIZABLE_HPP_

#include "core/Status.hpp"

/// @file
/// jarnax::Initializable Interface

namespace jarnax {

/// @brief Object which are initialize-able inherit this interface and implement the Initialize method
class Initializable {
public:
    /// Clients implement this function to be called during boot but *before* the SuperLoop
    virtual core::Status Initialize() = 0;

protected:
    ~Initializable() = default;
};

}    // namespace jarnax

#endif    // JARNAX_INITIALIZABLE_HPP_