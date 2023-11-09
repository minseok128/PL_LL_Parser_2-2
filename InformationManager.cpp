#include "InformationManager.h"

// Initialize the static instance pointer
InformationManager *InformationManager::instance = nullptr;

InformationManager::InformationManager()
        : identNum(0), constNum(0), opNum(0), leftParenNum(0), assignmentNum(0) {}

InformationManager *InformationManager::getInstance() {
    if (instance == nullptr) {
        instance = new InformationManager();
    }
    return (instance);
}

void InformationManager::initializeInfo() {
    identNum = constNum = opNum = leftParenNum = assignmentNum = 0;
}

void InformationManager::increaseIdentNum() { identNum++; }

void InformationManager::increaseConstNum() { constNum++; }

void InformationManager::increaseOpNum() { opNum++; }

void InformationManager::increaseLeftParenNum() { leftParenNum++; }

bool InformationManager::decreaseLeftParenNum() {
    if (leftParenNum > 0) {
        leftParenNum--;
        return (true);
    } else {
        pushWarning(8, "Unmatched parenthesis.");
        return (false);
    }
}

bool InformationManager::increaseAssignmentNum() {
    if (assignmentNum == 0) {
        assignmentNum++;
        return (true);
    } else {
        pushWarning(9, "Multiple assignments.");
        return (false);
    }
}

void InformationManager::pushError(int errorID, const std::string &str) {
    std::string errorMessage = "Error " + std::to_string(errorID) + ": " + str;
    errorQueue.push(errorMessage);
}

void InformationManager::pushWarning(int warningID, const std::string &str) {
    std::string warningMessage = "Warning " + std::to_string(warningID) + ": " + str;
    warningQueue.push(warningMessage);
}

void InformationManager::printInfo() {
    while (!errorQueue.empty()) {
        std::cout << "Error: " << errorQueue.front() << std::endl;
        errorQueue.pop();
    }
    while (!warningQueue.empty()) {
        std::cout << "Warning: " << warningQueue.front() << std::endl;
        warningQueue.pop();
    }
}

InformationManager::~InformationManager() {
    // Clean-up code, if needed. For example:
    while (!errorQueue.empty()) errorQueue.pop();
    while (!warningQueue.empty()) warningQueue.pop();
    // Since we're using a singleton, this would be called at the end of the program.
}
