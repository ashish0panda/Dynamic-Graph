#include <bits/stdc++.h>

using namespace std;

void dfs1(int u, const vector<int>& offsets, const vector<int>& edges, vector<int>& vis, vector<int>& order) {
    vis[u] = 1;
    for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
        int v = edges[i];
        if (!vis[v]) dfs1(v, offsets, edges, vis, order);
    }
    order.push_back(u);
}

void dfs2(int u, const vector<int>& offsets, const vector<int>& edges, vector<int>& vis, vector<int>& comp) {
    vis[u] = 1;
    comp.push_back(u);
    for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
        int v = edges[i];
        if (!vis[v]) dfs2(v, offsets, edges, vis, comp);
    }
}

int scc(const vector<int>& offsets, const vector<int>& edges, int n) {
    // 1. Build the reversed graph in CSR format
    vector<int> rev_offsets(n + 1, 0);
    for (int i = 0; i < (int)edges.size(); ++i) {
        rev_offsets[edges[i] + 1]++;
    }
    for (int i = 0; i < n; ++i) {
        rev_offsets[i + 1] += rev_offsets[i];
    }

    vector<int> rev_edges(edges.size());
    vector<int> current_pos = rev_offsets;
    for (int u = 0; u < n; ++u) {
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            rev_edges[current_pos[v]++] = u;
        }
    }

    // 2. First pass: fill order using original graph
    vector<int> vis(n, 0), order;
    order.reserve(n);
    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs1(i, offsets, edges, vis, order);
    }

    // 3. Second pass: process nodes in decreasing order of finishing time
    fill(vis.begin(), vis.end(), 0);
    int sccCount = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i];
        if (vis[v]) continue;

        vector<int> comp;
        dfs2(v, rev_offsets, rev_edges, vis, comp);
        ++sccCount;

        cout << "SCC " << sccCount << ": { ";
        for (int node : comp) cout << node << " ";
        cout << "}\n";
    }

    return sccCount;
}

int main() {
    // Sample directed graph converted to CSR
    // 0 -> 1
    // 1 -> 2, 1 -> 3
    // 2 -> 0
    // 3 -> 4
    // 4 -> 5
    // 5 -> 3
    int n = 6;
    vector<int> offsets = {0, 1, 3, 4, 5, 6, 7};
    vector<int> edges = {
        1,       // neighbors of 0
        2, 3,    // neighbors of 1
        0,       // neighbors of 2
        4,       // neighbors of 3
        5,       // neighbors of 4
        3        // neighbors of 5
    };

    cout << "Strongly Connected Components:" << endl;
    int count = scc(offsets, edges, n);
    cout << "Total SCCs: " << count << endl;

    return 0;
}
