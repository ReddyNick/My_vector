#ifndef MY_VECTOR_MY_VECTOR_H
#define MY_VECTOR_MY_VECTOR_H

#include <iostream>

typedef unsigned long size_t;


template <typename Type>
class Vector
{
public:

    Vector();
    explicit Vector(size_t capacity);
    Vector(const Vector<Type>& v);
    const Vector<Type>& operator=(const Vector<Type>& that);
    const Vector<Type>& operator=(Vector<Type> && that);


    void swap(Vector<Type>& copy);
    ~Vector();


    size_t size() const   { return size_; }
    size_t capacity() const { return capacity_; }
    bool empty() const  { return size_ == 0; }

    Type push_back(Type item);
    Type pop();

    Type& at(size_t index);
    Type& operator[](size_t index);
    const Type& operator[](size_t index) const;

    void* operator new(size_t size)
    {
        std::cout << "New vector created" << std::endl;
        return new char[size];
    }

private:
    Type* data_;
    size_t capacity_;
    size_t mincap_;
    size_t size_;

    int Resize(int how);
    int NewData();
};

typedef unsigned int bdata_t;
class Bits
{
public:
    int index;

    Bits() : data_(nullptr), index(0) {};
    Bits(int size) : data_(new bdata_t [size]{}), index(0) {};

    ~Bits() { delete[] data_; }

    bool operator=(bool value);
    bool operator&();

private:
    bdata_t* data_;

};

template<>
class Vector<bool>
{
public:

    Vector() : size_(0), elem_(nullptr) {};
    Vector(int size);
    int evaluate_size(int size);
    ~Vector();

    int size() const { return size_; };
    Bits& operator[](int index);
    bool operator[](int index) const;

private:
    Bits* elem_;
    int size_;
};




void* operator new[](size_t size, const int line, const char* func, const char* inf = "");
void operator delete[](void* p, const int line, const char* func, const char* inf = "");

template<typename Type>
Vector<Type> operator +(const Vector<Type>& v1, const Vector<Type>& v2);


#include "My_vector.hpp"

#endif //MY_VECTOR_MY_VECTOR_H
