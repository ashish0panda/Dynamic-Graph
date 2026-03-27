#include <bits/stdc++.h>
using namespace std;

vector<int> greedy_coloring(const vector<int>& offsets, const vector<int>& edges, int n) {
    vector<int> result(n, -1);
    if (n == 0) return result;

    result[0] = 0; // Assign the first color to first vertex

    vector<bool> available(n, false);

    for (int u = 1; u < n; u++) {
        // Mark colors of adjacent vertices as unavailable
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
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
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            if (result[v] != -1) {
                available[result[v]] = false;
            }
        }
    }
    return result;
}

int main() {
    // Sample graph (undirected) converted to CSR
    // Adjacency List:
    // 0: 1, 3
    // 1: 0, 2, 5
    // 2: 1, 3, 4
    // 3: 0, 2
    // 4: 2, 5
    // 5: 1, 4
    
    int n = 6;
    vector<int> offsets = {0, 2, 5, 8, 10, 12, 14};
    vector<int> edges = {
        1, 3,       // neighbors of 0
        0, 2, 5,    // neighbors of 1
        1, 3, 4,    // neighbors of 2
        0, 2,       // neighbors of 3
        2, 5,       // neighbors of 4
        1, 4        // neighbors of 5
    };

    vector<int> colors = greedy_coloring(offsets, edges, n);

    cout << "Vertex Coloring (Vertex: Color):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << " --->  Color " << colors[i] << endl;
    }

    return 0;
}
