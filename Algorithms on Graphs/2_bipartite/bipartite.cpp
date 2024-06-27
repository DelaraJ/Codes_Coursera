#include <bits/stdc++.h>
using namespace std;

bool distance(vector<vector<int> > &adj,
              // map<int, vector<int>> &distmap,
              vector<int> &dist,
              vector<int> &visited,
              vector<int> &bfsvisited,
              int s) {
  queue<int> Q;
  // map<int, vector<int>> distmap_vec;
  // map<int, set<int>> distmap_set;
  // vector<int> prev(n, NULL);
  dist[s] = 0;
  // distmap[0].push_back(s);
  Q.push(s);
  visited[s] = true;
  bfsvisited[s] = true;
  while(!Q.empty()){
    // int u = Dequeue(Q);
    int u = Q.front();
    Q.pop();
    for(int v : adj[u]){
      if(dist[v] == -1){
        visited[v] = true;
        bfsvisited[v] = true;
        Q.push(v);
        dist[v] = dist[u] + 1;
        // distmap_vec[dist[u] + 1].push_back(v);
        // distmap_set[dist[u] + 1].insert(v);
        // if(distmap_vec[dist[u] + 1].size() != distmap_set[dist[u] + 1].size()) return false;
        // prev[v] = u;
      }
      else if(dist[v] == dist[u]) return false;
    }
  }
  return true;
}


int bipartite(vector<vector<int> > &adj) {
  int n = adj.size();
  vector<int> dist(n, -1);
  vector<int> visited(n, false);
  vector<int> bfsvisited(n, false);
  for(int i=0; i<n; i++){
    if(!bfsvisited[i]){
      if(!distance(adj, dist, visited, bfsvisited, i)) return 0;
      // for(int j=0; j<n; j++){
      //   if(visited[j]){
      //     for(int k : adj[j]){
      //       if(dist[k] == dist[j]) return 0;
      //     }
      //   }
      // }
      for(int j=0; j<n; j++){
        dist[j] = -1;
        visited[j] = false;
      }
    }
  }
  return 1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  std::cout << bipartite(adj);
}
