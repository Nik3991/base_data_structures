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

    auto start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        collection.get(0);
    }
    auto end = high_resolution_clock::now();
    auto time = duration_cast<milliseconds>(end - start);
    _output << " get from (0);            elements count = " << _get_items << "   result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        collection.get(collection.size() / 2);
    }
    end = high_resolution_clock::now();
    time = duration_cast<milliseconds>(end - start);
    _output << " get from (c.size() / 2); elements count = " << _get_items << "   result time = " << time.count() << " ms" << endl;

    // - - - - - - - - - - - - - - - - - -

    start  = high_resolution_clock::now();
    for (int ix = 0; ix < _get_items; ++ix)
    {
        collection.get(collection.size());
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
        collection.remove(collection.size());
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
        cout << "TEST OF " << _message << " END WORK" << endl;
    } else
    {
        cout << " can`t open file to write test result for" << _message << endl;
    }
}

template <typename T>
struct StackWrapper : public Stack<T>
{
    void add(T _value)
    {
        this->push(_value);
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
    void add(T _value)
    {
        this->enqueue(_value);
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
    void add(T _value)
    {
        P priority(0);
        this->enqueue(_value, priority);
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
    void add(T _value)
    {
        this->push_back(_value);
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
    void add(T _value)
    {
        queue<T>::push(_value);
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
    void add(T _value)
    {
        stack<T>::push(_value);
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
    int count_of_elements = 100000;

    //void test(const char* _message, int _items_count, int _elements_to_remove, int _get_times, Args ...args)

    //---------------------------
    {
        {
            //VectorArray<int> vector_10_02(10, 0.2);
            thread t1(test<VectorArray<int>, int, int, double>, static_cast<const char*>("VectorArray<int>(10, 0.2)"),
                                                                static_cast<const char*>("D:/vector_results.txt"),
                                                                count_of_elements, 10000, 10000, 10, 0.2);

            t1.join();
            //test<VectorArray<int>, int, int, double>(static_cast<const char*>("VectorArray<int>(10, 0.2)"),
            //                                         static_cast<const char*>("D:/vector_results.txt"),
            //                                         count_of_elements, 10000, 10000, 10, 0.2);
        }
//        {
//            VectorArray<int> vector_10_1(10, 1.0);
//            test<VectorArray<int>, int>(vector_10_1,  count_of_elements, static_cast<const char*>("VectorArray<int>(10, 1.0)"));
//        }
    }
    //---------------------------


//    //---------------------------
//    {
//        StdVectorWrapper<int> std_vector;
//        test<StdVectorWrapper<int>, int>(std_vector, count_of_elements, static_cast<const char*>("StdVectorWrapper<int>"));
//    }
//    //---------------------------


//    count_of_elements = 100000;
//    //---------------------------
//    {
//        SingleArray<int> signle_array;
//        test<SingleArray<int>, int>(signle_array, count_of_elements, static_cast<const char*>("SingleArray<int>"));
//    }
//    //---------------------------


//    count_of_elements = 100000000;
//    //---------------------------
//    {
//        {
//            MatrixArray<int> ma_size_100(100);
//            test<MatrixArray<int>, int>(ma_size_100, count_of_elements, static_cast<const char*>("MatrixArray<int>(100)"));
//        }
//        {
//            MatrixArray<int> ma_size_1000(1000);
//            test<MatrixArray<int>, int>(ma_size_1000, count_of_elements, static_cast<const char*>("MatrixArray<int>(1000)"));
//        }
//        {
//            MatrixArray<int> ma_size_10000(10000);
//            test<MatrixArray<int>, int>(ma_size_10000, count_of_elements, static_cast<const char*>("MatrixArray<int>(10000)"));
//        }
//    }
//    //---------------------------


//    //---------------------------
//    {
//        {
//            SpaceArray<int> spa_size_100(100);
//            test<SpaceArray<int>, int>(spa_size_100, count_of_elements, static_cast<const char*>("SpaceArray<int>(100)"));
//        }
//        {
//            SpaceArray<int> spa_size_1000(1000);
//            test<SpaceArray<int>, int>(spa_size_1000, count_of_elements, static_cast<const char*>("SpaceArray<int>(1000)"));
//        }
//        {
//            SpaceArray<int> spa_size_10000(10000);
//            test<SpaceArray<int>, int>(spa_size_10000, count_of_elements, static_cast<const char*>("SpaceArray<int>(10000)"));
//        }
//    }
//    //---------------------------


//    //---------------------------
//    {
//        StackWrapper<int> stack;
//        test<StackWrapper<int>, int>(stack, count_of_elements, static_cast<const char*>("StackWrapper<int>"));
//    }
//    //---------------------------


//    //---------------------------
//    {
//        StdStackWrapper<int> std_stack;
//        test<StdStackWrapper<int>, int>(std_stack, count_of_elements, static_cast<const char*>("StdStackWrapper<int>"));
//    }
//    //---------------------------


//    //---------------------------
//    {
//        QueueWrapper<int> queue;
//        test<QueueWrapper<int>, int>(queue, count_of_elements, static_cast<const char*>("QueueWrapper<int>"));
//    }
//    //---------------------------


//    //---------------------------
//    {
//        StdQueueWrapper<int> std_queue;
//        test<StdQueueWrapper<int>, int>(std_queue, count_of_elements, static_cast<const char*>("StdQueueWrapper<int>"));
//    }
//    //---------------------------

    return 0;
}
