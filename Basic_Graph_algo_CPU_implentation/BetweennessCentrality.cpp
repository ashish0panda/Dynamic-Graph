#include <bits/stdc++.h>
using namespace std;

vector<double> betweenness_centrality(const vector<vector<int>>& graph, int n) {
    vector<double> centrality(n, 0.0);

    for (int s = 0; s < n; s++) {
        stack<int> S;
        vector<vector<int>> P(n);
        vector<int> sigma(n, 0);
        sigma[s] = 1;
        vector<int> d(n, -1);
        d[s] = 0;

        queue<int> q;
        q.push(s);

        while (!q.empty()) {
            int v = q.front();
            q.pop();
            S.push(v);

            for (int w : graph[v]) {
                if (d[w] < 0) {
                    q.push(w);
                    d[w] = d[v] + 1;
                }
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

    for (int i = 0; i < n; i++) {
        centrality[i] /= 2.0;
    }

    return centrality;
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

    vector<double> result = betweenness_centrality(graph, n);

    cout << "Betweenness Centrality:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Vertex " << i << ": " << fixed << setprecision(4) << result[i] << endl;
    }

    return 0;
}
