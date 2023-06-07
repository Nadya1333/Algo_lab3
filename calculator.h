#ifndef BI_ALGO_LAB2_POSTFIX_CALC_H
#define BI_ALGO_LAB2_POSTFIX_CALC_H
#include "stack.h"

class Calculator {
public:
    Calculator();
    int calculate(const std::string& expression);
    ~Calculator();

private:
    Stack<int> stack;

    static std::string infix_to_postfix(const std::string&);
    int get_answer(const std::string& expression);
    static int get_priority(char op);
    static bool is_operator(char symbol);
};

#endif //BI_ALGO_LAB2_POSTFIX_CALC_H
