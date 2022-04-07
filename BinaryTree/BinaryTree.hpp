#pragma once
#include "Node.hpp"


template<typename T>
class BinaryTree
{
public:
	BinaryTree() {}
	
	BinaryTree(Node<T> root)
		:_root(root) {}
	
	 ~BinaryTree() {}
	
	void AddKey(T key)
	{
		AddKey(_root, key);
	}
	
	void DeleteKey(T key)
	{
		auto nodePtr = FindKey(key, _root);
		if (nodePtr != nullptr)
		{
			auto parent = FindParent(key);
			if (nodePtr->_right == nullptr && nodePtr->_left == nullptr)
				(key >= parent->_data) ? parent->_right = nullptr : parent->_left = nullptr;
			else if (nodePtr->_right == nullptr)
				(key >= parent->_data) ? parent->_right = nodePtr->_left : parent->_left = nodePtr->_left;
			else if (nodePtr->_left == nullptr)
				(key >= parent->_data) ? parent->_right = nodePtr->_right : parent->_left = nodePtr->_right;
			else if (nodePtr->_right != nullptr && nodePtr->_left != nullptr)
			{
				auto maxKeyFromLeft = Right(nodePtr->_left)->_data;
				DeleteKey(maxKeyFromLeft);
				nodePtr->_data = maxKeyFromLeft;
			}
		}
	}
	
	bool FindKey(T key)
	{
		if (key == _root->_data)
			return true;
		if (FindKey(key, _root) != nullptr)
			return true;
		return false;
	}
	
	void OutTree(Node<T>* nodePtr = nullptr, int height = 0)
	{
		if (nodePtr == nullptr)
			nodePtr = _root;
		if (nodePtr->_right == nullptr)
		{
			Output(nodePtr->_data, height);
			if (nodePtr->_left != nullptr)
				OutTree(nodePtr->_left, ++height);
			return;
		}

		if (nodePtr->_right != nullptr)
		{
			OutTree(nodePtr->_right, ++height);
			Output(nodePtr->_data, --height);
			if (nodePtr->_left != nullptr)
				OutTree(nodePtr->_left, ++height);
			return;
		}
		return;
	}

private:
	
	void AddKey(Node<T>*& nodePtr, T key)
	{
		if (nodePtr == nullptr)
		{
			nodePtr = new Node<T>(key);
			return;
		}

		if (key < nodePtr->_data)
			AddKey(nodePtr->_left, key);
		else
			AddKey(nodePtr->_right, key);
	}
	
	static void Output(T key, int height)
	{
		for (int i = 0; i < height; ++i)
			std::cout << "   ";
		std::cout << key << std::endl;
	}
	
	Node<T>* FindKey(T key, Node<T>* nodePtr)
	{
		if (nodePtr != nullptr)
		{
			if (key == nodePtr->_data)
				return nodePtr;
			if (key < nodePtr->_data)
				return FindKey(key, nodePtr->_left);
			return FindKey(key, nodePtr->_right);
		}
		return nullptr;
	}
	
	Node<T>* FindParent(T key)
	{
		auto parent = _root;
		auto tree = _root;
		while (tree)
		{
			if (key < tree->_data)
			{
				parent = tree;
				tree = tree->_left;
			}
			else if (key > tree->_data)
			{
				parent = tree;
				tree = tree->_right;
			}
			else
				break;
		}
		if (!tree)
			parent = nullptr;
		return parent;
	}
	
	Node<T>* Right(Node<T>* nodePtr)
	{
		return (nodePtr->_right != nullptr) ? Right(nodePtr->_right) : nodePtr;
	}

	Node<T>* _root;
};

