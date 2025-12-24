#ifndef MYVECTOR_H
#define MYVECTOR_H

#include "../include/misura.h"

template <typename T>
class MyVector {
    class Invalid{};

public:
    MyVector(int dimension);
    ~MyVector();

    T& operator[](int index);
    T operator[](int index) const;

    void safe_set(int index, const T& value);
    T safe_get(int index) const;
        
    T at(int index) const;
    T& at(int index);

    void push_back(const T& value);
    T pop_back();

    void reserve(int n);

    int size() const { return sz; };

private:
    T *array = nullptr;
    int true_sz;
    int reserved;
    int sz;

    void resize(int dim);
    T& safe_get_reference(int position);
};

// Istanziazioni esplicite per i tipi usati
template class MyVector<double>;
template class MyVector<misura>;

#endif
