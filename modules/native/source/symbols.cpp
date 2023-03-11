#include "jarnax.hpp"

// Pretend we have hardware here

// Fake Flash
uint8_t flash[stm32::sizes::flash];
// Fake Couple Memory
uint8_t ccm[stm32::sizes::ccm];
// Fake System RAM
uint8_t sram[stm32::sizes::sram];

uint8_t *__ccm_beg = &ccm[0];
uint8_t *__ccm_end = &ccm[sizeof(ccm)];
uint8_t *__sram_beg = &sram[0];
uint8_t *__sram_end = &sram[sizeof(sram)];
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
uint8_t *__privileged_data_size =
    reinterpret_cast<uint8_t *>(ptrdiff_t(__privileged_data_end - __privileged_data_start));

uint8_t *__preinit_array_end = nullptr;
uint8_t *__preinit_array_start = nullptr;
