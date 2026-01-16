IROM_ADDR = 0x42000020;
DROM_ADDR = 0x3C000020;
DRAM_ADDR = 0x3FC7C000;
IRAM_ADDR = 0x4037C000;
FLASH_LENGTH = 0x800000-0x20;



MEMORY
{
    irom (RX) : ORIGIN = IROM_ADDR, LENGTH = FLASH_LENGTH
    drom (R)  : ORIGIN = DROM_ADDR, LENGTH = FLASH_LENGTH
    iram (RX) : ORIGIN = IRAM_ADDR, LENGTH = 128K
    dram (RW) : ORIGIN = DRAM_ADDR, LENGTH = 128K
}

ENTRY(_start)

SECTIONS
{
    .text : {

        _text_start = ABSOLUTE(.);

        *(.text*)
        *(.rodata*)

        _text_end = ABSOLUTE(.);
        
    } > irom

    .data : {

        __data_start = ABSOLUTE(.);

        *(.data*)

        __data_end = ABSOLUTE(.);
        . = ALIGN(4);

    } > dram AT > irom

    __sidata = LOADADDR(.data);

    .bss : {

        . = ALIGN (8);
        _bss_start = ABSOLUTE(.);

        *(.bss*)
        *(COMMON)

        . = ALIGN (8);
        _bss_end = ABSOLUTE(.);

    } > dram
}

/* Stack at top of DRAM */
_stack_top = ORIGIN(dram) + LENGTH(dram);
