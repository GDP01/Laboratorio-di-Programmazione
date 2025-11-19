#include "MyVector.h"
#include <iostream>

void arrayPrint(const double a[], int length, int size) {
    std::cout << "Array: [";
    for (int i = 0; i < length; ++i) {
        std::cout << a[i];

        if (i == (size - 1)) {
            std::cout << "|";
        }

        if (i < (length - 1)) {
            std::cout << ", ";
        } else {
            std::cout << "]" << std::endl;
        }
    }
}

int main() {
    // uso esplicito del template con double
    MyVector<double> a(5);

    a[3] = 2.4;
    std::cout << "a[3] = " << a[3] << std::endl;

    a.push_back(10.5);
    std::cout << "size = " << a.size() << std::endl;

    double last = a.pop_back();
    std::cout << "pop_back() = " << last << ", size = " << a.size() << std::endl;

    return 0;
}
