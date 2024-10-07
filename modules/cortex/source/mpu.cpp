#include "cortex/mpu.hpp"

namespace cortex {

MemoryProtectionUnit::Access make_access(MemoryProtectionUnit::Attribute attribute) {
    MemoryProtectionUnit::Access access;
    access.whole = 0U;
    access.bits.subregion_disable = 0U;    // all subregions enabled
    access.bits.enable = 1U;
    if (attribute == MemoryProtectionUnit::Attribute::StronglyOrdered) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 0U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::DeviceSharedProcessor) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 0U;
        access.bits.bufferable = 1U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::DeviceSingleProcessor) {
        access.bits.type_extension = 2U;
        access.bits.cacheable = 0U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 0U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteThroughShared) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteThroughSingle) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 0U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateShared) {
        access.bits.type_extension = 1U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 1U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteBackWriteAllocateSingle) {
        access.bits.type_extension = 1U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 1U;
        access.bits.sharable = 0U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteBackNoWriteAllocateShared) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 1U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalWriteBackNoWriteAllocateSingle) {
        access.bits.type_extension = 0U;
        access.bits.cacheable = 1U;
        access.bits.bufferable = 1U;
        access.bits.sharable = 0U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalNonCacheableShared) {
        access.bits.type_extension = 1U;
        access.bits.cacheable = 0U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 1U;
    } else if (attribute == MemoryProtectionUnit::Attribute::NormalNonCacheableSingle) {
        access.bits.type_extension = 1U;
        access.bits.cacheable = 0U;
        access.bits.bufferable = 0U;
        access.bits.sharable = 0U;
    }
    return access;
}
}    // namespace cortex