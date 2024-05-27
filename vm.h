#ifndef glig_vm_h
#define glig_vm_h

#define STACK_MAX 256

#include "debug.h"
#include "common.h"
#include "chunk.h"
#include "values.h"

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
  Value stack[STACK_MAX];
  Value *stackTop;
} VM;

typedef enum {
    INTERPRETER_OK,
    INTERPRETER_COMPILE_ERROR,
    INTERPRETER_RUNTIME_ERROR
} InterpreterResult;

static InterpreterResult run();
InterpreterResult Interpret(const char *source);
void ResetStack();
void Push(Value value);
Value Pop();
void InitVM();
void FreeVM();

#endif