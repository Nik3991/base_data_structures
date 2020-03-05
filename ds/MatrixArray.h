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

    MatrixArray(size_t _capacity = 10) : m_capacity(_capacity), m_full_capacity(_capacity)
    {
        m_data_ptr    = new T*[1];
        m_data_ptr[0] = new T [_capacity];
    }

    void add(const T _value, size_t _index)
    {
        if (m_size == m_full_capacity)
        {
            // create additional array if matrix vector is full
            size_t new_data_size = (m_full_capacity / m_capacity) + 1;
            T** tmp_data_ptr = new T*[new_data_size];
            memcpy(tmp_data_ptr, m_data_ptr, new_data_size * sizeof (T*));
            tmp_data_ptr[new_data_size - 1] = new T[m_capacity];
            delete [] m_data_ptr;
            m_data_ptr = tmp_data_ptr;
            m_full_capacity += m_capacity;
            // - - - - - - - - - - - - - - - - - - - - - - - -
        }

        int ix_of_last_array   = m_size / m_capacity;
        int ix_array_to_insert = _index / m_capacity;

        if (ix_of_last_array != ix_array_to_insert)
        {
            // move elements if new element should be inserted in the middle of the matrix
            T*     destination_ptr = m_data_ptr[ix_of_last_array] + 1;
            T*     source_ptr      = m_data_ptr[ix_of_last_array];
            size_t count_of_bytes  = (m_size % m_capacity) * sizeof(T);

            memcpy(destination_ptr, source_ptr, count_of_bytes);

            for (int ix = ix_of_last_array - 1; ix >= ix_array_to_insert; --ix)
            {
                m_data_ptr[ix + 1][0] = m_data_ptr[ix][m_capacity - 1];

                if (ix > ix_array_to_insert)
                {
                    T*     destination_ptr = m_data_ptr[ix] + 1;
                    T*     source_ptr      = m_data_ptr[ix];
                    size_t count_of_bytes  = (m_capacity - 1) * sizeof(T);

                    memcpy(destination_ptr, source_ptr, count_of_bytes);
                }
            }
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        }

        // move elements in destination array
        _index %= m_capacity;

        T*     destination_ptr = m_data_ptr[ix_array_to_insert] + _index + 1;
        T*     source_ptr      = m_data_ptr[ix_array_to_insert] + _index;
        size_t count_of_bytes  = (m_capacity - _index - 1) * sizeof (T);

        memcpy(destination_ptr, source_ptr, count_of_bytes);
        // - - - - - - - - - - - - - - - - -

        m_data_ptr [ix_array_to_insert] [_index] = std::move(_value);
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
            // last array in matrix now empty and should be removed
            T** new_data_ptr = new T*[last_index];
            memcpy(new_data_ptr, m_data_ptr, last_index * sizeof (T*));

            delete [] m_data_ptr[last_index];
            delete [] m_data_ptr;
            m_data_ptr = new_data_ptr;

            m_full_capacity -= m_capacity;
            // - - - - - - - - - - - - - - - - - - - - - - - - - - -
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
            cout << "array " << ix << ": ";
            for (size_t iy = 0; iy < m_capacity; ++iy)
            {
                if (current_index < m_size)
                {
                    cout << m_data_ptr[ix][iy] << " ";
                } else
                {
                    cout << ". ";
                }
                ++current_index;
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
