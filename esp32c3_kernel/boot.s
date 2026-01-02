.global _start
.section .text

#set the stack pointer from the linker script in the sp register
#jump in the main of the C code  
_start: la sp, _STACK_PTR
        call main
        j .

