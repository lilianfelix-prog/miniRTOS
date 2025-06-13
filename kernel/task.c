/*
* Simple RTOS task definition
* preemptive task assigned A TCB: 
* - task state information
* - pointer to task context (env + register values)
*/

#include "../include/task.h"
#include <inttypes.h>
#include <stdlib.h>
#include <string.h>
#include "task_handler.c"

//store task by state
static list_t* readyTaskList;
static list_t* suspendedTaskList;
static list_t* blockedTaskList;



static taskTCB_t* init_task(taskFunction_t* func, uint8_t priority, uint8_t status)
{
    taskTCB_t* newTaskTCB;
    
    newTaskTCB->ptStartBlock = newTaskTCB;
    //fill stack with zero to debug
    memset(newTaskTCB->ptStartBlock, 0x00, sizeof(taskTCB_t));

    //initialse pointers to TCB assuming the stack grows downward 
    newTaskTCB->ptBlockTop = ( newTaskTCB - sizeof(taskTCB_t) );

    newTaskTCB->taskFunction = func;
    newTaskTCB->taskPriority = priority;
    newTaskTCB->taskState = status;

    if (status == F_RDY && readyTaskList != NULL)
    {
        readyTaskList = listInit(F_RDY);
    }
    initialiseItemList();
    
    return newTaskTCB;

}

