#pragma once

template<typename T>
struct Node
{
	Node(T data)
		: _data(data), _left(nullptr), _right(nullptr)
	{}

	T _data;
	Node* _left = nullptr;
	Node* _right = nullptr;
};