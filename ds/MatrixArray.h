#ifndef MATRIXARRAY_H
#define MATRIXARRAY_H

#include <iostream>
#include <memory>

using namespace std;

#include "IArray.h"

template <typename T>
class MatrixArray : public IArray<T>
{
public:
    template <typename K>
    class iterator
    {
    public:
        iterator(K* _data_ptr, size_t _index, size_t _capacity)
                : m_ptr(_data_ptr), m_index(_index), m_capacity(_capacity) {}

        bool operator==(iterator& _i) const { return m_ptr == _i.m_ptr; }
        bool operator!=(iterator& _i) const { return !(*this == _i); }

        K& operator*() { return *m_ptr[m_index / m_capacity][m_index % m_capacity]; }

        void operator++()
        {
            ++m_index;
        }

        void operator--()
        {
            --m_index;
        }

    private:
        size_t m_index    {0};
        size_t m_capacity {0};
        K** m_ptr         {nullptr};
    };

    MatrixArray(size_t _capacity) : m_capacity(_capacity), m_full_capacity(_capacity)
    {
        m_data_ptr    = new T*[1];
        m_data_ptr[0] = new T [_capacity];
    }

    void add(const T value)
    {
        if (m_size == m_full_capacity)
        {
            size_t new_data_size = (m_full_capacity / m_capacity) + 1;
            T** tmp_data_ptr = new T*[new_data_size];
            memcpy(tmp_data_ptr, m_data_ptr, new_data_size * sizeof (T*));
            tmp_data_ptr[new_data_size - 1] = new T[m_capacity];
            delete [] m_data_ptr;
            m_data_ptr = tmp_data_ptr;
            m_full_capacity += m_capacity;
        }
        m_data_ptr [m_size / m_capacity]
                   [m_size % m_capacity] = std::move(value);
        ++m_size;
    }

    iterator<T> begin()
    {
        return iterator<T>(m_data_ptr, 0, m_capacity);
    }

    iterator<T> end()
    {
        return iterator<T>(m_data_ptr, m_size, m_capacity);
    }

    T& operator[](size_t _index)
    {
        return m_data_ptr [_index / m_capacity]
                          [_index % m_capacity];
    }

    T get(size_t _index) const
    {
        return m_data_ptr [_index / m_capacity]
                          [_index % m_capacity];
    }

    void remove(size_t _index)
    {
        size_t array_index = _index / m_capacity;
        size_t value_index = _index % m_capacity;
        size_t bytes = (m_capacity - value_index) * sizeof (T);
        memcpy(m_data_ptr[array_index] + value_index, m_data_ptr[array_index] + value_index + 1, bytes);

        size_t last_index = (m_size - 1) / m_capacity;
        if (last_index > array_index)
        {
            for (size_t ix = array_index + 1; ix <= last_index; ++ix)
            {
                m_data_ptr[ix - 1][m_capacity - 1] = m_data_ptr[ix][0];
                memcpy(m_data_ptr[ix], m_data_ptr[ix] + 1, (m_capacity - 1) * sizeof (T));
            }
        }

        --m_size;

        size_t new_last_index = (m_size - 1) / m_capacity;
        if (new_last_index < last_index)
        {
            // last array in matrix now empty
            // and should be removed

            T** new_data_ptr = new T*[last_index];
            memcpy(new_data_ptr, m_data_ptr, last_index * sizeof (T*));

            delete [] m_data_ptr[last_index];
            delete [] m_data_ptr;
            m_data_ptr = new_data_ptr;

            m_full_capacity -= m_capacity;
        }
    }

    size_t size() const
    {
        return m_size;
    }

    void print()
    {
        size_t current_index = 0;
        size_t count = m_full_capacity / m_capacity;
        for (size_t ix = 0; ix < count; ++ix)
        {
            cout << " array " << ix << ": ";
            for (size_t iy = 0; iy < m_capacity; ++iy)
            {
                 cout << m_data_ptr[ix][iy] << " ";
                ++current_index;

                if (current_index == m_size)
                {
                    break;
                }
            }
            cout << endl;
        }
    }

    ~MatrixArray()
    {
        size_t size = m_full_capacity / m_capacity;
        for (size_t ix = 0; ix < size; ++ix)
        {
            delete [] m_data_ptr[ix];
        }
        delete [] m_data_ptr;
    }

private:
          T**    m_data_ptr {nullptr};
          size_t m_size     {0};
          size_t m_full_capacity;
    const size_t m_capacity;
};

#endif // MATRIXARRAY_H
