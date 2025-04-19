/**
 * The GNU Linker Script for the STM32F407VE microcontroller.
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

STACK_SIZE = 32K;
FLASH_SIZE = 512K;

/* All 3 of these are considered the available SRAM of 196K */
CCM_SIZE = 64K;
SRAM_SIZE = 128K;
BKPRSRAM_SIZE = 4k;

INCLUDE cortex-m4.ld
