//
// Created by liamc on 11/28/2023.
//

#include "Parser.h"

#include <iostream>

#include "../Lexer/Lexer.h"
#include "../FunctionRegistry/FunctionRegistry.h"

Parser::Parser(Lexer& lexer) : lexer(lexer) {}

int Parser::parse() {
    Token token = lexer.getNextToken();
    int result = 0;

    while (token.type != END) {
        if (token.type == PLUS) {
            token = lexer.getNextToken();
            result += parseNumber(token);
        } else if (token.type == NUMBER) {
            result += std::stoi(token.value);
            token = lexer.getNextToken();
        } else {
            // Handle other cases, like function calls
            result += parseFunctionCall(token);
            token = lexer.getNextToken();
        }

        // Skip semicolons
        //while (token.type == END) {
        //    token = lexer.getNextToken();
        //}
    }

    return result;
}


int Parser::parseNumber(Token& token) {
    if (token.type == NUMBER) {
        return std::stoi(token.value);
    } else {
        return 0;
    }
}

int Parser::parseFunctionDef(Token& token) const {
    if (token.type != FUNC_DEF) {
        return 0;
    }

    token = lexer.getNextToken();
    if (token.type != IDENTIFIER) {
        return 0;
    }
    token = lexer.getNextToken();
    if (token.type != OPEN_PAREN) {
        // Handle error: expected '('
        std::cerr << "Error: expected '('.";
        return 0;
    }
    while (token.type != CLOSE_PAREN || token.type != END) {
        token = lexer.getNextToken();
        if (token.type == IDENTIFIER) {
            std::cout << token.value;
        }
    }
    if (token.type != CLOSE_PAREN) {
        // Handle error: expected ')'
        std::cerr << "Error: expected '('.";
        return 0;
    }
    addFunctionDefinition();


    return 0;
}

int Parser::parseFunctionCall(Token& token) const {
    // Assuming the token is the start of a function call
    // For simplicity, let's assume it's the "multiply" function

    if (token.type != IDENTIFIER || token.value != "multiply") {
        // Handle other function calls here if needed
        return 0;
    }

    // Parse parameters
    token = lexer.getNextToken();
    if (token.type != OPEN_PAREN) {
        // Handle error: expected '('
        std::cerr << "Error: expected '('...";
        return 0;
    }

    token = lexer.getNextToken();
    const int param1 = parseNumber(token);

    token = lexer.getNextToken();
    if (token.type != COMMA) {
        // Handle error: expected ','
        std::cerr << "Error: expected ','...";
        return 0;
    }

    token = lexer.getNextToken();
    const int param2 = parseNumber(token);

    // Assuming the function only takes two parameters for simplicity

    token = lexer.getNextToken();
    if (token.type != CLOSE_PAREN) {
        // Handle error: expected ')'
        std::cerr << "Error: expected ')'...";
        return 0;
    }

    return param1 * param2;
}
