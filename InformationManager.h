#ifndef INFORMATIONMANAGER_H
#define INFORMATIONMANAGER_H

#include <string>
#include <queue>
#include <iostream>

class InformationManager {
private:
    static InformationManager *instance;
    int identNum, constNum, opNum, leftParenNum, assignmentNum;
    std::queue<std::string> warningQueue, errorQueue;

    explicit InformationManager();

public:
    static InformationManager *getInstance();

    void initializeInfo();

    void increaseIdentNum();

    void increaseConstNum();

    void increaseOpNum();

    void increaseLeftParenNum();

    bool decreaseLeftParenNum();

    bool increaseAssignmentNum();

    void pushError(int errorID, const std::string &str);

    void pushWarning(int warningID, const std::string &str);

    void printInfo();

    // Destructor
    ~InformationManager();
};

#endif // INFORMATIONMANAGER_H
