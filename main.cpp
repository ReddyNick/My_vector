#include <iostream>
#include "My_vector.h"

int main() {

    Vector v1(3);
    Vector v2(3);

    v1[0] = 1; v1[1] = 1; v1[2] = 1;
    v2[0] = 1; v2[1] = 2; v2[2] = 3;

    Vector v3;
    v3 = v1 + v2;

    int size = v3.size();
    for (int i = 0; i < size; i++)
        std::cout << v3[i] << ' ';

    std::cout << std::endl;

    return 0;
}