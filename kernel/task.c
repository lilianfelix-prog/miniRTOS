/*
* Simple RTOS task definition
* preemptive task assigned A TCB: 
* - task state information
* - pointer to task context (env + register values)
*/

#include "include/task.h"

//store task by state
static taskTCB_t readyTaskList[MAX_TASK];
static taskTCB_t suspendedTaskList[MAX_TASK];
static taskTCB_t blockedTaskList[MAX_TASK];



static taskTCB_t* init_task(void* func)
{
    taskTCB_t* newTaskTCB;

    stack_t* pStartStack = heap1Malloc(sizeof(func));


}