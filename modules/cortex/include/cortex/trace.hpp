#ifndef CORTEX_M_TRACE_HPP_
#define CORTEX_M_TRACE_HPP_

/// @file
/// The Cortex M Core Header

#include "cortex/core.hpp"

namespace cortex {
/// Instruction Trace Macrocell Register Declaration
struct InstructionTraceMacrocell final {
    /// A Stimulus Port Register Declaration
    struct StimulusPort final {
        struct Fields final {
            std::uint32_t fifo_ready : 1U;     //!< Used to check when the register is ready again
            std::uint32_t            : 31U;    ///< Reserved field
        };
        union ports {
            std::uint8_t u08;     //!< Used to write std::uint8_t
            std::uint16_t u16;    //!< Used to write std::uint16_t
            std::uint32_t u32;    //!< Used to write std::uint32_t
        };
        union {
            Fields read;
            ports write;    // typed as SoftwareEventPacket?
        };
    };

    /// A bitfield which controls the Stimulus Fields.
    class StimulusEnable final {
    public:
        constexpr StimulusEnable() : m_bitfield_{0U} {}

        inline bool is_enabled(std::size_t bit) const volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t mask = (1U << shift);
            return ((this->m_bitfield_ & mask) != 0U);
        }
        inline void enable(std::size_t bit) volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t value = (1U << shift);
            this->m_bitfield_ = this->m_bitfield_ | value;
        }

