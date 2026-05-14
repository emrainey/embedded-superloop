#ifndef STM32_PERIPHERALS_HPP_
#define STM32_PERIPHERALS_HPP_

/// @file
/// The header to include in any chip specific driver to consolidate the chip/family specific picking of headers
/// @note Common Drivers should ONLY use stm32::peripherals::XXXX for their peripheral namespace, and not the family specific namespaces. This allows
/// the common drivers to be used across different STM32 families without modification.

#include "stm32/chip.hpp"

#if defined(STM32F4)
#include "stm32/f4xx/Debug.hpp"
#include "stm32/f4xx/DirectMemoryAccess.hpp"
#include "stm32/f4xx/FlashControl.hpp"
#include "stm32/f4xx/GeneralPurposeInputOutput.hpp"
#include "stm32/f4xx/InterIntegratedCircuit.hpp"
#include "stm32/f4xx/RandomNumberGenerator.hpp"
#include "stm32/f4xx/ResetAndClockControl.hpp"
#include "stm32/f4xx/SerialPeripheralInterface.hpp"
#include "stm32/f4xx/Timer2.hpp"
#include "stm32/f4xx/UniversalAsynchronousReceiverTransmitter.hpp"
#include "stm32/f4xx/UniversalSynchronousAsynchronousReceiverTransmitter.hpp"
#elif defined(STM32H7)
#include "stm32/h7xx/Debug.hpp"
#include "stm32/h7xx/DirectMemoryAccess.hpp"
#include "stm32/h7xx/FlashControl.hpp"
#include "stm32/h7xx/GeneralPurposeInputOutput.hpp"
#include "stm32/h7xx/InterIntegratedCircuit.hpp"
#include "stm32/h7xx/PowerController.hpp"
#include "stm32/h7xx/RandomNumberGenerator.hpp"
#include "stm32/h7xx/ResetAndClockControl.hpp"
#include "stm32/h7xx/SerialPeripheralInterface.hpp"
#include "stm32/h7xx/Timer2.hpp"
#include "stm32/h7xx/UniversalAsynchronousReceiverTransmitter.hpp"
#include "stm32/h7xx/UniversalSynchronousAsynchronousReceiverTransmitter.hpp"
#endif

#endif    // STM32_PERIPHERALS_HPP_
