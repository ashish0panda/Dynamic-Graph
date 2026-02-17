#include <bits/stdc++.h>

using namespace std;

void dfs1(int u, const vector<vector<int>>& g, vector<int>& vis, vector<int>& order) {
    vis[u] = 1;
    for (int v : g[u]) if (!vis[v]) dfs1(v, g, vis, order);
    order.push_back(u);
}

void dfs2(int u, const vector<vector<int>>& gr, vector<int>& vis, vector<int>& comp) {
    vis[u] = 1;
    comp.push_back(u);
    for (int v : gr[u]) if (!vis[v]) dfs2(v, gr, vis, comp);
}

int scc(vector<vector<int>>& graph, int n) {
    vector<vector<int>> rev(n);
    for (int u = 0; u < n; ++u) {
        for (int v : graph[u]) rev[v].push_back(u);
    }

    vector<int> vis(n, 0), order;
    order.reserve(n);

    for (int i = 0; i < n; ++i) {
        if (!vis[i]) dfs1(i, graph, vis, order);
    }

    fill(vis.begin(), vis.end(), 0);

    int sccCount = 0;
    for (int i = n - 1; i >= 0; --i) {
        int v = order[i];
        if (vis[v]) continue;

        vector<int> comp;
        dfs2(v, rev, vis, comp);
        ++sccCount;

        // Print this SCC (as a set/list of vertices)
        cout << "SCC " << sccCount << ": { ";
        for (int node : comp) cout << node << " ";
        cout << "}\n";
    }

    return sccCount;
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
    cout<<scc(graph,6);
    return 0;
}