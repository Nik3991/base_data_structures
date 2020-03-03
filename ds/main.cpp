#include <iostream>
#include <random>
#include <chrono>
#include <vector>
#include <stack>
#include <queue>

using namespace std;
using namespace std::chrono;

#include "SingleArray.h"
#include "VectorArray.h"
#include "MatrixArray.h"
//#include "SpaceArray.h"
#include "Stack.h"
#include "Queue.h"
#include "PriorityQueue.h"

template <typename T>
void print_array(T & _arr)
{
    cout << endl;
    for (size_t ix = 0; ix < _arr.size(); ++ix)
    {
        cout << "element " << ix << " = " << _arr.get(ix) << endl;
    }
}

//void SA()
//{
//    SpaceArray<int> sa(3);

//    for (int ix = 0; ix < 10; ++ ix)
//    {
//        sa.add(ix);
//    }

//    sa.print();

//    int select;
//    cin >> select;
//    while (select)
//    {
//        switch (select)
//        {
//            case 1:
//            {
//                sa.print();
//            } break;

//            case 2:
//            {
//                cin >> select;
//                sa.add(select);
//                sa.print();
//            } break;

//            case 3:
//            {
//                size_t index;
//                cin >> index;
//                sa.remove(index);
//                sa.print();
//            } break;

//            default: break;
//        }
//        cin >> select;
//        cout << endl;
//    }
//}

//void MA()
//{
//    MatrixArray<int> matrix(10);

//    print_array<MatrixArray<int>>(matrix);

//    for (int ix = 0; ix < 23; ++ix)
//    {
//        matrix.add(ix);
//    }

//    print_array<MatrixArray<int>>(matrix);

//    for (size_t ix = 0; ix < 5; ++ix)
//    {
//        matrix.remove(matrix.size() - 1);
//    }

//    print_array<MatrixArray<int>>(matrix);

//    for (size_t ix = 0; ix < 5; ++ix)
//    {
//        matrix.remove(0);
//    }

//    print_array<MatrixArray<int>>(matrix);

//    for (size_t ix = 0; ix < 3; ++ix)
//    {
//        matrix.remove(7);
//    }

//    print_array<MatrixArray<int>>(matrix);
//}

//void Q()
//{
//    Queue<int> q;

//    for (int ix = 0; ix < 10; ++ix)
//    {
//        q.enqueue(ix);
//    }

//    while (q.size())
//    {
//        cout << "element:" << q.size() << " " << q.dequeue() << endl;
//    }

//    //q.dequeue();
//}

//void S()
//{
//    Stack<int> s;

//    for(int ix = 0; ix < 10; ++ix)
//    {
//        s.push(ix);
//    }

//    while (s.size())
//    {
//        cout << "element:" << s.size() << " " << s.pop() << endl;
//    }

//    //s.pop();
//}

//void PQ()
//{
//    PriorityQueue<int, int> pq;

//    for (int ix = 0; ix < 10; ++ix)
//    {
//        int priority = rand() % 10;
//        //cout << " ix = " << ix << " priority = " << priority << endl;
//        pq.enqueue(ix, priority);
//    }

//    pq.print();

//    int select ;

//    cin >> select;
//    while (select != 0)
//    {
//        if (select == 2)
//        {
//            for (int ix = 0; ix < 10; ++ix)
//            {
//                int priority = rand() % 10;
//                pq.enqueue(ix, priority);
//            }
//            pq.print();
//            cout << endl;
//        } else
//        {
//            cout << "element = " << pq.dequeue() << endl << endl;
//            pq.print();
//            cout << endl;
//        }
//        cin >> select;
//    }
//}

//template <typename Collection, typename Type>
//milliseconds test_get(Collection& _c, size_t _index)
//{
//    int tests_cout = 100;

//    auto start = high_resolution_clock::now();
//    for (int ix = 0; ix < tests_cout; ++ix)
//    {
//        Type t = _c.get(_index);
//        ++t;
//        (void)t;
//    }
//    auto end = high_resolution_clock::now();
//    auto time = duration_cast<milliseconds>(end - start);
//    return time;
//}

//template <typename Collection, typename Type>
//void test(Collection& c, int _items_count, const char* _message)
//{
//    auto start  = high_resolution_clock::now();
//    for (int ix = 0; ix < _items_count; ++ix)
//    {
//        c.add(Type(ix));
//    }

//    auto end = high_resolution_clock::now();
//    auto time = duration_cast<milliseconds>(end - start);

//    cout << _message << " add " << _items_count << " elements = " << time.count() << " ms" << endl;

//    time = test_get<Collection, Type>(c, 0);
//    cout << _message << " get from start     = " << time.count() << " ms" << endl;

//    time = test_get<Collection, Type>(c, c.size() / 2);
//    cout << _message << " get from middle    = " << time.count() << " ms" << endl;

//    time = test_get<Collection, Type>(c, c.size() - 1);
//    cout << _message << " get from end       = " << time.count() << " ms" << endl;


//    int elements_to_remove = 100;
//    start = high_resolution_clock::now();
//    for (int ix = 0; ix < elements_to_remove; ++ix)
//    {
//        c.remove(0);
//    }
//    end = high_resolution_clock::now();
//    time = duration_cast<milliseconds>(end - start);
//    cout << _message << " remove from start  = " << time.count() << " ms" << endl;

