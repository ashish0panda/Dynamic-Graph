#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> floyd_warshal(vector<vector<pair<int,int>>>& graph,int n) {
    vector<vector<int>> res(n,vector<int>(n,INT_MAX));
    for(int i=0;i<n;i++) {
        res[i][i]=0;
        for(auto child:graph[i]) {
            res[i][child.first] = child.second;
        }
    }
    for(int k=0;k<n;k++) {
        for(int i=0;i<n;i++) {
            for(int j=0;j<n;j++) {
                if(res[i][k]!=INT_MAX && res[k][j]!=INT_MAX && res[i][j]>res[i][k]+res[k][j]) {
                    res[i][j]=res[i][k]+res[k][j];
                }
            }
        }
    }

    return res;
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
    vector<vector<int>> res=floyd_warshal(graph,6);
    for(auto row:res) {
        for(auto val:row) {
            if(val==INT_MAX) {
                cout<<"INF ";
            }else {
                cout<<val<<" ";
            }
        }
        cout<<endl;
    }
}