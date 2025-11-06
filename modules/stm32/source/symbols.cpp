#include "configure.hpp"
#include "core/Intervals.hpp"
#include "cortex/linker.hpp"
#include "cortex/m4.hpp"
#include "cortex/mcu.hpp"
#include "cortex/vectors.hpp"
#include "iso.hpp"
#include "jarnax.hpp"
#include "polyfill.hpp"

// Pretend we have hardware here
#if defined(UNITTEST)

using namespace ::iso;

#if defined(CORTEX_HAS_ITCM) and (CORTEX_HAS_ITCM == 1)
// Fake Instruction TCM
alignas(8) uint8_t itcm[64_KiB];
uint32_t *__itcm_beg = reinterpret_cast<std::uint32_t *>(&itcm[0]);
uint32_t *__itcm_end = reinterpret_cast<std::uint32_t *>(&itcm[sizeof(itcm)]);
#endif
#if defined(CORTEX_HAS_FLASH) and (CORTEX_HAS_FLASH == 1)
// Fake Flash
alignas(8) std::uint8_t flash[4_MiB];
uint32_t *__cortex_flash_start = reinterpret_cast<std::uint32_t *>(&flash[0]);
uint32_t *__cortex_flash_limit = reinterpret_cast<std::uint32_t *>(&flash[sizeof(flash)]);
uint32_t *__cortex_flash_used = nullptr;
uint32_t *__cortex_flash_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_flash_limit - __cortex_flash_start));
uint32_t *__cortex_flash_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(sizeof(flash)));
#endif
#if defined(CORTEX_HAS_CCM) and (CORTEX_HAS_CCM == 1)
// Fake Couple Memory
alignas(8) uint8_t ccm[128_KiB];
uint32_t *__ccm_beg = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__ccm_end = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm)]);
uint32_t *__main_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm) / 2]);
uint32_t *__main_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm)]);
uint32_t *__main_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm)]);
uint32_t *__main_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__main_stack_top - __main_stack_bottom));
uint32_t *__process_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__process_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm) / 2]);
uint32_t *__process_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm) / 2]);

uint32_t *__cortex_stack_start = __ccm_beg;
uint32_t *__cortex_stack_limit = __ccm_end;
uint32_t *__cortex_stack_used = nullptr;
uint32_t *__cortex_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_stack_limit - __cortex_stack_start));
uint32_t *__cortex_stack_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(ptrdiff_t(__cortex_stack_limit - __cortex_stack_start)));
#endif
#if defined(CORTEX_HAS_DTCM) and (CORTEX_HAS_DTCM == 1)
// Fake Data TCM
alignas(8) uint8_t dtcm[128 * 1024];
uint32_t *__dtcm_beg = reinterpret_cast<std::uint32_t *>(&dtcm[0]);
uint32_t *__dtcm_end = reinterpret_cast<std::uint32_t *>(&dtcm[dimof(dtcm)]);
#endif
#if defined(CORTEX_HAS_SRAM) and (CORTEX_HAS_SRAM == 1)
// Fake System RAM
alignas(8) uint8_t sram[512_KiB];
uint32_t *__sram_beg = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__sram_end = reinterpret_cast<std::uint32_t *>(&sram[sizeof(sram)]);
uint32_t *__cortex_sram_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__cortex_sram_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(sizeof(sram)));

alignas(8) uint8_t bkupram[4_KiB];
uint32_t *__cortex_backup_start = reinterpret_cast<std::uint32_t *>(&bkupram[0]);
uint32_t *__cortex_backup_limit = reinterpret_cast<std::uint32_t *>(&bkupram[sizeof(bkupram)]);
uint32_t *__cortex_backup_used = nullptr;
uint32_t *__cortex_backup_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_backup_limit - __cortex_backup_start));
uint32_t *__cortex_backup_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(sizeof(bkupram)));

// Try to mirror the link script here with rough divisions
uint32_t *__bss_end = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__bss_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
#if defined(CORTEX_HAS_FLASH) and (CORTEX_HAS_FLASH == 1)
uint32_t *__data_end = reinterpret_cast<std::uint32_t *>(&flash[0]);
uint32_t *__data_start = reinterpret_cast<std::uint32_t *>(&flash[0]);
#endif
uint32_t *__data_load = reinterpret_cast<std::uint32_t *>(&sram[0]);
cortex::destructor *__fini_array_end = reinterpret_cast<cortex::destructor *>(&sram[0]);
cortex::destructor *__fini_array_start = reinterpret_cast<cortex::destructor *>(&sram[0]);
cortex::constructor *__init_array_end = reinterpret_cast<cortex::constructor *>(&sram[0]);
cortex::constructor *__init_array_start = reinterpret_cast<cortex::constructor *>(&sram[0]);
uint32_t *__privileged_data_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__privileged_data_end = reinterpret_cast<std::uint32_t *>(&sram[0]);
#endif