//    for (int ix = 0; ix < elements_to_remove; ++ix)
//    {
//        c.add(ix);
//    }

//    start = high_resolution_clock::now();
//    for (int ix = 0; ix < elements_to_remove; ++ix)
//    {
//        c.remove(c.size() / 2);
//    }
//    end = high_resolution_clock::now();
//    time = duration_cast<milliseconds>(end - start);
//    cout << _message << " remove from middle = " << time.count() << " ms" << endl;

//    for (int ix = 0; ix < elements_to_remove; ++ix)
//    {
//        c.add(ix);
//    }

//    start = high_resolution_clock::now();
//    for (int ix = 0; ix < elements_to_remove; ++ix)
//    {
//        c.remove(c.size() - 1);
//    }
//    end = high_resolution_clock::now();
//    time = duration_cast<milliseconds>(end - start);
//    cout << _message << " remove from end    = " << time.count() << " ms" << endl << endl;
//}

//template <typename T>
//struct StackWrapper : public Stack<T>
//{
//    void add(T _value)
//    {
//        this->push(_value);
//    }

//    T get(size_t _index)
//    {
//        (void) _index;
//        return this->pop();
//    }

//    void remove(size_t _index) {(void)_index;}
//};


//template <typename T>
//struct QueueWrapper : public Queue<T>
//{
//    void add(T _value)
//    {
//        this->enqueue(_value);
//    }

//    T get(size_t _index)
//    {
//        (void) _index;
//        return this->dequeue();
//    }

//    void remove(size_t _index) {(void)_index;}
//};


//template <typename T, typename P>
//struct PriorityQueueWrapper : public PriorityQueue<T, P>
//{
//    void add(T _value)
//    {
//        P priority(0);
//        this->enqueue(_value, priority);
//    }

//    T get(size_t _index)
//    {
//        (void) _index;
//        return this->dequeue();
//    }

//    void remove(size_t _index) {(void)_index;}
//};


//template <typename T>
//struct StdVectorWrapper : public vector<T>
//{
//    void add(T _value)
//    {
//        this->push_back(_value);
//    }

//    T get(size_t _index)
//    {
//        return vector<T>::at(_index);
//    }

//    void remove(size_t _index)
//    {
//        vector<T>::erase(vector<T>::begin() + _index);
//    }
//};

//template <typename T>
//struct StdQueueWrapper : public queue<T>
//{
//    void add(T _value)
//    {
//        queue<T>::push(_value);
//    }

//    T get(size_t _index)
//    {
//        (void)_index;
//        T result = queue<T>::front();
//        queue<T>::pop();
//        return result;
//    }

//    void remove(size_t _index) {(void)_index;}
//};

//template <typename T>
//struct StdStackWrapper : public stack<T>
//{
//    void add(T _value)
//    {
//        stack<T>::push(_value);
//    }

//    T get(size_t _index)
//    {
//        (void)_index;
//        T result = stack<T>::top();
//        stack<T>::pop();
//        return result;
//    }

//    void remove(size_t _index) {(void)_index;}
//};

//int main ()
//{
//    VectorArray<int> va(10, 1.0);
//    for (int ix = 0; ix < 10; ++ix)
//    {
//        va.add(ix, 0);
//    }
//    va.print();
//    va.add(111, 5);
//    va.print();

//    SingleArray<int> sa;
//    for (int ix = 0; ix < 10; ++ix)
//    {
//        sa.add(ix,0);
//    }
//    sa.print();
//    sa.add(111, 5);
//    sa.print();

//    for (int ix = 11; ix < 20; ++ix)
//    {
//        sa.add(ix,sa.size());
//    }
//    sa.print();
//}

int main ()
{
    MatrixArray<int> ma(10);

    for (int ix = 0; ix < 20; ++ix)
    {
        ma.add(ix, 0);
        ma.print();
        cout << endl;
    }

    cout << endl << endl << endl;

    for (int ix = 100; ix < 110; ++ix)
    {
        ma.add(ix, ma.size());
        ma.print();
        cout << endl;
    }

    for (int ix = 100; ix < 110; ++ix)
    {
        ma.add(77, 20);
        ma.print();
        cout << endl;
    }

    while (ma.size()) {
        ma.remove(0);
        ma.print();
        cout << endl;
    }

    //for (int ix = 15; ix < 25; ++ix)
    //{
    //    ma.add(ix, 5);
    //    ma.print();
    //    cout << endl;
    //}
}

//int main()
//{
//    int count_of_elements = 100000000;

//    //---------------------------
//    {
//        {
//            VectorArray<int> vector_10_02(10, 0.2);
//            test<VectorArray<int>, int>(vector_10_02,  count_of_elements, static_cast<const char*>("VectorArray<int>(10, 0.2)"));
//        }
//        {
//            VectorArray<int> vector_10_1(10, 1.0);
//            test<VectorArray<int>, int>(vector_10_1,  count_of_elements, static_cast<const char*>("VectorArray<int>(10, 1.0)"));
//        }
//    }
//    //---------------------------


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

//    return 0;
//}
















