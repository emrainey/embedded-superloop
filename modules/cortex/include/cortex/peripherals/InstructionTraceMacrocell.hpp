#ifndef CORTEX_M_TRACE_HPP_
#define CORTEX_M_TRACE_HPP_

/// @file
/// The Cortex Microcontroller Core Header

#include "cortex/types.hpp"

namespace cortex {
namespace peripherals {
/// Instruction Trace Macrocell Register Declaration
struct InstructionTraceMacrocell final {
    /// A Stimulus Port Register Declaration
    struct StimulusPort final {
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t fifo_ready : 1U;     //!< Used to check when the register is ready again
            std::uint32_t            : 31U;    ///< Reserved field
        };
        /// @brief The union of the register types
        union ports {
            std::uint8_t u08;     //!< Used to write std::uint8_t
            std::uint16_t u16;    //!< Used to write std::uint16_t
            std::uint32_t u32;    //!< Used to write std::uint32_t
        };
        /// @brief The union of the register types and the bitfield
        union {
            Fields read;
            ports write;    // typed as SoftwareEventPacket?
        };
    };

    /// A bitfield which controls the Stimulus Fields.
    class StimulusEnable final {
    public:
        /// @brief Default constructor
        constexpr StimulusEnable()
            : bitfield_{0U} {}

        /// @param bit The bit to check
        /// @return True if the bit is enabled
        inline bool is_enabled(std::size_t bit) const volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t mask = (1U << shift);
            return ((this->bitfield_ & mask) != 0U);
        }
        /// Enables a bit in the bitfield
        /// @param bit The bit to enable
        inline void enable(std::size_t bit) volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t value = (1U << shift);
            this->bitfield_ = this->bitfield_ | value;
        }

