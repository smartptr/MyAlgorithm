/*
 * content: 小根堆模版;
 * author：czg1989
 * time：2012-3-18
*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
using namespace std;

const int m = 5e2;

template < class T >
class MinHeap
{
private:
  T* heapArray;	  //存放堆数据的数组;
	int currentSize;  //当前堆中元素数目;
	int maxSize;	  //堆所容纳的元素的最大数目;
	void swap(int& pos_x, int& pos_y);	 //交换x和y位置的元素;
	void BuildHeap();
public:
	MinHeap(const int n); //n为初始化堆的最大容量;
	virtual ~MinHeap() { delete[] heapArray; }
	bool isLeaf( int pos ) const;   //判断叶子节点；
	int leftChild( int pos ) const; //左孩子位置；
	int rightChild( int pos ) const;
	int parent( int pos ) const;
	bool Remove(int pos, T& node);//删除给定下标的元素;
	bool Insert(const T& node);
	T& RemoveMin(); //从堆顶删除最小值;
	void ShitUp(int pos);
	void ShitDown(int pos);
};

template < class T >
MinHeap<T>::MinHeap( const int n )
{
	if ( n <= 0 )
		return ;
	currentSize = 0;
	maxSize = n;
	heapArray = new T[maxSize];
	BuildHeap();
}

template< class T >
void MinHeap<T>::swap(int& x, int& y)
{
	std::swap(x, y);
}

template< class T >
bool MinHeap<T>::isLeaf( int pos ) const
{
	return ( pos >= currentSize/2 && pos < currentSize );
}

template< class T >
void MinHeap<T>::BuildHeap()
{
	for ( int i = currentSize/2; i >= 0; --i )
	{
		ShitDown(i);
	}
};

template< class T >
int MinHeap<T>::leftChild( int pos ) const
{
	return (pos<<1) + 1;
}

template< class T >
int MinHeap<T>::rightChild( int pos ) const
{
	return (pos<<1) + 2;
};

template< class T >
int MinHeap<T>::parent( int pos ) const
{
	return (pos-1)/2;
}

template< class T >
bool MinHeap<T>::Insert(const T& node)
{
	if ( currentSize == maxSize )
	{
		return false;
	}
	heapArray[currentSize] = node;
	ShitUp(currentSize);
	currentSize++;
}

template< class T >
void MinHeap<T>::ShitUp(int pos)
{
	int tmpPos = pos;
	T temp = heapArray[tmpPos];
	while((tmpPos>0)&&heapArray[parent(tmpPos)]>temp)
	{
		heapArray[tmpPos] = heapArray[parent(tmpPos)];
		tmpPos = parent(tmpPos);
	}
	heapArray[tmpPos] = temp;
}

template< class T >
T& MinHeap<T>::RemoveMin()
{
	if ( currentSize == 0)
	{
		exit(1);
	}
	swap(heapArray[0], heapArray[--currentSize]);
	if ( currentSize > 1)
	{
		ShitDown(0);
	}
	return heapArray[currentSize];
}

template< class T >
bool MinHeap<T>::Remove(int pos, T& node)
{
	if ( pos < 0 || pos >= currentSize)
		return false;
	T temp = heapArray[pos];
	heapArray[pos] = heapArray[--currentSize];
	ShitUp(pos);
	ShitDown(pos);
	node = temp;
	return true;
}

template< class T >
void MinHeap<T>::ShitDown(int pos)
{
	int i = pos;
	int j = leftChild(i);
	T temp = heapArray[i];
	while ( j < currentSize )
	{
		if( j < currentSize-1 && heapArray[j] > heapArray[j+1] )
			++j;
		if ( temp > heapArray[j] )
		{
			heapArray[i] = heapArray[j];
			i = j;
			j = leftChild(j);
		}
		else
			break;
	}
	heapArray[i] = temp;
}

int main()
{
    cout<<m<<endl;
	int a[]={12,3,2,43,54,32,154,21,1};
	int n=sizeof(a)/sizeof(int);
	//MinHeap<int> *heap = new MinHeap<int>(n);
	MinHeap<int> heap(n);
	for(int i=0;i<n;i++)
		heap.Insert(a[i]);
	for ( int i = 0; i < n; ++i )
	{
		cout<<heap.RemoveMin()<<endl;
	}
	system("pause");
	return 0;
}
