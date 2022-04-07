#pragma once
#include "pch.h"
#include "Node.hpp"

class AVLTree
{
private:
	AVLNode* _root;

    static AVLNode* maximum_node_of_tree(AVLNode* node)
    {
        if (node->_right_node == nullptr) 
            return node;
        return maximum_node_of_tree(node->_right_node);
    }

    static int sub_tree_height(AVLNode* node)
    {
        return (node != nullptr) ? node->_height + 1 : 0;
    }

    AVLNode* insert_(int key, AVLNode* node)
    {
        if (node == nullptr)
            return node = new AVLNode(key);

        if (key < node->_key)
            node->_left_node = insert_(key, node->_left_node);
    	
        else if (key > node->_key)
            node->_right_node = insert_(key, node->_right_node);
    	
        else if (node->_key == key) 
            return node;

        const int height_L = sub_tree_height(node->_left_node);
        const int height_R = sub_tree_height(node->_right_node);

        node->_height = max(height_L, height_R);

        const int balance_factor = height_L - height_R;

        if (balance_factor > 1)
        {
            if (key < node->_left_node->_key)
                return node = right_rotation(node);
        	
            else
            {
                node->_left_node = left_rotation(node->_left_node);
                return node = right_rotation(node);
            }
        }
        else if (balance_factor < -1)
        {
            if (key < node->_right_node->_key)
            {
                node->_right_node = right_rotation(node->_right_node);
                return node = left_rotation(node);
            }
            else
                return node = left_rotation(node);
        }

        return node;
    }

	AVLNode* remove_(int key, AVLNode* node)
    {
        if (node == nullptr) 
            return nullptr;

        if (key < node->_key)
            node->_left_node = remove_(key, node->_left_node);

        else if (key > node->_key)
            node->_right_node = remove_(key, node->_right_node);
    	
        else // If node->key == key
        {
            if (node->_left_node == nullptr && node->_right_node == nullptr)
            {
                delete node;
                return nullptr;
            }
            else if (node->_left_node == nullptr && node->_right_node != nullptr)
            {
                AVLNode* sub_right_tree = node->_right_node;
                delete node;
                return sub_right_tree;
            }
            else if (node->_left_node != nullptr && node->_right_node == nullptr)
            {
                AVLNode* sub_left_tree = node->_left_node;
                delete node;
                return sub_left_tree;
            }
            else
            {
                AVLNode* maximum_node_in_sub_left_tree = maximum_node_of_tree(node->_left_node);
                node->_key = maximum_node_in_sub_left_tree->_key;
                node->_left_node = remove_(maximum_node_in_sub_left_tree->_key, node->_left_node);
            }
        }

        const int height_L = sub_tree_height(node->_left_node);
        const int height_R = sub_tree_height(node->_right_node);

        node->_height = max(height_L, height_R);

        const int balance_factor = height_L - height_R;

        if (balance_factor > 1)
        {
            if (sub_tree_height(node->_left_node->_left_node) > sub_tree_height(node->_left_node->_right_node))
                return node = right_rotation(node);
        	
            else
            {
                node->_left_node = left_rotation(node->_left_node);
                return node = right_rotation(node);
            }
        }
        else if (balance_factor < -1)
        {
            if (sub_tree_height(node->_right_node->_left_node) > sub_tree_height(node->_right_node->_right_node))
            {
                node->_right_node = right_rotation(node->_right_node);
                return node = left_rotation(node);
            }
            else
                return node = left_rotation(node);
        }

        return node;
    }

    AVLNode* right_rotation(AVLNode* p)
    {
        AVLNode* new_p = p->_left_node;
        p->_left_node = new_p->_right_node;
        new_p->_right_node = p;

        p->_height = max(sub_tree_height(p->_left_node), sub_tree_height(p->_right_node));
        new_p->_height = max(sub_tree_height(new_p->_left_node), sub_tree_height(new_p->_right_node));

        return new_p;
    }

    AVLNode* left_rotation(AVLNode* p)
    {
        AVLNode* new_p = p->_right_node;
        p->_right_node = new_p->_left_node;
        new_p->_left_node = p;

        p->_height = max(sub_tree_height(p->_left_node), sub_tree_height(p->_right_node));
        new_p->_height = max(sub_tree_height(new_p->_left_node), sub_tree_height(new_p->_right_node));

        return new_p;
    }

    void PrintNode(AVLNode*& nodePtr, int currentLevel)
    {
    	if (!nodePtr) return;
        
		std::string spaces(currentLevel * 3, ' ');
        ++currentLevel;
    	
        PrintNode(nodePtr->_right_node, currentLevel);
        std::cout << spaces << nodePtr->_key << std::endl;
        PrintNode(nodePtr->_left_node, currentLevel);
    }

    public:

        AVLTree()
        {
            _root = nullptr;
        }

        ~AVLTree() = default;

        void insert(int key)
        {
            _root = insert_(key, _root);
        }

        void remove(int key)
        {
            _root = remove_(key, _root);
        }

        void display()
         {
            return this->PrintNode(_root, 0);
         }
};