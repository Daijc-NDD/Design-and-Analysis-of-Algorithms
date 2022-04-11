/**
 * @file 1.cpp
 * @author Junchao Dai (3529781875@qq.com)
 * @brief 用分治法实现一组无序序列 的两路合并排序和快速排序。
 *             要求清楚合并排序及快速排序的 基本原理，编程实现分别用这两 种方法将输入的一组无序序列 排序为有序序列后输出。
 * @version 1
 * @date 2022-04-08
 *
 * @copyright Copyright (c) 2022
 *
 */

#include <iostream>
using namespace std;
// 建立可排序列表类
template <class T>
class SortableList {
    private:
        int maxSize;// 最大表厂
        int n;// 线性表实际长度
        T *l;// 动态生成一维数组
        void Merge(int left, int mid, int right);
        void MergeSort(int left, int right);
    public:
        SortableList(int mSize) {// 构造函数，n初始化为0
            maxSize = mSize;
            l = new T[maxSize];
            n = 0;
        }
        ~SortableList() {// 析构函数
            delete []l;
        }
        void initialize(int num,int *list);
        void MergeSort();
        void Show();
};

template <class T>
void SortableList<T>::Show() {
    for (int i = 0; i < n; i++) {
        cout << l[i] << "-";
    }
    cout <<endl;
}

template <class T>
void SortableList<T>::initialize(int num,int *list) {
    for(int i = 0; i < num; i++) {
        l[i] = list[i];
    }
    n = num;
}

// 先写Merge函数
template <class T>
void SortableList<T>::Merge(int left, int mid, int right) {
    T *temp = new T[right-left +1]; // 生成临时数组
    int i = left, j = mid + 1, k = 0;// 生成临时变量
    while ((i <= mid) && (j <= right)) {// 只要两个数组中都有元素没有合并完，就一直比较大小放入临时数组
        if(l[i] <= l[j]) {
            temp[k++] = l[i++];
        }
        else {
            temp[k++] = l[j++];
        }
    }
    while (i <= mid) {// 执行到这里时，至少有一个数组已经没有元素了。就用两个while使得剩下的元素依次放入temp[]即可
        temp[k++] = l[i++];
    }
    while (j<= right) {
        temp[k++] = l[j++];
    }
    for (i = 0, k = left;k <= right;) {
        l[k++] = temp[i++];// 取出临时数组元素
    }
}

// 两路合并排序算法，通过不断的递归划分子序列排序进行分解，再不断合并
template <class T>
void SortableList<T>::MergeSort(int left, int right) {
    if (left < right) {// 递归出口
        int mid = (left + right) / 2;// 划分方法
        MergeSort(left, mid);// 排序左子序列
        MergeSort(mid + 1, right);// 排序右子序列
        Merge(left, mid, right);// 开始合并
    }
}

// 调用合并排序方法
template <class T>
void SortableList<T>::MergeSort() {
    MergeSort(0, n-1);
}



// 主函数main进行使用测试、
int main() {
    SortableList<int> list(20);
    int L[10] = {0,5,8,9,64,35,1,2,4,4};
    list.initialize(10, L);
    list.Show();
    list.MergeSort();
    list.Show();
    return 0;
}
