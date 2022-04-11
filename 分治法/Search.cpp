/**
 * @file Search.cpp
 * @author Junchao Dai (b20070433@njupt.edu.cn)
 * @brief       1.采用基于“五元中值组取中 值 分 割 法 ” （ median-of-median-of-five partitioning）的线性时间选择算 法，
 *                    找出 N 个元素集合 S 中的 第 k 个最小的元素，使其在线性 时间内解决。
 *                    2. 五元中值组取中值分割法即将N个元素分成每5个元素一组，运用8次比较找出每组的中值，得到约（N/5）个中值组，
 *                   再对中值组调用分割的快速选择算法，直至找到第k小的元素。
 *                    3.快速选择算法以快速排序算法为基础，特别适合topK算法
 * @version 0.1
 * @date 2022-04-11
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
        int Partition(int left, int right);
        void QuickSearch(int left, int right, int k);
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
        void Show();
        void Show(int index) {
            cout << l[index];
        }
        void Swap(int i, int j) {
            int temp;
            temp = l[i];
            l[i] = l[j];
            l[j] = temp;
        }
        void QuickSearch(int k ) {
            QuickSearch(0, n-1, k);
        }
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

template <class T>
int SortableList<T>::Partition(int left, int right) {
    int i = left, j = right +1;
    do {
        do {
            i++;
        }while(l[i] < l[left]);
        do {
            j--;
        }while(l[j] > l[left]);
        if(i < j) {
            Swap(i, j);
        }
    }while(i<j);
    Swap(left, j);
    return j;
}

template <class T>// TopK算法，我们只关心是否在k之前的序列中的元素都比k号元素大，是否在k之后的序列中的元素都比k号元素小，而不关心两个序列中的具体情况
void SortableList<T>::QuickSearch(int left, int right, int k) {
    int j = Partition(left, right);
    if(j < k) {
        QuickSearch(j+1, right, k);
    }
    if (j >k) {
        QuickSearch(left, j-1, k);
    }
}

// 主函数main进行使用测试、
int main() {
    SortableList<int> list(20);
    int L[10] = {0,5,8,9,64,35,1,2,4,4};
    list.initialize(10, L);
    list.Show();
    int k;//  假设求n个数中第k大
    cout << "你要找第几大？";
    cin >> k;
    int K = 10 - k +1;// 即求第n-k+1小
    list.QuickSearch(K-1);
    list.Show();
    list.Show(K-1);
    return 0;
}
