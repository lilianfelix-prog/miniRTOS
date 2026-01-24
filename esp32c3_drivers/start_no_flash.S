/* In order to debug with openOCD via JTAG without having to manually initialize cache + MMU,
 * remove rom init and copy loop, OpenOCD writes directly to iram/dram memory -> jumps directly to PC
*/
	
.extern main
.global _start /* prevent instructions following _start to be disassembled by objdump */

_start:

    la sp, _stack_top  /* load top of stack addr from linker.ld in sp register */

    /* 2. Disable watchdogs */
    li t0, 0x6001F048
    sw zero, 0(t0)
    li t0, 0x60020048
    sw zero, 0(t0)

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
