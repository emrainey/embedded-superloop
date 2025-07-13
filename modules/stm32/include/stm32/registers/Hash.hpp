
#ifndef STM32_REGISTERS_HASH__HPP_
#define STM32_REGISTERS_HASH__HPP_

/// @file
/// Auto Generated Structure Definitions for Hash from the Peripheralyzer.
/// @copyright

#include <cstdint>
#include <cstddef>
#include <type_traits>

namespace stm32 {
namespace registers {

/// Hash processor (HASH)
struct Hash final {
    /// control register (CR)
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

        /// The internal bitfield for the register
        struct Fields final {
            /// (reserved)
            uint32_t                                         : 2;    // bits 0:1
            /// Initialize message digest calculation (INIT)
            uint32_t initialize                              : 1;    // bit 2
            /// DMA enable (DMAE)
            uint32_t direct_memory_access_enable             : 1;    // bit 3
            /// Data type selection (DATATYPE)
            uint32_t datatype                                : 2;    // bits 4:5
            /// Mode selection (MODE)
            uint32_t mode                                    : 1;    // bit 6
            /// Algorithm selection (ALGO0)
            uint32_t algo0                                   : 1;    // bit 7
            /// Number of words already pushed (NBW)
            uint32_t number_of_words                         : 4;    // bits 8:11
            /// DIN not empty (DINNE)
            uint32_t data_input_not_empty                    : 1;    // bit 12
            /// Multiple DMA Transfers (MDMAT)
            uint32_t multiple_direct_memory_access_transfers : 1;    // bit 13
            /// (reserved)
            uint32_t                                         : 2;    // bits 14:15
            /// Long key selection (LKEY)
            uint32_t long_key                                : 1;    // bit 16
            /// (reserved)
            uint32_t                                         : 1;    // bit 17
            /// ALGO (ALGO1)
            uint32_t algo1                                   : 1;    // bit 18
            /// (reserved)
            uint32_t                                         : 13;    // bits 19:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Control& operator=(Control&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Control volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Control const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Control>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Control) == 4UL, "Must be this exact size");
    /// data input register (DIN)
    struct DataInput final {
        /// Default Constructor
        DataInput()
            : whole{0u} {}
        /// Copy Constructor from volatile
        DataInput(DataInput volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        DataInput(DataInput const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        DataInput(DataInput&&) = delete;
        /// Parameterized Constructor for constant references
        explicit DataInput(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit DataInput(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~DataInput() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Data input (DATAIN)
            uint32_t data_input : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        DataInput& operator=(DataInput&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(DataInput volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(DataInput const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<DataInput>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(DataInput) == 4UL, "Must be this exact size");
    /// start register (STR)
    struct Start final {
        /// Default Constructor
        Start()
            : whole{0u} {}
        /// Copy Constructor from volatile
        Start(Start volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        Start(Start const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        Start(Start&&) = delete;
        /// Parameterized Constructor for constant references
        explicit Start(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit Start(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~Start() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Number of valid bits in the last word of the message (NBLW)
            uint32_t number_in_last_word : 5;    // bits 0:4
            /// (reserved)
            uint32_t                     : 3;    // bits 5:7
            /// Digest calculation (DCAL)
            uint32_t digest_calculation  : 1;    // bit 8
            /// (reserved)
            uint32_t                     : 23;    // bits 9:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        Start& operator=(Start&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(Start volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(Start const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<Start>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(Start) == 4UL, "Must be this exact size");
    /// digest registers (HR0)
    struct HR0 final {
        /// Default Constructor
        HR0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HR0(HR0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HR0(HR0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HR0(HR0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HR0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HR0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HR0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H0 (H0)
            uint32_t h0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HR0& operator=(HR0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HR0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HR0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HR0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HR0) == 4UL, "Must be this exact size");
    /// digest registers (HR1)
    struct HR1 final {
        /// Default Constructor
        HR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HR1(HR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HR1(HR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HR1(HR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H1 (H1)
            uint32_t h1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HR1& operator=(HR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HR1) == 4UL, "Must be this exact size");
    /// digest registers (HR2)
    struct HR2 final {
        /// Default Constructor
        HR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HR2(HR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HR2(HR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HR2(HR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H2 (H2)
            uint32_t h2 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HR2& operator=(HR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HR2) == 4UL, "Must be this exact size");
    /// digest registers (HR3)
    struct HR3 final {
        /// Default Constructor
        HR3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HR3(HR3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HR3(HR3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HR3(HR3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HR3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HR3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HR3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H3 (H3)
            uint32_t h3 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HR3& operator=(HR3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HR3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HR3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HR3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HR3) == 4UL, "Must be this exact size");
    /// digest registers (HR4)
    struct HR4 final {
        /// Default Constructor
        HR4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HR4(HR4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HR4(HR4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HR4(HR4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HR4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HR4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HR4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H4 (H4)
            uint32_t h4 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HR4& operator=(HR4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HR4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HR4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HR4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HR4) == 4UL, "Must be this exact size");
    /// interrupt enable register (IMR)
    struct InterruptManagement final {
        /// Default Constructor
        InterruptManagement()
            : whole{0u} {}
        /// Copy Constructor from volatile
        InterruptManagement(InterruptManagement volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        InterruptManagement(InterruptManagement const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        InterruptManagement(InterruptManagement&&) = delete;
        /// Parameterized Constructor for constant references
        explicit InterruptManagement(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit InterruptManagement(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~InterruptManagement() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Data input interrupt enable (DINIE)
            uint32_t data_input_interrupt_enable       : 1;    // bit 0
            /// Digest calculation completion interrupt enable (DCIE)
            uint32_t data_calculation_interrupt_enable : 1;    // bit 1
            /// (reserved)
            uint32_t                                   : 30;    // bits 2:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        InterruptManagement& operator=(InterruptManagement&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(InterruptManagement volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(InterruptManagement const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<InterruptManagement>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(InterruptManagement) == 4UL, "Must be this exact size");
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
            /// Data input interrupt status (DINIS)
            uint32_t data_input_interrupt_status                  : 1;    // bit 0
            /// Digest calculation completion interrupt status (DCIS)
            uint32_t data_calculation_completion_interrupt_status : 1;    // bit 1
            /// DMA Status (DMAS)
            uint32_t direct_memory_access_status                  : 1;    // bit 2
            /// Busy bit (BUSY)
            uint32_t busy                                         : 1;    // bit 3
            /// (reserved)
            uint32_t                                              : 28;    // bits 4:31
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
    /// context swap registers (CSR0)
    struct CSR0 final {
        /// Default Constructor
        CSR0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR0(CSR0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR0(CSR0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR0(CSR0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR0 (CSR0)
            uint32_t csr0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR0& operator=(CSR0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR0) == 4UL, "Must be this exact size");
    /// context swap registers (CSR1)
    struct CSR1 final {
        /// Default Constructor
        CSR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR1(CSR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR1(CSR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR1(CSR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR1 (CSR1)
            uint32_t csr1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR1& operator=(CSR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR1) == 4UL, "Must be this exact size");
    /// context swap registers (CSR2)
    struct CSR2 final {
        /// Default Constructor
        CSR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR2(CSR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR2(CSR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR2(CSR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR2 (CSR2)
            uint32_t csr2 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR2& operator=(CSR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR2) == 4UL, "Must be this exact size");
    /// context swap registers (CSR3)
    struct CSR3 final {
        /// Default Constructor
        CSR3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR3(CSR3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR3(CSR3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR3(CSR3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR3 (CSR3)
            uint32_t csr3 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR3& operator=(CSR3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR3) == 4UL, "Must be this exact size");
    /// context swap registers (CSR4)
    struct CSR4 final {
        /// Default Constructor
        CSR4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR4(CSR4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR4(CSR4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR4(CSR4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR4 (CSR4)
            uint32_t csr4 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR4& operator=(CSR4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR4) == 4UL, "Must be this exact size");
    /// context swap registers (CSR5)
    struct CSR5 final {
        /// Default Constructor
        CSR5()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR5(CSR5 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR5(CSR5 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR5(CSR5&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR5(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR5(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR5() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR5 (CSR5)
            uint32_t csr5 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR5& operator=(CSR5&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR5 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR5 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR5>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR5) == 4UL, "Must be this exact size");
    /// context swap registers (CSR6)
    struct CSR6 final {
        /// Default Constructor
        CSR6()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR6(CSR6 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR6(CSR6 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR6(CSR6&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR6(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR6(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR6() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR6 (CSR6)
            uint32_t csr6 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR6& operator=(CSR6&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR6 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR6 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR6>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR6) == 4UL, "Must be this exact size");
    /// context swap registers (CSR7)
    struct CSR7 final {
        /// Default Constructor
        CSR7()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR7(CSR7 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR7(CSR7 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR7(CSR7&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR7(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR7(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR7() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR7 (CSR7)
            uint32_t csr7 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR7& operator=(CSR7&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR7 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR7 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR7>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR7) == 4UL, "Must be this exact size");
    /// context swap registers (CSR8)
    struct CSR8 final {
        /// Default Constructor
        CSR8()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR8(CSR8 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR8(CSR8 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR8(CSR8&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR8(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR8(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR8() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR8 (CSR8)
            uint32_t csr8 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR8& operator=(CSR8&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR8 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR8 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR8>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR8) == 4UL, "Must be this exact size");
    /// context swap registers (CSR9)
    struct CSR9 final {
        /// Default Constructor
        CSR9()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR9(CSR9 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR9(CSR9 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR9(CSR9&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR9(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR9(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR9() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR9 (CSR9)
            uint32_t csr9 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR9& operator=(CSR9&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR9 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR9 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR9>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR9) == 4UL, "Must be this exact size");
    /// context swap registers (CSR10)
    struct CSR10 final {
        /// Default Constructor
        CSR10()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR10(CSR10 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR10(CSR10 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR10(CSR10&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR10(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR10(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR10() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR10 (CSR10)
            uint32_t csr10 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR10& operator=(CSR10&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR10 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR10 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR10>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR10) == 4UL, "Must be this exact size");
    /// context swap registers (CSR11)
    struct CSR11 final {
        /// Default Constructor
        CSR11()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR11(CSR11 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR11(CSR11 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR11(CSR11&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR11(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR11(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR11() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR11 (CSR11)
            uint32_t csr11 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR11& operator=(CSR11&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR11 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR11 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR11>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR11) == 4UL, "Must be this exact size");
    /// context swap registers (CSR12)
    struct CSR12 final {
        /// Default Constructor
        CSR12()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR12(CSR12 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR12(CSR12 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR12(CSR12&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR12(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR12(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR12() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR12 (CSR12)
            uint32_t csr12 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR12& operator=(CSR12&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR12 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR12 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR12>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR12) == 4UL, "Must be this exact size");
    /// context swap registers (CSR13)
    struct CSR13 final {
        /// Default Constructor
        CSR13()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR13(CSR13 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR13(CSR13 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR13(CSR13&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR13(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR13(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR13() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR13 (CSR13)
            uint32_t csr13 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR13& operator=(CSR13&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR13 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR13 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR13>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR13) == 4UL, "Must be this exact size");
    /// context swap registers (CSR14)
    struct CSR14 final {
        /// Default Constructor
        CSR14()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR14(CSR14 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR14(CSR14 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR14(CSR14&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR14(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR14(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR14() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR14 (CSR14)
            uint32_t csr14 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR14& operator=(CSR14&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR14 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR14 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR14>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR14) == 4UL, "Must be this exact size");
    /// context swap registers (CSR15)
    struct CSR15 final {
        /// Default Constructor
        CSR15()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR15(CSR15 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR15(CSR15 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR15(CSR15&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR15(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR15(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR15() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR15 (CSR15)
            uint32_t csr15 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR15& operator=(CSR15&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR15 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR15 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR15>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR15) == 4UL, "Must be this exact size");
    /// context swap registers (CSR16)
    struct CSR16 final {
        /// Default Constructor
        CSR16()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR16(CSR16 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR16(CSR16 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR16(CSR16&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR16(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR16(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR16() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR16 (CSR16)
            uint32_t csr16 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR16& operator=(CSR16&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR16 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR16 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR16>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR16) == 4UL, "Must be this exact size");
    /// context swap registers (CSR17)
    struct CSR17 final {
        /// Default Constructor
        CSR17()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR17(CSR17 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR17(CSR17 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR17(CSR17&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR17(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR17(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR17() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR17 (CSR17)
            uint32_t csr17 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR17& operator=(CSR17&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR17 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR17 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR17>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR17) == 4UL, "Must be this exact size");
    /// context swap registers (CSR18)
    struct CSR18 final {
        /// Default Constructor
        CSR18()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR18(CSR18 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR18(CSR18 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR18(CSR18&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR18(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR18(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR18() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR18 (CSR18)
            uint32_t csr18 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR18& operator=(CSR18&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR18 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR18 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR18>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR18) == 4UL, "Must be this exact size");
    /// context swap registers (CSR19)
    struct CSR19 final {
        /// Default Constructor
        CSR19()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR19(CSR19 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR19(CSR19 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR19(CSR19&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR19(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR19(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR19() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR19 (CSR19)
            uint32_t csr19 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR19& operator=(CSR19&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR19 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR19 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR19>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR19) == 4UL, "Must be this exact size");
    /// context swap registers (CSR20)
    struct CSR20 final {
        /// Default Constructor
        CSR20()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR20(CSR20 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR20(CSR20 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR20(CSR20&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR20(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR20(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR20() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR20 (CSR20)
            uint32_t csr20 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR20& operator=(CSR20&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR20 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR20 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR20>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR20) == 4UL, "Must be this exact size");
    /// context swap registers (CSR21)
    struct CSR21 final {
        /// Default Constructor
        CSR21()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR21(CSR21 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR21(CSR21 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR21(CSR21&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR21(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR21(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR21() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR21 (CSR21)
            uint32_t csr21 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR21& operator=(CSR21&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR21 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR21 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR21>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR21) == 4UL, "Must be this exact size");
    /// context swap registers (CSR22)
    struct CSR22 final {
        /// Default Constructor
        CSR22()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR22(CSR22 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR22(CSR22 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR22(CSR22&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR22(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR22(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR22() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR22 (CSR22)
            uint32_t csr22 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR22& operator=(CSR22&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR22 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR22 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR22>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR22) == 4UL, "Must be this exact size");
    /// context swap registers (CSR23)
    struct CSR23 final {
        /// Default Constructor
        CSR23()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR23(CSR23 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR23(CSR23 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR23(CSR23&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR23(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR23(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR23() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR23 (CSR23)
            uint32_t csr23 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR23& operator=(CSR23&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR23 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR23 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR23>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR23) == 4UL, "Must be this exact size");
    /// context swap registers (CSR24)
    struct CSR24 final {
        /// Default Constructor
        CSR24()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR24(CSR24 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR24(CSR24 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR24(CSR24&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR24(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR24(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR24() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR24 (CSR24)
            uint32_t csr24 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR24& operator=(CSR24&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR24 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR24 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR24>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR24) == 4UL, "Must be this exact size");
    /// context swap registers (CSR25)
    struct CSR25 final {
        /// Default Constructor
        CSR25()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR25(CSR25 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR25(CSR25 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR25(CSR25&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR25(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR25(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR25() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR25 (CSR25)
            uint32_t csr25 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR25& operator=(CSR25&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR25 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR25 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR25>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR25) == 4UL, "Must be this exact size");
    /// context swap registers (CSR26)
    struct CSR26 final {
        /// Default Constructor
        CSR26()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR26(CSR26 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR26(CSR26 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR26(CSR26&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR26(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR26(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR26() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR26 (CSR26)
            uint32_t csr26 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR26& operator=(CSR26&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR26 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR26 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR26>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR26) == 4UL, "Must be this exact size");
    /// context swap registers (CSR27)
    struct CSR27 final {
        /// Default Constructor
        CSR27()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR27(CSR27 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR27(CSR27 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR27(CSR27&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR27(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR27(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR27() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR27 (CSR27)
            uint32_t csr27 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR27& operator=(CSR27&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR27 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR27 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR27>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR27) == 4UL, "Must be this exact size");
    /// context swap registers (CSR28)
    struct CSR28 final {
        /// Default Constructor
        CSR28()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR28(CSR28 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR28(CSR28 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR28(CSR28&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR28(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR28(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR28() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR28 (CSR28)
            uint32_t csr28 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR28& operator=(CSR28&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR28 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR28 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR28>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR28) == 4UL, "Must be this exact size");
    /// context swap registers (CSR29)
    struct CSR29 final {
        /// Default Constructor
        CSR29()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR29(CSR29 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR29(CSR29 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR29(CSR29&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR29(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR29(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR29() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR29 (CSR29)
            uint32_t csr29 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR29& operator=(CSR29&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR29 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR29 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR29>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR29) == 4UL, "Must be this exact size");
    /// context swap registers (CSR30)
    struct CSR30 final {
        /// Default Constructor
        CSR30()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR30(CSR30 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR30(CSR30 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR30(CSR30&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR30(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR30(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR30() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR30 (CSR30)
            uint32_t csr30 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR30& operator=(CSR30&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR30 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR30 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR30>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR30) == 4UL, "Must be this exact size");
    /// context swap registers (CSR31)
    struct CSR31 final {
        /// Default Constructor
        CSR31()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR31(CSR31 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR31(CSR31 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR31(CSR31&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR31(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR31(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR31() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR31 (CSR31)
            uint32_t csr31 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR31& operator=(CSR31&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR31 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR31 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR31>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR31) == 4UL, "Must be this exact size");
    /// context swap registers (CSR32)
    struct CSR32 final {
        /// Default Constructor
        CSR32()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR32(CSR32 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR32(CSR32 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR32(CSR32&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR32(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR32(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR32() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR32 (CSR32)
            uint32_t csr32 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR32& operator=(CSR32&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR32 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR32 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR32>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR32) == 4UL, "Must be this exact size");
    /// context swap registers (CSR33)
    struct CSR33 final {
        /// Default Constructor
        CSR33()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR33(CSR33 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR33(CSR33 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR33(CSR33&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR33(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR33(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR33() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR33 (CSR33)
            uint32_t csr33 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR33& operator=(CSR33&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR33 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR33 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR33>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR33) == 4UL, "Must be this exact size");
    /// context swap registers (CSR34)
    struct CSR34 final {
        /// Default Constructor
        CSR34()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR34(CSR34 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR34(CSR34 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR34(CSR34&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR34(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR34(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR34() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR34 (CSR34)
            uint32_t csr34 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR34& operator=(CSR34&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR34 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR34 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR34>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR34) == 4UL, "Must be this exact size");
    /// context swap registers (CSR35)
    struct CSR35 final {
        /// Default Constructor
        CSR35()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR35(CSR35 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR35(CSR35 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR35(CSR35&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR35(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR35(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR35() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR35 (CSR35)
            uint32_t csr35 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR35& operator=(CSR35&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR35 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR35 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR35>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR35) == 4UL, "Must be this exact size");
    /// context swap registers (CSR36)
    struct CSR36 final {
        /// Default Constructor
        CSR36()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR36(CSR36 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR36(CSR36 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR36(CSR36&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR36(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR36(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR36() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR36 (CSR36)
            uint32_t csr36 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR36& operator=(CSR36&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR36 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR36 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR36>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR36) == 4UL, "Must be this exact size");
    /// context swap registers (CSR37)
    struct CSR37 final {
        /// Default Constructor
        CSR37()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR37(CSR37 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR37(CSR37 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR37(CSR37&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR37(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR37(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR37() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR37 (CSR37)
            uint32_t csr37 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR37& operator=(CSR37&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR37 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR37 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR37>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR37) == 4UL, "Must be this exact size");
    /// context swap registers (CSR38)
    struct CSR38 final {
        /// Default Constructor
        CSR38()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR38(CSR38 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR38(CSR38 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR38(CSR38&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR38(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR38(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR38() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR38 (CSR38)
            uint32_t csr38 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR38& operator=(CSR38&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR38 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR38 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR38>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR38) == 4UL, "Must be this exact size");
    /// context swap registers (CSR39)
    struct CSR39 final {
        /// Default Constructor
        CSR39()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR39(CSR39 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR39(CSR39 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR39(CSR39&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR39(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR39(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR39() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR39 (CSR39)
            uint32_t csr39 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR39& operator=(CSR39&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR39 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR39 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR39>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR39) == 4UL, "Must be this exact size");
    /// context swap registers (CSR40)
    struct CSR40 final {
        /// Default Constructor
        CSR40()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR40(CSR40 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR40(CSR40 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR40(CSR40&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR40(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR40(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR40() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR40 (CSR40)
            uint32_t csr40 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR40& operator=(CSR40&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR40 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR40 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR40>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR40) == 4UL, "Must be this exact size");
    /// context swap registers (CSR41)
    struct CSR41 final {
        /// Default Constructor
        CSR41()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR41(CSR41 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR41(CSR41 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR41(CSR41&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR41(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR41(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR41() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR41 (CSR41)
            uint32_t csr41 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR41& operator=(CSR41&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR41 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR41 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR41>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR41) == 4UL, "Must be this exact size");
    /// context swap registers (CSR42)
    struct CSR42 final {
        /// Default Constructor
        CSR42()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR42(CSR42 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR42(CSR42 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR42(CSR42&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR42(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR42(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR42() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR42 (CSR42)
            uint32_t csr42 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR42& operator=(CSR42&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR42 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR42 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR42>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR42) == 4UL, "Must be this exact size");
    /// context swap registers (CSR43)
    struct CSR43 final {
        /// Default Constructor
        CSR43()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR43(CSR43 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR43(CSR43 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR43(CSR43&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR43(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR43(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR43() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR43 (CSR43)
            uint32_t csr43 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR43& operator=(CSR43&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR43 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR43 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR43>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR43) == 4UL, "Must be this exact size");
    /// context swap registers (CSR44)
    struct CSR44 final {
        /// Default Constructor
        CSR44()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR44(CSR44 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR44(CSR44 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR44(CSR44&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR44(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR44(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR44() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR44 (CSR44)
            uint32_t csr44 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR44& operator=(CSR44&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR44 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR44 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR44>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR44) == 4UL, "Must be this exact size");
    /// context swap registers (CSR45)
    struct CSR45 final {
        /// Default Constructor
        CSR45()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR45(CSR45 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR45(CSR45 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR45(CSR45&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR45(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR45(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR45() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR45 (CSR45)
            uint32_t csr45 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR45& operator=(CSR45&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR45 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR45 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR45>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR45) == 4UL, "Must be this exact size");
    /// context swap registers (CSR46)
    struct CSR46 final {
        /// Default Constructor
        CSR46()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR46(CSR46 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR46(CSR46 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR46(CSR46&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR46(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR46(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR46() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR46 (CSR46)
            uint32_t csr46 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR46& operator=(CSR46&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR46 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR46 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR46>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR46) == 4UL, "Must be this exact size");
    /// context swap registers (CSR47)
    struct CSR47 final {
        /// Default Constructor
        CSR47()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR47(CSR47 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR47(CSR47 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR47(CSR47&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR47(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR47(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR47() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR47 (CSR47)
            uint32_t csr47 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR47& operator=(CSR47&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR47 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR47 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR47>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR47) == 4UL, "Must be this exact size");
    /// context swap registers (CSR48)
    struct CSR48 final {
        /// Default Constructor
        CSR48()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR48(CSR48 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR48(CSR48 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR48(CSR48&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR48(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR48(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR48() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR48 (CSR48)
            uint32_t csr48 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR48& operator=(CSR48&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR48 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR48 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR48>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR48) == 4UL, "Must be this exact size");
    /// context swap registers (CSR49)
    struct CSR49 final {
        /// Default Constructor
        CSR49()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR49(CSR49 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR49(CSR49 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR49(CSR49&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR49(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR49(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR49() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR49 (CSR49)
            uint32_t csr49 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR49& operator=(CSR49&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR49 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR49 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR49>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR49) == 4UL, "Must be this exact size");
    /// context swap registers (CSR50)
    struct CSR50 final {
        /// Default Constructor
        CSR50()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR50(CSR50 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR50(CSR50 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR50(CSR50&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR50(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR50(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR50() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR50 (CSR50)
            uint32_t csr50 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR50& operator=(CSR50&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR50 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR50 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR50>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR50) == 4UL, "Must be this exact size");
    /// context swap registers (CSR51)
    struct CSR51 final {
        /// Default Constructor
        CSR51()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR51(CSR51 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR51(CSR51 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR51(CSR51&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR51(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR51(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR51() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR51 (CSR51)
            uint32_t csr51 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR51& operator=(CSR51&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR51 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR51 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR51>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR51) == 4UL, "Must be this exact size");
    /// context swap registers (CSR52)
    struct CSR52 final {
        /// Default Constructor
        CSR52()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR52(CSR52 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR52(CSR52 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR52(CSR52&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR52(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR52(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR52() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR52 (CSR52)
            uint32_t csr52 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR52& operator=(CSR52&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR52 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR52 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR52>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR52) == 4UL, "Must be this exact size");
    /// context swap registers (CSR53)
    struct CSR53 final {
        /// Default Constructor
        CSR53()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CSR53(CSR53 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CSR53(CSR53 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CSR53(CSR53&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CSR53(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CSR53(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CSR53() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// CSR53 (CSR53)
            uint32_t csr53 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CSR53& operator=(CSR53&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CSR53 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CSR53 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CSR53>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CSR53) == 4UL, "Must be this exact size");
    /// HASH digest register (HASH_HR0)
    struct HASH_HR0 final {
        /// Default Constructor
        HASH_HR0()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR0(HASH_HR0 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR0(HASH_HR0 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR0(HASH_HR0&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR0(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR0(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR0() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H0 (H0)
            uint32_t h0 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR0& operator=(HASH_HR0&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR0 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR0 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR0>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR0) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR1)
    struct HASH_HR1 final {
        /// Default Constructor
        HASH_HR1()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR1(HASH_HR1 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR1(HASH_HR1 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR1(HASH_HR1&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR1(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR1(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR1() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H1 (H1)
            uint32_t h1 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR1& operator=(HASH_HR1&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR1 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR1 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR1>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR1) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR2)
    struct HASH_HR2 final {
        /// Default Constructor
        HASH_HR2()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR2(HASH_HR2 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR2(HASH_HR2 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR2(HASH_HR2&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR2(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR2(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR2() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H2 (H2)
            uint32_t h2 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR2& operator=(HASH_HR2&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR2 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR2 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR2>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR2) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR3)
    struct HASH_HR3 final {
        /// Default Constructor
        HASH_HR3()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR3(HASH_HR3 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR3(HASH_HR3 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR3(HASH_HR3&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR3(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR3(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR3() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H3 (H3)
            uint32_t h3 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR3& operator=(HASH_HR3&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR3 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR3 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR3>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR3) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR4)
    struct HASH_HR4 final {
        /// Default Constructor
        HASH_HR4()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR4(HASH_HR4 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR4(HASH_HR4 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR4(HASH_HR4&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR4(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR4(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR4() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H4 (H4)
            uint32_t h4 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR4& operator=(HASH_HR4&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR4 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR4 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR4>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR4) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR5)
    struct HASH_HR5 final {
        /// Default Constructor
        HASH_HR5()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR5(HASH_HR5 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR5(HASH_HR5 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR5(HASH_HR5&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR5(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR5(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR5() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H5 (H5)
            uint32_t h5 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR5& operator=(HASH_HR5&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR5 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR5 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR5>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR5) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR6)
    struct HASH_HR6 final {
        /// Default Constructor
        HASH_HR6()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR6(HASH_HR6 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR6(HASH_HR6 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR6(HASH_HR6&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR6(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR6(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR6() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H6 (H6)
            uint32_t h6 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR6& operator=(HASH_HR6&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR6 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR6 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR6>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR6) == 4UL, "Must be this exact size");
    /// read-only (HASH_HR7)
    struct HASH_HR7 final {
        /// Default Constructor
        HASH_HR7()
            : whole{0u} {}
        /// Copy Constructor from volatile
        HASH_HR7(HASH_HR7 volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        HASH_HR7(HASH_HR7 const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        HASH_HR7(HASH_HR7&&) = delete;
        /// Parameterized Constructor for constant references
        explicit HASH_HR7(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit HASH_HR7(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~HASH_HR7() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// H7 (H7)
            uint32_t h7 : 32;    // bits 0:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        HASH_HR7& operator=(HASH_HR7&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(HASH_HR7 volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(HASH_HR7 const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<HASH_HR7>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(HASH_HR7) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// control register (CR)
    Control control;    // offset 0x0UL
    /// data input register (DIN)
    DataInput data_input;    // offset 0x4UL
    /// start register (STR)
    Start start;    // offset 0x8UL
    /// digest registers (HR0-HR7)
    uint32_t small_digest[5];    // offset 0xcUL
    /// interrupt enable register (IMR)
    InterruptManagement interrupt_management;    // offset 0x20UL
    /// status register (SR)
    Status status;    // offset 0x24UL
    uint32_t : 32;    // offset 0x28UL
    uint32_t : 32;    // offset 0x2cUL
    uint32_t : 32;    // offset 0x30UL
    uint32_t : 32;    // offset 0x34UL
    uint32_t : 32;    // offset 0x38UL
    uint32_t : 32;    // offset 0x3cUL
    uint32_t : 32;    // offset 0x40UL
    uint32_t : 32;    // offset 0x44UL
    uint32_t : 32;    // offset 0x48UL
    uint32_t : 32;    // offset 0x4cUL
    uint32_t : 32;    // offset 0x50UL
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
    /// context swap registers (CSR0-CSR53)
    uint32_t context_swap[54];    // offset 0xf8UL
    uint32_t : 32;                // offset 0x1d0UL
    uint32_t : 32;                // offset 0x1d4UL
    uint32_t : 32;                // offset 0x1d8UL
    uint32_t : 32;                // offset 0x1dcUL
    uint32_t : 32;                // offset 0x1e0UL
    uint32_t : 32;                // offset 0x1e4UL
    uint32_t : 32;                // offset 0x1e8UL
    uint32_t : 32;                // offset 0x1ecUL
    uint32_t : 32;                // offset 0x1f0UL
    uint32_t : 32;                // offset 0x1f4UL
    uint32_t : 32;                // offset 0x1f8UL
    uint32_t : 32;                // offset 0x1fcUL
    uint32_t : 32;                // offset 0x200UL
    uint32_t : 32;                // offset 0x204UL
    uint32_t : 32;                // offset 0x208UL
    uint32_t : 32;                // offset 0x20cUL
    uint32_t : 32;                // offset 0x210UL
    uint32_t : 32;                // offset 0x214UL
    uint32_t : 32;                // offset 0x218UL
    uint32_t : 32;                // offset 0x21cUL
    uint32_t : 32;                // offset 0x220UL
    uint32_t : 32;                // offset 0x224UL
    uint32_t : 32;                // offset 0x228UL
    uint32_t : 32;                // offset 0x22cUL
    uint32_t : 32;                // offset 0x230UL
    uint32_t : 32;                // offset 0x234UL
    uint32_t : 32;                // offset 0x238UL
    uint32_t : 32;                // offset 0x23cUL
    uint32_t : 32;                // offset 0x240UL
    uint32_t : 32;                // offset 0x244UL
    uint32_t : 32;                // offset 0x248UL
    uint32_t : 32;                // offset 0x24cUL
    uint32_t : 32;                // offset 0x250UL
    uint32_t : 32;                // offset 0x254UL
    uint32_t : 32;                // offset 0x258UL
    uint32_t : 32;                // offset 0x25cUL
    uint32_t : 32;                // offset 0x260UL
    uint32_t : 32;                // offset 0x264UL
    uint32_t : 32;                // offset 0x268UL
    uint32_t : 32;                // offset 0x26cUL
    uint32_t : 32;                // offset 0x270UL
    uint32_t : 32;                // offset 0x274UL
    uint32_t : 32;                // offset 0x278UL
    uint32_t : 32;                // offset 0x27cUL
    uint32_t : 32;                // offset 0x280UL
    uint32_t : 32;                // offset 0x284UL
    uint32_t : 32;                // offset 0x288UL
    uint32_t : 32;                // offset 0x28cUL
    uint32_t : 32;                // offset 0x290UL
    uint32_t : 32;                // offset 0x294UL
    uint32_t : 32;                // offset 0x298UL
    uint32_t : 32;                // offset 0x29cUL
    uint32_t : 32;                // offset 0x2a0UL
    uint32_t : 32;                // offset 0x2a4UL
    uint32_t : 32;                // offset 0x2a8UL
    uint32_t : 32;                // offset 0x2acUL
    uint32_t : 32;                // offset 0x2b0UL
    uint32_t : 32;                // offset 0x2b4UL
    uint32_t : 32;                // offset 0x2b8UL
    uint32_t : 32;                // offset 0x2bcUL
    uint32_t : 32;                // offset 0x2c0UL
    uint32_t : 32;                // offset 0x2c4UL
    uint32_t : 32;                // offset 0x2c8UL
    uint32_t : 32;                // offset 0x2ccUL
    uint32_t : 32;                // offset 0x2d0UL
    uint32_t : 32;                // offset 0x2d4UL
    uint32_t : 32;                // offset 0x2d8UL
    uint32_t : 32;                // offset 0x2dcUL
    uint32_t : 32;                // offset 0x2e0UL
    uint32_t : 32;                // offset 0x2e4UL
    uint32_t : 32;                // offset 0x2e8UL
    uint32_t : 32;                // offset 0x2ecUL
    uint32_t : 32;                // offset 0x2f0UL
    uint32_t : 32;                // offset 0x2f4UL
    uint32_t : 32;                // offset 0x2f8UL
    uint32_t : 32;                // offset 0x2fcUL
    uint32_t : 32;                // offset 0x300UL
    uint32_t : 32;                // offset 0x304UL
    uint32_t : 32;                // offset 0x308UL
    uint32_t : 32;                // offset 0x30cUL
    /// HASH digest register (HASH_HR0-HASH_HR7)
    uint32_t digest[8];    // offset 0x310UL
    uint32_t : 32;         // offset 0x330UL
    uint32_t : 32;         // offset 0x334UL
    uint32_t : 32;         // offset 0x338UL
    uint32_t : 32;         // offset 0x33cUL
    uint32_t : 32;         // offset 0x340UL
    uint32_t : 32;         // offset 0x344UL
    uint32_t : 32;         // offset 0x348UL
    uint32_t : 32;         // offset 0x34cUL
    uint32_t : 32;         // offset 0x350UL
    uint32_t : 32;         // offset 0x354UL
    uint32_t : 32;         // offset 0x358UL
    uint32_t : 32;         // offset 0x35cUL
    uint32_t : 32;         // offset 0x360UL
    uint32_t : 32;         // offset 0x364UL
    uint32_t : 32;         // offset 0x368UL
    uint32_t : 32;         // offset 0x36cUL
    uint32_t : 32;         // offset 0x370UL
    uint32_t : 32;         // offset 0x374UL
    uint32_t : 32;         // offset 0x378UL
    uint32_t : 32;         // offset 0x37cUL
    uint32_t : 32;         // offset 0x380UL
    uint32_t : 32;         // offset 0x384UL
    uint32_t : 32;         // offset 0x388UL
    uint32_t : 32;         // offset 0x38cUL
    uint32_t : 32;         // offset 0x390UL
    uint32_t : 32;         // offset 0x394UL
    uint32_t : 32;         // offset 0x398UL
    uint32_t : 32;         // offset 0x39cUL
    uint32_t : 32;         // offset 0x3a0UL
    uint32_t : 32;         // offset 0x3a4UL
    uint32_t : 32;         // offset 0x3a8UL
    uint32_t : 32;         // offset 0x3acUL
    uint32_t : 32;         // offset 0x3b0UL
    uint32_t : 32;         // offset 0x3b4UL
    uint32_t : 32;         // offset 0x3b8UL
    uint32_t : 32;         // offset 0x3bcUL
    uint32_t : 32;         // offset 0x3c0UL
    uint32_t : 32;         // offset 0x3c4UL
    uint32_t : 32;         // offset 0x3c8UL
    uint32_t : 32;         // offset 0x3ccUL
    uint32_t : 32;         // offset 0x3d0UL
    uint32_t : 32;         // offset 0x3d4UL
    uint32_t : 32;         // offset 0x3d8UL
    uint32_t : 32;         // offset 0x3dcUL
    uint32_t : 32;         // offset 0x3e0UL
    uint32_t : 32;         // offset 0x3e4UL
    uint32_t : 32;         // offset 0x3e8UL
    uint32_t : 32;         // offset 0x3ecUL
    uint32_t : 32;         // offset 0x3f0UL
    uint32_t : 32;         // offset 0x3f4UL
    uint32_t : 32;         // offset 0x3f8UL
    uint32_t : 32;         // offset 0x3fcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<Hash>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(Hash, control) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(Hash, data_input) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(Hash, start) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(Hash, small_digest) == 0xcUL, "Must be located at this offset");
static_assert(offsetof(Hash, interrupt_management) == 0x20UL, "Must be located at this offset");
static_assert(offsetof(Hash, status) == 0x24UL, "Must be located at this offset");
static_assert(offsetof(Hash, context_swap) == 0xf8UL, "Must be located at this offset");
static_assert(offsetof(Hash, digest) == 0x310UL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(Hash) == 0x400UL, "Must be this exact size");

/// The external volatile hash which is a memory mapped register or peripheral.
/// @note The address of the peripheral is set either by the linkerscript or by a unit test.
extern Hash volatile hash;
}    // namespace registers
}    // namespace stm32
#endif    // STM32_REGISTERS_HASH__HPP_