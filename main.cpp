//
// Created by liamc on 11/28/2023.
//

#include <iostream>

#include "Parser/Parser.h"
#include "Lexer/Lexer.h"

int main() {
    const std::string input = "func multiply(a, b){ return a * b };= 1 + multiply(2, 3);";
    Lexer lexer(input);
    Parser parser(lexer);

    const int result = parser.parse();

    std::cout << "Result: " << result << std::endl;

    return 0;
}
