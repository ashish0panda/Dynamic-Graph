#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> floyd_warshal(const vector<int>& offsets, const vector<int>& edges, const vector<int>& weights, int n) {
    vector<vector<int>> res(n, vector<int>(n, INT_MAX));
    
    for (int i = 0; i < n; i++) {
        res[i][i] = 0;
        // In CSR, neighbors of i are in edges[offsets[i] ... offsets[i+1]-1]
        for (int j = offsets[i]; j < offsets[i + 1]; ++j) {
            int v = edges[j];
            int w = weights[j];
            res[i][v] = w;
        }
    }

    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (res[i][k] != INT_MAX && res[k][j] != INT_MAX && res[i][j] > res[i][k] + res[k][j]) {
                    res[i][j] = res[i][k] + res[k][j];
                }
            }
        }
    }

    return res;
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

    vector<vector<int>> res = floyd_warshal(offsets, edges, weights, n);

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (res[i][j] == INT_MAX) {
                cout << "INF ";
            } else {
                cout << res[i][j] << " ";
            }
        }
        cout << endl;
    }

    return 0;
}
