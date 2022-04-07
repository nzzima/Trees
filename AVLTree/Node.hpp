#pragma once

class AVLNode
{
	friend class AVLTree;

public:
	AVLNode(int key, AVLNode* left_node = nullptr, AVLNode* right_node = nullptr)
	{
		_key = key;
		_left_node = left_node;
		_right_node = right_node;
		_height = 0;
	}
	
private:
	int _key;
	int _height;

	AVLNode* _left_node;
	AVLNode* _right_node;
};