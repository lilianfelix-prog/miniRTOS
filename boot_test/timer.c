
// ref: https://github.com/riscv-non-isa/riscv-sbi-doc/blob/master/src/binary-encoding.adoc

#define HANDLER_MSG "Hello, handling the interrupt!\n"
#define TEST_MSG "Kernel launch successful!\n"
#define MAIN_THREAD_MSG "Back to the main thread..."
//return values of all SBI operation
struct SBI_ret{
    long error;
    union {
        long value;
        unsigned long uvalue;
    };
};

struct SBI_ret debug_out(char *msg, int len){
    struct SBI_ret return_status;
    // setting the register to print to UART 
    asm(
            "li a7, 0x4442434E\n\t"
            "li a6, 0x00\n\t"
            "li a2, 0\n\t"
            "mv a1, %3\n\t"
            "mv a0, %4\n\t"
            "ecall\n\t"
            "mv %0, a0\n\t" //returned error code from syscall into return_status.error
            "mv %1, a1\n\t" //returned value from syscall into return_status.value
            "mv %2, a2\n" //returned bytes written from syscall into return_status.uvalue
            : /* Outputs: */ "=r"(return_status.error), "=r"(return_status.value), "=r"(return_status.uvalue) // %0, %1, %2
            : /* Inputs: */ "r"(msg), "r"(len) // %3, %4
            : /* Clobbered registers: */ "a0", "a1", "a2", "a6", "a7"
        );
    return return_status;
}

// enable s mode interupts
void set_s_mode_interupt(void *handler){
    asm(
            "csrw stvec, %0\n\t"
            "csrsi sstatus, 2"
            :
            : "r"(handler)
       );
}

struct SBI_ret set_interupt_timer(){
    struct SBI_ret return_status;

    asm(
            "rdtime t0\n\t" // retreive CSR timer val
            "li t1, 0x10000000\n\t" // interrupt interval
            "li a7, 0x54494D45\n\t"
            "li a6, 0x00\n\t"
            "ecall\n\t"
            "mv %0, a0\n\t"
            "mv %1, a1\n"
            : /* Outputs: */ "=r"(return_status.error), "=r"(return_status.value)
            : /* Inputs: none */
            : /* Clobbered registers: */ "a0", "a1", "a6", "a7", "t0", "t1"
       );
    return return_status;
}

void enable_s_mode_timer(){
    asm(
      "li t1, 32\n\t"
      "csrs sie, t1\n" // Timer interrupt enable flag: STIE
      ::: /* Clobbered registers: */ "t1"
      );
}

//after entering the interrupt handling, clear the coressponding pending bit
//TODO: handle different interrupts
void clear_pending_bit(){
    asm(
        "li t0, 32\n\t"
        "csrs sip, t0\n" //the entire register from 1 to 0 
        ::: "t0"
    );
} 

//Before the interrupt logic, GCC saves all the registers and then load them back up after. (doing the context switch for us)  
__attribute__((interrupt ("supervisor")))
__attribute__((section (".text.interrupt")))
void s_mode_interrupt_handler(void){
    // would need to inspect the cause of interrupts here
    clear_pending_bit();
    
    // set a new interrupt for later
    set_interupt_timer();

    debug_out(HANDLER_MSG, sizeof(HANDLER_MSG));
}

void main(){
    struct SBI_ret test_msg = debug_out(TEST_MSG, sizeof(TEST_MSG));

    if(test_msg.error < 0){
        return;
    }

    set_s_mode_interupt(&s_mode_interrupt_handler);
    set_interupt_timer();
    enable_s_mode_timer();

    while (1) {
        debug_out(MAIN_THREAD_MSG, sizeof(MAIN_THREAD_MSG));
        for (int i = 0; i < 300000000; i++); // Simulate a delay
    }
    
}



