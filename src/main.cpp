#include "Lexer.h"
#include "Parser.h"

int main(int argc, char **argv) {
    if (!Lexer::initializeInstance(argv[1]))
        return (1);
    Parser::getInstance()->program();
    return (0);
}
