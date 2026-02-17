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

pair<long long, vector<Edge>> kruskal_mst(int n, vector<Edge> edges) {
    sort(edges.begin(), edges.end(), [](const Edge& a, const Edge& b) {
        return a.w < b.w;
    });

    DSU dsu(n);
    long long total = 0;
    vector<Edge> chosen;
    chosen.reserve(n - 1);

    for (const auto& e : edges) {
        if (dsu.unite(e.u, e.v)) {
            chosen.push_back(e);
            total += e.w;
            if ((int)chosen.size() == n - 1) break;
        }
    }

    if ((int)chosen.size() != n - 1) {
        return {LLONG_MAX, chosen};
    }
    return {total, chosen};
}

int main() {
    int n = 6;
    vector<Edge> edges = {
        {0, 1, 4},
        {0, 2, 4},
        {1, 2, 2},
        {1, 3, 5},
        {2, 3, 5},
        {2, 4, 11},
        {3, 4, 2},
        {3, 5, 6},
        {4, 5, 1}
    };

    auto [cost, mstEdges] = kruskal_mst(n, edges);

    if (cost == LLONG_MAX) {
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