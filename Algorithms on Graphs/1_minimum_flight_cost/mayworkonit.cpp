// #include <bits/stdc++.h>

// using namespace std;

// class myComparator{
//   public:
//     bool operator() (const int* p1, const int* p2){
//       return *p1 > *p2; 
//     }
// };

// void change_priority(priority_queue<pair<int, int> , vector<pair<int, int>>, myComparator> &Q,
//                      int i, int v){
//   vector<pair<int, int>> temp;
//   bool found=false;
//   while(!Q.empty()){
//     pair<int, int> u = Q.top();
//     Q.pop();
//     temp.push_back(u);
//     if(u.first == i){
//       found = true;
//       break;
//     }
//   }
//   if(found){
//     Q.push(make_pair(i, v));
//   }
//   for(const auto &j: temp){
//     Q.push(j);
//   }
// }

// long long distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
//   int n = adj.size();
//   vector<long long> dist(n, INT32_MAX);
//   // vector<int> prev(n, -1);
//   dist[s] = 0;
//   priority_queue<int*, vector<int*>, myComparator> H;
//   for(int i=0; i< n; i++){
//     H.push(*dist[i]);
//   }
//   // bool first_time = false;
//   while(!H.empty()){
//     pair<int, int> u = H.top();
//     H.pop();
//     for(int i=0; i< adj[u.first].size(); i++){
//       if(dist[adj[u.first][i]] > dist[u.first] + cost[u.first][i]){
//         dist[adj[u.first][i]] = dist[u.first] + cost[u.first][i];
//         // prev[adj[u][i]] = u;
//         change_priority(H, adj[u.first][i], dist[adj[u.first][i]]);
//       }
//     }
//     // if(!first_time && H.top().second == INT32_MAX) return -1;
//     // first_time = true;
//   } 
//   return (dist[t] == INT32_MAX) ? -1: dist[t];
// }

// int main() {
//   int n, m;
//   std::cin >> n >> m;
//   vector<vector<int> > adj(n, vector<int>());
//   vector<vector<int> > cost(n, vector<int>());
//   for (int i = 0; i < m; i++) {
//     int x, y, w;
//     std::cin >> x >> y >> w;
//     adj[x - 1].push_back(y - 1);
//     cost[x - 1].push_back(w);
//   }
//   int s, t;
//   std::cin >> s >> t;
//   s--, t--;
//   std::cout << distance(adj, cost, s, t);
// }
