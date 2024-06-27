#include <bits/stdc++.h>

using namespace std;

int findMin(vector<long long> dist, vector<bool> processed){
  long long m = INT32_MAX/2 + 1;
  int index = 0;
  for(int i=0; i< dist.size(); i++){
    if(!processed[i] && (dist[i]<m)){
      m = dist[i];
      index = i;
    }
  }
  return index;
}

long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  int n = adj.size();
  vector<long long> dist(n);
  vector<bool> processed(n);
  for(int i=0; i< n; i++){
    dist[i] = INT32_MAX/2;
  }
  dist[s] = 0;
  vector<int> safeZone;
  while(safeZone.size() != n){
    for(int j=0; j< adj[s].size(); j++){
      if(dist[adj[s][j]] > dist[s] + cost[s][j]){
        dist[adj[s][j]] = dist[s] + cost[s][j];
        // prev[adj[u][i]] = u;
      }
    }
    safeZone.push_back(s);
    processed[s] = true;
    s=findMin(dist, processed);
    // if(!first_time && H.top().second == INT32_MAX) return -1;
    // first_time = true;
  } 
  return (dist[t] == INT32_MAX/2) ? -1: dist[t];
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
