#include <iostream>
#include <vector>
#include <string>
using namespace std;

// Simple DFS on adjacency matrix
void dfs(int u, const vector<vector<double>>& mat, vector<bool>& vis) {
    vis[u] = true;
    for (int v = 0; v < mat.size(); ++v)
        if (mat[u][v] > 0 && !vis[v])
            dfs(v, mat, vis);
}

bool isConnected(const vector<vector<double>>& mat) {
    int n = mat.size();
    if (n == 0) return true;
    vector<bool> visited(n, false);
    dfs(0, mat, visited);
    for (bool v : visited)
        if (!v) return false;
    return true;
}

int main() {
    // 1. City names
    vector<string> cities = { "Delhi", "Mumbai", "Bangalore", "Chennai" };
    int n = cities.size();

    // 2. Build empty n×n matrix
    vector<vector<double>> cost(n, vector<double>(n, 0));

    // 3. Add flights (undirected)
    auto addFlight = [&](int u, int v, double w) {
        cost[u][v] = cost[v][u] = w;
    };
    addFlight(0, 1, 2.5);
    addFlight(1, 2, 1.8);
    addFlight(2, 3, 2.0);
    // (no flight between 3 and 0 here)

    // 4. Print matrix
    cout << "Cost Matrix:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            cout << cost[i][j] << "\t";
        cout << "\n";
    }

    // 5. Print list of flights
    cout << "\nFlights:\n";
    for (int i = 0; i < n; ++i)
        for (int j = i+1; j < n; ++j)
            if (cost[i][j] > 0)
                cout << cities[i] << " <-> " << cities[j]
                     << "  (" << cost[i][j] << ")\n";

    // 6. Connectivity check
    cout << "\nNetwork is "
         << (isConnected(cost) ? "connected\n" : "not connected\n");

    return 0;
}
