#ifndef CORTEX_M_MPU_HPP_
#define CORTEX_M_MPU_HPP_

/// @file
/// The Cortex M Core Header

#include "cortex/core.hpp"
#include "core/Split.hpp"

namespace cortex {

/// @brief The default number of regions allowed on a Cortex M processor
constexpr static size_t kDefaultRegionLimit{16U};

/// The Memory Protection Unit
struct MemoryProtectionUnit {
    /// The type register
    /// @see MPU_TYPE
    struct Type final {
        Type()
            : whole{0U} {}
        /// Copy Constructor
        Type(Type volatile& other)
            : whole{other.whole} {}

        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t separate                      : 1U;
            std::uint32_t                               : 7U;    ///< Reserved field
            std::uint32_t number_of_data_regions        : 8U;    //<! Unifed number of regions (in doc as number of data regions)
            std::uint32_t number_of_instruction_regions : 8U;
            std::uint32_t                               : 8U;    ///< Reserved field
        };
        /// @brief The union of the bitfield and the register as a whole.
        union {
            Fields bits;
            std::uint32_t whole;
        };
    };

    /// The control register
    /// @see MPU_CTRL
    struct Control final {
        Control()
            : whole{0U} {}
        /// Copy Constructor
        Control(Control volatile& other)
            : whole{other.whole} {}
        /// @brief The bitfield definition of the register
        struct Fields final {
            std::uint32_t enable                           : 1U;
            std::uint32_t core_handlers_use_mpu            : 1U;
            std::uint32_t default_memory_map_in_privileged : 1U;
            std::uint32_t                                  : 29U;    ///< Reserved field
        };
        /// @brief The union of the bitfield and the register as a whole.
        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Write Only Assignment
        void operator=(Control volatile& other) volatile { whole = other.whole; }
    };

    /// The Region Register
    struct Region final {
        Region()
            : whole{0U} {}
        /// Copy Constructor
        Region(Region volatile& other)
            : whole{other.whole} {}
        struct Fields final {
            std::uint32_t number : 8U;     ///< The region value. @see MPU_RNR
            std::uint32_t        : 24U;    ///< Reserved field
        };
        union {
            Fields parts;
            std::uint32_t whole;
        };
        /// Write Only Assignment
        void operator=(Region volatile& other) volatile { whole = other.whole; }
    };

    /// The base address register
    /// @see MPU_RBAR
    class BaseAddress final {
    public:
#if defined(__arm__)
        using AddressType = std::uint32_t;
#elif defined(__x86_64__) or defined(__aarch64__) or defined(__arm64__)
        using AddressType = std::uint64_t;
#endif
        /// Default Constructor
        // BaseAddress() : whole{0U} {}
        /// Copy Constructor
        // BaseAddress(BaseAddress volatile& other) : whole{other.whole} {}
        /// Parameter Constructor
        // BaseAddress(uintptr_t addr) {
        void Set(uintptr_t addr) volatile {
            /// The register field only wants the top 27 bits (the pointer will be forced to align to 32 bytes)
            core::Split<AddressType, 5U> tmp;
            /// put the address into the tmp
            tmp.whole = addr;
            // we'll use the external RNR
            parts.region = 0U;
            parts.valid = 0U;
            parts.address = tmp.parts.upper;
        }
        /// Readable Copy Assignment
        void operator=(BaseAddress const& other) volatile { whole = other.whole; }
        /// Write Only Operator
        void operator=(BaseAddress volatile& other) { whole = other.whole; }

        struct Fields final {
            AddressType region : 4U;
            AddressType valid  : 1U;
            ///@todo Find a way to make this a uintptr_t again. Compiler was very insistent that it
            /// would not allow a narrowing here, which is nice but not useful in this one place
            AddressType address : (sizeof(AddressType) * 8u) - 5u;    // 27 in 32 bit, more on 64 bit
        };
        union {
            Fields parts;
            AddressType whole;
        };
    };
    static_assert(sizeof(BaseAddress) == sizeof(std::uintptr_t), "Must be this size exactly");

    /// Each entry does not correlate to a bit position change but does try to consistently apply
    /// permissions similar to the rwx bits in a file system.
    /// The access choices are RO (Read Only), RW (Read/Write) and NA (No Access)
    enum class Permissions : std::uint8_t {
        NA_Priv_NA_User = 0b000,
        RW_Priv_NA_User = 0b001,
        RW_Priv_RO_User = 0b010,
        RW_Priv_RW_User = 0b011,
        RO_Priv_NA_User = 0b101,
        RO_Priv_RO_User = 0b110,    //!< Also == 0b111
    };

    /// The access register
    /// @see MPU_RASR
    struct Access final {
        /// Default Constructor
        constexpr Access()
            : whole{0U} {}
        /// Copy Constructor
        constexpr Access(const cortex::MemoryProtectionUnit::Access& other)
            : whole{other.whole} {}

