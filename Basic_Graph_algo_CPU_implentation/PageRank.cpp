#include <bits/stdc++.h>
using namespace std;

vector<double> pagerank(const vector<vector<int>>& graph, int n, double damping = 0.85, int iterations = 100) {
    vector<double> pr(n, 1.0 / n);
    vector<int> out_degree(n, 0);
    
    for (int i = 0; i < n; ++i) {
        out_degree[i] = graph[i].size();
    }

    for (int iter = 0; iter < iterations; ++iter) {
        vector<double> next_pr(n, (1.0 - damping) / n);
        double dangling_sum = 0;

        for (int i = 0; i < n; ++i) {
            if (out_degree[i] > 0) {
                for (int neighbor : graph[i]) {
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
    // Sample directed graph
    vector<vector<int>> graph = {
        {1, 2},    // 0 -> 1, 0 -> 2
        {2},       // 1 -> 2
        {0},       // 2 -> 0
        {2}        // 3 -> 2
    };
    int n = 4;

    vector<double> results = pagerank(graph, n);

    cout << "PageRank scores:" << endl;
    for (int i = 0; i < n; ++i) {
        cout << "Node " << i << ": " << fixed << setprecision(4) << results[i] << endl;
    }

    return 0;
}
