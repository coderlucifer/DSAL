#include <iostream>
#include <vector>
#include <limits>
using namespace std;

struct Node {
    int key;
    double prob;
    Node* left;
    Node* right;
    Node(int k, double p): key(k), prob(p), left(nullptr), right(nullptr) {}
};

// Recursively build the tree from the root table
Node* buildTree(const vector<vector<int>>& root,
                const vector<int>& keys,
                int i, int j) {
    if (i > j) return nullptr;
    int r = root[i][j];
    Node* node = new Node(keys[r], /*prob is not needed*/ 0);
    node->left  = buildTree(root, keys, i,   r-1);
    node->right = buildTree(root, keys, r+1, j  );
    return node;
}

double optimalBST(const vector<int>& keys,
                  const vector<double>& p) {
    int n = keys.size() - 1; // assume keys[1..n], p[1..n]
    const double INF = numeric_limits<double>::infinity();

    // Tables are 1..n+1 for e and w, root is 1..n
    vector<vector<double>> e(n+2, vector<double>(n+1, 0.0)),
                        w(n+2, vector<double>(n+1, 0.0));
    vector<vector<int>>    root(n+2, vector<int>(n+1, 0));

    // Base initialization: e[i][i-1] = w[i][i-1] = 0 (already zeroed)

    // Build for lengths l = 1..n
    for (int l = 1; l <= n; ++l) {
        for (int i = 1; i <= n-l+1; ++i) {
            int j = i + l - 1;
            w[i][j] = w[i][j-1] + p[j];

            // Find best root
            double minCost = INF;
            int bestR = i;
            for (int r = i; r <= j; ++r) {
                double cost = e[i][r-1] + e[r+1][j] + w[i][j];
                if (cost < minCost) {
                    minCost = cost;
                    bestR = r;
                }
            }
            e[i][j]    = minCost;
            root[i][j] = bestR;
        }
    }

    cout << "Minimum expected search cost = " << e[1][n] << "\n";

    // Optional: build and return the actual tree
    Node* obstRoot = buildTree(root, keys, 1, n);
    // … you could traverse obstRoot to verify structure …

    return e[1][n];
}

int main() {
    // 1-based: insert dummy at index 0
    vector<int>   keys = {0, 10, 20, 30, 40};  
    vector<double> p   = {0, 0.10, 0.20, 0.40, 0.30};

    optimalBST(keys, p);
    return 0;
}
/*viva questions:
1. What is the time complexity of the algorithm?
2. What is the space complexity of the algorithm?
3. What is the optimal binary search tree for the given keys and probabilities?
4. What is the minimum expected search cost for the given keys and probabilities?
5. What is the structure of the optimal binary search tree?
6. How does the algorithm handle duplicate keys?
7. Can you explain the role of the root table in the algorithm?
8. How does the algorithm ensure that the tree is balanced?
9. What is the significance of the weight table in the algorithm?
10. How would you modify the algorithm to handle non-uniform probabilities?

answer:
1. The time complexity of the algorithm is O(n^3), where n is the number of keys.
2. The space complexity of the algorithm is O(n^2), where n is the number of keys.
3. The optimal binary search tree for the given keys and probabilities is:
   30
  /  \
20   40
   \
   10
4. The minimum expected search cost for the given keys and probabilities is 2.3.
5. The structure of the optimal binary search tree is:
   30
  /  \
20   40
   \
    10
6. The algorithm does not handle duplicate keys; it assumes all keys are unique.
7. The root table stores the indices of the roots of the subtrees for each range of keys.
8. The algorithm does not guarantee a balanced tree; it focuses on minimizing the expected search cost.
9. The weight table stores the sum of probabilities for each range of keys, which is used to calculate the expected search cost.
10. To handle non-uniform probabilities, the algorithm can be modified to accept a probability distribution for the keys and adjust the calculations accordingly.
*/