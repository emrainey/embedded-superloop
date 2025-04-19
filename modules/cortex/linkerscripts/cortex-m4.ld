/**
 * The GNU Linker Script for a Cortex M4 microcontroller.
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

/* Some of these values have to be set in the Chip specific linker script */

MEMORY {
    /* The architecture reference manual breaks the default Cortex M space down like this: */
    /*
    CODE          (rx) : ORIGIN = 0x00000000, LENGTH = 0x1FFFFFFF
    SRAM1         (rw) : ORIGIN = 0x20000000, LENGTH = 0x1FFFFFFF
    PERIPH        (rw) : ORIGIN = 0x40000000, LENGTH = 0x1FFFFFFF
    RAM2          (rw) : ORIGIN = 0x60000000, LENGTH = 0x1FFFFFFF
    RAM2          (rw) : ORIGIN = 0x80000000, LENGTH = 0x1FFFFFFF
    DEVICE1       (rw) : ORIGIN = 0xA0000000, LENGTH = 0x1FFFFFFF
    DEVICE2       (rw) : ORIGIN = 0xC0000000, LENGTH = 0x1FFFFFFF
    SYSTEM        (rw) : ORIGIN = 0xE0000000, LENGTH = 0x1FFFFFFF
    */

    FLASH         (rx) : ORIGIN = 0x08000000, LENGTH = FLASH_SIZE
    CCM           (rw) : ORIGIN = 0x10000000, LENGTH = CCM_SIZE
    SRAM          (rw) : ORIGIN = 0x20000000, LENGTH = SRAM_SIZE
    APB1          (rw) : ORIGIN = 0x40000000, LENGTH = 0x00010000
    APB2          (rw) : ORIGIN = 0x40010000, LENGTH = 0x00010000
    AHB1          (rw) : ORIGIN = 0x40020000, LENGTH = 0x0000BC00
    USB_OTG_HS    (rw) : ORIGIN = 0x40040000, LENGTH = 0x00040000
    USB_OTG_FS    (rw) : ORIGIN = 0x50000000, LENGTH = 0x00040000
    AHB2          (rw) : ORIGIN = 0x50050000, LENGTH = 0x00060C00
    AHB3          (rw) : ORIGIN = 0x60000000, LENGTH = 0x40001000
    PPB           (rw) : ORIGIN = 0xE0000000, LENGTH = 1M
    VENDOR        (rw) : ORIGIN = 0xE0100000, LENGTH = 0x1FF00000
}

REGION_ALIAS("REGION_TEXT",    FLASH);
REGION_ALIAS("REGION_RODATA",  FLASH);
REGION_ALIAS("REGION_DATA",    SRAM);
REGION_ALIAS("REGION_BSS",     SRAM);
REGION_ALIAS("REGION_STACK",   CCM);
REGION_ALIAS("REGION_SYSTEM",  PPB);
REGION_ALIAS("REGION_HEAP",    SRAM);
/* DMA CAN NOT BE LOCATED IN ITCM, DTCM or CCM! */
