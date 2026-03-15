#include<bits/stdc++.h>

using namespace std;

vector<int> greedy_mis(const vector<vector<int>>& graph, int n) {
    vector<int> mis;
    vector<bool> excluded(n, false);

    for (int i = 0; i < n; ++i) {
        if (!excluded[i]) {
            mis.push_back(i);
            for (int neighbor : graph[i]) {
                excluded[neighbor] = true;
            }
        }
    }
    return mis;
}

int main() {
    // Sample graph (undirected)
    vector<vector<int>> graph = {
        {1, 3},
        {0, 2, 5},
        {1, 3, 4},
        {0, 2},
        {2, 5},
        {1, 4}
    };
    int n = 6;

    vector<int> result = greedy_mis(graph, n);

    cout << "Maximal Independent Set: { ";
    for (int node : result) {
        cout << node << " ";
    }
    cout << "}" << endl;

    return 0;
}
