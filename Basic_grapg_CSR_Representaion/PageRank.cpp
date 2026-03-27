#include <bits/stdc++.h>
using namespace std;

vector<double> pagerank(const vector<int>& offsets, const vector<int>& edges, int n, double damping = 0.85, int iterations = 100) {
    vector<double> pr(n, 1.0 / n);
    vector<int> out_degree(n, 0);
    
    for (int i = 0; i < n; ++i) {
        out_degree[i] = offsets[i + 1] - offsets[i];
    }

    for (int iter = 0; iter < iterations; ++iter) {
        vector<double> next_pr(n, (1.0 - damping) / n);
        double dangling_sum = 0;

        for (int i = 0; i < n; ++i) {
            if (out_degree[i] > 0) {
                // In CSR, neighbors of i are in edges[offsets[i] ... offsets[i+1]-1]
                for (int j = offsets[i]; j < offsets[i + 1]; ++j) {
                    int neighbor = edges[j];
                    next_pr[neighbor] += damping * pr[i] / out_degree[i];
                }
            } else {
                dangling_sum += damping * pr[i] / n;
            }
        }

        for (int i = 0; i < n; ++i) {
            next_pr[i] += dangling_sum;
        }
        pr = next_pr;
    }
    return pr;
}

int main() {
    // Sample directed graph converted to CSR
    // 0 -> 1, 0 -> 2
    // 1 -> 2
    // 2 -> 0
    // 3 -> 2
    int n = 4;
    vector<int> offsets = {0, 2, 3, 4, 5};
    vector<int> edges = {
        1, 2, // neighbors of 0
        2,    // neighbors of 1
        0,    // neighbors of 2
        2     // neighbors of 3
    };

    vector<double> results = pagerank(offsets, edges, n);

    cout << "PageRank scores:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << fixed << setprecision(4) << results[i] << endl;
    }

    return 0;
}
