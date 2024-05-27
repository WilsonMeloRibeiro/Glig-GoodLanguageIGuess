#include "chunk.h"
#include <stdlib.h>
#include "memory.h"
#include "common.h"

void InitChunk(Chunk *chunk)
{
    chunk->capacity = 0;
    chunk->count = 0;
    chunk->code = NULL;
    chunk->lines=NULL;
    InitValue(&chunk->constants);
}

void WriteChunk(Chunk *chunk, uint8_t byte, int line)
{
    int nextEmpty =0;
    int count = chunk->count;
    for(int i = 0; i<chunk->capacity;){
        if(chunk->lines[i]>=count){
            nextEmpty = i+2;
            break;
        }else{
            count -= chunk->lines[i];
            i+=2;
        }
    }
    
    if (chunk->capacity < chunk->count + 1 || chunk->capacity < nextEmpty +2)
    {
        int oldCapacity = chunk->capacity;
        chunk->capacity = GROW_CAPACITY(oldCapacity);
        chunk->code = GROW_ARRAY(uint8_t, chunk->code, oldCapacity, chunk->capacity);
        chunk->lines = GROW_ARRAY(int, chunk->lines, oldCapacity, chunk->capacity);
    }
    chunk->code[chunk->count] = byte;
    if(line == chunk->lines[nextEmpty-1]){ 
        chunk->lines[nextEmpty-2]++;
    }else{
        chunk->lines[nextEmpty] = 1;
        chunk->lines[nextEmpty+1] = line;
    }
    chunk->count++;
}
void FreeChunk(Chunk *chunk)
{
    FREE_ARRAY(uint8_t, chunk->code, chunk->capacity);
    FREE_ARRAY(int, chunk->lines, chunk->capacity);
    FreeValue(&chunk->constants);
    InitChunk(chunk);
}

int AddConstant(Chunk *chunk, Value value){
    WriteValue(&chunk->constants, value);
    return chunk->constants.count -1;
}
