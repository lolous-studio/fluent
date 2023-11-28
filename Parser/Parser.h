//
// Created by liamc on 11/28/2023.
//

#pragma once

#include "Lexer.h"

class Parser {
public:
    explicit Parser(Lexer& lexer);

    int parse();

private:
    Lexer& lexer;

    static int parseNumber(Token& token);
    int parseFunctionCall(Token& token) const;
    int parseFunctionDef(Token& token) const;
};
