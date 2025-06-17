#include "include/task.h"
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>
#define MAX_SIZE 5


//store task by state
static list_t* readyTaskList;
static list_t* suspendedTaskList;
static list_t* blockedTaskList;

/*
* Simple RTOS task definition
* preemptive task assigned A TCB: 
* - task state information
* - pointer to task context (env + register values)
*/

//implementing a linked list to handle the task status lists

struct taskListItem
{
    taskTCB_t* listItem;
    struct taskListItem* nextTask;
    struct taskListItem* prevTask;
};
typedef struct taskListItem taskListItem_t;

typedef struct
{
    uint8_t listType;
    uint8_t* index;
    taskListItem_t* listEnd;
} list_t;

int addToListEnd(taskListItem_t* task, list_t* list)
{
    if(*list->index < 5){
        *list->index += 1;
        list->listEnd->nextTask = task;
        task->prevTask = list->listEnd;
        list->listEnd = task;
    }else{
        return -1;
    }
    return 0;
}

void listInit()
{
    
    readyTaskList->listType = F_RDY; 
    readyTaskList->index = 0;
    readyTaskList->listEnd = NULL;
    
    suspendedTaskList->listType = f_SSD; 
    suspendedTaskList->index = 0;
    suspendedTaskList->listEnd = NULL;

    blockedTaskList->listType = F_BCK; 
    blockedTaskList->index = 0;
    blockedTaskList->listEnd = NULL;

    return 0;
}

int initialiseItemList(taskTCB_t* task, list_t* list)
{
    taskListItem_t* newTaskItem;
    newTaskItem->listItem = task;
    newTaskItem->nextTask = NULL;
    newTaskItem->prevTask = NULL;

    if(addToListEnd(newTaskItem, list) < 0) return -1;
    return 0;
}

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

    list_t* setList;

    if (status == F_RDY) setList = readyTaskList;
    if (status == F_BCK) setList = blockedTaskList;
    if (status == f_SSD) setList = suspendedTaskList;

    initialiseItemList(newTaskTCB, setList);
    
    return newTaskTCB;

}