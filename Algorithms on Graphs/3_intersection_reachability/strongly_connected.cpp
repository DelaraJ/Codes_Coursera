#include <bits/stdc++.h>

using namespace std;

vector<vector<int>> reverseGraph(vector<vector<int> > adj){
  int n= adj.size();
  vector<vector<int> > rG(n, vector<int>());
  for(int i=0; i<n; i++){
    for(int j : adj[i]){
      rG[j].push_back(i);
    }
  }
  return rG;
}

bool comparer(tuple<int, int, int> a, tuple<int, int, int> b){
  return (get<2>(a)>get<2>(b));
}

int Clock=1;
void dfs_with_pre_post_order(vector<tuple<int, int, int>> &prepost,
                            vector<vector<int>> &adj, 
                            vector<bool> &visited, int x){
  visited[x] = true;
  get<0>(prepost[x]) = x;
  get<1>(prepost[x]) = Clock;
  Clock++;
  for(int i : adj[x]){
    if(!visited[i]) dfs_with_pre_post_order(prepost, adj, visited, i);
  }
  get<2>(prepost[x]) = Clock;
  Clock++;
}

void Explore(vector<vector<int>> &adj, vector<int> &visit, int x, int j){
        visit[x] = j;
        for(int i : adj[x]){
            if(visit[i] == -1) Explore(adj, visit, i, j);
        }
    }

    int number_of_strongly_connected_components(vector<vector<int> > adj, vector<vector<int> > rGraph) {
        int result = 0, n= adj.size();
        vector<tuple<int, int, int>> prepost(n);
        vector<bool> visited(n, false);
        for(int i=0; i< n; i++){
            if(!visited[i]) dfs_with_pre_post_order(prepost, rGraph, visited, i);
        }
        // for(int i=0; i<n; i++) visited[i] = false;
        vector<int> visit(n, -1);
        int x=0;
        sort(prepost.begin(), prepost.end(), comparer);
        for(int i=0; i<n; i++){
            if(visit[get<0>(prepost[i])] == -1){
                Explore(adj, visit, get<0>(prepost[i]), x);
                x++;
            }
        }
        return result;
    }

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int>> rGraph(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    rGraph[y - 1].push_back(x - 1);
  }
  std::cout << number_of_strongly_connected_components(adj, rGraph);
}
