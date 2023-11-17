#ifndef CONTEXTMANAGER_H
#define CONTEXTMANAGER_H

# include <iostream>
# include <string>
# include <queue>

namespace Color {
	const std::string RESET = "\033[0m";
	const std::string MAGENTA = "\033[35m";
	const std::string YELLOW = "\033[33m";
	const std::string RED = "\033[31m";
	const std::string GREEN = "\033[32m";
}

class ContextManager {
private:
	static ContextManager *instance;
	int identNum, constNum, opNum, leftParenNum, assignmentNum;
	std::queue<std::string> warningQueue, errorQueue;

	ContextManager();

public:
	static ContextManager *getInstance();

	void initializeInfo();

	void increaseIdentNum();

	void increaseConstNum();

	void increaseOpNum();

	void increaseLeftParenNum();

	bool decreaseLeftParenNum();

	bool increaseAssignmentNum();

	void pushError(int errorID, const std::string &str = "");

	void pushWarning(int warningID, const std::string &str = "");

	void printInfo(bool vOption);
};

#endif // CONTEXTMANAGER_H
