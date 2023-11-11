#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

# include <iostream>
# include <string>
# include <fstream>
# include <stdexcept>
# include "ContextManager.h"

enum class TokenType {
    CONST,
    IDENT,
    ASSIGN_OP,
    ADD_OP,
    MULT_OP,
    LEFT_PAREN,
    RIGHT_PAREN,
    SEMI_COLON,
    UNDEFINED,
    END_OF_FILE
};

class Lexer {
private:
    ContextManager *ctxMan;
    static Lexer *instance;
    std::string totalStr;
    int now;
    TokenType nextToken;
    std::string tokenStr;

    explicit Lexer(const std::string &fileName);

public:
    static bool initializeInstance(const std::string &fileName);

    static Lexer *getInstance();

    TokenType getNextToken() const;

    std::string getTokenStr() const;

    void lexical();

    void printTokenStr(const std::string &str);

    static bool isMetaChar(char c);
};

#endif // LEXICALANALYZER_H
