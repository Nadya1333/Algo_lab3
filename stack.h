#ifndef BI_ALGO_LAB2_STACK_H
#define BI_ALGO_LAB2_STACK_H
#include "linked_list.h"


template <typename T>
class Stack {
public:
    Stack() = default;
    ~Stack() = default;

    void push(T value) {
        this->stack.push_front(value);
    }

    T pop() {
        T popped = this->top();
        this->stack.pop_front();
        return popped;
    }

    T top() {
        return this->stack[0];
    }

    size_t size() {
        return this->stack.get_size();
    }

    void clear() {
        this->stack.clear();
    }


private:
    LinkedList<T> stack;
};

#endif //BI_ALGO_LAB2_STACK_H
