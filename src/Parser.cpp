#include "Parser.h"

Parser *Parser::instance = nullptr;

Parser::Parser()
        : lexer(Lexer::getInstance()),
          symTab(SymbolTable::getInstance()),
          ctxMan(ContextManager::getInstance()) {}

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
    ctxMan->initializeInfo();
    statement();
    // Assuming printTokenStr exists and accepts std::string.
    lexer->printTokenStr("");
    ctxMan->printInfo();
    if (lexer->getNextToken() == TokenType::SEMI_COLON) {
        lexer->lexical();
        statements();
    }
}

void Parser::statement() {
    std::string lhs_name = lexer->getTokenStr();
    if (lexer->getNextToken() == TokenType::IDENT) {
        lexer->printTokenStr("");
        ctxMan->increaseIdentNum();
        lexer->lexical();
    } else {
        lexer->printTokenStr("[Unknown]");
        lhs_name.clear();
        ctxMan->pushError(1, "");
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
        ctxMan->pushWarning(3, "");
        ctxMan->increaseAssignmentNum();
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
        ctxMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        while (lexer->getNextToken() == TokenType::MULT_OP || lexer->getNextToken() == TokenType::ADD_OP) {
            ctxMan->pushWarning(0, lexer->getTokenStr());
            lexer->lexical();
        }
        term();
        Var v2 = valStack.top();
        valStack.pop();
        Var v1 = valStack.top();
        valStack.pop();
        valStack.push(Var::cal(v1, v2, prevTokenStr[0]));
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
        ctxMan->increaseOpNum();
        std::string prevTokenStr = lexer->getTokenStr();
        lexer->lexical();
        while (lexer->getNextToken() == TokenType::MULT_OP || lexer->getNextToken() == TokenType::ADD_OP) {
            ctxMan->pushWarning(0, lexer->getTokenStr());
            lexer->lexical();
        }
        factor();
        Var v2 = valStack.top();
        valStack.pop();
        Var v1 = valStack.top();
        valStack.pop();
        valStack.push(Var::cal(v1, v2, prevTokenStr[0]));
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
                ctxMan->pushWarning(1, "");
            }
        } else if (nextToken == TokenType::IDENT) {
            lexer->printTokenStr("");
            ctxMan->increaseIdentNum();
            Var found = symTab->find(lexer->getTokenStr());
            if (!found.getIsInitialized()) {
                ctxMan->pushError(0, lexer->getTokenStr());
            }
            valStack.push(found);
            lexer->lexical();
        } else {
            lexer->printTokenStr("");
            ctxMan->increaseConstNum();
            valStack.emplace(std::stoi(lexer->getTokenStr()));
            lexer->lexical();
        }
        while ((nextToken = lexer->getNextToken()) != TokenType::ADD_OP && nextToken != TokenType::MULT_OP &&
               nextToken != TokenType::RIGHT_PAREN && nextToken != TokenType::SEMI_COLON &&
               nextToken != TokenType::END_OF_FILE) {
            ctxMan->pushWarning(2, lexer->getTokenStr());
            lexer->lexical();
        }
    } else {
        valStack.emplace();
        lexer->printTokenStr("[Unknown]");
        ctxMan->pushWarning(5, lexer->getTokenStr());
    }
}
