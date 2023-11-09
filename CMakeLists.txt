cmake_minimum_required(VERSION 3.26)
project(CPP_Parser)

set(CMAKE_CXX_STANDARD 14)

add_executable(CPP_Parser main.cpp
        InformationManager.cpp
        InformationManager.h
        LexicalAnalyzer.cpp
        LexicalAnalyzer.h
        Value.cpp
        Value.h
)
