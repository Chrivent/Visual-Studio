#pragma once

#include<iostream>
#include "Node.h"

class BinarySearchTree
{
public:
	Node* Search(Node* node, int key)
	{
		if (node == nullptr)
			return nullptr;
		else if (node->data == key)
			return  node;
		else if (node->data > key)
			return Search(node->left, key);
		else
			return Search(node->right, key);
	}

	Node* Insert(Node* node, int key)
	{
		if (node == nullptr)
			node = new Node(key);
		else if (node->data > key)
			node->left = Insert(node->left, key);
		else
			node->right = Insert(node->right, key);

		return node;
	}

	void Delete(Node* node, int key)
	{
		if (node == nullptr)
			std::cout << "No Record with Such Key";
		else if (node->data > key)
			Delete(node->left, key);
		else if (node->data < key)
			Delete(node->right, key);
		else if (node->data == key)
		{
			if ((node->left == nullptr) && (node->right == nullptr))
			{
				Node* tmp = node;
				node = nullptr;
				delete  tmp;
			}
			else if (node->left == nullptr)
			{
				Node* tmp = node;
				node = node->right;
				delete  tmp;
			}
			else if (node->right == nullptr)
			{
				Node* tmp = node;
				node = node->left;
				delete tmp;
			}
			else
			{
				Node* successor = node->right;

				while (successor->left != nullptr)
					successor = successor->left;

				node->data = successor->data;
				Delete(node->right, successor->data);
			}
		}
	}
};