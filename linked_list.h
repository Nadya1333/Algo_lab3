#ifndef BI_ALGO_LAB2_LINKED_LIST_H
#define BI_ALGO_LAB2_LINKED_LIST_H
#include <iostream>

template <typename T>
class LinkedList {
public:
    LinkedList() {
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    void print() {
        if (this->head != nullptr) {
            Node *cur = head;
            while (cur != nullptr) {
                std::cout << cur->value << ' ';
                cur = cur->next;
            }
            std::cout << std::endl;
        } else {
            std::cout << "Nothing to print. List is empty!" << std::endl;
        }
    }

    // add element in the end
    void push_back(T value) {
        if (head == nullptr) {
            this->head = new Node(value, nullptr);
            this->tail = head;
        } else {
            this->tail->next = new Node(value, nullptr);
            tail = tail->next;
        }
        this->size++;
    }

    // add element in the beginning
    void push_front(T value) {
        Node *newHead = new Node(value, this->head);
        if (this->head == nullptr) {
            this->tail = newHead;
        }
        this->head = newHead;
        this->size++;
    }

    // add element by index
    void push_index(int index, T value) {
        if (index < 0 || index > this->size) {
            std::cout << "Given index out of list borders" << std::endl;
        } else if (index == 0) {
            push_front(value);
        } else if (index == size) {
            push_back(value);
        } else {
            Node *cur = head;
            int cur_index = 0;
            while (cur_index + 1 != index) {
                cur = cur->next;
                cur_index++;
            }
            cur->next = new Node(value, cur->next);
            this->size++;
        }
    }

    // delete element from the end
    void pop_back() {
        if (head != nullptr) {
            Node *cur = head, *prev = nullptr;
            while (cur->next != nullptr) {
                prev = cur;
                cur = cur->next;
            }
            tail = prev;
            this->size--;
            if (tail != nullptr) {
                tail->next = nullptr;
            }
            delete cur;
            if (this->size == 0) {
                head = nullptr;
            }
        } else {
            std::cout << "Nothing to pop. List is empty!" << std::endl;
        }
    }

    // delete element from the beginning
    void pop_front() {
        if (head != nullptr) {
            Node *cur = head;
            this->head = head->next;
            this->size--;

            cur->next = nullptr;
            delete cur;
        } else {
            std::cout << "Nothing to pop. List is empty!" << std::endl;
        }
    }

    // delete all elements with given value
    void pop_value(T value) {
        if (this->head != nullptr) {
            Node *cur = head, *prev = nullptr;
            while (cur != nullptr) {
                if (cur->value == value) {
                    if (prev != nullptr) {
                        prev->next = cur->next;
                        cur->next = nullptr;
                        delete cur;
                        cur = prev->next;
                    } else {
                        this->head = cur->next;
                        cur->next = nullptr;
                        delete cur;
                        cur = head;
                    }
                    this->size--;
                } else {
                    prev = cur;
                    cur = cur->next;
                }
            }
            this->tail = prev;
        } else {
            std::cout << "Nothing to pop. List is empty!" << std::endl;
        }
    }

    // delete element by index
    void pop_index(int index) {
        if (head == nullptr) {
            std::cout << "Nothing to pop. List is empty!" << std::endl;
        } else if (index < 0 || index >= this->size) {
            std::cout << "Given index out of list borders" << std::endl;
        } else if (index == 0) {
            pop_front();
        } else {
            Node *cur = head;
            int cur_index = 0;
            while (cur_index + 1 != index) {
                cur = cur->next;
                cur_index++;
            }
            Node *deleted = cur->next;
            cur->next = deleted->next;

            deleted->next = nullptr;
            delete deleted;

            if (cur_index == this->size - 2) {
                this->tail = cur;
            }
            this->size--;
        }
    }

    // returns first position of element, -1 if not found
    int find_value(T value) {
        int cur_index = 0;
        Node *cur = head;
        while (cur != nullptr) {
            if (cur->value == value) {
                return cur_index;
            } else {
                cur = cur->next;
                cur_index++;
            }
        }
        return -1;
    }

    // returns true if element at index == value, else returns false
    T find_at_index(int index) {
        if (index < 0 || index >= this->size) {
            std::cout << "Given index out of list borders!" << std::endl;
            exit(1);
        } else {
            int cur_ind = 0;
            Node *cur = head;
            while (cur_ind != index) {
                cur_ind++;
                cur = cur->next;
            }
            return cur->value;
        }
    }

    // delete all elements from the list
    void clear() {
        delete head;
        this->head = nullptr;
        this->tail = nullptr;
        this->size = 0;
    }

    // list destructor
    ~LinkedList() {
        delete head;
    }

    T operator[](int index) {
        return find_at_index(index);
    }

    size_t get_size() {
        return this->size;
    }

private:
    struct Node {
        T value;  // value of element
        Node *next; // pointer to next element

        Node() {
            this->value = 0;
            this->next = nullptr;
        }

        // node arguments constructor
        Node(T value, Node* next) {
            this->value = value;
            this->next = next;
        }

        // node destructor
        ~Node() {
            delete next;
        }
    };

    Node *head;     // pointer to head of list
    Node *tail;     // pointer to end of list
    size_t size{};    // length of list
};



#endif //BI_ALGO_LAB2_LINKED_LIST_H
