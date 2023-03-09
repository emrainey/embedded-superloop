#include <cstdint>
#include <cstddef>

namespace cortex {
namespace m4 {

/// The hardware representation of a processor word on Cortex M4
union word {
   uintptr_t address;
	   void* pointer;
    uint32_t u32[1];
	uint16_t u16[2];
	 uint8_t u08[4];
	 int32_t s32[1];
	 int16_t s16[2];
	  int8_t s08[4];
        char chr[4];
	   float f32[1];
};
static_assert(sizeof(word) == sizeof(uint32_t), "Must be exactly this size");

/// Processor Half-Word
union half {
	uint16_t u16[1];
	 uint8_t u08[2];
	 int16_t s16[1];
	  int8_t s08[2];
        char chr[2];
};
static_assert(sizeof(half) == sizeof(uint16_t), "Must be exactly this size");

/// Processor Byte
union byte {
	uint8_t u08;
	 int8_t s08;
	   char chr;
};
static_assert(sizeof(byte) == sizeof(uint8_t), "Must be exactly this size");

/// The various exception types in the System
enum class ExceptionType : uint32_t {
	Reset = 1u,
	NonMaskable = 2u,
	HardFault = 3u,
	MemoryManagementFault = 4u,
	BusFault = 5u,
	UsageFault = 6u,
	// 7-10 Reserved
	SupervisorCall = 11u,
	// 12-13 Reserved
	PendingSupervisor = 14u,
	SystemTick = 15u,
	Interrupt = 16u,
};

/// The enumeration of Interrupt Request Numbers
enum class InterruptRequest : int {
	NonMaskable = -14,
	HardFault = -13,
	MemoryManagementFault = -12,
	BusFault = -11,
	UsageFault = -10,
	SupervisorCall = -5,
	DebugMonitor = -4,
	PendSV = -2,
	SysTick = -1,
};

/// Exception Priorities
enum class Priority {
	Highest = -3,
	Higher = -2,
	High = -1,
	/// value between 0 - 255
};

enum class InterruptServiceRoutine : uint32_t {
	Thread = 0u,
	// 1 is Reserved
	NonMaskable = 2u,
	HardFault = 3u,
	MemoryManagement = 4u,
	BusFault = 5u,
	UsageFault = 6u,
	// 6-10 is Reserved
	SupervisorCall = 11u,
	// 12 is Reserved for Debug
	// 13 is Reserved
	PendSV = 14u,
	SystemTick = 15u,

};
struct Registers {
	word general_purpose[13]; //!< r[0] through r[12]
	word stack_pointer; //!< r13
	word link; //!< r14
	word program_counter; //!< r15
	struct ProgramStatus {
		struct Application {
			uint32_t : 16;
			uint32_t ge_flags : 4;  //!< GE
			uint32_t : 7;
			uint32_t saturation : 1; //!< aka Q
			uint32_t overflow : 1; //!< aka V
			uint32_t carry : 1; //!< aka C
			uint32_t zero : 1; //!< aka Z
			uint32_t negative : 1; //!< aka N
		};
		struct Interrupt {
			InterruptServiceRoutine interrupt_service_routine : 9; //!< @see cortex::m4::IRQn or processor specific enum
			uint32_t : 23;
		};
		struct Execution {
			uint32_t : 10;
			uint32_t bottom : 6; //!< Bottom ICI/IT bits
			uint32_t : 8;
			uint32_t thumb : 1; //!< Thumb Mode
			uint32_t top : 2; //!< Top ICI/IT Bits
			uint32_t : 5;

			inline uint8_t get(void) const {
				uint8_t tmp = bottom;
				tmp |= (top << 6u);
				return tmp;
			}
		};
		Application apsr;
		Interrupt ipsr;
		Execution epsr;
	};
	ProgramStatus program_status;
	struct PriorityMask {
		uint32_t mask : 1;
		uint32_t : 31;
	};
	struct FaultMask {
		uint32_t mask : 1;
		uint32_t : 31;
	};
	struct BasePriorityMask {
		uint32_t mask : 8u; //!< Not a bit mask but _masks_ priorities less than this value
		uint32_t : 24u;
	};
	PriorityMask priority;
	FaultMask fault;
	BasePriorityMask base_priority;

