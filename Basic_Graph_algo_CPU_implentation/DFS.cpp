#include <bits/stdc++.h>

using namespace std;

vector<int> DFS(vector<vector<int>>& graph,int n) {
    vector<int> visited_order;
    vector<bool> visited(n, false);
    stack<int> s;
    s.push(0);
    visited[0]=true;
    while(!s.empty()){
        int node=s.top();
        visited_order.push_back(node);
        s.pop();
        for(int child:graph[node]){
            if(!visited[child]) {
                s.push(child);
                visited[child]=true;
            }
        }
    }
    return visited_order;
}

int main() {
    vector<vector<int>> graph = {
        {1, 3},
        {0, 2, 5},
        {1, 3, 4},
        {0, 2},
        {2, 5},
        {1, 4}
    };
    vector<int> visited_order=DFS(graph,6);
    for(auto node:visited_order){
        cout<<node<<" ";
    }
    return 0;
}