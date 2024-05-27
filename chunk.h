#ifndef glig_chunk_h
#define glig_chunk_h

#include "common.h"
#include "values.h"

typedef enum
{
    OP_RETURN,
    OP_NEGATE,
    OP_ADD,
    OP_SUBTRACT,
    OP_MULTIPLY,
    OP_DIVIDE,
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