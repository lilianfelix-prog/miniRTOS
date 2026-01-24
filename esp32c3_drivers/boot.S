.extern main
.global _start /* prevent instructions following _start to be disassembled by objdump */

_start:

    la sp, _stack_top  /* load top of stack addr from linker.ld in sp register */

    /* 2. Disable watchdogs */
    li t0, 0x6001F048
    sw zero, 0(t0)
    li t0, 0x60020048
    sw zero, 0(t0)

    /* loading .data section */
    la   t0, __sidata     /* load data addr from rom to t0 register */
    la   t1, __data_start /* load data start addr to t1 register */
    la   t2, __data_end   /* load data end addr to t2 register */

L_copy_loop:
    bgeu t1, t2, L_bss_init /* when ram start addr >= end addr branch */
    lw t3, 0(t1)           /* dereferenced load t1 reg (val at _start addr)  to t3 reg */
                
                            /* increments addr rom and ram */ 
    addi t1, t1, 4          /* registers are 4 bytes */
    addi t0, t0, 4
    sw t3, -4(t0)
    j L_copy_loop


L_bss_init:
    la t0, _bss_start   /* load bss start addr in t0 */
    la t1, _bss_end     /* load bss end addr in t1 */

L_clear_bss:	
    bgeu t0, t1, L_end  /* when start addr >= end addr branch */
    sw zero, 0(t0)      /* dereferenced store 0 at t0 addr */
    addi t0, t0, 4       /* increment 4 bytes */
    j L_clear_bss
	
L_end:
    /* reset reg to zero */
    li t0, 0
    li t1, 0
    li t2, 0
    li t3, 0
	
    jal main
    ebreak
