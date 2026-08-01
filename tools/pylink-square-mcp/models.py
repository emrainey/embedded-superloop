
# Contains the MCU named "models" and their associated RTT memory ranges.
# This is used by the pylink-square-mcp to determine if a model is supported
# and to provide the correct RTT memory ranges for that model.
models = {
    "STM32H753ZI": {
        "flash": [
            # Flash (2MB)
            [0x08000000, 0x08200000],
        ],
        "ram": [
            # ITCM (64KB)
            [0x00000000, 0x00010000],
            # DTCM (128KB)
            [0x20000000, 0x20020000],
            # AXI SRAM (512KB)
            [0x24000000, 0x24080000],
            # SRAM1 (128KB)
            [0x30000000, 0x30020000],
            # SRAM2 (128KB)
            [0x30020000, 0x30040000],
            # SRAM3 (32KB)
            [0x30040000, 0x30048000],
            # SRAM4 (64KB)
            [0x38000000, 0x38010000],
            # BKUP SRAM (4KB)
            [0x38800000, 0x38801000],
        ]
    },
    "STM32F407VE": {
        "flash": [
            # Flash (512KB)
            [0x08000000, 0x08080000],
        ],
        "ram": [
            # CCM (64KB)
            [0x10000000, 0x10010000],
            # SRAM (128KB)
            [0x20000000, 0x20020000],
            # BKUP SRAM (4KB)
            [0x40024000, 0x40025000],
        ]
    },
    "STM32F407VG": {
        "flash": [
            # Flash (1MB)
            [0x08000000, 0x08100000],
        ],
        "ram": [
            # CCM (64KB)
            [0x10000000, 0x10010000],
            # SRAM (128KB)
            [0x20000000, 0x20020000],
            # BKUP SRAM (4KB)
            [0x40024000, 0x40025000],
        ]
    }
}