#include <bits/stdc++.h>

using namespace std;

vector<int> BFS(vector<vector<int>>& graph,int n) {
    vector<int> visited_order;
    vector<bool> visited(n, false);
    queue<int> q;
    q.push(0);
    visited[0]=true;
    while(!q.empty()){
        int node=q.front();
        visited_order.push_back(node);
        q.pop();
        for(int child:graph[node]){
            if(!visited[child]){
                q.push(child);
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
    int size=6;
    vector<int> visited_order=BFS(graph,6);
    for(auto node:visited_order){
        cout<<node<<" ";
    }
    return 0;
}