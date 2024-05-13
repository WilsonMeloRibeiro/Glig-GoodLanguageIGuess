#ifndef clox_debug_h
#define clox_debug_h

#include "chunk.h"

void disassembleChunk(Chunk* chunk, const char* name);
int disassembleInstruction(Chunk* chunk, int offset);
static int simpleInstruction(const char *instruction, int offset);
static int ConstantInstruction(const char *name,Chunk *chunk, int offset);
void PrintValue(Value value);
int GetLine(Chunk *chunk, int number);

#endif