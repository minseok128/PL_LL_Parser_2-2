#ifndef LEXICALANALYZER_H
#define LEXICALANALYZER_H

# include <iostream>
# include <string>
# include <fstream>
# include <stdexcept>
# include "ContextManager.h"
# include "TokenType.h"

class Lexer {
private:
    ContextManager *ctxMan;
    static Lexer *instance;
    std::string totalStr;
    unsigned int now;
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
