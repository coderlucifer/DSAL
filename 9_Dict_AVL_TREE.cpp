#include <iostream>
#include <string>
using namespace std;

struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    int height;

    Node(string k, string m) : key(k), meaning(m), left(nullptr), right(nullptr), height(1) {}
};

int height(Node* N) {
    return (N == nullptr) ? 0 : N->height;
}

int getBalance(Node* N) {
    return (N == nullptr) ? 0 : height(N->left) - height(N->right);
}

Node* rightRotate(Node* y) {
    Node* x = y->left;
    Node* T2 = x->right;
    x->right = y;
    y->left = T2;
    y->height = max(height(y->left), height(y->right)) + 1;
    x->height = max(height(x->left), height(x->right)) + 1;
    return x;
}

Node* leftRotate(Node* x) {
    Node* y = x->right;
    Node* T2 = y->left;
    y->left = x;
    x->right = T2;
    x->height = max(height(x->left), height(x->right)) + 1;
    y->height = max(height(y->left), height(y->right)) + 1;
    return y;
}

Node* insert(Node* node, string key, string meaning) {
    if (node == nullptr)
        return new Node(key, meaning);

    if (key < node->key)
        node->left = insert(node->left, key, meaning);
    else if (key > node->key)
        node->right = insert(node->right, key, meaning);
    else {
        node->meaning = meaning;
        return node;
    }

    node->height = max(height(node->left), height(node->right)) + 1;
    int balance = getBalance(node);

    if (balance > 1 && key < node->left->key)
        return rightRotate(node);
    if (balance < -1 && key > node->right->key)
        return leftRotate(node);
    if (balance > 1 && key > node->left->key) {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && key < node->right->key) {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
    return node;
}

Node* minNode(Node* node) {
    while (node->left != nullptr)
        node = node->left;
    return node;
}

Node* deleteNode(Node* root, string key) {
    if (root == nullptr)
        return root;

    if (key < root->key)
        root->left = deleteNode(root->left, key);
    else if (key > root->key)
        root->right = deleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            Node* temp = root->left ? root->left : root->right;
            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            } else
                *root = *temp;
            delete temp;
        } else {
            Node* temp = minNode(root->right);
            root->key = temp->key;
            root->meaning = temp->meaning;
            root->right = deleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr)
        return root;

    root->height = max(height(root->left), height(root->right)) + 1;
    int balance = getBalance(root);

    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);
    if (balance > 1 && getBalance(root->left) < 0) {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);
    if (balance < -1 && getBalance(root->right) > 0) {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
}

void inorder(Node* root) {
    if (root) {
        inorder(root->left);
        cout << root->key << " : " << root->meaning << endl;
        inorder(root->right);
    }
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;
    do {
        cout << "\nDictionary Menu:\n";
        cout << "1. Insert Word\n";
        cout << "2. Delete Word\n";
        cout << "3. Display Dictionary\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();
        switch (choice) {
            case 1:
                cout << "Enter word: ";
                getline(cin, key);
                cout << "Enter meaning: ";
                getline(cin, meaning);
                root = insert(root, key, meaning);
                break;
            case 2:
                cout << "Enter word to delete: ";
                getline(cin, key);
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "\nDictionary in sorted order:\n";
                inorder(root);
                break;
            case 4:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
