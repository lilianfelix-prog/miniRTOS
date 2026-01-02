.global _start
.section .text.bios

_start: addi a0, x0, 0x68 # (func arg) = 0 + "h"
	li a1, 0x10000000 # load uart address for qemu virt machine in a1 reg
    sb a0, (a1) # mem[a1][0:7] = "h" 

    addi a0, x0, 0x65
    sb a0, (a1)

    addi a0, x0, 0x6C
    sb a0, (a1)

    addi a0, x0, 0x6C
    sb a0, (a1)

    addi a0, x0, 0x6F
    sb a0, (a1)

    loop: j loop # infinite loop (loop func calls itself) 


