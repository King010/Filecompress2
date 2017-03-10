#define _CRT_SECURE_NO_WARNINGS 1
#pragma once
#include<iostream>
using namespace std;
#include<vector>
#include<assert.h>

template<class T>
class Less
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left <= right;
	}
};
template<class T>
class Greater
{
public:
	bool operator()(const T& left, const T& right)
	{
		return left >= right;
	}
};
template<class T, template<class> class Compare = Less> //ģ���ģ�����
class Heap
{
public:
	Heap()
	{}
	Heap(const T arr[], size_t size)
	{
		//��arr�����ݱ��浽 _heap��
		//_heap.resize(size);
		for (size_t idx = 0; idx < size; ++idx)
		{
			//_heap[idx] = arr[idx];
			_heap.push_back(arr[idx]);
		}

		// �ҵ����һ����Ҷ�ӽ��
		size_t root = (size - 2) / 2;
		for (int idx = root; idx >= 0; idx--)
		{
			_AdjustDown(idx, size);//������
		}
	}
	void Insert(const T data)
		// �� �ǿ�
	{
		_heap.push_back(data);
		size_t size = Size();
		if (size > 1)
		{
			_AdJustUp(size);
		}
	}
	void Remove() //�Ѷ��˵ĺ����һλ������Ȼ��ɾ��
	{
		assert(!Empty());
		size_t size = _heap.size();
		if (size > 1)
		{
			std::swap(_heap[0], _heap[size - 1]);
			_heap.pop_back();
			_AdjustDown(0, size - 1);
		}
		else
		{
			_heap.pop_back();
		}
	}
	bool Empty() const
	{
		return _heap.empty();
	}
	size_t Size()
	{
		return _heap.size();
	}
	T& Top()
	{
		return _heap[0];
	}
	~Heap()
	{}

private:
	// �����¶�
	void _AdjustDown(size_t root, size_t size) //���������ڵ���±꣬�ѵĴ�С
	{
		size_t parent = root;
		size_t child = (parent * 2) + 1; // Ĭ����С����Ϊ����
		while (child < size)
		{
			//�ҵ���С�ĺ��ӽ��,�ж�child+1�Ƿ�Խ��

			if (child + 1 < size && Compare<T>()(_heap[child + 1], _heap[child]))
				//if (child +1 < size && _heap[child + 1] < _heap[child])
			{
				child = child + 1;
			}
			//�ȽϺ��Ӻ�˫�׽��
			if (Compare<T>()(_heap[child], _heap[parent]))
				//if (_heap[child] < _heap[parent])
			{
				std::swap(_heap[child], _heap[parent]);
				parent = child;
				child = child * 2 + 1;
			}
			else
			{
				break;
			}
		}
	}
	void _AdJustUp(size_t size) // ���� ���ϵ�����
	{
		size_t parent = (size - 2) / 2;
		size_t child = size - 1;
		while (child != 0)
		{
			if (Compare<T>()(_heap[child], _heap[parent]))
				//if (_heap[child] < _heap[parent])
			{
				std::swap(_heap[child], _heap[parent]);
				child = parent;
				parent = (child - 1) / 2;
			}
			else
				break;
		}
	}

private:
	std::vector<T> _heap;
};
/*
template<class T,class Compare = Less<T>> //ģ�����
class Heap
{
public:
Heap()
{}
Heap(const T arr[], size_t size)
{
//��arr�����ݱ��浽 _heap��
//_heap.resize(size);
for (size_t idx = 0; idx < size; ++idx)
{
//_heap[idx] = arr[idx];
_heap.push_back(arr[idx]);
}

// �ҵ����һ����Ҷ�ӽ��
size_t root = (size - 2) / 2;
for (int idx = root; idx >= 0; idx--)
{
_AdjustDown(idx, size);//������
}
}
void Insert(const T data)
// �� �ǿ�
{
_heap.push_back(data);
size_t size = Size();
if (size > 1)
{
_AdJustUp(size);
}
}
void Remove() //�Ѷ��˵ĺ����һλ������Ȼ��ɾ��
{
assert(!Empty());
size_t size = _heap.size();
if (size > 1)
{
std::swap(_heap[0], _heap[size - 1]);
_heap.pop_back();
_AdjustDown(0, size - 1);
}
else
{
_heap.pop_back();
}
}
bool Empty() const
{
return _heap.empty();
}
size_t Size()
{
return _heap.size();
}
~Heap()
{}

private:
// �����¶�
void _AdjustDown(size_t root,size_t size) //���������ڵ���±꣬�ѵĴ�С
{
size_t parent = root;
size_t child = (parent * 2) + 1; // Ĭ����С����Ϊ����
while (child < size)
{
//�ҵ���С�ĺ��ӽ��,�ж�child+1�Ƿ�Խ��

if (child + 1 < size && Compare()(_heap[child +1], _heap[child]))
//if (child +1 < size && _heap[child + 1] < _heap[child])
{
child = child + 1;
}
//�ȽϺ��Ӻ�˫�׽��
if (Compare()(_heap[child] , _heap[parent]))
//if (_heap[child] < _heap[parent])
{
std::swap(_heap[child] ,_heap[parent]);
parent = child;
child = child * 2 + 1;
}
else
{
break;
}
}
}
void _AdJustUp(size_t size) // ���� ���ϵ�����
{
size_t parent = (size - 2) / 2;
size_t child = size - 1;
while (child != 0)
{
if (Compare()(_heap[child], _heap[parent]))
//if (_heap[child] < _heap[parent])
{
std::swap(_heap[child], _heap[parent]);
child = parent;
parent = (child - 1) / 2;
}
else
break;
}
}

private:
std::vector<T> _heap;
};
*/
void FunTest()
{
	int arr[] = { 53, 17, 78, 9, 45, 65, 87, 23 };
	//Heap<int> hp(arr,sizeof(arr)/sizeof(arr[0]));
	Heap<int, Less> hp(arr, sizeof(arr) / sizeof(arr[0]));
	hp.Insert(6);
	hp.Remove();
}

