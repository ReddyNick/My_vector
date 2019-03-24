#include "My_vector.h"
#include <iostream>
#include "stdio.h"
#include <typeinfo>

const int more = 1;
const int less = 0;
const int INCREASE_RATIO = 2;
const double DECREASE_RATIO = 0.25;

FILE* log = fopen("log.txt", "w");


Vector::Vector():
        data_(nullptr),
        capacity_(0),
        mincap_(0),
        size_(0)
{
    fprintf(log, "'new' in the %d line (function <%s 'nullptr'>)\n", __LINE__, __func__);
}

Vector::Vector(int capacity):
        data_(new(__LINE__, __func__) data_t[capacity]{}),
        capacity_(capacity),
        mincap_(capacity),
        size_(capacity)
{}

Vector::~Vector()
{
    if (this->data_ == nullptr)
        operator delete[] (data_, __LINE__, __func__, " 'nullptr'");
    else
        operator delete[] (data_, __LINE__, __func__);
    data_ = nullptr;
    capacity_ = size_ = -1;
}

int Vector::push_back(data_t item)
{
    if (size_ == capacity_)
            Resize(more);

    data_[size_++] = item;

    return 0;
}

data_t Vector::pop()
{
    if(size_ == 0)
    {
        std::cout << "\nSTACK UNDERFLOW!\n" << std::endl;
        abort();
    }

    data_t item = data_[--size_];

    Resize(less);
    return  item;
}

int Vector::Resize(int how)
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

int Vector::NewData()
{
    data_t* newdata = new(__LINE__, __func__) data_t[capacity_];

    for (int i = 0; i < size_; i++)
        newdata[i] = data_[i];

    data_t* ptr = data_;
    data_ = newdata;

    delete[] ptr;
}

data_t& Vector::at(int index)
{
    if (index < 0 || index >= size_)
    {
        std::cout << "out of range!\n";
        abort();
    }

    return data_[index];
}

data_t& Vector::operator[](int index)
{
    return at(index);
}

const data_t& Vector::operator[](int index) const
{
    if (index < 0 || index >= size_)
    {
        std::cout << "out of range!\n";
        abort();
    }
    return data_[index];
}

Vector::Vector(const Vector &v):
        data_(new(__LINE__, __func__, "(const Vector &v)") data_t[v.size_]),
        size_(v.size_),
        capacity_(v.capacity_),
        mincap_(v.mincap_)
{
    for (int i = 0; i < size_; i++)
        data_[i] = v.data_[i];
}

//const Vector& Vector::operator=(const Vector &that)
//{
//    this-> ~Vector();
//    new(this) Vector(that);
//
//    return *this;
//}

const Vector& Vector::operator=(const Vector &that)
{
    Vector copy (that);
    swap(copy);

    return *this;
}

void Vector::swap(Vector &copy)
{
    std::swap(size_, copy.size_);
    std::swap(data_, copy.data_);
    std::swap(capacity_, copy.capacity_);
    std::swap(mincap_, copy.mincap_);
}

void* operator new[](size_t size, const int line, const char* func, const char* inf)
{
    fprintf(log,"'new' in the %d line (function <%s%s>)\n", line, func, inf);
    return new char[size];
}

void operator delete[](void *p, const int line, const char* func, const char* inf)
{
    fprintf(log,"'delete' in the %d line (function <%s%s>)\n", line, func, inf);
    free(p);
}

Vector operator +(const Vector& v1, const Vector& v2)
{
    Vector result;
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

const Vector& Vector::operator=(Vector &&that)
{
    swap(that);
    return *this;
}
