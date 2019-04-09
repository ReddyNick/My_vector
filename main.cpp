#include <iostream>
#include "My_vector.h"

const int var = 3;

int main() {

    Vector<int> v1(3);
    Vector<bool> vb(10);

    vb[7] = true;
    vb[4] = true;
    vb[3] = true;
    vb[2] = true;

    std::cout << "size = " << vb.size() << std::endl;

    for (int i = 0; i < 10; i++)
        std::cout << i << ' ' << &vb[i] << std::endl;

    Vector<int> v2(3);

    v1[0] = 1; v1[1] = 1; v1[2] = 1;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;

    Vector<int>* v3 = new Vector<int>(5);
    *v3 = v1 + v2;

    int size = v3->size();
    for (int i = 0; i < size; i++)
        std::cout << (*v3)[i] << ' ';

    std::cout << std::endl;

    delete v3;
    return 0;
}