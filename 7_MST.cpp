#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

double primMST(int N, const vector<vector<pair<int,double>>>& adj) {
    const double INF = numeric_limits<double>::infinity();
    vector<bool>   inMST(N, false);
    vector<double> key( N, INF);
    vector<int>    parent(N, -1);

    // Start from vertex 0
    key[0] = 0.0;
    // Min‐heap of (key, vertex)
    priority_queue<
        pair<double,int>,
        vector<pair<double,int>>,
        greater<pair<double,int>>
    > pq;
    pq.push(make_pair(0.0, 0));

    double totalCost = 0.0;
    while (!pq.empty()) {
        // extract-min
        pair<double,int> top = pq.top();
        pq.pop();
        double cost_u = top.first;
        int u         = top.second;

        if (inMST[u]) 
            continue;
        inMST[u] = true;
        totalCost += cost_u;

        // relax adjacent edges
        for (size_t i = 0; i < adj[u].size(); ++i) {
            int    v = adj[u][i].first;
            double w = adj[u][i].second;
            if (!inMST[v] && w < key[v]) {
                key[v]    = w;
                parent[v] = u;
                pq.push(make_pair(w, v));
            }
        }
    }

    return totalCost;
}

int main() {
    int N = 5;  
    vector<vector<pair<int,double>>> adj(N);

    // Example costs between offices (undirected)
    auto addEdge = [&](int u, int v, double w){
        adj[u].push_back(make_pair(v,w));
        adj[v].push_back(make_pair(u,w));
    };

    addEdge(0, 1, 10.0);
    addEdge(0, 2,  5.0);
    addEdge(1, 2,  2.0);
    addEdge(1, 3,  1.0);
    addEdge(2, 3,  9.0);
    addEdge(2, 4,  2.0);
    addEdge(3, 4,  4.0);

    double minCost = primMST(N, adj);
    cout << "Minimum total leasing cost = " << minCost << "\n";
    return 0;
}

/*viva questions:
1. What is the time complexity of Prim's algorithm?
2. How does Prim's algorithm differ from Kruskal's algorithm?
3. Can you explain the role of the priority queue in Prim's algorithm?
4. What is the significance of the parent array in the implementation?
5. How would you modify the algorithm to handle negative edge weights?
6. What is the space complexity of the algorithm?
7. How does the algorithm ensure that no cycles are formed in the MST?
8. Can you explain the process of edge relaxation in the context of Prim's algorithm?
9. How would you adapt the algorithm for a directed graph?
10. What are some real-world applications of Prim's algorithm?
11. How would you implement Prim's algorithm using an adjacency matrix instead of an adjacency list?
12. Can you describe a scenario where Prim's algorithm would not be the best choice for finding a minimum spanning tree?

answers:
1. The time complexity of Prim's algorithm is O(E log V) when using a priority queue, where E is the number of edges and V is the number of vertices.
2. Prim's algorithm builds the MST by adding edges from a single starting vertex, while Kruskal's algorithm sorts all edges and adds them one by one, ensuring no cycles are formed. Prim's is more efficient for dense graphs, while Kruskal's is better for sparse graphs.
3. The priority queue is used to efficiently extract the edge with the minimum weight that connects a vertex in the MST to a vertex outside the MST. It allows for quick updates and retrieval of the minimum edge.
4. The parent array keeps track of the vertices from which each vertex was reached in the MST. It can be used to reconstruct the MST after the algorithm completes.
5. To handle negative edge weights, you can use a modified version of Prim's algorithm or switch to a different algorithm like Bellman-Ford, which can handle negative weights but is not specifically designed for MSTs.
6. The space complexity of Prim's algorithm is O(V + E) for the adjacency list representation, where V is the number of vertices and E is the number of edges.
7. The algorithm ensures no cycles are formed by only adding edges that connect a vertex in the MST to a vertex outside the MST, and by marking vertices as included in the MST once they are added.
8. Edge relaxation in Prim's algorithm involves checking if the current edge can provide a shorter path to a vertex not yet included in the MST. If it does, the key value and parent of that vertex are updated.
9. To adapt Prim's algorithm for a directed graph, you would need to ensure that the edges are treated as directed and only consider outgoing edges from the vertices in the MST when relaxing edges.
10. Real-world applications of Prim's algorithm include network design (like telecommunications), road construction, and clustering in data analysis.
11. To implement Prim's algorithm using an adjacency matrix, you would maintain a matrix of weights and use a similar approach to track the minimum edge for each vertex, but with O(V^2) time complexity.
12. Prim's algorithm may not be the best choice for finding a minimum spanning tree in very sparse graphs or when the graph is not connected, as Kruskal's algorithm might be more efficient in those cases.
*/
