#include <iostream>
#include "calculator.h"

void print_help() {
    std::cout << "Input expression to calculate"    << std::endl <<
                 "Input 'exit' to quit the program" << std::endl;
}

int main() {
    Calculator calculator;
    std::string expression;

    print_help();
    std::getline(std::cin, expression);
    while (expression != "exit") {
        try {
            std::cout << expression << " = " << calculator.calculate(expression) << std::endl;
        } catch (std::invalid_argument &ex) {
            std::cout << ex.what() << std::endl;
        }
        std::getline(std::cin, expression);
    }
}