    protected:
        std::uint32_t bitfield_;    ///< The bitfield for the stimulus
    };

    /// A bitfield which controls if the port is only accessible in Privilege mode
    class StimulusPrivilege final {
    public:
        /// Checks if a stimulus port requires privileged access
        /// @param bit The bit index to check (0-31)
        /// @return True if privileged access is required
        inline bool is_privileged(std::size_t bit) const volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t mask = (1U << shift);
            return ((this->bitfield_ & mask) != 0U);
        }
        /// Enables privileged access requirement for a stimulus port
        /// @param bit The bit index to enable (0-31)
        inline void enable(std::size_t bit) volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t value = (1U << shift);
            this->bitfield_ = this->bitfield_ | value;
        }

    protected:
        std::uint32_t bitfield_;    ///< Privilege control bitfield
    };

    /// Checks if a stimulus port is enabled
    /// @param index The stimulus port index (0-255)
    /// @return True if enabled, false otherwise
    inline bool is_enabled(std::size_t index) volatile {
        std::size_t idx = index >> 5U;
        std::size_t bit = index & 0x1FU;
        return this->stimulus_enable[idx].is_enabled(bit);
    }

    /// Enables a stimulus port
    /// @param index The stimulus port index (0-255)
    inline void enable(std::size_t index) volatile {
        std::size_t idx = index >> 5U;
        std::size_t bit = index & 0x1FU;
        return this->stimulus_enable[idx].enable(bit);
    }

    /// Timestamp prescaler values
    enum class Prescaler : std::uint32_t {
        None = 0U,          ///< No prescaling
        Quarter = 1U,       ///< Divide by 4
        Sixteenth = 2U,     ///< Divide by 16
        SixtyFourth = 3U    ///< Divide by 64
    };

    /// Timestamp packet emission frequency
    enum class TimestampFrequency : std::uint32_t {
        Disabled = 0U,           ///< Timestamps disabled
        Every128Cycles = 1U,     ///< Emit every 128 cycles
        Every8192Cycles = 2U,    ///< Emit every 8192 cycles
        EveryPacket = 3U,        ///< Emit with every packet
    };

    /// Control Register
    struct Control final {
        /// Default Constructor
        Control()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control(Control volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control(Control const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control(Control&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control() = default;

        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t enable                   : 1U;    ///< Enable ITM
            std::uint32_t timestamps               : 1U;    ///< Enable timestamp generation
            std::uint32_t synchronized             : 1U;    ///< Enable synchronization packets
            std::uint32_t forwarding               : 1U;    ///< Forwards from DWT to ITM
            std::uint32_t asynchronous_clock       : 1U;    ///< Also called SWOENA for some reason
            std::uint32_t                          : 3U;    ///< Reserved field
            Prescaler prescaler                    : 2U;    ///< Timestamp prescaler
            TimestampFrequency timestamp_frequency : 2U;    ///< Timestamp packet frequency
            std::uint32_t                          : 4U;    ///< Reserved field
            std::uint32_t id                       : 7U;    ///< ATB ID for this device
            std::uint32_t busy                     : 1U;    ///< ITM busy flag
            std::uint32_t                          : 8U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    StimulusPort stimulus_port[256];          //!< Offset 0x000 to 0x3FC
    std::uint32_t _reserved1[640];            //!< Offset 0x400 to 0xDFC
    StimulusEnable stimulus_enable[8];        //!< Offset 0xE00 to 0xE1C
    std::uint32_t _reserved2[8];              //!< Offset 0xE20 to 0xE3C
    StimulusPrivilege privilege;              //!< Offset 0xE40
    std::uint32_t _reserved3[15];             //!< Offset 0xE44 to 0xE7C
    Control control;                          //!< Offset 0xE80
    std::uint32_t _reserved4[29];             //!< Offset 0xE84 to 0xEF4
    std::uint32_t integrated_write;           ///< Integration mode write register
    std::uint32_t integrated_read;            ///< Integration mode read register
    std::uint32_t integrated_mode_control;    ///< Integration mode control register
    std::uint32_t _reserved5[43];             ///< Reserved field
    std::uint32_t lock_access;                ///< Lock access register (write 0xC5ACCE55 to unlock)
    std::uint32_t lock_status;                ///< Lock status register
};
static_assert(sizeof(InstructionTraceMacrocell) == 0xFB8U, "Must be this many bytes");

constexpr static std::uint32_t ItmLockValue = 0xC5ACCE55U;

/// The Data Watch and Trace module.
/// @aka DWT
struct DataWatchAndTrace final {
    /// The DWT Tap Values
    enum class Tap : std::uint32_t {
        Count6 = 0U,
        Count10 = 1U,
    };
    /// DWT Synchronization tap values for synchronization packet emission
    enum class SyncTap : std::uint32_t {
        Disabled = 0U,    ///< Synchronization disabled
        Count24 = 1U,     ///< Sync every 2^24 cycles
        Count26 = 2U,     ///< Sync every 2^26 cycles
        Count28 = 3U      ///< Sync every 2^28 cycles
    };
    /// The Control Register
    struct Control final {
        /// Default constructor - initializes to zero
        Control()
            : whole{0} {}
        /// Copy constructor from another Control
        Control(Control const& other)
            : whole{other.whole} {}
        /// Copy constructor from volatile Control register
        Control(Control volatile& other)
            : whole{other.whole} {}
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t cycle_count_enable                     : 1U;    ///< Enable cycle counter
            std::uint32_t post_counter_reload                    : 4U;    ///< Post-counter reload value
            std::uint32_t post_counter_init                      : 4U;    ///< Post-counter initial value
            Tap tap                                              : 1U;    ///< CYCCNT tap position
            SyncTap sync_tap                                     : 2U;    ///< Synchronization packet rate
            std::uint32_t periodic                               : 1U;    ///< Enable periodic PC sample packets
            std::uint32_t                                        : 3U;    ///< Reserved field
            std::uint32_t exception_trace                        : 1U;    ///< Enable exception trace
            std::uint32_t cpi_overflow                           : 1U;    ///< CPI counter overflow event enable
            std::uint32_t exception_overhead                     : 1U;    ///< Exception overhead counter overflow enable
            std::uint32_t sleep                                  : 1U;    ///< Sleep counter overflow event enable
            std::uint32_t load_store_overhead                    : 1U;    ///< LSU counter overflow event enable
            std::uint32_t fold_instruction_overhead              : 1U;    ///< Fold counter overflow event enable
            std::uint32_t post_count_underflow                   : 1U;    ///< Post-counter underflow event enable
            std::uint32_t                                        : 1U;    ///< Reserved field
            std::uint32_t no_profile_counters                    : 1U;    ///< Profiling counters not implemented
            std::uint32_t no_cycle_counters                      : 1U;    ///< Cycle counter not implemented
            std::uint32_t no_match_signal                        : 1U;    ///< Comparator match events not supported
            std::uint32_t no_trace_sampling_or_exception_tracing : 1U;    ///< Trace sampling and exception tracing not supported
            std::uint32_t number_of_comparators                  : 4U;    ///< Number of comparators implemented
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };

        /// Assignment from copy back to volatile registers
        void operator=(Control const& other) volatile { whole = other.whole; }
        /// Copy from volatile register to local copy
        void operator=(Control volatile& other) { whole = other.whole; }
    };
    /// @brief Cluster register
    struct Cluster final {
        std::uint32_t comparator;    ///< Comparator value
        std::uint32_t mask : 4U;     ///< Address mask for comparator
        std::uint32_t      : 28U;    ///< Reserved field
        /// The Function sub register
        struct Function final {
            /// Data size for watchpoint comparison
            enum class DataSize : std::uint32_t {
                Byte = 0U,                                  ///< 8-bit data comparison
                Halfword = 1U,                              ///< 16-bit data comparison
                Word = 2U,                                  ///< 32-bit data comparison
                Reserved = 3U,                              ///< Reserved value
            };
            std::uint32_t function                 : 4U;    ///< @todo ?
            std::uint32_t                          : 1U;    ///< Reserved field
            std::uint32_t enable                   : 1U;    ///< @todo ?
            std::uint32_t                          : 1U;    ///< Reserved field
            std::uint32_t cycle_match              : 1U;    //!< Only valid on [0].
            std::uint32_t data_value_compare       : 1U;    ///< Data Value Comparison Enable
            std::uint32_t second_linked_comparator : 1U;    ///< Second linked comparator enable
            DataSize size                          : 2U;    ///< Data Size for data value comparison
            std::uint32_t data_value_address0      : 4U;    ///< Data Value Address 0
            std::uint32_t data_value_address1      : 4U;    ///< Data Value Address 1
            std::uint32_t                          : 4U;    ///< Reserved field
            std::uint32_t matched                  : 1U;    ///< Comparator matched flag
            std::uint32_t                          : 7U;    ///< Reserved field
        };
        std::uint32_t function;                             ///< The Function Register as bitfield
        std::uint32_t : 32U;                                ///< Reserved field
    };
    //=======================================================
    Control control;              ///< The Control Register
    std::uint32_t cycle_count;    ///< The Cycle Counter
    /// Many registers in the DWT as simple counters
    struct Counter final {
        std::uint32_t count : 8U;     ///< Counter value (8-bit)
        std::uint32_t       : 24U;    ///< Reserved field
    };
    /// The number of cycles per instruction
    Counter cycles_per_instruction;
    /// The number of cycles an exception costs
    Counter exception_overhead;
    /// The number of cycles a sleep costs
    Counter sleep;
    /// The number of cycles a load/store costs
    Counter load_store_overhead;
    /// The number of cycles a fold instruction costs
    Counter fold_instruction_overhead;
    /// The address of the program counter when last sampled.
    uintptr_t program_counter;
    /// The Cluster Register
};

/// The Trace Port Interface Unit (TPIU)
struct TracePortInterfaceUnit final {
    /// @brief The bitfield definition of the register
    struct SupportedParallelPortSizes final {
        std::uint32_t width;    ///< Supported parallel port width bitmap
    };
    /// @brief The bitfield definition of the register
    struct CurrentParallelPortSizes final {
        std::uint32_t width;    ///< Current parallel port width setting
    };
    /// @brief The bitfield definition of the register
    struct AsynchronousClockPrescaler final {
        std::uint32_t scaler : 16U;    ///< Clock prescaler divisor value
        std::uint32_t        : 16U;    ///< Reserved field
    };
    /// TPIU trace output protocol selection
    enum class Protocol : std::uint32_t {
        Parallel = 0U,           ///< Parallel trace port mode
        AsyncManchester = 1U,    ///< Asynchronous Manchester encoded
        AsyncNRZ = 2U,           ///< Asynchronous NRZ encoded
        Reserved = 3U,           ///< Reserved protocol
    };
    /// @brief The bitfield definition of the register
    struct SelectedPinProtocol final {
        Protocol transmit_mode : 2U;     ///< Selected trace output protocol
        std::uint32_t          : 30U;    ///< Reserved field
    };
    /// @brief The bitfield definition of the register
    struct Type final {
        std::uint32_t                             : 6U;     ///< Reserved field
        std::uint32_t fifo_size_power_2           : 3U;     ///< FIFO depth as power of 2
        std::uint32_t parallel_trace_port_invalid : 1U;     ///< Parallel trace port not available
        std::uint32_t manchester_supported        : 1U;     ///< Manchester encoding supported
        std::uint32_t nrz_supported               : 1U;     ///< NRZ encoding supported
        std::uint32_t                             : 20U;    ///< Reserved field
    };

    /// Calculates the SWO output clock frequency
    /// @param reference_clock The reference clock frequency in Hz
    /// @return The SWO clock frequency in Hz
    inline std::size_t get_swo_clock(std::size_t reference_clock) const { return reference_clock / (asynchronous_clock_prescaler.scaler + 1U); }

    /// Gets the FIFO size in bytes
    /// @return The FIFO size (2^fifo_size_power_2)
    inline std::size_t get_fifo_size(void) { return (1U << type.fifo_size_power_2); }

    SupportedParallelPortSizes supported_parallel_port_sizes;    ///< Supported parallel port width capabilities
    CurrentParallelPortSizes current_parallel_port_sizes;        ///< Current parallel port width configuration
    std::uint32_t _reserved1[2];                                 ///< Reserved field. Offset 0x08 to 0x0C
    AsynchronousClockPrescaler asynchronous_clock_prescaler;     ///< Async clock prescaler for SWO
    std::uint32_t _reserved2[55];                                ///< Reserved field. Offset 0x14 to 0xEC
    SelectedPinProtocol selected_pin_protocol;                   ///< Trace output protocol selection
    std::uint32_t _reserved4[131];                               ///< Reserved field
    std::uint32_t format_and_flush_status;                       ///< Formatter and flush status
    std::uint32_t format_and_flush_control;                      ///< Formatter and flush control
    std::uint32_t format_sync_counter;                           ///< Formatter sync counter
    std::uint32_t _reserved5[759];                               ///< Reserved field
    std::uint32_t trigger;                                       ///< Trigger register
    std::uint32_t fifo0;                                         ///< FIFO data 0
    std::uint32_t _reserved6[3];                                 ///< Reserved field
    std::uint32_t fifo1;                                         ///< FIFO data 1
    std::uint32_t integration_mode_control;                      ///< Integration mode control
    std::uint32_t _reserved7[39];                                ///< Reserved field
    std::uint32_t claim_tag;                                     ///< Claim tag set
    std::uint32_t claim_clear;                                   ///< Claim tag clear
    std::uint32_t _reserved8[8];                                 ///< Reserved field
    std::uint32_t device_id;                                     ///< Device configuration
    Type type;                                                   ///< TPIU type register
};
static_assert(offsetof(TracePortInterfaceUnit, selected_pin_protocol) == 0xF0, "Must be at this offset");
static_assert(offsetof(TracePortInterfaceUnit, type) == 0xFCC, "Must be at this offset");
// ConstexprValueCompare<sizeof(TracePortInterfaceUnit), 0xFD0> test{};
static_assert(sizeof(TracePortInterfaceUnit) == 0xFD0, "Must be this size!");

/// The linker symbol to the ITM Module
extern InstructionTraceMacrocell volatile instruction_trace_macrocell;

/// The pointer to the DWT module
extern DataWatchAndTrace volatile data_watch_and_trace;

/// The pointer to the TPIU module
extern TracePortInterfaceUnit volatile trace_port_interface_unit;
}    // namespace peripherals
}    // namespace cortex

#endif    // CORTEX_M_TRACE_HPP_
