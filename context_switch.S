/* assuming that the chip specific extensions has portasmHAS_MTIME and on 64 bit machine*/
/* RISCV specifiction includes a standar machine-level timer: mtime 64 bits constantly increasing */
/* counter register, mtimecmp holds a compare value. A timer interupt is generated when */
/* mtime >= mtimecmp.  */
#define portWORD_SIZE    8 //word size on 64-bits
.extern pullMachineTimerCompareRegister
.extern pullNextTime

// sets the timer for the next interrupt
.macro UPDATE_MTIMER_REGISTER
    ld a0, pullMachineTimerCompareRegister //get the addr of the compare register from machine
    ld a1, pullNextTime //get addr of time incrementation from ram 

    ld t2, 0(a1) // load the current tick time in t2
    sd t2, 0(a0) // store that new time value in the compare register
    ld t0, uxTimerIncrementsForOneTick // num of clock cycle per os tick
    add t4, t0, t2 // add the clock increment to current tick time
    sd t4, 0(a1) // store the new value for next tick in pullNextTime

.endm

initialiseStack:
    addi a0, a0, -(22 * portWORD_SIZE) // register x10 - x31, add byte size needed to a0
    sw a2, 0(a0) // task parameters
    addi a0, a0, -(6 * portWORD_SIZE) // register x5 - x9 + ret addr
    lw t0, x1 // return addr at register x1
    sw t0, 0(a0) // return addr on stack

// chip specific registers and mstatus for fpu/vpu

    addi a0, a0, -portWORD_SIZE 
    sw a1, 0(a0) // mret value (pxCode parameter) onto the stack
    ret

    
startFirstTask:
    lw sp, currentTCB // load current task block into stack pointer
    lw sp, 0(sp) // load the sp in the first element of the TCB struct (startStack + size)
    lw x1, 0(sp) // replace the sp in TCB struct with task ret addr

    
