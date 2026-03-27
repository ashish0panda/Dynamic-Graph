#include <bits/stdc++.h>
using namespace std;

vector<int> k_core(const vector<int>& offsets, const vector<int>& edges, int n, int k) {
    vector<int> degrees(n);
    vector<bool> exists(n, true);

    for (int i = 0; i < n; i++) {
        degrees[i] = offsets[i + 1] - offsets[i];
    }

    queue<int> q;
    for (int i = 0; i < n; i++) {
        if (degrees[i] < k) {
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        if (!exists[u]) continue;
        exists[u] = false;

        // In CSR, neighbors of u are in edges[offsets[u] ... offsets[u+1]-1]
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            if (exists[v]) {
                degrees[v]--;
                if (degrees[v] < k) {
                    q.push(v);
                }
            }
        }
    }

    vector<int> core_nodes;
    for (int i = 0; i < n; i++) {
        if (exists[i]) {
            core_nodes.push_back(i);
        }
    }
    return core_nodes;
}

int main() {
    // Sample graph (undirected) converted to CSR
    // 0: 1, 2
    // 1: 0, 2, 5
    // 2: 0, 1, 3, 4, 5
    // 3: 2, 4, 5
    // 4: 2, 3, 5
    // 5: 1, 2, 3, 4
    
    int n = 6;
    int k = 3;
    vector<int> offsets = {0, 2, 5, 10, 13, 16, 20};
    vector<int> edges = {
        1, 2,                // neighbors of 0
        0, 2, 5,             // neighbors of 1
        0, 1, 3, 4, 5,       // neighbors of 2
        2, 4, 5,             // neighbors of 3
        2, 3, 5,             // neighbors of 4
        1, 2, 3, 4           // neighbors of 5
    };

    vector<int> result = k_core(offsets, edges, n, k);

    cout << k << "-Core vertices: { ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << "}" << endl;

    return 0;
}
