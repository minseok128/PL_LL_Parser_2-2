#include "Lexer.h"

Lexer *Lexer::instance = nullptr;
bool Lexer::vOption = false;

Lexer::Lexer(const std::string &fileName) : ctxMan(ContextManager::getInstance()),
											now(0), nextToken(TokenType::UNDEFINED) {
	std::ifstream file(fileName);
	if (!file.is_open())
		throw std::runtime_error("Cannot open or read the file.");
	std::string line;
	while (getline(file, line))
		totalStr += line + " ";
	totalStr += "\0"; // Simulate end of file marker
}

bool Lexer::initializeInstance(char **argv) {
	if (instance != nullptr) {
		return (false);
	}
	try {
		std::string argv1 = argv[1], filename;
		if (argv1 == "-v") {
			Lexer::vOption = true;
			filename = argv[2];
		} else
			filename = argv[1];
		instance = new Lexer(filename);
	} catch (...) {
		return (false);
	}
	return (true);
}

Lexer *Lexer::getInstance() {
	return instance;
}

TokenType Lexer::getNextToken() const {
	return nextToken;
}

std::string Lexer::getTokenStr() const {
	return tokenStr;
}

void Lexer::lexical() {
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
		ctxMan->increaseLeftParenNum();
	} else if (nowChar == ')') {
		nextToken = TokenType::RIGHT_PAREN;
		if (!ctxMan->decreaseLeftParenNum())
			nextToken = TokenType::UNDEFINED;
	} else if (nowChar == ';')
		nextToken = TokenType::SEMI_COLON;
	else if (nowChar == ':' && now + 1 < totalStr.length() && totalStr[now + 1] == '=') {
		nextToken = TokenType::ASSIGN_OP;
		if (!ctxMan->increaseAssignmentNum())
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
				ctxMan->pushWarning(6, totalStr.substr(now, j));
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
				ctxMan->pushWarning(7, totalStr.substr(now, j));
			now += j - 1;
		} else {
			nextToken = TokenType::UNDEFINED;
			ctxMan->pushWarning(4, std::string(1, nowChar));
		}
	}
	now++;

	if (nextToken == TokenType::UNDEFINED)
		this->lexical();
}

void Lexer::printTokenStr(const std::string &str) {
	if (Lexer::vOption) {
		std::cout << TokenTypeToString(nextToken) << '\n';
		return;
	}
	if (str.empty()) {
		if (nextToken == TokenType::SEMI_COLON || nextToken == TokenType::END_OF_FILE)
			std::cout << "\b;\n";
		else
			std::cout << tokenStr << " ";
	} else {
		std::cout << str << " ";
	}
}

bool Lexer::isMetaChar(char c) {
	return (!(c == '+' || c == '-' || c == '*' || c == '/' ||
			  c == '(' || c == ')' || c == ';' || c == ' '));
}

std::string Lexer::TokenTypeToString(TokenType type) {
	switch (type) {
		case TokenType::CONST:
			return "CONST";
		case TokenType::IDENT:
			return "IDENT";
		case TokenType::ASSIGN_OP:
			return "ASSIGN_OP";
		case TokenType::ADD_OP:
			return "ADD_OP";
		case TokenType::MULT_OP:
			return "MULT_OP";
		case TokenType::LEFT_PAREN:
			return "LEFT_PAREN";
		case TokenType::RIGHT_PAREN:
			return "RIGHT_PAREN";
		case TokenType::SEMI_COLON:
			return "SEMI_COLON";
		case TokenType::UNDEFINED:
			return "UNDEFINED";
		case TokenType::END_OF_FILE:
			return "END_OF_FILE";
		default:
			return "UNDEFINED";
	}
}