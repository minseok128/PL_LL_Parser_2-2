#ifndef PARSER_H
#define PARSER_H

#include <stack>
#include "Lexer.h"
#include "SymbolTable.h"
#include "ContextManager.h"
#include "Var.h"

class Parser {
private:
    Lexer *lexer;
    SymbolTable *symTab;
    ContextManager *ctxMan;
    std::stack<Var> valStack;
    static Parser *instance;

    Parser();

public:
    static Parser *getInstance();

    void program();

private:
    void statements();

    void statement();

    void expression();

    void term();

    void termTail();

    void factor();

    void factorTail();
};

#endif // PARSER_H
