//
// Created by liamc on 11/28/2023.
//

#pragma once

#include "../Lexer/Lexer.h"
#include "../FunctionRegistry/FunctionRegistry.h"

class Parser {
public:
    explicit Parser(Lexer& lexer);

    int parse();

private:
    Lexer& lexer;
    FunctionRegistry functionRegistry;

    static int parseNumber(Token& token);
    int parseFunctionCall(Token& token) const;
    int parseFunctionDef(Token& token);
};
