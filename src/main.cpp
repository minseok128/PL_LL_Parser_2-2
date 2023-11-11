#include "LexicalAnalyzer.h"
#include "Parser.h"

int main(int argc, char **argv) {
    if (!LexicalAnalyzer::initializeInstance(argv[1]))
        return (1);
    Parser::getInstance()->program();
    return (0);
}
