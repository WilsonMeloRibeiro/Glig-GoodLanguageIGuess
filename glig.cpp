#include <stdlib.h>
#include <stdio.h>
#include "vm.c"
#include "values.c"
#include "memory.c"
#include "chunk.c"
#include "debug.c"

int main(int argc, char *argv[])
{
    InitVM();    
    Chunk test;
    InitChunk(&test);
    int constant = AddConstant(&test, 1.2);
    WriteChunk(&test, OP_CONSTANT, 123);
    WriteChunk(&test, constant, 123);
    WriteChunk(&test, OP_RETURN, 127);
    disassembleChunk(&test, "Chunk Test");
    Interpret(&test);
    FreeVM();
    FreeChunk(&test);
    return 0;
}