//
// Created by hqnddw on 2019/5/15.
//

#ifndef DSA_VECTOR_H
#define DSA_VECTOR_H


typedef int Rank;
#define DEFAULT_CAPACITY 3

template<typename T>
class Vector {
protected:
    Rank size; //规模
    int capacity; //容量
    T *elem;  //数据区

    void copyFrom(T const *A, Rank lo, Rank hi); //复制区间数组A[lo, hi)

    void expand();  //空间不足时扩容

    void shrink();  //装填因子过小时压缩

    bool bubble(Rank lo, Rank hi);  //扫描交换

    void bubbleSort(Rank lo, Rank hi); //冒泡排序算法

    Rank max(Rank lo, Rank hi);  //选取最大元素

    void selectionSort(Rank lo, Rank hi);  //选择排序算法

    void merge(Rank lo, Rank mi, Rank hi);  //归并算法

    void mergeSort(Rank lo, Rank hi);  //归并排序算法

public:
    //构造函数
    Vector(int c = DEFAULT_CAPACITY, int s = 0, T v = 0) { //容量为c，规模为s，初始元素为v
        elem = new T[capacity = c];
        for (size = 0; size < s; elem[size++] = v); //s<=c
    }

    Vector(T const *A, Rank lo, Rank hi) {
        copyFrom(A, lo, hi);  //数组区间复制
    }

    Vector(T const *A, Rank n) {
        copyFrom(A, 0, n);    //数组整体复制
    }

    Vector(Vector<T> const &V, Rank lo, Rank hi) {
        copyFrom(V.elem, lo, hi);  //向量区间复制
    }

    Vector(Vector<T> const &V) {
        copyFrom(V.elem, 0, V.size); //向量整体复制
    }

    //析构函数
    ~Vector() { delete[] elem; };

    //只读访问接口
    Rank getSize() const {
        return size; //返回规模大小
    }

    bool isEmpty() const {
        return !size; //判断向量是否为空
    }

    bool isOrdered() const; //判断是否有序

    Rank find(T const &e) const {
        return find(e, 0, (Rank) size); //无序向量整体查找
    }

    Rank find(T const &e, Rank lo, Rank hi) const;  //无序向量区间查找

    Rank search(T const &e) const {
        return (size <= 0) ? -1 : search(e, (Rank) 0, (Rank) size); //有序向量整体查找
    }

    Rank search(T const &e, Rank lo, Rank hi) const; //有序向量区间查找

    //可写访问接口
    T &operator[](Rank r) const;
    T remove(Rank r); //删除单个元素
    int remove(Rank lo, Rank hi);  //删除区间元素
    Rank insert(Rank r, T const &e); //插入元素
    Rank insert(T const &e) {
        return insert(e, size); //向量尾部插入元素
    }

    void sort(Rank lo, Rank hi);  //区间排序
    void sort() {
        sort(0, size); //整体排序
    }

    int deduplicate();  //无序去重
    int uniquify();  //有序去重
};

#endif //DSA_VECTOR_H
