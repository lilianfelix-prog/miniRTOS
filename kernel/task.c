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
    volatile stack_t* ptStackTop; // startStack + size
    state_t* taskState;
    priority_t* taskPriority;
    stack_t* startStack;

} taskTCB_t;

//store task by state
static taskTCB_t readyTaskList[MAX_TASK];
static taskTCB_t suspendedTaskList[MAX_TASK];
static taskTCB_t blockedTaskList[MAX_TASK];

static taskTCB_t* init_task()
{
    taskTCB_t* newTaskTCB;

    stack_t* pStartStack = heap1Malloc();
}