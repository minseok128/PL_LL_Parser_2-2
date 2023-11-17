#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

# include <unordered_map>
# include <string>
# include <iostream>
# include "Var.h"

class SymbolTable {
private:
	static SymbolTable *instance;
	std::unordered_map<std::string, Var> table;

	SymbolTable();

public:
	SymbolTable(const SymbolTable &) = delete;

	SymbolTable &operator=(const SymbolTable &) = delete;

	static SymbolTable *getInstance();

	void insert(const std::string &name, const Var &v);

	Var find(const std::string &name);

	void print_all(bool vOption);
};

#endif // SYMBOLTABLE_H
