# openSBI spec: https://github.com/riscv-non-isa/riscv-sbi-doc/blob/master/src/ext-debug-console.adoc

.global _start
.section .text.kernel

_start: li a7, 0x4442434E # load the openSBI extension ID in the specified a7 register for EID
li a6, 0x00 # load openSBI func ID for write (0) in FID register 
li a0, 13 # func argument: num of bytes 
lla a1, hello_string # func argument: base addr low (first half of the 64-bit addr)
li a2, 0 # func argument: base addr high (second half of the 64-bit addr)
ecall # pc jumps to openSBI

loop: j loop

.section .rodata

hello_string:
.string "Hello openSBI\n" 
