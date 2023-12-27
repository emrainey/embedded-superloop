#include "jarnax.hpp"

// Pretend we have hardware here

#if defined(HAS_FLASH)
// Fake Flash
uint8_t flash[stm32::sizes::flash];
#endif
#if defined(HAS_CCM)
// Fake Couple Memory
uint8_t ccm[stm32::sizes::ccm];
uint8_t *__ccm_beg = &ccm[0];
uint8_t *__ccm_end = &ccm[sizeof(ccm)];
#endif
#if defined(HAS_ITCM)
// Fake Instruction TCM
uint8_t itcm[stm32::sizes::itcm];
uint8_t *__itcm_beg = &itcm[0];
uint8_t *__itcm_end = &itcm[sizeof(itcm)];
#endif
#if defined(HAS_DTCM)
// Fake Data TCM
uint8_t dtcm[stm32::sizes::dtcm];
uint8_t *__dtcm_beg = &dtcm[0];
uint8_t *__dtcm_end = &dtcm[sizeof(dtcm)];
#endif
#if defined(HAS_SRAM)
// Fake System RAM
uint8_t sram[stm32::sizes::sram];
uint8_t *__sram_beg = &sram[0];
uint8_t *__sram_end = &sram[sizeof(sram)];
#endif

// Try to mirror the link script here with rough divisions
uint8_t *__bss_end = &sram[0];
uint8_t *__bss_start = &sram[0];
uint8_t *__data_end = &flash[0];
uint8_t *__data_start = &flash[0];
uint8_t *__data_load = &sram[0];
uint8_t *__fini_array_end = &sram[0];
uint8_t *__fini_array_start = &sram[0];
uint8_t *__init_array_end = &sram[0];
uint8_t *__init_array_start = &sram[0];
uint8_t *__main_stack_bottom = &ccm[stm32::sizes::ccm / 2];
uint8_t *__main_stack_top = &ccm[stm32::sizes::ccm];
uint8_t *__main_stack_ceiling = &ccm[stm32::sizes::ccm];
uint8_t *__main_stack_size = reinterpret_cast<uint8_t *>(ptrdiff_t(__main_stack_top - __main_stack_bottom));
uint8_t *__process_stack_bottom = &ccm[0];
uint8_t *__process_stack_top = &ccm[stm32::sizes::ccm / 2];
uint8_t *__process_stack_ceiling = &ccm[stm32::sizes::ccm / 2];
uint8_t *__process_stack_size = reinterpret_cast<uint8_t *>(ptrdiff_t(__process_stack_top - __process_stack_bottom));
uint8_t *__privileged_data_start = &sram[0];
uint8_t *__privileged_data_end = &sram[0];
uint8_t *__privileged_data_size = reinterpret_cast<uint8_t *>(ptrdiff_t(__privileged_data_end - __privileged_data_start));

uint8_t *__preinit_array_end = nullptr;
uint8_t *__preinit_array_start = nullptr;
