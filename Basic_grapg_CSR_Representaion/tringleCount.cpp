#include <bits/stdc++.h>
using namespace std;

long long countTriangles(const vector<int>& offsets, const vector<int>& edges, int n) {
    long long count = 0;
    
    // To count each triangle {u, v, w} exactly once, we enforce u < v < w
    for (int u = 0; u < n; ++u) {
        for (int i = offsets[u]; i < offsets[u + 1]; ++i) {
            int v = edges[i];
            if (v > u) {
                // Look for common neighbors w of u and v such that w > v
                for (int j = offsets[v]; j < offsets[v + 1]; ++j) {
                    int w = edges[j];
                    if (w > v) {
                        // Check if w is also a neighbor of u
                        for (int k = offsets[u]; k < offsets[u + 1]; ++k) {
                            if (edges[k] == w) {
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
    // Sample graph (undirected) converted to CSR
    // 0: 1, 2, 3
    // 1: 0, 2, 3
    // 2: 0, 1, 3, 4
    // 3: 0, 1, 2
    // 4: 2, 5
    // 5: 4
    
    int n = 6;
    vector<int> offsets = {0, 3, 6, 10, 13, 15, 16};
    vector<int> edges = {
        1, 2, 3,       // neighbors of 0
        0, 2, 3,       // neighbors of 1
        0, 1, 3, 4,    // neighbors of 2
        0, 1, 2,       // neighbors of 3
        2, 5,          // neighbors of 4
        4              // neighbors of 5
    };

    long long triangles = countTriangles(offsets, edges, n);
    cout << "Total Triangles: " << triangles << endl;

    return 0;
}
