#ifndef INFORMATIONMANAGER_H
#define INFORMATIONMANAGER_H

#include <iostream>
#include <string>
#include <queue>

class InformationManager {
private:
    static InformationManager *instance;
    int identNum, constNum, opNum, leftParenNum, assignmentNum;
    std::queue<std::string> warningQueue, errorQueue;

    InformationManager();

public:
    static InformationManager *getInstance();

    void initializeInfo();

    void increaseIdentNum();

    void increaseConstNum();

    void increaseOpNum();

    void increaseLeftParenNum();

    bool decreaseLeftParenNum();

    bool increaseAssignmentNum();

    void pushError(int errorID, const std::string &str = "");

    void pushWarning(int warningID, const std::string &str = "");

    void printInfo();
};

#endif // INFORMATIONMANAGER_H