        /// @brief The bitfield definition of the register
        class Fields {    // anonymous
        public:
            std::uint32_t enable : 1U;    //!< Enable the region

        private:
            std::uint32_t pow2_size : 5U;    //!< The power of 2 field. Limited to 0-31 inclusive (do not set directly)

        public:
            std::uint32_t                   : 2U;
            std::uint32_t subregion_disable : 8U;
            std::uint32_t bufferable        : 1U;
            std::uint32_t cacheable         : 1U;
            std::uint32_t sharable          : 1U;
            std::uint32_t type_extension    : 3U;    ///< This field is so poorly documented!
            std::uint32_t                   : 2U;
            Permissions permissions         : 3U;
            std::uint32_t                   : 1U;
            std::uint32_t execute_never     : 1U;
            std::uint32_t                   : 3U;

            /// Setting the Power of Two Size requires this interface
            /// to ensure it is done correctly w/ all the strict flags on.
            inline bool set_power2_size(std::uint32_t bytes) volatile {
                if (::is_power_of_two(bytes)) {
                    core::Split<std::uint32_t, 5U> tmp;
                    tmp.whole = polyfill::log2(bytes);
                    pow2_size = tmp.parts.lower;
                    return true;
                }
                return false;
            }
            /// Setting the Power of Two Size requires this interface
            /// to ensure it is done correctly w/ all the strict flags on.
            inline void set_power2_size(std::uint8_t power2) volatile {
                core::Split<std::uint32_t, 5U> tmp;
                tmp.whole = power2;
                pow2_size = tmp.parts.lower;
            }
        };

        union {
            Fields bits;
            std::uint32_t whole;
        };
        /// Write Only Operator on Volatile from Normal
        void operator=(Access& other) volatile { whole = other.whole; }
        /// Write Only Operator on Volatile from Const
        void operator=(Access const& other) volatile { whole = other.whole; }
        /// Write Only Operator on Volatile from Volatile
        void operator=(Access volatile& other) volatile { whole = other.whole; }
    };
    static_assert(sizeof(Access) == sizeof(std::uint32_t), "Must be this size exactly");

    //=======================
    // MEMORY
    //=======================
    Type type;
    Control control;
    Region region;
    BaseAddress base;
    Access access;
    //=======================

    /// Returns the number of regions this processor supports
    inline std::uint32_t get_number_of_regions(void) volatile {
        if (type.bits.separate == 1U) {
            return type.bits.number_of_data_regions + type.bits.number_of_instruction_regions;
        } else {
            return type.bits.number_of_data_regions;
        }
    }

    /// The various memory region types. This does not map to any specific cortex field directly.
    enum class Attribute : std::uint32_t {
        StronglyOrdered,                         ///< Implicitly sharable as all transactions are in program order.
        DeviceSharedProcessor,                   ///< For Memory Mapped Peripherals accessed by Multiple Cores.
        DeviceSingleProcessor,                   ///< For Memory Mapped Peripherals accessed by a Single Core.
        NormalWriteThroughShared,                ///< Normal Memory which is marked as Write Through and possible accessed by
                                                 ///< multiple cores.
        NormalWriteThroughSingle,                ///< Normal Memory which is marked as Write Through but only accessed by one core.
        NormalWriteBackWriteAllocateShared,      ///< Normal Memory with Write Back and Write Allocate from multiple
                                                 ///< processors
        NormalWriteBackWriteAllocateSingle,      ///< Normal Memory with Write Back and Write Allocate from one processor
        NormalWriteBackNoWriteAllocateShared,    ///< Normal Memory with Write Back but not Write Allocate from multiple
                                                 ///< processors
        NormalWriteBackNoWriteAllocateSingle,    ///< Normal Memory with Write Back but not Write Allocate from one
                                                 ///< processor
        NormalNonCacheableShared,                ///< Normal memory but uncacheable access from multiple cores
        NormalNonCacheableSingle,                ///< Normal memory but uncacheable access from a single core
    };
};

/// Creates an Access Register filled in from the given attribute
/// @param attribute
MemoryProtectionUnit::Access make_access(MemoryProtectionUnit::Attribute attribute);

/// An enumerated count of the various protected regions in the MPU
enum class ProtectedRegion : std::uint8_t {
    Code = 0U,              ///< The .text section
    Data = 1U,              ///< The section of RAM which contains the .bss and .data
    Stack = 2U,             ///< The Full Stack area
    MainStack = 3U,         ///< Just the Main Stack area (comes after Stack)
    ProcesStack = 4U,       ///< Just the Process Stack area (comes after Main)
    PrivilegedData = 5U,    ///< The section of RAM dedicated to the Privilege mode (comes after Data)
    Peripherals = 6U,       ///< Device memory mapped peripherals
    Backup = 7U,            ///< The backup RAM area (for low power mode, if supported), (must overlay Peripherals)
    System = 8U,            ///< The system processor memory map
};

}    // namespace cortex

#endif    // CORTEX_M_MPU_HPP_