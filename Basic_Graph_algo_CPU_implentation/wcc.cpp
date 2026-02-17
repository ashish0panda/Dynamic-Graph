#include <bits/stdc++.h>
using namespace std;

static void dfs_wcc(int u, const vector<vector<int>>& ug, vector<int>& vis, vector<int>& comp) {
    vis[u] = 1;
    comp.push_back(u);
    for (int v : ug[u]) {
        if (!vis[v]) dfs_wcc(v, ug, vis, comp);
    }
}

int wcc(const vector<vector<int>>& graph, int n) {
    // Build an undirected view of the graph
    vector<vector<int>> ug(n);
    for (int u = 0; u < n; ++u) {
        for (int v : graph[u]) {
            ug[u].push_back(v);
            ug[v].push_back(u);
        }
    }

    for (int i = 0; i < n; ++i) {
        auto& a = ug[i];
        sort(a.begin(), a.end());
        a.erase(unique(a.begin(), a.end()), a.end());
    }

    vector<int> vis(n, 0);
    int cnt = 0;

    for (int i = 0; i < n; ++i) {
        if (vis[i]) continue;

        vector<int> comp;
        dfs_wcc(i, ug, vis, comp);
        ++cnt;

        cout << "WCC " << cnt << ": { ";
        for (int node : comp) cout << node << " ";
        cout << "}\n";
    }

    return cnt;
}

int main() {
    vector<vector<int>> graph = {
        {1, 3},
        {0, 2, 5},
        {1, 3, 4},
        {0, 2},
        {2, 5},
        {1, 4}
    };

    cout << wcc(graph, 6);
    return 0;
}