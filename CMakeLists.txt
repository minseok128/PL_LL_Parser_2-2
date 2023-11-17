cmake_minimum_required(VERSION 3.25.2)
project(CPP_Parser)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_custom_target(CPP_Parser COMMAND make -C ${CMAKE_SOURCE_DIR} CLION_EXE_DIR=${PROJECT_BINARY_DIR})
