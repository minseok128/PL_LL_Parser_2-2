#include "ContextManager.h"

ContextManager *ContextManager::instance = nullptr;

ContextManager::ContextManager() : identNum(0), constNum(0), opNum(0), leftParenNum(0), assignmentNum(0) {}

ContextManager *ContextManager::getInstance() {
    if (instance == nullptr) {
        instance = new ContextManager();
    }
    return instance;
}

void ContextManager::initializeInfo() {
    identNum = constNum = opNum = leftParenNum = assignmentNum = 0;
}

void ContextManager::increaseIdentNum() {
    identNum++;
}

void ContextManager::increaseConstNum() {
    constNum++;
}

void ContextManager::increaseOpNum() {
    opNum++;
}

void ContextManager::increaseLeftParenNum() {
    leftParenNum++;
}

bool ContextManager::decreaseLeftParenNum() {
    if (leftParenNum > 0) {
        leftParenNum--;
        return true;
    }
    pushWarning(8, "");
    return false;
}

bool ContextManager::increaseAssignmentNum() {
    if (assignmentNum == 0) {
        assignmentNum++;
        return true;
    }
    pushWarning(9, "");
    return false;
}

void ContextManager::pushError(int errorID, const std::string &str) {
    std::string errorMessage;
    switch (errorID) {
        case 0:
            errorMessage = "정의되지 않은 변수(" + str + ")가 참조됨";
            break;
        case 1:
            errorMessage = "대입 연산의 Left-hand side 명시되지 않음";
            break;
        case 2:
            errorMessage = "0으로 나누려는 시도";
            break;
        default:
            errorMessage = "Unknown Error ID: " + std::to_string(errorID);
            break;
    }
    errorQueue.push(errorMessage);
}

void ContextManager::pushWarning(int warningID, const std::string &str) {
    std::string warningMessage;
    switch (warningID) {
        case 0:
            warningMessage = "연산자(" + str + ") 중복";
            break;
        case 1:
            warningMessage = "닫는 괄호')' 누락";
            break;
        case 2:
            warningMessage = "<factor> 뒤 불필요한 요소(" + str + ") 등장";
            break;
        case 3:
            warningMessage = "대입 연산자(:=) 누락";
            break;
        case 4:
            warningMessage = "인식할 수 없는 UNDEFINED 토큰(" + str + ") 등장";
            break;
        case 5:
            warningMessage = "피연산자(상수 or 변수) 누락";
            break;
        case 6:
            warningMessage = "CONST 내부에 숫자 외의 문자 포함(" + str + ")";
            break;
        case 7:
            warningMessage = "IDENT 내부에 규칙 외의 문자 포함(" + str + ")";
            break;
        case 8:
            warningMessage = "여는 괄호'(' 누락";
            break;
        case 9:
            warningMessage = "대입연산자 중복(:=)";
            break;
        default:
            warningMessage = "Unknown Warning ID: " + std::to_string(warningID);
            break;
    }
    warningQueue.push(warningMessage);
}

namespace Color {
    const std::string RESET = "\033[0m";
    const std::string MAGENTA = "\033[35m";
    const std::string YELLOW = "\033[33m";
    const std::string RED = "\033[31m";
    const std::string GREEN = "\033[32m";
}

void ContextManager::printInfo() {
    std::cout << Color::MAGENTA;
    std::cout << "ID: " << identNum << "; CONST: " << constNum << "; OP: " << opNum << ";" << Color::RESET << '\n';

    if (warningQueue.empty() && errorQueue.empty()) {
        std::cout << Color::GREEN << "(OK)" << Color::RESET << '\n';
    } else {
        while (!warningQueue.empty()) {
            std::cout << Color::YELLOW << "(Warning) " << warningQueue.front() << Color::RESET << '\n';
            warningQueue.pop();
        }
        while (!errorQueue.empty()) {
            std::cout << Color::RED << "(Error) " << errorQueue.front() << Color::RESET << '\n';
            errorQueue.pop();
        }
    }
}