#ifndef SPACEARRAY_H
#define SPACEARRAY_H

#include <iostream>
#include <tuple>

#include "IArray.h"

using namespace std;

template <typename T>
class SpaceArray : public IArray<T>
{
public:
    SpaceArray(const size_t _size) : m_single_array_size(_size), m_full_size(0)
    {
        m_data_ptr = new T*[1];
        m_data_ptr[0] = new T[m_single_array_size];
        m_arrays_count = 1;
        m_elements_count = new size_t[m_arrays_count];
        m_elements_count[0] = 0;
    }

    virtual void add(const T value)
    {
        if (m_elements_count[m_arrays_count - 1] == m_single_array_size)
        {
            size_t* tmp_last_indexes = new size_t[m_arrays_count + 1];
            memcpy(tmp_last_indexes, m_elements_count, m_arrays_count * sizeof(size_t));

            tmp_last_indexes[m_arrays_count] = 0;
            delete [] m_elements_count;
            m_elements_count = tmp_last_indexes;

            T** tmp_data_array = new T*[m_arrays_count + 1];
            memcpy(tmp_data_array, m_data_ptr, m_arrays_count * sizeof(T*));

            tmp_data_array[m_arrays_count] = new T[m_single_array_size];
            delete [] m_data_ptr;
            m_data_ptr = tmp_data_array;
            ++m_arrays_count;
        }
        m_data_ptr[m_arrays_count - 1][m_elements_count[m_arrays_count - 1]] = std::move(value);
        ++m_elements_count[m_arrays_count - 1];
        ++m_full_size;
    }

    virtual T& operator[](size_t _index)
    {
        size_t array_index, position;
        tie(array_index, position) = get_position(_index);
        return m_data_ptr[array_index][position];
    }

    virtual T get(size_t _index) const
    {
        size_t array_index, position;
        tie(array_index, position) = get_position(_index);
        return m_data_ptr[array_index][position];
    }

    virtual void remove(size_t _index)
    {
        size_t array_index, position_to_remove;
        tie(array_index, position_to_remove) = get_position(_index);

/*                           position_to_remove
                                  |
                           0  1  2  3
        array_index -> 0: [.][.][.][.]
                       1: [.][.][.][.]
                       2: [.][.][.][.]
*/
        // remove element from array
        memcpy(m_data_ptr[array_index] + position_to_remove,
               m_data_ptr[array_index] + (position_to_remove + 1),
               (m_elements_count[array_index] - position_to_remove) * sizeof (T));

        --m_elements_count[array_index];
        --m_full_size;

        if (!m_elements_count[array_index] && m_arrays_count > 1)
        {
            // one of arrays is empty now

            // before operation:
            // 0: [.][.][.][.]
            // 1: [ ][ ][ ][ ]
            // 2: [.][.][.][.]

            T** new_data_ptr = new T*[m_arrays_count - 1];

            memcpy(new_data_ptr, m_data_ptr, array_index * sizeof (T*));

            memcpy(new_data_ptr + array_index,
                   m_data_ptr + array_index + 1,
                   (m_arrays_count - 1 - array_index) * sizeof (T*));

            delete [] m_data_ptr[array_index];
            delete [] m_data_ptr;
            m_data_ptr = new_data_ptr;

            size_t* new_elements_count_ptr = new size_t[m_arrays_count - 1];
            memcpy(new_elements_count_ptr, m_elements_count, array_index * sizeof (size_t));

            memcpy(new_elements_count_ptr + array_index,
                   m_elements_count + array_index + 1,
                   (m_arrays_count - 1 - array_index) * sizeof (size_t));

            delete [] m_elements_count;
            m_elements_count = new_elements_count_ptr;

            --m_arrays_count;

            // after operation:
            // 0: [.][.][.][.]
            // 1: [.][.][.][.]
        }
    }

    virtual size_t size() const
    {
        return m_full_size;
    }

    void print()
    {
        for (size_t ix = 0; ix < m_arrays_count; ++ix)
        {
            cout << "array " << ix << ": ";
            for (size_t iy = 0; iy < m_elements_count[ix]; ++iy)
            {
                cout << m_data_ptr[ix][iy] << " ";
            }
            cout << endl;
        }
    }

    virtual ~SpaceArray()
    {
        for (size_t ix = 0; ix < m_arrays_count; ++ix)
        {
            delete [] m_data_ptr[ix];
        }
        delete [] m_data_ptr;
    }

private:
    tuple<size_t, size_t> get_position(size_t _index) const
    {
        size_t size = 0;
        size_t array_index = 0;
        for (; array_index < m_arrays_count; ++array_index)
        {
            if ((size + m_elements_count[array_index]) > _index)
            {
                break;
            } else
            {
                size += m_elements_count[array_index];
            }
        }

        size_t position = _index - size;
        return make_tuple(array_index, position);
    }

    T**     m_data_ptr     {nullptr};
    size_t* m_elements_count {nullptr};
    size_t  m_arrays_count;
    size_t  m_full_size;
    const size_t m_single_array_size;
};

#endif // SPACEARRAY_H
