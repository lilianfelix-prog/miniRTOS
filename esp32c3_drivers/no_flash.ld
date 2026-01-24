DRAM_ADDR = 0x3FC7C000;
IRAM_ADDR = 0x4037C000;


MEMORY
{
    iram (RX) : ORIGIN = IRAM_ADDR, LENGTH = 128K
    dram (RW) : ORIGIN = DRAM_ADDR, LENGTH = 128K
}

ENTRY(_start)

SECTIONS
{

    .text ORIGIN(iram): {
        *(.entry*)
        *(.text*)
        *(.rodata .rodata* .srodata)
        
    } > iram
    
    __data_start = ABSOLUTE(.);
    
    .data ORIGIN(dram) : AT(__data_start) {

        *(.data*)
	
    } > dram

    __data_end = __data_start + SIZEOF(.data);
    . = ALIGN(4);

   
    _bss_start = ABSOLUTE(.);

    .bss : {

        *(.bss*)
        *(COMMON)

    } > dram

    _bss_end = ABSOLUTE(.);

}

_stack_top = ORIGIN(dram) + LENGTH(dram);
