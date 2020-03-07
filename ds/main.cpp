#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <stack>
#include <queue>
#include <fstream>
#include <thread>

using namespace std;
using namespace std::chrono;

#include "SingleArray.h"
#include "VectorArray.h"
#include "MatrixArray.h"
#include "SpaceArray.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

template <typename Collection, typename Type, typename ...Args>
void test_get(ofstream& _output, int _items_count, int _get_items, Args ...args)
{
    Collection collection(args...);
    for (int ix = 0; ix < _items_count; ++ix)
    {
        collection.add(Type(ix), collection.size());
    }

    // - - - - - - - - - - - - - - - - - -

    volatile Type t;
    auto start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        t = ++collection[0];
    }
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    _output << " get from (0);            elements count = " << _get_items << "   result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        t = ++collection[collection.size() / 2];
    }
    end = high_resolution_clock::now();
    time = duration_cast<milliseconds>(end - start);
    _output << " get from (c.size() / 2); elements count = " << _get_items << "   result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        t = ++collection[collection.size() - 1];
    }
    end = high_resolution_clock::now();
    time = duration_cast<milliseconds>(end - start);
    _output << " get from (c.size());     elements count = " << _get_items << "   result time = " << time.count() << " ms" << endl;
}

template <typename Collection, typename Type, typename ...Args>
void test_remove(ofstream& _output, int _items_count, int _remove_items, Args ...args)
{
    Collection collection(args...);
    // - - - - - - - - - - - - - - - - - - - - -
    for (int ix = 0; ix < _items_count; ++ix)
    {
        collection.add(Type(ix), collection.size());
    }
    // - - - - - - - - - - - - - - - - - - - - -

    auto start  = high_resolution_clock::now();
    for (int ix = 0; ix < _remove_items; ++ix)
    {
        collection.remove(0);
    }
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    _output << " remove from (0);              elements count = " << _remove_items << "    result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - - - - -
    for (int ix = 0; ix < _remove_items; ++ix)
    {
        collection.add(Type(ix), collection.size());
    }
    // - - - - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _remove_items; ++ix)
    {
        collection.remove(collection.size() / 2);
    }
    end = high_resolution_clock::now();
    time = duration_cast<milliseconds>(end - start);
    _output << " remove from (c.size() / 2);   elements count = " << _remove_items << "    result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - - - - -
    for (int ix = 0; ix < _remove_items; ++ix)
    {
        collection.add(Type(ix), collection.size());
    }
    // - - - - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _remove_items; ++ix)
    {
        collection.remove(collection.size() - 1);
    }
    end = high_resolution_clock::now();
    time = duration_cast<milliseconds>(end - start);
    _output << " remove from (c.size());       elements count = " << _remove_items << "    result time = " << time.count() << " ms" << endl;
}

template <typename Collection, typename Type, typename ...Args>
void test_add(ofstream& _output, size_t _items_count, Args ...args)
{
    {
        Collection collection(args...);
        auto start  = high_resolution_clock::now();
        for (int ix = 0; ix < _items_count; ++ix)
        {
            collection.add(Type(ix), 0);
        }
        auto end = high_resolution_clock::now();
        auto time = duration_cast<milliseconds>(end - start);

        _output << " add to (0);            elements = " << _items_count << "   result time = " << time.count() << " ms" << endl;
    }

    {
        Collection collection(args...);
        auto start  = high_resolution_clock::now();
        for (int ix = 0; ix < _items_count; ++ix)
        {
            collection.add(Type(ix), collection.size() / 2);
        }
        auto end = high_resolution_clock::now();
        auto time = duration_cast<milliseconds>(end - start);

        _output << " add to (c.size() / 2); elements = " << _items_count << "   result time = " << time.count() << " ms" << endl;
    }

    {
        Collection collection(args...);
        auto start  = high_resolution_clock::now();
        for (int ix = 0; ix < _items_count; ++ix)
        {
            collection.add(Type(ix), collection.size());
        }
        auto end = high_resolution_clock::now();
        auto time = duration_cast<milliseconds>(end - start);

        _output << " add to (c.size());     elements = " << _items_count << "   result time = " << time.count() << " ms" << endl;
    }
}

template <typename Collection, typename Type, typename ...Args>
void test(const char* _message, const char * _file, int _items_count, int _elements_to_remove, int _get_times, Args ...args)
{
    ofstream output;
    output.open(_file);

    if (output)
    {
        cout << "TEST OF " << _message << " START WORK" << endl;
        output << " - - - - - - - START TEST OF " << _message << " - - - - - - -" << endl << endl;
        test_add<Collection, Type>(output, _items_count, args...);
        output << endl;
        test_get<Collection, Type>(output, _items_count, _get_times, args...);
        output << endl;
        test_remove<Collection, Type>(output, _items_count, _elements_to_remove, args...);
        output << endl;
        output << " - - - - - - - - END TEST OF " << _message << " - - - - - - -" << endl << endl;

        output.flush();
        output.close();
        cout << "TEST OF " << _message << " END WORK" << endl << endl;
    } else
    {
        cout << " can`t open file to write test result for" << _message << endl;
    }
}

template <typename T>
struct StackWrapper : public Stack<T>
{
    void add(T _value, size_t _index)
    {
        (void)_index;
        this->push(_value);
    }

    T& operator[](size_t _index)
    {
        (void)_index;
        static int i = this->pop();
        return i;
    }

    T get(size_t _index)
    {
        (void) _index;
        return this->pop();
    }

    void remove(size_t _index) {(void)_index;}
};


template <typename T>
struct QueueWrapper : public Queue<T>
{
    void add(T _value, size_t _index)
    {
        (void)_index;
        this->enqueue(_value);
    }

