#include "Parser.h"

Parser *Parser::instance = nullptr;

Parser::Parser() : lexer(LexicalAnalyzer::getInstance()), symTab(SymbolTable::getInstance()),
                   infoMan(InformationManager::getInstance()) {}

Parser *Parser::getInstance() {
    if (instance == nullptr) {
        instance = new Parser();
    }
    return instance;
}

void Parser::program() {
    lexer->lexical();
    statements();
    symTab->print_all();
}

void Parser::statements() {
    infoMan->initializeInfo();
    statement();
    infoMan->printInfo();
    if (lexer->getNextToken() == TokenType::SEMI_COLON) {
        lexer->lexical();
        statements();
    }
}

void Parser::statement() {
    std::string lhs_name = lexer->getTokenStr();
    if (lexer->getNextToken() == TokenType::IDENT) {
        infoMan->increaseIdentNum();
        lexer->lexical();
    } else {
        lhs_name.clear();
        infoMan->pushError(1, "");
        if (lexer->getNextToken() != TokenType::ASSIGN_OP && lexer->getNextToken() != TokenType::SEMI_COLON &&
            lexer->getNextToken() != TokenType::END_OF_FILE) {
            lexer->lexical();
        }
    }
    if (lexer->getNextToken() == TokenType::ASSIGN_OP) {
        lexer->lexical();
    } else {
        infoMan->pushWarning(3, "");
        infoMan->increaseAssignmentNum();
    }
    expression();
    symTab->insert(lhs_name, valStack.top());
    valStack.pop();
}

void Parser::expression() {
    term();
    termTail();
}

void Parser::term() {
    factor();
    factorTail();
}

void Parser::termTail() {
    if (lexer->getNextToken() == TokenType::ADD_OP) {
        infoMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        term();
        Value v2 = valStack.top();
        valStack.pop();
        Value v1 = valStack.top();
        valStack.pop();
        valStack.push(Value::cal(v1, v2, prevTokenStr[0])); // Assuming '+' operator is overloaded in Value
        termTail();
    }
}

void Parser::factor() {
    if (lexer->getNextToken() == TokenType::LEFT_PAREN || lexer->getNextToken() == TokenType::IDENT ||
        lexer->getNextToken() == TokenType::CONST) {
        if (lexer->getNextToken() == TokenType::LEFT_PAREN) {
            lexer->lexical();
            expression();
            if (lexer->getNextToken() == TokenType::RIGHT_PAREN) {
                lexer->lexical();
            } else {
                infoMan->pushWarning(1, "");
            }
        } else if (lexer->getNextToken() == TokenType::IDENT) {
            infoMan->increaseIdentNum();
            Value found = symTab->find(lexer->getTokenStr());
            if (!found.getIsInitialized()) {
                infoMan->pushError(0, lexer->getTokenStr());
            }
            valStack.push(found);
            lexer->lexical();
        } else if (lexer->getNextToken() == TokenType::CONST) {
            infoMan->increaseConstNum();
            valStack.emplace(std::stoi(lexer->getTokenStr()));
            lexer->lexical();
        }
        while (lexer->getNextToken() != TokenType::ADD_OP && lexer->getNextToken() != TokenType::MULT_OP &&
               lexer->getNextToken() != TokenType::RIGHT_PAREN && lexer->getNextToken() != TokenType::SEMI_COLON &&
               lexer->getNextToken() != TokenType::END_OF_FILE) {
            infoMan->pushWarning(2, lexer->getTokenStr());
            lexer->lexical();
        }
    } else {
        valStack.emplace();
        infoMan->pushWarning(5, lexer->getTokenStr());
    }
}

void Parser::factorTail() {
    if (lexer->getNextToken() == TokenType::MULT_OP) {
        infoMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        factor();
        Value v2 = valStack.top();
        valStack.pop();
        Value v1 = valStack.top();
        valStack.pop();
        valStack.push(Value::cal(v1, v2, prevTokenStr[0])); // Assuming '*' operator is overloaded in Value
        factorTail();
    }
}
