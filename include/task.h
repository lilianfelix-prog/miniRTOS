

//task state (Ready, Blocked, Suspended )
#define F_RDY 0x01
#define F_BCK 0x02
#define f_SSD 0x03

#define MAX_TASK 16

#define STACK_DEPTH 4096

typedef struct{
    void (* function)(void *arg);
} taskFunction_t;

typedef struct
{
    //variable shared between Interupt are volatile, can change unexpectedly
    volatile uint8_t* ptBlockTop; // startStack + size
    uint8_t* taskState;
    uint8_t* taskPriority;  
    taskFunction_t* taskFunction;
    uint8_t* ptStartBlock;
} taskTCB_t;