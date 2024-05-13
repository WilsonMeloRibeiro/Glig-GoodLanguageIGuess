#ifndef clox_chunk_h
#define clox_chunk_h

#include "common.h"
#include "values.h"

typedef enum
{
    OP_RETURN,
    OP_CONSTANT,
} OpCode;

typedef struct
{
    int capacity;
    int count;
    ValueArray constants;
    int *lines;
    uint8_t *code;
} Chunk;

void InitChunk(Chunk *chunk);
void FreeChunk(Chunk *chunk);
void WriteChunk(Chunk *chunk, uint8_t byte, int line);
int AddConstant(Chunk *chunk, Value value);

#endif