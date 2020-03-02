#ifndef QUEUE_H
#define QUEUE_H

#include <iostream>

using namespace std;

template <typename T>
class Queue
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
    Queue() : m_size(0) {}

    void enqueue(T _value)
    {
        if (!m_size)
        {
            m_first_ptr = new Node(_value);
            m_last_ptr = m_first_ptr;
        } else
        {
            Node* new_node_ptr = new Node(_value);
            m_last_ptr->m_next_ptr = new_node_ptr;
            m_last_ptr = new_node_ptr;
        }
        ++m_size;
    }

    T dequeue()
    {
        if (m_size)
        {
            T value = m_first_ptr->m_value;
            Node* next_node_ptr = m_first_ptr->m_next_ptr;

            if (m_last_ptr == m_first_ptr)
            {
                m_last_ptr = nullptr;
            }

            delete m_first_ptr;
            m_first_ptr = next_node_ptr;

            --m_size;

            return value;

        } else
        {
            // size == 0
            throw out_of_range("queue size == 0");
        }
    }

    size_t size()
    {
        return m_size;
    }

    void print()
    {
        Node* current_node_ptr = m_first_ptr;
        while (current_node_ptr)
        {
            cout << current_node_ptr->m_value << " ";
            current_node_ptr = current_node_ptr->m_next_ptr;
        }
    }

    ~Queue()
    {
        Node* current_node = m_first_ptr;
        while (current_node)
        {
            Node* tmp_ptr = current_node->m_next_ptr;
            delete current_node;
            current_node = tmp_ptr;
        }
    }

private:
    size_t m_size;
    Node* m_first_ptr {nullptr};
    Node* m_last_ptr  {nullptr};
};

#endif // QUEUE_H
