#ifndef CORTEX_MCU_HPP_
#define CORTEX_MCU_HPP_

/// @file
/// The Cortex Micro Controller Header (variant DEPENDENT)

#include <cstddef>
#include <cstdint>
#include <limits>
#include "compiler.hpp"
#include "debug.hpp"
// =============================================================
// Core Includes
#include "core/Intervals.hpp"
#include "core/Split.hpp"
// =============================================================
// Cortex API Includes
#include "cortex/addresses.hpp"
#include "cortex/bist.hpp"
#include "cortex/cache.hpp"
#include "cortex/clocks.hpp"
#include "cortex/exceptions.hpp"
#include "cortex/halt.hpp"
#include "cortex/nvic.hpp"
#include "cortex/supervisor.hpp"
#include "cortex/swo.hpp"
#include "cortex/thumb.hpp"
#include "cortex/tick.hpp"
#include "cortex/trigger.hpp"
// =============================================================
// Builders will pass in the CORTEX_M variant value to select the correct variant
#include "cortex/variant.hpp"
// =============================================================
// System Private Bus Peripherals
#include "cortex/peripherals/DebugSystem.hpp"
#include "cortex/peripherals/FloatingPoint.hpp"
#include "cortex/peripherals/InstructionTraceMacrocell.hpp"
#include "cortex/peripherals/InterruptControllerType.hpp"
#include "cortex/peripherals/MemoryProtectionUnit.hpp"
#include "cortex/peripherals/NestedVectorInterruptController.hpp"
#include "cortex/peripherals/SoftwareTriggeredInterrupt.hpp"
#include "cortex/peripherals/SystemControlBlock.hpp"    // <-- depends on variant
#include "cortex/peripherals/SystemTick.hpp"
// =============================================================

#endif    // CORTEX_MCU_HPP_
