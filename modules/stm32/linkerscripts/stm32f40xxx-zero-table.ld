/* Does not need to be in order and will do some repetitive work if overlapping. Second value is EXCLUSIVE */
.zero_table ALIGN(8) : {
    __zero_table_start = . ;
    LONG(__ccm_start)
    LONG(__ccm_limit)
    LONG(__sram_start)
    LONG(__sram_limit)
    __zero_table_limit = . ;
} >FLASH

/* Intervals MUST BE IN ORDER AND NON-OVERLAPPING! */
.intervals ALIGN(8) : {
    __intervals_count = . ;
    LONG((__intervals_limit - __intervals_start) / 8) /* size of interval */
    __intervals_start = . ;
    /* Data in the table is a pair of two INCLUSIVE addresses */
    LONG(ORIGIN(FLASH))
    LONG(ORIGIN(FLASH) + LENGTH(FLASH) - 1)
    LONG(ORIGIN(CCM))
    LONG(ORIGIN(CCM) + LENGTH(CCM) - 1)
    LONG(ORIGIN(SRAM))
    LONG(ORIGIN(SRAM) + LENGTH(SRAM) - 1)
    LONG(ORIGIN(APB1))
    LONG(ORIGIN(APB1) + LENGTH(APB1) - 1)
    LONG(ORIGIN(APB2))
    LONG(ORIGIN(APB2) + LENGTH(APB2) - 1)
    LONG(ORIGIN(AHB1))
    LONG(ORIGIN(AHB1) + LENGTH(AHB1) - 1)
    /* TODO we don't use USB so drop it  */
    LONG(ORIGIN(AHB2))
    LONG(ORIGIN(AHB2) + LENGTH(AHB2) - 1)
    LONG(ORIGIN(AHB3))
    LONG(ORIGIN(AHB3) + LENGTH(AHB3) - 1)
    LONG(ORIGIN(PPB))
    LONG(ORIGIN(PPB) + LENGTH(PPB) - 1)
    __intervals_limit = . ;
} >FLASH

PROVIDE(_ZN6cortex2m421sorted_memory_regionsE = __intervals_start);
PROVIDE(_ZN6cortex2m419sorted_region_countE = __intervals_count);
