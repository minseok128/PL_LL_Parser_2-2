cmake_minimum_required(VERSION 3.25.2)
project(CPP_Parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(CPP_Parser src/main.cpp
        src/ContextManager.cpp src/ContextManager.h
        src/Lexer.cpp src/Lexer.h
        src/Var.cpp src/Var.h
        src/SymbolTable.cpp src/SymbolTable.h
        src/Parser.cpp src/Parser.h
        src/TokenType.h src/main.cpp)
