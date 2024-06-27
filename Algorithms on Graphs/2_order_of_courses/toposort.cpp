#include <bits/stdc++.h>

using namespace std;

stack<int> ss;
vector<bool> visited;
vector<int> inDegree;
vector<int> outDegree;
vector<pair<int, int>> yalha;
vector<vector<int> > adj;

int toposort() {
  int m = yalha.size();

  for(int i=0; i<m; ++i){
    if(inDegree[yalha[i].second] == 1) return i;
  }
  return -1;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  visited.resize(n);
  inDegree.resize(n);
  outDegree.resize(n);
  yalha.resize(m);
  adj.resize(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    inDegree[y-1]++;
    outDegree[x-1]++;
    yalha[i] = {x-1, y-1};
  }
  cout<< 1<< '\n' << toposort();
}
