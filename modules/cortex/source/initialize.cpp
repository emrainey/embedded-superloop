#include "configure.hpp"
#include "cortex/linker.hpp"
#include "cortex/mcu.hpp"
// ============================================================
#include "cortex/globals.hpp"
#include "cortex/initialize.hpp"

namespace cortex {

/// @brief The system's memory protected scheme.
struct MemoryProtectionUnitInitializer {
    peripherals::MemoryProtectionUnit::Region region;          ///< The region of the MPU
    peripherals::MemoryProtectionUnit::BaseAddress address;    ///< The base address of the region
    peripherals::MemoryProtectionUnit::Access access;          ///< The access for the region
} mpui[variant::DefaultRegionLimit];                           ///< The list of MPU regions for this processor

/// The number of Desired Regions from the initializer
size_t DesiredRegions;

namespace initialize {
void simple_globals(void) {
    using namespace core::units;
    DesiredRegions = 0U;
    clock_frequency = 0_Hz;
    system_clock_frequency = 0_Hz;
    // initialize the tick count
    ticks_since_boot = 0;
    // initialize the tick flag
    is_tick_enabled = false;
    // initialize the bist flag
    is_bist_successful = false;
    // initialize the built in self test data
    built_in_self_test.trigger_non_maskable_interrupt.is_testing = false;
    built_in_self_test.trigger_hard_fault.is_testing = false;
    built_in_self_test.trigger_memory_management_fault.is_testing = false;
    built_in_self_test.trigger_bus_fault.is_testing = false;
    built_in_self_test.trigger_usage_fault.is_testing = false;
    built_in_self_test.trigger_supervisor_call.is_testing = false;
    built_in_self_test.trigger_pending_supervisor.is_testing = false;
    built_in_self_test.trigger_system_tick.is_testing = false;
    built_in_self_test.trigger_hard_fault.has_passed = false;
    built_in_self_test.trigger_memory_management_fault.has_passed = false;
    built_in_self_test.trigger_bus_fault.has_passed = false;
    built_in_self_test.trigger_usage_fault.has_passed = false;
    built_in_self_test.trigger_supervisor_call.has_passed = false;
    built_in_self_test.trigger_pending_supervisor.has_passed = false;
    built_in_self_test.trigger_system_tick.has_passed = false;
}

void class_globals() {
    /// @internal If these structures or objects contain a Constructor
    /// they will execute here!
    size_t idx{0U};
    std::uint32_t size = 0U;
    std::uint8_t pow2 = 0U;
    //===============================================================================
    pow2 = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(__cortex_flash_pow2));
    mpui[idx].region.parts.number = polyfill::to_underlying(cortex::peripherals::ProtectedRegion::Code);
    mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_flash_start));
    mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteThroughSingle);
    mpui[idx].access.bits.set_power2_size(pow2);
    mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 0U;    // CODE must be executable!
    idx++;
    //===============================================================================
    pow2 = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(__cortex_sram_pow2));
    mpui[idx].region.parts.number = polyfill::to_underlying(cortex::peripherals::ProtectedRegion::Data);
    mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_sram_start));
    mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
    mpui[idx].access.bits.set_power2_size(pow2);
    mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;
    //===============================================================================
    pow2 = static_cast<uint8_t>(reinterpret_cast<uintptr_t>(__cortex_stack_pow2));
    mpui[idx].region.parts.number = polyfill::to_underlying(cortex::peripherals::ProtectedRegion::Stack);
    mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_stack_start));
    mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
    mpui[idx].access.bits.set_power2_size(pow2);
    mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;
    //===============================================================================
    std::uint32_t const volatile main_stack_size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__main_stack_size));
    if (main_stack_size > 0U) {
        if (not polyfill::is_power_of_two(main_stack_size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__main_stack_bottom);
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::MainStack);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(main_stack_size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the Process Stack, never execute!
    // the linker script computed the size of the process stack and we pull it in here...
    size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__process_stack_size));
    if (size > 0U) {
        if (not polyfill::is_power_of_two(size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__process_stack_bottom);
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::ProcessStack);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }
    //===============================================================================
    // Read/Write over the Privileged Data, never execute!
    size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__privileged_data_size));
    if (size > 0U) {
        if (not polyfill::is_power_of_two(size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__privileged_data_start);
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::PrivilegedData);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the Peripherals, but all R/W
    size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__cortex_peripheral_size));
    if (size > 0) {
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::Peripherals);
        mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_peripheral_start));
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::DeviceSingleProcessor);
        mpui[idx].access.bits.set_power2_size(size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Append any vendor-specific MPU regions.
    MpuRegionConfiguration vendor_regions[variant::DefaultRegionLimit]{};
    std::size_t const vendor_region_count = vendor_mpu_regions(vendor_regions, variant::DefaultRegionLimit);
    if (vendor_region_count > variant::DefaultRegionLimit) {
        cortex::spinhalt();
    }
    for (std::size_t region_idx = 0U; region_idx < vendor_region_count; region_idx++) {
        if (idx >= variant::DefaultRegionLimit) {
            cortex::spinhalt();
        }
        auto const &region = vendor_regions[region_idx];
        if (region.size_bytes == 0U or not polyfill::is_power_of_two(region.size_bytes)) {
            cortex::spinhalt();
        }
        mpui[idx].region.parts.number = region.region_number;
        mpui[idx].address.Set(region.base_address);
        mpui[idx].access = make_access(region.attribute);
        mpui[idx].access.bits.set_power2_size(region.size_bytes);
        mpui[idx].access.bits.permissions = region.permissions;
        mpui[idx].access.bits.execute_never = region.execute_never ? 1U : 0U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the Backup (adding execute never)
    size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__cortex_backup_size));
    if (size > 0U) {
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::Backup);
        mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_backup_start));
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the System, but Privilege Only RW
    size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__cortex_system_size));
    if (size > 0U) {
        mpui[idx].region.parts.number = polyfill::to_underlying(peripherals::ProtectedRegion::System);
        mpui[idx].address.Set(reinterpret_cast<uintptr_t>(__cortex_system_start));
        mpui[idx].access = make_access(peripherals::MemoryProtectionUnit::Attribute::StronglyOrdered);
        mpui[idx].access.bits.set_power2_size(size);
        mpui[idx].access.bits.permissions = peripherals::MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    // save the number of Desired Regions.
    DesiredRegions = idx;

    // there's a serious problem if the number of desired regions exceeds the limit
    if (not use_only_default_mpu_configuration and DesiredRegions > variant::DefaultRegionLimit) {
        cortex::spinhalt();
    }
}

