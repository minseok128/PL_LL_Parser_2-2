#ifndef LEXER_H
#define LEXER_H

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
	static bool vOption;

	static bool initializeInstance(char **argv);

	static Lexer *getInstance();

	TokenType getNextToken() const;

	std::string getTokenStr() const;

	void lexical();

	void printTokenStr(const std::string &str);

	static bool isMetaChar(char c);

	static std::string TokenTypeToString(TokenType type);
};

#endif // LEXER_H
