#ifndef IARRAY_H
#define IARRAY_H

#include <memory>

template <typename T>
class IArray
{
public:
    virtual void add(const T value) = 0;

    //virtual Iter begin() = 0;
    //virtual Iter end() = 0;

    virtual T& operator[](size_t _index) = 0;
    virtual T get(size_t _index) const = 0;

    virtual void remove(size_t _index) = 0;

    virtual size_t size() const = 0;

    virtual ~IArray() {}
};

#endif // IARRAY_H
