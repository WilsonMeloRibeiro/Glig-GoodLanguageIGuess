#include <stdio.h>
#include <string.h>
#include "common.h"
#include "scanner.h"


typedef struct
{
    const char *start;
    const char *current;
    int line;
} Scanner;

Scanner scanner;

void InitScanner(const char *source)
{
    scanner.current = source;
    scanner.start = source;
    scanner.line = 1;
}

static bool IsAtEnd(){
    return *scanner.current == '\0';
}

static Token MakeToken(TokenType type){
    Token token;
    token.type = type;
    token.length = (int)(scanner.current - scanner.start);
    token.start = scanner.start;
    token.line = scanner.line;
    return token;
}
static Token ErrorToken(const char* error){
    Token token;
    token.type = TOKEN_ERROR;
    token.length = (int)strlen(error);
    token.start = error;
    token.line = scanner.line;
    return token;
}

Token ScanToken(){
    scanner.start = scanner.current;

    if(IsAtEnd()) return MakeToken(TOKEN_EOF);

    return ErrorToken("Token not indentified");
}