#ifndef MY_VECTOR_TEMPLATES_HPP
#define MY_VECTOR_TEMPLATES_HPP

#include "My_vector.h"
#include <iostream>
#include "stdio.h"
#include <typeinfo>
#include <cassert>

const int more = 1;
const int less = 0;
const int INCREASE_RATIO = 2;
const double DECREASE_RATIO = 0.25;

FILE* log = fopen("log.txt", "w");

template<typename Type>
Vector<Type>::Vector():
        data_(nullptr),
        capacity_(0),
        mincap_(0),
        size_(0)
{
    fprintf(log, "'new' in the %d line (function <%s 'nullptr'>)\n", __LINE__, __func__);
}

template<typename Type>
Vector<Type>::Vector(size_t capacity):
        data_(new(__LINE__, __func__) Type[capacity]{}),
        capacity_(capacity),
        mincap_(capacity),
        size_(capacity)
{}

template<typename Type>
Vector<Type>::~Vector()
{
    if (this->data_ == nullptr)
        operator delete[] (data_, __LINE__, __func__, " 'nullptr'");
    else
        operator delete[] (data_, __LINE__, __func__);
    data_ = nullptr;
    capacity_ = size_ = -1;
}

template<typename Type>
Type Vector<Type>::push_back(Type item)
{
    if (size_ == capacity_)
            Resize(more);

    data_[size_++] = item;

    return 0;
}

template<typename Type>
Type Vector<Type>::pop()
{
    if(size_ == 0)
    {
        std::cout << "\nSTACK UNDERFLOW!\n" << std::endl;
        abort();
    }

    Type item = data_[--size_];

    Resize(less);
    return  item;
}

template<typename Type>
int Vector<Type>::Resize(int how)
{
    if (how == more)
    {
        if (capacity_ == 0)
            capacity_ = 1;
        else
            capacity_ = INCREASE_RATIO * capacity_;

        NewData();
        return 0;
    }
    else
    {
        if ((capacity_ / INCREASE_RATIO < mincap_) || (size_ > DECREASE_RATIO * capacity_))
            return 0;

        capacity_ = capacity_ / INCREASE_RATIO;

        NewData();
        return 0;
    }
}

template<typename Type>
int Vector<Type>::NewData()
{
    Type* newdata = new(__LINE__, __func__) Type[capacity_];

    for (int i = 0; i < size_; i++)
        newdata[i] = data_[i];

    Type* ptr = data_;
    data_ = newdata;

    delete[] ptr;
}

template<typename Type>
Type& Vector<Type>::at(size_t index)
{
    if (index < 0 || index >= size_)
    {
        std::cout << "out of range!\n";
        abort();
    }

    return data_[index];
}

template<typename Type>
Type& Vector<Type>::operator[](size_t index)
{
    return at(index);
}

template<typename Type>
const Type& Vector<Type>::operator[](size_t index) const
{
    if (index < 0 || index >= size_)
    {
        std::cout << "out of range!\n";
        abort();
    }
    return data_[index];
}

template<typename Type>
Vector<Type>::Vector(const Vector<Type>& v):
        data_(new(__LINE__, __func__, "(const Vector &v)") Type [v.size_]),
        size_(v.size_),
        capacity_(v.capacity_),
        mincap_(v.mincap_)
{
    for (int i = 0; i < size_; i++)
        data_[i] = v.data_[i];
}

template<typename Type>
const Vector<Type>& Vector<Type>::operator=(const Vector<Type> &that)
{
    Vector copy (that);         // deduction -> copy is Vector<Type>
    swap(copy);
    return *this;
}

template<typename Type>
void Vector<Type>::swap(Vector<Type> &copy)
{
    std::swap(size_, copy.size_);
    std::swap(data_, copy.data_);
    std::swap(capacity_, copy.capacity_);
    std::swap(mincap_, copy.mincap_);
}

//another copy constructor
//const Vector& Vector::operator=(const Vector &that)
//{
//    this-> ~Vector();
//    new(this) Vector(that);
//
//    return *this;
//}



void* operator new[](size_t size, const int line, const char* func, const char* inf)
{
    fprintf(log,"'new' in the %d line (function <%s%s>)\n", line, func, inf);
    return malloc(size);
}

void operator delete[](void *p, const int line, const char* func, const char* inf)
{
    fprintf(log,"'delete' in the %d line (function <%s%s>)\n", line, func, inf);
    free(p) ;
}

template<typename Type>
Vector<Type> operator+(const Vector<Type>& v1, const Vector<Type>& v2)
{
    Vector<Type> result;
    bool left = true;

    if (v1.size() > v2.size())
        result = v1;
    else
    {

        result = v2;
        left = false;
    }

    if (left)
    {
        int leng = v2.size();
        for (int i = 0; i < leng; i++)
            result[i] += v2[i];
    }
    else
    {
        int leng = v1.size();
        for (int i = 0; i < leng; i++)
            result[i] += v1[i];
    }

    return result;
}

template<typename Type>
const Vector<Type>& Vector<Type>::operator=(Vector<Type> &&that)
{
    swap(that);
    return *this;
}


int Vector<bool>::evaluate_size(int size)
{
    return size/31 + ((size % 31 != 0) ? 1 : 0);
}

Vector<bool>::Vector(int size)
{
    size_ = 0;
    elem_ = new Bits(evaluate_size(size));
}

Bits& Vector<bool>::operator[](int index)
{
     assert(index >= 0);
     elem_->index = index;
     return *elem_;
}

bool Bits::operator=(bool value)
{
    if (value)
        data_[index / 32] |= (unsigned int)0x1 << (index % 32);
    else
        data_ [index / 32] &= ((unsigned int)0xFFFFFFFF - 0x1) << (index % 32);

    return value;
}

bool Bits::operator&()
{
    return data_[index / 32] & (0x1 << (index % 32));
}

Vector<bool>::~Vector()
{
    size_ = -1;
    delete elem_;
}

#endif //MY_VECTOR_TEMPLATES_HPP