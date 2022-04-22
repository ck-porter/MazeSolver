#ifndef ASSIGNMENT_2_STACK_H
#define ASSIGNMENT_2_STACK_H

#include "position.h"
#include <iostream>

class Node {
public:
    position m_data{-1, -1};
    Node *m_next{nullptr};
};

class stack {
private:
    Node *m_top{nullptr};

public:
    stack() = default;

    virtual ~stack();

    void push(position num);

    position peek();

    void pop();
};

std::ostream &operator<<(std::ostream &output, stack &stack);

#endif //ASSIGNMENT_2_STACK_H
