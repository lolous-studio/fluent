//
// Created by liamc on 11/28/2023.
//

// FunctionDefinitions.h
#ifndef FUNCTION_DEFINITIONS_H
#define FUNCTION_DEFINITIONS_H

#include <string>
#include <unordered_map>

class FunctionRegistry {
public:
    void addFunction(const std::string& functionName, const std::string& definition);
    std::string getFunctionDefinition(const std::string& functionName) const;

private:
    std::unordered_map<std::string, std::string> functionDefinitions;
};

#endif // FUNCTION_DEFINITIONS_H
