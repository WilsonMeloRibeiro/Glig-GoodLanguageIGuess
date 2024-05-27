#include <stdio.h>
#include "debug.h"
#include "values.h"
#include "chunk.h"
#include "common.h"


int GetLine(Chunk *chunk, int number){
    int count = number;
    for(int i=0; i<chunk->capacity;){
        if(count<= chunk->lines[i]){
            return chunk->lines[i+1];
        }else{
            count -= chunk->lines[i];
            i+=2;
        }
    }
    return 0;
}

void disassembleChunk(Chunk *chunk, const char *name)
{
    printf("== %s ==\n", name);

    for (int offset = 0; offset < chunk->count;)
    {
        offset = disassembleInstruction(chunk, offset);
    }
}
int disassembleInstruction(Chunk *chunk, int offset)
{
    printf("%04d ", offset);
    int line1 = GetLine(chunk, offset);
    int line2 = GetLine(chunk, offset+1);
    if(offset>0 && line1 == line2){
        printf("    |");
    }else{
        printf("%d ", line2);
    }
    uint8_t instruction = chunk->code[offset];
    switch (instruction)
    {
    case OP_NEGATE: return simpleInstruction("OP_NEGATE", offset);
    case OP_ADD: return simpleInstruction("OP_ADD", offset);
    case OP_SUBTRACT: return simpleInstruction("OP_SUBTRACT", offset);
    case OP_DIVIDE: return simpleInstruction("OP_DIVIDE", offset);
    case OP_MULTIPLY: return simpleInstruction("OP_MULTIPLY", offset);
    case OP_RETURN:
        return simpleInstruction("OP_RETURN", offset);
    case OP_CONSTANT:
        return ConstantInstruction("OP_CONSTANT", chunk, offset);
    default:
        printf("%i", offset);
        printf("Instruction not found\n");
        return offset + 1;
    }
}

static int simpleInstruction(const char *instruction, int offset)
{
    printf("%s\n", instruction);
    return offset + 1;
}

static int ConstantInstruction(const char *name, Chunk *chunk, int offset){
    uint8_t constant = chunk->code[offset+1];
    printf("%16s %4d ",name, constant);
    PrintValue(chunk->constants.values[constant]);
    printf("\n");

    return offset+2;
}

void PrintValue(Value value){
    printf(" %g ", value);
}