uint32_t *__process_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__process_stack_top - __process_stack_bottom));
uint32_t *__privileged_data_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__privileged_data_end - __privileged_data_start));
cortex::constructor *__preinit_array_end = nullptr;
cortex::constructor *__preinit_array_start = nullptr;

alignas(8) std::uint8_t peripherals[64_KiB];    // Not the accurate size

uint32_t *__cortex_peripheral_start = reinterpret_cast<std::uint32_t *>(&peripherals[0]);
uint32_t *__cortex_peripheral_limit = reinterpret_cast<std::uint32_t *>(&peripherals[0] + sizeof(peripherals));
uint32_t *__cortex_peripheral_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_peripheral_limit - __cortex_peripheral_start));
uint32_t *__cortex_peripheral_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(sizeof(peripherals)));    // assumption

uint32_t ppb[64_KiB];

uint32_t *__cortex_system_start = reinterpret_cast<std::uint32_t *>(&ppb[0]);                       // starting at 0xE000E000
uint32_t *__cortex_system_limit = reinterpret_cast<std::uint32_t *>(&ppb[0] + sizeof(ppb));         // 64KB of system
uint32_t *__cortex_system_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_system_limit - __cortex_system_start));
uint32_t *__cortex_system_pow2 = reinterpret_cast<std::uint32_t *>(polyfill::log2(sizeof(ppb)));    // 64KB of system is

ZeroEntry zero_table[] = {
#if defined(CORTEX_HAS_CCM) and (CORTEX_HAS_CCM == 1)
    {reinterpret_cast<std::uintptr_t>(__ccm_beg), reinterpret_cast<std::uintptr_t>(__ccm_end)},
#endif
#if defined(CORTEX_HAS_ITCM) and (CORTEX_HAS_ITCM == 1)
    {reinterpret_cast<std::uintptr_t>(__itcm_beg), reinterpret_cast<std::uintptr_t>(__itcm_end)},
#endif
#if defined(CORTEX_HAS_DTCM) and (CORTEX_HAS_DTCM == 1)
    {reinterpret_cast<std::uintptr_t>(__dtcm_beg), reinterpret_cast<std::uintptr_t>(__dtcm_end)},
#endif
#if defined(CORTEX_HAS_SRAM) and (CORTEX_HAS_SRAM == 1)
    {reinterpret_cast<std::uintptr_t>(__sram_beg), reinterpret_cast<std::uintptr_t>(__sram_end)},
#endif
};

ZeroEntry *__zero_table_start = &zero_table[0];
ZeroEntry *__zero_table_limit = &zero_table[dimof(zero_table)];

namespace cortex {

core::Interval const sorted_memory_regions[] = {
#if defined(CORTEX_HAS_ITCM) and (CORTEX_HAS_ITCM == 1)
    {reinterpret_cast<std::uintptr_t>(&itcm[0]), reinterpret_cast<std::uintptr_t>(&itcm[sizeof(itcm)] - 1)},
#endif
    {reinterpret_cast<std::uintptr_t>(&flash[0]), reinterpret_cast<std::uintptr_t>(&flash[dimof(flash)] - 1)},
#if defined(CORTEX_HAS_CCM) and (CORTEX_HAS_CCM == 1)
    {reinterpret_cast<std::uintptr_t>(&ccm[0]), reinterpret_cast<std::uintptr_t>(&ccm[sizeof(ccm)] - 1)},
#endif
#if defined(CORTEX_HAS_DTCM) and (CORTEX_HAS_DTCM == 1)
    {reinterpret_cast<std::uintptr_t>(&dtcm[0]), reinterpret_cast<std::uintptr_t>(&dtcm[dimof(dtcm)] - 1)},
#endif
#if defined(CORTEX_HAS_SRAM) and (CORTEX_HAS_SRAM == 1)
    {reinterpret_cast<std::uintptr_t>(&sram[0]), reinterpret_cast<std::uintptr_t>(&sram[dimof(sram)] - 1)},
#endif
};

std::uint32_t const sorted_memory_region_count = dimof(sorted_memory_regions);
std::uint32_t const *sorted_region_count = &sorted_memory_region_count;

}    // namespace cortex

#endif
