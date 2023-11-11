cmake_minimum_required(VERSION 3.25.2)
project(CPP_Parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_Parser src/main.cpp
        src/InformationManager.cpp src/InformationManager.h
        src/LexicalAnalyzer.cpp src/LexicalAnalyzer.h
        src/Value.cpp src/Value.h
        src/SymbolTable.cpp src/SymbolTable.h
        src/Parser.cpp src/Parser.h
        )
