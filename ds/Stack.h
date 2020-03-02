#ifndef STACK_H
#define STACK_H

#include <iostream>
using namespace std;

template <typename T>
class Stack
{
    struct Node
    {
        Node(T _value, Node* _next_ptr = nullptr)
            : m_value(move(_value)),
              m_next_ptr(_next_ptr) {}

        T m_value;
        Node* m_next_ptr;
    };

public:
    Stack() : m_size(0) {}

    void push(T _value)
    {
        Node* new_node_ptr = new Node(_value);
        new_node_ptr->m_next_ptr = m_first_ptr;
        m_first_ptr = new_node_ptr;

        ++m_size;
    }

    T pop()
    {
        if (m_size)
        {
            T value = m_first_ptr->m_value;

            Node* tmp_node_ptr = m_first_ptr->m_next_ptr;

            delete m_first_ptr;
            m_first_ptr = tmp_node_ptr;

            --m_size;
            return value;
        } else
        {
            // size == 0
            throw out_of_range("stack size == 0");
        }
    }

    size_t size()
    {
        return m_size;
    }

    ~Stack()
    {
        Node* current_node_ptr = m_first_ptr;
        while (current_node_ptr)
        {
            Node* tmp_ptr = current_node_ptr->m_next_ptr;
            delete current_node_ptr;
            current_node_ptr = tmp_ptr;
        }
    }

private:
    size_t m_size;
    Node*  m_first_ptr {nullptr};
};

#endif // STACK_H
