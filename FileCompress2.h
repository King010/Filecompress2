#pragma once
#include<string>
#include"Heap.hpp"
#include"Huffman.h"
#include<assert.h>

struct FileInfo
{

	std::string _strCode; //�ַ�����
	char _ch;	//��ǰ�ַ�
	size_t _count; //�ַ����ֵĴ���
	FileInfo operator+(const FileInfo&fileInfo)
	{
		FileInfo ret(*this);
		ret._count += fileInfo._count;
		return ret;
	}
	bool operator<(const FileInfo&fileInfo)const
	{
		return _count < fileInfo._count;
	}

	bool operator!=(const FileInfo&fileInfo)const
	{
		return _count != fileInfo._count;
	}
};

class FileCompress
{
public:

	FileCompress()
	{
		memset(_fileInfo, 0, sizeof(_fileInfo));
		for (size_t idx = 0; idx < 256; ++idx)
		{

		}

	}

	FileCompress(const std::string &strFileName)
	{
		memset(_fileInfo, 0, sizeof(_fileInfo));
	}

	void CompressFile(const std::string &strFileName)
	{
		//ͳ����ͬ�ַ����ֵĴ���
		FILE*fOut = fopen(strFileName.c_str(), "r");
		assert(fOut);
		char readBuff[1024];
		while (true)
		{
			size_t readSize=fread(readBuff, 1, 1024, fOut);
			if (0 == readSize)
				break;
			for (size_t idx = 0; idx < readSize; ++idx)
			{
				_fileInfo[readBuff[idx]]._count++;
			}
		}
		HuffmanTree<FileInfo>ht(_fileInfo,sizeof(_fileInfo)) ;
	}
	
	void _GenerateHuffmanCode(HuffmanTreeNode<FileInfo>*pRoot)
	{
		if (pRoot)
		{
			_GenerateHuffmanCode(pRoot->_pLeft );
			_GenerateHuffmanCode(pRoot->_pRight);
			

		}
		if (NULL == pRoot->_pLeft&&NULL == pRoot->_pRight)
		{
			HuffmanTreeNode<FileInfo>* pCur = pRoot;
			//HuffmanTreeNode<FileInfo>* pParent = pCur->_pParent;
			std::string strcode;
		//	while (pParent)
		}
	}

private:
	FileInfo _fileInfo[256];
};

