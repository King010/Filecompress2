#pragma once
#include"Heap.hpp"
#include<queue>

template<class T>
struct HuffmanTreeNode
{
	HuffmanTreeNode(const T& data)
	: _pLeft(NULL)
	, _pRight(NULL)
	, _pParent(NULL)
	, _weight(data)
	{}
	HuffmanTreeNode<T>* _pLeft;
	HuffmanTreeNode<T>* _pRight;
	HuffmanTreeNode<T>* _pParent;
	T _weight;
};
template<class T>
struct Compare
{
public:
	bool operator()(const T pLeft, const T pRight)
	{
		return pLeft->_weight < pRight->_weight;
	}
};

template<class T>
class HuffmanTree
{
public:
	HuffmanTree()
		:_pRoot(NULL)
	{}
	HuffmanTree(const T *arr, size_t size, const T& invalid)
	{
		_pRoot = _CreateHuffmanTree(arr, size,invalid);
	}
	void LevelOrder()
	{
		if (NULL == _pRoot)
			return;
		HuffmanTreeNode<T>* pCur = _pRoot;
		queue<HuffmanTreeNode<T>*> q;
		q.push(_pRoot);
		while (!q.empty())
		{
			pCur = q.front();
			cout << pCur->_weight << " ";
			if (pCur->_pLeft)
				q.push(pCur->_pLeft);
			if (pCur->_pRight)
				q.push(pCur->_pLeft);
			q.pop();
		}

	}
	~HuffmanTree()
	{
		_DestoryTree(_pRoot);
	}

	HuffmanTreeNode<T>* GetRoot()
	{
		return _pRoot;
	}

private:
	HuffmanTreeNode<T>* _CreateHuffmanTree(const T arr[], size_t size, const T& invalid)
	{

		Heap<HuffmanTreeNode<T>*, Compare> hp;
		for (size_t idx = 0; idx < size; ++idx)
		{
			if (arr[idx]!=invalid)
			{
				hp.Insert(new HuffmanTreeNode<T>(arr[idx]));
			}
		}
		if (0 == hp.Size())
		{
			return NULL;
		}
		while (hp.Size() >1)
		{
			//堆中取权值最小的两个
			HuffmanTreeNode<T>* pLeft = hp.Top();
			hp.Remove();
			HuffmanTreeNode<T>* pRight = hp.Top();
			hp.Remove();

			HuffmanTreeNode<T>* parent = new HuffmanTreeNode<T>(pLeft->_weight + pRight->_weight);
			parent->_pLeft = pLeft;
			parent->_pLeft->_pParent = parent;
			parent->_pRight = pRight;
			parent->_pRight->_pParent = parent;
			hp.Insert(parent);
		}
		return hp.Top();
	}

	void _DestoryTree(HuffmanTreeNode<T>*& pRoot)
	{
		if (pRoot)
		{
			_DestoryTree(pRoot->_pLeft);
			_DestoryTree(pRoot->_pRight);
			delete pRoot;
			pRoot = NULL;
		}
	}
private:
	HuffmanTreeNode<T>* _pRoot;
};

