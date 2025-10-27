/**
 * The GNU Linker Script for the STM32F407VE microcontroller.
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

/* Normally we would include the cortex-m7.ld script here, but we need to override
 * nearly all memory regions to get all the features of the chip enabled. */

/* INCLUDE cortex-m7.ld */

MEMORY {
    ITCM         (rwx) : ORIGIN = 0x00000000, LENGTH = 64K
    SYSROM1       (rx) : ORIGIN = 0x1FF00000, LENGTH = 128K
    SYSROM2       (rx) : ORIGIN = 0x1FF40000, LENGTH = 128K
    FLASH         (rx) : ORIGIN = 0x08000000, LENGTH = 2M
    DTCM          (rw) : ORIGIN = 0x20000000, LENGTH = 128K
    AXISRAM       (rw) : ORIGIN = 0x24000000, LENGTH = 512K
    SRAM123       (rw) : ORIGIN = 0x30000000, LENGTH = 288K
    SRAM4         (rw) : ORIGIN = 0x38000000, LENGTH = 64K
    BKUP          (rw) : ORIGIN = 0x38800000, LENGTH = 4K
    APB1          (rw) : ORIGIN = 0x40000000, LENGTH = 0x0000D400
    APB2          (rw) : ORIGIN = 0x40010000, LENGTH = 0x00007800
    AHB1          (rw) : ORIGIN = 0x40020000, LENGTH = 0x000A0000
    AHB2          (rw) : ORIGIN = 0x48020000, LENGTH = 0x00002C00
    APB3          (rw) : ORIGIN = 0x50000000, LENGTH = 0x00004000
    AHB3          (rw) : ORIGIN = 0x51000000, LENGTH = 0x01009000
    APB4          (rw) : ORIGIN = 0x58000000, LENGTH = 0x00006C00
    AHB4          (rw) : ORIGIN = 0x58020000, LENGTH = 0x00007400
    PPB           (rw) : ORIGIN = 0xE0000000, LENGTH = 1M
    VENDOR        (rw) : ORIGIN = 0xE0100000, LENGTH = 0x1FF00000
}

REGION_ALIAS("REGION_TEXT",    FLASH);
REGION_ALIAS("REGION_RODATA",  FLASH);
REGION_ALIAS("REGION_DATA",    SRAM123);
REGION_ALIAS("REGION_BSS",     AXIRAM);
REGION_ALIAS("REGION_STACK",   DTCM);
REGION_ALIAS("REGION_SYSTEM",  PPB);
REGION_ALIAS("REGION_HEAP",    SRAM4);

ITCM_SIZE = LENGTH(ITCM);
DTCM_SIZE = LENGTH(DTCM);
SRAM_SIZE = LENGTH(AXIRAM) + LENGTH(SRAM123) + LENGTH(SRAM4);
BKUP_SIZE = LENGTH(BKUP);
FLASH_SIZE = LENGTH(FLASH);
/* For two stacks, Main and Process */
STACK_SIZE = DTCM_SIZE / 2;

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
__cortex_peripheral_start = ORIGIN(APB1);
__cortex_peripheral_limit = 0x60000000;
__cortex_peripheral_size = __cortex_peripheral_limit - __cortex_peripheral_start;
__cortex_peripheral_pow2  = LOG2CEIL(__cortex_peripheral_size);

__cortex_system_start = ORIGIN(PPB);
__cortex_system_limit = ORIGIN(PPB) + LENGTH(PPB);
__cortex_system_size = LENGTH(PPB);
__cortex_system_pow2  = LOG2CEIL(__cortex_system_size);

