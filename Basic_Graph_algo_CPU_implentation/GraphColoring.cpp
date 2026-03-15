#include <bits/stdc++.h>
using namespace std;

vector<int> greedy_coloring(const vector<vector<int>>& graph, int n) {
    vector<int> result(n, -1);
    result[0] = 0; // Assign the first color to first vertex

    vector<bool> available(n, false);

    for (int u = 1; u < n; u++) {
        // Mark colors of adjacent vertices as unavailable
        for (int v : graph[u]) {
            if (result[v] != -1) {
                available[result[v]] = true;
            }
        }

        // Find the first available color
        int cr;
        for (cr = 0; cr < n; cr++) {
            if (!available[cr]) break;
        }

        result[u] = cr;

        // Reset the values for the next iteration
        for (int v : graph[u]) {
            if (result[v] != -1) {
                available[result[v]] = false;
            }
        }
    }
    return result;
}

int main() {
    // Sample graph (undirected)
    vector<vector<int>> graph = {
        {1, 3},
        {0, 2, 5},
        {1, 3, 4},
        {0, 2},
        {2, 5},
        {1, 4}
    };
    int n = 6;

    vector<int> colors = greedy_coloring(graph, n);

    cout << "Vertex Coloring (Vertex: Color):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " --->  Color " << colors[i] << endl;
    }

    return 0;
}
