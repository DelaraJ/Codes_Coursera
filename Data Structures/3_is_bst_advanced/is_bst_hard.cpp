#include <bits/stdc++.h>

using namespace std;

struct Node {
  int key;
  int left;
  int right;
  Node() : key(0), left(-1), right(-1) {}
  Node(int key_, int left_, int right_) : key(key_), left(left_), right(right_) {}
};

void in_order(vector<int> &inOrderedTrevers, Node n, const vector<Node> &tree, bool &check) {
  if(n.left != -1)   in_order(inOrderedTrevers, tree[n.left], tree, check);
  if(n.key != tree[n.right].key) inOrderedTrevers.push_back(n.key);
  if(n.key == tree[n.left].key){
    check = false;
    return;
  }
  if(n.right != -1)  in_order(inOrderedTrevers, tree[n.right], tree, check);
}

bool IsBinarySearchTree(const vector<Node>& tree) {
  vector<int> inOrderedTrevers;
  bool check = true;
  in_order(inOrderedTrevers, tree[0], tree, check);
  if(check == false) return false;
  return is_sorted(inOrderedTrevers.begin(), inOrderedTrevers.end());
}
// void in_order(vector<int> &inOrderedTrevers, set<int> &inOrderedTreversSet, Node n, const vector<Node> &tree) {
//   if(n.left != -1)   in_order(inOrderedTrevers, inOrderedTreversSet, tree[n.left], tree);
//   if(n.key != tree[n.right].key){
//     inOrderedTreversSet.insert(n.key);
//     inOrderedTrevers.push_back(n.key);
//   } 
//   if(n.right != -1)  in_order(inOrderedTrevers, inOrderedTreversSet, tree[n.right], tree);
// }

// bool IsBinarySearchTree(const vector<Node>& tree) {
//   vector<int> inOrderedTrevers;
//   set<int> inOrderedTreversSet;
//   in_order(inOrderedTrevers, inOrderedTreversSet, tree[0], tree);
//   if(inOrderedTrevers.size() != inOrderedTreversSet.size()) return false;
//   return is_sorted(inOrderedTrevers.begin(), inOrderedTrevers.end());
// }

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
