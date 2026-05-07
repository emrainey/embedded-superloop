
#ifndef STM32_H7XX_TIMER2__HPP_
#define STM32_H7XX_TIMER2__HPP_

/// @file
/// Auto Generated Structure Definitions for Timer2 from the Peripheralyzer.
/// @copyright

#include <cstddef>
#include <cstdint>
#include <type_traits>

namespace stm32 {
namespace h7xx {

/// General purpose timers (TIM2)
struct Timer2 final {
    /// control register 1 (CR1)
    struct Control1 final {
        /// Default Constructor
        Control1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control1(Control1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control1(Control1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control1(Control1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Counter enable (CEN)
            uint32_t counter_enable             : 1;    // bit 0
            /// Update disable (UDIS)
            uint32_t update_disable             : 1;    // bit 1
            /// Update request source (URS)
            uint32_t update_request_source      : 1;    // bit 2
            /// One-pulse mode (OPM)
            uint32_t one_pulse_mode             : 1;    // bit 3
            /// Direction (DIR)
            uint32_t data_transfer_direction    : 1;    // bit 4
            /// Center-aligned mode selection (CMS)
            uint32_t center_aligned_mode        : 2;    // bits 5:6
            /// Auto-reload preload enable (ARPE)
            uint32_t auto_reload_preload_enable : 1;    // bit 7
            /// Clock division (CKD)
            uint32_t clock_division             : 2;    // bits 8:9
            /// (reserved)
            uint32_t                            : 22;    // bits 10:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control1& operator=(Control1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Control1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control1) == 4UL, "Must be this exact size");
    /// control register 2 (CR2)
    struct Control2 final {
        /// Default Constructor
        Control2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Control2(Control2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Control2(Control2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Control2(Control2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Control2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Control2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Control2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t      : 3;    // bits 0:2
            /// Capture/compare DMA selection (CCDS)
            uint32_t ccds : 1;    // bit 3
            /// Master mode selection (MMS)
            uint32_t mms  : 3;    // bits 4:6
            /// TI1 selection (TI1S)
            uint32_t ti1s : 1;    // bit 7
            /// (reserved)
            uint32_t      : 24;    // bits 8:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control2& operator=(Control2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control2 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Control2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control2) == 4UL, "Must be this exact size");
    /// slave mode control register (SMCR)
    struct FollowerMode final {
        /// Default Constructor
        FollowerMode()
            : whole{0u} {}
        /// Copy Constructor from volatile
        FollowerMode(FollowerMode volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        FollowerMode(FollowerMode const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        FollowerMode(FollowerMode&&) = delete;
        /// Parameterized Constructor for constant references
        explicit FollowerMode(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit FollowerMode(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~FollowerMode() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Slave mode selection (SMS)
            uint32_t follower_mode_selection    : 3;    // bits 0:2
            /// (reserved)
            uint32_t                            : 1;    // bit 3
            /// Trigger selection (TS)
            uint32_t trigger_selection          : 3;    // bits 4:6
            /// Master/Slave mode (MSM)
            uint32_t leader_mode_selection      : 1;    // bit 7
            /// External trigger filter (ETF)
            uint32_t external_trigger_filter    : 4;    // bits 8:11
            /// External trigger prescaler (ETPS)
            uint32_t external_trigger_prescaler : 2;    // bits 12:13
            /// External clock enable (ECE)
            uint32_t external_clock_parity      : 1;    // bit 14
            /// External trigger polarity (ETP)
            uint32_t external_trigger_parity    : 1;    // bit 15
            /// (reserved)
            uint32_t                            : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        FollowerMode& operator=(FollowerMode&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(FollowerMode volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(FollowerMode const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<FollowerMode>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(FollowerMode) == 4UL, "Must be this exact size");
    /// DMA/Interrupt enable register (DIER)
    struct DirectMemoryAccessInterruptEnable final {
        /// Default Constructor
        DirectMemoryAccessInterruptEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        DirectMemoryAccessInterruptEnable(DirectMemoryAccessInterruptEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        DirectMemoryAccessInterruptEnable(DirectMemoryAccessInterruptEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        DirectMemoryAccessInterruptEnable(DirectMemoryAccessInterruptEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit DirectMemoryAccessInterruptEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit DirectMemoryAccessInterruptEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~DirectMemoryAccessInterruptEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Update interrupt enable (UIE)
            uint32_t update_interrupt_enable  : 1;    // bit 0
            /// Capture/Compare 1 interrupt enable (CC1IE)
            uint32_t cc1ie                    : 1;    // bit 1
            /// Capture/Compare 2 interrupt enable (CC2IE)
            uint32_t cc2ie                    : 1;    // bit 2
            /// Capture/Compare 3 interrupt enable (CC3IE)
            uint32_t cc3ie                    : 1;    // bit 3
            /// Capture/Compare 4 interrupt enable (CC4IE)
            uint32_t cc4ie                    : 1;    // bit 4
            /// (reserved)
            uint32_t                          : 1;    // bit 5
            /// Trigger interrupt enable (TIE)
            uint32_t trigger_interrupt_enable : 1;    // bit 6
            /// (reserved)
            uint32_t                          : 1;    // bit 7
            /// Update DMA request enable (UDE)
            uint32_t ude                      : 1;    // bit 8
            /// Capture/Compare 1 DMA request enable (CC1DE)
            uint32_t cc1de                    : 1;    // bit 9
            /// Capture/Compare 2 DMA request enable (CC2DE)
            uint32_t cc2de                    : 1;    // bit 10
            /// Capture/Compare 3 DMA request enable (CC3DE)
            uint32_t cc3de                    : 1;    // bit 11
            /// Capture/Compare 4 DMA request enable (CC4DE)
            uint32_t cc4de                    : 1;    // bit 12
            /// (reserved)
            uint32_t                          : 1;    // bit 13
            /// Trigger DMA request enable (TDE)
            uint32_t tde                      : 1;    // bit 14
            /// (reserved)
            uint32_t                          : 17;    // bits 15:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        DirectMemoryAccessInterruptEnable& operator=(DirectMemoryAccessInterruptEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessInterruptEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessInterruptEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<DirectMemoryAccessInterruptEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(DirectMemoryAccessInterruptEnable) == 4UL, "Must be this exact size");
    /// status register (SR)
    struct Status final {
        /// Default Constructor
        Status()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Status(Status volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Status(Status const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Status(Status&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Status(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Status(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Status() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Update interrupt flag (UIF)
            uint32_t update_interrupt_flag : 1;    // bit 0
            /// Capture/compare 1 interrupt flag (CC1IF)
            uint32_t cc1if                 : 1;    // bit 1
            /// Capture/Compare 2 interrupt flag (CC2IF)
            uint32_t cc2if                 : 1;    // bit 2
            /// Capture/Compare 3 interrupt flag (CC3IF)
            uint32_t cc3if                 : 1;    // bit 3
            /// Capture/Compare 4 interrupt flag (CC4IF)
            uint32_t cc4if                 : 1;    // bit 4
            /// (reserved)
            uint32_t                       : 1;    // bit 5
            /// Trigger interrupt flag (TIF)
            uint32_t tif                   : 1;    // bit 6
            /// (reserved)
            uint32_t                       : 2;    // bits 7:8
            /// Capture/Compare 1 overcapture flag (CC1OF)
            uint32_t cc1of                 : 1;    // bit 9
            /// Capture/compare 2 overcapture flag (CC2OF)
            uint32_t cc2of                 : 1;    // bit 10
            /// Capture/Compare 3 overcapture flag (CC3OF)
            uint32_t cc3of                 : 1;    // bit 11
            /// Capture/Compare 4 overcapture flag (CC4OF)
            uint32_t cc4of                 : 1;    // bit 12
            /// (reserved)
            uint32_t                       : 19;    // bits 13:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Status& operator=(Status&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Status volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Status const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Status>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Status) == 4UL, "Must be this exact size");
    /// event generation register (EGR)
    struct EventGeneration final {
        /// Default Constructor
        EventGeneration()
            : whole{0u} {}
        /// Copy Constructor from volatile
        EventGeneration(EventGeneration volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        EventGeneration(EventGeneration const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        EventGeneration(EventGeneration&&) = delete;
        /// Parameterized Constructor for constant references
        explicit EventGeneration(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit EventGeneration(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~EventGeneration() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Update generation (UG)
            uint32_t update_generation  : 1;    // bit 0
            /// Capture/compare 1 generation (CC1G)
            uint32_t cc1g               : 1;    // bit 1
            /// Capture/compare 2 generation (CC2G)
            uint32_t cc2g               : 1;    // bit 2
            /// Capture/compare 3 generation (CC3G)
            uint32_t cc3g               : 1;    // bit 3
            /// Capture/compare 4 generation (CC4G)
            uint32_t cc4g               : 1;    // bit 4
            /// (reserved)
            uint32_t                    : 1;    // bit 5
            /// Trigger generation (TG)
            uint32_t trigger_generation : 1;    // bit 6
            /// (reserved)
            uint32_t                    : 25;    // bits 7:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        EventGeneration& operator=(EventGeneration&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(EventGeneration volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(EventGeneration const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<EventGeneration>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(EventGeneration) == 4UL, "Must be this exact size");
    /// capture/compare mode register 1 (output mode) (CaptureCompareOutput1)
    struct CaptureCompareMode1 final {
        /// Default Constructor
        CaptureCompareMode1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompareMode1(CaptureCompareMode1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompareMode1(CaptureCompareMode1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompareMode1(CaptureCompareMode1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompareMode1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompareMode1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompareMode1() = default;

        /// The internal bitfield for the register
        struct OutputFields final {
            /// Capture/Compare 1 selection (CC1S)
            uint32_t capture_compare_selection1     : 2;    // bits 0:1
            /// Output Compare 1 Fast enable (OC1FE)
            uint32_t output_compare_fast_enable1    : 1;    // bit 2
            /// Output Compare 1 Preload enable (OC1PE)
            uint32_t output_compare_preload_enable1 : 1;    // bit 3
            /// Output Compare 1 Mode (OC1M)
            uint32_t output_compare_mode1           : 3;    // bits 4:6
            /// Output Compare 1 Clear Enable (OC1CE)
            uint32_t output_compare_clear_enable1   : 1;    // bit 7
            /// Capture/Compare 2 selection (CC2S)
            uint32_t capture_compare_selection2     : 2;    // bits 8:9
            /// Output Compare 2 Fast enable (OC2FE)
            uint32_t output_compare_fast_enable2    : 1;    // bit 10
            /// Output Compare 2 Preload enable (OC2PE)
            uint32_t output_compare_preload_enable2 : 1;    // bit 11
            /// Output Compare 2 Mode (OC2M)
            uint32_t output_compare_mode2           : 3;    // bits 12:14
            /// Output Compare 2 Clear Enable (OC2CE)
            uint32_t output_compare_clear_enable2   : 1;    // bit 15
            /// (reserved)
            uint32_t                                : 16;    // bits 16:31
        };
        /// The internal bitfield for the register
        struct InputFields final {
            /// Capture/Compare 1 selection (CC1S)
            uint32_t capture_compare_selection1 : 2;    // bits 0:1
            /// Input capture 1 prescaler (ICPCS)
            uint32_t input_capture_prescaler1   : 2;    // bits 2:3
            /// Input capture 1 filter (IC1F)
            uint32_t input_capture_filter1      : 4;    // bits 4:7
            /// Capture/Compare 2 selection (CC2S)
            uint32_t capture_compare_selection2 : 2;    // bits 8:9
            /// Input capture 2 prescaler (IC2PCS)
            uint32_t input_capture_prescaler2   : 2;    // bits 10:11
            /// Input capture 2 filter (IC2F)
            uint32_t input_capture_filter2      : 4;    // bits 12:15
            /// (reserved)
            uint32_t                            : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            OutputFields output;
            InputFields input;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompareMode1& operator=(CaptureCompareMode1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompareMode1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompareMode1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompareMode1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompareMode1) == 4UL, "Must be this exact size");
    /// capture/compare mode register 2 (output mode) (CaptureCompareOutput2)
    struct CaptureCompareMode2 final {
        /// Default Constructor
        CaptureCompareMode2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompareMode2(CaptureCompareMode2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompareMode2(CaptureCompareMode2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompareMode2(CaptureCompareMode2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompareMode2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompareMode2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompareMode2() = default;

        /// The internal bitfield for the register
        struct OutputFields final {
            /// Capture/Compare 3 selection (CC3S)
            uint32_t capture_compare_selection3     : 2;    // bits 0:1
            /// Output Compare 3 Fast enable (OC3FE)
            uint32_t output_compare_fast_enable3    : 1;    // bit 2
            /// Output Compare 3 Preload enable (OC3PE)
            uint32_t output_compare_preload_enable3 : 1;    // bit 3
            /// Output Compare 3 Mode (OC3M)
            uint32_t output_compare_mode3           : 3;    // bits 4:6
            /// Output Compare 3 Clear Enable (OC3CE)
            uint32_t output_compare_clear_enable3   : 1;    // bit 7
            /// Capture/Compare 4 selection (CC4S)
            uint32_t capture_compare_selection4     : 2;    // bits 8:9
            /// Output Compare 4 Fast enable (OC4FE)
            uint32_t output_compare_fast_enable4    : 1;    // bit 10
            /// Output Compare 4 Preload enable (OC4PE)
            uint32_t output_compare_preload_enable4 : 1;    // bit 11
            /// Output Compare 4 Mode (OC4M)
            uint32_t output_compare_mode4           : 3;    // bits 12:14
            /// Output Compare 4 Clear Enable (OC4CE)
            uint32_t output_compare_clear_enable4   : 1;    // bit 15
            /// (reserved)
            uint32_t                                : 16;    // bits 16:31
        };
        /// The internal bitfield for the register
        struct InputFields final {
            /// Capture/compare 3 selection (CC3S)
            uint32_t capture_compare_selection3 : 2;    // bits 0:1
            /// Input capture 3 prescaler (IC3PSC)
            uint32_t input_capture_prescaler3   : 2;    // bits 2:3
            /// Input capture 3 filter (IC3F)
            uint32_t input_capture_filter3      : 4;    // bits 4:7
            /// Capture/Compare 4 selection (CC4S)
            uint32_t capture_compare_selection4 : 2;    // bits 8:9
            /// Input capture 4 prescaler (IC4PSC)
            uint32_t input_capture_prescaler4   : 2;    // bits 10:11
            /// Input capture 4 filter (IC4F)
            uint32_t input_capture_filter4      : 4;    // bits 12:15
            /// (reserved)
            uint32_t                            : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            OutputFields output;
            InputFields input;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompareMode2& operator=(CaptureCompareMode2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompareMode2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompareMode2 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular
        /// instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompareMode2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompareMode2) == 4UL, "Must be this exact size");
    /// capture/compare enable register (CCER)
    struct CaptureCompareEnable final {
        /// Default Constructor
        CaptureCompareEnable()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompareEnable(CaptureCompareEnable volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompareEnable(CaptureCompareEnable const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompareEnable(CaptureCompareEnable&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompareEnable(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompareEnable(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompareEnable() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Capture/Compare 1 output enable (CC1E)
            uint32_t cc1e  : 1;    // bit 0
            /// Capture/Compare 1 output Polarity (CC1P)
            uint32_t cc1p  : 1;    // bit 1
            /// (reserved)
            uint32_t       : 1;    // bit 2
            /// Capture/Compare 1 output Polarity (CC1NP)
            uint32_t cc1np : 1;    // bit 3
            /// Capture/Compare 2 output enable (CC2E)
            uint32_t cc2e  : 1;    // bit 4
            /// Capture/Compare 2 output Polarity (CC2P)
            uint32_t cc2p  : 1;    // bit 5
            /// (reserved)
            uint32_t       : 1;    // bit 6
            /// Capture/Compare 2 output Polarity (CC2NP)
            uint32_t cc2np : 1;    // bit 7
            /// Capture/Compare 3 output enable (CC3E)
            uint32_t cc3e  : 1;    // bit 8
            /// Capture/Compare 3 output Polarity (CC3P)
            uint32_t cc3p  : 1;    // bit 9
            /// (reserved)
            uint32_t       : 1;    // bit 10
            /// Capture/Compare 3 output Polarity (CC3NP)
            uint32_t cc3np : 1;    // bit 11
            /// Capture/Compare 4 output enable (CC4E)
            uint32_t cc4e  : 1;    // bit 12
            /// Capture/Compare 4 output Polarity (CC4P)
            uint32_t cc4p  : 1;    // bit 13
            /// (reserved)
            uint32_t       : 1;    // bit 14
            /// Capture/Compare 4 output Polarity (CC4NP)
            uint32_t cc4np : 1;    // bit 15
            /// (reserved)
            uint32_t       : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompareEnable& operator=(CaptureCompareEnable&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompareEnable volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompareEnable const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompareEnable>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompareEnable) == 4UL, "Must be this exact size");
    /// counter (CNT)
    struct Counter final {
        /// Default Constructor
        Counter()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Counter(Counter volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Counter(Counter const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Counter(Counter&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Counter(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Counter(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Counter() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low counter value (CNT_L)
            uint32_t counter_low  : 16;    // bits 0:15
            /// High counter value (CNT_H)
            uint32_t counter_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Counter& operator=(Counter&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Counter volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Counter const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Counter>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Counter) == 4UL, "Must be this exact size");
    /// prescaler (PSC)
    struct Prescaler final {
        /// Default Constructor
        Prescaler()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Prescaler(Prescaler volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Prescaler(Prescaler const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Prescaler(Prescaler&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Prescaler(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Prescaler(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Prescaler() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Prescaler value (PSC)
            uint32_t prescaler : 16;    // bits 0:15
            /// (reserved)
            uint32_t           : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Prescaler& operator=(Prescaler&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Prescaler volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Prescaler const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Prescaler>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Prescaler) == 4UL, "Must be this exact size");
    /// auto-reload register (ARR)
    struct AutoReload final {
        /// Default Constructor
        AutoReload()
            : whole{0u} {}
        /// Copy Constructor from volatile
        AutoReload(AutoReload volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        AutoReload(AutoReload const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        AutoReload(AutoReload&&) = delete;
        /// Parameterized Constructor for constant references
        explicit AutoReload(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit AutoReload(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~AutoReload() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Auto-reload value (ARR_L)
            uint32_t auto_reload_low  : 16;    // bits 0:15
            /// High Auto-reload value (ARR_H)
            uint32_t auto_reload_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        AutoReload& operator=(AutoReload&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(AutoReload volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(AutoReload const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<AutoReload>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(AutoReload) == 4UL, "Must be this exact size");
    /// capture/compare register 1 (CCR1)
    struct CaptureCompare1 final {
        /// Default Constructor
        CaptureCompare1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare1(CaptureCompare1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare1(CaptureCompare1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare1(CaptureCompare1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Capture/Compare 1 value (CCR1_L)
            uint32_t capture_compare1_low  : 16;    // bits 0:15
            /// High Capture/Compare 1 value (CCR1_H)
            uint32_t capture_compare1_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare1& operator=(CaptureCompare1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare1 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompare1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare1) == 4UL, "Must be this exact size");
    /// capture/compare register 2 (CCR2)
    struct CaptureCompare2 final {
        /// Default Constructor
        CaptureCompare2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare2(CaptureCompare2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare2(CaptureCompare2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare2(CaptureCompare2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Capture/Compare 2 value (CCR2_L)
            uint32_t capture_compare2_low  : 16;    // bits 0:15
            /// High Capture/Compare 2 value (CCR2_H)
            uint32_t capture_compare2_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare2& operator=(CaptureCompare2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare2 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompare2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare2) == 4UL, "Must be this exact size");
    /// capture/compare register 3 (CCR3)
    struct CaptureCompare3 final {
        /// Default Constructor
        CaptureCompare3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare3(CaptureCompare3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare3(CaptureCompare3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare3(CaptureCompare3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Capture/Compare value (CCR3_L)
            uint32_t capture_compare3_low  : 16;    // bits 0:15
            /// High Capture/Compare value (CCR3_H)
            uint32_t capture_compare3_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare3& operator=(CaptureCompare3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare3 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompare3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare3) == 4UL, "Must be this exact size");
    /// capture/compare register 4 (CCR4)
    struct CaptureCompare4 final {
        /// Default Constructor
        CaptureCompare4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CaptureCompare4(CaptureCompare4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CaptureCompare4(CaptureCompare4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CaptureCompare4(CaptureCompare4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CaptureCompare4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CaptureCompare4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CaptureCompare4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Low Capture/Compare value (CCR4_L)
            uint32_t capture_compare4_low  : 16;    // bits 0:15
            /// High Capture/Compare value (CCR4_H)
            uint32_t capture_compare4_high : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CaptureCompare4& operator=(CaptureCompare4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CaptureCompare4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CaptureCompare4 const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<CaptureCompare4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CaptureCompare4) == 4UL, "Must be this exact size");
    /// DMA control register (DCR)
    struct DirectMemoryAccessControl final {
        /// Default Constructor
        DirectMemoryAccessControl()
            : whole{0u} {}
        /// Copy Constructor from volatile
        DirectMemoryAccessControl(DirectMemoryAccessControl volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        DirectMemoryAccessControl(DirectMemoryAccessControl const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        DirectMemoryAccessControl(DirectMemoryAccessControl&&) = delete;
        /// Parameterized Constructor for constant references
        explicit DirectMemoryAccessControl(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit DirectMemoryAccessControl(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~DirectMemoryAccessControl() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DMA base address (DBA)
            uint32_t dma_base_address : 5;    // bits 0:4
            /// (reserved)
            uint32_t                  : 3;    // bits 5:7
            /// DMA burst length (DBL)
            uint32_t dma_burst_length : 5;    // bits 8:12
            /// (reserved)
            uint32_t                  : 19;    // bits 13:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        DirectMemoryAccessControl& operator=(DirectMemoryAccessControl&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessControl volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessControl const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<DirectMemoryAccessControl>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(DirectMemoryAccessControl) == 4UL, "Must be this exact size");
    /// DMA address for full transfer (DMAR)
    struct DirectMemoryAccessAddress final {
        /// Default Constructor
        DirectMemoryAccessAddress()
            : whole{0u} {}
        /// Copy Constructor from volatile
        DirectMemoryAccessAddress(DirectMemoryAccessAddress volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        DirectMemoryAccessAddress(DirectMemoryAccessAddress const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        DirectMemoryAccessAddress(DirectMemoryAccessAddress&&) = delete;
        /// Parameterized Constructor for constant references
        explicit DirectMemoryAccessAddress(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit DirectMemoryAccessAddress(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~DirectMemoryAccessAddress() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// DMA register for burst accesses (DMAB)
            uint32_t dma_burst : 16;    // bits 0:15
            /// (reserved)
            uint32_t           : 16;    // bits 16:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        DirectMemoryAccessAddress& operator=(DirectMemoryAccessAddress&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessAddress volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(DirectMemoryAccessAddress const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<DirectMemoryAccessAddress>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(DirectMemoryAccessAddress) == 4UL, "Must be this exact size");
    /// TIM5 option register (OR)
    struct Option final {
        /// Default Constructor
        Option()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Option(Option volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Option(Option const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Option(Option&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Option(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Option(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Option() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t          : 10;    // bits 0:9
            /// Timer Input 4 remap (ITR1_RMP)
            uint32_t itr1_rmp : 2;    // bits 10:11
            /// (reserved)
            uint32_t          : 20;    // bits 12:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Option& operator=(Option&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Option volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Option const& other) volatile { whole = other.whole; }
        /// Copy Assign a complete value from the base type uint32_t into a volatile version
        /// This allows you to assign the whole register to a literal value or a known constant of the same type.
        /// @note Does not return a reference
        inline void operator=(uint32_t const& value) volatile { whole = value; }
        /// Returns a copy of the register as an uint32_t.
        inline explicit operator uint32_t(void) const { return whole; }
        /// Returns a copy of the volatile register as an uint32_t
        inline explicit operator uint32_t(void) volatile { return whole; }
        /// Defined as a runtime function which tests all the combinations of the bitfields but not on any particular instance
        static bool validate(void);
    };
    // Ensure the register is in standard layout format
    static_assert(std::is_standard_layout<Option>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Option) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// control register 1 (CR1)
    Control1 control1;    // offset 0x0UL
    /// control register 2 (CR2)
    Control2 control2;    // offset 0x4UL
    /// slave mode control register (SMCR)
    FollowerMode follower_mode;    // offset 0x8UL
    /// DMA/Interrupt enable register (DIER)
    DirectMemoryAccessInterruptEnable direct_memory_access_interrupt_enable;    // offset 0xcUL
    /// status register (SR)
    Status status;    // offset 0x10UL
    /// event generation register (EGR)
    EventGeneration event_generation;    // offset 0x14UL
    /// capture/compare mode register 1 (CCMR1)
    CaptureCompareMode1 capture_compare_mode1;    // offset 0x18UL
    /// capture/compare mode register 2 (CCMR2)
    CaptureCompareMode2 capture_compare_mode2;    // offset 0x1cUL
    /// capture/compare enable register (CCER)
    CaptureCompareEnable capture_compare_enable;    // offset 0x20UL
    /// counter (CNT)
    Counter counter;    // offset 0x24UL
    /// prescaler (PSC)
    Prescaler prescaler;    // offset 0x28UL
    /// auto-reload register (ARR)
    AutoReload auto_reload;    // offset 0x2cUL
    uint32_t : 32;             // offset 0x30UL
    /// capture/compare register 1 (CCR1)
    CaptureCompare1 capture_compare1;    // offset 0x34UL
    /// capture/compare register 2 (CCR2)
    CaptureCompare2 capture_compare2;    // offset 0x38UL
    /// capture/compare register 3 (CCR3)
    CaptureCompare3 capture_compare3;    // offset 0x3cUL
    /// capture/compare register 4 (CCR4)
    CaptureCompare4 capture_compare4;    // offset 0x40UL
    uint32_t : 32;                       // offset 0x44UL
    /// DMA control register (DCR)
    DirectMemoryAccessControl direct_memory_access_control;    // offset 0x48UL
    /// DMA address for full transfer (DMAR)
    DirectMemoryAccessAddress direct_memory_access_address;    // offset 0x4cUL
    /// TIM5 option register (OR)
    Option option;    // offset 0x50UL
    uint32_t : 32;    // offset 0x54UL
    uint32_t : 32;    // offset 0x58UL
    uint32_t : 32;    // offset 0x5cUL
    uint32_t : 32;    // offset 0x60UL
    uint32_t : 32;    // offset 0x64UL
    uint32_t : 32;    // offset 0x68UL
    uint32_t : 32;    // offset 0x6cUL
    uint32_t : 32;    // offset 0x70UL
    uint32_t : 32;    // offset 0x74UL
    uint32_t : 32;    // offset 0x78UL
    uint32_t : 32;    // offset 0x7cUL
    uint32_t : 32;    // offset 0x80UL
    uint32_t : 32;    // offset 0x84UL
    uint32_t : 32;    // offset 0x88UL
    uint32_t : 32;    // offset 0x8cUL
    uint32_t : 32;    // offset 0x90UL
    uint32_t : 32;    // offset 0x94UL
    uint32_t : 32;    // offset 0x98UL
    uint32_t : 32;    // offset 0x9cUL
    uint32_t : 32;    // offset 0xa0UL
    uint32_t : 32;    // offset 0xa4UL
    uint32_t : 32;    // offset 0xa8UL
    uint32_t : 32;    // offset 0xacUL
    uint32_t : 32;    // offset 0xb0UL
    uint32_t : 32;    // offset 0xb4UL
    uint32_t : 32;    // offset 0xb8UL
    uint32_t : 32;    // offset 0xbcUL
    uint32_t : 32;    // offset 0xc0UL
    uint32_t : 32;    // offset 0xc4UL
    uint32_t : 32;    // offset 0xc8UL
    uint32_t : 32;    // offset 0xccUL
    uint32_t : 32;    // offset 0xd0UL
    uint32_t : 32;    // offset 0xd4UL
    uint32_t : 32;    // offset 0xd8UL
    uint32_t : 32;    // offset 0xdcUL
    uint32_t : 32;    // offset 0xe0UL
    uint32_t : 32;    // offset 0xe4UL
    uint32_t : 32;    // offset 0xe8UL
    uint32_t : 32;    // offset 0xecUL
    uint32_t : 32;    // offset 0xf0UL
    uint32_t : 32;    // offset 0xf4UL
    uint32_t : 32;    // offset 0xf8UL
    uint32_t : 32;    // offset 0xfcUL
    uint32_t : 32;    // offset 0x100UL
    uint32_t : 32;    // offset 0x104UL
    uint32_t : 32;    // offset 0x108UL
    uint32_t : 32;    // offset 0x10cUL
    uint32_t : 32;    // offset 0x110UL
    uint32_t : 32;    // offset 0x114UL
    uint32_t : 32;    // offset 0x118UL
    uint32_t : 32;    // offset 0x11cUL
    uint32_t : 32;    // offset 0x120UL
    uint32_t : 32;    // offset 0x124UL
    uint32_t : 32;    // offset 0x128UL
    uint32_t : 32;    // offset 0x12cUL
    uint32_t : 32;    // offset 0x130UL
    uint32_t : 32;    // offset 0x134UL
    uint32_t : 32;    // offset 0x138UL
    uint32_t : 32;    // offset 0x13cUL
    uint32_t : 32;    // offset 0x140UL
    uint32_t : 32;    // offset 0x144UL
    uint32_t : 32;    // offset 0x148UL
    uint32_t : 32;    // offset 0x14cUL
    uint32_t : 32;    // offset 0x150UL
    uint32_t : 32;    // offset 0x154UL
    uint32_t : 32;    // offset 0x158UL
    uint32_t : 32;    // offset 0x15cUL
    uint32_t : 32;    // offset 0x160UL
    uint32_t : 32;    // offset 0x164UL
    uint32_t : 32;    // offset 0x168UL
    uint32_t : 32;    // offset 0x16cUL
    uint32_t : 32;    // offset 0x170UL
    uint32_t : 32;    // offset 0x174UL
    uint32_t : 32;    // offset 0x178UL
    uint32_t : 32;    // offset 0x17cUL
    uint32_t : 32;    // offset 0x180UL
    uint32_t : 32;    // offset 0x184UL
    uint32_t : 32;    // offset 0x188UL
    uint32_t : 32;    // offset 0x18cUL
    uint32_t : 32;    // offset 0x190UL
    uint32_t : 32;    // offset 0x194UL
    uint32_t : 32;    // offset 0x198UL
    uint32_t : 32;    // offset 0x19cUL
    uint32_t : 32;    // offset 0x1a0UL
    uint32_t : 32;    // offset 0x1a4UL
    uint32_t : 32;    // offset 0x1a8UL
    uint32_t : 32;    // offset 0x1acUL
    uint32_t : 32;    // offset 0x1b0UL
    uint32_t : 32;    // offset 0x1b4UL
    uint32_t : 32;    // offset 0x1b8UL
    uint32_t : 32;    // offset 0x1bcUL
    uint32_t : 32;    // offset 0x1c0UL
    uint32_t : 32;    // offset 0x1c4UL
    uint32_t : 32;    // offset 0x1c8UL
    uint32_t : 32;    // offset 0x1ccUL
    uint32_t : 32;    // offset 0x1d0UL
    uint32_t : 32;    // offset 0x1d4UL
    uint32_t : 32;    // offset 0x1d8UL
    uint32_t : 32;    // offset 0x1dcUL
    uint32_t : 32;    // offset 0x1e0UL
    uint32_t : 32;    // offset 0x1e4UL
    uint32_t : 32;    // offset 0x1e8UL
    uint32_t : 32;    // offset 0x1ecUL
    uint32_t : 32;    // offset 0x1f0UL
    uint32_t : 32;    // offset 0x1f4UL
    uint32_t : 32;    // offset 0x1f8UL
    uint32_t : 32;    // offset 0x1fcUL
    uint32_t : 32;    // offset 0x200UL
    uint32_t : 32;    // offset 0x204UL
    uint32_t : 32;    // offset 0x208UL
    uint32_t : 32;    // offset 0x20cUL
    uint32_t : 32;    // offset 0x210UL
    uint32_t : 32;    // offset 0x214UL
    uint32_t : 32;    // offset 0x218UL
    uint32_t : 32;    // offset 0x21cUL
    uint32_t : 32;    // offset 0x220UL
    uint32_t : 32;    // offset 0x224UL
    uint32_t : 32;    // offset 0x228UL
    uint32_t : 32;    // offset 0x22cUL
    uint32_t : 32;    // offset 0x230UL
    uint32_t : 32;    // offset 0x234UL
    uint32_t : 32;    // offset 0x238UL
    uint32_t : 32;    // offset 0x23cUL
    uint32_t : 32;    // offset 0x240UL
    uint32_t : 32;    // offset 0x244UL
    uint32_t : 32;    // offset 0x248UL
    uint32_t : 32;    // offset 0x24cUL
    uint32_t : 32;    // offset 0x250UL
    uint32_t : 32;    // offset 0x254UL
    uint32_t : 32;    // offset 0x258UL
    uint32_t : 32;    // offset 0x25cUL
    uint32_t : 32;    // offset 0x260UL
    uint32_t : 32;    // offset 0x264UL
    uint32_t : 32;    // offset 0x268UL
    uint32_t : 32;    // offset 0x26cUL
    uint32_t : 32;    // offset 0x270UL
    uint32_t : 32;    // offset 0x274UL
    uint32_t : 32;    // offset 0x278UL
    uint32_t : 32;    // offset 0x27cUL
    uint32_t : 32;    // offset 0x280UL
    uint32_t : 32;    // offset 0x284UL
    uint32_t : 32;    // offset 0x288UL
    uint32_t : 32;    // offset 0x28cUL
    uint32_t : 32;    // offset 0x290UL
    uint32_t : 32;    // offset 0x294UL
    uint32_t : 32;    // offset 0x298UL
    uint32_t : 32;    // offset 0x29cUL
    uint32_t : 32;    // offset 0x2a0UL
    uint32_t : 32;    // offset 0x2a4UL
    uint32_t : 32;    // offset 0x2a8UL
    uint32_t : 32;    // offset 0x2acUL
    uint32_t : 32;    // offset 0x2b0UL
    uint32_t : 32;    // offset 0x2b4UL
    uint32_t : 32;    // offset 0x2b8UL
    uint32_t : 32;    // offset 0x2bcUL
    uint32_t : 32;    // offset 0x2c0UL
    uint32_t : 32;    // offset 0x2c4UL
    uint32_t : 32;    // offset 0x2c8UL
    uint32_t : 32;    // offset 0x2ccUL
    uint32_t : 32;    // offset 0x2d0UL
    uint32_t : 32;    // offset 0x2d4UL
    uint32_t : 32;    // offset 0x2d8UL
    uint32_t : 32;    // offset 0x2dcUL
    uint32_t : 32;    // offset 0x2e0UL
    uint32_t : 32;    // offset 0x2e4UL
    uint32_t : 32;    // offset 0x2e8UL
    uint32_t : 32;    // offset 0x2ecUL
    uint32_t : 32;    // offset 0x2f0UL
    uint32_t : 32;    // offset 0x2f4UL
    uint32_t : 32;    // offset 0x2f8UL
    uint32_t : 32;    // offset 0x2fcUL
    uint32_t : 32;    // offset 0x300UL
    uint32_t : 32;    // offset 0x304UL
    uint32_t : 32;    // offset 0x308UL
    uint32_t : 32;    // offset 0x30cUL
    uint32_t : 32;    // offset 0x310UL
    uint32_t : 32;    // offset 0x314UL
    uint32_t : 32;    // offset 0x318UL
    uint32_t : 32;    // offset 0x31cUL
    uint32_t : 32;    // offset 0x320UL
    uint32_t : 32;    // offset 0x324UL
    uint32_t : 32;    // offset 0x328UL
    uint32_t : 32;    // offset 0x32cUL
    uint32_t : 32;    // offset 0x330UL
    uint32_t : 32;    // offset 0x334UL
    uint32_t : 32;    // offset 0x338UL
    uint32_t : 32;    // offset 0x33cUL
    uint32_t : 32;    // offset 0x340UL
    uint32_t : 32;    // offset 0x344UL
    uint32_t : 32;    // offset 0x348UL
    uint32_t : 32;    // offset 0x34cUL
    uint32_t : 32;    // offset 0x350UL
    uint32_t : 32;    // offset 0x354UL
    uint32_t : 32;    // offset 0x358UL
    uint32_t : 32;    // offset 0x35cUL
    uint32_t : 32;    // offset 0x360UL
    uint32_t : 32;    // offset 0x364UL
    uint32_t : 32;    // offset 0x368UL
    uint32_t : 32;    // offset 0x36cUL
    uint32_t : 32;    // offset 0x370UL
    uint32_t : 32;    // offset 0x374UL
    uint32_t : 32;    // offset 0x378UL
    uint32_t : 32;    // offset 0x37cUL
    uint32_t : 32;    // offset 0x380UL
    uint32_t : 32;    // offset 0x384UL
    uint32_t : 32;    // offset 0x388UL
    uint32_t : 32;    // offset 0x38cUL
    uint32_t : 32;    // offset 0x390UL
    uint32_t : 32;    // offset 0x394UL
    uint32_t : 32;    // offset 0x398UL
    uint32_t : 32;    // offset 0x39cUL
    uint32_t : 32;    // offset 0x3a0UL
    uint32_t : 32;    // offset 0x3a4UL
    uint32_t : 32;    // offset 0x3a8UL
    uint32_t : 32;    // offset 0x3acUL
    uint32_t : 32;    // offset 0x3b0UL
    uint32_t : 32;    // offset 0x3b4UL
    uint32_t : 32;    // offset 0x3b8UL
    uint32_t : 32;    // offset 0x3bcUL
    uint32_t : 32;    // offset 0x3c0UL
    uint32_t : 32;    // offset 0x3c4UL
    uint32_t : 32;    // offset 0x3c8UL
    uint32_t : 32;    // offset 0x3ccUL
    uint32_t : 32;    // offset 0x3d0UL
    uint32_t : 32;    // offset 0x3d4UL
    uint32_t : 32;    // offset 0x3d8UL
    uint32_t : 32;    // offset 0x3dcUL
    uint32_t : 32;    // offset 0x3e0UL
    uint32_t : 32;    // offset 0x3e4UL
    uint32_t : 32;    // offset 0x3e8UL
    uint32_t : 32;    // offset 0x3ecUL
    uint32_t : 32;    // offset 0x3f0UL
    uint32_t : 32;    // offset 0x3f4UL
    uint32_t : 32;    // offset 0x3f8UL
    uint32_t : 32;    // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Timer2>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Timer2, control1) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(Timer2, control2) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(Timer2, follower_mode) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(Timer2, direct_memory_access_interrupt_enable) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(Timer2, status) == 0x10UL, "Must be located at this offset");
static_assert(offsetof(Timer2, event_generation) == 0x14UL, "Must be located at this offset");
static_assert(offsetof(Timer2, capture_compare_enable) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(Timer2, counter) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(Timer2, prescaler) == 0x28UL, "Must be located at this offset");
static_assert(offsetof(Timer2, auto_reload) == 0x2cUL, "Must be located at this offset");
static_assert(offsetof(Timer2, capture_compare1) == 0x34UL, "Must be located at this offset");
static_assert(offsetof(Timer2, capture_compare2) == 0x38UL, "Must be located at this offset");
static_assert(offsetof(Timer2, capture_compare3) == 0x3cUL, "Must be located at this offset");
static_assert(offsetof(Timer2, capture_compare4) == 0x40UL, "Must be located at this offset");
static_assert(offsetof(Timer2, direct_memory_access_control) == 0x48UL, "Must be located at this offset");
static_assert(offsetof(Timer2, direct_memory_access_address) == 0x4cUL, "Must be located at this offset");
static_assert(offsetof(Timer2, option) == 0x50UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Timer2) == 0x400UL, "Must be this exact size");

/// The external volatile timer2 which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern Timer2 volatile timer2;
}    // namespace h7xx
}    // namespace stm32
#endif    // STM32_H7XX_TIMER2__HPP_
