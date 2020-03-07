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
    SpaceArray(const size_t _size = 10) : m_single_array_size(_size), m_full_size(0)
    {
        m_data_ptr = new T*[1];
        m_data_ptr[0] = new T[m_single_array_size];
        m_arrays_count = 1;
        m_elements_count = new size_t[m_arrays_count];
        m_elements_count[0] = 0;
    }

    virtual void add(const T value, size_t _index)
    {
        size_t array_index, position_to_add;
        tie(array_index, position_to_add) = get_position(_index);

        bool array_with_free_position_found = false;
        size_t ix_of_array_with_free_position = array_index;
        for (;ix_of_array_with_free_position < m_arrays_count; ++ix_of_array_with_free_position)
        {
            if (m_elements_count[ix_of_array_with_free_position] < m_single_array_size)
            {
                array_with_free_position_found = true;
                break;
            }
        }

        if ((array_index == m_arrays_count) || !array_with_free_position_found)
        {
            // space array is full - - - - - - - - - - - - - - - - - -
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
            // - - - - - - - - - - - - - - - - - - - - - - - - - - - -
        }

        bool elements_should_be_moved = (ix_of_array_with_free_position != array_index);
        if (elements_should_be_moved)
        {
            for (size_t iy = ix_of_array_with_free_position; iy > array_index; --iy)
            {
                T*     destination_ptr = m_data_ptr[iy] + 1;
                T*     source_ptr      = m_data_ptr[iy];

                size_t shift           = iy == ix_of_array_with_free_position ? 0 : 1;
                size_t count_of_bytes  = (m_elements_count[iy] - shift) * sizeof (T);

                memcpy(destination_ptr, source_ptr, count_of_bytes);
                m_data_ptr[iy][0] = m_data_ptr[iy - 1][m_elements_count[iy - 1] - 1];
            }
        }

        T* destination_ptr    = m_data_ptr[array_index] + position_to_add + 1;
        T* source_ptr         = m_data_ptr[array_index] + position_to_add;
        size_t count_of_bytes = (m_elements_count[array_index] - position_to_add - elements_should_be_moved) * sizeof (T);

        memcpy(destination_ptr, source_ptr, count_of_bytes);
        m_data_ptr[array_index][position_to_add] = std::move(value);

        ++m_elements_count[ix_of_array_with_free_position];
        ++m_full_size;
    }

    virtual T& operator[](size_t _index)
    {
        size_t array_index, position;
        if (_index == m_full_size - 1)
        {
            array_index = m_arrays_count - 1;
            position = m_elements_count[array_index] - 1;
        } else
        {
            tie(array_index, position) = get_position(_index);
        }
        return m_data_ptr[array_index][position];
    }

    virtual T get(size_t _index) const
    {
        size_t array_index, position;
        if (_index == m_full_size - 1)
        {
            array_index = m_arrays_count - 1;
            position = m_elements_count[array_index] - 1;
        } else
        {
            tie(array_index, position) = get_position(_index);
        }
        return m_data_ptr[array_index][position];
    }

    virtual void remove(size_t _index)
    {
        size_t array_index, position_to_remove;
        if (_index == m_full_size - 1)
        {
            array_index = m_arrays_count - 1;
            position_to_remove = m_elements_count[array_index] - 1;
        } else
        {
            tie(array_index, position_to_remove) = get_position(_index);
        }

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
            for (size_t iy = 0; iy < m_single_array_size; ++iy)
            {
                if (iy < m_elements_count[ix])
                {
                    cout << m_data_ptr[ix][iy] << " ";
                } else
                {
                    cout << ". ";
                }
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
        size_t array_index = 0, position = 0, size = 0;
        for (; array_index < m_arrays_count; ++array_index)
        {
            size_t current_count = size + m_elements_count[array_index];
            if (current_count >= _index && (_index < m_single_array_size * (array_index + 1)))
            {
                break;
            }
            size += m_elements_count[array_index];
        }

        position = _index - size;
        return make_tuple(array_index, position);
    }

    T**     m_data_ptr       {nullptr};
    size_t* m_elements_count {nullptr};
    size_t  m_arrays_count;
    size_t  m_full_size;
    const size_t m_single_array_size;
};

#endif // SPACEARRAY_H