	enum class ThreadMode : uint32_t {
		Priviledged = 0u,
		Unpriviledged = 1u,
	};
	enum class StackType : uint32_t {
		Main = 0u, //!< Kernel and Exceptions
		Process = 1u, //!< Threads
	};
	struct Control {
		ThreadMode const thread_mode : 1;
		StackType const stack_type : 1;
		uint32_t float_active : 1;
		uint32_t : 29;
	};
	Control control;
};

struct SystemHandlerControlState {
	uint32_t active_mem_fault : 1;
	uint32_t active_bus_fault : 1;
	uint32_t : 1;
	uint32_t active_usage_fault : 1;
	uint32_t : 3;
	uint32_t active_supervisor_call : 1;
	uint32_t active_debug_monitor : 1;
	uint32_t : 1;
	uint32_t active_pending_supervisor : 1;
	uint32_t active_system_tick : 1;

	uint32_t pending_usage_fault : 1;
	uint32_t pending_mem_fault : 1;
	uint32_t pending_bus_fault : 1;
	uint32_t pending_supervisor_call : 1;

	uint32_t enable_mem_fault : 1;
	uint32_t enable_bus_fault : 1;
	uint32_t enable_usage_fault : 1;

	uint32_t : 13;
};

struct __attribute__((packed)) ConfigurableFaultStatus {
	//uint32_t memory_management : 8u;
	struct MemoryManagement {
		uint8_t instruction_access_violation : 1u;
		uint8_t data_access_violation : 1u;
		uint8_t : 1;
		uint8_t unstacking : 1u;
		uint8_t stacking : 1u;
		uint8_t floating_point_lazy_state : 1u;
		uint8_t : 1;
		uint8_t valid : 1u;
	};
	MemoryManagement memory_manage;

	struct BusError {
		// uint32_t bus_fault : 8u;
		uint8_t instruction : 1u;
		uint8_t precise_data : 1u;
		uint8_t imprecise_data : 1u;
		uint8_t unstacking : 1u;
		uint8_t stacking : 1u;
		uint8_t floating_point_lazy_evaluation : 1u;
		uint8_t : 1;
		uint8_t valid : 1; //!< BFAR is valid
	};
	BusError bus_error;

	struct UsageFaults {
		uint16_t undefined_instruction : 1u;
		uint16_t invalid_state : 1u;
		uint16_t invalid_program_counter_load : 1u;
		uint16_t coprocessor_access : 1u;
		uint16_t : 3;
		uint16_t unaligned : 1u;
		uint16_t divide_by_zero : 1u;
		uint16_t : 6;
	};
	UsageFaults usage_fault;
};
static_assert(sizeof(ConfigurableFaultStatus) == sizeof(word), "Must be a word size");

/// An ISR Handler takes no direct arguments
using Handler = void (*)(void);


/// Contains the Vector Table
struct VectorTable {
	void * const stack_pointer;
	/// Contains the Exception Handlers (Reset + Faults + Interrupts)
	struct ExceptionHandlers {
		Handler reset_entry;
		Handler non_maskable_interrupt;
		/// Contains the Fault Handlers
		struct FaultHandlers {
			Handler hard;
			Handler memory_management;
			Handler bus;
			Handler usage;
		};
		FaultHandlers faults;
		Handler _reserved1[4];
		Handler supervisor_call;
		Handler _reserved2[2];
		Handler pending_supervisor;
		Handler system_tick;
		Handler interrupts[16]; // Vendor Core Specific defaults
	};
	ExceptionHandlers exceptions_handlers;
};
static_assert(sizeof(VectorTable) == 0x60, "Must fit exactly");
static_assert(offsetof(VectorTable::exceptions_handlers::fault_handlers, bus) == 0x14, "Must be at this offset");



} // namespace m4
} // namespace cortex
