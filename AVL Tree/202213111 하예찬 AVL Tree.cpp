#include<iostream>
#include<vector>
#include<queue>

using namespace std;

class Node
{
public:
	int key;
	int height;

	Node* left;
	Node* right;

	Node(int key) : key(key), height(1), left(nullptr), right(nullptr) {}
};

int GetHeight(Node* node)
{
	if (node == nullptr)
		return 0;

	return node->height;
}

int GetBalance(Node* node)
{
	if (node == nullptr)
		return 0;

	return GetHeight(node->left) - GetHeight(node->right);
}

void UpdateHeight(Node* node)
{
	node->height = max(GetHeight(node->left), GetHeight(node->right)) + 1;
}

Node* rotate_Left(Node* node)
{
	Node* right = node->right;
	node->right = right->left;
	right->left = node;

	UpdateHeight(node);
	UpdateHeight(right);

	return right;
}

Node* rotate_Right(Node* node)
{
	Node* left = node->left;
	node->left = left->right;
	left->right = node;

	UpdateHeight(node);
	UpdateHeight(left);

	return left;
}

Node* Search(Node* node, int key)
{
	if (node == nullptr || node->key == key)
		return node;

	if (key < node->key)
		return Search(node->left, key);

	return Search(node->right, key);
}


Node* Balance(Node* node)
{
	int balance = GetBalance(node);

	if (balance > 1)
	{
		if (GetBalance(node->left) < 0)
			node->left = rotate_Left(node->left);

		return rotate_Right(node);
	}
	else if (balance < -1)
	{
		if (GetBalance(node->right) > 0)
			node->right = rotate_Right(node->right);

		return rotate_Left(node);
	}

	return node;
}

Node* InsertNode(Node* node, int key, int& nodeCount)
{
	if (node == NULL)
	{
		nodeCount++;
		return new Node(key);
	}

	if (key < node->key)
		node->left = InsertNode(node->left, key, nodeCount);
	else
		node->right = InsertNode(node->right, key, nodeCount);

	UpdateHeight(node);

	return Balance(node);
}

Node* RemoveNode(Node* node, int key, int& nodeCount)
{
	if (node == NULL)
		return NULL;

	if (key < node->key)
		node->left = RemoveNode(node->left, key, nodeCount);
	else if (key > node->key)
		node->right = RemoveNode(node->right, key, nodeCount);
	else
	{
		if (node->left == NULL && node->right == NULL)
		{
			delete node;
			nodeCount--;
			return NULL;
		}
		if (node->left == NULL)
		{
			Node* right = node->right;
			delete node;
			nodeCount--;
			return right;
		}
		if (node->right == NULL)
		{
			Node* left = node->left;
			delete node;
			nodeCount--;
			return left;
		}

		Node* successor = node->right;

		while (successor->left != NULL)
			successor = successor->left;

		node->key = successor->key;
		node->right = RemoveNode(node->right, successor->key, nodeCount);
	}

	UpdateHeight(node);

	return Balance(node);
}

void PrintTreeLevelKeys(Node* root, int& nodeCount)
{
	vector<vector<Node>> res;

	if (root == nullptr)
		return;

	queue<Node*> q;
	q.push(root);

	int count = nodeCount;
	Node* tmp = new Node(-1);

	while (!q.empty() && count > 0)
	{
		int size = q.size();
		vector<Node> v;

		for (int i = 0; i < size; i++)
		{
			Node* front = q.front();
			q.pop();

			if (front->key != -1)
				count--;

			v.push_back(*front);

			if (front->left != nullptr)
				q.push(front->left);
			else
				q.push(tmp);

			if (front->right != nullptr)
				q.push(front->right);
			else
				q.push(tmp);
		}

		res.push_back(v);
	}

	for (int i = 0; i < res.size(); i++)
	{
		for (int j = 0; j < res[i].size(); j++)
		{
			if (res[i][j].key == -1)
				cout << "X  " << "(X, X) ";
			else
			{
				Node* temp = new Node(res[i][j]);

				if (GetBalance(temp) < 0)
					cout << res[i][j].key << " (" << res[i][j].height << ", " << GetBalance(temp) << ") ";
				else
					cout << res[i][j].key << " (" << res[i][j].height << ", " << GetBalance(temp) << ") ";
			}
		}

		cout << endl;
	}
}

int main()
{
	ios::sync_with_stdio(false);
	cin.tie(NULL);
	srand((unsigned)time(NULL));

	Node* root = nullptr;
	int nodeCount = 0;

	int nodes;
	cout << "input node count : ";
	cin >> nodes;

	for (int i = 0; i < nodes; i++)
		root = InsertNode(root, (i + 1) * 10, nodeCount);

	PrintTreeLevelKeys(root, nodeCount);

	RemoveNode(root, 30, nodeCount);
	RemoveNode(root, 40, nodeCount);

	PrintTreeLevelKeys(root, nodeCount);

	cout << "Node remains : " << nodeCount << endl;

	if (Search(root, 50))
		cout << "Key 50 is exist" << endl;
	else
		cout << "Key 30 is not exist" << endl;

	return 0;
}