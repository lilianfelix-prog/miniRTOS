#include <stdlib.h>
#include <string.h>
#include <ctype.h>

extern void* _sbrk(int increment);

void* heap1Malloc(size_t size)
{
    if(size == 0){
        return NULL;
    }
    void* block = _sbrk(size);
    return block;
    
}