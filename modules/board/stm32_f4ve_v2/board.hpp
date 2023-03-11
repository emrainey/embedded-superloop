#ifndef BOARD_HPP_
#define BOARD_HPP_

/// @file
/// Contains configuration information for the board.

#include <cstdint>
#include "iso.hpp"
#include "stm32/stm32f407ve.hpp"

/// RTT features
namespace rtt {
/// The size of the buffer to send to the RTT Host
constexpr static size_t kUpwardBufferSize{4096u};
/// The size of the buffer to receive from the RTT Host
constexpr static size_t kDownwardBufferSize{16u};
}    // namespace rtt

namespace jarnax {    // Choices for Jarnax
/// Alias the namespace from STM32 as our vendor
namespace vendor = stm32;
constexpr static bool use_rtt_for_printf = true;
constexpr static bool use_swo_for_printf = false;
}    // namespace jarnax

namespace stm32 {    // Choices for STM32
/// The HSE value for this board.
constexpr static size_t high_speed_external_oscillator_frequency = 8 * iso::prefix::mega;
}    // namespace stm32

#endif    // BOARD_HPP_