    protected:
        std::uint32_t m_bitfield_;
    };

    /// A bitfield which controls if the port is only accessible in Privilege mode
    class StimulusPrivilege final {
    public:
        inline bool is_privileged(std::size_t bit) const volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t mask = (1U << shift);
            return ((this->m_bitfield_ & mask) != 0U);
        }
        inline void enable(std::size_t bit) volatile {
            std::size_t shift = bit & 0x1FU;
            std::uint32_t value = (1U << shift);
            this->m_bitfield_ = this->m_bitfield_ | value;
        }

    protected:
        std::uint32_t m_bitfield_;
    };

    inline bool is_enabled(std::size_t index) volatile {
        std::size_t idx = index >> 5U;
        std::size_t bit = index & 0x1FU;
        return this->stimulus_enable[idx].is_enabled(bit);
    }

    inline void enable(std::size_t index) volatile {
        std::size_t idx = index >> 5U;
        std::size_t bit = index & 0x1FU;
        return this->stimulus_enable[idx].enable(bit);
    }

    enum class Prescaler : std::uint32_t {
        None = 0U,
        Quarter = 1U,
        Sixteenth = 2U,
        SixtyFourth = 3U
    };

    enum class TimestampFrequency : std::uint32_t {
        Disabled = 0U,
        Every128Cycles = 1U,
        Every8192Cycles = 2U,
        EveryPacket = 3U,
    };

    /// Control Register
    struct Control final {
        struct Fields final {
            std::uint32_t enable                   : 1U;
            std::uint32_t timestamps               : 1U;
            std::uint32_t synchronized             : 1U;
            std::uint32_t forwarding               : 1U;    //!< Forwards from DWT to ITM
            std::uint32_t asynchronous_clock       : 1U;    //!< Also called SWOENA for some reason
            std::uint32_t                          : 3U;    ///< Reserved field
            Prescaler prescaler                    : 2U;
            TimestampFrequency timestamp_frequency : 2U;
            std::uint32_t                          : 4U;    ///< Reserved field
            std::uint32_t id                       : 7U;
            std::uint32_t busy                     : 1U;
            std::uint32_t                          : 8U;    ///< Reserved field
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    StimulusPort stimulus_port[256];      //!< Offset 0x000 to 0x3FC
    std::uint32_t _reserved1[640];        //!< Offset 0x400 to 0xDFC
    StimulusEnable stimulus_enable[8];    //!< Offset 0xE00 to 0xE1C
    std::uint32_t _reserved2[8];          //!< Offset 0xE20 to 0xE3C
    StimulusPrivilege privilege;          //!< Offset 0xE40
    std::uint32_t _reserved3[15];         //!< Offset 0xE44 to 0xE7C
    Control control;                      //!< Offset 0xE80
    std::uint32_t _reserved4[29];         //!< Offset 0xE84 to 0xEF4
    std::uint32_t integrated_write;
    std::uint32_t integrated_read;
    std::uint32_t integrated_mode_control;
    std::uint32_t _reserved5[43];    ///< Reserved field
    std::uint32_t lock_access;
    std::uint32_t lock_status;
};
static_assert(sizeof(InstructionTraceMacrocell) == 0xFB8U, "Must be this many bytes");

constexpr static std::uint32_t kItmLockValue = 0xC5ACCE55U;

/// The Data Watch and Trace module.
/// @aka DWT
struct DataWatchAndTrace final {
    /// The DWT Tap Values
    enum class Tap : std::uint32_t {
        Count6 = 0U,
        Count10 = 1U,
    };
    // The DWT Sync Tap Values
    enum class SyncTap : std::uint32_t {
        Disabled = 0U,
        Count24 = 1U,
        Count26 = 2U,
        Count28 = 3U
    };
    /// The Control Register
    struct Control final {
        Control() : whole{0} {}
        Control(Control const& other) : whole{other.whole} {}
        Control(Control volatile& other) : whole{other.whole} {}
        struct Fields final {
            std::uint32_t cycle_count_enable                     : 1U;
            std::uint32_t post_counter_reload                    : 4U;
            std::uint32_t post_counter_init                      : 4U;
            Tap tap                                              : 1U;
            SyncTap sync_tap                                     : 2U;
            std::uint32_t periodic                               : 1U;
            std::uint32_t                                        : 3U;    ///< Reserved field
            std::uint32_t exception_trace                        : 1U;
            std::uint32_t cpi_overflow                           : 1U;
            std::uint32_t exception_overhead                     : 1U;
            std::uint32_t sleep                                  : 1U;
            std::uint32_t load_store_overhead                    : 1U;
            std::uint32_t fold_instruction_overhead              : 1U;
            std::uint32_t post_count_underflow                   : 1U;
            std::uint32_t                                        : 1U;    ///< Reserved field
            std::uint32_t no_profile_counters                    : 1U;
            std::uint32_t no_cycle_counters                      : 1U;
            std::uint32_t no_match_signal                        : 1U;
            std::uint32_t no_trace_sampling_or_exception_tracing : 1U;
            std::uint32_t number_of_comparators                  : 4U;
        };
        union {
            Fields bits;
            std::uint32_t whole;
        };

        // Assignment from copy back to registers
        void operator=(Control const& other) volatile { whole = other.whole; }
        // Copy from volatile register to local copy
        void operator=(Control volatile& other) { whole = other.whole; }
    };
    /// @brief Cluster register
    struct Cluster final {
        std::uint32_t comparator;
        std::uint32_t mask : 4U;
        std::uint32_t      : 28U;    ///< Reserved field
        /// The Function sub register
        struct Function final {
            enum class DataSize : std::uint32_t {
                Byte = 0U,
                Halfword = 1U,
                Word = 2U,
                Reserved = 3U,
            };
            std::uint32_t function                 : 4U;    ///< @todo ?
            std::uint32_t                          : 1U;    ///< Reserved field
            std::uint32_t enable                   : 1U;    ///< @todo ?
            std::uint32_t                          : 1U;    ///< Reserved field
            std::uint32_t cycle_match              : 1U;    //!< Only valid on [0].
            std::uint32_t data_value_compare       : 1U;
            std::uint32_t second_linked_comparator : 1U;
            DataSize size                          : 2U;
            std::uint32_t data_value_address0      : 4U;
            std::uint32_t data_value_address1      : 4U;
            std::uint32_t                          : 4U;    ///< Reserved field
            std::uint32_t matched                  : 1U;
            std::uint32_t                          : 7U;    ///< Reserved field
        };
        std::uint32_t function;
        std::uint32_t : 32U;    ///< Reserved field
    };
    //=======================================================
    Control control;              //<! The Control Register
    std::uint32_t cycle_count;    //<! The Cycle Counter
    /// Many registers in the DWT as simple counters
    struct Counter final {
        std::uint32_t count : 8U;
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

/// The Trace Point Interface Unit
/// @aka TPIU
struct TracePortInterfaceUnit final {
    struct SupportedParallelPortSizes final {
        std::uint32_t width;
    };
    struct CurrentParallelPortSizes final {
        std::uint32_t width;
    };
    ///
    struct AsynchronousClockPrescaler final {
        std::uint32_t scaler : 16U;
        std::uint32_t        : 16U;    ///< Reserved field
    };
    enum class Protocol : std::uint32_t {
        Parallel = 0U,
        AsyncManchester = 1U,
        AsyncNRZ = 2U,
        Reserved = 3U,
    };
    struct SelectedPinProtocol final {
        Protocol transmit_mode : 2U;
        std::uint32_t          : 30U;    ///< Reserved field
    };
    struct Type final {
        std::uint32_t                             : 6U;    ///< Reserved field
        std::uint32_t fifo_size_power_2           : 3U;
        std::uint32_t parallel_trace_port_invalid : 1U;
        std::uint32_t manchester_supported        : 1U;
        std::uint32_t nrz_supported               : 1U;
        std::uint32_t                             : 20U;    ///< Reserved field
    };

    inline std::size_t get_swo_clock(std::size_t reference_clock) const {
        return reference_clock / (asynchronous_clock_prescaler.scaler + 1U);
    }

    inline std::size_t get_fifo_size(void) { return (1U << type.fifo_size_power_2); }

    SupportedParallelPortSizes supported_parallel_port_sizes;
    CurrentParallelPortSizes current_parallel_port_sizes;
    std::uint32_t _reserved1[2];    ///< Reserved field. Offset 0x08 to 0x0C
    AsynchronousClockPrescaler asynchronous_clock_prescaler;
    std::uint32_t _reserved2[55];    ///< Reserved field. Offset 0x14 to 0xEC
    SelectedPinProtocol selected_pin_protocol;
    std::uint32_t _reserved4[131];    ///< Reserved field
    std::uint32_t format_and_flush_status;
    std::uint32_t format_and_flush_control;
    std::uint32_t format_sync_counter;
    std::uint32_t _reserved5[759];    ///< Reserved field
    std::uint32_t trigger;
    std::uint32_t fifo0;
    std::uint32_t _reserved6[3];    ///< Reserved field
    std::uint32_t fifo1;
    std::uint32_t integration_mode_control;
    std::uint32_t _reserved7[39];    ///< Reserved field
    std::uint32_t claim_tag;
    std::uint32_t claim_clear;
    std::uint32_t _reserved8[8];    ///< Reserved field
    std::uint32_t device_id;
    Type type;    // offset 0xFC8
};
static_assert(offsetof(TracePortInterfaceUnit, selected_pin_protocol) == 0xF0, "Must be at this offset");
static_assert(offsetof(TracePortInterfaceUnit, type) == 0xFCC, "Must be at this offset");
// ConstexprValueCompare<sizeof(TracePortInterfaceUnit), 0xFD0> test{};
static_assert(sizeof(TracePortInterfaceUnit) == 0xFD0, "Must be this size!");

/// The linker symbol to the ITM Module
extern InstructionTraceMacrocell volatile instruction_trace_macrocell;

}    // namespace cortex

#endif    // CORTEX_M_TRACE_HPP_
