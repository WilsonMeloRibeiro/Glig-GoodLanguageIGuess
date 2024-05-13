#include "common.h"
#include <stdlib.h>
#include <stdio.h>
#include "chunk.h"
#include "debug.h"
#include "memory.h"
#include "values.h"
#include "values.c"
#include "memory.c"
#include "chunk.c"
#include "debug.c"

int main(int argc, char *argv[])
{
    Chunk test;
    InitChunk(&test);
    int constant = AddConstant(&test, 1.2);
    WriteChunk(&test, OP_CONSTANT, 123);
    WriteChunk(&test, constant, 123);
    WriteChunk(&test, OP_RETURN, 123);
    WriteChunk(&test, OP_RETURN, 123);
    WriteChunk(&test, OP_RETURN, 127);
    disassembleChunk(&test, "Chunk Test");
    FreeChunk(&test);
    return 0;
}