#include <iostream>
using namespace std;

// Node structure
struct Node {
    int data;
    Node* left;
    Node* right;
    Node(int val) : data(val), left(nullptr), right(nullptr) {}
};

// Insert a new node into BST
Node* insert(Node* root, int val) {
    if (!root) return new Node(val);
    if (val < root->data)
        root->left = insert(root->left, val);
    else
        root->right = insert(root->right, val);
    return root;
}

// Find number of nodes in longest path (height)
int longestPath(Node* root) {
    if (!root) return 0;
    int left = longestPath(root->left);
    int right = longestPath(root->right);
    return max(left, right) + 1;
}

// Find minimum data value in the tree
int findMin(Node* root) {
    if (!root) throw std::runtime_error("Tree is empty");
    while (root->left)
        root = root->left;
    return root->data;
}

// Swap left and right pointers at every node (mirror)
void swapNodes(Node* root) {
    if (!root) return;
    std::swap(root->left, root->right);
    swapNodes(root->left);
    swapNodes(root->right);
}

// Search a value in BST
bool search(Node* root, int val) {
    if (!root) return false;
    if (root->data == val) return true;
    if (val < root->data)
        return search(root->left, val);
    else
        return search(root->right, val);
}

// Preorder traversal (VLR)
void preorder(Node* root) {
    if (!root) return;
    cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

// Inorder traversal (LVR)
void inorder(Node* root) {
    if (!root) return;
    inorder(root->left);
    cout << root->data << " ";
    inorder(root->right);
}

// Postorder traversal (LRV)
void postorder(Node* root) {
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    cout << root->data << " ";
}

int main() {
    Node* root = nullptr;
    int n, val, choice;
    // Example: Insert values 10, 5, 15, 3, 7, 12, 18
    int values[] = {10, 5, 15, 3, 7, 12, 18};
    for (int v : values)
        root = insert(root, v);

    cout << "BST created with values: ";
    inorder(root);
    cout << endl;

    // i. Insert new node
    cout << "Insert new value: ";
    cin >> val;
    root = insert(root, val);
    cout << "Inorder after insertion: ";
    inorder(root);
    cout << endl;

    // ii. Longest path (height)
    cout << "Number of nodes in longest path: " << longestPath(root) << endl;

    // iii. Minimum data value
    cout << "Minimum data value in tree: " << findMin(root) << endl;

    // iv. Swap left and right pointers at every node
    swapNodes(root);
    cout << "Inorder after swapping left/right: ";
    inorder(root);
    cout << endl;

    // v. Search a value
    cout << "Enter value to search: ";
    cin >> val;
    if (search(root, val))
        cout << "Value found in BST." << endl;
    else
        cout << "Value not found in BST." << endl;

    // Traversals
    cout << "Preorder: "; preorder(root); cout << endl;
    cout << "Inorder: "; inorder(root); cout << endl;
    cout << "Postorder: "; postorder(root); cout << endl;

    return 0;
}
