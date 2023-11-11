#include "LexicalAnalyzer.h"

LexicalAnalyzer *LexicalAnalyzer::instance = nullptr;

LexicalAnalyzer::LexicalAnalyzer(const std::string &fileName) : now(0), nextToken(TokenType::UNDEFINED),
                                                                infoMan(InformationManager::getInstance()) {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Cannot open or read the file.");
    }
    std::string line;
    while (getline(file, line)) {
        totalStr += line + " ";
    }
    totalStr += "\0"; // Simulate end of file marker
}

bool LexicalAnalyzer::initializeInstance(const std::string &fileName) {
    if (instance != nullptr) {
        return (false);
    }
    try {
        instance = new LexicalAnalyzer(fileName);
    } catch (...) {
        return (false);
    }
    return (true);
}

LexicalAnalyzer *LexicalAnalyzer::getInstance() {
    return instance;
}

TokenType LexicalAnalyzer::getNextToken() const {
    return nextToken;
}

std::string LexicalAnalyzer::getTokenStr() const {
    return tokenStr;
}

void LexicalAnalyzer::lexical() {
    bool warningFlag = false;
    int j = 0;
    std::string sb;

    while (now < totalStr.length() && totalStr[now] <= 32 && totalStr[now] > 0)
        now++;

    if (now >= totalStr.length()) {
        nextToken = TokenType::END_OF_FILE;
        return;
    }

    tokenStr = std::string(1, totalStr[now]);
    char nowChar = totalStr[now];

    if (nowChar == '+')
        nextToken = TokenType::ADD_OP;
    else if (nowChar == '-')
        nextToken = TokenType::ADD_OP;
    else if (nowChar == '*' || nowChar == '/')
        nextToken = TokenType::MULT_OP;
    else if (nowChar == '(') {
        nextToken = TokenType::LEFT_PAREN;
        infoMan->increaseLeftParenNum();
    } else if (nowChar == ')') {
        nextToken = TokenType::RIGHT_PAREN;
        if (!infoMan->decreaseLeftParenNum())
            nextToken = TokenType::UNDEFINED;
    } else if (nowChar == ';')
        nextToken = TokenType::SEMI_COLON;
    else if (nowChar == ':' && now + 1 < totalStr.length() && totalStr[now + 1] == '=') {
        nextToken = TokenType::ASSIGN_OP;
        if (!infoMan->increaseAssignmentNum())
            nextToken = TokenType::UNDEFINED;
        tokenStr += "=";
        now++;
    } else {
        if (std::isdigit(nowChar)) {
            while ((now + j < totalStr.length()) && isMetaChar(totalStr[now + j])) {
                if (std::isdigit(totalStr[now + j]))
                    sb += totalStr[now + j];
                else
                    warningFlag = true;
                j++;
            }
            nextToken = TokenType::CONST;
            tokenStr = sb;
            if (warningFlag)
                infoMan->pushWarning(6, totalStr.substr(now, j));
            now += j - 1;
        } else if (std::isalpha(nowChar) || nowChar == '_') {
            while ((now + j < totalStr.length()) && isMetaChar(totalStr[now + j])) {
                if (totalStr[now + j] == '_' || std::isalpha(totalStr[now + j]) || std::isdigit(totalStr[now + j]))
                    sb += totalStr[now + j];
                else
                    warningFlag = true;
                j++;
            }
            nextToken = TokenType::IDENT;
            tokenStr = sb;
            if (warningFlag)
                infoMan->pushWarning(7, totalStr.substr(now, j));
            now += j - 1;
        } else {
            nextToken = TokenType::UNDEFINED;
            infoMan->pushWarning(4, std::string(1, nowChar));
        }
    }
    now++;

    if (nextToken == TokenType::UNDEFINED)
        this->lexical();
}

void LexicalAnalyzer::printTokenStr(const std::string &str) {
    if (str.empty()) {
        if (nextToken == TokenType::SEMI_COLON || nextToken == TokenType::END_OF_FILE)
            std::cout << "\b;\n";
        else
            std::cout << tokenStr << " ";
    } else {
        std::cout << str << " ";
    }
}

bool LexicalAnalyzer::isMetaChar(char c) {
    return (!(c == '+' || c == '-' || c == '*' || c == '/' ||
              c == '(' || c == ')' || c == ';' || c == ' '));
}