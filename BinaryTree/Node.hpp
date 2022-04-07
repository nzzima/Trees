#pragma once

template<typename T>
struct Node
{
	T _data;
	Node(T key)
		:_data(key) {}
	Node* _left = nullptr;
	Node* _right = nullptr;
};