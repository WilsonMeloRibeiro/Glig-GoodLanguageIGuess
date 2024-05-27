#include <stdio.h>
#include "common.h"
#include "compiler.h"
#include "scanner.h"

void Compile(const char* source){
    InitScanner(source);
    int line = -1;
    for(;;){
        Token token = ScanToken();
        if(token.line == line){
            printf("    | ");
        }
        else{
            printf("%4d ", token.line);
        }
        line = token.line;
        printf("%2d '%.*s'\n", token.type, token.length, token.start);

        if(token.type == TOKEN_EOF){
            break;
        }
    }
}