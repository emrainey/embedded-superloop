
PROGRAM_FLASH_ADDRESS = 0x00000000;
PROGRAM_FLASH_SIZE = 0x4000; /* 256k */

SRAM_ADDRESS = 0x20000000;
SRAM_SIZE = 0x080000; /*  32k */

MEMORY {
    PROGRAM_FLASH (rx) : ORIGIN = PROGRAM_FLASH_ADDRESS, LENGTH = PROGRAM_FLASH_SIZE
    RAM (rwx)  : ORIGIN = SRAM_ADDRESS, LENGTH = SRAM_SIZE
}

ENTRY(reset_handler) /* must be extern "C" or in mangled format */

/* +===================================================================+ */
/* This linker script does not support Heaps, C++ Exceptions or C++ RTTI */
/* +===================================================================+ */
SECTIONS
{
    /* Program Code */
    .text :
    {
        KEEP(*(.vectors))
        *(.text)
        *(.text.*)
        KEEP(*(.init))
        KEEP(*(.fini))
        *(SORT(.ctors.*))
		*(.ctors)
        *(SORT(.dtors.*))
 		*(.dtors)
        . = ALIGN(4);
    } > PROGRAM_FLASH

    /* Intialized Constant Static Storage */
    .rodata :
    {
        *(.rodata)
        *(.rodata.*)
    } > PROGRAM_FLASH

    /* Intialized Static Storage */
    .data ALIGN(8) :
    {
        *(.data)
        *(.data.*)
    } > RAM

    /* Unintialized Static Storage */
    .bss ALIGN(8) :
    {
        __bss_start = .;
        *(.bss)
        *(.bss.*)
        . = ALIGN(8);
        __bss_end = .;
    } > RAM

    .stack ALIGN(4) : {
        __stack_btm = .;
        KEEP(*(.stack))
        __stack_top = .;
    } > RAM
}
