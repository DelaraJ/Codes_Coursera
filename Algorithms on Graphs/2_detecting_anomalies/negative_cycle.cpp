#include <bits/stdc++.h>

using namespace std;

int negative_cycle(vector<pair<pair<int, int>, int>> &adj, int n) {
  int m = adj.size(); //tedade yal ha
  vector<long long> dist(n, INT32_MAX);
  dist[0] = 0;
  for(int i=0; i<n-1; i++){
    for(int j=0; j<m; j++){
      if(dist[adj[j].first.second] > dist[adj[j].first.first] + adj[j].second){
        dist[adj[j].first.second] = dist[adj[j].first.first] + adj[j].second;
      }
    }
  }
  for(int j=0; j<m; j++){
    if(dist[adj[j].first.second] > dist[adj[j].first.first] + adj[j].second){
      return 1;
    }
  }
  return 0;
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<pair<pair<int, int>, int> > adj(m, pair<pair<int, int>, int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    cin >> x >> y >> w;
    adj[i] = {{x - 1, y - 1}, w};
  }
  cout << negative_cycle(adj, n);
}
