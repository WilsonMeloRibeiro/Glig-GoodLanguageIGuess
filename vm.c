#include "vm.h"
#include <stdio.h>
#include "debug.h"
#include "common.h"

//(TODO): Change vm declaration
VM vm;

InterpreterResult Interpret(Chunk *chunk){
    vm.chunk = chunk;
    vm.ip = chunk->code;
    return run();
}

static InterpreterResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])

    for(;;){
        #ifdef DEBUG_TRACE_EXECUTION
            disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));
        #endif


        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_CONSTANT :{
            Value constant = READ_CONSTANT();
            PrintValue(constant);
            printf("\n");
            break;
        }
        case OP_RETURN:{
        return INTERPRETER_OK;

        }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
}

void InitVM()
{
    
}
void FreeVM()
{

}
