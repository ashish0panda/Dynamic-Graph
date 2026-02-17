#include <bits/stdc++.h>

using namespace std;

int dijkstra(vector<vector<pair<int,int>>>& graph,int n,int target, int source) {
    vector<int> dist(n,INT_MAX);
    dist[source]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>> pq;
    pq.push({0,source});
    while(!pq.empty()){
        int node=pq.top().second;
        if(dist[node]<pq.top().first) {
            pq.pop();
            continue;
        }
        pq.pop();
        for(auto child:graph[node]){
            if(dist[child.first]>dist[node]+child.second){
                dist[child.first]=dist[node]+child.second;
                pq.push({dist[child.first],child.first});
            }
        }
    }
    return dist[target];
}

int bellmanford(vector<vector<pair<int,int>>>& graph,int n,int target, int source) {
    vector<int> dist(n,INT_MAX);
    dist[source]=0;
    for(int i=0;i<n-1;i++){
        for(int j=0;j<n;j++){
            if (dist[j] == INT_MAX) {
                continue;
            }
            for(auto child:graph[j]){
                if(dist[child.first]>dist[j]+child.second){
                    dist[child.first]=dist[j]+child.second;
                }
            }
        }
    }
    return dist[target];
}

int main() {
    vector<vector<pair<int,int>>> graph = {
        {{1,7}, {2,9}, {5,14}},
        {{0,7}, {2,10}, {3,15}},
        {{0,9}, {1,10}, {3,11}, {5,2}},
        {{1,15}, {2,11}, {4,6}},
        {{3,6}},
        {{0,14}, {2,2}}
    };
    int res_Dijkstra=dijkstra(graph,6,0,5);
    if(res_Dijkstra==INT_MAX) {
        cout<<"No path";
    }else {
        cout<<res_Dijkstra;
    }
    cout<<endl;
    int res_bellmanford=bellmanford(graph,6,0,5);
    if(res_bellmanford==INT_MAX) {
        cout<<"No path";
    }else {
        cout<<res_bellmanford;
    }

}