#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include "Queue.h"

template <typename T, typename P>
class PriorityQueue
{
    struct Node
    {
        Node() = default;
        ~Node() = default;

        Queue<T> m_queue;
        P m_priority;
        Node* m_next_ptr {nullptr};
    };

public:
    PriorityQueue() = default;

    void enqueue(T _value, P _priority)
    {
        Node* prev_ptr = nullptr;
        Node* current_ptr = m_first;

        while (current_ptr && _priority < current_ptr->m_priority)
        {
            prev_ptr = current_ptr;
            current_ptr = current_ptr->m_next_ptr;
        }

        if (current_ptr)
        {
            if  (current_ptr->m_priority < _priority)
            {
                // _priority biggest than the current priority
                Node* new_node_ptr = new Node();
                new_node_ptr->m_priority = _priority;
                new_node_ptr->m_queue.enqueue(_value);
                new_node_ptr->m_next_ptr = current_ptr;

                if (prev_ptr)
                {
                    prev_ptr->m_next_ptr = new_node_ptr;
                    new_node_ptr->m_next_ptr = current_ptr;
                }

                if (current_ptr == m_first)
                {
                    // new top proirity element added
                    m_first = new_node_ptr;
                }
            } else
            {
                // _priority equal to the current priority
                current_ptr->m_queue.enqueue(_value);
            }
        } else
        {
            // current element == nullptr
            Node* new_node_ptr = new Node();
            new_node_ptr->m_priority = _priority;
            new_node_ptr->m_queue.enqueue(_value);

            if (prev_ptr)
            {
                // new last element added
                prev_ptr->m_next_ptr = new_node_ptr;
            } else
            {
                // first element created
                m_first = new_node_ptr;
            }
        }

        ++m_size;
    }

    T dequeue()
    {
        if (m_size)
        {
            T value = m_first->m_queue.dequeue();

            if (!m_first->m_queue.size())
            {
                Node* tmp_node_ptr = m_first->m_next_ptr;
                delete m_first;
                m_first = tmp_node_ptr;
            }

            --m_size;

            return value;
        } else
        {
            throw out_of_range("PriorityQueue size == 0");
        }
    }

    size_t size()
    {
        return m_size;
    }

    void print()
    {
        Node* current_node_ptr = m_first;
        while (current_node_ptr)
        {
            cout << "proirity = " << current_node_ptr->m_priority << ": ";
            current_node_ptr->m_queue.print(); cout << endl;
            current_node_ptr = current_node_ptr->m_next_ptr;
        }
    }

    ~PriorityQueue()
    {
        Node* current_ptr = m_first;
        while (current_ptr)
        {
            Node* tmp_next_node = current_ptr->m_next_ptr;
            delete current_ptr;
            current_ptr = tmp_next_node;
        }
    }

private:
    size_t m_size {0};
    Node* m_first {nullptr};
};

#endif // PRIORITYQUEUE_H
