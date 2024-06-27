#include <bits/stdc++.h>

using namespace std;


struct Node {
  int key;
  int left;
  int right;

  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

bool comparer(pair< int, int> a, pair< int, int> b){
  if(a.first==b.first){
    if(b.second==(2*a.second)+2) return true;
    return false;
  }
  return (a.first<b.first);
}
bool check_sorted (vector<pair<int, int>>v, int n){
  if(n==0 || n==1) return true;
  for(int i=1; i<n; i++){
    if(comparer(v[i-1], v[i]) == false) return false;
  }
  return true;
}
void in_order(vector<pair<int, int>> &inOrderedTrevers, Node n, const vector<Node> &tree) {
  if(n.left != -1)   in_order(inOrderedTrevers, tree[n.left], tree);
  auto it = find_if(tree.begin(), tree.end(), [&](const Node& x) {return (x.key == n.key && x.left == n.left && x.right == n.right);});
  inOrderedTrevers.push_back(make_pair(n.key, distance(tree.begin(), it)));
  if(n.right != -1)  in_order(inOrderedTrevers, tree[n.right], tree);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  vector<pair<int, int>> inOrderedTrevers;
  in_order(inOrderedTrevers, tree[0], tree);
  return check_sorted(inOrderedTrevers, inOrderedTrevers.size());
}

int main() {
  int nodes;
  cin >> nodes;
  if(nodes == 0) cout << "CORRECT" << '\n';
  else{
    vector<Node> tree;
    for (int i = 0; i < nodes; ++i) {
      int key, left, right;
      cin >> key >> left >> right;
      tree.push_back(Node(key, left, right));
    }
    if (IsBinarySearchTree(tree)) {
      cout << "CORRECT" << '\n';
    } else {
      cout << "INCORRECT" << '\n';
    }
  }
  return 0;
}