    T& operator[](size_t _index)
    {
        (void)_index;
        static int i = this->dequeue();
        return i;
    }

    T get(size_t _index)
    {
        (void) _index;
        return this->dequeue();
    }

    void remove(size_t _index) {(void)_index;}
};


template <typename T, typename P>
struct PriorityQueueWrapper : public PriorityQueue<T, P>
{
    void add(T _value, size_t _index)
    {
        (void)_index;
        P priority(0);
        this->enqueue(_value, priority);
    }

    T& operator[](size_t _index)
    {
        (void)_index;
        static int i = this->dequeue();
        return i;
    }

    T get(size_t _index)
    {
        (void) _index;
        return this->dequeue();
    }

    void remove(size_t _index) {(void)_index;}
};


template <typename T>
struct StdVectorWrapper : public vector<T>
{
    void add(T _value, size_t _index)
    {
        this->emplace(this->begin() + _index, _value);
    }


    T get(size_t _index)
    {
        return vector<T>::at(_index);
    }

    void remove(size_t _index)
    {
        vector<T>::erase(vector<T>::begin() + _index);
    }
};

template <typename T>
struct StdQueueWrapper : public queue<T>
{
    void add(T _value, size_t _index)
    {
        (void)_index;
        queue<T>::push(_value);
    }

    T& operator[](size_t _index)
    {
        (void)_index;
        return this->front();
    }

    T get(size_t _index)
    {
        (void)_index;
        T result = queue<T>::front();
        queue<T>::pop();
        return result;
    }

    void remove(size_t _index) {(void)_index;}
};

template <typename T>
struct StdStackWrapper : public stack<T>
{
    void add(T _value, size_t _index)
    {
        (void)_index;
        stack<T>::push(_value);
    }

    T& operator[](size_t _index)
    {
        (void)_index;
        return this->top();
    }

    T get(size_t _index)
    {
        (void)_index;
        T result = stack<T>::top();
        stack<T>::pop();
        return result;
    }

    void remove(size_t _index) {(void)_index;}
};

int main()
{
    int count_of_elements = 1000000;
    int elements_to_remove = 100000;
    int elements_to_get = 100000;

    test<VectorArray<int>, int, int, double>(static_cast<const char*>("VectorArray<int>(10, 0.2)"),
                                             static_cast<const char*>("vector_array_10_02.txt"),
                                             count_of_elements, elements_to_remove, elements_to_get, 10, 0.2);

    test<VectorArray<int>, int, int, double>(static_cast<const char*>("VectorArray<int>(10, 1.0)"),
                                             static_cast<const char*>("vector_array_10_10.txt"),
                                             count_of_elements, elements_to_remove, elements_to_get, 10, 1.0);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<StdVectorWrapper<int>, int>(static_cast<const char*>("StdVectorWrapper<int>"),
                                     static_cast<const char*>("std_vector.txt"),
                                     count_of_elements, elements_to_remove, elements_to_get);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<MatrixArray<int>, int, int>(static_cast<const char*>("MatrixArray<int>(100)"),
                                     static_cast<const char*>("matrix_array_100.txt"),
                                     count_of_elements, elements_to_remove, elements_to_get, 100);

    test<MatrixArray<int>, int, int>(static_cast<const char*>("MatrixArray<int>(1000)"),
                                     static_cast<const char*>("matrix_array_1000.txt"),
                                     count_of_elements, elements_to_remove, elements_to_get, 1000);

    test<MatrixArray<int>, int, int>(static_cast<const char*>("MatrixArray<int>(10000)"),
                                     static_cast<const char*>("matrix_array_10000.txt"),
                                     count_of_elements, elements_to_remove, elements_to_get, 10000);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<SpaceArray<int>, int, int>(static_cast<const char*>("SpaceArray<int>(100)"),
                                    static_cast<const char*>("space_array_100.txt"),
                                    count_of_elements, elements_to_remove, elements_to_get, 100);

    test<SpaceArray<int>, int, int>(static_cast<const char*>("SpaceArray<int>(1000)"),
                                    static_cast<const char*>("space_array_1000.txt"),
                                    count_of_elements, elements_to_remove, elements_to_get, 1000);

    test<SpaceArray<int>, int, int>(static_cast<const char*>("SpaceArray<int>(10000)"),
                                    static_cast<const char*>("space_array_10000.txt"),
                                    count_of_elements, elements_to_remove, elements_to_get, 10000);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<StackWrapper<int>, int>(static_cast<const char*>("StackWrapper<int>"),
                                 static_cast<const char*>("stack_wrapper.txt"),
                                 count_of_elements, elements_to_remove, elements_to_get);

    test<StdStackWrapper<int>, int>(static_cast<const char*>("StdStackWrapper<int>"),
                                 static_cast<const char*>("std_stack_wrapper.txt"),
                                 count_of_elements, elements_to_remove, elements_to_get);
    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<QueueWrapper<int>, int>(static_cast<const char*>("QueueWrapper<int>"),
                                 static_cast<const char*>("queue_wrapper.txt"),
                                 count_of_elements, elements_to_remove, elements_to_get);

    test<StdQueueWrapper<int>, int>(static_cast<const char*>("StdQueueWrapper<int>"),
                                    static_cast<const char*>("std_queue_wrapper.txt"),
                                    count_of_elements, elements_to_remove, elements_to_get);

    // - - - - - - - - - - - - - - - - - - - - - - - - - -

    test<SingleArray<int>, int>(static_cast<const char*>("SingleArray<int>"),
                                static_cast<const char*>("single_array.txt"),
                                count_of_elements, elements_to_remove, elements_to_get);

    return 0;
}
