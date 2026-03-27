#include <bits/stdc++.h>
using namespace std;

void dfs_wcc(int u, const vector<int>& offsets, const vector<int>& edges, vector<int>& vis, vector<int>& comp) {
    vis[u] = 1;
    comp.push_back(u);
    for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
        int v = edges[i];
        if (!vis[v]) dfs_wcc(v, offsets, edges, vis, comp);
    }
}

int wcc(const vector<int>& offsets, const vector<int>& edges, int n) {
    // To find Weakly Connected Components, we treat the graph as undirected.
    // 1. Build an undirected CSR representation
    vector<pair<int, int>> undirected_edges;
    for (int u = 0; u < n; ++u) {
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            undirected_edges.push_back({u, v});
            undirected_edges.push_back({v, u});
        }
    }
    sort(undirected_edges.begin(), undirected_edges.end());
    undirected_edges.erase(unique(undirected_edges.begin(), undirected_edges.end()), undirected_edges.end());

    vector<int> ug_offsets(n + 1, 0);
    for (auto& edge : undirected_edges) {
        ug_offsets[edge.first + 1]++;
    }
    for (int i = 0; i < n; ++i) {
        ug_offsets[i + 1] += ug_offsets[i];
    }

    vector<int> ug_edges(undirected_edges.size());
    for (int i = 0; i < (int)undirected_edges.size(); ++i) {
        ug_edges[i] = undirected_edges[i].second;
    }

    // 2. Perform DFS to find components
    vector<int> vis(n, 0);
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;

        vector<int> comp;
        dfs_wcc(i, ug_offsets, ug_edges, vis, comp);
        ++cnt;

        cout << "WCC " << cnt << ": { ";
        for (int node : comp) cout << node << " ";
        cout << "}\n";
    }

    return cnt;
}

int main() {
    // Sample graph (represented in CSR)
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

    cout << "Weakly Connected Components:" << endl;
    int count = wcc(offsets, edges, n);
    cout << "Total WCCs: " << count << endl;

    return 0;
}
