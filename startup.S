//here we want to set up the initial stack pointer and jump to main()

.extern main
.section .text.startup
.global _start /* prevent instructions following _start to be disassembled by objdump */

_start:
    
    la gp, __global_pointer$

    // primary hart (main hardware thread)
    //  CSR instruction read-modify-write control and status registers
    csrr a0, mhartid    //write hart id to a0 function arg register
    li   a1, 0          //load hart index
    bne  a0, a1, L_sec      //branch if not equal 

    la sp, _stack_top   //load top of stack addr from linker.ld in sp register

    //loading .data section
    la   a0, __sidata     //load data addr from rom to a0 register
    la   a1, __data_start //load data start addr to a1 register
    la   a2, __data_end   //load data end addr to a2 register

L_copy_loop:
    bgtu a1, a2, L_bss_init //when ram start addr == end addr branch
    LOAD t0, (a0)
    STOR t0, (a1)
                       //increments addr rom and ram 
    addi a0, a0, 4     //registers are 4 bytes
    addi a1, a1, 4
    j L_copy_loop


L_bss_init:
    la a0, __bss_start   //load bss start addr in a0
    la a1, __bss_end     //load bss end addr in a1

    bgtu a0, a2, L_next
    STOR zero, (a0)
    addi a0, a0, 4

L_next:


