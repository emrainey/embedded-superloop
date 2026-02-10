
#include "configure.hpp"
//=============================
#include "cortex/cache.hpp"
#include "cortex/supervisor.hpp"
//=============================
#include "jarnax/L1DataCache.hpp"    // from internal jarnax

namespace jarnax {

void L1DataCache::Enable() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::enable();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::Enable;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Disable() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::disable();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::Disable;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Invalidate() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::invalidate();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::Invalidate;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Invalidate(std::uintptr_t address, size_t bytes) {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::invalidate(address, bytes);
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::InvalidateByAddress;
        marshal.type.data_cache.address = address;
        marshal.type.data_cache.size = bytes;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Clean() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::clean();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::Clean;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Clean(std::uintptr_t address, size_t bytes) {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::clean(address, bytes);
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::CleanByAddress;
        marshal.type.data_cache.address = address;
        marshal.type.data_cache.size = bytes;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Flush() {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::flush();
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::Flush;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

void L1DataCache::Flush(std::uintptr_t address, size_t bytes) {
    if constexpr (cortex::run_in_privileged_mode_only) {
        cortex::cache::data::flush(address, bytes);
    } else {
        cortex::supervisor::Marshal marshal;
        marshal.call = cortex::supervisor::Marshal::Calls::DataCache;
        marshal.type.data_cache.operation = cortex::supervisor::Marshal::Arguments::DataCache::Operations::FlushByAddress;
        marshal.type.data_cache.address = address;
        marshal.type.data_cache.size = bytes;
        thumb::supervisor<polyfill::to_underlying(cortex::supervisor::Marshal::Calls::DataCache)>(&marshal.type.generic);
    }
}

}    // namespace jarnax
