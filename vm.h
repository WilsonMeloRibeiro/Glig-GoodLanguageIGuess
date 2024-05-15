#ifndef glig_vm_h
#define glig_vm_h

#include "debug.h"
#include "common.h"
#include "chunk.h"

typedef struct {
  Chunk *chunk;
  uint8_t *ip;
} VM;

typedef enum {
    INTERPRETER_OK,
    INTERPRETER_COMPILE_ERROR,
    INTERPRETER_RUNTIME_ERROR
} InterpreterResult;

static InterpreterResult run();
InterpreterResult Interpret(Chunk *chunk);
void InitVM();
void FreeVM();

#endif