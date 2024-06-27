#include <bits/stdc++.h>

using namespace std;

int Dequeue(queue<int> &Q){
  int u= Q.back();
  Q.pop();
  return u;
}

int distance(vector<vector<int> > &adj, int s, int t) {
  int n = adj.size();
  vector<int> dist(n, -1);
  queue<int> Q;
  // vector<int> prev(n, NULL);
  dist[s] = 0;
  Q.push(s);
  while(!Q.empty()){
    // int u = Dequeue(Q);
    int u = Q.front();
    Q.pop();
    for(int v : adj[u]){
      if(dist[v] == -1){
        Q.push(v);
        dist[v] = dist[u] + 1;
        // prev[v] = u;
      }
    }
  }
  return dist[t];
}

int main() {
  int n, m;
  cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  cin >> s >> t;
  s--, t--;
  cout << distance(adj, s, t);
}
