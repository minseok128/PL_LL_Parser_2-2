#include "SymbolTable.h"
#include <iostream>

SymbolTable *SymbolTable::instance = nullptr;

SymbolTable::SymbolTable() = default;

SymbolTable *SymbolTable::getInstance() {
    if (instance == nullptr) {
        instance = new SymbolTable();
    }
    return instance;
}

void SymbolTable::insert(const std::string &name, const Value &v) {
    if (!name.empty()) {
        table[name] = v;
    }
}

Value SymbolTable::find(const std::string &name) {
    auto it = table.find(name);
    if (it == table.end()) {
        table[name] = Value();
        return table[name];
    }
    return it->second;
}

void SymbolTable::print_all() {
    std::cout << "Result ==> ";
    for (const auto &pair: table) {
        std::cout << pair.first << ": ";
        if (pair.second.getIsInitialized()) {
            std::cout << pair.second.getValue();
        } else {
            std::cout << "Unknown";
        }
        std::cout << "; ";
    }
    std::cout << std::endl;
}
