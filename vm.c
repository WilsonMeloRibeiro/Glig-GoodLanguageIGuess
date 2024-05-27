#include "vm.h"
#include <stdio.h>
#include "debug.h"
#include "compiler.c"
#include "common.h"

//(TODO): Change vm declaration
VM vm;

InterpreterResult Interpret(const char *source){
    Compile(source);
    return INTERPRETER_OK;
}

static InterpreterResult run(){
    #define READ_BYTE() (*vm.ip++)
    #define READ_CONSTANT() (vm.chunk->constants.values[READ_BYTE()])
    
    #define BINARY_OP(op) \
    do{\
        double b = Pop();\
        double a = Pop();\
        Push(a op b);\
        } while(false)

    for(;;){
        #ifdef DEBUG_TRACE_EXECUTION
            printf("    ");
            for(Value *slot = vm.stack; slot<vm.stackTop; slot++){
                printf("[");
                PrintValue(*slot);
                printf("]");
            }
            printf("\n");
            disassembleInstruction(vm.chunk, (int) (vm.ip - vm.chunk->code));
        #endif


        uint8_t instruction;
        switch (instruction = READ_BYTE())
        {
        case OP_CONSTANT :{
            Value constant = READ_CONSTANT();
            Push(constant);
            PrintValue(constant);
            printf("\n");
            break;
        }
        case OP_NEGATE: *(vm.stackTop-1) = -(*(vm.stackTop-1)); break;
        case OP_ADD: BINARY_OP(+); break;
        case OP_SUBTRACT: BINARY_OP(-); break;
        case OP_MULTIPLY: BINARY_OP(*); break;
        case OP_DIVIDE: BINARY_OP(/); break;
        case OP_RETURN:{
            PrintValue(Pop());
            printf("\n");
            return INTERPRETER_OK;

        }
        }
    }
    #undef READ_BYTE
    #undef READ_CONSTANT
    #undef BINARY_OP
}

static void ResetStack(){    
    vm.stackTop = vm.stack;
}

void InitVM()
{
    ResetStack();
}
void FreeVM()
{

}

void Push(Value value){
    *vm.stackTop = value;
    vm.stackTop++;
}

Value Pop(){
    vm.stackTop--;
    return *vm.stackTop;
}
