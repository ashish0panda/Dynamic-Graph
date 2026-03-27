#include <bits/stdc++.h>

using namespace std;

vector<int> greedy_mis(const vector<int>& offsets, const vector<int>& edges, int n) {
    vector<int> mis;
    vector<bool> excluded(n, false);

    for (int i = 0; i < n; ++i) {
        if (!excluded[i]) {
            mis.push_back(i);
            // In CSR, neighbors of i are in edges[offsets[i] ... offsets[i+1]-1]
            for (int j = offsets[i]; j < offsets[i + 1]; ++j) {
                int neighbor = edges[j];
                excluded[neighbor] = true;
            }
        }
    }
    return mis;
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

    vector<int> result = greedy_mis(offsets, edges, n);

    cout << "Maximal Independent Set: { ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << "}" << endl;

    return 0;
}
