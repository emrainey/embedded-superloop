/**
 * The GNU Linker Script for a Cortex M7 microcontroller.
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

/* Some of these values have to be set in the Chip specific linker script */

MEMORY {
    /* The architecture reference manual breaks the default Cortex M space down like this: */
    ITCM         (rwx) : ORIGIN = 0x00000000, LENGTH = ITCM_SIZE
    FLASH         (rx) : ORIGIN = 0x08000000, LENGTH = FLASH_SIZE
    DTCM          (rw) : ORIGIN = 0x20000000, LENGTH = DTCM_SIZE
    SRAM          (rw) : ORIGIN = 0x20400000, LENGTH = SRAM_SIZE
    PERIPH        (rw) : ORIGIN = 0x40000000, LENGTH = 0x20000000
    EXTRAM        (rw) : ORIGIN = 0x60000000, LENGTH = 0x40000000
    DEVICE        (rw) : ORIGIN = 0xA0000000, LENGTH = 0x40000000
    PPB           (rw) : ORIGIN = 0xE0000000, LENGTH = 1M
    VENDOR        (rw) : ORIGIN = 0xE0100000, LENGTH = 0x1FF00000
}

REGION_ALIAS("REGION_TEXT",    FLASH);
REGION_ALIAS("REGION_RODATA",  FLASH);
REGION_ALIAS("REGION_DATA",    SRAM);
REGION_ALIAS("REGION_BSS",     SRAM);
REGION_ALIAS("REGION_STACK",   DTCM);
REGION_ALIAS("REGION_SYSTEM",  PPB);
REGION_ALIAS("REGION_HEAP",    SRAM);

/* DMA CAN NOT BE LOCATED IN ITCM or DTCM! */

__cortex_flash_start = ORIGIN(FLASH);
__cortex_flash_limit = ORIGIN(FLASH) + LENGTH(FLASH);
__cortex_flash_size = LENGTH(FLASH);
__cortex_flash_pow2  = LOG2CEIL(__cortex_flash_size);

__cortex_stack_start = ORIGIN(DTCM);
__cortex_stack_limit = ORIGIN(DTCM) + LENGTH(DTCM);
__cortex_stack_size = LENGTH(DTCM);
__cortex_stack_pow2  = LOG2CEIL(__cortex_stack_size);

__cortex_sram_start = ORIGIN(SRAM);
__cortex_sram_limit = ORIGIN(SRAM) + LENGTH(SRAM);
__cortex_sram_size = LENGTH(SRAM);
__cortex_sram_pow2  = LOG2CEIL(__cortex_sram_size);

/* APB1 is the lowest peripheral address */
__cortex_peripheral_start = ORIGIN(DEVICE);
__cortex_peripheral_limit = ORIGIN(DEVICE) + LENGTH(DEVICE);
__cortex_peripheral_size = __cortex_peripheral_limit - __cortex_peripheral_start;
__cortex_peripheral_pow2  = LOG2CEIL(__cortex_peripheral_size);

__cortex_system_start = ORIGIN(PPB);
__cortex_system_limit = ORIGIN(PPB) + LENGTH(PPB);
__cortex_system_size = LENGTH(PPB);
__cortex_system_pow2  = LOG2CEIL(__cortex_system_size);