#include "stack.h"
#include <iostream>

stack::~stack() = default;

void stack::push(position num) {

    auto new_node = new Node();
    new_node->m_data = num;
    new_node->m_next = m_top;
    m_top = new_node;
}

position stack::peek() {
    if (m_top != nullptr)
        //return the top of the stack to be used for marking the solution for the maze
        return m_top->m_data;
    return {-1, -1};
}

void stack::pop() {
    if (m_top != nullptr) {
        //delete the top node off the stack, used to backtrack from dead ends
        //and also in tandem with peek to mark the solution for the maze
        auto node = m_top;
        m_top = m_top->m_next;
        delete node;
    } else {
        std::cout << "There are no more nodes to remove..." << std::endl;
    }
}