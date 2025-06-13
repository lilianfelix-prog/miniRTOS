#include <stdlib.h>
#include <string.h>
#include <ctype.h>

/**
 * fetching the addr of the end of bss in memory set in linker.ld,
 *  where the heap starts.
 */
extern int* __end[];
// Initialise pointer to the current top of heap with the __end addr
// variable set .sdata
int* heap_ptr = (int*) &__end;

/**
 * Add the size asked to the heap pointer
 * Returns the end of the previous block, which is now the start of this block
 */
void* _sbrk(__uint8_t size)
{
    int* prev_block = heap_ptr;
    int* block_end = heap_ptr + size;

    heap_ptr = prev_block;

    return prev_block;
}

void _sbrkf_free(void* block)
{
    if( block != NULL){
        memset(block, 0x00, )
    }
}