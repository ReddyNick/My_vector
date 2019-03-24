#ifndef MY_VECTOR_MY_VECTOR_H
#define MY_VECTOR_MY_VECTOR_H

typedef unsigned long size_t;
typedef int data_t;
class Vector
{
public:

    Vector();
    explicit Vector(int capacity);
    Vector(const Vector& v);
    const Vector& operator=(const Vector& that);
    const Vector& operator=(Vector && that);


    void swap(Vector& copy);
    ~Vector();


    int size() const   { return size_; }
    int capacity() const { return capacity_; }
    bool empty() const  { return size_ == 0; }

    int push_back(data_t item);
    data_t pop();

    int& at(int index);
    data_t& operator[](int index);
    const data_t& operator[](int index) const;

private:
    data_t* data_;
    int capacity_;
    int mincap_;
    int size_;


    int Resize(int how);
    int NewData();
};

void* operator new[](size_t size, const int line, const char* func, const char* inf = "");
void operator delete[](void* p, const int line, const char* func, const char* inf = "");
Vector operator +(const Vector& v1, const Vector& v2);

#endif //MY_VECTOR_MY_VECTOR_H
