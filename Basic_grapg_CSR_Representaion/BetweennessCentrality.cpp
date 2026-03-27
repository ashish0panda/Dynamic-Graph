#include <bits/stdc++.h>
using namespace std;

vector<double> betweenness_centrality(const vector<int>& offsets, const vector<int>& edges, int n) {
    vector<double> centrality(n, 0.0);

    for (int s = 0; s < n; s++) {
        stack<int> S;
        vector<vector<int>> P(n);
        vector<long long> sigma(n, 0);
        sigma[s] = 1;
        vector<int> d(n, -1);
        d[s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            S.push(v);

            // In CSR, neighbors of v are in edges[offsets[v] ... offsets[v+1]-1]
            for (int i = offsets[v]; i < offsets[v + 1]; ++i) {
                int w = edges[i];
                // Path discovery
                if (d[w] < 0) {
                    q.push(w);
                    d[w] = d[v] + 1;
                }
                // Path counting
                if (d[w] == d[v] + 1) {
                    sigma[w] += sigma[v];
                    P[w].push_back(v);
                }
            }
        }

        vector<double> delta(n, 0.0);
        while (!S.empty()) {
            int w = S.top();
            S.pop();
            for (int v : P[w]) {
                delta[v] += ((double)sigma[v] / sigma[w]) * (1.0 + delta[w]);
            }
            if (w != s) {
                centrality[w] += delta[w];
            }
        }
    }

    // For undirected graphs, each edge is counted twice
    for (int i = 0; i < n; i++) {
        centrality[i] /= 2.0;
    }

    return centrality;
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
    vector<int> offsets = {0, 2, 5, 10, 13, 16, 20};
    vector<int> edges = {
        1, 2,                // neighbors of 0
        0, 2, 5,             // neighbors of 1
        0, 1, 3, 4, 5,       // neighbors of 2
        2, 4, 5,             // neighbors of 3
        2, 3, 5,             // neighbors of 4
        1, 2, 3, 4           // neighbors of 5
    };

    vector<double> result = betweenness_centrality(offsets, edges, n);

    cout << "Betweenness Centrality:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": " << fixed << setprecision(4) << result[i] << endl;
    }

    return 0;
}
