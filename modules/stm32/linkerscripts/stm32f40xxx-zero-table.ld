
.zero_table ALIGN(8) : {
    __zero_table_start = . ;
    LONG(__ccm_beg)
    LONG(__ccm_end)
    LONG(__sram_beg)
    LONG(__sram_end)
    __zero_table_limit = . ;
} >FLASH
