#include <bits/stdc++.h>

using namespace std;

struct point{
  double x,y;
  int pNum;
  point(double x, double y):x(x), y(y){}
  point() : x(0.0), y(0.0), pNum(0) {}
};
struct adj{
  point start, end;
  double weight;

  double distance(point p1, point p2){
    return sqrt((p1.x - p2.x)*(p1.x - p2.x) + (p1.y - p2.y)*(p1.y - p2.y));
  }

  adj(point start, point end) : start(start), end(end)/*, weight(distance(start, end))*/{
    weight = distance(start, end);
  }
  adj():start(point()), end(point()), weight(0){}


};
vector<adj> adjs;
vector<int> parent;
vector<int> Rank;
vector<point> points;
bool comparer(adj a1, adj a2){
  return a1.weight <= a2.weight;
}

int Find(int i){
  if(parent[i] == -1){
    return i;
  }
  return parent[i] = Find(parent[i]);
}
void Union(int i, int j){
  int i_id = Find(i);
  int j_id = Find(j);
  if(i_id == j_id) return;
  if(Rank[i_id] > Rank[j_id])
    parent[j_id] = i_id;
  else{
    parent[i_id] = j_id;
    if(Rank[i_id] == Rank[j_id])
      Rank[j_id] = Rank[i_id]+1;
  }
}


double clustering(vector<point> points, int k) {
  double result = 0.;
  int n = points.size();
  vector<adj> mst;
  parent.resize(n,-1);
  Rank.resize(n, 1);
  for(int i=0; i<n; i++){
    for(int j=i+1; j<n; j++){
      adjs.push_back(adj(points[i], points[j]));
    }
  }
  sort(adjs.begin(), adjs.end(), comparer);
  //
  // result = adjs[0].weight;
  for(const auto& a : adjs){
    int q = Find(a.start.pNum);
    int w = Find(a.end.pNum);
    if(q != w && n==k) return a.weight;
    if(q != w){
      Union(a.start.pNum, a.end.pNum);
      n--;
      // result = a.weight;
    }
  }
  return result;
} 

int main() {
  size_t n;
  int k;
  cin >> n;
  points.resize(n);
  for (size_t i = 0; i < n; i++) {
    cin >> points[i].x >> points[i].y;
    points[i].pNum = i;
  }
  cin >> k;
  cout << fixed << setprecision(10) << clustering(points, k) << endl;
}
