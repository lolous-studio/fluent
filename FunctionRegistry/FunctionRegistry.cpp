//
// Created by liamc on 11/28/2023.
//

#include "FunctionRegistry.h"

void FunctionRegistry::addFunction(const std::string& functionName, const std::string& definition) {
    functionDefinitions[functionName] = definition;
}

std::string FunctionRegistry::getFunctionDefinition(const std::string& functionName) const {
    auto it = functionDefinitions.find(functionName);
    if (it != functionDefinitions.end()) {
        return it->second;
    }
    return ""; // Function not found
}
