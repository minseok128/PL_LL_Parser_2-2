#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv) {
	if (argc < 2)
		return (1);
	if (!Lexer::initializeInstance(argv))
		return (1);
	Parser::getInstance()->program();
	return (0);
}
