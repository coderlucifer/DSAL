#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Edge {
    int to;
    double cost;
};

class Graph {
    vector<string> cities;
    vector<vector<Edge>> adj;

public:
    Graph(const vector<string>& cityList) {
        cities = cityList;
        adj.resize(cities.size());
    }

    void addFlight(int src, int dest, double cost) {
        adj[src].push_back({dest, cost});
        adj[dest].push_back({src, cost}); // undirected graph
    }

    void printGraph() {
        for (int i = 0; i < cities.size(); i++) {
            cout << cities[i] << " -> ";
            for (auto& edge : adj[i]) {
                cout << "(" << cities[edge.to] << ", " << edge.cost << ") ";
            }
            cout << endl;
        }
    }

    void dfs(int v, vector<bool>& visited) {
        visited[v] = true;
        for (auto& edge : adj[v]) {
            if (!visited[edge.to])
                dfs(edge.to, visited);
        }
    }

    bool isConnected() {
        vector<bool> visited(cities.size(), false);
        dfs(0, visited);
        for (bool v : visited) {
            if (!v) return false;
        }
        return true;
    }
};

int main() {
    vector<string> cities = {"Delhi", "Mumbai", "Bangalore", "Chennai"};
    Graph g(cities);

    g.addFlight(0, 1, 2.5);
    g.addFlight(1, 2, 1.8);
    g.addFlight(2, 3, 2.0);
    g.addFlight(3, 0, 3.1);

    cout << "Flight Network:\n";
    g.printGraph();

    if (g.isConnected())
        cout << "The flight network is connected.\n";
    else
        cout << "The flight network is not connected.\n";

    return 0;
}
