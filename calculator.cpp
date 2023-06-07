#include "calculator.h"

Calculator::Calculator() = default;

// организуем работу калькулятора через приватные методы класса
int Calculator::calculate(const std::string& expression) {
    std::string postfix_exp = infix_to_postfix(expression);

    // std::cout << "Postfix expression:" << std::endl << postfix_exp << std::endl;
    int result = get_answer(postfix_exp);
    // std::cout << "Result:" << std::endl << result << std::endl;
    return result;
}

// перевод выражения в постфиксную форму
std::string Calculator::infix_to_postfix(const std::string& expression) {
    std::string postfix_exp;       // переменная для итогового постфиксного выражения
    Stack<char> operators;         // стек операторов
    LinkedList<std::string> queue; // очередь для формирования постфиксной записи

    std::string cur_digit;         // текущее число
    bool need_operator = false;    // флаг необходимости оператора (нужен для отлова ошибок)
    for (char i : expression) {
        // если встретили цифру -> формируем число,
        // но если мы начинаем формировать новое число и у нас стоит флаг необходимости оператора,
        // то это значит что мы встретили 2 числа не разделённые оператором -> ошибка
        if (std::isdigit(i)) {
            if (cur_digit.empty() && need_operator) {
                throw std::invalid_argument("Error. Wrong expression.");
            }
            cur_digit.push_back(i);
        // если встретили пробел -> сохраняем сформированное число
        } else if (i == ' ') {
            if (!cur_digit.empty()) {
                queue.push_back(cur_digit);
                cur_digit.clear();
                need_operator = true;
            }
        // если встретили ( -> добавляем в стек операторов
        } else if (i == '(') {
            operators.push(i);
        // если встретили ) -> добавляем в выходную очередь операторы до (
        } else if (i == ')') {
            if (!cur_digit.empty()) {
                queue.push_back(cur_digit);
                cur_digit.clear();
            }

            while (operators.size() != 0 && operators.top() != '(') {
                std::string a;
                queue.push_back(a + operators.pop());
            }
            if (operators.size() != 0 && operators.top() == '(') {
                operators.pop();
            } else if (operators.size() == 0) {
                throw std::invalid_argument("Error. Wrong expression.");
            }
        // если встретили оператор (+, -, *, /) -> достаём из стека операторы с большим приоритетом
        } else if (is_operator(i)) {
            if (!cur_digit.empty()) {
                queue.push_back(cur_digit);
                cur_digit.clear();
            }
            while (operators.size() != 0 && get_priority(i) <= get_priority(operators.top())) {
                std::string a;
                queue.push_back(a + operators.pop());
            }
            operators.push(i);
            need_operator = false;
        // если встретили что-то не желаемое -> выбрасываем ошибку
        } else {
            throw std::invalid_argument("Error. Strange symbol in expression.");
        }
    }
    // добавляем в очередь последнее число
    if (!cur_digit.empty()) {
        queue.push_back(cur_digit);
        cur_digit.clear();
    }

    // достаём из стека оставшиеся операторы
    while (operators.size() != 0 && operators.top() != '(') {
        std::string a;
        queue.push_back(a + operators.pop());
    }

    // если в стеке осталась ( -> значит в выражении была неправильная скобочная последовательность
    if (operators.size() > 0) {
        throw std::invalid_argument("Error. Wrong expression.");
    }

    // строим получившееся постфиксное выражение в строке
    while (queue.get_size() > 0) {
        postfix_exp += queue[0] + " ";
        queue.pop_front();
    }

    return postfix_exp;
}

bool Calculator::is_operator(char symbol) {
    return symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/';
}

int Calculator::get_priority(char op) {
    if (op == '+' || op == '-') {
        return 1;
    } else if (op == '*' || op == '/') {
        return 2;
    }
    return 0;
}

// вычисление ответа из постфиксной формы
int Calculator::get_answer(const std::string& expression) {
    std::string current_digit;

    for (auto symbol: expression) {
        if (isdigit(symbol)) {
            current_digit.push_back(symbol);
        } else if (symbol == '+' || symbol == '-' || symbol == '*' || symbol == '/') {
            if (this->stack.size() < 2) {
                this->stack.clear();
                throw std::invalid_argument("Error. Wrong expression.");
            }

            int second = this->stack.pop();
            int first = this->stack.pop();

            switch (symbol) {
                case '+':
                    stack.push(first + second);
                    break;
                case '-':
                    stack.push(first - second);
                    break;
                case '*':
                    stack.push(first * second);
                    break;
                default:
                    if (second == 0) {
                        this->stack.clear();
                        throw std::invalid_argument("Division by zero :)");
                    }
                    stack.push(first / second);
                    break;
            }
        } else if (symbol == ' ') {
            if (!current_digit.empty()) {
                this->stack.push(std::stoi(current_digit));
                current_digit.clear();
            }
        } else {
            this->stack.clear();
            throw std::invalid_argument("Error. Wrong expression.");
        }
    }

    if (!current_digit.empty()) {
        this->stack.push(std::stoi(current_digit));
        current_digit.clear();
    }

    if (stack.size() > 1) {
        this->stack.clear();
        throw std::invalid_argument("Error. Wrong expression.");
    }
    if (stack.size() == 0) {
        throw std::invalid_argument("Error. Wrong expression.");
    }
    return this->stack.pop();
}

Calculator::~Calculator() = default;