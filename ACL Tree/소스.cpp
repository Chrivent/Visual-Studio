#include <iostream>

using namespace std;

struct Node {
    int key;
    int height;
    Node* left;
    Node* right;

    Node(int key) {
        this->key = key;
        this->height = 1;
        this->left = NULL;
        this->right = NULL;
    }
};

int get_height(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return node->height;
}

int get_balance(Node* node) {
    if (node == NULL) {
        return 0;
    }
    return get_height(node->left) - get_height(node->right);
}

void update_height(Node* node) {
    node->height = max(get_height(node->left), get_height(node->right)) + 1;
}

Node* rotate_left(Node* node) {
    Node* right = node->right;
    node->right = right->left;
    right->left = node;
    update_height(node);
    update_height(right);
    return right;
}

Node* rotate_right(Node* node) {
    Node* left = node->left;
    node->left = left->right;
    left->right = node;
    update_height(node);
    update_height(left);
    return left;
}

Node* balance(Node* node) {
    int balance_factor = get_balance(node);
    if (balance_factor > 1) {
        if (get_balance(node->left) < 0) {
            node->left = rotate_left(node->left);
        }
        return rotate_right(node);
    }
    else if (balance_factor < -1) {
        if (get_balance(node->right) > 0) {
            node->right = rotate_right(node->right);
        }
        return rotate_left(node);
    }
    return node;
}

Node* insert(Node* node, int key) {
    if (node == NULL) {
        return new Node(key);
    }
    if (key < node->key) {
        node->left = insert(node->left, key);
    }
    else {
        node->right = insert(node->right, key);
    }
    update_height(node);
    return balance(node);
}

Node* remove(Node* node, int key) {
    if (node == NULL) {
        return NULL;
    }
    if (key < node->key) {
        node->left = remove(node->left, key);
    }
    else if (key > node->key) {
        node->right = remove(node->right, key);
    }
    else {
        if (node->left == NULL && node->right == NULL) {
            delete node;
            return NULL;
        }
        if (node->left == NULL) {
            Node* right = node->right;
            delete node;
            return right;
        }
        if (node->right == NULL) {
            Node* left = node->left;
            delete node;
            return left;
        }
        Node* successor = node->right;
        while (successor->left != NULL) {
            successor = successor->left;
        }
        node->key = successor->key;
        node->right = remove(node->right, successor->key);
    }
    update_height(node);
    return balance(node);
}

// AVL 트리에서 특정 key 값을 가진 노드를 찾는 함수
Node* search(Node* node, int key) {
    if (node == NULL || node->key == key) {
        return node;
    }
    if (key < node->key) {
        return search(node->left, key);
    }
    else {
        return search(node->right, key);
    }
}

void inorder(Node* node) {
    if (node != NULL) {
        inorder(node->left);
        cout << node->key << " ";
        inorder(node->right);
    }
}

int main() {
    Node* root = NULL;

    root = insert(root, 10);
    root = insert(root, 20);
    root = insert(root, 30);
    root = insert(root, 40);
    root = insert(root, 50);
    root = insert(root, 25);

    cout << "AVL tree after insertions: ";
    inorder(root);
    cout << endl;

    root = remove(root, 30);
    root = remove(root, 40);

    cout << "삭제 후 AVL tree: ";
    inorder(root);
    cout << endl;

    Node* node = search(root, 20);
    if (node != NULL) {
        cout << "key 20의 노드를 찾음" << endl;
    }
    else {
        cout << "key 20의 노드를 찾지 못함" << endl;
    }

    node = search(root, 30);
    if (node != NULL) {
        cout << "key 30의 노드를 찾음" << endl;
    }
    else {
        cout << "key 30의 노드를 찾지 못함" << endl;
    }

    return 0;
}