#ifndef CORTEX_PROCESSOR_HPP_
#define CORTEX_PROCESSOR_HPP_

/// @file
/// Cortex Processor Utilities

#include <cortex/partnumber.hpp>
#include <cortex/types.hpp>

namespace cortex {
namespace processor {

/// @brief Gets the Part Number from Hardware
PartNumber GetPartNumber();

/// @brief Gets the Revision from Hardware
Revision GetRevision();

}    // namespace processor
}    // namespace cortex

#endif    // CORTEX_PROCESSOR_HPP_