void fpu(void) {
    // read the value;
    auto cpac = peripherals::system_control_block.coprocessor_access_control;
    // set the bits
    cpac.bits.cp10 = cortex::peripherals::SystemControlBlock::CoProcessorAccessControl::Access::Full;
    cpac.bits.cp11 = cortex::peripherals::SystemControlBlock::CoProcessorAccessControl::Access::Full;
    // write back
    peripherals::system_control_block.coprocessor_access_control = cpac;
}

void mpu(void) {
    if constexpr (cortex::use_only_default_mpu_configuration) {
        /// don't change anything and return
        return;
    }
    peripherals::MemoryProtectionUnit::Access volatile access;
    peripherals::MemoryProtectionUnit::BaseAddress volatile base;
    // finish any previous operations (not strictly required but good practice)
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();

    //===============================================================================
    // turn off MPU at first
    peripherals::memory_protection_unit.control.bits.enable = 0U;
    // disable each entry
    access.whole = 0U;
    access.bits.enable = 0U;    // just being explicit
    std::uint32_t number_of_regions_limit = peripherals::memory_protection_unit.get_number_of_regions();
    for (std::uint32_t count = 0U; count < number_of_regions_limit; count++) {
        core::Split<std::uint32_t, 8U> tmp;
        tmp.whole = count;
        peripherals::memory_protection_unit.region.parts.number = tmp.parts.lower;
        peripherals::memory_protection_unit.base.whole = base.whole;
        peripherals::memory_protection_unit.access.whole = access.whole;
    }
    // @TODO move these specialized regions to a vendor::initialize::mpu()
    //===============================================================================
    for (std::uint32_t idx = 0U; idx < DesiredRegions and idx < number_of_regions_limit; idx++) {
        peripherals::memory_protection_unit.region = mpui[idx].region;
        peripherals::memory_protection_unit.base = mpui[idx].address;
        peripherals::memory_protection_unit.access = mpui[idx].access;
    }

    //===============================================================================
    // turn on MPU
    peripherals::MemoryProtectionUnit::Control ctrl{peripherals::memory_protection_unit.control};
    ctrl.bits.enable = 1U;
    ctrl.bits.core_handlers_use_mpu = 0U;    // handlers may need to go around the MPU
    // see the system address map for the default values, the MPU entries
    // above only add to the default memory map if this is 1U
    ctrl.bits.default_memory_map_in_privileged = 0U;
    peripherals::memory_protection_unit.control = ctrl;
    // force all of these writes to complete (not strictly required but good practice)
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void swo(std::uint32_t desired_baud, Hertz clock_frequency) {
    if constexpr (not cortex::swo::enable) {
        return;
    }
    // @see https://black-magic.org/usage/swo.html

    // compute the clock divider as a zero based value
    std::uint32_t clock_divider = (clock_frequency.value() / desired_baud) - 1U;

    // disable itm
    peripherals::instruction_trace_macrocell.control.bits.enable = 0U;
    // enable trace
    peripherals::debug_system.exception_monitor_control.bits.enable_trace = 1U;
    // configure for UART
    peripherals::trace_port_interface_unit.selected_pin_protocol.transmit_mode = peripherals::TracePortInterfaceUnit::Protocol::AsyncNRZ;
    // set the clock divider
    peripherals::trace_port_interface_unit.asynchronous_clock_prescaler.scaler = std::uint16_t(clock_divider);
    // send the key to the register
    peripherals::instruction_trace_macrocell.lock_access = peripherals::ItmLockValue;

    if (not cortex::run_in_privileged_mode_only) {
        // configure the privilege access
        peripherals::instruction_trace_macrocell.privilege.enable(0);
        peripherals::instruction_trace_macrocell.privilege.enable(1);
    }
    // force ITM to be off again (in preparation of it enabling)
    peripherals::instruction_trace_macrocell.control.bits.enable = 0U;
    while (peripherals::instruction_trace_macrocell.control.bits.busy) { /* spin */
    }
    // (should be enabled now)
    auto ctrl = peripherals::data_watch_and_trace.control;
    ctrl.bits.post_counter_reload = 0xFU;
    ctrl.bits.post_counter_init = 0xFU;
    ctrl.bits.tap = peripherals::DataWatchAndTrace::Tap::Count10;
    ctrl.bits.sync_tap = peripherals::DataWatchAndTrace::SyncTap::Disabled;
    ctrl.bits.periodic = 0U;
    ctrl.bits.exception_trace = 0U;
    ctrl.bits.cpi_overflow = 0U;
    ctrl.bits.exception_overhead = 0U;
    ctrl.bits.sleep = 0U;
    ctrl.bits.load_store_overhead = 0U;
    ctrl.bits.fold_instruction_overhead = 0U;
    ctrl.bits.post_count_underflow = 0U;
    ctrl.bits.number_of_comparators = 4U;
    peripherals::data_watch_and_trace.control = ctrl;
    peripherals::instruction_trace_macrocell.control.bits.enable = 1U;
    // enable 2 sub channels for now
    peripherals::instruction_trace_macrocell.enable(0);
    peripherals::instruction_trace_macrocell.enable(1);
}

void faults(void) {
    auto shcsr = peripherals::system_control_block.system_handler_control_state;
    shcsr.bits.enable_bus_fault = 1U;
    shcsr.bits.enable_mem_fault = 1U;
    shcsr.bits.enable_usage_fault = 1U;
    peripherals::system_control_block.system_handler_control_state = shcsr;
}

void tick(Hertz ticks_per_second, Hertz reference_clock_frequency) {
    // creates a 24 bit value for the reload register
    core::Split<uint32_t, 24U> tmp;    // NOLINT (reload is a 24 bit value)
    tmp.whole = reference_clock_frequency.value() / ticks_per_second.value();

    peripherals::system_tick.reload.bits.value = tmp.parts.lower;
    peripherals::system_tick.current = 0U;

    // initialize the system tick
    auto ctrl = peripherals::system_tick.control_status;    // read
    ctrl.bits.enable = 1U;
    ctrl.bits.interrupt = 1U;
    ctrl.bits.use_processor_clock = 0U;                // 0 indicates the "external" processor clock, 1 indicates the core "processor" clock
    peripherals::system_tick.control_status = ctrl;    // write back
    cortex::is_tick_enabled = true;
    // this won't start interrupting until after the NVIC is initialized
}

void configuration() {
    // read the configuration control
    auto config = peripherals::system_control_block.configuration_control;
    // set the bits
    config.parts.allow_thread_mode_exception_return = cortex::allow_thread_mode_exception_return ? 1U : 0U;
    config.parts.allow_unprivileged_access_to_software_trigger = cortex::allow_unprivileged_software_trigger ? 1U : 0U;
    config.parts.trap_unaligned_access = cortex::trap_unaligned_access ? 1U : 0U;
    config.parts.trap_divide_by_zero = cortex::trap_divide_by_zero ? 1U : 0U;
    config.parts.ignore_precise_data_access_faults_in_negative_priority = cortex::ignore_precise_data_access_faults_in_negative_priority ? 1U : 0U;
    config.parts.enable_data_cache = cortex::enable_data_cache ? 1U : 0U;
    config.parts.enable_instruction_cache = cortex::enable_instruction_cache ? 1U : 0U;
    // write back
    peripherals::system_control_block.configuration_control = config;
    // Configure the TCMs if present
#if defined(CORTEX_HAS_ITCM) and (CORTEX_HAS_ITCM == 1)
    if constexpr (variant::configuration::has_itcm) {
        auto tcm = cortex::peripherals::itcm_control;
        tcm.bits.enable = 1U;
        tcm.bits.read_modify_write = 1U;
        tcm.bits.retry = 1U;
        cortex::peripherals::itcm_control = tcm;
    }
#endif
#if defined(CORTEX_HAS_DTCM) and (CORTEX_HAS_DTCM == 1)
    if constexpr (variant::configuration::has_dtcm) {
        auto tcm = cortex::peripherals::dtcm_control;
        tcm.bits.enable = 1U;
        tcm.bits.read_modify_write = 1U;
        tcm.bits.retry = 1U;
        cortex::peripherals::dtcm_control = tcm;
    }
#endif
}

}    // namespace initialize

}    // namespace cortex
