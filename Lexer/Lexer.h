//
// Created by liamc on 11/28/2023.
//

#pragma once

#include <string>

enum TokenType {
    NUMBER,
    PLUS,
    END,
    IDENTIFIER,
    OPEN_PAREN,
    CLOSE_PAREN,
    COMMA,
    FUNC_DEF
};

struct Token {
    TokenType type;
    std::string value;
};

class Lexer {
public:
    explicit Lexer(std::string input);

    Token getNextToken();

private:
    std::string input;
    size_t pos;
};
