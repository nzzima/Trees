#pragma once
#include "Node.hpp"


template<typename Type>
class OptimalBinaryTree
{
public:
	struct Matrix_of_Elements
	{
		Type key;
		int length;
		int sumWeight;
	};

	OptimalBinaryTree(Type* k, int keyCount, int* p, int pCount, int* q)
	{
		SetMatrix(k, keyCount, p, pCount, q);
		int rootInd = 0;
		while (true)
		{
			if (k[rootInd] == _matrix[0][keyCount - 1].key)
				break;
			++rootInd;
		}
		_root = new Node<Type>(_matrix[0][keyCount - 1].key);
		AddNode(_root, k, 0, rootInd - 1, rootInd + 1, keyCount - 1);
	}
	
	~OptimalBinaryTree()
	{
		if (_root != nullptr)
			RemoveNode(_root);

		for (int i = 0; i < _keyCount; ++i)
			delete[] _matrix[i];

		delete[] _matrix;
	}
	
	Node<Type>* Search(Type key)
	{
		return SearchNode(_root, key);
	}
	
	void PrintTree()
	{
		return this->PrintNode(_root, 0);
	}
	
	void RemoveNode(Node<Type>*& root)
	{
		if (root != nullptr)
		{
			RemoveNode(root->_left);
			RemoveNode(root->_right);
			delete root;
		}
	}
	
	void SetMatrix_of_Elementsent(int a, int b, int* p, int* q)
	{
		int T = 0, minT = INT_MAX;
		for (int i = a; i <= b; ++i)
			_matrix[a][b].sumWeight += p[i] + q[i];

		_matrix[a][b].sumWeight += q[b + 1];

		for (int curRoot = a; curRoot <= b; ++curRoot)
		{
			T = 0;
			if (curRoot > 0)
				T += _matrix[a][curRoot - 1].length + _matrix[a][curRoot - 1].sumWeight;
			if (curRoot < _keyCount - 1)
				T += _matrix[curRoot + 1][b].length + _matrix[curRoot + 1][b].sumWeight;

			if (T < minT)
			{
				_matrix[a][b].key = _matrix[curRoot][curRoot].key;
				_matrix[a][b].length = T;
				minT = T;
			}
		}
	}
	
	void SetMatrix(Type* k, int keyCount, int* p, int pCount, int* q)
	{
		_matrix = new Matrix_of_Elements * [keyCount];
		_keyCount = keyCount;
		for (int i = 0; i < keyCount; ++i)
			_matrix[i] = new Matrix_of_Elements[keyCount];

		for (int i = 0; i < keyCount; ++i)
		{
			for (int j = 0; j < keyCount; ++j)
			{
				_matrix[i][j].key = i == j ? k[i] : 0;
				_matrix[i][j].length = 0;
				_matrix[i][j].sumWeight = i == j ? p[i] + q[i] + q[i + 1] : 0;
			}
		}

		for (int j = 1; j < keyCount; ++j)
		{
			for (int i = 0; i + j < keyCount; ++i)
				SetMatrix_of_Elementsent(i, i + j, p, q);
		}
	}
	
	void AddNode(Node<Type>* curNode, Type* k, int leftBegin, int leftEnd, int rightBegin, int rightEnd)
	{
		if (leftBegin >= 0 && leftEnd < _keyCount && leftBegin < _keyCount && leftEnd >= 0 && leftBegin <= leftEnd)
		{
			Node<Type>* leftNode = new Node<Type>(_matrix[leftBegin][leftEnd].key);
			curNode->_left = leftNode;
			int leftNodeInd = 0;
			while (true)
			{
				if (k[leftNodeInd] == _matrix[leftBegin][leftEnd].key)
					break;
				++leftNodeInd;
			}
			AddNode(leftNode, k, leftBegin, leftNodeInd - 1, leftNodeInd + 1, leftEnd);
		}

		if (rightBegin >= 0 && rightEnd < _keyCount && rightBegin < _keyCount && rightEnd >= 0 && rightBegin <= rightEnd)
		{
			Node<Type>* rightNode = new Node<Type>(_matrix[rightBegin][rightEnd].key);
			curNode->_right = rightNode;
			int rightNodeInd = 0;
			while (true)
			{
				if (k[rightNodeInd] == _matrix[rightBegin][rightEnd].key)
					break;
				++rightNodeInd;
			}
			AddNode(rightNode, k, rightBegin, rightNodeInd - 1, rightNodeInd + 1, rightEnd);
		}
	}
	
	void PrintNode(Node<Type>*& nodePtr, int currentLevel)
	{
		if (!nodePtr)
			return;

		std::string spaces(currentLevel * 3, ' ');
		++currentLevel;
		PrintNode(nodePtr->_right, currentLevel);
		std::cout << spaces << nodePtr->_data << std::endl;
		PrintNode(nodePtr->_left, currentLevel);
	}
	
	Node<Type>* SearchNode(Node<Type>*& nodePtr, Type& key)
	{
		if (nodePtr == nullptr)
			return nodePtr;

		Node<Type>* leftInd = nullptr;
		leftInd = SearchNode(nodePtr->_left, key);
		if (leftInd != nullptr)
			return leftInd;
		return nodePtr->_data == key ? nodePtr : SearchNode(nodePtr->_right, key);
	}
	
private:
	Node<Type>* _root;
	int _keyCount;
	Matrix_of_Elements** _matrix;
};


