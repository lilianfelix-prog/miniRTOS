

.section .data

heap_pos:
    .quad __end       //initialise the start of the heap in 64bit space

.section .text.entry
.global _sbrk         //make the function accessible
.global _sbrk_start   // 

_sbrk:

    LOAD t0, heap_pos   //load current addr of heap in t0

    add t1, t0, a0    //the function argument is set in a0 reg
                      //heap addr + size arg set in t1
    
    mv t0, t1

    STOR a0, (t1)     //a0 is also the return reg
                      //

    ret

