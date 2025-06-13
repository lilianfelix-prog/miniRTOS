
//better to use the c version
.section .data

heap_pos:
    .word __end       //initialise the start of the heap in 32bit space

.section .text.entry
.global _sbrk         //make the function accessible
.global _sbrk_start   // 

_sbrk:

    la t0, heap_pos   //load current addr of heap in t0

    add t1, 0(t0), 0(a0)    //the function argument is set in a0 reg
                            //heap addr + size arg set in t1
    
    sw 0(t0), t1

    sw a0, 0(t0)      //a0 is also the return reg
                      //return the previous heap_pos which is the start of the mem block

    ret

    ebreak
