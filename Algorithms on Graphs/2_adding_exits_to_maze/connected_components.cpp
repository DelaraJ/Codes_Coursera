#include <bits/stdc++.h>

using namespace std;

vector<bool> visited;
// vector<int> CCnum;
// vector<vector<int> > Adjancency;
void Explore(vector<vector<int> > adj, int v){
  visited[v] = true;
  for(int i=0; i<adj[v].size(); i++){
    if(!visited[adj[v][i]]) 
      Explore(adj, adj[v][i]);
  }
}

int DFS(vector<vector<int> > adj, int n){
  int cc=1;
  for(int i=0; i<n; i++){
    if(!visited[i]){
      Explore(adj, i);
      cc+=1;
    }
  }
  return cc;
}

int number_of_components(vector<vector<int> > &adj) {
  int res = DFS(adj, adj.size())-1;
  return res;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  visited.resize(n, false);
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << number_of_components(adj);
}
