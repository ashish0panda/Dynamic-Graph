#include <bits/stdc++.h>
using namespace std;

struct DSU {
    vector<int> p, r;
    DSU(int n = 0) { init(n); }

    void init(int n) {
        p.resize(n);
        r.assign(n, 0);
        iota(p.begin(), p.end(), 0);
    }

    int find(int x) {
        if (p[x] == x) return x;
        return p[x] = find(p[x]);
    }

    bool unite(int a, int b) {
        a = find(a), b = find(b);
        if (a == b) return false;
        if (r[a] < r[b]) swap(a, b);
        p[b] = a;
        if (r[a] == r[b]) r[a]++;
        return true;
    }
};

struct Edge {
    int u, v;
    long long w;
};

pair<long long, vector<Edge>> kruskal_mst(const vector<int>& offsets, const vector<int>& edges, const vector<int>& weights, int n) {
    vector<Edge> all_edges;
    for (int u = 0; u < n; ++u) {
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            // To avoid processing the same edge twice in an undirected graph
            if (u < v) {
                all_edges.push_back({u, v, (long long)weights[i]});
            }
        }
    }

    sort(all_edges.begin(), all_edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    long long total = 0;
    vector<Edge> chosen;
    chosen.reserve(n - 1);

    for (const auto& e : all_edges) {
        if (dsu.unite(e.u, e.v)) {
            chosen.push_back(e);
            total += e.w;
            if ((int)chosen.size() == n - 1) break;
        }
    }

    if ((int)chosen.size() != n - 1 && n > 0) {
        return {LLONG_MAX, chosen};
    }
    return {total, chosen};
}

int main() {
    // Sample graph (undirected) converted to CSR
    // 0: {1,4}, {2,4}
    // 1: {0,4}, {2,2}, {3,5}
    // 2: {0,4}, {1,2}, {3,5}, {4,11}
    // 3: {1,5}, {2,5}, {4,2}, {5,6}
    // 4: {2,11}, {3,2}, {5,1}
    // 5: {3,6}, {4,1}
    
    int n = 6;
    vector<int> offsets = {0, 2, 5, 9, 13, 16, 18};
    vector<int> edges = {
        1, 2,          // neighbors of 0
        0, 2, 3,       // neighbors of 1
        0, 1, 3, 4,    // neighbors of 2
        1, 2, 4, 5,    // neighbors of 3
        2, 3, 5,       // neighbors of 4
        3, 4           // neighbors of 5
    };
    vector<int> weights = {
        4, 4,          // weights for 0
        4, 2, 5,       // weights for 1
        4, 2, 5, 11,   // weights for 2
        5, 5, 2, 6,    // weights for 3
        11, 2, 1,      // weights for 4
        6, 1           // weights for 5
    };

    auto [cost, mstEdges] = kruskal_mst(offsets, edges, weights, n);

    if (cost == LLONG_MAX && n > 0) {
        cout << "Graph is disconnected -> MST doesn't exist.\n";
        cout << "Minimum Spanning Forest edges found:\n";
    } else {
        cout << "MST total cost = " << cost << "\n";
        cout << "MST edges:\n";
    }

    for (auto &e : mstEdges) {
        cout << e.u << " - " << e.v << "  (w=" << e.w << ")\n";
    }

    return 0;
}
