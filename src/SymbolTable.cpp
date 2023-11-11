#include "SymbolTable.h"

SymbolTable *SymbolTable::instance = nullptr;

SymbolTable::SymbolTable() = default;

SymbolTable *SymbolTable::getInstance() {
    if (instance == nullptr) {
        instance = new SymbolTable();
    }
    return instance;
}

void SymbolTable::insert(const std::string &name, const Var &v) {
    if (!name.empty()) {
        table[name] = v;
    }
}

Var SymbolTable::find(const std::string &name) {
    auto it = table.find(name);
    if (it == table.end()) {
        table[name] = Var();
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
    std::cout << '\n';
}
