//
// Created by liamc on 11/28/2023.
//

#include "Parser.h"

#include <iostream>

#include "../Lexer/Lexer.h"
#include "../FunctionRegistry/FunctionRegistry.h"

Parser::Parser(Lexer& lexer) : lexer(lexer), functionRegistry() {}

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
            result += parseFunctionDef(token);
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

int Parser::parseFunctionDef(Token& token) {
    if (token.type != FUNC_DEF) {
        return 0;
    }
    token = lexer.getNextToken();
    if (token.type != IDENTIFIER) {
        return 0;
    }
    const std::string funcName = token.value;  // Set the function name
    token = lexer.getNextToken();
    if (token.type != OPEN_PAREN) {
        // Handle error: expected '('
        std::cerr << "Error: expected '('.\n";
        return 0;
    }
    while (token.type != CLOSE_PAREN && token.type != END) {
        token = lexer.getNextToken();
        if (token.type == IDENTIFIER) {
            std::cout << token.value << "\n";
        }
    }
    if (token.type != CLOSE_PAREN) {
        // Handle error: expected ')'
        std::cerr << "Error: expected '('.\n";
        return 0;
    }
    functionRegistry.addFunction(funcName, funcName + "(param1){return param1*param1;}");
    std::cout << "Added function " << funcName << "\n";

    return 0;
}


int Parser::parseFunctionCall(Token& token) const {
    if (token.type != IDENTIFIER) {
        // Handle other function calls here if needed
        std::cout << token.type << " " << token.value << ": is the type and value received instead of valid type.\n";
        return 0;
    }

    const std::string functionName = token.value;
    const std::string functionDefinition = functionRegistry.getFunctionDefinition(functionName);

    if (functionDefinition.empty()) {
        std::cerr << "Error: Function not found.\n";
        return 0;
    }

    // Parse parameters
    std::vector<int> params;
    token = lexer.getNextToken();
    if (token.type != OPEN_PAREN) {
        // Handle error: expected '('
        std::cerr << "Error: expected '('.\n";
        return 0;
    }

    // Parsing parameters
    while (token.type != CLOSE_PAREN) {
        if (token.type != COMMA) {
            params.push_back(parseNumber(token));
        }
        token = lexer.getNextToken();
    }

    // Check if the number of parameters matches the function definition
    // For simplicity, assuming that the function takes the same number of parameters as specified in its definition.
    const size_t expectedParams = std::count(functionDefinition.begin(), functionDefinition.end(), ',') + 1;

    if (params.size() != expectedParams) {
        std::cerr << "Error: Incorrect number of parameters for function " << functionName << ".\n";
        return 0;
    }

    token = lexer.getNextToken();
    if (token.type != CLOSE_PAREN) {
        // Handle error: expected ')'
        std::cerr << "Error: expected ')'.\n";
        return 0;
    }

    // Execute the function based on its definition
    // For simplicity, assuming that the function definition is a valid C++ expression.
    // You might need to enhance this based on your requirements.
    const int return_res = 1; // Use the appropriate data type based on your function's return type
    // Execute the function here using functionDefinition and params

    return return_res;
}
