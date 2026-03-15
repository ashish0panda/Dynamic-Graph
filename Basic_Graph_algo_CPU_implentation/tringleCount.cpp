#include <bits/stdc++.h>
using namespace std;

long long countTriangles(const vector<vector<int>>& graph, int n) {
    long long count = 0;
    
    for (int u = 0; u < n; ++u) {
        for (int v : graph[u]) {
            if (v > u) {
                for (int w : graph[v]) {
                    if (w > v) {
                        for (int neighbor_u : graph[u]) {
                            if (neighbor_u == w) {
                                count++;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
    return count;
}

int main() {
    vector<vector<int>> graph = {
        {1, 2, 3},
        {0, 2, 3},
        {0, 1, 3, 4},
        {0, 1, 2},
        {2, 5},
        {4}
    };
    int n = 6;

    long long triangles = countTriangles(graph, n);
    cout << "Total Triangles: " << triangles << endl;

    return 0;
}
