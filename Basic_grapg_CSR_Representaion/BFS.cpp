#include <bits/stdc++.h>

using namespace std;

vector<int> BFS(const vector<int>& offsets, const vector<int>& edges, int n) {
    vector<int> visited_order;
    vector<bool> visited(n, false);
    queue<int> q;
    
    if (n > 0) {
        q.push(0);
        visited[0] = true;
    }

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        visited_order.push_back(u);

        // In CSR, neighbors of u are in edges[offsets[u] ... offsets[u+1]-1]
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            if (!visited[v]) {
                visited[v] = true;
                q.push(v);
            }
        }
    }
    return visited_order;
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

    vector<int> visited_order = BFS(offsets, edges, n);
    
    cout << "BFS traversal order starting from node 0:" << endl;
    for (auto node : visited_order) {
        cout << node << " ";
    }
    cout << endl;

    return 0;
}
