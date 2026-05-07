#ifndef STM32_FAMILY_H_
#define STM32_FAMILY_H_

#include <cstddef>
#include <cstdint>

/// @file
/// The ST Micro 32 Family Header

namespace stm32 {

// declare the namespaces for the different series of STM32 parts. These are defined in their respective headers.
// declare the namespaces for the different series of STM32 parts. These are defined in their respective headers.
namespace f4xx {}
namespace h7xx {}

/// The enumerated supported families in the STM32 module
enum class Family : std::uint32_t {
    Undefined = 0U,
    stm32f4xx,
    stm32h7xx,
};

#if not defined(FAMILY)
#define FAMILY Undefined
#endif

/// Declares the family from the enumeration. This is passed on the command line i.e.: -DFAMILY=stm32f4xx
constexpr static Family family = Family::FAMILY;

// Map the family namespace to the peripherals namespace for common code in drivers
namespace peripherals {
#if defined(STM32F405RG) || defined(STM32F407VE)
using namespace stm32::f4xx;
#elif defined(STM32H753ZI)
using namespace stm32::h7xx;
#else
#error "Unsupported STM32 family. Please define FAMILY to a supported value (e.g., -DFAMILY=stm32f4xx)."
#endif
}    // namespace peripherals

}    // namespace stm32

#if defined(STM32F405RG) || defined(STM32F407VE)
#define STM32F4
#elif defined(STM32H753ZI)
#define STM32H7
#else
#error "Unsupported STM32 family. Please define FAMILY to a supported value (e.g., -DFAMILY=stm32f4xx)."
#endif

#endif    // STM32_FAMILY_H_
