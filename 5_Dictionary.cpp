#include <iostream>
#include <string>
using namespace std;

// Node structure representing each dictionary entry
struct Node {
    string key;
    string meaning;
    Node* left;
    Node* right;
    Node(const string& k, const string& m)
        : key(k), meaning(m), left(nullptr), right(nullptr) {}
};

// Utility: compare two strings lexicographically
int compareKeys(const string& a, const string& b) {
    if (a < b) return -1;
    if (a > b) return 1;
    return 0;
}

// Insert a new node into BST
Node* insertNode(Node* root, const string& key, const string& meaning) {
    if (!root)
        return new Node(key, meaning);
    int cmp = compareKeys(key, root->key);
    if (cmp < 0)
        root->left = insertNode(root->left, key, meaning);
    else if (cmp > 0)
        root->right = insertNode(root->right, key, meaning);
    else
        cout << "Key '" << key << "' already exists. Use update to change meaning.\n";
    return root;
}

// Find minimum node in a subtree (used for deletion)
Node* findMin(Node* root) {
    while (root && root->left)
        root = root->left;
    return root;
}

// Delete a node by key
Node* deleteNode(Node* root, const string& key) {
    if (!root) return nullptr;
    int cmp = compareKeys(key, root->key);
    if (cmp < 0) {
        root->left = deleteNode(root->left, key);
    } else if (cmp > 0) {
        root->right = deleteNode(root->right, key);
    } else {
        // Found the node
        if (!root->left) {
            Node* temp = root->right;
            delete root;
            return temp;
        } else if (!root->right) {
            Node* temp = root->left;
            delete root;
            return temp;
        }
        // Two children: replace with inorder successor
        Node* successor = findMin(root->right);
        root->key = successor->key;
        root->meaning = successor->meaning;
        root->right = deleteNode(root->right, successor->key);
    }
    return root;
}

// Update meaning of an existing key
void updateNode(Node* root, const string& key, const string& newMeaning) {
    if (!root) {
        cout << "Key '" << key << "' not found.\n";
        return;
    }
    int cmp = compareKeys(key, root->key);
    if (cmp < 0)
        updateNode(root->left, key, newMeaning);
    else if (cmp > 0)
        updateNode(root->right, key, newMeaning);
    else {
        root->meaning = newMeaning;
        cout << "Updated key '" << key << "' successfully.\n";
    }
}

// Inorder traversal (ascending)
void inorderPrint(Node* root) {
    if (!root) return;
    inorderPrint(root->left);
    cout << root->key << " : " << root->meaning << "\n";
    inorderPrint(root->right);
}

// Descending order (reverse-inorder)
void descendingPrint(Node* root) {
    if (!root) return;
    descendingPrint(root->right);
    cout << root->key << " : " << root->meaning << "\n";
    descendingPrint(root->left);
}

// Search for a key and count comparisons
bool searchKey(Node* root, const string& key, int& comparisons) {
    if (!root) return false;
    comparisons++;
    int cmp = compareKeys(key, root->key);
    if (cmp == 0) return true;
    if (cmp < 0)
        return searchKey(root->left, key, comparisons);
    else
        return searchKey(root->right, key, comparisons);
}

// Compute height of tree (max comparisons = height)
int treeHeight(Node* root) {
    if (!root) return 0;
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    return 1 + max(lh, rh);
}

// Clean up all nodes
void deleteTree(Node* root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}

int main() {
    Node* root = nullptr;
    int choice;
    string key, meaning;

    do {
        cout << "\nDictionary Operations Menu:\n";
        cout << "1. Add keyword\n";
        cout << "2. Delete keyword\n";
        cout << "3. Update meaning\n";
        cout << "4. Display ascending\n";
        cout << "5. Display descending\n";
        cout << "6. Search keyword (comparisons)\n";
        cout << "7. Maximum comparisons (tree height)\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter keyword: "; cin >> key;
                cout << "Enter meaning: "; cin.ignore(); getline(cin, meaning);
                root = insertNode(root, key, meaning);
                break;
            case 2:
                cout << "Enter keyword to delete: "; cin >> key;
                root = deleteNode(root, key);
                break;
            case 3:
                cout << "Enter keyword to update: "; cin >> key;
                cout << "Enter new meaning: "; cin.ignore(); getline(cin, meaning);
                updateNode(root, key, meaning);
                break;
            case 4:
                cout << "\nDictionary (Ascending):\n";
                inorderPrint(root);
                break;
            case 5:
                cout << "\nDictionary (Descending):\n";
                descendingPrint(root);
                break;
            case 6: {
                cout << "Enter keyword to search: "; cin >> key;
                int comparisons = 0;
                bool found = searchKey(root, key, comparisons);
                if (found)
                    cout << "Found '" << key << "' in " << comparisons << " comparisons.\n";
                else
                    cout << "Keyword '" << key << "' not found after " << comparisons << " comparisons.\n";
                break;
            }
            case 7:
                cout << "Maximum comparisons needed = " << treeHeight(root) << " (tree height).\n";
                break;
            case 0:
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 0);

    deleteTree(root);
    return 0;
}
