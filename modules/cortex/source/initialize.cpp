#include "configure.hpp"
#include "cortex/m4.hpp"
#include "core/core.hpp"
#include "cortex/linker.hpp"
#include "cortex/globals.hpp"
#include "cortex/thumb.hpp"

namespace cortex {

/// @brief The system's memory protected scheme.
struct MemoryProtectionUnitInitializer {
    MemoryProtectionUnit::Region region;
    MemoryProtectionUnit::BaseAddress address;
    MemoryProtectionUnit::Access access;
} mpui[kDefaultRegionLimit];

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
    //===============================================================================
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::Code);
    mpui[idx].address.Set(cortex::address::flash);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteThroughSingle);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::flash);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 0U;    // CODE must be executable!
    idx++;
    //===============================================================================
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::Data);
    mpui[idx].address.Set(cortex::address::sram);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::sram);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;
    //===============================================================================
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::Stack);
    mpui[idx].address.Set(cortex::address::stack);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::stack);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;
    //===============================================================================
    std::uint32_t const volatile main_stack_size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__main_stack_size));
    if (main_stack_size > 0U) {
        if (not ::is_power_of_two(main_stack_size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__main_stack_bottom);
        mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::MainStack);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(main_stack_size);
        mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the Process Stack, never execute!
    // the linker script computed the size of the process stack and we pull it in here...
    std::uint32_t const volatile process_stack_size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__process_stack_size));
    if (process_stack_size > 0U) {
        if (not ::is_power_of_two(process_stack_size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__process_stack_bottom);
        mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::ProcesStack);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(process_stack_size);
        mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }
    //===============================================================================
    // Read/Write over the Privileged Data, never execute!
    std::uint32_t const volatile privileged_data_size = static_cast<uint32_t>(reinterpret_cast<uintptr_t>(__privileged_data_size));
    if (privileged_data_size > 0U) {
        if (not ::is_power_of_two(privileged_data_size)) {
            cortex::spinhalt();
        }
        uintptr_t base_address = reinterpret_cast<uintptr_t>(__privileged_data_start);
        mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::PrivilegedData);
        mpui[idx].address.Set(base_address);
        mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
        mpui[idx].access.bits.set_power2_size(privileged_data_size);
        mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
        mpui[idx].access.bits.execute_never = 1U;
        idx++;
    }

    //===============================================================================
    // Read/Write over the Peripherals, but all R/W
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::Peripherals);
    mpui[idx].address.Set(cortex::address::peripheral);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::DeviceSingleProcessor);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::peripheral);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;

    //===============================================================================
    // Read/Write over the Backup (adding execute never)
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::Backup);
    mpui[idx].address.Set(cortex::address::backup);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::backup);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_RW_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;

    //===============================================================================
    // Read/Write over the System, but Privilege Only RW
    mpui[idx].region.parts.number = to_underlying(cortex::ProtectedRegion::System);
    mpui[idx].address.Set(cortex::address::system);
    mpui[idx].access = make_access(MemoryProtectionUnit::Attribute::StronglyOrdered);
    mpui[idx].access.bits.set_power2_size(cortex::sizes::power2::system);
    mpui[idx].access.bits.permissions = MemoryProtectionUnit::Permissions::RW_Priv_NA_User;
    mpui[idx].access.bits.execute_never = 1U;
    idx++;

    // save the number of Desired Regions.
    DesiredRegions = idx;
}

void fpu(void) {
    // read the value;
    auto cpac = system_control_block.coprocessor_access_control;
    // set the bits
    cpac.bits.cp10 = cortex::SystemControlBlock::CoProcessorAccessControl::Access::Full;
    cpac.bits.cp11 = cortex::SystemControlBlock::CoProcessorAccessControl::Access::Full;
    // write back
    system_control_block.coprocessor_access_control = cpac;
}

void mpu(void) {
    if /* constexpr */ (cortex::use_only_default_mpu_configuration) {
        /// don't change anything and return
        return;
    }
    MemoryProtectionUnit::Access volatile access;
    MemoryProtectionUnit::BaseAddress volatile base;
    // finish any previous operations (not strictly required but good practice)
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();

    //===============================================================================
    // turn off MPU at first
    memory_protection_unit.control.bits.enable = 0U;
    // disable each entry
    access.whole = 0U;
    access.bits.enable = 0U;    // just being explicit
    std::uint32_t number_of_regions_limit = memory_protection_unit.get_number_of_regions();
    for (std::uint32_t count = 0U; count < number_of_regions_limit; count++) {
        core::Split<std::uint32_t, 8U> tmp;
        tmp.whole = count;
        memory_protection_unit.region.parts.number = tmp.parts.lower;
        memory_protection_unit.base.whole = base.whole;
        memory_protection_unit.access.whole = access.whole;
    }
    // @TODO move these specialized regions to a vendor::initialize::mpu()
    //===============================================================================
    for (std::uint32_t idx = 0U; idx < DesiredRegions and idx < number_of_regions_limit; idx++) {
        memory_protection_unit.region = mpui[idx].region;
        memory_protection_unit.base = mpui[idx].address;
        memory_protection_unit.access = mpui[idx].access;
    }

    //===============================================================================
    // turn on MPU
    MemoryProtectionUnit::Control ctrl{memory_protection_unit.control};
    ctrl.bits.enable = 1U;
    ctrl.bits.core_handlers_use_mpu = 0U;    // handlers may need to go around the MPU
    // see the system address map for the default values, the MPU entries
    // above only add to the default memory map if this is 1U
    ctrl.bits.default_memory_map_in_privileged = 0U;
    memory_protection_unit.control = ctrl;
    // force all of these writes to complete (not strictly required but good practice)
    thumb::data_synchronization_barrier();
    thumb::instruction_barrier();
}

