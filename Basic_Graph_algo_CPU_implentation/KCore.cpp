#include <bits/stdc++.h>
using namespace std;

vector<int> k_core(const vector<vector<int>>& graph, int n, int k) {
    vector<int> degrees(n);
    vector<bool> exists(n, true);

    for (int i = 0; i < n; i++) {
        degrees[i] = graph[i].size();
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

        for (int v : graph[u]) {
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
    // Sample graph (undirected)
    vector<vector<int>> graph = {
        {1, 2},
        {0, 2, 5},
        {0, 1, 3, 4, 5},
        {2, 4, 5},
        {2, 3, 5},
        {1, 2, 3, 4}
    };
    int n = 6;
    int k = 3;

    vector<int> result = k_core(graph, n, k);

    cout << k << "-Core vertices: { ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << "}" << endl;

    return 0;
}
