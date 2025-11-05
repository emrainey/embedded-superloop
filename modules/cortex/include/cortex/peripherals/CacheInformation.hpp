
#ifndef CORTEX_CACHE_INFORMATION_HPP_
#define CORTEX_CACHE_INFORMATION_HPP_

/// @file
/// Auto Generated Structure Definitions for CacheInformation from the Peripheralyzer.
/// @copyright

#include "cortex/types.hpp"

namespace cortex {
namespace peripherals {

/// Cortex M7 Cache Information
struct CacheInformation final {
    /// Cache Level ID Register (CLDIR)
    struct CacheLevelID final {
        /// Default Constructor
        CacheLevelID()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CacheLevelID(CacheLevelID volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CacheLevelID(CacheLevelID const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CacheLevelID(CacheLevelID&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CacheLevelID(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CacheLevelID(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CacheLevelID() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Level Cache Type
            uint32_t level_cache_type     : 2;    // bits 0:1
            /// (reserved)
            uint32_t                      : 22;    // bits 2:23
            /// Level of Coherency
            uint32_t level_of_coherency   : 3;    // bits 24:26
            /// Level of Unification
            uint32_t level_of_unification : 3;    // bits 27:29
            /// (reserved)
            uint32_t                      : 2;    // bits 30:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CacheLevelID& operator=(CacheLevelID&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CacheLevelID volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CacheLevelID const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CacheLevelID>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CacheLevelID) == 4UL, "Must be this exact size");
    /// Cache Size ID Register (CCSIDR)
    struct CacheSizeID final {
        /// Default Constructor
        CacheSizeID()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CacheSizeID(CacheSizeID volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CacheSizeID(CacheSizeID const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CacheSizeID(CacheSizeID&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CacheSizeID(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CacheSizeID(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CacheSizeID() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Line Size
            uint32_t line_size              : 3;    // bits 0:2
            /// Associativity
            uint32_t associativity          : 10;    // bits 3:12
            /// Number of Sets
            uint32_t number_of_sets         : 15;    // bits 13:27
            /// Write Allocate Support
            uint32_t support_write_allocate : 1;    // bit 28
            /// Read Allocation Support
            uint32_t support_read_allocate  : 1;    // bit 29
            /// Write Back Support
            uint32_t support_write_back     : 1;    // bit 30
            /// Write Through Support
            uint32_t support_write_through  : 1;    // bit 31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CacheSizeID& operator=(CacheSizeID&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CacheSizeID volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CacheSizeID const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CacheSizeID>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CacheSizeID) == 4UL, "Must be this exact size");
    /// Cache Size Selection Register (CSSELR)
    struct CacheSizeSelection final {
        /// Default Constructor
        CacheSizeSelection()
            : whole{0u} {}
        /// Copy Constructor from volatile
        CacheSizeSelection(CacheSizeSelection volatile const& other)
            : whole{other.whole} {}
        /// Copy Construction from nonvolatile
        CacheSizeSelection(CacheSizeSelection const& other)
            : whole{other.whole} {}
        /// Move Constructor is deleted
        CacheSizeSelection(CacheSizeSelection&&) = delete;
        /// Parameterized Constructor for constant references
        explicit CacheSizeSelection(uint32_t const& value)
            : whole{value} {}
        /// Parameterized Constructor for volatile references
        explicit CacheSizeSelection(uint32_t volatile& value)
            : whole{value} {}
        /// Destructor is empty
        ~CacheSizeSelection() = default;

        /// The internal bitfield for the register
        struct Fields final {
            /// Instruction (1) or Data Cache (0) (InD)
            uint32_t cache_type : 1;    // bit 0
            /// Cache Level Select (Level) 0=L1, 1=L2, etc. RAZ/WI
            uint32_t level      : 3;    // bits 1:3
            /// (reserved)
            uint32_t            : 28;    // bits 4:31
        };
        //+=MEMORY======================================+
        union {
            Fields bits;
            uint32_t whole;
        };
        //+=MEMORY======================================+
        /// Move Assignment is deleted
        CacheSizeSelection& operator=(CacheSizeSelection&&) = delete;
        /// Assignment from a volatile to a non volatile copy of the register.
        /// @note Does not return a reference
        inline void operator=(CacheSizeSelection volatile& other) { whole = other.whole; }
        /// Assignment from a non volatile to a volatile register
        /// @note Does not return a reference
        inline void operator=(CacheSizeSelection const& other) volatile { whole = other.whole; }
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
    static_assert(std::is_standard_layout<CacheSizeSelection>::value, "Must be standard layout");
    // Ensure the sizeof the entire register is correct.
    static_assert(sizeof(CacheSizeSelection) == 4UL, "Must be this exact size");

    //+=MEMORY======================================+
    /// Cache Level ID Register (CLIDR)
    CacheLevelID cache_level_id;    // offset 0x0UL
    /// Cache Type ID Register (CTIDR) --- IGNORE ---
    uint32_t cache_type_id;    // offset 0x4UL
    /// Cache Size ID Register (CCSIDR)
    CacheSizeID cache_size_id;    // offset 0x8UL
    /// Cache Size Selection Register (CSSELR)
    CacheSizeSelection cache_size_selection;    // offset 0xcUL
    //+=MEMORY======================================+
};
// Ensure the structure is in standard layout format
static_assert(std::is_standard_layout<CacheInformation>::value, "Must be standard layout");
// Ensure the offsets are all correct
static_assert(offsetof(CacheInformation, cache_level_id) == 0x0UL, "Must be located at this offset");
static_assert(offsetof(CacheInformation, cache_type_id) == 0x4UL, "Must be located at this offset");
static_assert(offsetof(CacheInformation, cache_size_id) == 0x8UL, "Must be located at this offset");
static_assert(offsetof(CacheInformation, cache_size_selection) == 0xcUL, "Must be located at this offset");

// Ensure the sizeof the entire structure is correct.
static_assert(sizeof(CacheInformation) == 0x10UL, "Must be this exact size");

}    // namespace peripherals
}    // namespace cortex
#endif    // CORTEX_CACHE_INFORMATION_HPP_
