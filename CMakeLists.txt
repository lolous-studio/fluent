cmake_minimum_required(VERSION 3.27)
project(fluent)

set(CMAKE_CXX_STANDARD 23)

add_executable(fluent main.cpp
        Lexer/Lexer.h
        Lexer/Lexer.cpp
        Parser/Parser.h
        Parser/Parser.cpp
        FunctionRegistry/FunctionRegistry.cpp
        FunctionRegistry/FunctionRegistry.h)
