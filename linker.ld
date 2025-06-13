/* define the memory layout */

/* entry point to the linker */
ENTRY(_start)

MEMORY
{
    /* memory area */
    rom (rxa) : ORIGIN = 0x80000000, LENGTH = 512K
    ram (wxa) : ORIGIN  = 0x80080000, LENGH = 1024K
}
SECTIONS
{

    /* initialize stack and stack top needed for startup */
    /* start at top of ram and grows downwords */
    /* by putting the stack first instead of possible collision with heap a memory fault is triggered */

    
    
    /* initialize current addr ( . represent current addr) */
    __start = .;
    __text_start = .;
    /* memory space for executalble */
    .text :
    {
        /* this is where the startup.S will be stored */
        KEEP(*(.text.startup))

        /* all other objects */
        *(.text.entry .text.entry.*)
        *(.text .text.*)

    } >rom AT>rom     /* execute from addr in rom and store in addr in rom */

    /* page alignement, rouding to the nearest biggest addr divisible by 4
    . = ALIGN(4); 
    __text_end = .;

    /* read only data, global contants */

    __rodata_start = .;
    .rodata :
    {
        *(.rodata)
        *(.rodata .rodata.*)
    } >rom AT>rom 

    . = ALIGN(4);
    __rodata_end = .;

    /* compile time global variable */
    __data_start = .;
    .data :
    {
        *(.data .data.*)
        . = ALIGN(8);
        PROVIDE( __global_pointer$ = . + 0x800 );
        . = ALIGN(4);
    } >ram AT>rom     /* variable in ram at runtime, stored initial value in rom */ 
    /* tells the loader to use the ROM addrs for loading but links RAM addrs for the code */ 
    __data_end;
    __sidata = LOADADDR(.data);  /* load rom addr needed for copy */

    /* uninitialized global variable */
    __bss_start = .;
    .bss :
    {
        *(.bss)
    } >ram    /* no loadable content so no LMA */
    .= ALIGN(8);
    __end = .;

    /* end of static data, start of heap memory */
    .stack :
    {
        . = ALIGN(8);
        . += 0x1000; /* about 4K stack size */
        _stack_top = .;
    } >ram
}