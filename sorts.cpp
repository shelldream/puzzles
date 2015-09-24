/**
    各种排序算法的实现和比较
    Author:Xiaojun Huang
	Date:2015-09-24
*/

#include <iostream>
#include <vector>
#include <time.h>
#include <stdlib.h>
using namespace std;

inline void swap(int& x, int& y)
{
    int tmp = x;
    x = y;
    y = tmp;
}

class QuickSort  //快排
{
public:
    static void sort(vector<int>&);
    static void qsort(vector<int>&, int, int);
    static int Partition1(vector<int>&, int, int);
    static int Partition2(vector<int>&, int, int);
};

void QuickSort::sort(vector<int>& nums)
{
    int n = nums.size()-1;
    qsort(nums, 0, n);
}

void QuickSort::qsort(vector<int>& nums, int low, int high)
{
    if(low < high)
    {
        //int privot_loc = Partition1(nums, low, high);
        int privot_loc = Partition1(nums, low, high);
        qsort(nums, low, privot_loc-1);
        qsort(nums, privot_loc+1, high);
    }
}

int QuickSort::Partition1(vector<int>& nums, int low, int high)
{
    int privotkey = nums[low];
    while(low < high)
    {
        while(low < high && nums[high] > privotkey) high--;
        nums[low] = nums[high];
        while(low < high && nums[low] <= privotkey) low++;
        nums[high] = nums[low];
    }
    nums[low] = privotkey;
    return low;
}

/**
    partition函数《算法导论》中实现版本

*/
int QuickSort::Partition2(vector<int>& nums, int low, int high)
{
    int privot_loc = low-1;
    for(int i = low;i < high;i++)
    {
        if(nums[i] <= nums[high])  //轴元素为末尾元素
            swap(nums[++privot_loc], nums[i]);
    }
    swap(nums[++privot_loc], nums[high]);
    return privot_loc;
}

class HeapSort //堆排;大顶堆
{
public:
    static void sort(vector<int>&);
    static void swim(vector<int>& ,int);
    static void sink(vector<int>&, int, int);
};

void HeapSort::swim(vector<int>& nums, int i)
{
    int j = i+1; //元素在堆中的下标
    while(j/2)
    {
        if(nums[j/2-1] < nums[j-1])
        {
            swap(nums[j/2-1], nums[j-1]);
            j /= 2;
        }
        else break;
    }
}

void HeapSort::sink(vector<int>& nums, int i, int heap_cap)
{
    int j = i+1;
    while(j-1 <= heap_cap-1)
    {
        int max_index = 2*j;
        if(max_index > heap_cap)
            return;
        if(max_index+1 <= heap_cap && nums[max_index-1] < nums[max_index])
            max_index++;
        if(nums[j-1] < nums[max_index-1])
        {
            swap(nums[j-1], nums[max_index-1]);
            j = max_index;
        }
        else return;
    }
}

void HeapSort::sort(vector<int>& nums)
{
    int n = nums.size()-1;
    for(int i = 0;i <= n;i++)  //大顶堆建堆过程
    {
        swim(nums,i);
    }
    int heap_cap = n+1;
    for(int i = n;i >= 0;i--)
    {
        swap(nums[0],nums[i]);
        heap_cap--;
        sink(nums, 0, heap_cap);
    }
}

class MergeSort//归并排序
{
public:
    static void sort(vector<int>&);
    static void sort(vector<int>&, vector<int>&, int, int);
    static void merge(vector<int>&, vector<int>& ,int, int);
};

void MergeSort::sort(vector<int>& nums, vector<int>& aux, int low, int high)
{
    if(low >= high)
        return;
    int mid = (low+high)/2;
    sort(nums, aux, low, mid);
    sort(nums, aux, mid+1, high);
    merge(nums, aux, low, high);
}

void MergeSort::merge(vector<int>& nums, vector<int>& aux, int low, int high)
{
    for(int k = low;k <= high;k++)
        aux[k] = nums[k];
    int i = low;
    int mid = (low+high)/2;
    int j = mid+1;
    for(int k = low;k <= high;k++)
    {
        if(i > mid)
            nums[k] = aux[j++];
        else if(j > high)
            nums[k] = aux[i++];
        else if(aux[i] > aux[j])
            nums[k] = aux[j++];
        else nums[k] = aux[i++];
    }
}

void MergeSort::sort(vector<int>& nums)
{
    int n = nums.size();
    vector<int> aux(n,0);
    sort(nums, aux, 0, n-1);
}



int main()
{
    const int N = 1000;//总共要排序数字的数目
    vector<int> test;
    int a = 0;
	int b = 100;  // a和b是生成随机数的上下界
	srand((unsigned)time(NULL));
	for(int i = 0;i < N;i++)
		test.push_back((rand() % (b-a+1))+ a);
    MergeSort::sort(test);
    for(int i = 0;i < N;i++)
        cout<<test[i]<<"  ";
    cout<<endl;
}
