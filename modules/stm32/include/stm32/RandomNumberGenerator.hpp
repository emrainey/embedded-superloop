#ifndef STM32_RNG_H
#define STM32_RNG_H

/// @file
/// STM32 Random Number Generator Driver

#include "core/Status.hpp"
#include "jarnax/Initializable.hpp"
#include "jarnax/RandomNumberGenerator.hpp"

#include "stm32/peripherals.hpp"

namespace stm32 {
/// The random number generator driver for STM32
class RandomNumberGenerator : public jarnax::RandomNumberGenerator, public jarnax::Initializable {
public:
    /// Default Constructor
    RandomNumberGenerator(stm32::peripherals::RandomNumberGenerator volatile& peripheral);
    /// Default Destructor
    virtual ~RandomNumberGenerator() = default;

    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
    core::Status Initialize() override;
    std::uint32_t GetNextRandom(void) override;
    bool IsReady(void) const override;
    //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

    void HandleInterrupt(void);

    struct Statistics {
        std::size_t readings{0U};
        std::size_t errors{0U};
    };

    // @TODO should be a Statistican!
    Statistics const& GetStatistics(void) const { return statistics_; }

protected:
    constexpr static std::size_t kInitializeLimit{1000U};               ///< Don't let the object initialize forever.
    stm32::peripherals::RandomNumberGenerator volatile& peripheral_;    ///< The reference to the peripheral registers
    std::uint32_t first_;                                               ///< The first value read to check for an active generation
    bool initialized_;                                                  ///< True when the object has been initialized.
    std::uint32_t volatile value_;                                               ///< The latest value read. 
    bool volatile value_ready_;                                                  ///< True when the value is ready to be read.
    Statistics statistics_;                                             ///< Statistics about the random number generator.
};
}    // namespace stm32

#endif    // STM32_RNG_H
