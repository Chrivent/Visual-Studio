#include<iostream>

using namespace std;

template<typename T>
class Node
{
public:
	Node* left;
	T* key1;
	Node* middle;
	T* key2;
	Node* right;
	T* tmp_key;
	Node* tmp_node;

	Node() : left(nullptr), key1(nullptr), middle(nullptr), key2(nullptr), right(nullptr), tmp_key(nullptr), tmp_node(nullptr) {}
};

template<typename T>
class TwoThreeTree
{
private:
	Node<T>* root;

	int height;

	void DevideNode(Node<T>* node)
	{
		if (node->left->tmp_key != nullptr)
		{
			if (node->left->key2 < node->key1)
			{
				node->tmp_key = node->key2;
				node->key2 = node->key1;
				node->key1 = node->left->key2;
			}
			else if (node->left->key2 < node->key2)
			{
				node->tmp_key = node->key2;
				node->key2 = node->left->key2;
			}
			else
				node->tmp_key = node->left->key2;

			node->left->key2 = nullptr;

			node->left
		}
	}

	void Insert_Recursive(T t, Node<T>* node, int tmp_height)
	{
		if (node->key1 == nullptr)
		{
			node->key1 = new T(t);

			return;
		}

		if (node->key2 == nullptr)
		{
			if (t < node->key1)
			{
				node->key2 = node->key1;
				node->key1 = new T(t);
			}
			else
				node->key2 = new T(t);

			return;
		}

		if (tmp_height > height)
		{
			if (t < node->key1)
			{
				node->tmp_key = node->key2;
				node->key2 = node->key1;
				node->key1 = new T(t);
			}
			else if (t < node->key2)
			{
				node->tmp_key = node->key2;
				node->key2 = new T(t);
			}
			else
				node->tmp_key = new T(t);

			return;
		}

		if (t < node->key1)
		{
			if (node->left == nullptr)
				node->left = new Node<T>();

			tmp_height++;

			Insert_Recursive(t, node->left, tmp_height);

			return;
		}

		if (t < node->key2)
		{
			if (node->middle == nullptr)
				node->middle = new Node<T>();

			tmp_height++;

			Insert_Recursive(t, node->middle, tmp_height);

			return;
		}

		if (node->right == nullptr)
			node->right = new Node<T>();

		tmp_height++;

		Insert_Recursive(t, node->right, tmp_height);

		return;
	}

	void DeleteAll()
	{
		DeleteAll_Recursive(root)
	}

	void DeleteAll_Recursive(Node<T>* node)
	{
		if (node->left != nullptr)
			DeleteAll_Recursive(node->left);

		if (key1 != nullptr)
			delete key1;

		if (node->middle != nullptr)
			DeleteAll_Recursive(node->middle);

		if (key2 != nullptr)
			delete key2;

		if (node->right != nullptr)
			DeleteAll_Recursive(node->right);

		delete node;
	}

public:
	TwoThreeTree() : root(nullptr), height(0) {}

	void Insert(T t)
	{
		if (root == nullptr)
		{
			root = new Node<T>();
			root->key1 = new T(t);

			height++:

			return;
		}

		int tmp_height = 1;

		Insert_Recursive(t, root, tmp_height);
		DevideNode(root);
	}
	
	~TwoThreeTree()
	{
		DeleteAll();
	}
};

int main()
{
	TwoThreeTree<int> tree;

	tree.Insert(10);
	tree.Insert(8);
	tree.Insert(7);
	tree.Insert(20);
	tree.Insert(30);
	tree.Insert(50);

	return 0;
}