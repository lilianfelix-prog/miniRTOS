

//task state (Ready, Blocked, Suspended )
#define F_RDY 0x01
#define F_BCK 0x02
#define f_SSD 0x03

#define MAX_TASK 32

typedef struct uint8_t stack_t;

typedef struct uint8_t state_t;

typedef struct uint8_t priority_t;

typedef struct
{
    //variable shared between Interupt are volatile, can change unexpectedly
    volatile stack_t* ptStackTop; // startStack + size
    state_t* taskState;
    priority_t* taskPriority;
    stack_t* startStack;

} taskTCB_t;