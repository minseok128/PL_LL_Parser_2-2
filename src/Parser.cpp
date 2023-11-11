#include "Parser.h"

Parser *Parser::instance = nullptr;

Parser::Parser()
        : lexer(LexicalAnalyzer::getInstance()),
          symTab(SymbolTable::getInstance()),
          infoMan(InformationManager::getInstance()) {}

Parser *Parser::getInstance() {
    if (instance == nullptr) {
        instance = new Parser();
    }
    return (instance);
}

void Parser::program() {
    lexer->lexical();
    statements();
    symTab->print_all();
}

void Parser::statements() {
    infoMan->initializeInfo();
    statement();
    // Assuming printTokenStr exists and accepts std::string.
    lexer->printTokenStr("");
    infoMan->printInfo();
    if (lexer->getNextToken() == TokenType::SEMI_COLON) {
        lexer->lexical();
        statements();
    }
}

void Parser::statement() {
    std::string lhs_name = lexer->getTokenStr();
    if (lexer->getNextToken() == TokenType::IDENT) {
        lexer->printTokenStr("");
        infoMan->increaseIdentNum();
        lexer->lexical();
    } else {
        lexer->printTokenStr("[Unknown]");
        lhs_name.clear();
        infoMan->pushError(1, "");
        if (lexer->getNextToken() != TokenType::ASSIGN_OP && lexer->getNextToken() != TokenType::SEMI_COLON &&
            lexer->getNextToken() != TokenType::END_OF_FILE) {
            lexer->lexical();
        }
    }
    if (lexer->getNextToken() == TokenType::ASSIGN_OP) {
        lexer->printTokenStr("");
        lexer->lexical();
    } else {
        lexer->printTokenStr(":=");
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

void Parser::termTail() {
    if (lexer->getNextToken() == TokenType::ADD_OP) {
        lexer->printTokenStr("");
        infoMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        while (lexer->getNextToken() == TokenType::MULT_OP || lexer->getNextToken() == TokenType::ADD_OP) {
            infoMan->pushWarning(0, lexer->getTokenStr());
            lexer->lexical();
        }
        term();
        Value v2 = valStack.top();
        valStack.pop();
        Value v1 = valStack.top();
        valStack.pop();
        valStack.push(Value::cal(v1, v2, prevTokenStr[0]));
        termTail();
    }
}

void Parser::term() {
    factor();
    factorTail();
}

void Parser::factorTail() {
    if (lexer->getNextToken() == TokenType::MULT_OP) {
        lexer->printTokenStr("");
        infoMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        while (lexer->getNextToken() == TokenType::MULT_OP || lexer->getNextToken() == TokenType::ADD_OP) {
            infoMan->pushWarning(0, lexer->getTokenStr());
            lexer->lexical();
        }
        factor();
        Value v2 = valStack.top();
        valStack.pop();
        Value v1 = valStack.top();
        valStack.pop();
        valStack.push(Value::cal(v1, v2, prevTokenStr[0]));
        factorTail();
    }
}

void Parser::factor() {
    TokenType nextToken = lexer->getNextToken();
    if (nextToken == TokenType::LEFT_PAREN || nextToken == TokenType::IDENT || nextToken == TokenType::CONST) {
        if (nextToken == TokenType::LEFT_PAREN) {
            lexer->printTokenStr("");
            lexer->lexical();
            expression();
            if (lexer->getNextToken() == TokenType::RIGHT_PAREN) {
                lexer->printTokenStr("");
                lexer->lexical();
            } else {
                lexer->printTokenStr(")");
                infoMan->pushWarning(1, "");
            }
        } else if (nextToken == TokenType::IDENT) {
            lexer->printTokenStr("");
            infoMan->increaseIdentNum();
            Value found = symTab->find(lexer->getTokenStr());
            if (!found.getIsInitialized()) {
                infoMan->pushError(0, lexer->getTokenStr());
            }
            valStack.push(found);
            lexer->lexical();
        } else {
            lexer->printTokenStr("");
            infoMan->increaseConstNum();
            valStack.emplace(std::stoi(lexer->getTokenStr()));
            lexer->lexical();
        }
        while ((nextToken = lexer->getNextToken()) != TokenType::ADD_OP && nextToken != TokenType::MULT_OP &&
               nextToken != TokenType::RIGHT_PAREN && nextToken != TokenType::SEMI_COLON &&
               nextToken != TokenType::END_OF_FILE) {
            infoMan->pushWarning(2, lexer->getTokenStr());
            lexer->lexical();
        }
    } else {
        valStack.emplace();
        lexer->printTokenStr("[Unknown]");
        infoMan->pushWarning(5, lexer->getTokenStr());
    }
}
