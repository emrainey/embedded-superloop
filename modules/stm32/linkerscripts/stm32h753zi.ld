/**
 * The GNU Linker Script for the STM32F407VE microcontroller.
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

/* Normally we would include the cortex-m7.ld script here, but we need to override
 * nearly all memory regions to get all the features of the chip enabled. */

FLASH_SIZE = 2M;

/* All 3 of these together are considered the available SRAM of 196K */
ITCM_SIZE = 64K;
DTCM_SIZE = 128K;
/* we'll calculate SRAM_SIZE later as it's not contiguous */
BKPRSRAM_SIZE = 4K;

/* For two stacks, Main and Process */
STACK_SIZE = DTCM_SIZE / 2;

/* INCLUDE cortex-m7.ld */

MEMORY {
    /* +============================================================+ */
    ITCM         (rwx) : ORIGIN = 0x00000000, LENGTH = ITCM_SIZE
    /* gap */
    FLASH         (rx) : ORIGIN = 0x08000000, LENGTH = FLASH_SIZE
    /* gap */
    SYSROM        (rx) : ORIGIN = 0x1FF00000, LENGTH = 256K
    /* gap */
    /* +============================================================+ */
    DTCM          (rw) : ORIGIN = 0x20000000, LENGTH = DTCM_SIZE
    /* gap */
    AXISRAM       (rw) : ORIGIN = 0x24000000, LENGTH = 512K
    /* gap */
    SRAM1         (rw) : ORIGIN = 0x30000000, LENGTH = 128K
    SRAM2         (rw) : ORIGIN = 0x30020000, LENGTH = 128K
    SRAM3         (rw) : ORIGIN = 0x30040000, LENGTH = 32K
    /* gap */
    SRAM4         (rw) : ORIGIN = 0x38000000, LENGTH = 64K
    /* gap */
    BKUP          (rw) : ORIGIN = 0x38800000, LENGTH = BKPRSRAM_SIZE
    /* gap */
    /* +============================================================+ */
    APB1          (rw) : ORIGIN = 0x40000000, LENGTH = 0x0000D400
    APB2          (rw) : ORIGIN = 0x40010000, LENGTH = 0x00007800
    AHB1          (rw) : ORIGIN = 0x40020000, LENGTH = 0x00020000
    USB_OTG_HS    (rw) : ORIGIN = 0x40040000, LENGTH = 0x00040000
    USB_OTG_FS    (rw) : ORIGIN = 0x40080000, LENGTH = 0x00040000
    AHB2          (rw) : ORIGIN = 0x48020000, LENGTH = 0x00003400
    APB3          (rw) : ORIGIN = 0x50000000, LENGTH = 0x00004000
    AHB3          (rw) : ORIGIN = 0x51000000, LENGTH = 0x01009400
    APB4          (rw) : ORIGIN = 0x58000000, LENGTH = 0x00006C00
    AHB4          (rw) : ORIGIN = 0x58020000, LENGTH = 0x00007400
    /* +============================================================+ */
    FMC1          (rw) : ORIGIN = 0x60000000, LENGTH = 0x04000000
    FMC2          (rw) : ORIGIN = 0x64000000, LENGTH = 0x04000000
    FMC3          (rw) : ORIGIN = 0x68000000, LENGTH = 0x04000000
    FMC4          (rw) : ORIGIN = 0x6C000000, LENGTH = 0x04000000
    NAND          (rw) : ORIGIN = 0x80000000, LENGTH = 0x10000000
    QSPI          (rw) : ORIGIN = 0x90000000, LENGTH = 0x10000000
    SDRAM1        (rw) : ORIGIN = 0xC0000000, LENGTH = 0x0C000000
    SDRAM2        (rw) : ORIGIN = 0xD0000000, LENGTH = 0x10000000
    /* +============================================================+ */
    PPB           (rw) : ORIGIN = 0xE0000000, LENGTH = 1M
    VENDOR        (rw) : ORIGIN = 0xE0100000, LENGTH = 0x1FF00000
}

REGION_ALIAS("REGION_TEXT",    FLASH);
REGION_ALIAS("REGION_RODATA",  FLASH);
REGION_ALIAS("REGION_DATA",    AXISRAM);
REGION_ALIAS("REGION_BSS",     AXISRAM);
REGION_ALIAS("REGION_STACK",   DTCM);
REGION_ALIAS("REGION_SYSTEM",  PPB);
REGION_ALIAS("REGION_HEAP",    SRAM4);

/* Computed SRAM size, but it's discontiguous so we can't use it as the actual SRAM region */
SRAM_SIZE = LENGTH(AXISRAM) + LENGTH(SRAM1) + LENGTH(SRAM2) + LENGTH(SRAM3) + LENGTH(SRAM4);

__cortex_flash_start = ORIGIN(FLASH);
__cortex_flash_limit = ORIGIN(FLASH) + LENGTH(FLASH);
__cortex_flash_size = LENGTH(FLASH);
__cortex_flash_pow2  = LOG2CEIL(__cortex_flash_size);

__cortex_stack_start = ORIGIN(DTCM);
__cortex_stack_limit = ORIGIN(DTCM) + LENGTH(DTCM);
__cortex_stack_size = LENGTH(DTCM);
__cortex_stack_pow2  = LOG2CEIL(__cortex_stack_size);

/* SRAM is not contiguous, so we just call the AXI SRAM as the SRAM */
__cortex_sram_start = ORIGIN(AXISRAM);
__cortex_sram_limit = ORIGIN(AXISRAM) + LENGTH(AXISRAM);
__cortex_sram_size = LENGTH(AXISRAM);
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

__sram1_start = ORIGIN(SRAM1);
__sram1_limit = ORIGIN(SRAM1) + LENGTH(SRAM1);

__sram2_start = ORIGIN(SRAM2);
__sram2_limit = ORIGIN(SRAM2) + LENGTH(SRAM2);

__sram3_start = ORIGIN(SRAM3);
__sram3_limit = ORIGIN(SRAM3) + LENGTH(SRAM3);

__sram4_start = ORIGIN(SRAM4);
__sram4_limit = ORIGIN(SRAM4) + LENGTH(SRAM4);