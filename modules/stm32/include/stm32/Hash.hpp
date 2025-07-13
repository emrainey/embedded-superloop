#ifndef STM32_HASH_H
#define STM32_HASH_H

#include "core/Status.hpp"
#include "jarnax/Hash.hpp"
#include "jarnax/Initializable.hpp"

namespace stm32 {
/// The random number generator driver for STM32
class Hash : public jarnax::Hash, public jarnax::Initializable {
public:
    RandomNumberGenerator() = default;
    core::Status Initialize() override;
    std::uint32_t GetNextHash(void) override;

protected:
    constexpr static std::size_t kInitializeLimit{1000U};    ///< Don't let the object initialize forever.
    std::uint32_t first_{0U};                                ///< The first value read to check for an active generation
    bool initialized_{false};                                ///< True when the object has been initialized.
};
}    // namespace stm32

#endif    // STM32_RNG_H