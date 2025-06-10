/*
* Simple RTOS task definition
* preemptive task assigned A TCB: 
* - task state information
* - pointer to task context (env + register values)
*/

#include "task.h"


typedef struct
{
    //variable shared between Interupt are volatile, can change unexpectedly
    volatile stack_t* ptStackTop; // 
    state_t* taskState;
    priority_t* taskPriority;
    stack_t* startStack;

} taskTCB;
