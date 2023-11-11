#ifndef PARSER_H
#define PARSER_H

#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include "InformationManager.h"
#include "Value.h"
#include <stack>

class Parser {
private:
    LexicalAnalyzer* lexer;
    SymbolTable* symTab;
    InformationManager* infoMan;
    std::stack<Value> valStack;
    static Parser* instance;

    Parser();

public:
    static Parser* getInstance();
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
