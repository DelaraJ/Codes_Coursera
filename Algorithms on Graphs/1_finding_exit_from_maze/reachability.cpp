#include <bits/stdc++.h>

using namespace std;

vector<bool> visited;
// vector<int> CCnum;
// vector<vector<int> > Adjancency;
void Explore(vector<vector<int> > adj, int v){
  visited[v] = true;
  // CCnum[v-1] = cc;
  for(int i=0; i<adj[v].size(); i++){
    if(!visited[adj[v][i]]) 
      Explore(adj, adj[v][i]);
  }
}

// void DFS(int n){
//   int cc=1;
//   for(int i=0; i<n; i++){
//     if(!visited[i]) Explore(i+1, cc);
//     cc+=1;
//   }
// }

// void makeAdjList(vector<vector<int> > Adjancency, vector<vector<int> > adj, int n){
//   for(int i=0; i<n; i++){
//     Adjancency[adj[i][0]].push_back(adj[i][1]);
//     Adjancency[adj[i][1]].push_back(adj[i][0]);
//   }
// }

int reach(vector<vector<int> > &adj, int x, int y) {
  // DFS(adj.size());
  Explore(adj, x);
  if(visited[y]) return 1;
  return 0;
}

int main() {
  size_t n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  visited.resize(n, false);
  // CCnum.resize(n);
  // Adjancency.resize(n);
  // vector<vector<int> > Adjancency(n);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  // makeAdjList(Adjancency, adj, n);
  int x, y;
  cin >> x >> y;
  cout << reach(adj, x-1 , y-1);
}
