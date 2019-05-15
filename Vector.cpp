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
    if (capacity < DEFAULT_CAPACITY << 1) return; //不致收缩到DEFAULT_CAPACITY以下
    if (size > capacity >> 2) return; //以25%为边界
    T *oldelem = elem;
    elem = new T[capacity >>= 1];
    for (int i = 0; i < size; ++i) {
        elem[i] = oldelem[i];
    }
    delete[]oldelem;
}

//重载下标操作符
template<typename T>
T &Vector<T>::operator[](Rank r) const {
    return elem[r];
}

//无序向量查找
template<typename T>
Rank Vector<T>::find(const T &e, Rank lo, Rank hi) const { //assert：0<lo<=hi<=size
    while ((lo < hi--) && elem[hi] != e); //同时有多个命中元素时，返回秩最大者
    return hi; //若hi<lo,则查找失败，否则hi即命中的秩
}

//有序向量查找
template<typename T>
Rank Vector<T>::search(const T &e, Rank lo, Rank hi) const {
    while (lo < hi) {
        Rank mi = (lo + hi) >> 1;
        if (e < elem[mi]) mi = hi;
        else if (e > elem[mi]) lo = mi + 1;
        else return mi;
    }
    return -1;
}

//插入
template<typename T>
Rank Vector<T>::insert(Rank r, const T &e) { //assert:0<=r<size
    expand(); //如有必要，扩容
    for (Rank i = size; i > r; i--) elem[i] = elem[i - 1];
    elem[r] = e;
    size++;
    return r;
}

//区间删除
template<typename T>
int Vector<T>::remove(Rank lo, Rank hi) { //删除区间[lo, hi)
    if (lo == hi) return 0;
    while (hi < size) {
        elem[lo++] = elem[hi++];
    }
    size = size - hi + lo;
    shrink(); // 如有必要，则缩容
    return hi - lo;
}

//单个元素删除
template<typename T>
T Vector<T>::remove(Rank r) {
    T e = elem[r];
    remove(r, r + 1);
    return e; //返回被删除的元素
}

//无序去重
template<typename T>
int Vector<T>::deduplicate() {
    Rank oldsize = size;
    Rank i = 1;
    while (i < size) {
        (find(elem[i], 0, i) < 0) ?
        i++ : remove(i); //remove会维护现在的size
    }
    return oldsize - size;
}

//有序性甄别
template<typename T>
int Vector<T>::disordered() const {
    int n = 0;
    for (int i = 1; i < size; ++i) {
        if (elem[i - 1] > elem[i]) n++;
    }
    return n;
}


//有序去重
template<typename T>
int Vector<T>::uniquify() {
    int i = 0, j = 0;
    while (++j < size)
        if (elem[i] != elem[j])
            elem[++i] = elem[j];
    size = ++i;
    shrink();
    return j - i; //返回删除元素总数
}

//遍历
template<typename T>
void Vector<T>::traverse() {
    for (int i = 0; i < size; ++i) {
        cout << elem[i] << " ";
    }
    cout << endl;
}

int main() {
    int a[] = {1, 2, 3, 4, 5, 6, 7, 8};
    Vector<int> v(a, 0, 7);
    v.traverse();
    cout << v.getSize() << endl;
    cout << v.search(4) << endl;
    v.insert(0,1);
    v.insert(3,7);
    v.traverse();
    v.deduplicate();
    v.traverse();
    v.remove(2,4);
    v.traverse();
}