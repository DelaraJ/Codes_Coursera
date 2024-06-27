#include <bits/stdc++.h>

using namespace std;

int optimal_weight(int W, vector<int> weights) {
  weights.insert(weights.begin(), 0);
  int items = weights.size();
  vector<vector<int>> table(W+1, vector<int> (items, 0));
  for(int i=0; i<=W; i++) table[i][0]=i;
  for(int j=1; j<items; j++)
  {
    for(int w=1; w<=W; w++)
    {
      table[w][j]=table[w][j-1];
      if(w>=weights[j])
        table[w][j]=min(table[w][j], table[w-weights[j]][j-1]);
    }
  }
  return table[W][items-1];
}



int recursive_optimal_weight(int W, vector<int> weights,int lastw, vector<vector<int>> &table) {



  if(table[W][lastw-1]==-1) table[W][lastw-1]=recursive_optimal_weight(W, weights, lastw-1, table);
  table[W][lastw] = table[W][lastw-1];

  if(W>=weights[lastw])
  {
    if(table[W-weights[lastw]][lastw-1]==-1) 
      table[W-weights[lastw]][lastw-1] = recursive_optimal_weight(W-weights[lastw], weights, lastw-1, table);
    table[W][lastw]= min(table[W][lastw], table[W-weights[lastw]][lastw-1]);
  }
  // cout<<"table["+to_string(W)+"]["+to_string(lastw)+"]="+to_string(table[W][lastw])<<endl;
  return table[W][lastw];
  
}
// int real_recursive_optimal_weight(int W, vector<int> weights,int lastw, vector<vector<int>> &table) {

//   if(table[W][lastw-1]==-1) table[W][lastw-1]=real_recursive_optimal_weight(W, weights, lastw-1, table);
//   table[W][lastw] = table[W][lastw-1];

//   if(W>=weights[lastw])
//   {
//     if(table[W-weights[lastw]][lastw-1]==-1) 
//       table[W-weights[lastw]][lastw-1] = real_recursive_optimal_weight(W-weights[lastw], weights, lastw-1, table);
//     table[W][lastw]= max(W-table[W][lastw], W-table[W-weights[lastw]][lastw-1]);
//   }
//   cout<<"table["+to_string(W)+"]["+to_string(lastw)+"]="+to_string(table[W][lastw])<<endl;
//   return table[W][lastw];

// }
int recursive_optimal_weight(int W, vector<int> weights) {

  weights.insert(weights.begin(), 0);
  int items = weights.size();
  vector<vector<int>> table(W+1, vector<int> (items, -1));
  for(int i=0; i<=W; i++) table[i][0]=i;
  for(int i=0; i<items; i++) table[0][i]=0;
  int check =0;
  for(int i=1; i<items; i++)
  {
    if(weights[i]<=W)
    {
      check =1;
      break;
    }
  }
  if(check==0) return 0;
  int modW= recursive_optimal_weight(W, weights, weights.size()-1, table);
  return (W-modW==0)? W : W-modW;

}
// int real_recursive_optimal_weight(int W, vector<int> weights) {

//   weights.insert(weights.begin(), 0);
//   int items = weights.size();
//   vector<vector<int>> table(W+1, vector<int> (items, -1));
//   for(int i=0; i<=W; i++) table[i][0]=i;
//   for(int i=0; i<items; i++) table[0][i]=0;
  
//   return real_recursive_optimal_weight(W, weights, weights.size()-1, table);

// }


int main() {
  int n, W;
  std::cin >> W >> n;
  vector<int> w(n);
  for (int i = 0; i < n; i++) {
    std::cin >> w[i];
  }
  std::cout << recursive_optimal_weight(W, w) << '\n';
}
