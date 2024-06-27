#include <bits/stdc++.h>

using namespace std;

vector<bool> visited;
bool isCycle = false;

void Explore(vector<vector<int> > &adj, int v){
  visited[v] = true;
  int n = adj.size(), m = adj[v].size();
  for(int i=0; i<m; i++){
    if(visited[adj[v][i]]){
      isCycle = true;
      return;
    }
    Explore(adj, adj[v][i]);
  }
  visited[v] = false;
}

// void DFS(vector<vector<int> > &adj){
//   int n = adj.size();
//   visited.resize(n, false);
//   for(int i=0; i<n; i++){
//     if(!visited[i]) Explore(adj, i);
//   }
// }

int acyclic(vector<vector<int> > &adj) {
  int n = adj.size();
  visited.resize(n, false);
  for(int i=0; i<n; i++){
    if(isCycle) return 1;
    Explore(adj, i);
  }
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  cout << acyclic(adj);
}
