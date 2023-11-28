//
// Created by liamc on 11/28/2023.
//

#include "Lexer.h"
#include <cctype>
#include <sstream>

Lexer::Lexer(std::string input) : input(std::move(input)), pos(0) {}

Token Lexer::getNextToken() {
    while (pos < input.size() && isspace(input[pos])) {
        pos++;
    }

    if (pos == input.size()) {
        return {END, ""};
    }

    const char currentChar = input[pos];

    if (isdigit(currentChar)) {
        std::string value;
        while (pos < input.size() && isdigit(input[pos])) {
            value += input[pos];
            pos++;
        }
        return {NUMBER, value};
    }

    if (currentChar == '+') {
        pos++;
        return {PLUS, ""};
    }

    if (isalpha(currentChar)) {
        std::string value;
        while (pos < input.size() && isalpha(input[pos])) {
            value += input[pos];
            pos++;
        }
        if (value == "func") {
            return {FUNC_DEF, ""};
        }
        return {IDENTIFIER, value};
    }

    if (currentChar == '(') {
        pos++;
        return {OPEN_PAREN, ""};
    }

    if (currentChar == ')') {
        pos++;
        return {CLOSE_PAREN, ""};
    }

    if (currentChar == ',') {
        pos++;
        return {COMMA, ""};
    }

    if (currentChar == ';') {
        pos++;
        // Don't return {END, ""} for semicolons
        return getNextToken();
    }

    return {END, ""};
}
