#ifndef SYMBOLTABLE_H
#define SYMBOLTABLE_H

#include <unordered_map>
#include <string>
#include "Value.h"

class SymbolTable {
private:
    static SymbolTable *instance;
    std::unordered_map<std::string, Value> table;

    SymbolTable(); // Private constructor for singleton

public:
    // Delete copy constructor and assignment operator
    SymbolTable(const SymbolTable &) = delete;

    SymbolTable &operator=(const SymbolTable &) = delete;

    static SymbolTable *getInstance();

    void insert(const std::string &name, const Value &v);

    Value find(const std::string &name);

    void print_all();
};

#endif // SYMBOLTABLE_H
