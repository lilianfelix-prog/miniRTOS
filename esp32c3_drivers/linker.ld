IROM_ADDR = 0x42000020;
DROM_ADDR = 0x3C000020;
DRAM_ADDR = 0x3FC7C000;
IRAM_ADDR = 0x4037C000;
FLASH_LENGTH = 0x800000-0x20;



MEMORY
{
    irom (RX) : ORIGIN = IROM_ADDR, LENGTH = FLASH_LENGTH
    drom (RX)  : ORIGIN = DROM_ADDR, LENGTH = FLASH_LENGTH
    iram (RX) : ORIGIN = IRAM_ADDR, LENGTH = 128K
    dram (RW) : ORIGIN = DRAM_ADDR, LENGTH = 128K
}

ENTRY(_start)

SECTIONS
{

    .text ORIGIN(drom): {
        *(.entry*)
        *(.text*)
        *(.rodata .rodata* .srodata)
        
    } > drom
    
    __data_start = ABSOLUTE(.);
    
    .data ORIGIN(dram) : AT(__data_start) {

        *(.data*)
	
    } > dram

    __data_end = __data_start + SIZEOF(.data);
    . = ALIGN(4);

    __sidata = LOADADDR(.data);

   
    _bss_start = ABSOLUTE(.);

    .bss : {

        *(.bss*)
        *(COMMON)

    } > dram

    _bss_end = ABSOLUTE(.);

}

_stack_top = ORIGIN(dram) + LENGTH(dram);
