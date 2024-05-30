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

static char Peek(){
    return *scanner.current;
}
static char PeekNext(){
    if(IsAtEnd()) return '\n';
    return scanner.current[1];
}

static void SkipWhiteSpace(){
    for(;;){
        char c = Peek();
        switch (c)
        {
        case'\r':
        case' ':
        case'\t':
            Advance();
            break;
        case'\n':
            scanner.line++;
            Advance();
            break;
        case'/':
            if (PeekNext()=='/'){
                while(Peek()!='\n' && !IsAtEnd()) Advance();
            }else{
                return;
            }
            break;
        default:
            return;
        }
    }
}

void InitScanner(const char *source)
{
    scanner.current = source;
    scanner.start = source;
    scanner.line = 1;
}

static Token MakeString(){
    for (;;)
    {
        char c = Peek();
        while(c != '"' && !IsAtEnd()){
            if(c=='\n') scanner.line++;
            Advance();
        }
        if(IsAtEnd()) return ErrorToken("Unterminated String.");

        Advance();
        return MakeToken(TOKEN_STRING);
    }
    
}

static bool IsDigit(char c){
    return c>= '0' && c<='9';
}

static bool IsAtEnd(){
    return *scanner.current == '\0';
}

static Token MakeNumber(){
    while(IsDigit(Peek())) Advance();

    if(Peek()=='.' && IsDigit(PeekNext())) {
        Advance();
        while (IsDigit(Peek())) Advance();
    }

    return MakeToken(TOKEN_NUMBER);
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

static bool Match(const char expected){
    if(IsAtEnd()) return false;
    if(expected != *scanner.current) return false;
    scanner.current++;
    return true;
}

static char Advance(){
    scanner.current++;
    return scanner.current[-1];
}

Token ScanToken(){
    SkipWhiteSpace();
    scanner.start = scanner.current;

    if(IsAtEnd()) return MakeToken(TOKEN_EOF);

    char c = Advance();
    if(IsDigit(c)) return MakeNumber();

    switch (c)
    {
    case '+': return MakeToken(TOKEN_PLUS);
    case '-': return MakeToken(TOKEN_MINUS);
    case '/': return MakeToken(TOKEN_SLASH);
    case '*': return MakeToken(TOKEN_STAR);
    case '(': return MakeToken(TOKEN_LEFT_PAREN);
    case ')': return MakeToken(TOKEN_RIGHT_PAREN);
    case '{': return MakeToken(TOKEN_LEFT_BRACE);
    case '}': return MakeToken(TOKEN_RIGHT_BRACE);
    case ';': return MakeToken(TOKEN_SEMICOLON);
    case ',': return MakeToken(TOKEN_COMMA);
    case '.': return MakeToken(TOKEN_DOT);
    case '!': return MakeToken(Match('=')? TOKEN_BANG_EQUAL: TOKEN_BANG);
    case '=': return MakeToken(Match('=')? TOKEN_EQUAL_EQUAL: TOKEN_EQUAL);
    case '>': return MakeToken(Match('=')? TOKEN_GREATER_EQUAL: TOKEN_GREATER);
    case '<': return MakeToken(Match('=')? TOKEN_LESS_EQUAL: TOKEN_LESS);
    case '"': return MakeString();
    default:
        break;
    }

    return ErrorToken("Token not indentified");
}