#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "vm.c"
#include "values.c"
#include "chunk.c"
#include "compiler.c"
#include "memory.c"
#include "debug.c"

static void Relp()
{
    char line[1024];
    for (;;)
    {
        printf("> ");
        if (!fgets(line, sizeof(line), stdin))
        {
            printf("Could not read line");
            break;
        }

        Interpret(line);
    }
}

static char *ReadFile(const char *path)
{
    FILE *file = fopen(path, "rb");

    //error handle
    if (!file)
    {
        fprintf(stderr, "Could not open file \"%s\".\n", path);
        exit(74);
    }

    fseek(file, 0L, SEEK_END);
    size_t fileSize = ftell(file);
    rewind(file);

    char *buffer = (char *)malloc(sizeof(fileSize) + 1);

    //error handle
    if (!buffer)
    {
        fprintf(stderr, "Not enough memory to read \"%s\".\n", path);
        exit(74);
    }

    size_t bytesRead = fread(buffer, sizeof(char), fileSize, file);

    //error handle
    if (bytesRead < fileSize)
    {
        fprintf(stderr, "Could not read file \"%s\".\n", path);
        exit(74);
    }

    buffer[bytesRead + 1] = '\0';

    fclose(file);
    return buffer;
}

void RunFile(const char *path)
{
    char *source = ReadFile(path);
    InterpreterResult result = Interpret(source);

    if (result == INTERPRETER_COMPILE_ERROR)
        exit(65);
    if (result == INTERPRETER_RUNTIME_ERROR)
        exit(70);
}

int main(int argc, char *argv[])
{
    InitVM();
    if (argc == 1)
    {
        Relp();
    }
    else if (argc == 2)
    {
        RunFile(argv[1]);
    }
    else
    {
        fprintf(stderr, "Usage: glig [path]\n");
        exit(64);
    }
    FreeVM();
    return 0;
}
