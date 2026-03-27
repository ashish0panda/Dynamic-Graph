#include <bits/stdc++.h>

using namespace std;

int dijkstra(const vector<int>& offsets, const vector<int>& edges, const vector<int>& weights, int n, int target, int source) {
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    pq.push({0, source});

    while (!pq.empty()) {
        int d = pq.top().first;
        int u = pq.top().second;
        pq.pop();

        if (d > dist[u]) continue;

        // In CSR, neighbors of u are in edges[offsets[u] ... offsets[u+1]-1]
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            int weight = weights[i];
            if (dist[v] > dist[u] + weight) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }
    return dist[target];
}

int bellmanford(const vector<int>& offsets, const vector<int>& edges, const vector<int>& weights, int n, int target, int source) {
    vector<int> dist(n, INT_MAX);
    dist[source] = 0;

    for (int i = 0; i < n - 1; i++) {
        bool changed = false;
        for (int u = 0; u < n; u++) {
            if (dist[u] == INT_MAX) continue;
            for (int j = offsets[u]; j < offsets[u + 1]; ++j) {
                int v = edges[j];
                int weight = weights[j];
                if (dist[v] > dist[u] + weight) {
                    dist[v] = dist[u] + weight;
                    changed = true;
                }
            }
        }
        if (!changed) break;
    }
    return dist[target];
}

int main() {
    // Sample graph (undirected) converted to CSR
    // 0: {1,7}, {2,9}, {5,14}
    // 1: {0,7}, {2,10}, {3,15}
    // 2: {0,9}, {1,10}, {3,11}, {5,2}
    // 3: {1,15}, {2,11}, {4,6}
    // 4: {3,6}
    // 5: {0,14}, {2,2}
    
    int n = 6;
    vector<int> offsets = {0, 3, 6, 10, 13, 14, 16};
    vector<int> edges = {
        1, 2, 5,       // neighbors of 0
        0, 2, 3,       // neighbors of 1
        0, 1, 3, 5,    // neighbors of 2
        1, 2, 4,       // neighbors of 3
        3,             // neighbors of 4
        0, 2           // neighbors of 5
    };
    vector<int> weights = {
        7, 9, 14,      // weights for 0
        7, 10, 15,     // weights for 1
        9, 10, 11, 2,  // weights for 2
        15, 11, 6,     // weights for 3
        6,             // weights for 4
        14, 2          // weights for 5
    };

    int source = 5;
    int target = 0;

    int res_Dijkstra = dijkstra(offsets, edges, weights, n, target, source);
    cout << "Dijkstra result: ";
    if (res_Dijkstra == INT_MAX) cout << "No path";
    else cout << res_Dijkstra;
    cout << endl;

    int res_bellmanford = bellmanford(offsets, edges, weights, n, target, source);
    cout << "Bellman-Ford result: ";
    if (res_bellmanford == INT_MAX) cout << "No path";
    else cout << res_bellmanford;
    cout << endl;

    return 0;
}
