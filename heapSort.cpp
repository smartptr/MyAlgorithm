// 堆排序，利用大顶堆进行升序排列
#include <iostream>
#include <cstdio>
#include <cstring>
using namespace std;

//从0开始
int parent(int i)
{
    return (i-1)/2;
}

int left(int i)
{
    return i*2+1;
}

int right(int i)
{
    return i*2+2;
}

void max_heapfix(int A[], int i, int size)
{
    int index = i;
    int lt = left(index);
    int temp = A[index];
    while(lt < size)
    {
        if(lt < size - 1 && A[lt] < A[lt+1])
            ++lt;
        if(temp < A[lt])
        {
            swap(A[index], A[lt]);
            index = lt;
            lt = left(index);
        }
        else
            break;
    }
}

void BuildHeap(int A[], int len)
{
    for(int i = (len-2)/2; i >= 0; --i)
    {
        max_heapfix(A, i, len);
    }
}

void print(int A[], int len)
{
    for(int i = 0; i < len; ++i)
        cout << A[i] << " ";
    cout << endl;
}

void HeapSort(int A[], int len)
{
    BuildHeap(A, len);
    print(A, len);
    for(int i = len-1; i >= 0; --i)
    {
        std::swap(A[0], A[i]);
        max_heapfix(A, 0, i);
    }
    print(A, len);
}

int main()
{
    const int len = 13;
    int A[] = {19, 1, 10, 14, 16, 4, 7, 9, 3, 2, 8, 5, 11};
    HeapSort(A, len);
    return 0;
}
