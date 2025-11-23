#include "../include/MyVector.h"
#include <algorithm>

//===== Costruttore =====//
template <typename T>
MyVector<T>::MyVector(int dimension) {
    if (dimension < 0) throw Invalid();
    sz = dimension;
    true_sz = dimension;
    reserved = 0;
    array = new T[dimension];
}

//===== Distruttore =====//
template <typename T>
MyVector<T>::~MyVector() {
    delete[] array;
}

//===== Secure set & Secure get =====//
template <typename T>
void MyVector<T>::safe_set(int index, const T& value) {
    if(index >= 0 && index < sz){
        array[index] = value;
    } else {
        throw Invalid();
    }
}

template <typename T>
T MyVector<T>::safe_get(int index) const {
    if(index >= 0 && index < sz)
        return array[index];
    
    throw Invalid();
}

template <typename T>
T& MyVector<T>::safe_get_reference(int index) {
	if(index >= 0 && index < sz)
        return array[index];
    
    throw Invalid();
}

//===== Private function =====//
template <typename T>
void MyVector<T>::resize(int dim) {
    if (dim <= 0) throw Invalid();
    T* t = new T[dim];
    std::copy(array, array + sz, t);
    delete[] array;
    array = t;
    true_sz = dim;
}

//===== Overload operatore [] =====//
template <typename T>
T MyVector<T>::operator[](int index) const {
	return array[index];
}

template <typename T>
T& MyVector<T>::operator[](int index) {
    return array[index];
}

//===== Funzione at() =====//
template <typename T>
T MyVector<T>::at(int index) const {
	return safe_get(index);
}

template <typename T>
T& MyVector<T>::at(int index) {
	return safe_get_reference(index);
}

//===== push_back() =====//
template <typename T>
void MyVector<T>::push_back(const T& value) {
	if (true_sz == sz) {
		true_sz = true_sz * 2;
		resize(true_sz);
	}
	sz++;
	safe_set(sz - 1, value);
}

//===== pop_back() =====//
template <typename T>
T MyVector<T>::pop_back() {
    if (sz == 0) throw Invalid();
	T el = safe_get(sz - 1);
	if (true_sz/3 == sz && true_sz/3 > reserved) {
		true_sz = true_sz/2;
		resize(true_sz);
	}
	sz--;
	return el;
}

//===== reserve() =====//
template <typename T>
void MyVector<T>::reserve(int n) {
    if (n < 0) throw Invalid();
    if (true_sz < n) resize(n);
    reserved = n;
}
