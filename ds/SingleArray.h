#ifndef SINGLEARRAY_H
#define SINGLEARRAY_H

#include <memory>
#include <iostream>
#include "IArray.h"

using namespace std;

template <typename T>
class SingleArray : public IArray<T>
{
public:
    template <typename K>
    class iterator
    {
    public:
        iterator(K* _data_ptr) { m_ptr = _data_ptr; }

        bool operator==(iterator& _i) const { return m_ptr == _i.m_ptr; }
        bool operator!=(iterator& _i) const { return !(*this == _i); }

        K& operator*() { return *m_ptr; }

        void operator++() { ++m_ptr; }
        void operator--() { --m_ptr; }

    private:
        K* m_ptr {nullptr};
    };

    SingleArray()
    {
        m_data_ptr = new T[0];
    }

    iterator<T> begin()
    {
        return iterator<T>(m_data_ptr);
    }

    iterator<T> end()
    {
        return iterator<T>(m_data_ptr + m_size);
    }

    void add(const T value, size_t _index)
    {
        T* tmp_ptr = new T[m_size + 1];
        memcpy(tmp_ptr, m_data_ptr, _index * sizeof (T));
        memcpy(tmp_ptr + _index + 1, m_data_ptr + _index, (m_size - _index) * sizeof (T));

        delete[] m_data_ptr;
        m_data_ptr = tmp_ptr;

        m_data_ptr[_index] = std::move(value);
        ++m_size;
    }

    T& operator[](size_t _index)
    {
        return m_data_ptr[_index];
    }

    T get(size_t _index) const
    {
        return m_data_ptr[_index];
    }

    void remove(size_t _index)
    {
        --m_size;
        T* tmp_ptr = new T[m_size];
        memcpy(tmp_ptr, m_data_ptr, _index * sizeof (T));
        memcpy(tmp_ptr + _index, m_data_ptr + _index + 1, (m_size - _index) * sizeof (T));

        delete [] m_data_ptr;
        m_data_ptr = tmp_ptr;
    }

    size_t size() const
    {
        return m_size;
    }

    void print()
    {
        cout << "array: ";
        for (int ix = 0; ix < m_size; ++ix)
        {
            cout << m_data_ptr[ix] << " ";
        }
        cout << endl;
    }

    ~SingleArray()
    {
        delete [] m_data_ptr;
    }

private:
    size_t m_size     {0};
        T* m_data_ptr {nullptr};
};

#endif // SINGLEARRAY_H
