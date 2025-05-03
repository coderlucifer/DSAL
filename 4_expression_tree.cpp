#include <iostream>
#include <stack>
#include <cctype>
#include <string>
using namespace std;

// TreeNode structure
struct TreeNode {
    char data;
    TreeNode* left;
    TreeNode* right;
    TreeNode(char val) : data(val), left(nullptr), right(nullptr) {}
};

// Check if character is operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Construct expression tree from prefix expression
TreeNode* constructExpressionTree(const string& prefix) {
    stack<TreeNode*> st;
    for (int i = prefix.length() - 1; i >= 0; --i) {
        char c = prefix[i];
        if (isalpha(c)) {
            st.push(new TreeNode(c));
        } else if (isOperator(c)) {
            TreeNode* node = new TreeNode(c);
            //  pop left first, then pop right ***
            if (!st.empty()) { 
                node->left = st.top(); 
                st.pop();
            }
            if (!st.empty()) { 
                node->right = st.top(); 
                st.pop();
            }
            st.push(node);
        }
    }
    return st.empty() ? nullptr : st.top();
}


// Non-recursive post-order traversal
void postOrderTraversal(TreeNode* root) {
    if (!root) return;
    
    stack<TreeNode*> st1;
    stack<char> st2;  // Changed to store characters directly
    st1.push(root);
    
    while (!st1.empty()) {
        TreeNode* node = st1.top();
        st1.pop();
        st2.push(node->data);
        
        // Push left child first (will be processed later)
        if (node->left) 
            st1.push(node->left);
            
        // Push right child next
        if (node->right)
            st1.push(node->right);
    }
    
    // Print in reverse order
    while (!st2.empty()) {
        cout << st2.top();
        st2.pop();
    }
    cout << endl;
}

// Delete the entire tree (non-recursive post-order)
void deleteTree(TreeNode* root) {
    if (!root) return;
    stack<TreeNode*> st;
    st.push(root);
    while (!st.empty()) {
        TreeNode* node = st.top(); st.pop();
        if (node->left) st.push(node->left);
        if (node->right) st.push(node->right);
        delete node;
    }
}

int main() {
    string prefix = "+--a*bc/def";
    TreeNode* root = constructExpressionTree(prefix);
    cout << "Post-order traversal: ";
    postOrderTraversal(root);
    deleteTree(root);
    return 0;
}
