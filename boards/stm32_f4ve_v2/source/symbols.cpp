#include "jarnax.hpp"

// Pretend we have hardware here
#if defined(UNITTEST)

#if defined(HAS_FLASH)
// Fake Flash
std::uint8_t flash[stm32::sizes::flash];
#endif
#if defined(HAS_CCM)
// Fake Couple Memory
alignas(8) uint8_t ccm[stm32::sizes::ccm];
uint32_t *__ccm_beg = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__ccm_end = reinterpret_cast<std::uint32_t *>(&ccm[sizeof(ccm)]);
#endif
#if defined(HAS_ITCM)
// Fake Instruction TCM
alignas(8) uint8_t itcm[stm32::sizes::itcm];
uint32_t *__itcm_beg = reinterpret_cast<std::uint32_t *>(&itcm[0]);
uint32_t *__itcm_end = reinterpret_cast<std::uint32_t *>(&itcm[sizeof(itcm)]);
#endif
#if defined(HAS_DTCM)
// Fake Data TCM
alignas(8) uint8_t dtcm[stm32::sizes::dtcm];
uint32_t *__dtcm_beg = reinterpret_cast<std::uint32_t *>(&dtcm[0]);
uint32_t *__dtcm_end = reinterpret_cast<std::uint32_t *>(&dtcm[dimof(dtcm)]);
#endif
#if defined(HAS_SRAM)
// Fake System RAM
alignas(8) uint8_t sram[stm32::sizes::sram];
uint32_t *__sram_beg = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__sram_end = reinterpret_cast<std::uint32_t *>(&sram[sizeof(sram)]);
#endif

// Try to mirror the link script here with rough divisions
uint32_t *__bss_end = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__bss_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__data_end = reinterpret_cast<std::uint32_t *>(&flash[0]);
uint32_t *__data_start = reinterpret_cast<std::uint32_t *>(&flash[0]);
uint32_t *__data_load = reinterpret_cast<std::uint32_t *>(&sram[0]);
destructor *__fini_array_end = reinterpret_cast<destructor *>(&sram[0]);
destructor *__fini_array_start = reinterpret_cast<destructor *>(&sram[0]);
constructor *__init_array_end = reinterpret_cast<constructor *>(&sram[0]);
constructor *__init_array_start = reinterpret_cast<constructor *>(&sram[0]);
uint32_t *__main_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);
uint32_t *__main_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm]);
uint32_t *__main_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm]);
uint32_t *__main_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__main_stack_top - __main_stack_bottom));
uint32_t *__process_stack_bottom = reinterpret_cast<std::uint32_t *>(&ccm[0]);
uint32_t *__process_stack_top = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);
uint32_t *__process_stack_ceiling = reinterpret_cast<std::uint32_t *>(&ccm[stm32::sizes::ccm / 2]);
uint32_t *__process_stack_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__process_stack_top - __process_stack_bottom));
uint32_t *__privileged_data_start = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__privileged_data_end = reinterpret_cast<std::uint32_t *>(&sram[0]);
uint32_t *__privileged_data_size = reinterpret_cast<std::uint32_t *>(ptrdiff_t(__privileged_data_end - __privileged_data_start));

constructor *__preinit_array_end = nullptr;
constructor *__preinit_array_start = nullptr;

#endif