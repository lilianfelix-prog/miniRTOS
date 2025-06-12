#include "include/task.h"
#include <stdlib.h>
#include <inttypes.h>
#define MAX_SIZE 5

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

list_t* listInit(uint8_t type)
{
    list_t* newList;
    newList->listType = type; 
    newList->index = 0;
    newList->listEnd = NULL;

    return newList;
}
