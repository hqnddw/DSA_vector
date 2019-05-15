//
// Created by hqnddw on 2019/5/15.
//

#include "Vector.h"
#include <iostream>

using namespace std;


//元素复制
template<typename T>
void Vector<T>::copyFrom(T const *A, Rank lo, Rank hi) {
    elem = new T[capacity = 2 * (hi - lo)];
    size = 0;
    while (lo < hi) {
        elem[size++] = A[lo++];
    }
}

//扩容
template<typename T>
void Vector<T>::expand() {
    if (size < capacity) return;
    T *oldelem = elem;
    elem = new T[capacity <<= 1];
    for (int i = 0; i < size; ++i) {
        elem[i] = oldelem[i];
    }
    delete[]oldelem;
}

//缩容
template<typename T>
void Vector<T>::shrink() {
    if (capacity<DEFAULT_CAPACITY<<1) return; //不致收缩到DEFAULT_CAPACITY以下
    if (size > capacity >> 2) return; //以25%为边界
    T *oldelem = elem;
    elem = new T[capacity >>= 1];
    for (int i = 0; i < size; ++i) {
        elem[i] = oldelem[i];
    }
    delete[]oldelem;
}

//重载下标操作符
template <typename T>
T& Vector<T>::operator[](Rank r) const {
    return elem[r];
}