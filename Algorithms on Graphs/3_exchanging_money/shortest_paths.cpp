#include <bits/stdc++.h>

using namespace std;

void shortest_paths(vector<vector<long> > &adj,
                    vector<vector<long> > &cost, long s,
                    vector<long long> &distance,
                    vector<bool> &shortest,
                    vector<pair<pair<long, long>, long>> yalha){
  queue<long> nodes;
  queue<long> Q;
  int n = adj.size(); // nodes
  int m = yalha.size(); //yals
  distance[s] = 0;
  for(long i=0; i<n-1; i++){
    for(long j=0; j<m; j++){
      if(distance[yalha[j].first.first] != LONG_MAX && 
      distance[yalha[j].first.second] > distance[yalha[j].first.first] + yalha[j].second){
        distance[yalha[j].first.second] = distance[yalha[j].first.first] + yalha[j].second;
      }
    }
  }
  for(long j=0; j<m; j++){
    if(distance[yalha[j].first.first] != LONG_MAX) {
      if(distance[yalha[j].first.second] > distance[yalha[j].first.first] + yalha[j].second){
          nodes.push(yalha[j].first.first);
          shortest[yalha[j].first.first] = false;
        }
      }
    }

  while(!nodes.empty()){
    long u = nodes.front();
    nodes.pop();
    for(long v : adj[u]){
      if(shortest[v]){
        shortest[v] = false;
        nodes.push(v);
      }
    }
  }
}

int main() {
  long n, m, s;
  cin >> n >> m;
  vector<vector<long> > adj(n, vector<long>());
  vector<vector<long> > cost(n, vector<long>());
  vector<pair<pair<long, long>, long>> yalha(m, pair<pair<long, long>, long>());
  for (long i = 0; i < m; i++) {
    long x, y, w;
    cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
    yalha[i] = {{x - 1, y - 1}, w};
  }
  cin >> s;
  s--;
  if(n == 0) return 0;
  vector<long long> distance(n, LONG_MAX);
  vector<bool> reachable(n,false);
  vector<bool> shortest(n, true);
  shortest_paths(adj, cost, s, distance, shortest, yalha);
  for (long i = 0; i < n; i++) {
    if (distance[i] == LONG_MAX) {
      cout << "*\n";
    } else if (!shortest[i]) {
      cout << "-\n";
    } else {
      cout << distance[i] << "\n";
    }
  }
  return 0;
}
