#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern int* __end[];

int* heap_ptr = (int*) &__end;

void* _sbrk(__uint8_t size)
{
    int* prev_block = heap_ptr;
    int* block_end = heap_ptr + size;

    heap_ptr = prev_block;

    return prev_block;
}