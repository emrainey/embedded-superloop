/**
 * The GNU Linker Script for this system
 * @see https://ftp.gnu.org/old-gnu/Manuals/ld-2.9.1/html_mono/ld.html
 */

INCLUDE board.ld

ENTRY(reset_entry)

/* +===================================================================+ */
/* This linker script does not support Heaps, C++ Exceptions or C++ RTTI */
/* +===================================================================+ */
SECTIONS {
    /* Vector Table(s) */
    .tables : {
        __vector_table_start = .;
        KEEP(*(.vectors))
        KEEP(*(.extended_vectors))
        __vector_table_end = .;
    } >REGION_TEXT

    /* Program Code (aligned at next 1KB) */
    .text ALIGN(1024) : {
        *(.text)
        *(.text.*)
    } >REGION_TEXT

    /* meant to run before shared object dependencies... (we don't have those) */
    .preinit_array ALIGN(4) : {
        PROVIDE_HIDDEN(__preinit_array_start = .);
        KEEP(*(.preinit_array))
        PROVIDE_HIDDEN(__preinit_array_end = .);
    } >REGION_TEXT

    .init_array ALIGN(4) : {
        KEEP(*(.init)) /* process initialization (we don't need) */
        *(SORT(.ctors.*))
        *(.ctors)
        PROVIDE_HIDDEN(__init_array_start = .);
        KEEP(*(SORT(.init_array.*)))
        KEEP(*(.init_array))
        PROVIDE_HIDDEN(__init_array_end = .);
    } >REGION_TEXT

    .fini_array ALIGN(4) : {
        KEEP(*(.fini)) /* process teardown (we don't need) */
        PROVIDE_HIDDEN (__fini_array_start = .);
        KEEP(*(SORT(.fini_array.*)))
        KEEP(*(.fini_array*))
        PROVIDE_HIDDEN (__fini_array_end = .);
        *(SORT(.dtors.*))
        *(.dtors)
        . = ALIGN(4);
    } >REGION_TEXT

    /* Initialized Constant Static Storage */
    .rodata ALIGN(4) : {
        __data_load = .;
        *(.rodata)
        *(.rodata.*)
    } >REGION_TEXT

    /* Initialized Static Storage */
    .data : {
        __data_start = .;
        *(.data)
        *(.data.*)
        . = ALIGN(4);
        __data_end = .;
    } >REGION_DATA

    /* The privileged memory section contains data which only Privileged mode should access.
     * It needs to be aligned to a larger power of 2, like 1K to support making an MPU region
     */
    .privileged_data ALIGN(1024) : {
        __privileged_data_start = .;
        *(.privileged_data)
        . = ALIGN(1024);
        __privileged_data_end = .;
    } >REGION_DATA
    __privileged_data_size = SIZEOF(.privileged_data);
    __privileged_data_size_pow2 = LOG2CEIL(__privileged_data_size);

    /* Uninitialized Static Storage */
    .bss (NOLOAD) : {
        __bss_start = ALIGN(4);
        *(.bss)
        *(.bss.*)
        . = ALIGN(4);
        __bss_end = .;
    } >REGION_BSS

    /* DMA Buffers (uncached memory) */
    .dma_buffers ALIGN(1024) (NOLOAD) : {
        __dma_buffers_start = .;
        *(.dma_buffers)
        . = ALIGN(8);
        __dma_buffers_end = .;
    } > REGION_DATA
    __dma_buffers_size = SIZEOF(.dma_buffers);
    __dma_buffers_size_pow2 = LOG2CEIL(__dma_buffers_size);

    /* Process Stack */
    .process_stack (NOLOAD) : {
        __process_stack_bottom = .;
        . = . + STACK_SIZE - 8;
        __process_stack_ceiling = .;
        . = . + 8;
        __process_stack_top = .;
    } >REGION_STACK
    __process_stack_size = SIZEOF(.process_stack);
    __process_stack_size_pow2 = LOG2CEIL(__process_stack_size);

    /* Main Stack Guard */
    .main_stack (NOLOAD) : {
        __main_stack_bottom = .;
        . = . + STACK_SIZE - 64;
        __main_stack_ceiling = .;
        . = . + 64;
        __main_stack_top = .;
    } >REGION_STACK
    __main_stack_size = SIZEOF(.main_stack);
    __main_stack_size_pow2 = LOG2CEIL(__main_stack_size);

    /* Pull in the sections from the board which will pull in the sections from the chip */
    INCLUDE board-sections.ld
}