void swo(std::uint32_t desired_baud, Hertz clock_frequency) {
    if constexpr (not cortex::swo::enable) {
        return;
    }

    // compute the clock divider as a zero based value
    std::uint32_t clock_divider = (clock_frequency.value() / desired_baud) - 1U;

    // disable itm
    instruction_trace_macrocell.control.bits.enable = 0U;
    // enable trace
    debug_system.exception_monitor_control.bits.enable_trace = 1U;
    // configure for UART
    trace_port_interface_unit.selected_pin_protocol.transmit_mode = TracePortInterfaceUnit::Protocol::AsyncNRZ;
    // set the clock divider
    trace_port_interface_unit.asynchronous_clock_prescaler.scaler = std::uint16_t(clock_divider);
    // send the key to the register
    instruction_trace_macrocell.lock_access = kItmLockValue;

    if (not cortex::run_in_privileged_mode_only) {
        // configure the privilege access
        instruction_trace_macrocell.privilege.enable(0);
        instruction_trace_macrocell.privilege.enable(1);
    }
    // force ITM to be off again (in preparation of it enabling)
    instruction_trace_macrocell.control.bits.enable = 0U;
    while (instruction_trace_macrocell.control.bits.busy) { /* spin */
    }
    // (should be enabled now)
    auto ctrl = data_watch_and_trace.control;
    ctrl.bits.post_counter_reload = 0xFU;
    ctrl.bits.post_counter_init = 0xFU;
    ctrl.bits.tap = DataWatchAndTrace::Tap::Count10;
    ctrl.bits.sync_tap = DataWatchAndTrace::SyncTap::Disabled;
    ctrl.bits.periodic = 0U;
    ctrl.bits.exception_trace = 0U;
    ctrl.bits.cpi_overflow = 0U;
    ctrl.bits.exception_overhead = 0U;
    ctrl.bits.sleep = 0U;
    ctrl.bits.load_store_overhead = 0U;
    ctrl.bits.fold_instruction_overhead = 0U;
    ctrl.bits.post_count_underflow = 0U;
    ctrl.bits.number_of_comparators = 4U;
    data_watch_and_trace.control = ctrl;
    instruction_trace_macrocell.control.bits.enable = 1U;
    // enable 2 sub channels for now
    instruction_trace_macrocell.enable(0);
    instruction_trace_macrocell.enable(1);
}

void itm(void) {
    /// @todo Initialize the ITM
}

void tpiu(void) {
    /// @todo Initialize the TPIU
}

void faults(void) {
    auto shcsr = system_control_block.system_handler_control_state;
    shcsr.bits.enable_bus_fault = 1U;
    shcsr.bits.enable_mem_fault = 1U;
    shcsr.bits.enable_usage_fault = 1U;
    system_control_block.system_handler_control_state = shcsr;
}

void nvic(void) {
    // Insert more NVIC initialization here for statically configured interrupts
    // cortex parts don't need to have any NVIC configuration
}

void tick(Hertz ticks_per_second, Hertz reference_clock_frequency) {
    // creates a 24 bit value for the reload register
    core::Split<uint32_t, 24U> tmp;    // NOLINT (reload is a 24 bit value)
    tmp.whole = reference_clock_frequency.value() / ticks_per_second.value();

    system_tick.reload.bits.value = tmp.parts.lower;
    system_tick.current = 0U;

    // initialize the system tick
    auto ctrl = system_tick.control_status;    // read
    ctrl.bits.enable = 1U;
    ctrl.bits.interrupt = 1U;
    ctrl.bits.use_processor_clock = 0U;    // 0 indicates the "external" processor clock, 1 indicates the core "processor" clock
    system_tick.control_status = ctrl;     // write back
    cortex::is_tick_enabled = true;
    // this won't start interrupting until after the NVIC is initialized
}

}    // namespace initialize

}    // namespace cortex
