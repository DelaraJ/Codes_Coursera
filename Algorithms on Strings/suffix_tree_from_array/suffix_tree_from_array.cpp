#include <bits/stdc++.h>

using namespace std;

// Data structure to store edges of a suffix tree.
struct Edge {
  // The ending node of this edge.
  int node;
  // Starting position of the substring of the text 
  // corresponding to the label of this edge.
  int start;
  // Position right after the end of the substring of the text 
  // corresponding to the label of this edge.
  int end;

  int string_depth;

  Edge(int node_, int start_, int end_) : node(node_), start(start_), end(end_) {}
  Edge(const Edge& e) : node(e.node), start(e.start), end(e.end) {}
};

class Node{
  public:
  Node* parent;
  map<char, Node*> children;
  int string_depth;
  int start, end;
  Node() :
   parent(nullptr), string_depth(0), start(-1), end(-1){}
  Node(Node* _parent, int _string_depth, int _start, int _end) :
   parent(_parent), string_depth(_string_depth), start(_start), end(_end){}
};

Node* CreateNewLeaf(Node*& node, string& s, int suffix){
  Node* leaf = new Node(node, s.size()-suffix, suffix + node->string_depth, s.size()-1);
  node->children[s[leaf->start]] = leaf;
  return leaf;
}

Node* BreakEdge(Node*& node, string& s, int start, int offset){
  char startChar = s[start], midchar = s[start + offset];
  Node* midNode = new Node(node, node->string_depth + offset, start, start + offset -1);
  midNode->children[midchar] = node->children[startChar];
  node->children[startChar]->parent = midNode;
  node->children[startChar]->start += offset;
  node->children[startChar] = midNode;
  return midNode;
}

// Build suffix tree of the string text given its suffix array suffix_array
// and LCP array lcp_array. Return the tree as a mapping from a node ID
// to the vector of all outgoing edges of the corresponding node. The edges in the
// vector must be sorted in the ascending order by the first character of the edge label.
// Root must have node ID = 0, and all other node IDs must be different
// nonnegative integers.
//
// For example, if text = "ACACAA$", an edge with label "$" from root to a node with ID 1
// must be represented by Edge(1, 6, 7). This edge must be present in the vector tree[0]
// (corresponding to the root node), and it should be the first edge in the vector 
// // (because it has the smallest first character of all edges outgoing from the root).
// map<int, vector<Edge> > SuffixTreeFromSuffixArray(
//     const vector<int>& suffix_array,
//     const vector<int>& lcp_array,
//     const string& text) {
//   map<int, vector<Edge> > tree;
  
//   // Implement this function yourself
//   return tree;
// }

Node* SuffixTreeFromSuffixArray(
    vector<int>& suffix_array,
    vector<int>& lcp_array,
    string& text) {
      int ts = text.size();
  Node* root = new Node();
  int lcpPrev = 0;
  Node* curNode = root;
  for(int i=0; i<ts; i++){
    int suffix = suffix_array[i];
    while(curNode->string_depth > lcpPrev){
      curNode = curNode->parent;
    }
    if(curNode->string_depth == lcpPrev){
      curNode = CreateNewLeaf(curNode, text, suffix);
    }
    else{
      int edgeStart = suffix_array[i-1] + curNode->string_depth;
      int offset = lcpPrev - curNode->string_depth;
      Node* midNode = BreakEdge(curNode, text, edgeStart, offset);
      curNode = CreateNewLeaf(midNode, text, suffix);
    }
    if(i<ts-1) lcpPrev = lcp_array[i];
  }
  return root;

}

int main() {
  char buffer[200001];
  scanf("%s", buffer);
  string text = buffer;
  vector<int> suffix_array(text.length());
  for (int i = 0; i < text.length(); ++i) {
    scanf("%d", &suffix_array[i]);
  }
  vector<int> lcp_array(text.length() - 1);
  for (int i = 0; i + 1 < text.length(); ++i) {
    scanf("%d", &lcp_array[i]);
  }
  // Build the suffix tree and get a mapping from 
  // suffix tree node ID to the list of outgoing Edges.
  vector<char>x {'T', 'G', 'C', 'A', '$'};
  Node* root = SuffixTreeFromSuffixArray(suffix_array, lcp_array, text);
  printf("%s\n", buffer);
  stack<Node*> q;
  for(int i=0; i<5; i++){
    if(root->children.find(x[i]) != root->children.end()){
      q.push(root->children[x[i]]);
    }
  }
  while(!q.empty()){
    auto tmp = q.top();
    q.pop();
    printf("%d %d\n",tmp->start, tmp->end+1);
    // cout<< text.substr(tmp->start, tmp->end -tmp->start +1) << endl;
    for(int i=0; i<5; i++){
      if(tmp->children.find(x[i]) != tmp->children.end()){
        q.push(tmp->children[x[i]]);
      }
    }
  }
  // Output the edges of the suffix tree in the required order.
  // Note that we use here the contract that the root of the tree
  // will have node ID = 0 and that each vector of outgoing edges
  // will be sorted by the first character of the corresponding edge label.
  //
  // The following code avoids recursion to avoid stack overflow issues.
  // It uses a stack to convert recursive function to a while loop.
  // The stack stores pairs (node, edge_index). 
  // This code is an equivalent of 
  //
  //    OutputEdges(tree, 0);
  //
  // for the following _recursive_ function OutputEdges:
  //
  // void OutputEdges(map<int, vector<Edge> > tree, int node_id) {
  //   const vector<Edge>& edges = tree[node_id];
  //   for (int edge_index = 0; edge_index < edges.size(); ++edge_index) {
  //     printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
  //     OutputEdges(tree, edges[edge_index].node);
  //   }
  // }
  //
  // vector<pair<int, int> > stack(1, make_pair(0, 0));    
  // while (!stack.empty()) {
  //   pair<int, int> p = stack.back();
  //   stack.pop_back();
  //   int node = p.first;
  //   int edge_index = p.second;
  //   if (!tree.count(node)) {
  //     continue;
  //   }
  //   const vector<Edge>& edges = tree[node];
  //   if (edge_index + 1 < edges.size()) {
  //     stack.push_back(make_pair(node, edge_index + 1));
  //   }
  //   printf("%d %d\n", edges[edge_index].start, edges[edge_index].end);
  //   stack.push_back(make_pair(edges[edge_index].node, 0));
  // }


  return 0;
}
