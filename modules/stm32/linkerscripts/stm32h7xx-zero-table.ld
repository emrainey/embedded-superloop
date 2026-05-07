/* Does not need to be in order and will do some repetitive work if overlapping. Second value is EXCLUSIVE */
.zero_table ALIGN(8) : {
    __zero_table_start = . ;
    LONG(ORIGIN(ITCM))
    LONG(ORIGIN(ITCM) + LENGTH(ITCM))
    LONG(ORIGIN(DTCM))
    LONG(ORIGIN(DTCM) + LENGTH(DTCM))
    LONG(ORIGIN(AXISRAM))
    LONG(ORIGIN(AXISRAM) + LENGTH(AXISRAM))
    LONG(ORIGIN(SRAM1))
    LONG(ORIGIN(SRAM1) + LENGTH(SRAM1))
    LONG(ORIGIN(SRAM2))
    LONG(ORIGIN(SRAM2) + LENGTH(SRAM2))
    LONG(ORIGIN(SRAM3))
    LONG(ORIGIN(SRAM3) + LENGTH(SRAM3))
    LONG(ORIGIN(SRAM4))
    LONG(ORIGIN(SRAM4) + LENGTH(SRAM4))
    __zero_table_limit = . ;
} >FLASH


/* Intervals MUST BE IN ORDER AND NON-OVERLAPPING! */
.intervals ALIGN(8) : {
    __intervals_count = . ;
    LONG((__intervals_limit - __intervals_start) / 8) /* size of interval */
    __intervals_start = . ;
    /* Data in the table is a pair of two INCLUSIVE addresses */
    LONG(ORIGIN(ITCM))
    LONG(ORIGIN(ITCM) + LENGTH(ITCM) - 1)
    LONG(ORIGIN(FLASH))
    LONG(ORIGIN(FLASH) + LENGTH(FLASH) - 1)
    LONG(ORIGIN(DTCM))
    LONG(ORIGIN(DTCM) + LENGTH(DTCM) - 1)
    LONG(ORIGIN(AXISRAM))
    LONG(ORIGIN(AXISRAM) + LENGTH(AXISRAM) - 1)
    LONG(ORIGIN(SRAM1))
    LONG(ORIGIN(SRAM1) + LENGTH(SRAM1) - 1)
    LONG(ORIGIN(SRAM2))
    LONG(ORIGIN(SRAM2) + LENGTH(SRAM2) - 1)
    LONG(ORIGIN(SRAM3))
    LONG(ORIGIN(SRAM3) + LENGTH(SRAM3) - 1)
    LONG(ORIGIN(SRAM4))
    LONG(ORIGIN(SRAM4) + LENGTH(SRAM4) - 1)
    LONG(ORIGIN(BKUP))
    LONG(ORIGIN(BKUP) + LENGTH(BKUP) - 1)
    LONG(ORIGIN(APB1))
    LONG(ORIGIN(APB1) + LENGTH(APB1) - 1)
    LONG(ORIGIN(APB2))
    LONG(ORIGIN(APB2) + LENGTH(APB2) - 1)
    LONG(ORIGIN(AHB1))
    LONG(ORIGIN(AHB1) + LENGTH(AHB1) - 1)
    LONG(ORIGIN(AHB2))
    LONG(ORIGIN(AHB2) + LENGTH(AHB2) - 1)
    LONG(ORIGIN(APB3))
    LONG(ORIGIN(APB3) + LENGTH(APB3) - 1)
    LONG(ORIGIN(AHB3))
    LONG(ORIGIN(AHB3) + LENGTH(AHB3) - 1)
    LONG(ORIGIN(APB4))
    LONG(ORIGIN(APB4) + LENGTH(APB4) - 1)
    LONG(ORIGIN(AHB4))
    LONG(ORIGIN(AHB4) + LENGTH(AHB4) - 1)
    LONG(ORIGIN(PPB))
    LONG(ORIGIN(PPB) + LENGTH(PPB) - 1)
    __intervals_limit = . ;
} >FLASH

PROVIDE(_ZN6cortex21sorted_memory_regionsE = __intervals_start);
PROVIDE(_ZN6cortex19sorted_region_countE = __intervals_count);
