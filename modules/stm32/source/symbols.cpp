#include "configure.hpp"
#include "cortex/linker.hpp"
#include "cortex/m4.hpp"
#include "cortex/mcu.hpp"
#include "cortex/vectors.hpp"
#include "jarnax.hpp"

// Pretend we have hardware here
#if defined(UNITTEST)

#if defined(CORTEX_HAS_FLASH) and (CORTEX_HAS_FLASH == 1)
// Fake Flash
std::uint8_t flash[stm32::sizes::flash];
uint32_t *__cortex_flash_start = reinterpret_cast<std::uint32_t *>(&flash[0]);
uint32_t *__cortex_flash_limit = reinterpret_cast<std::uint32_t *>(&flash[sizeof(flash)]);
uint32_t *__cortex_flash_used = nullptr;
uint32_t *__cortex_flash_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_flash_limit - __cortex_flash_start));
uint32_t *__cortex_flash_pow2 = reinterpret_cast<std::uint32_t *>(stm32::sizes::power2::flash);
#endif
#if defined(CORTEX_HAS_CCM) and (CORTEX_HAS_CCM == 1)
// Fake Couple Memory
alignas(8) uint8_t ccm[stm32::sizes::ccm];
uint32_t *__ccm_beg = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__ccm_end = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm)]);
uint32_t *__main_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);
uint32_t *__main_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm]);
uint32_t *__main_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm]);
uint32_t *__main_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__main_stack_top - __main_stack_bottom));
uint32_t *__process_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__process_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);
uint32_t *__process_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);

uint32_t *__cortex_stack_start = __ccm_beg;
uint32_t *__cortex_stack_limit = __ccm_end;
uint32_t *__cortex_stack_used = nullptr;
uint32_t *__cortex_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_stack_limit - __cortex_stack_start));
uint32_t *__cortex_stack_pow2 = reinterpret_cast<std::uint32_t *>(cortex::sizes::power2::stack);
#endif
#if defined(CORTEX_HAS_ITCM) and (CORTEX_HAS_ITCM == 1)
// Fake Instruction TCM
alignas(8) uint8_t itcm[stm32::sizes::itcm];
uint32_t *__itcm_beg = reinterpret_cast<std::uint32_t *>(&itcm[0]);
uint32_t *__itcm_end = reinterpret_cast<std::uint32_t *>(&itcm[sizeof(itcm)]);
#endif
#if defined(CORTEX_HAS_DTCM) and (CORTEX_HAS_DTCM == 1)
// Fake Data TCM
alignas(8) uint8_t dtcm[stm32::sizes::dtcm];
uint32_t *__dtcm_beg = reinterpret_cast<std::uint32_t *>(&dtcm[0]);
uint32_t *__dtcm_end = reinterpret_cast<std::uint32_t *>(&dtcm[dimof(dtcm)]);
#endif
#if defined(CORTEX_HAS_SRAM) and (CORTEX_HAS_SRAM == 1)
// Fake System RAM
alignas(8) uint8_t sram[stm32::sizes::sram];
uint32_t *__sram_beg = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__sram_end = reinterpret_cast<std::uint32_t *>(&sram[sizeof(sram)]);
uint32_t *__cortex_sram_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__cortex_sram_pow2 = reinterpret_cast<std::uint32_t *>(stm32::sizes::power2::sram);

alignas(8) uint8_t bkupram[stm32::sizes::backup_sram];
uint32_t *__cortex_backup_start = reinterpret_cast<std::uint32_t *>(&bkupram[0]);
uint32_t *__cortex_backup_limit = reinterpret_cast<std::uint32_t *>(&bkupram[sizeof(bkupram)]);
uint32_t *__cortex_backup_used = nullptr;
uint32_t *__cortex_backup_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_backup_limit - __cortex_backup_start));
uint32_t *__cortex_backup_pow2 = reinterpret_cast<std::uint32_t *>(stm32::sizes::power2::backup_sram);

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

uint32_t *__cortex_peripheral_start = reinterpret_cast<std::uint32_t *>(cortex::variant::address::peripheral);
uint32_t *__cortex_peripheral_limit = reinterpret_cast<std::uint32_t *>(cortex::variant::address::peripheral + cortex::variant::sizes::peripheral);
uint32_t *__cortex_peripheral_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_peripheral_limit - __cortex_peripheral_start));
uint32_t *__cortex_peripheral_pow2 = reinterpret_cast<std::uint32_t *>(20);                                  // assumption

uint32_t *__cortex_system_start = reinterpret_cast<std::uint32_t *>(cortex::variant::address::system);       // starting at 0xE000E000
uint32_t *__cortex_system_limit =
    reinterpret_cast<std::uint32_t *>(cortex::variant::address::system + cortex::variant::sizes::system);    // 64KB of system
uint32_t *__cortex_system_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__cortex_system_limit - __cortex_system_start));
uint32_t *__cortex_system_pow2 = reinterpret_cast<std::uint32_t *>(16);                                      // 64KB of system is

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

#endif
